
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <time.h>
#include <sys/prctl.h>
#include <pthread.h>
#include <semaphore.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <dirent.h>
#include <linux/unistd.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/route.h>
#include <sys/time.h>

#include "QMAPI.h"
#include "QMAPINetSdk.h"
#include "zn_dh_base_type.h"
#include "zhinuo_search_protocol.h"

static int g_zhinuo_sock = 0;
static int g_dahua_sock = 0;

static int g_zhinuo_handle = 0;
static int g_run_flag = 0;
extern int g_nw_search_run_index;

void ZhiNuo_SetHandle(int handle)
{
	g_zhinuo_handle = handle;
}

/////////////////////////////////////////////////////////////////////////
void* ZhiNuo_Broadcast_Thread(void *param)
{
	prctl(PR_SET_NAME, (unsigned long)"ZhiNuo_Broadcast_Thread", 0, 0, 0);
	X6_TRACE("ZhiNuo_Broadcast_Thread pid:%d\n", getpid());

	int i = 0;
	int nWidth = 0;
	int nHeight = 0;
	int n_max_resolution = 0;
	int n_extra_len = 0;
	char a_extra_sting[255];
	int n_offset = 0;
	char mac[17];

	int sockedfd = -1;

	// �󶨵�ַ  
	struct sockaddr_in addrto;
	bzero(&addrto, sizeof(struct sockaddr_in));
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = htonl(INADDR_ANY);
	addrto.sin_port = htons(ZHINUO_RCV_PORT);

	// �㲥��ַ  
	struct sockaddr_in from;
	bzero(&from, sizeof(struct sockaddr_in));

	if ((g_zhinuo_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		X6_TRACE("socket error\n");
		return NULL;
	}

	const int opt = 1;

	//���ø��׽���Ϊ�㲥���ͣ�  
	int nb = 0;
	nb = setsockopt(g_zhinuo_sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set socket error...\n");
		goto ZhiNuo_Search_End;
	}

	struct ifreq ifr;
	struct sockaddr_in broadcast_addr;      /*���ص�ַ*/
	
	sockedfd = socket(AF_INET, SOCK_DGRAM, 0);/*�������ݱ��׽���*/
	if (sockedfd < 0)
	{
		X6_TRACE("socket error\n");
		goto ZhiNuo_Search_End;
	}
	strcpy(ifr.ifr_name, IFNAME);
	if (ioctl(g_zhinuo_sock, SIOCGIFBRDADDR, &ifr) == -1)
	{
		;// perror("ioctl error"), exit(1);			//
	}

	memcpy(&broadcast_addr, &ifr.ifr_broadaddr, sizeof(struct sockaddr_in));
	broadcast_addr.sin_port = htons(ZHINUO_SEND_PORT);/*���ù㲥�˿�*/

	nb = setsockopt(sockedfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set sockedfd error...\n");
		goto ZhiNuo_Search_End;
	}

	if (bind(g_zhinuo_sock, (struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1)
	{
		X6_TRACE("bind error...\n");
		goto ZhiNuo_Search_End;
	}

	int len = sizeof(struct sockaddr_in);
	char smsg[1024] = { 0 };

	int ret = 0;
	struct timeval timeout;
	fd_set readfd; //���ļ�����������
	while (1)
	{
		timeout.tv_sec = 10;  //��ʱʱ��Ϊ2��
		timeout.tv_usec = 0;
		//�ļ���������0
		FD_ZERO(&readfd);
		//���׽����ļ����������뵽�ļ�������������
		FD_SET(g_zhinuo_sock, &readfd);
		//select�����Ƿ������ݵ���
		ret = select(g_zhinuo_sock + 1, &readfd, NULL, NULL, &timeout);
		if (0 == g_run_flag)
		{
			break;
		}

		if (FD_ISSET(g_zhinuo_sock, &readfd))
		{
			//�ӹ㲥��ַ������Ϣ  
			ret = recvfrom(g_zhinuo_sock, smsg, 1024, 0, (struct sockaddr*)&from, (socklen_t*)&len);
			if (ret <= 0)
			{
				X6_TRACE("read error....\n");
			}
			else
			{
				//int rcv_msg_len = 0;
				char tem_buf[DVRIP_HEAD_T_SIZE] = { 0 };
				memcpy(tem_buf, smsg, DVRIP_HEAD_T_SIZE);
				DVRIP_HEAD_T *t_msg_head = (DVRIP_HEAD_T *)tem_buf;
				char * extra = smsg + DVRIP_HEAD_T_SIZE;

				//X6_TRACE("type:%d, cmd:%x,len:%d,%s,extra:%d,fromip:%s,fromeport:%d\n", t_msg_head->c[16], t_msg_head->dvrip.cmd, ret, smsg, t_msg_head->dvrip.dvrip_extlen, inet_ntoa(from.sin_addr), from.sin_port);                  
				if (CMD_DEV_SEARCH == t_msg_head->dvrip.cmd)
				{
					n_offset = 0;
					char extra_data[164] = { 0 };
					ZhiNuo_Dev_Search * str_dev_search = (ZhiNuo_Dev_Search *)extra_data;

					//��ȡ�������������
					QMAPI_NET_NETWORK_CFG st_ipc_net_info;
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
					{
						X6_TRACE("QMAPI_SYSCFG_GET_NETCFG fail\n");
						goto ZhiNuo_Search_End;
					}

					str_dev_search->Version[0] = 0X32;  //�汾��Ϣ 
					str_dev_search->Version[1] = 0X33;
					str_dev_search->Version[2] = 0X30;
					str_dev_search->Version[3] = 0X32;

					str_dev_search->HostName[0] = 0x44; //������
					str_dev_search->HostName[1] = 0x56;
					str_dev_search->HostName[2] = 0x52;

					//��ȡ�������������
					QMAPI_NET_WIFI_CONFIG st_wifi_net_info;
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
					{
						X6_TRACE("QMAPI_SYSCFG_GET_WIFICFG fail\n");
						goto ZhiNuo_Search_End;
					}

					struct sockaddr_in adr_inet;

					//������߿��þ�ֻ�����ߵ�����
					//if(st_wifi_net_info.bWifiEnable && st_wifi_net_info.byStatus == 0)
					if (st_wifi_net_info.bWifiEnable && st_wifi_net_info.byStatus == 0 && 1 != st_wifi_net_info.byWifiMode)
					{
						inet_aton(st_wifi_net_info.dwNetIpAddr.csIpV4, &adr_inet.sin_addr);
						str_dev_search->HostIP = (unsigned long)adr_inet.sin_addr.s_addr;
//						X6_TRACE("ip:%s\n", (char *)inet_ntoa(str_dev_search->HostIP));
						inet_aton(st_wifi_net_info.dwNetMask.csIpV4, &adr_inet.sin_addr);
						str_dev_search->Submask = (unsigned long)adr_inet.sin_addr.s_addr;
						inet_aton(st_wifi_net_info.dwGateway.csIpV4, &adr_inet.sin_addr);
						str_dev_search->GateWayIP = (unsigned long)adr_inet.sin_addr.s_addr;
						inet_aton(st_wifi_net_info.dwDNSServer.csIpV4, &adr_inet.sin_addr);
						str_dev_search->DNSIP = (unsigned long)adr_inet.sin_addr.s_addr;
					}
					else
					{
						inet_aton(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, &adr_inet.sin_addr);
						str_dev_search->HostIP = (unsigned long)adr_inet.sin_addr.s_addr;
//						X6_TRACE("ip:%s\n", (char *)inet_ntoa(str_dev_search->HostIP));
						inet_aton(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, &adr_inet.sin_addr);
						str_dev_search->Submask = (unsigned long)adr_inet.sin_addr.s_addr;
						inet_aton(st_ipc_net_info.stGatewayIpAddr.csIpV4, &adr_inet.sin_addr);
						str_dev_search->GateWayIP = (unsigned long)adr_inet.sin_addr.s_addr;
						inet_aton(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, &adr_inet.sin_addr);
						str_dev_search->DNSIP = (unsigned long)adr_inet.sin_addr.s_addr;
					}
					inet_aton("10.1.0.2", &adr_inet.sin_addr);
					str_dev_search->AlarmServerIP = (unsigned long)adr_inet.sin_addr.s_addr;
					str_dev_search->HttpPort = st_ipc_net_info.wHttpPort;
					str_dev_search->TCPPort = TCP_LISTEN_PORT;
					str_dev_search->TCPMaxConn = MAX_LINK_NUM;
					str_dev_search->SSLPort = 8443;
					str_dev_search->UDPPort = 8001;
					inet_aton("239.255.42.42", &adr_inet.sin_addr);
					str_dev_search->McastIP = (unsigned long)adr_inet.sin_addr.s_addr;
					str_dev_search->McastPort = 36666;

					//rcv_msg_len = DVRIP_HEAD_T_SIZE + t_msg_head->dvrip.dvrip_extlen;
					char send_msg[512] = { 0 };
					t_msg_head = (DVRIP_HEAD_T *)send_msg;
					memset(send_msg, 0, sizeof(send_msg));

					t_msg_head->dvrip.dvrip_extlen = 0xa4;  //�̶�Ϊ164             
					t_msg_head->dvrip.cmd = ACK_DEV_SEARCH;
					t_msg_head->c[16] = 2; //�̶�Ϊ2
					t_msg_head->c[19] = 0; //������ 0:���� 1:��Ȩ�� 2:�޶�Ӧ�����ṩ

					struct sockaddr_in udpaddrto;
					bzero(&udpaddrto, sizeof(struct sockaddr_in));
					udpaddrto.sin_family = AF_INET;
					udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
					udpaddrto.sin_port = htons(ZHINUO_SEND_PORT);
					n_offset += DVRIP_HEAD_T_SIZE;

					memcpy(send_msg + n_offset, &extra_data, sizeof(extra_data));
					n_offset += sizeof(extra_data);
					sprintf(send_msg + n_offset, "%02x:%02x:%02x:%02x:%02x:%02x", st_ipc_net_info.stEtherNet[0].byMACAddr[0],
							st_ipc_net_info.stEtherNet[0].byMACAddr[1],
							st_ipc_net_info.stEtherNet[0].byMACAddr[2],
							st_ipc_net_info.stEtherNet[0].byMACAddr[3],
							st_ipc_net_info.stEtherNet[0].byMACAddr[4],
							st_ipc_net_info.stEtherNet[0].byMACAddr[5]);
					memcpy(mac, send_msg + n_offset, 17);
					//memcpy(temp, &st_net_info.szMac, 17);
					n_offset += 17;

					n_max_resolution = 0;
					QMAPI_NET_SUPPORT_STREAM_FMT stSupportFmt;
					QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT, 0, &stSupportFmt, sizeof(stSupportFmt));
					for (i = 0; i < 9; i++)
					{
						if (stSupportFmt.stVideoSize[0][i].nWidth * stSupportFmt.stVideoSize[0][i].nHeight > n_max_resolution)
						{
							nWidth = stSupportFmt.stVideoSize[0][i].nWidth;
							nHeight = stSupportFmt.stVideoSize[0][i].nHeight;
							n_max_resolution = nWidth * nHeight;
						}
					}

					memset(a_extra_sting, 0, sizeof(a_extra_sting));
					sprintf(a_extra_sting, "IPC%5d*%-5d", nWidth, nHeight);
					n_extra_len = strlen(a_extra_sting);
					strncpy(send_msg + n_offset, a_extra_sting, n_extra_len);
					n_offset += n_extra_len;
					t_msg_head->c[2] = 17 + n_extra_len;   //mac��ַ���ȼ����豸����

					//memcpy(send_msg + n_offset, DEV_NAME, strlen(DEV_NAME));
					//n_offset += strlen(DEV_NAME);

					//�ӹ㲥��ַ������Ϣ  
					usleep(500000); //˯��500���룬����nvr��������̫�࣬�������������֤nvrÿ�ζ����ѵ��豸
					ret = sendto(sockedfd, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
					if (ret <= 0)
					{
						X6_TRACE("send error....:%d\n", ret);
					}
				}
				if (CMD_ZHINUO_LOG_ON == t_msg_head->dvrip.cmd)
				{
					X6_TRACE("name:%s, pass:%s, cmd:%x, extralen:%d, extra:%s, clienttype:%d, locktype:%d, hl:%d, v:%d\n",
							 t_msg_head->dvrip.dvrip_p, &t_msg_head->dvrip.dvrip_p[8], t_msg_head->dvrip.cmd
							 , t_msg_head->dvrip.dvrip_extlen, extra, t_msg_head->dvrip.dvrip_p[18],
							 t_msg_head->dvrip.dvrip_p[19], t_msg_head->dvrip.dvrip_hl, t_msg_head->dvrip.dvrip_v);

					if (0 == strncmp(mac, extra, 17))
					{
						char send_msg[BUFLEN] = { 0 };
						DVRIP_HEAD_T *t_msg_head_send = (DVRIP_HEAD_T *)send_msg;
						ZERO_DVRIP_HEAD_T(t_msg_head_send)

							t_msg_head_send->c[1] = 0; //0��û�� 1�����ж໭��Ԥ������                         
						t_msg_head_send->c[8] = 1; //0: ��ʾ��¼�ɹ� 1: ��ʾ��¼ʧ�� 3: �û��ѵ�¼  

						int n_index = 0;
						for (n_index = 0; n_index < 10; n_index++)
						{
							//��ȡ�û�������
							QMAPI_NET_USER_INFO st_user_info;
							if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_USERCFG, n_index, &st_user_info, sizeof(QMAPI_NET_USER_INFO)))
							{
								X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
								goto ZhiNuo_Search_End;
							}

							if (0 == t_msg_head->dvrip.dvrip_extlen)
							{
								int usrname_len = strlen((char *)t_msg_head->dvrip.dvrip_p);
								if (usrname_len > 8)
								{
									usrname_len = 8;
								}
								int passwd_len = strlen((char *)&t_msg_head->dvrip.dvrip_p[8]);
								if (passwd_len > 8)
								{
									passwd_len = 8;
								}

								if ((0 == strncmp((char *)t_msg_head->dvrip.dvrip_p, st_user_info.csUserName, strlen(st_user_info.csUserName)))
									&& (usrname_len + passwd_len == strlen(st_user_info.csUserName) + strlen(st_user_info.csPassword))
									&& (0 == strncmp((char *)&t_msg_head->dvrip.dvrip_p[8], st_user_info.csPassword, strlen(st_user_info.csPassword))))
								{
									t_msg_head_send->c[8] = 0;
									break;
								}
							}
							else
							{
								//��2�Ǽ�ȥ"&&"����ĩβû�н�����
								if ((0 == strncmp(extra, st_user_info.csUserName, strlen(st_user_info.csUserName)))
									&& (t_msg_head->dvrip.dvrip_extlen - 2 == strlen(st_user_info.csUserName) + strlen(st_user_info.csPassword))
									&& (0 == strncmp(extra + strlen(st_user_info.csUserName) + 2, st_user_info.csPassword, strlen(st_user_info.csPassword))))
								{
									t_msg_head->c[8] = 0;
									break;
								}
							}
						}

						/* ��¼ʧ�ܷ�����  0:���벻��ȷ 1:�ʺŲ����� 3:�ʺ��Ѿ���¼ 4:�ʺű�����
						5:�ʺű���������� 6:��Դ���㣬ϵͳæ 7:�汾���ԣ��޷���½ */
						t_msg_head_send->c[9] = 0; //��¼ʧ�ܷ�����

						t_msg_head_send->c[10] = 1;  //ͨ����    
						t_msg_head_send->c[11] = 9;   //��Ƶ���뷽ʽ 8:MPEG4 9:H.264
						t_msg_head_send->c[12] = 51;  //�豸����  51:IPC���Ʒ
						t_msg_head_send->l[4] = 45;    //�豸���ص�Ψһ��ʶ�ţ���־������
						t_msg_head_send->c[28] = 0;  //��Ƶ��ʽ��0: ��ʾPAL��     1: ��ʾNTSC��
						t_msg_head_send->s[15] = 0x8101; //��30��31�ֽڱ�������ֵ �������ز�Ʒ��0x8101, 0x8001, 0x8002, 0x8003

						n_offset = DVRIP_HEAD_T_SIZE;
						memcpy(send_msg + n_offset, mac, 17);
						n_offset += 17;

						n_max_resolution = 0;
						QMAPI_NET_SUPPORT_STREAM_FMT stSupportFmt;
						QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT, 0, &stSupportFmt, sizeof(stSupportFmt));
						for (i = 0; i < 9; i++)
						{
							if (stSupportFmt.stVideoSize[0][i].nWidth * stSupportFmt.stVideoSize[0][i].nHeight > n_max_resolution)
							{
								nWidth = stSupportFmt.stVideoSize[0][i].nWidth;
								nHeight = stSupportFmt.stVideoSize[0][i].nHeight;
								n_max_resolution = nWidth * nHeight;
							}

						}

						memset(a_extra_sting, 0, sizeof(a_extra_sting));
						sprintf(a_extra_sting, "IPC%5d*%-5d", nWidth, nHeight);
						n_extra_len = strlen(a_extra_sting);
						strncpy(send_msg + n_offset, a_extra_sting, n_extra_len);
						n_offset += n_extra_len;
						t_msg_head_send->c[2] = 17 + n_extra_len;   //mac��ַ���ȼ����豸����   

						struct sockaddr_in udpaddrto;
						bzero(&udpaddrto, sizeof(struct sockaddr_in));
						udpaddrto.sin_family = AF_INET;
						udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
						udpaddrto.sin_port = htons(ZHINUO_SEND_PORT);

						t_msg_head_send->dvrip.cmd = ACK_LOG_ON;

						//�ӹ㲥��ַ������Ϣ  
						ret = sendto(sockedfd, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
						if (ret <= 0)
						{
							X6_TRACE("send error....:%d\n", ret);
						}
					}
				}
				if (0xc1 == t_msg_head->dvrip.cmd)
				{
					if (0 == strncmp(mac, extra + 164, 17))
					{
						ZhiNuo_Dev_Search * str_dev_search = (ZhiNuo_Dev_Search *)extra;
// 						X6_TRACE("%d,HostIP:%s \n", sizeof(ZhiNuo_Dev_Search), (char *)inet_ntoa((unsigned int)str_dev_search->HostIP));
// 						X6_TRACE("Submask:%s\n", (char *)inet_ntoa(str_dev_search->Submask));
// 						X6_TRACE("GateWayIP:%s\n", (char *)inet_ntoa(str_dev_search->GateWayIP));
// 						X6_TRACE("DNSIP:%s\n", (char *)inet_ntoa(str_dev_search->DNSIP));

						//��ȡ�������������
						QMAPI_NET_NETWORK_CFG st_ipc_net_info;
						if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
						{
							X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
							goto ZhiNuo_Search_End;
						}

						//��ȡ�������������
						QMAPI_NET_WIFI_CONFIG st_wifi_net_info;
						if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
						{
							X6_TRACE("QMAPI_SYSCFG_GET_WIFICFG fail\n");
							goto ZhiNuo_Search_End;
						}

						if (st_wifi_net_info.bWifiEnable && st_wifi_net_info.byStatus == 0 && 1 != st_wifi_net_info.byWifiMode)
						{
							struct in_addr objAddr;

							memset(st_wifi_net_info.dwNetIpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->HostIP;
							strcpy(st_wifi_net_info.dwNetIpAddr.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_wifi_net_info.dwNetMask.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->Submask;
							strcpy(st_wifi_net_info.dwNetMask.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_wifi_net_info.dwGateway.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->GateWayIP;
							strcpy(st_wifi_net_info.dwGateway.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_wifi_net_info.dwDNSServer.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->DNSIP;
							strcpy(st_wifi_net_info.dwDNSServer.csIpV4, (char*)inet_ntoa(objAddr));
							st_wifi_net_info.byEnableDHCP = 0;

							//�����������������
							if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
							{
								X6_TRACE("QMAPI_SYSCFG_SET_WIFICFG fail\n");
								goto ZhiNuo_Search_End;
							}
						}
						else
						{
							struct in_addr objAddr;

							memset(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->HostIP;
							strcpy(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->Submask;
							strcpy(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_ipc_net_info.stGatewayIpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->GateWayIP;
							strcpy(st_ipc_net_info.stGatewayIpAddr.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->DNSIP;
							strcpy(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, (char*)inet_ntoa(objAddr));
							st_ipc_net_info.byEnableDHCP = 0;

							//���ñ������������
							if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
							{
								X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
								goto ZhiNuo_Search_End;
							}
						}

						char ch_param_type = 0;
						char ch_child_type = 0;
						char ch_config_edition = 0;
						//char ch_param_effect_flag = 0;
						char ch_child_type_limit = 0;
						char tem_buf[DVRIP_HEAD_T_SIZE] = { 0 };
						memcpy(tem_buf, smsg, DVRIP_HEAD_T_SIZE);
						DVRIP_HEAD_T *t_msg_head = (DVRIP_HEAD_T *)tem_buf;

						X6_TRACE("hl:%d, v:%d, vextralen:%d\n", t_msg_head->dvrip.dvrip_hl,
								 t_msg_head->dvrip.dvrip_v, t_msg_head->dvrip.dvrip_extlen);

						ch_param_type = t_msg_head->c[16];
						ch_child_type = t_msg_head->c[17];
						ch_config_edition = t_msg_head->c[18];
						//ch_param_effect_flag = t_msg_head->c[20];
						ch_child_type_limit = t_msg_head->c[24];

						//
						X6_TRACE("ch_param_type:%d, ch_child_type:%d, ch_config_edition:%d, ch_param_effect_flag:%d, ch_child_type_limit:%d\n",
								 t_msg_head->c[16], t_msg_head->c[17], t_msg_head->c[18], t_msg_head->c[20], t_msg_head->c[24]);

						//rcv_msg_len = DVRIP_HEAD_T_SIZE + t_msg_head->dvrip.dvrip_extlen;


						char send_msg[BUFLEN] = { 0 };
						t_msg_head = (DVRIP_HEAD_T *)send_msg;
						ZERO_DVRIP_HEAD_T(t_msg_head)
							t_msg_head->dvrip.cmd = ACK_SET_CONFIG;
						t_msg_head->c[2] = 17 + strlen(DEV_NAME);   //mac��ַ���ȼ����豸����
						t_msg_head->c[8] = 0; //������0:�ɹ�1:ʧ��2:���ݲ��Ϸ�3:��ʱ�޷�����4:û��Ȩ��
						t_msg_head->c[9] = 1; //0������Ҫ���� 1����Ҫ����������Ч
						t_msg_head->c[16] = ch_param_type;
						t_msg_head->c[17] = ch_child_type;
						t_msg_head->c[18] = ch_config_edition;
						t_msg_head->c[24] = ch_child_type_limit;

						n_offset = DVRIP_HEAD_T_SIZE;
						memcpy(send_msg + n_offset, mac, 17);
						n_offset += 17;
						n_max_resolution = 0;
						QMAPI_NET_SUPPORT_STREAM_FMT stSupportFmt;
						QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT, 0, &stSupportFmt, sizeof(stSupportFmt));
						for (i = 0; i < 9; i++)
						{
							if (stSupportFmt.stVideoSize[0][i].nWidth * stSupportFmt.stVideoSize[0][i].nHeight > n_max_resolution)
							{
								nWidth = stSupportFmt.stVideoSize[0][i].nWidth;
								nHeight = stSupportFmt.stVideoSize[0][i].nHeight;
								n_max_resolution = nWidth * nHeight;
							}

						}

						memset(a_extra_sting, 0, sizeof(a_extra_sting));
						sprintf(a_extra_sting, "IPC%5d*%-5d", nWidth, nHeight);
						n_extra_len = strlen(a_extra_sting);
						strncpy(send_msg + n_offset, a_extra_sting, n_extra_len);
						n_offset += n_extra_len;
						t_msg_head->c[2] = 17 + n_extra_len;   //mac��ַ���ȼ����豸����   

						struct sockaddr_in udpaddrto;
						bzero(&udpaddrto, sizeof(struct sockaddr_in));
						udpaddrto.sin_family = AF_INET;
						udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
						udpaddrto.sin_port = htons(ZHINUO_SEND_PORT);

						t_msg_head->dvrip.cmd = ACK_SET_CONFIG;

						//�ӹ㲥��ַ������Ϣ  
						ret = sendto(sockedfd, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
						if (ret <= 0)
						{
							X6_TRACE("send error....:%d\n", ret);
						}
						sleep(3); //��֤���ݷ���������
						ret = QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_SAVECFG_ASYN, 0, 0, 0);
						if (0 != ret)
						{
							X6_TRACE("DMS_NET_GET_PICCFG error\n");
						}
					}
				}
			}
		}
	}

ZhiNuo_Search_End:
	if (g_zhinuo_sock >= 0){
		close(g_zhinuo_sock);
		g_zhinuo_sock = -1;
	}

	if (sockedfd >= 0){
		close(sockedfd);
		sockedfd = -1;
	}	

	X6_TRACE("ZhiNuo_Broadcast_Thread end !\n");
	return NULL;
}


void* Dahua_Broadcast_Thread(void *param)
{
	prctl(PR_SET_NAME, (unsigned long)"Dahua_Broadcast_Thread", 0, 0, 0);
	X6_TRACE("Dahua_Broadcast_Thread pid:%d\n", getpid());

	int i = 0;
	int nWidth = 0;
	int nHeight = 0;
	int n_max_resolution = 0;
	int n_extra_len = 0;
	char a_extra_sting[255];
	int n_offset = 0;
	char mac[17];

	int sockedfdX = -1;

	// �󶨵�ַ  
	struct sockaddr_in addrto;
	bzero(&addrto, sizeof(struct sockaddr_in));
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = htonl(INADDR_ANY);
	addrto.sin_port = htons(DAHUA_RCV_PORT);

	// �㲥��ַ  
	struct sockaddr_in from;
	bzero(&from, sizeof(struct sockaddr_in));

	if ((g_dahua_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		X6_TRACE("socket error\n");
		return NULL;
	}

	const int opt = 1;

	//���ø��׽���Ϊ�㲥���ͣ�  
	int nb = 0;
	nb = setsockopt(g_dahua_sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set socket error...\n");
		goto DaHua_Search_End;
	}

	struct ifreq ifr;
	struct sockaddr_in broadcast_addr;      /*���ص�ַ*/
		
	sockedfdX = socket(AF_INET, SOCK_DGRAM, 0);/*�������ݱ��׽���*/
	if (sockedfdX < 0)
	{
		X6_TRACE("socket error\n");
		goto DaHua_Search_End;
	}

	strcpy(ifr.ifr_name, IFNAME);
	if (ioctl(g_dahua_sock, SIOCGIFBRDADDR, &ifr) == -1)
	{
		; // perror("ioctl error"), exit(1);
	}
	memcpy(&broadcast_addr, &ifr.ifr_broadaddr, sizeof(struct sockaddr_in));
	broadcast_addr.sin_port = htons(DAHUA_SEND_PORT);/*���ù㲥�˿�*/

	nb = setsockopt(sockedfdX, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set sockedfdX error...\n");
		goto DaHua_Search_End;
	}

	if (bind(g_dahua_sock, (struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1)
	{
		X6_TRACE("bind error...\n");
		goto DaHua_Search_End;
	}

	int len = sizeof(struct sockaddr_in);
	char smsg[1024] = { 0 };

	int ret = 0;
	struct timeval timeout;
	fd_set readfd; //���ļ�����������

	while (1)
	{
		timeout.tv_sec = 10;  //��ʱʱ��Ϊ2��
		timeout.tv_usec = 0;
		//�ļ���������0
		FD_ZERO(&readfd);

		//���׽����ļ����������뵽�ļ�������������
		FD_SET(g_dahua_sock, &readfd);

		//select�����Ƿ������ݵ���
		ret = select(g_dahua_sock + 1, &readfd, NULL, NULL, &timeout);
		if (0 == g_run_flag)
		{
			break;
		}

		if (FD_ISSET(g_dahua_sock, &readfd))
		{
			//�ӹ㲥��ַ������Ϣ  
			ret = recvfrom(g_dahua_sock, smsg, 1024, 0, (struct sockaddr*)&from, (socklen_t*)&len);
			if (ret <= 0)
			{
				X6_TRACE("read error....%d:%s\n", ret, strerror(errno));
			}
			else
			{
				//int rcv_msg_len = 0;
				char tem_buf[DVRIP_HEAD_T_SIZE] = { 0 };
				memcpy(tem_buf, smsg, DVRIP_HEAD_T_SIZE);
				DVRIP_HEAD_T *t_msg_head = (DVRIP_HEAD_T *)tem_buf;
				char * extra = smsg + DVRIP_HEAD_T_SIZE;
				//X6_TRACE("type:%d, cmd:%x,len:%d,%s,extra:%d,fromip:%s,fromeport:%d\n", t_msg_head->c[16], t_msg_head->dvrip.cmd, ret, smsg, t_msg_head->dvrip.dvrip_extlen, inet_ntoa(from.sin_addr), from.sin_port);                  
				if (CMD_DEV_SEARCH == t_msg_head->dvrip.cmd)
				{
					n_offset = 0;
					char extra_data[88] = { 0 };
					ZhiNuo_Dev_Search * str_dev_search = (ZhiNuo_Dev_Search *)extra_data;

					//��ȡ�������������
					QMAPI_NET_NETWORK_CFG st_ipc_net_info;
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
					{
						X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
						goto DaHua_Search_End;
					}

					str_dev_search->Version[0] = 0X32;  //�汾��Ϣ 
					str_dev_search->Version[1] = 0X33;
					str_dev_search->Version[2] = 0X30;
					str_dev_search->Version[3] = 0X32;

					str_dev_search->HostName[0] = 0x44; //������
					str_dev_search->HostName[1] = 0x56;
					str_dev_search->HostName[2] = 0x52;

					//��ȡ�������������
					QMAPI_NET_WIFI_CONFIG st_wifi_net_info;
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
					{
						X6_TRACE("QMAPI_SYSCFG_GET_WIFICFG fail\n");
						return NULL;
					}

					struct sockaddr_in adr_inet;

					//������߿��þ�ֻ�����ߵ�����
					if (st_wifi_net_info.bWifiEnable && st_wifi_net_info.byStatus == 0 && 1 != st_wifi_net_info.byWifiMode)
					{
						inet_aton(st_wifi_net_info.dwNetIpAddr.csIpV4, &adr_inet.sin_addr);
						str_dev_search->HostIP = (unsigned long)adr_inet.sin_addr.s_addr;
//						X6_TRACE("ip:%s\n", (char *)inet_ntoa(str_dev_search->HostIP));
						inet_aton(st_wifi_net_info.dwNetMask.csIpV4, &adr_inet.sin_addr);
						str_dev_search->Submask = (unsigned long)adr_inet.sin_addr.s_addr;
						inet_aton(st_wifi_net_info.dwGateway.csIpV4, &adr_inet.sin_addr);
						str_dev_search->GateWayIP = (unsigned long)adr_inet.sin_addr.s_addr;
						inet_aton(st_wifi_net_info.dwDNSServer.csIpV4, &adr_inet.sin_addr);
						str_dev_search->DNSIP = (unsigned long)adr_inet.sin_addr.s_addr;

					}
					else
					{
						inet_aton(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, &adr_inet.sin_addr);
						str_dev_search->HostIP = (unsigned long)adr_inet.sin_addr.s_addr;
//						X6_TRACE("ip:%s\n", (char *)inet_ntoa(str_dev_search->HostIP));
						inet_aton(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, &adr_inet.sin_addr);
						str_dev_search->Submask = (unsigned long)adr_inet.sin_addr.s_addr;
						inet_aton(st_ipc_net_info.stGatewayIpAddr.csIpV4, &adr_inet.sin_addr);
						str_dev_search->GateWayIP = (unsigned long)adr_inet.sin_addr.s_addr;
						inet_aton(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, &adr_inet.sin_addr);
						str_dev_search->DNSIP = (unsigned long)adr_inet.sin_addr.s_addr;
					}

					inet_aton("10.1.0.2", &adr_inet.sin_addr);
					str_dev_search->AlarmServerIP = (unsigned long)adr_inet.sin_addr.s_addr;
					str_dev_search->HttpPort = st_ipc_net_info.wHttpPort;
					str_dev_search->TCPPort = TCP_LISTEN_PORT;
					str_dev_search->TCPMaxConn = MAX_LINK_NUM;
					str_dev_search->SSLPort = 8443;
					str_dev_search->UDPPort = 8001;
					inet_aton("239.255.42.42", &adr_inet.sin_addr);
					str_dev_search->McastIP = (unsigned long)adr_inet.sin_addr.s_addr;
					str_dev_search->McastPort = 36666;

					//rcv_msg_len = DVRIP_HEAD_T_SIZE + t_msg_head->dvrip.dvrip_extlen;
					char send_msg[512] = { 0 };
					t_msg_head = (DVRIP_HEAD_T *)send_msg;
					memset(send_msg, 0, sizeof(send_msg));
					t_msg_head->c[2] = 17 + strlen(DEV_NAME);   //mac��ַ���ȼ����豸����
					t_msg_head->dvrip.dvrip_extlen = 0x58;  //Ϊextra_data����ĳ���           
					t_msg_head->dvrip.cmd = ACK_DEV_SEARCH;
					t_msg_head->c[16] = 2; //�̶�Ϊ2
					t_msg_head->c[19] = 0; //������ 0:���� 1:��Ȩ�� 2:�޶�Ӧ�����ṩ
					t_msg_head->c[20] = 0xa3; //����ץ�����������ֵ�������

					struct sockaddr_in udpaddrto;
					bzero(&udpaddrto, sizeof(struct sockaddr_in));
					udpaddrto.sin_family = AF_INET;
					udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
					udpaddrto.sin_port = htons(DAHUA_SEND_PORT);
					n_offset += DVRIP_HEAD_T_SIZE;

					memcpy(send_msg + n_offset, &extra_data, sizeof(extra_data));
					n_offset += sizeof(extra_data);
					sprintf(send_msg + n_offset, "%02x:%02x:%02x:%02x:%02x:%02x", st_ipc_net_info.stEtherNet[0].byMACAddr[0],
							st_ipc_net_info.stEtherNet[0].byMACAddr[1],
							st_ipc_net_info.stEtherNet[0].byMACAddr[2],
							st_ipc_net_info.stEtherNet[0].byMACAddr[3],
							st_ipc_net_info.stEtherNet[0].byMACAddr[4],
							st_ipc_net_info.stEtherNet[0].byMACAddr[5]);
					memcpy(mac, send_msg + n_offset, 17);
					//memcpy(temp, &st_net_info.szMac, 17);
					n_offset += 17;
					memcpy(send_msg + n_offset, DEV_NAME, strlen(DEV_NAME));
					n_offset += strlen(DEV_NAME);

					n_max_resolution = 0;
					QMAPI_NET_SUPPORT_STREAM_FMT stSupportFmt;
					QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT, 0, &stSupportFmt, sizeof(stSupportFmt));
					for (i = 0; i < 9; i++)
					{
						if (stSupportFmt.stVideoSize[0][i].nWidth * stSupportFmt.stVideoSize[0][i].nHeight > n_max_resolution)
						{
							nWidth = stSupportFmt.stVideoSize[0][i].nWidth;
							nHeight = stSupportFmt.stVideoSize[0][i].nHeight;
							n_max_resolution = nWidth * nHeight;
						}

					}

					n_extra_len = strlen("Name:PZC3EW11102007\r\nDevice:IPC-IPVM3150F\r\nIPv6Addr:2001:250:3000:1::1:2/112;gateway:2001:250:3000:1::1:1\r\nIPv6Addr:fe80::9202:a9ff:fe1b:f6b3/64;gateway:fe80::\r\n\r\n");
					sprintf(a_extra_sting, "Name:IPC%5d*%-5d\r\nDevice:IPC-IPVM3150F\r\nIPv6Addr:2001:250:3000:1::1:2/112;gateway:2001:250:3000:1::1:1\r\nIPv6Addr:fe80::9202:a9ff:fe1b:f6b3/64;gateway:fe80::\r\n\r\n", nWidth, nHeight);
					strncpy(send_msg + n_offset, a_extra_sting, n_extra_len);
					//strcpy(send_msg + n_offset, "Name:IPC%d*%d\r\nDevice:IPC-IPVM3150F\r\nIPv6Addr:2001:250:3000:1::1:2/112;gateway:2001:250:3000:1::1:1\r\nIPv6Addr:fe80::9202:a9ff:fe1b:f6b3/64;gateway:fe80::\r\n\r\n");
					n_offset += n_extra_len;

					//�ӹ㲥��ַ������Ϣ  
					usleep(500000); //˯��500���룬����nvr��������̫�࣬�������������֤nvrÿ�ζ����ѵ��豸
					ret = sendto(sockedfdX, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
					if (ret <= 0)
					{
						X6_TRACE("send error....:%d\n", ret);
					}
				}

				//���޸�ip���õ�½�����´���û��ִ�е���������Ժ���˹��ܿ����õ�
				if (CMD_DAHUA_LOG_ON == t_msg_head->dvrip.cmd)
				{
					X6_TRACE("name:%s, pass:%s, cmd:%x, extralen:%d, extra:%s, clienttype:%d, locktype:%d, hl:%d, v:%d\n",
							 t_msg_head->dvrip.dvrip_p, &t_msg_head->dvrip.dvrip_p[8], t_msg_head->dvrip.cmd
							 , t_msg_head->dvrip.dvrip_extlen, extra, t_msg_head->dvrip.dvrip_p[18],
							 t_msg_head->dvrip.dvrip_p[19], t_msg_head->dvrip.dvrip_hl, t_msg_head->dvrip.dvrip_v);

					if (0 == strncmp(mac, extra, 17))
					{
						char send_msg[BUFLEN] = { 0 };
						t_msg_head = (DVRIP_HEAD_T *)send_msg;
						ZERO_DVRIP_HEAD_T(t_msg_head)

						t_msg_head->c[1] = 0; //0��û�� 1�����ж໭��Ԥ������ 
						t_msg_head->c[2] = 17 + strlen(DEV_NAME); //uuid

						/*//��ȡ�û�������
						QMAPI_NET_USER_INFO st_user_info;
						if(0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_user_info, sizeof(QMAPI_NET_USER_INFO)))
						{
						X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
						return NULL;
						}

						printf("name:%s, pass:%s\n", st_user_info.csUserName, st_user_info.csPassword);
						if((0 == strcmp(t_msg_head->dvrip.dvrip_p, st_user_info.csUserName))
						&& (0 == strcmp(&t_msg_head->dvrip.dvrip_p[8], st_user_info.csPassword)))
						{
						t_msg_head->c[8] = 0;
						}
						else
						{
						t_msg_head->c[8] = 1; //0: ��ʾ��¼�ɹ� 1: ��ʾ��¼ʧ�� 3: �û��ѵ�¼
						}*/


						t_msg_head->c[8] = 0;

						/* ��¼ʧ�ܷ�����  0:���벻��ȷ 1:�ʺŲ����� 3:�ʺ��Ѿ���¼ 4:�ʺű�����
						5:�ʺű���������� 6:��Դ���㣬ϵͳæ 7:�汾���ԣ��޷���½ */
						t_msg_head->c[9] = 2; //��¼ʧ�ܷ�����
						t_msg_head->c[10] = 1;  //ͨ����    
						t_msg_head->c[11] = 9;   //��Ƶ���뷽ʽ 8:MPEG4 9:H.264
						t_msg_head->c[12] = 51;  //�豸����  51:IPC���Ʒ
						t_msg_head->l[4] = 45;    //�豸���ص�Ψһ��ʶ�ţ���־������
						t_msg_head->c[28] = 0;  //��Ƶ��ʽ��0: ��ʾPAL��     1: ��ʾNTSC��
						t_msg_head->s[15] = 0x8101; //��30��31�ֽڱ�������ֵ �������ز�Ʒ��0x8101, 0x8001, 0x8002, 0x8003

						n_offset = DVRIP_HEAD_T_SIZE;
						memcpy(send_msg + n_offset, mac, 17);
						n_offset += 17;
						memcpy(send_msg + n_offset, DEV_NAME, strlen(DEV_NAME));
						n_offset += strlen(DEV_NAME);

						struct sockaddr_in udpaddrto;
						bzero(&udpaddrto, sizeof(struct sockaddr_in));
						udpaddrto.sin_family = AF_INET;
						udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
						udpaddrto.sin_port = htons(DAHUA_SEND_PORT);

						t_msg_head->dvrip.cmd = ACK_LOG_ON;

						//�ӹ㲥��ַ������Ϣ  
						ret = sendto(sockedfdX, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
						if (ret <= 0)
						{
							X6_TRACE("send error....:%d\n", ret);
						}
					}
				}

				if (0xc1 == t_msg_head->dvrip.cmd)
				{
					if (0 == strncmp(mac, extra + 0x58, 17)) //Ϊextra_data����ĳ��� 
					{
						ZhiNuo_Dev_Search * str_dev_search = (ZhiNuo_Dev_Search *)extra;
// 						X6_TRACE("%d,HostIP:%s \n", sizeof(ZhiNuo_Dev_Search), (char *)inet_ntoa(str_dev_search->HostIP));
// 						X6_TRACE("Submask:%s\n", (char *)inet_ntoa(str_dev_search->Submask));
// 						X6_TRACE("GateWayIP:%s\n", (char *)inet_ntoa(str_dev_search->GateWayIP));
// 						X6_TRACE("DNSIP:%s\n", (char *)inet_ntoa(str_dev_search->DNSIP));

						//��ȡ�������������
						QMAPI_NET_NETWORK_CFG st_ipc_net_info;
						if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
						{
							X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
							goto DaHua_Search_End;
						}

						//��ȡ�������������
						QMAPI_NET_WIFI_CONFIG st_wifi_net_info;
						if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
						{
							X6_TRACE("QMAPI_SYSCFG_GET_WIFICFG fail\n");
							goto DaHua_Search_End;
						}

						if (st_wifi_net_info.bWifiEnable  && st_wifi_net_info.byStatus == 0 && 1 != st_wifi_net_info.byWifiMode)
						{
							struct in_addr objAddr;
							
							memset(st_wifi_net_info.dwNetIpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->HostIP;
							strcpy(st_wifi_net_info.dwNetIpAddr.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_wifi_net_info.dwNetMask.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->Submask;
							strcpy(st_wifi_net_info.dwNetMask.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_wifi_net_info.dwGateway.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->GateWayIP;
							strcpy(st_wifi_net_info.dwGateway.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_wifi_net_info.dwDNSServer.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->DNSIP;
							strcpy(st_wifi_net_info.dwDNSServer.csIpV4, (char*)inet_ntoa(objAddr));
							st_wifi_net_info.byEnableDHCP = 0;

							//�����������������
							if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
							{
								X6_TRACE("QMAPI_SYSCFG_SET_WIFICFG fail\n");
								goto DaHua_Search_End;
							}
						}
						else
						{
							struct in_addr objAddr;

							memset(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->HostIP;
							strcpy(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->Submask;
							strcpy(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_ipc_net_info.stGatewayIpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->GateWayIP;
							strcpy(st_ipc_net_info.stGatewayIpAddr.csIpV4, (char*)inet_ntoa(objAddr));
							memset(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
							objAddr.s_addr = str_dev_search->DNSIP;
							strcpy(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, (char*)inet_ntoa(objAddr));
							st_ipc_net_info.byEnableDHCP = 0;

							//���ñ������������
							if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
							{
								X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
								goto DaHua_Search_End;
							}
						}

						char ch_param_type = 0;
						char ch_child_type = 0;
						char ch_config_edition = 0;
						//char ch_param_effect_flag = 0;
						char ch_child_type_limit = 0;
						char tem_buf[DVRIP_HEAD_T_SIZE] = { 0 };
						memcpy(tem_buf, smsg, DVRIP_HEAD_T_SIZE);
						DVRIP_HEAD_T *t_msg_head = (DVRIP_HEAD_T *)tem_buf;

						X6_TRACE("hl:%d, v:%d, vextralen:%d\n", t_msg_head->dvrip.dvrip_hl,
								 t_msg_head->dvrip.dvrip_v, t_msg_head->dvrip.dvrip_extlen);

						ch_param_type = t_msg_head->c[16];
						ch_child_type = t_msg_head->c[17];
						ch_config_edition = t_msg_head->c[18];
						//ch_param_effect_flag = t_msg_head->c[20];
						ch_child_type_limit = t_msg_head->c[24];

						//
						X6_TRACE("ch_param_type:%d, ch_child_type:%d, ch_config_edition:%d, ch_param_effect_flag:%d, ch_child_type_limit:%d\n",
								 t_msg_head->c[16], t_msg_head->c[17], t_msg_head->c[18], t_msg_head->c[20], t_msg_head->c[24]);

						//rcv_msg_len = DVRIP_HEAD_T_SIZE + t_msg_head->dvrip.dvrip_extlen;


						char send_msg[BUFLEN] = { 0 };
						t_msg_head = (DVRIP_HEAD_T *)send_msg;
						ZERO_DVRIP_HEAD_T(t_msg_head)
							t_msg_head->dvrip.cmd = ACK_SET_CONFIG;
						t_msg_head->c[2] = 17 + strlen(DEV_NAME);   //mac��ַ���ȼ����豸����
						t_msg_head->c[8] = 0; //������0:�ɹ�1:ʧ��2:���ݲ��Ϸ�3:��ʱ�޷�����4:û��Ȩ��
						t_msg_head->c[9] = 1; //0������Ҫ���� 1����Ҫ����������Ч
						t_msg_head->c[16] = ch_param_type;
						t_msg_head->c[17] = ch_child_type;
						t_msg_head->c[18] = ch_config_edition;
						t_msg_head->c[24] = ch_child_type_limit;

						n_offset = DVRIP_HEAD_T_SIZE;
						memcpy(send_msg + n_offset, mac, 17);
						n_offset += 17;
						memcpy(send_msg + n_offset, DEV_NAME, strlen(DEV_NAME));
						n_offset += strlen(DEV_NAME);

						struct sockaddr_in udpaddrto;
						bzero(&udpaddrto, sizeof(struct sockaddr_in));
						udpaddrto.sin_family = AF_INET;
						udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
						udpaddrto.sin_port = htons(DAHUA_SEND_PORT);

						t_msg_head->dvrip.cmd = ACK_SET_CONFIG;

						//�ӹ㲥��ַ������Ϣ  
						ret = sendto(sockedfdX, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
						if (ret <= 0)
						{
							X6_TRACE("send error....:%d\n", ret);
						}
						sleep(3); //��֤���ݷ���������
						ret = QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_SAVECFG_ASYN, 0, 0, 0);
						if (0 != ret)
						{
							X6_TRACE("DMS_NET_GET_PICCFG error\n");
						}
						goto DaHua_Search_End;
					}
				}
			}
		}
	}

DaHua_Search_End:
	if (g_dahua_sock >= 0){
		close(g_dahua_sock);
		g_dahua_sock = -1;
	}
	
	if (sockedfdX >= 0){
		close(sockedfdX);
		sockedfdX = -1;
	}	

	X6_TRACE("DaHua_Broadcast_Thread end !\n");
	return NULL;
}

static void zhiNuo_search_stop_v2(int factory, int port)
{
	/*�������ݱ��׽���*/
	int sock_send = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_send < 0)
	{		
		X6_TRACE(" socket(AF_INET, SOCK_DGRAM, 0) fail\n");
		return ;
	}

	//�ر���ŵ�ʹ󻪵��豸�����߳�
	int nb = 0;
	const int opt = 1;
	char send_msg[] = "shutdown";
	int n_offset = strlen(send_msg);
	nb = setsockopt(sock_send, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set sock_send error...\n");
	}

	struct sockaddr_in udpaddrto;
	bzero(&udpaddrto, sizeof(struct sockaddr_in));

	udpaddrto.sin_family = AF_INET;
	udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
	udpaddrto.sin_port = htons(/*DAHUA_SEND_PORT*/ port);

	//�ӹ㲥��ַ������Ϣ  
	int ret = sendto(sock_send, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
	if (ret <= 0)
	{
		X6_TRACE("send error....:%d\n", ret);
	}

// 	//�ӹ㲥��ַ������Ϣ
// 	udpaddrto.sin_port = htons(ZHINUO_SEND_PORT);	  
// 	ret = sendto(sock_send, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
// 	if (ret <= 0)
// 	{
// 		X6_TRACE("send error....:%d\n", ret);
// 	}

	close(sock_send);
}

/////////////////////////////////////////////////////////////////////////
int zhiNuo_search_start()
{
	g_run_flag = 1;

	//�����豸���������̣߳�����㲥��
	pthread_t zhinuo_broadcast_thread_id;
	pthread_attr_t zhinuo_attr_broadcast;	
	pthread_attr_init(&zhinuo_attr_broadcast);
	pthread_attr_setdetachstate(&zhinuo_attr_broadcast, PTHREAD_CREATE_DETACHED);
	if (0 != pthread_create(&zhinuo_broadcast_thread_id, &zhinuo_attr_broadcast, ZhiNuo_Broadcast_Thread, NULL))
	{
		X6_TRACE("erro:creat zhinuo_main_thread fail\n");
		return 0;
	}
	
	return 0;
}

int zhiNuo_search_stop()
{
	g_run_flag = 0;
	zhiNuo_search_stop_v2(0, ZHINUO_SEND_PORT);

	return 0;
}

int daHua_search_start()
{
	g_run_flag = 1;

	//�����豸���������̣߳�����㲥��
	pthread_t dahua_broadcast_thread_id;
	pthread_attr_t dahua_attr_broadcast;	
	pthread_attr_init(&dahua_attr_broadcast);
	pthread_attr_setdetachstate(&dahua_attr_broadcast, PTHREAD_CREATE_DETACHED);
	if (0 != pthread_create(&dahua_broadcast_thread_id, &dahua_attr_broadcast, Dahua_Broadcast_Thread, NULL))
	{
		X6_TRACE("erro:creat zhinuo_main_thread fail\n");
		return 0;
	}

	return 0;
}

int daHua_search_stop()
{
	g_run_flag = 0;
	zhiNuo_search_stop_v2(1, DAHUA_SEND_PORT);

	return 0;
}



//
int zhiNuo_CreateSearchSocket(int *socktype)
{
// 	int i = 0;
// 	int nWidth = 0;
// 	int nHeight = 0;
// 	int n_max_resolution = 0;
// 	int n_extra_len = 0;
// 	char a_extra_sting[255];
// 	int n_offset = 0;
// 	char mac[17];

	// �󶨵�ַ  
	struct sockaddr_in addrto;
	bzero(&addrto, sizeof(struct sockaddr_in));
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = htonl(INADDR_ANY);
	addrto.sin_port = htons(ZHINUO_RCV_PORT);

	// �㲥��ַ  
	struct sockaddr_in from;
	bzero(&from, sizeof(struct sockaddr_in));

	if ((g_zhinuo_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		X6_TRACE("socket error\n");
		return -1;
	}

	//���ø��׽���Ϊ�㲥���ͣ�  
	const int opt = 1;	
	int nb = 0;
	nb = setsockopt(g_zhinuo_sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set socket error...\n");
		goto ZhiNuo_Search_Close;
	}

	struct ifreq ifr;
	struct sockaddr_in broadcast_addr;      /*���ص�ַ*/
	strcpy(ifr.ifr_name, IFNAME);

	if (ioctl(g_zhinuo_sock, SIOCGIFBRDADDR, &ifr) == -1)
	{
		;// perror("ioctl error"), exit(1);			//
	}

	memcpy(&broadcast_addr, &ifr.ifr_broadaddr, sizeof(struct sockaddr_in));
	broadcast_addr.sin_port = htons(ZHINUO_SEND_PORT);/*���ù㲥�˿�*/

	if (bind(g_zhinuo_sock, (struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1)
	{
		X6_TRACE("bind error...\n");
		goto ZhiNuo_Search_Close;
	}

	return g_zhinuo_sock;


ZhiNuo_Search_Close:
	printf("goto ZhiNuo_Search_End: \n");
	close(g_zhinuo_sock);

	return -1;
}

int zhiNuo_ProcessRequest(int handle, int sockfd, int socktype)
{
	g_nw_search_run_index = 600;
	// 1. /*�������ݱ��׽���*/
	int sockedfd = -1;
	sockedfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockedfd < 0)
	{
		X6_TRACE("socket error\n");
		return 0;
	}

	const int opt = 1;
	int nb = setsockopt(sockedfd, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set sockedfd error...\n");
		close(sockedfd);
		return 0;
	}
	g_nw_search_run_index = 601;

	// 2. //�ӹ㲥��ַ������Ϣ  
	int g_zhinuo_sock = sockfd;
	int g_zhinuo_handle = handle;

	int i;
	int nWidth = 0;
	int nHeight = 0;
	int n_offset = 0;
	int n_max_resolution = 0;
	int n_extra_len = 0;
	char a_extra_sting[255];
	char mac[17];

	int len = sizeof(struct sockaddr_in);
	char smsg[1024] = { 0 };

	// �㲥��ַ  
	struct sockaddr_in from;
	bzero(&from, sizeof(struct sockaddr_in));
	g_nw_search_run_index = 602;

	//�ӹ㲥��ַ������Ϣ  
	int ret = recvfrom(g_zhinuo_sock, smsg, 1024, 0, (struct sockaddr*)&from, (socklen_t*)&len);
	if (ret <= 0)
	{
		X6_TRACE("read error....\n");
	}
	else
	{
		//int rcv_msg_len = 0;
		char tem_buf[DVRIP_HEAD_T_SIZE] = { 0 };
		memcpy(tem_buf, smsg, DVRIP_HEAD_T_SIZE);
		DVRIP_HEAD_T *t_msg_head = (DVRIP_HEAD_T *)tem_buf;
		char * extra = smsg + DVRIP_HEAD_T_SIZE;

		g_nw_search_run_index = 603;
		//X6_TRACE("type:%d, cmd:%x,len:%d,%s,extra:%d,fromip:%s,fromeport:%d\n", t_msg_head->c[16], t_msg_head->dvrip.cmd, ret, smsg, t_msg_head->dvrip.dvrip_extlen, inet_ntoa(from.sin_addr), from.sin_port);                  
		if (CMD_DEV_SEARCH == t_msg_head->dvrip.cmd)
		{
			g_nw_search_run_index = 6031;
			n_offset = 0;
			char extra_data[164] = { 0 };
			ZhiNuo_Dev_Search * str_dev_search = (ZhiNuo_Dev_Search *)extra_data;

			//��ȡ�������������
			QMAPI_NET_NETWORK_CFG st_ipc_net_info;
			if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
			{
				X6_TRACE("QMAPI_SYSCFG_GET_NETCFG fail\n");
				goto ZhiNuo_Search_End_v2;
			}
			g_nw_search_run_index = 6032;

			str_dev_search->Version[0] = 0X32;  //�汾��Ϣ 
			str_dev_search->Version[1] = 0X33;
			str_dev_search->Version[2] = 0X30;
			str_dev_search->Version[3] = 0X32;

			str_dev_search->HostName[0] = 0x44; //������
			str_dev_search->HostName[1] = 0x56;
			str_dev_search->HostName[2] = 0x52;

			//��ȡ�������������
			QMAPI_NET_WIFI_CONFIG st_wifi_net_info;
			if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
			{
				X6_TRACE("QMAPI_SYSCFG_GET_WIFICFG fail\n");
				goto ZhiNuo_Search_End_v2;
			}

			struct sockaddr_in adr_inet;
			g_nw_search_run_index = 6033;

			//������߿��þ�ֻ�����ߵ�����
			//if(st_wifi_net_info.bWifiEnable && st_wifi_net_info.byStatus == 0)
			if (st_wifi_net_info.bWifiEnable && st_wifi_net_info.byStatus == 0 && 1 != st_wifi_net_info.byWifiMode)
			{
				inet_aton(st_wifi_net_info.dwNetIpAddr.csIpV4, &adr_inet.sin_addr);
				str_dev_search->HostIP = (unsigned long)adr_inet.sin_addr.s_addr;
				//						X6_TRACE("ip:%s\n", (char *)inet_ntoa(str_dev_search->HostIP));
				inet_aton(st_wifi_net_info.dwNetMask.csIpV4, &adr_inet.sin_addr);
				str_dev_search->Submask = (unsigned long)adr_inet.sin_addr.s_addr;
				inet_aton(st_wifi_net_info.dwGateway.csIpV4, &adr_inet.sin_addr);
				str_dev_search->GateWayIP = (unsigned long)adr_inet.sin_addr.s_addr;
				inet_aton(st_wifi_net_info.dwDNSServer.csIpV4, &adr_inet.sin_addr);
				str_dev_search->DNSIP = (unsigned long)adr_inet.sin_addr.s_addr;
			}
			else
			{
				inet_aton(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, &adr_inet.sin_addr);
				str_dev_search->HostIP = (unsigned long)adr_inet.sin_addr.s_addr;
				//						X6_TRACE("ip:%s\n", (char *)inet_ntoa(str_dev_search->HostIP));
				inet_aton(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, &adr_inet.sin_addr);
				str_dev_search->Submask = (unsigned long)adr_inet.sin_addr.s_addr;
				inet_aton(st_ipc_net_info.stGatewayIpAddr.csIpV4, &adr_inet.sin_addr);
				str_dev_search->GateWayIP = (unsigned long)adr_inet.sin_addr.s_addr;
				inet_aton(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, &adr_inet.sin_addr);
				str_dev_search->DNSIP = (unsigned long)adr_inet.sin_addr.s_addr;
			}
			g_nw_search_run_index = 6034;
			inet_aton("10.1.0.2", &adr_inet.sin_addr);
			str_dev_search->AlarmServerIP = (unsigned long)adr_inet.sin_addr.s_addr;
			str_dev_search->HttpPort = st_ipc_net_info.wHttpPort;
			str_dev_search->TCPPort = TCP_LISTEN_PORT;
			str_dev_search->TCPMaxConn = MAX_LINK_NUM;
			str_dev_search->SSLPort = 8443;
			str_dev_search->UDPPort = 8001;
			inet_aton("239.255.42.42", &adr_inet.sin_addr);
			str_dev_search->McastIP = (unsigned long)adr_inet.sin_addr.s_addr;
			str_dev_search->McastPort = 36666;

			//rcv_msg_len = DVRIP_HEAD_T_SIZE + t_msg_head->dvrip.dvrip_extlen;
			char send_msg[512] = { 0 };
			t_msg_head = (DVRIP_HEAD_T *)send_msg;
			memset(send_msg, 0, sizeof(send_msg));

			t_msg_head->dvrip.dvrip_extlen = 0xa4;  //�̶�Ϊ164             
			t_msg_head->dvrip.cmd = ACK_DEV_SEARCH;
			t_msg_head->c[16] = 2; //�̶�Ϊ2
			t_msg_head->c[19] = 0; //������ 0:���� 1:��Ȩ�� 2:�޶�Ӧ�����ṩ

			struct sockaddr_in udpaddrto;
			bzero(&udpaddrto, sizeof(struct sockaddr_in));
			udpaddrto.sin_family = AF_INET;
			udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
			udpaddrto.sin_port = htons(ZHINUO_SEND_PORT);
			n_offset += DVRIP_HEAD_T_SIZE;

			memcpy(send_msg + n_offset, &extra_data, sizeof(extra_data));
			n_offset += sizeof(extra_data);
			sprintf(send_msg + n_offset, "%02x:%02x:%02x:%02x:%02x:%02x", st_ipc_net_info.stEtherNet[0].byMACAddr[0],
					st_ipc_net_info.stEtherNet[0].byMACAddr[1],
					st_ipc_net_info.stEtherNet[0].byMACAddr[2],
					st_ipc_net_info.stEtherNet[0].byMACAddr[3],
					st_ipc_net_info.stEtherNet[0].byMACAddr[4],
					st_ipc_net_info.stEtherNet[0].byMACAddr[5]);
			memcpy(mac, send_msg + n_offset, 17);
			//memcpy(temp, &st_net_info.szMac, 17);
			n_offset += 17;
			g_nw_search_run_index = 6035;

			n_max_resolution = 0;
			QMAPI_NET_SUPPORT_STREAM_FMT stSupportFmt;
			QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT, 0, &stSupportFmt, sizeof(stSupportFmt));
			for (i = 0; i < 9; i++)
			{
				if (stSupportFmt.stVideoSize[0][i].nWidth * stSupportFmt.stVideoSize[0][i].nHeight > n_max_resolution)
				{
					nWidth = stSupportFmt.stVideoSize[0][i].nWidth;
					nHeight = stSupportFmt.stVideoSize[0][i].nHeight;
					n_max_resolution = nWidth * nHeight;
				}
			}

			memset(a_extra_sting, 0, sizeof(a_extra_sting));
			sprintf(a_extra_sting, "IPC%5d*%-5d", nWidth, nHeight);
			n_extra_len = strlen(a_extra_sting);
			strncpy(send_msg + n_offset, a_extra_sting, n_extra_len);
			n_offset += n_extra_len;
			t_msg_head->c[2] = 17 + n_extra_len;   //mac��ַ���ȼ����豸����
			g_nw_search_run_index = 6036;

			//memcpy(send_msg + n_offset, DEV_NAME, strlen(DEV_NAME));
			//n_offset += strlen(DEV_NAME);

			//�ӹ㲥��ַ������Ϣ  
			usleep(500000); //˯��500���룬����nvr��������̫�࣬�������������֤nvrÿ�ζ����ѵ��豸
			g_nw_search_run_index = 6037;
			ret = sendto(sockedfd, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
			if (ret <= 0)
			{
				X6_TRACE("send error....:%d\n", ret);
			}
			g_nw_search_run_index = 6038;
		}
		g_nw_search_run_index = 604;
		if (CMD_ZHINUO_LOG_ON == t_msg_head->dvrip.cmd)
		{
			g_nw_search_run_index = 6041;
			X6_TRACE("name:%s, pass:%s, cmd:%x, extralen:%d, extra:%s, clienttype:%d, locktype:%d, hl:%d, v:%d\n",
					 t_msg_head->dvrip.dvrip_p, &t_msg_head->dvrip.dvrip_p[8], t_msg_head->dvrip.cmd
					 , t_msg_head->dvrip.dvrip_extlen, extra, t_msg_head->dvrip.dvrip_p[18],
					 t_msg_head->dvrip.dvrip_p[19], t_msg_head->dvrip.dvrip_hl, t_msg_head->dvrip.dvrip_v);

			if (0 == strncmp(mac, extra, 17))
			{
				g_nw_search_run_index = 6042;
				char send_msg[BUFLEN] = { 0 };
				DVRIP_HEAD_T *t_msg_head_send = (DVRIP_HEAD_T *)send_msg;
				ZERO_DVRIP_HEAD_T(t_msg_head_send)

				t_msg_head_send->c[1] = 0; //0��û�� 1�����ж໭��Ԥ������                         
				t_msg_head_send->c[8] = 1; //0: ��ʾ��¼�ɹ� 1: ��ʾ��¼ʧ�� 3: �û��ѵ�¼  

				int n_index = 0;
				for (n_index = 0; n_index < 10; n_index++)
				{
					//��ȡ�û�������
					QMAPI_NET_USER_INFO st_user_info;
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_USERCFG, n_index, &st_user_info, sizeof(QMAPI_NET_USER_INFO)))
					{
						X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
						goto ZhiNuo_Search_End_v2;
					}

					if (0 == t_msg_head->dvrip.dvrip_extlen)
					{
						int usrname_len = strlen((char *)t_msg_head->dvrip.dvrip_p);
						if (usrname_len > 8)
						{
							usrname_len = 8;
						}
						int passwd_len = strlen((char *)&t_msg_head->dvrip.dvrip_p[8]);
						if (passwd_len > 8)
						{
							passwd_len = 8;
						}

						if ((0 == strncmp((char *)t_msg_head->dvrip.dvrip_p, st_user_info.csUserName, strlen(st_user_info.csUserName)))
							&& (usrname_len + passwd_len == strlen(st_user_info.csUserName) + strlen(st_user_info.csPassword))
							&& (0 == strncmp((char *)&t_msg_head->dvrip.dvrip_p[8], st_user_info.csPassword, strlen(st_user_info.csPassword))))
						{
							t_msg_head_send->c[8] = 0;
							break;
						}
					}
					else
					{
						//��2�Ǽ�ȥ"&&"����ĩβû�н�����
						if ((0 == strncmp(extra, st_user_info.csUserName, strlen(st_user_info.csUserName)))
							&& (t_msg_head->dvrip.dvrip_extlen - 2 == strlen(st_user_info.csUserName) + strlen(st_user_info.csPassword))
							&& (0 == strncmp(extra + strlen(st_user_info.csUserName) + 2, st_user_info.csPassword, strlen(st_user_info.csPassword))))
						{
							t_msg_head->c[8] = 0;
							break;
						}
					}
				}
				g_nw_search_run_index = 6043;

				/* ��¼ʧ�ܷ�����  0:���벻��ȷ 1:�ʺŲ����� 3:�ʺ��Ѿ���¼ 4:�ʺű�����
				5:�ʺű���������� 6:��Դ���㣬ϵͳæ 7:�汾���ԣ��޷���½ */
				t_msg_head_send->c[9] = 0; //��¼ʧ�ܷ�����

				t_msg_head_send->c[10] = 1;  //ͨ����    
				t_msg_head_send->c[11] = 9;   //��Ƶ���뷽ʽ 8:MPEG4 9:H.264
				t_msg_head_send->c[12] = 51;  //�豸����  51:IPC���Ʒ
				t_msg_head_send->l[4] = 45;    //�豸���ص�Ψһ��ʶ�ţ���־������
				t_msg_head_send->c[28] = 0;  //��Ƶ��ʽ��0: ��ʾPAL��     1: ��ʾNTSC��
				t_msg_head_send->s[15] = 0x8101; //��30��31�ֽڱ�������ֵ �������ز�Ʒ��0x8101, 0x8001, 0x8002, 0x8003

				n_offset = DVRIP_HEAD_T_SIZE;
				memcpy(send_msg + n_offset, mac, 17);
				n_offset += 17;

				n_max_resolution = 0;
				QMAPI_NET_SUPPORT_STREAM_FMT stSupportFmt;
				QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT, 0, &stSupportFmt, sizeof(stSupportFmt));
				for (i = 0; i < 9; i++)
				{
					if (stSupportFmt.stVideoSize[0][i].nWidth * stSupportFmt.stVideoSize[0][i].nHeight > n_max_resolution)
					{
						nWidth = stSupportFmt.stVideoSize[0][i].nWidth;
						nHeight = stSupportFmt.stVideoSize[0][i].nHeight;
						n_max_resolution = nWidth * nHeight;
					}
				}
				g_nw_search_run_index = 6044;

				memset(a_extra_sting, 0, sizeof(a_extra_sting));
				sprintf(a_extra_sting, "IPC%5d*%-5d", nWidth, nHeight);
				n_extra_len = strlen(a_extra_sting);
				strncpy(send_msg + n_offset, a_extra_sting, n_extra_len);
				n_offset += n_extra_len;
				t_msg_head_send->c[2] = 17 + n_extra_len;   //mac��ַ���ȼ����豸����   

				struct sockaddr_in udpaddrto;
				bzero(&udpaddrto, sizeof(struct sockaddr_in));
				udpaddrto.sin_family = AF_INET;
				udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
				udpaddrto.sin_port = htons(ZHINUO_SEND_PORT);

				t_msg_head_send->dvrip.cmd = ACK_LOG_ON;
				g_nw_search_run_index = 6045;

				//�ӹ㲥��ַ������Ϣ  
				ret = sendto(sockedfd, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
				if (ret <= 0)
				{
					X6_TRACE("send error....:%d\n", ret);
				}
				g_nw_search_run_index = 6046;
			}
		}
		g_nw_search_run_index = 605;
		if (0xc1 == t_msg_head->dvrip.cmd)
		{
			g_nw_search_run_index = 6051;
			if (0 == strncmp(mac, extra + 164, 17))
			{
				g_nw_search_run_index = 6052;
				ZhiNuo_Dev_Search * str_dev_search = (ZhiNuo_Dev_Search *)extra;
				// 						X6_TRACE("%d,HostIP:%s \n", sizeof(ZhiNuo_Dev_Search), (char *)inet_ntoa((unsigned int)str_dev_search->HostIP));
				// 						X6_TRACE("Submask:%s\n", (char *)inet_ntoa(str_dev_search->Submask));
				// 						X6_TRACE("GateWayIP:%s\n", (char *)inet_ntoa(str_dev_search->GateWayIP));
				// 						X6_TRACE("DNSIP:%s\n", (char *)inet_ntoa(str_dev_search->DNSIP));

				//��ȡ�������������
				QMAPI_NET_NETWORK_CFG st_ipc_net_info;
				if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
				{
					X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
					goto ZhiNuo_Search_End_v2;
				}

				//��ȡ�������������
				QMAPI_NET_WIFI_CONFIG st_wifi_net_info;
				if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
				{
					X6_TRACE("QMAPI_SYSCFG_GET_WIFICFG fail\n");
					goto ZhiNuo_Search_End_v2;
				}
				g_nw_search_run_index = 6053;

				if (st_wifi_net_info.bWifiEnable && st_wifi_net_info.byStatus == 0 && 1 != st_wifi_net_info.byWifiMode)
				{
					struct in_addr objAddr;

					memset(st_wifi_net_info.dwNetIpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->HostIP;
					strcpy(st_wifi_net_info.dwNetIpAddr.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_wifi_net_info.dwNetMask.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->Submask;
					strcpy(st_wifi_net_info.dwNetMask.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_wifi_net_info.dwGateway.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->GateWayIP;
					strcpy(st_wifi_net_info.dwGateway.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_wifi_net_info.dwDNSServer.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->DNSIP;
					strcpy(st_wifi_net_info.dwDNSServer.csIpV4, (char*)inet_ntoa(objAddr));
					st_wifi_net_info.byEnableDHCP = 0;

					//�����������������
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
					{
						X6_TRACE("QMAPI_SYSCFG_SET_WIFICFG fail\n");
						goto ZhiNuo_Search_End_v2;
					}
				}
				else
				{
					struct in_addr objAddr;

					memset(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->HostIP;
					strcpy(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->Submask;
					strcpy(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_ipc_net_info.stGatewayIpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->GateWayIP;
					strcpy(st_ipc_net_info.stGatewayIpAddr.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->DNSIP;
					strcpy(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, (char*)inet_ntoa(objAddr));
					st_ipc_net_info.byEnableDHCP = 0;

					//���ñ������������
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
					{
						X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
						goto ZhiNuo_Search_End_v2;
					}
				}
				g_nw_search_run_index = 6054;

				char ch_param_type = 0;
				char ch_child_type = 0;
				char ch_config_edition = 0;
				//char ch_param_effect_flag = 0;
				char ch_child_type_limit = 0;
				char tem_buf[DVRIP_HEAD_T_SIZE] = { 0 };
				memcpy(tem_buf, smsg, DVRIP_HEAD_T_SIZE);
				DVRIP_HEAD_T *t_msg_head = (DVRIP_HEAD_T *)tem_buf;

				X6_TRACE("hl:%d, v:%d, vextralen:%d\n", t_msg_head->dvrip.dvrip_hl,
						 t_msg_head->dvrip.dvrip_v, t_msg_head->dvrip.dvrip_extlen);

				ch_param_type = t_msg_head->c[16];
				ch_child_type = t_msg_head->c[17];
				ch_config_edition = t_msg_head->c[18];
				//ch_param_effect_flag = t_msg_head->c[20];
				ch_child_type_limit = t_msg_head->c[24];
				g_nw_search_run_index = 6055;

				//
				X6_TRACE("ch_param_type:%d, ch_child_type:%d, ch_config_edition:%d, ch_param_effect_flag:%d, ch_child_type_limit:%d\n",
						 t_msg_head->c[16], t_msg_head->c[17], t_msg_head->c[18], t_msg_head->c[20], t_msg_head->c[24]);

				//rcv_msg_len = DVRIP_HEAD_T_SIZE + t_msg_head->dvrip.dvrip_extlen;


				char send_msg[BUFLEN] = { 0 };
				t_msg_head = (DVRIP_HEAD_T *)send_msg;
				ZERO_DVRIP_HEAD_T(t_msg_head)
					t_msg_head->dvrip.cmd = ACK_SET_CONFIG;
				t_msg_head->c[2] = 17 + strlen(DEV_NAME);   //mac��ַ���ȼ����豸����
				t_msg_head->c[8] = 0; //������0:�ɹ�1:ʧ��2:���ݲ��Ϸ�3:��ʱ�޷�����4:û��Ȩ��
				t_msg_head->c[9] = 1; //0������Ҫ���� 1����Ҫ����������Ч
				t_msg_head->c[16] = ch_param_type;
				t_msg_head->c[17] = ch_child_type;
				t_msg_head->c[18] = ch_config_edition;
				t_msg_head->c[24] = ch_child_type_limit;
				g_nw_search_run_index = 6056;

				n_offset = DVRIP_HEAD_T_SIZE;
				memcpy(send_msg + n_offset, mac, 17);
				n_offset += 17;
				n_max_resolution = 0;
				QMAPI_NET_SUPPORT_STREAM_FMT stSupportFmt;
				QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT, 0, &stSupportFmt, sizeof(stSupportFmt));
				for (i = 0; i < 9; i++)
				{
					if (stSupportFmt.stVideoSize[0][i].nWidth * stSupportFmt.stVideoSize[0][i].nHeight > n_max_resolution)
					{
						nWidth = stSupportFmt.stVideoSize[0][i].nWidth;
						nHeight = stSupportFmt.stVideoSize[0][i].nHeight;
						n_max_resolution = nWidth * nHeight;
					}
				}

				memset(a_extra_sting, 0, sizeof(a_extra_sting));
				sprintf(a_extra_sting, "IPC%5d*%-5d", nWidth, nHeight);
				n_extra_len = strlen(a_extra_sting);
				strncpy(send_msg + n_offset, a_extra_sting, n_extra_len);
				n_offset += n_extra_len;
				t_msg_head->c[2] = 17 + n_extra_len;   //mac��ַ���ȼ����豸����   

				struct sockaddr_in udpaddrto;
				bzero(&udpaddrto, sizeof(struct sockaddr_in));
				udpaddrto.sin_family = AF_INET;
				udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
				udpaddrto.sin_port = htons(ZHINUO_SEND_PORT);

				t_msg_head->dvrip.cmd = ACK_SET_CONFIG;
				g_nw_search_run_index = 6057;

				//�ӹ㲥��ַ������Ϣ  
				ret = sendto(sockedfd, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
				if (ret <= 0)
				{
					X6_TRACE("send error....:%d\n", ret);
				}
				sleep(3); //��֤���ݷ���������
				ret = QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_SAVECFG_ASYN, 0, 0, 0);
				if (0 != ret)
				{
					X6_TRACE("DMS_NET_GET_PICCFG error\n");
				}
				g_nw_search_run_index = 6058;
			}
		}
		g_nw_search_run_index = 606;
	}

ZhiNuo_Search_End_v2:
	close(sockedfd);
	sockedfd = -1;

	return 0;
}

void zhiNuo_SendEndProc(int sockfd)
{
	zhiNuo_search_stop_v2(0, ZHINUO_SEND_PORT);
}


int daHua_CreateSearchSocket(int *socktype)
{
	// �󶨵�ַ  
	struct sockaddr_in addrto;
	bzero(&addrto, sizeof(struct sockaddr_in));
	addrto.sin_family = AF_INET;
	addrto.sin_addr.s_addr = htonl(INADDR_ANY);
	addrto.sin_port = htons(DAHUA_RCV_PORT);

	// �㲥��ַ  
	struct sockaddr_in from;
	bzero(&from, sizeof(struct sockaddr_in));

	if ((g_dahua_sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		X6_TRACE("socket error\n");
		return -1;
	}

	//���ø��׽���Ϊ�㲥���ͣ�  
	const int opt = 1;	
	int nb = 0;
	nb = setsockopt(g_dahua_sock, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set socket error...\n");
		goto DaHua_Search_Close;
	}

	struct ifreq ifr;
	struct sockaddr_in broadcast_addr;      /*���ص�ַ*/
	strcpy(ifr.ifr_name, IFNAME);

	if (ioctl(g_dahua_sock, SIOCGIFBRDADDR, &ifr) == -1)
	{
		; // perror("ioctl error"), exit(1);
	}

	memcpy(&broadcast_addr, &ifr.ifr_broadaddr, sizeof(struct sockaddr_in));
	broadcast_addr.sin_port = htons(DAHUA_SEND_PORT);/*���ù㲥�˿�*/

	if (bind(g_dahua_sock, (struct sockaddr *)&(addrto), sizeof(struct sockaddr_in)) == -1)
	{
		X6_TRACE("bind error...\n");
		goto DaHua_Search_Close;
	}
	return g_dahua_sock;
	
DaHua_Search_Close:
	close(g_dahua_sock);
	
	return -1;
}

int daHua_ProcessRequest(int handle, int sockfd, int socktype)
{
	g_nw_search_run_index = 700;
	// 1.
	int sockedfdX = -1;
	sockedfdX = socket(AF_INET, SOCK_DGRAM, 0);			/*�������ݱ��׽���*/
	if (sockedfdX < 0)
	{
		X6_TRACE("socket error\n");
		goto DaHua_Search_End_v2;
	}

	const int opt = 1;
	int nb = setsockopt(sockedfdX, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));
	if (nb == -1)
	{
		X6_TRACE("set sockedfdX error...\n");
		goto DaHua_Search_End_v2;
	}
	g_nw_search_run_index = 701;

	// 2.
	int i = 0;
	int nWidth = 0;
	int nHeight = 0;
	int n_max_resolution = 0;
	int n_extra_len = 0;
	char a_extra_sting[255];
	int n_offset = 0;
	char mac[17];

	int len = sizeof(struct sockaddr_in);
	char smsg[1024] = { 0 };
	int ret = 0;

	int g_dahua_sock = sockfd;
	int g_zhinuo_handle = handle;

	// �㲥��ַ  
	struct sockaddr_in from;
	bzero(&from, sizeof(struct sockaddr_in));
	g_nw_search_run_index = 702;

	//�ӹ㲥��ַ������Ϣ  
	ret = recvfrom(g_dahua_sock, smsg, 1024, 0, (struct sockaddr*)&from, (socklen_t*)&len);
	if (ret <= 0)
	{
		X6_TRACE("read error....%d:%s\n", ret, strerror(errno));
	}
	else
	{
		g_nw_search_run_index = 703;
		//int rcv_msg_len = 0;
		char tem_buf[DVRIP_HEAD_T_SIZE] = { 0 };
		memcpy(tem_buf, smsg, DVRIP_HEAD_T_SIZE);
		DVRIP_HEAD_T *t_msg_head = (DVRIP_HEAD_T *)tem_buf;
		char * extra = smsg + DVRIP_HEAD_T_SIZE;
		//X6_TRACE("type:%d, cmd:%x,len:%d,%s,extra:%d,fromip:%s,fromeport:%d\n", t_msg_head->c[16], t_msg_head->dvrip.cmd, ret, smsg, t_msg_head->dvrip.dvrip_extlen, inet_ntoa(from.sin_addr), from.sin_port);                  
		g_nw_search_run_index = 704;

		if (CMD_DEV_SEARCH == t_msg_head->dvrip.cmd)
		{
			g_nw_search_run_index = 7041;
			n_offset = 0;
			char extra_data[88] = { 0 };
			ZhiNuo_Dev_Search * str_dev_search = (ZhiNuo_Dev_Search *)extra_data;

			//��ȡ�������������
			QMAPI_NET_NETWORK_CFG st_ipc_net_info;
			if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
			{
				X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
				goto DaHua_Search_End_v2;
			}

			str_dev_search->Version[0] = 0X32;  //�汾��Ϣ 
			str_dev_search->Version[1] = 0X33;
			str_dev_search->Version[2] = 0X30;
			str_dev_search->Version[3] = 0X32;

			str_dev_search->HostName[0] = 0x44; //������
			str_dev_search->HostName[1] = 0x56;
			str_dev_search->HostName[2] = 0x52;

			//��ȡ�������������
			QMAPI_NET_WIFI_CONFIG st_wifi_net_info;
			if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
			{
				X6_TRACE("QMAPI_SYSCFG_GET_WIFICFG fail\n");
				goto DaHua_Search_End_v2;
			}

			struct sockaddr_in adr_inet;

			//������߿��þ�ֻ�����ߵ�����
			if (st_wifi_net_info.bWifiEnable && st_wifi_net_info.byStatus == 0 && 1 != st_wifi_net_info.byWifiMode)
			{
				inet_aton(st_wifi_net_info.dwNetIpAddr.csIpV4, &adr_inet.sin_addr);
				str_dev_search->HostIP = (unsigned long)adr_inet.sin_addr.s_addr;
				//						X6_TRACE("ip:%s\n", (char *)inet_ntoa(str_dev_search->HostIP));
				inet_aton(st_wifi_net_info.dwNetMask.csIpV4, &adr_inet.sin_addr);
				str_dev_search->Submask = (unsigned long)adr_inet.sin_addr.s_addr;
				inet_aton(st_wifi_net_info.dwGateway.csIpV4, &adr_inet.sin_addr);
				str_dev_search->GateWayIP = (unsigned long)adr_inet.sin_addr.s_addr;
				inet_aton(st_wifi_net_info.dwDNSServer.csIpV4, &adr_inet.sin_addr);
				str_dev_search->DNSIP = (unsigned long)adr_inet.sin_addr.s_addr;

			}
			else
			{
				inet_aton(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, &adr_inet.sin_addr);
				str_dev_search->HostIP = (unsigned long)adr_inet.sin_addr.s_addr;
				//						X6_TRACE("ip:%s\n", (char *)inet_ntoa(str_dev_search->HostIP));
				inet_aton(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, &adr_inet.sin_addr);
				str_dev_search->Submask = (unsigned long)adr_inet.sin_addr.s_addr;
				inet_aton(st_ipc_net_info.stGatewayIpAddr.csIpV4, &adr_inet.sin_addr);
				str_dev_search->GateWayIP = (unsigned long)adr_inet.sin_addr.s_addr;
				inet_aton(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, &adr_inet.sin_addr);
				str_dev_search->DNSIP = (unsigned long)adr_inet.sin_addr.s_addr;
			}
			g_nw_search_run_index = 7042;

			inet_aton("10.1.0.2", &adr_inet.sin_addr);
			str_dev_search->AlarmServerIP = (unsigned long)adr_inet.sin_addr.s_addr;
			str_dev_search->HttpPort = st_ipc_net_info.wHttpPort;
			str_dev_search->TCPPort = TCP_LISTEN_PORT;
			str_dev_search->TCPMaxConn = MAX_LINK_NUM;
			str_dev_search->SSLPort = 8443;
			str_dev_search->UDPPort = 8001;
			inet_aton("239.255.42.42", &adr_inet.sin_addr);
			str_dev_search->McastIP = (unsigned long)adr_inet.sin_addr.s_addr;
			str_dev_search->McastPort = 36666;
			g_nw_search_run_index = 7043;

			//rcv_msg_len = DVRIP_HEAD_T_SIZE + t_msg_head->dvrip.dvrip_extlen;
			char send_msg[512] = { 0 };
			t_msg_head = (DVRIP_HEAD_T *)send_msg;
			memset(send_msg, 0, sizeof(send_msg));
			t_msg_head->c[2] = 17 + strlen(DEV_NAME);   //mac��ַ���ȼ����豸����
			t_msg_head->dvrip.dvrip_extlen = 0x58;  //Ϊextra_data����ĳ���           
			t_msg_head->dvrip.cmd = ACK_DEV_SEARCH;
			t_msg_head->c[16] = 2; //�̶�Ϊ2
			t_msg_head->c[19] = 0; //������ 0:���� 1:��Ȩ�� 2:�޶�Ӧ�����ṩ
			t_msg_head->c[20] = 0xa3; //����ץ�����������ֵ�������

			struct sockaddr_in udpaddrto;
			bzero(&udpaddrto, sizeof(struct sockaddr_in));
			udpaddrto.sin_family = AF_INET;
			udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
			udpaddrto.sin_port = htons(DAHUA_SEND_PORT);
			n_offset += DVRIP_HEAD_T_SIZE;

			memcpy(send_msg + n_offset, &extra_data, sizeof(extra_data));
			n_offset += sizeof(extra_data);
			sprintf(send_msg + n_offset, "%02x:%02x:%02x:%02x:%02x:%02x", st_ipc_net_info.stEtherNet[0].byMACAddr[0],
					st_ipc_net_info.stEtherNet[0].byMACAddr[1],
					st_ipc_net_info.stEtherNet[0].byMACAddr[2],
					st_ipc_net_info.stEtherNet[0].byMACAddr[3],
					st_ipc_net_info.stEtherNet[0].byMACAddr[4],
					st_ipc_net_info.stEtherNet[0].byMACAddr[5]);
			memcpy(mac, send_msg + n_offset, 17);
			//memcpy(temp, &st_net_info.szMac, 17);
			n_offset += 17;
			memcpy(send_msg + n_offset, DEV_NAME, strlen(DEV_NAME));
			n_offset += strlen(DEV_NAME);
			g_nw_search_run_index = 7044;

			n_max_resolution = 0;
			QMAPI_NET_SUPPORT_STREAM_FMT stSupportFmt;
			QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT, 0, &stSupportFmt, sizeof(stSupportFmt));
			for (i = 0; i < 9; i++)
			{
				if (stSupportFmt.stVideoSize[0][i].nWidth * stSupportFmt.stVideoSize[0][i].nHeight > n_max_resolution)
				{
					nWidth = stSupportFmt.stVideoSize[0][i].nWidth;
					nHeight = stSupportFmt.stVideoSize[0][i].nHeight;
					n_max_resolution = nWidth * nHeight;
				}
			}
			g_nw_search_run_index = 7045;

			n_extra_len = strlen("Name:PZC3EW11102007\r\nDevice:IPC-IPVM3150F\r\nIPv6Addr:2001:250:3000:1::1:2/112;gateway:2001:250:3000:1::1:1\r\nIPv6Addr:fe80::9202:a9ff:fe1b:f6b3/64;gateway:fe80::\r\n\r\n");
			sprintf(a_extra_sting, "Name:IPC%5d*%-5d\r\nDevice:IPC-IPVM3150F\r\nIPv6Addr:2001:250:3000:1::1:2/112;gateway:2001:250:3000:1::1:1\r\nIPv6Addr:fe80::9202:a9ff:fe1b:f6b3/64;gateway:fe80::\r\n\r\n", nWidth, nHeight);
			strncpy(send_msg + n_offset, a_extra_sting, n_extra_len);
			//strcpy(send_msg + n_offset, "Name:IPC%d*%d\r\nDevice:IPC-IPVM3150F\r\nIPv6Addr:2001:250:3000:1::1:2/112;gateway:2001:250:3000:1::1:1\r\nIPv6Addr:fe80::9202:a9ff:fe1b:f6b3/64;gateway:fe80::\r\n\r\n");
			n_offset += n_extra_len;
			g_nw_search_run_index = 7046;

			//�ӹ㲥��ַ������Ϣ  
			usleep(500000); //˯��500���룬����nvr��������̫�࣬�������������֤nvrÿ�ζ����ѵ��豸
			g_nw_search_run_index = 7047;
			ret = sendto(sockedfdX, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
			if (ret <= 0)
			{
				X6_TRACE("send error....:%d\n", ret);
			}
			g_nw_search_run_index = 7048;
		}
		g_nw_search_run_index = 705;

		//���޸�ip���õ�½�����´���û��ִ�е���������Ժ���˹��ܿ����õ�
		if (CMD_DAHUA_LOG_ON == t_msg_head->dvrip.cmd)
		{
			g_nw_search_run_index = 7051;
			X6_TRACE("name:%s, pass:%s, cmd:%x, extralen:%d, extra:%s, clienttype:%d, locktype:%d, hl:%d, v:%d\n",
					 t_msg_head->dvrip.dvrip_p, &t_msg_head->dvrip.dvrip_p[8], t_msg_head->dvrip.cmd
					 , t_msg_head->dvrip.dvrip_extlen, extra, t_msg_head->dvrip.dvrip_p[18],
					 t_msg_head->dvrip.dvrip_p[19], t_msg_head->dvrip.dvrip_hl, t_msg_head->dvrip.dvrip_v);
			g_nw_search_run_index = 7052;

			if (0 == strncmp(mac, extra, 17))
			{
				g_nw_search_run_index = 7053;
				char send_msg[BUFLEN] = { 0 };
				t_msg_head = (DVRIP_HEAD_T *)send_msg;
				ZERO_DVRIP_HEAD_T(t_msg_head)

				t_msg_head->c[1] = 0; //0��û�� 1�����ж໭��Ԥ������ 
				t_msg_head->c[2] = 17 + strlen(DEV_NAME); //uuid

				/*//��ȡ�û�������
				QMAPI_NET_USER_INFO st_user_info;
				if(0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_user_info, sizeof(QMAPI_NET_USER_INFO)))
				{
				X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
				return NULL;
				}

				printf("name:%s, pass:%s\n", st_user_info.csUserName, st_user_info.csPassword);
				if((0 == strcmp(t_msg_head->dvrip.dvrip_p, st_user_info.csUserName))
				&& (0 == strcmp(&t_msg_head->dvrip.dvrip_p[8], st_user_info.csPassword)))
				{
				t_msg_head->c[8] = 0;
				}
				else
				{
				t_msg_head->c[8] = 1; //0: ��ʾ��¼�ɹ� 1: ��ʾ��¼ʧ�� 3: �û��ѵ�¼
				}*/

				t_msg_head->c[8] = 0;

				/* ��¼ʧ�ܷ�����  0:���벻��ȷ 1:�ʺŲ����� 3:�ʺ��Ѿ���¼ 4:�ʺű�����
				5:�ʺű���������� 6:��Դ���㣬ϵͳæ 7:�汾���ԣ��޷���½ */
				t_msg_head->c[9] = 2; //��¼ʧ�ܷ�����
				t_msg_head->c[10] = 1;  //ͨ����    
				t_msg_head->c[11] = 9;   //��Ƶ���뷽ʽ 8:MPEG4 9:H.264
				t_msg_head->c[12] = 51;  //�豸����  51:IPC���Ʒ
				t_msg_head->l[4] = 45;    //�豸���ص�Ψһ��ʶ�ţ���־������
				t_msg_head->c[28] = 0;  //��Ƶ��ʽ��0: ��ʾPAL��     1: ��ʾNTSC��
				t_msg_head->s[15] = 0x8101; //��30��31�ֽڱ�������ֵ �������ز�Ʒ��0x8101, 0x8001, 0x8002, 0x8003

				n_offset = DVRIP_HEAD_T_SIZE;
				memcpy(send_msg + n_offset, mac, 17);
				n_offset += 17;
				memcpy(send_msg + n_offset, DEV_NAME, strlen(DEV_NAME));
				n_offset += strlen(DEV_NAME);

				struct sockaddr_in udpaddrto;
				bzero(&udpaddrto, sizeof(struct sockaddr_in));
				udpaddrto.sin_family = AF_INET;
				udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
				udpaddrto.sin_port = htons(DAHUA_SEND_PORT);

				t_msg_head->dvrip.cmd = ACK_LOG_ON;
				g_nw_search_run_index = 7054;

				//�ӹ㲥��ַ������Ϣ  
				ret = sendto(sockedfdX, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
				if (ret <= 0)
				{
					X6_TRACE("send error....:%d\n", ret);
				}
				g_nw_search_run_index = 7055;
			}
		}
		g_nw_search_run_index = 706;

		if (0xc1 == t_msg_head->dvrip.cmd)
		{
			g_nw_search_run_index = 7061;
			if (0 == strncmp(mac, extra + 0x58, 17)) //Ϊextra_data����ĳ��� 
			{
				g_nw_search_run_index = 7062;
				ZhiNuo_Dev_Search * str_dev_search = (ZhiNuo_Dev_Search *)extra;
				// 						X6_TRACE("%d,HostIP:%s \n", sizeof(ZhiNuo_Dev_Search), (char *)inet_ntoa(str_dev_search->HostIP));
				// 						X6_TRACE("Submask:%s\n", (char *)inet_ntoa(str_dev_search->Submask));
				// 						X6_TRACE("GateWayIP:%s\n", (char *)inet_ntoa(str_dev_search->GateWayIP));
				// 						X6_TRACE("DNSIP:%s\n", (char *)inet_ntoa(str_dev_search->DNSIP));

				//��ȡ�������������
				QMAPI_NET_NETWORK_CFG st_ipc_net_info;
				if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
				{
					X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
					goto DaHua_Search_End_v2;
				}

				//��ȡ�������������
				QMAPI_NET_WIFI_CONFIG st_wifi_net_info;
				if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_GET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
				{
					X6_TRACE("QMAPI_SYSCFG_GET_WIFICFG fail\n");
					goto DaHua_Search_End_v2;
				}

				if (st_wifi_net_info.bWifiEnable  && st_wifi_net_info.byStatus == 0 && 1 != st_wifi_net_info.byWifiMode)
				{
					struct in_addr objAddr;

					memset(st_wifi_net_info.dwNetIpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->HostIP;
					strcpy(st_wifi_net_info.dwNetIpAddr.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_wifi_net_info.dwNetMask.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->Submask;
					strcpy(st_wifi_net_info.dwNetMask.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_wifi_net_info.dwGateway.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->GateWayIP;
					strcpy(st_wifi_net_info.dwGateway.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_wifi_net_info.dwDNSServer.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->DNSIP;
					strcpy(st_wifi_net_info.dwDNSServer.csIpV4, (char*)inet_ntoa(objAddr));
					st_wifi_net_info.byEnableDHCP = 0;

					//�����������������
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_WIFICFG, 0, &st_wifi_net_info, sizeof(st_wifi_net_info)))
					{
						X6_TRACE("QMAPI_SYSCFG_SET_WIFICFG fail\n");
						goto DaHua_Search_End_v2;
					}
				}
				else
				{
					struct in_addr objAddr;

					memset(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->HostIP;
					strcpy(st_ipc_net_info.stEtherNet[0].strIPAddr.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->Submask;
					strcpy(st_ipc_net_info.stEtherNet[0].strIPMask.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_ipc_net_info.stGatewayIpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->GateWayIP;
					strcpy(st_ipc_net_info.stGatewayIpAddr.csIpV4, (char*)inet_ntoa(objAddr));
					memset(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, 0, QMAPI_MAX_IP_LENGTH);
					objAddr.s_addr = str_dev_search->DNSIP;
					strcpy(st_ipc_net_info.stDnsServer1IpAddr.csIpV4, (char*)inet_ntoa(objAddr));
					st_ipc_net_info.byEnableDHCP = 0;

					//���ñ������������
					if (0 != QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_NETCFG, 0, &st_ipc_net_info, sizeof(st_ipc_net_info)))
					{
						X6_TRACE("DMS_NET_GET_PLATFORMCFG fail\n");
						goto DaHua_Search_End_v2;
					}
				}
				g_nw_search_run_index = 7063;

				char ch_param_type = 0;
				char ch_child_type = 0;
				char ch_config_edition = 0;
				//char ch_param_effect_flag = 0;
				char ch_child_type_limit = 0;
				char tem_buf[DVRIP_HEAD_T_SIZE] = { 0 };
				memcpy(tem_buf, smsg, DVRIP_HEAD_T_SIZE);
				DVRIP_HEAD_T *t_msg_head = (DVRIP_HEAD_T *)tem_buf;

				X6_TRACE("hl:%d, v:%d, vextralen:%d\n", t_msg_head->dvrip.dvrip_hl,
						 t_msg_head->dvrip.dvrip_v, t_msg_head->dvrip.dvrip_extlen);

				ch_param_type = t_msg_head->c[16];
				ch_child_type = t_msg_head->c[17];
				ch_config_edition = t_msg_head->c[18];
				//ch_param_effect_flag = t_msg_head->c[20];
				ch_child_type_limit = t_msg_head->c[24];

				//
				X6_TRACE("ch_param_type:%d, ch_child_type:%d, ch_config_edition:%d, ch_param_effect_flag:%d, ch_child_type_limit:%d\n",
						 t_msg_head->c[16], t_msg_head->c[17], t_msg_head->c[18], t_msg_head->c[20], t_msg_head->c[24]);

				//rcv_msg_len = DVRIP_HEAD_T_SIZE + t_msg_head->dvrip.dvrip_extlen;
				g_nw_search_run_index = 7064;

				char send_msg[BUFLEN] = { 0 };
				t_msg_head = (DVRIP_HEAD_T *)send_msg;
				ZERO_DVRIP_HEAD_T(t_msg_head)
					t_msg_head->dvrip.cmd = ACK_SET_CONFIG;
				t_msg_head->c[2] = 17 + strlen(DEV_NAME);   //mac��ַ���ȼ����豸����
				t_msg_head->c[8] = 0; //������0:�ɹ�1:ʧ��2:���ݲ��Ϸ�3:��ʱ�޷�����4:û��Ȩ��
				t_msg_head->c[9] = 1; //0������Ҫ���� 1����Ҫ����������Ч
				t_msg_head->c[16] = ch_param_type;
				t_msg_head->c[17] = ch_child_type;
				t_msg_head->c[18] = ch_config_edition;
				t_msg_head->c[24] = ch_child_type_limit;

				n_offset = DVRIP_HEAD_T_SIZE;
				memcpy(send_msg + n_offset, mac, 17);
				n_offset += 17;
				memcpy(send_msg + n_offset, DEV_NAME, strlen(DEV_NAME));
				n_offset += strlen(DEV_NAME);

				struct sockaddr_in udpaddrto;
				bzero(&udpaddrto, sizeof(struct sockaddr_in));
				udpaddrto.sin_family = AF_INET;
				udpaddrto.sin_addr.s_addr = inet_addr("255.255.255.255"); //htonl(INADDR_BROADCAST);  //
				udpaddrto.sin_port = htons(DAHUA_SEND_PORT);

				t_msg_head->dvrip.cmd = ACK_SET_CONFIG;

				//�ӹ㲥��ַ������Ϣ  
				ret = sendto(sockedfdX, send_msg, n_offset, 0, (struct sockaddr*)&udpaddrto, sizeof(udpaddrto));
				if (ret <= 0)
				{
					X6_TRACE("send error....:%d\n", ret);
				}
				g_nw_search_run_index = 7065;

				sleep(3); //��֤���ݷ���������
				ret = QMapi_sys_ioctrl(g_zhinuo_handle, QMAPI_SYSCFG_SET_SAVECFG_ASYN, 0, 0, 0);
				if (0 != ret)
				{
					X6_TRACE("DMS_NET_GET_PICCFG error\n");
				}
				g_nw_search_run_index = 7066;

				goto DaHua_Search_End_v2;
			}
		}
		g_nw_search_run_index = 707;
	}

DaHua_Search_End_v2:
	g_nw_search_run_index = 710;
	close(sockedfdX);
	sockedfdX = -1;
	
	return 0;
}

void daHua_SendEndProc(int sockfd)
{
	zhiNuo_search_stop_v2(1, DAHUA_SEND_PORT);
}

