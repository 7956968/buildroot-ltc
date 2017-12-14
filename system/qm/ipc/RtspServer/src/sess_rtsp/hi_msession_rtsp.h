
#ifndef _HI_MSESS_RTSP_H_
#define _HI_MSESS_RTSP_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_type.h"
#include "hi_vod.h"
#define RTSP_LISNSVR_FIRST_MSGBUFF_LEN 1024

typedef enum hiRTSP_LIVESVR_STATE
{
    RTSP_LIVESVR_STATE_STOP = 0,         /*׼���׶Σ� ��û����*/        
    RTSP_LIVESVR_STATE_Running = 1,      /*׼���׶Σ� ��û����*/
    RTSP_LIVESVR_STATE_BUTT              /*׼���׶Σ� ��û����*/
    
}RTSP_LIVESVR_STATE;

typedef struct hiRTSP_LIVE_SVR_S
{
    HI_U32* pu32RTSPLisnSvrHandle;
    HI_U32* pu32RTSPSessListHandle;
    RTSP_LIVESVR_STATE enSvrState;      /*RTSP live server state*/
    HI_U16  u16UserNum;                 /*current RTSP user number,should less than RTSP_MAX_SESS_NUM*/
    
    
}RTSP_LIVE_SVR_S;

/*��ʼ��RTSP�Ự����*/
HI_S32 HI_RTSP_LiveSvr_Init(HI_S32 s32MaxConnNum, HI_U16 u16Port);

HI_S32 HI_RTSP_LiveSvr_Init_11(HI_S32 s32MaxConnNum, HI_U16 u16Port,NW_ClientInfo * clientinfo);

HI_S32 HI_RTSP_LiveSvr_DeInit_11();

/*ȥ��ʼ��RTSP�Ự����*/
HI_S32 HI_RTSP_LiveSvr_DeInit();


/*�����Ự��������һ���Ự��Ϣ�ѽ�����ʹpMsgBuffAddrָ����Ϣ�׵�ַ,
 ������pMsgBuffAddrΪnull*/
HI_S32 HI_RTSP_CreatRTSPLiveSession(HI_S32 s32LinkFd, HI_CHAR* pMsgBuffAddr,HI_U32 u32MsgLen, HI_BOOL bIsTurnRelay);

/*����һ���ɼ���ģ��(webserver)�ַ�������
 1 �����Ƿ���RTSP ֱ������
 2 ���������ֱ������
 3 ����ͬ�ķ�ʽ�ֱ�������󷽷�*/
HI_S32 HI_RTSP_DistribLink(HI_S32 s32LinkFd, HI_CHAR* pMsgBuffAddr,HI_U32 u32MsgLen, HI_BOOL bIsTurnRelay);


#ifndef DEBUG_RTSP_LIVE
#define DEBUG_RTSP_LIVE 8
#if (DEBUG_RTSP_LIVE == 0) || !defined(DEBUG_ON)
    #define DEBUG_RTSP_LIVE_PRINT(pszModeName, u32Level, args ...)
#else
#define DEBUG_RTSP_LIVE_PRINT(pszModeName, u32Level, args ...)   \
    do  \
    {   \
        if (DEBUG_RTSP_LIVE >= u32Level)    \
        {   \
            printf(args);   \
        }   \
    }   \
    while(0)
#endif
#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif

