#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <unistd.h> 

#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <assert.h>


#include "QMAPIType.h"
#include "domain.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */


const unsigned char DNS_REQ_DATA_HEAD[12] = {0x2b,0x50,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00};
const unsigned char DNS_REQ_DATA_TAIL[4]  = {0x00,0x01,0x00,0x01};
const unsigned short DNS_PORT = 53;

static void ReleaseHost(struct hostent *pHost)
{
	if (NULL != pHost)
	{
		delete[] pHost->h_addr_list[0];
		delete[] pHost->h_addr_list[1];
		delete[] pHost->h_addr_list[2];
		delete[] pHost->h_addr_list[3];
		delete[] pHost->h_addr_list;
		delete pHost;
	}
}

static bool ParseDomainName(char * pDNS, size_t &length)
{
	if (length < strlen(pDNS) + 2)
	{
		printf("%s:%s:%d, the length is too short\n", __FUNCTION__, __FILE__, __LINE__);
		return false;
	}
	char *pDNSTemp = new char [length];
	if(NULL == pDNSTemp)
	{
		printf("%s:%s:%d, New error\n", __FUNCTION__, __FILE__, __LINE__);
		return false;
	}
	else
	{
		memcpy(pDNSTemp, pDNS, length);
		memset(pDNS, 0, length);
		strcpy(pDNS+1, pDNSTemp);
		delete [] pDNSTemp;
		pDNSTemp = NULL;
	}

	char * pCurrent	= pDNS+1;
	char * pMark	= pDNS;
	*pMark = 0;

	while ('\0' != *pCurrent)
	{
		//ֻҪ��ǰ�ַ���Ϊ�ַ����Ľ�����־
		//�����ǰ�ַ��� .
		if ('.' == *pCurrent)
		{
			//��������������� . ,���ʾ�����ʽ��, ���ش���
			if ('.' == *(pCurrent-1))
			{
				printf("%s:%s:%d, The dns %s is invalid\n", __FUNCTION__, __FILE__, __LINE__, pDNS);
				assert(false);
				return false;
			}
			pMark = pCurrent;
			*pMark = 0;
		}
		else
		{
			(*pMark)++;	//����
		}
		pCurrent++;		//ָ�����
	}

	length = strlen(pDNS) + 1;

	return true;
}

struct hostent *SRDKGetHostbyname(const char * pDNS, char * pDnsServer)
{
	struct hostent * pHost = new hostent;
	if (NULL == pHost)
	{
		printf("%s:%s:%d, New error\n", __FUNCTION__, __FILE__, __LINE__);
		assert(false);
		return NULL;
	}
	else
	{
		memset(pHost, 0, sizeof(struct hostent));
		pHost->h_addr_list = new char*[4];
		assert(NULL != pHost->h_addr_list);
		for(int index1 = 0; index1 < 4; ++index1)
		{
			pHost->h_addr_list[index1] = new char[40];
			assert(NULL != pHost->h_addr_list[index1]);
			memset(pHost->h_addr_list[index1], 0, 40);
		}
	}

	if (inet_aton(pDNS, (struct in_addr*)pHost->h_addr))
	{
		//����������������IP��ַ
		return pHost;
	}

	//��������ΪDNS����ĸ�ʽ
	size_t lengthParseName = strlen(pDNS) + 2;		//�������ַ�������
	char * pParseName = new char[lengthParseName];	//���ڴ洢�����������
	assert(NULL != pParseName);
	memset(pParseName, 0, lengthParseName);
	strcpy(pParseName, pDNS);
	if (!ParseDomainName(pParseName, lengthParseName)) 
	{
		delete [] pParseName;
		pParseName = NULL;
		ReleaseHost(pHost);

		return NULL;
	}

	//����DNS����ͷ����Ϣ	 ��ʽΪ[��ʾ(2�ֽ�)][��־(2�ֽ�)][������(2�ֽ�)][Ӧ����Դ��(2�ֽ�)][��Ȩ��Դ��][������Դ��]{��ѯ����}{Ӧ��}{��Ȩ}{����}
	size_t lengthDatagram = 12 + lengthParseName + 4;
	char * pDadagram = new char[lengthDatagram];
	assert(NULL != pDadagram);
	memcpy(pDadagram, DNS_REQ_DATA_HEAD,12);							//����Э��ͷ
	memcpy(pDadagram + 12, pParseName, lengthParseName);				//����Ҫ����������
	memcpy(pDadagram + 12 + lengthParseName, DNS_REQ_DATA_TAIL, 4);		//����Э��β
	delete [] pParseName;
	pParseName = NULL;

	//���DNS��������IP��ַ
	struct sockaddr_in their_addr;
	memset(&their_addr, 0, sizeof(their_addr));
	their_addr.sin_family = AF_INET;
	their_addr.sin_port = htons(DNS_PORT);
	their_addr.sin_addr.s_addr = inet_addr(pDnsServer);
	if (INADDR_NONE == their_addr.sin_addr.s_addr)
	{
		delete [] pDadagram;
		pDadagram = NULL;

		ReleaseHost(pHost);

		return NULL;
	}

