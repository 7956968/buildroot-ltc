
#ifndef __QMAPI_NET_WORK_H__
#define __QMAPI_NET_WORK_H__

#include "QMAPI.h"

#define QMAPI_ETH_DEV   "eth0"

typedef int (*CBDhcpAddr)(char *IPAddr, char *IPMask, char *GatewayIpAddr, char *Dns1Addr, char *Dns2Addr);

/*************************************************************************
	��ʼ������������ã�IP��ַ �������� ���� DNS DHCP

	pNetWorkCfg [in]: ����Ĳ���
	Callback    [in]: DHCP �ɹ�֮����Ҫ�����������ò�����ͨ���ص��ķ�ʽ��֪Ӧ�ò㣻ֻ�п���DHCP��ʱ������
*/
int QMAPI_InitNetWork(QMAPI_NET_NETWORK_CFG *pNetWorkCfg, CBDhcpAddr Callback);


/*************************************************************************
	�޸�����������ã�

	pNetWorkCfg [in]: ����Ĳ���
	Callback    [in]: DHCP �ɹ�֮����Ҫ�����������ò�����ͨ���ص��ķ�ʽ��֪Ӧ�ò㣻ֻ�п���DHCP��ʱ������
*/
int QMAPI_SetNetWork(QMAPI_NET_NETWORK_CFG *pNetWorkCfg, CBDhcpAddr Callback);

#endif

