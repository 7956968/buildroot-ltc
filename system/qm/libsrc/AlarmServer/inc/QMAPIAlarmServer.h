/**
*
**/
#ifndef __QMAPI_ALARMSERVER_H__
#define __QMAPI_ALARMSERVER_H__

#include "QMAPINetSdk.h"
#include "QMAPIErrno.h"

/*********************************************************************
    Function:   QMAPI_AlarmServer_Init
    Description: ��ʼ����������ģ��
    Calls:
    Called By:
    parameter:
            [in] lpDeafultParam QMAPI_NET_ALARM_SERVER
    Return: ģ����
********************************************************************/
int QMAPI_AlarmServer_Init(void *lpDeafultParam);

/*********************************************************************
    Function:   QMAPI_AlarmServer_UnInit
    Description: ����ʼ������ģ��
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AlarmServer_UnInit(int Handle);

/*********************************************************************
    Function:   QMAPI_AlarmServer_Start
    Description: ���ñ���ģ�����
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AlarmServer_Start(int Handle);

/*********************************************************************
    Function:   QMAPI_AlarmServer_Stop
    Description: ͣ�ñ���ģ�����
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AlarmServer_Stop(int Handle);

/*********************************************************************
    Function:   QMAPI_AlarmServer_IOCtrl
    Description: ���ñ�������������
    Calls:
    Called By:
    parameter:
            [in] Handle ���ƾ��
            [in] nCmd ��������
                    ��ЧֵΪ: QMAPI_SYSCFG_GET_MOTIONCFG/QMAPI_SYSCFG_SET_MOTIONCFG/QMAPI_SYSCFG_GET_VLOSTCFG/QMAPI_SYSCFG_SET_VLOSTCFG
                                QMAPI_SYSCFG_GET_HIDEALARMCFG/QMAPI_SYSCFG_SET_HIDEALARMCFG/QMAPI_SYSCFG_GET_ALARMINCFG/QMAPI_SYSCFG_SET_ALARMINCFG
            [in/out] lpInParam QMAPI_NET_CHANNEL_PIC_INFO
            [in/out] nInSize ���ýṹ���С
    Return: QMAPI_SUCCESS/QMAPI_FAILURE/QMAPI_ERR_UNKNOW_COMMNAD
********************************************************************/
int QMAPI_AlarmServer_IOCtrl(int Handle, int nCmd, int nChannel, void* Param, int nSize);






















#endif



