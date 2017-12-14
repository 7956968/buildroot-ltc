#ifndef __QMAPI_UPGRADE_H__
#define __QMAPI_UPGRADE_H__

#include "QMAPI.h"
#include "QMAPINetSdk.h"
#include "QMAPIErrno.h"


typedef int (*CBUpgradeExit)(void);

/***************************************************************************************/
// ����ģ���ʼ����(������ʼ��,�����֧���������)
//  pFunc [in] ע������ʱģ���˳��������ͷ��ڴ棬
//    ��Ҫ�߶�ע��ģ���˳���������
int QMAPI_Upgrade_Init(CBUpgradeExit pFunc);

/***************************************************************************************/
// ������ʽһ��
//   ���ж�У���ֶ�
//   ������������д����ʱ�ļ��ڣ�
//   ����ƽ̨�ṩ�������ӿ�
int QMAPI_UpgradeFlashReq(int userId, QMAPI_NET_UPGRADE_REQ *lpUpgradeReq);
int QMAPI_UpgradeFlashData(int userId, QMAPI_NET_UPGRADE_DATA *lpUpgradeData);

// ������ʽ����
//   ֱ�Ӵ����ļ����������߳�ֱ�ӵ���ƽ̨�ṩ�������ӿ�
int QMAPI_StartUpgrade(char *pFilePath);

/*
* ���������ص��ӿ�
*/
int QMAPI_PrepareUpgrade(CBUpgradeProc pFunc);

/*
* ��ȡ����ģ�鵱ǰ״̬
*/
int QMAPI_UpgradeFlashGetState(QMAPI_NET_UPGRADE_RESP * pPara);

#endif

