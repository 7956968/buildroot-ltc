#ifndef __QMAPI_SYSNETAPI_H__
#define __QMAPI_SYSNETAPI_H__

#include "QMAPIType.h"
#include "QMAPINetSdk.h"
#include "QMAPIErrno.h"


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

//-------------�ص�������Ϣ------------------
/*********************************************************************************
* �������ܣ����ݴ���ص�
* ���������channel: ͨ����
			streamType:��������0,��������1,������
            data: ���ݽ��ջ�����
            size: ���ݽ��ջ�������С
            flag: 0--���������� 1--����������
            frame_header---֡ͷ��Ϣ
* �����������
* ����ֵ  ����
**********************************************************************************/
typedef int (*CBVideoProc)(int nChannel, int nStreamType, char* pData, unsigned int dwSize, QMAPI_NET_FRAME_HEADER stFrameHeader, DWORD dwUserData);

/*********************************************************************************
* �������ܣ��Խ���Ƶ���ݴ���ص�
* ���������pdata�� ��Ƶ����ָ��
            len�� ��Ƶ���ݴ�С
            param�� ����ָ���ݲ���
* �����������
* ����ֵ  ��
    0 --- �ɹ���<0 --- ʧ��
**********************************************************************************/
typedef int (*CBAudioProc)(int* pData, unsigned int dwSize, int nType, DWORD dwUserData);


/*********************************************************************************
* �������ܣ�������Ϣ����ص�
* ���������nChannel
            nAlarmType���澯����
            nAction���澯״̬
* �����������
* ����ֵ  ��
    0 --- �ɹ���<0 --- ʧ��
**********************************************************************************/
typedef void (*CBAlarmProc)(int nChannel, int nAlarmType, int nAction, void* pParam);


/*********************************************************************************
* �������ܣ��طŴ���ص�
* ���������PlayHandle���طž��
            dwDataType��1ϵͳͷ����;2 ������
            pBuffer��������ݵĻ�����ָ�� 
			dwBufSize: ��������С 
			stFrameHeader:֡ͷ��Ϣ
			dwUser: �û�����
* �����������
* ����ֵ  ��
    0 --- �ɹ���<0 --- ʧ��
**********************************************************************************/
typedef void (*CBPlayProc)(int PlayHandle, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize, QMAPI_NET_FRAME_HEADER stFrameHeader, DWORD dwUser);


/*********************************************************************************
* �������ܣ�͸���������ݴ���ص�
* ���������
					port: ��������,1 232, 2:485
					data --- ͸����������ָ��
                                	size --- ͸���������ݴ�С
* �����������
* ����ֵ  ��
    0 --- �ɹ���<0 --- ʧ��
**********************************************************************************/
typedef int(*CBSerialDataProc)(int nPort, char *pData, unsigned int dwSize);

/*********************************************************************************
* �������ܣ���������״̬�ص�
* ���������
					result:   �������,  -1-- ʧ��, 0---���ڽ���,1----�����ɹ�
					progress: ��������,  0-100 �������Ȱٷֱ�
* �����������
* ����ֵ  ����
**********************************************************************************/
typedef void(*CBUpgradeProc)(int result, int progress);

/*********************************************************************************
* �������ܣ�͸���������ݴ���ص�
* ���������
					port: ��������,1 232, 2:485
					data --- ͸����������ָ��
                                	size --- ͸���������ݴ�С
* �����������
* ����ֵ  ��
    0 --- �ɹ���<0 --- ʧ��
**********************************************************************************/
typedef int(*CBSystemReboot)(void );


typedef struct tagQMAPI_SYSNETAPI
{
	QMAPI_NETPT_TYPE_E			euNetPtType;
	
	int							bMainVideoStarted;
	CBVideoProc		pfMainVideoCallBk;
	int							dwMainVideoUser;

	int							bSecondVideoStarted;
	CBVideoProc		pfSecondVideoCallBk;
	int							dwSecondVideoUser;

	int							bMobileVideoStarted;
	CBVideoProc		pfMobileVideoCallBk;
	int							dwMobileVideoUser;
		
	CBAlarmProc			pfAlarmCallBk;

	CBAudioProc		pfAudioStreamCallBk;
	int							dwAudioUser;
    
	CBSerialDataProc		pfnSerialDataCallBk;
	struct tagQMAPI_SYSNETAPI	*pNext;
}QMAPI_SYSNETAPI, *PQMAPI_SYSNETAPI;




/*************************************************************
* �������ܣ���ģ��
* ���������pt_flag--ƽ̨���
* �����������
* ����ֵ  ��ƽ̨ģ����>0-�ɹ���<0-�������
*************************************************************/
int QMapi_sys_open(int nFlag);

/*************************************************************
* �������ܣ��ر�ģ��
* ���������
* �����������
* ����ֵ  ��>0-�ɹ���<0-�������
*************************************************************/
int QMapi_sys_close(int Handle);

/*************************************************************
* �������ܣ�����ģ��
* ���������
* �����������
* ����ֵ  ��>0-�ɹ���<0-�������
*************************************************************/
int QMapi_sys_start(int Handle, CBSystemReboot CallBack);

int QMapi_sys_stop(int Handle);

/************************************************************
*
*
*
*
*
**************************************************************/
int QMapi_sys_send_alarm(int nChannel, DWORD dwMsgType, QMAPI_SYSTEMTIME *SysTime);

/*************************************************************
* �������ܣ�����ӿ�ģ������
* ���������handle:�ӿ�ģ����
            cmd: ���
            channel: ͨ����
            param�����������
            size: param���ȣ��ر����GET����ʱ���������Ӧ���жϻ������Ƿ��㹻
* ���������param�����������
* ����ֵ  ��>=0-�ɹ���<0-�������
*************************************************************/
int QMapi_sys_ioctrl(int Handle, int nCmd, int nChannel, void* Param, int nSize);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

