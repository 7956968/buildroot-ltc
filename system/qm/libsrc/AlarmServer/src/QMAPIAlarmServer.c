/**
*
**/
#include "QMAPIAlarmServer.h"
#include "QMAPIAlarmpro.h"
#include "tl_common.h"
#include "tlmisc.h"
#include "q3_gpio.h"
#include "motion_controller.h"

int qmapi_alarm_run = 0;
int qmapi_alarm_count = 0;
/*********************************************************************
    Function:   QMAPI_AlarmServer_Init
    Description: ��ʼ����������ģ��
    Calls:
    Called By:
    parameter:
            [in] lpDeafultParam QMAPI_NET_ALARM_SERVER
    Return: ģ����
********************************************************************/
int QMAPI_AlarmServer_Init(void *lpDeafultParam)
{
    //QMAPI_NET_ALARM_SERVER *pstAlarmServer = lpDeafultParam;

#if 0
    if(NULL == lpDeafultParam)
    {
        //TL_Default_MotionDetect_Param();
        return -1;
    }
#endif

    tl_read_Channel_Motion_Detect();
    tl_read_Channel_Probe_Alarm();

    TL_Video_Motion_Alarm_Initial(0);  //Inital Motion Alarm
    DMS_DEV_GPIO_Init_Ext(g_tl_globel_param.TL_Channel_EnhancedColor[0].bEnableBAW);

    return 0;	
}

/*********************************************************************
    Function:   QMAPI_AlarmServer_UnInit
    Description: ����ʼ������ģ��
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: 
********************************************************************/
int QMAPI_AlarmServer_UnInit(int Handle)
{
	return 0;	
}


/*********************************************************************
    Function:   QMAPI_AlarmServer_Start
    Description: ���ñ���ģ�����
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AlarmServer_Start(int Handle)
{
    if (qmapi_alarm_run==1)
        return 0;

	qmapi_alarm_run = 1;
    DMS_DEV_GPIO_Init_Ext(g_tl_globel_param.TL_Channel_EnhancedColor[0].bEnableBAW);

	///TL Video New Alarm Thread
	pthread_t  g_alarmprocThread;
    if (pthread_create(&g_alarmprocThread, NULL, (void *)&TL_Alarm_Thread , NULL) == 0 )
    {
		qmapi_alarm_count ++;
	}

    ///TL Video New Motion Alarm Thread
    pthread_t threadID;
    if (pthread_create(&threadID, NULL, (void *)&TL_Video_Alarm_Thread , NULL) == 0)
    {
		qmapi_alarm_count ++;
	}

    pthread_t tid;
    if (pthread_create(&tid, NULL, (void *)&detectIOThread, NULL) == 0)
    {
		qmapi_alarm_count ++;
	}

    motion_controller_init();
    motion_controller_start();
    
    return 0;	
}


/*********************************************************************
    Function:   QMAPI_AlarmServer_Stop
    Description: ͣ�ñ���ģ�����
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AlarmServer_Stop(int Handle)
{
	qmapi_alarm_run = 0;
	printf("###### %s %d.\n",__FUNCTION__,__LINE__);
	while (qmapi_alarm_count)
	{
		usleep(1000);
	}
	printf("###### %s %d.\n",__FUNCTION__,__LINE__);
	
    motion_controller_stop();
    motion_controller_deinit();

    return 0;
}


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
int QMAPI_AlarmServer_IOCtrl(int Handle, int nCmd, int nChannel, void* Param, int nSize)
{
    int ret = 0;

    /** Ŀǰ��֧�����������֣�֮���������صĻص��ӿ� **/
    if(QMAPI_SYSCFG_GET_MOTIONCFG != nCmd
        || QMAPI_SYSCFG_SET_MOTIONCFG != nCmd
        || QMAPI_SYSCFG_GET_VLOSTCFG != nCmd
        || QMAPI_SYSCFG_SET_VLOSTCFG != nCmd
        || QMAPI_SYSCFG_GET_HIDEALARMCFG != nCmd
        || QMAPI_SYSCFG_SET_HIDEALARMCFG != nCmd
        || QMAPI_SYSCFG_GET_ALARMINCFG != nCmd
        || QMAPI_SYSCFG_SET_ALARMINCFG != nCmd)
    {
        printf("<fun:%s>-<line:%d>, unspport cmd!\n", __FUNCTION__, __LINE__);
        return QMAPI_ERR_UNKNOW_COMMNAD;
    }
    
    ret = QMapi_sys_ioctrl(Handle, nCmd, 0, Param, nSize);

    return ret;	
}