	//����socket��DNS������ͨ��
	int sockfd = -1;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockfd < 0) 
	{
		printf("(%s %d) Failed: open socket failed,%s!\n",__FILE__,__LINE__,strerror(errno));
		delete [] pDadagram;
		pDadagram = NULL;
		ReleaseHost(pHost);

		return NULL;
	}

	timeval timeout;
	timeout.tv_sec	= 5;	//��ʱʱ��Ϊ5s
	timeout.tv_usec = 0;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&timeout, sizeof(timeout))) 
	{
		close(sockfd);

		printf("(%s %d) Failed: setsockopt failed,%s\n",__FILE__,__LINE__,strerror(errno));
		delete [] pDadagram;
		pDadagram = NULL;
		ReleaseHost(pHost);
		return NULL;
	}

	//����DNS���ݲ����շ�������Ӧ
	char revBuffer[1024] = {0};
	int  revLength = 0;

	bool ret =  false;
	//����5��ͨ��
	for (int timer = 0; !ret && timer < 3; timer ++) 
	{
		revLength = sendto(sockfd, (const char*)pDadagram, lengthDatagram, 0, (struct sockaddr *)&their_addr, sizeof(struct sockaddr));
		if (-1 == revLength)
		{
			//printf("%s, %s %d Failed: send DNS data failed, timer=%d, %s!\n",__FUNCTION__, __FILE__,__LINE__,timer, strerror(errno));
			continue;
		}

		memset(revBuffer, 0, sizeof(revBuffer));
		socklen_t addr_len = sizeof(their_addr);

		revLength = recvfrom(sockfd, revBuffer, sizeof(revBuffer), 0, (sockaddr*)&their_addr, &addr_len);	
		if(12 < revLength)
		{
			//�Ƚ�DNS id
			if(0 == memcmp(revBuffer, DNS_REQ_DATA_HEAD, 2)) 
			{
				//�ڻ�Ӧ�����п����ж�����ص�ַ, �õ������
				short temp = 0;
				memcpy(&temp, revBuffer + 6, sizeof(short));
				short nameNum = ntohs(temp);

				char * pAnser = revBuffer;
				pAnser = pAnser+ 12 + lengthParseName + 4;	//12ΪDNSЭ���ͷ����//4Ϊquery�ֶε�:type, class ,��Ϊһ��short����
				int useLen = 12 + lengthParseName + 4;
				int index = 0;
				while( (nameNum > 0) && (useLen + 12 <= revLength) )
				{
					//�õ�������ݵ�����
					memcpy(&temp, pAnser + 2, sizeof(short));
					short nameType = ntohs(temp);
					memcpy(&temp, pAnser + 10, sizeof(short));
					short nameLength = ntohs(temp);

					//�����IP��ַ, ����
					if( (1==nameType) && (useLen + 16 <= revLength) )
					{
						memcpy(&pHost->h_addr_list[index][3],(pAnser+15),1);
						memcpy(&pHost->h_addr_list[index][2],(pAnser+14),1);
						memcpy(&pHost->h_addr_list[index][1],(pAnser+13),1);
						memcpy(&pHost->h_addr_list[index][0],(pAnser+12),1);
						pHost->h_addrtype = AF_INET;
						index ++;
						ret  = true;
						if (2 == index)
						{
							break;
						}
					}
					pAnser = pAnser + 12 + nameLength;
					useLen += 12 + nameLength;
					nameNum --;
				}			
			}
		}
	}

	close(sockfd);
	delete [] pDadagram;
	pDadagram  = NULL;

	if (ret) 
	{		
		return pHost;
	}
	else
	{
		ReleaseHost(pHost);

		return NULL;
	}
}

/* RM#2291: Get DNS Server from config file: /tmp/resolv.conf.    henry.li    2017/03/01 */
static int GetDnsServer(char *dnsServer, unsigned int len)
{
	FILE *fp = NULL;
	char line[32] = {0};

	fp = fopen("/tmp/resolv.conf", "r");

	if (NULL == fp)
	{
		printf("Open dns server file failed!\n");
		return 0;
	}

	if (fgets(line, 32, fp) == NULL)
	{
		printf("Read dns server failed!\n");
		fclose(fp);
		return 0;
	}

	/* cat /tmp/resolv.conf
	nameserver 202.96.199.133 */
	strcpy(dnsServer, line + (strlen("nameserver ")));
	dnsServer[strlen(dnsServer) - 1] = '\0';
	//printf("--\nDnsServer:[%s]------\n", dnsServer);

	fclose(fp);
	return 1;
}


/*
* ����0 ����ʧ��
*/
UINT32 dms_gethostbyname(const char *pDNS)
{
	int i;
	hostent * pHost = NULL;
	UINT32 ip_addr = 0;
	//char nameserver[4][16] = {"114.114.114.114"/*114*/, "8.8.8.8"/*google*/, "180.76.76.76"/*baidu*/, "202.45.84.58"/*hk*/};
	char nameserver[2][16] = {"114.114.114.114"/*114*/, "8.8.8.8"/*google*/};

	/* RM#2291: used Primary DNS from resolv.conf(Web setting).    henry.li    2017/03/01  */
	char dnsserver[32] = {0};

	if (GetDnsServer(dnsserver, 32) == 1)
	{
		strcpy(nameserver[0], dnsserver);
	}

	//printf("dnsserver[0]=[%s], dnsserver[1]=[%s]\n", nameserver[0], nameserver[1]);
	if(NULL == pDNS)
		return 0;

	for(i = 0; i < 2; i++)
	{
		pHost = SRDKGetHostbyname(pDNS, nameserver[i]);
		if (NULL != pHost)
		{
			ip_addr = *((unsigned long*)pHost->h_addr);

			ReleaseHost(pHost);
			
			break;
		}
	}
/*
 	if(2 == i)
	{
		ip_addr = gethostbyname_fromserver(pDNS);
	}
*/
	return ip_addr;
}








#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


