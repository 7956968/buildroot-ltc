#ifndef _AUTO_CHECK_H_
#define _AUTO_CHECK_H_

#include "QMAPINetSdk.h"
#include "DMSErrno.h"
#include "wireless.h"

typedef struct tagAUTOCHECKCMDNODE
{
    int rSock;
    char szBuff[512];
    struct tagAUTOCHECKCMDNODE *pNext;
}CAutoCheckCmdNode;
CAutoCheckCmdNode* AutoCheckCmdNode_AddTail(char *pData, int len, int rSock);

#define     CMD_TEST_UDISK_OK            0x00000000
#define     CMD_TEST_UDISK_NO_UDISK     0x00000001
#define     CMD_TEST_UDISK_WRITE_ERROR  0x00000002
typedef struct tagRESULT_TEST_UDISK
{
    int errorCode;
    unsigned long udiskSize;
}RESULT_TEST_UDISK;
typedef struct tagRESULT_TEST_ALARM_IN
{
    int alarmInChnNum;
    int alarmInChnState;//��λ��1:������0:
}RESULT_TEST_ALARM_IN;

typedef struct tagTEST_DEVICE_INFO
{
	DWORD dwSize;
	char  DevType[24];				//�豸����
	DWORD dwServerIp;				//ip��ַ
	DWORD dwDataPort;				//���ݶ˿�
	DWORD dwWebPort;				//web�˿�
	DWORD dwChannelNum;				//ͨ����
	DWORD dwCPUType;				//cpu����
	BYTE  bServerSerial[48];		//�豸���к�
	BYTE  byMACAddr[6];				//�豸MAC��ַ
	DWORD dwAlarmInCount;			//�����������
	DWORD dwAlarmOutCount;			//�����������
	DWORD dwLanguageSupport;		//�豸֧�ֵ�����
	char  cDeviceVersion[32];		//�豸�汾��
	DWORD dwVideoType;				//0:PAL,1:NTSC
}TEST_DEVICE_INFO;
typedef struct tagTEST_NET_PACK_HEAD
{
	DWORD	nFlag;
	DWORD	nCommand;
	DWORD	nChannel;
	DWORD	nErrorCode;
	DWORD	nBufSize;
}TEST_NET_PACK_HEAD;
typedef struct tagTEST_DEFAULT
{
	DWORD	dwSize;
	DWORD	dwLanguage;
	DWORD	dwVideoType;
}TEST_DEFAULT;

void DMS_Log_System_Start(QMAPI_TIME *pTime);
void DMS_Log_System_Run(QMAPI_TIME *pTime);
void DMS_Log_System_Reboot(QMAPI_TIME *pTime);
void DMS_Log_System_Get_Log(int iSocket);

#endif


