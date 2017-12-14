
#ifndef _HI_MSESS_RTSP_O_HTTP_H_
#define _HI_MSESS_RTSP_O_HTTP_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_type.h"
#include "cgiinterface.h"

#define RTSP_O_HTTP_LISNSVR_FIRST_MSGBUFF_LEN 1024

typedef enum hiRTSP_O_HTTP_LIVESVR_STATE
{
    RTSP_O_HTTP_LIVESVR_STATE_STOP = 0,         /*׼���׶Σ� ��û����*/        
    RTSP_O_HTTP_LIVESVR_STATE_Running = 1,      /*׼���׶Σ� ��û����*/
    RTSP_O_HTTP_LIVESVR_STATE_BUTT              /*׼���׶Σ� ��û����*/
    
}RTSP_O_HTTP_LIVESVR_STATE;

typedef struct hiRTSP_O_HTTP_LIVE_SVR_S
{
    HI_U32* pu32RTSP_O_HTTPLisnSvrHandle;
    HI_U32* pu32RTSP_O_HTTPSessListHandle;
    RTSP_O_HTTP_LIVESVR_STATE enSvrState;      /*http live server state*/
    HI_U16  u16UserNum;                 /*current http user number,should less than RTSP_O_HTTP_MAX_SESS_NUM*/
    
    
}RTSP_O_HTTP_LIVE_SVR_S;

/*��ʼ��http�Ự����*/
HI_S32 HI_RTSP_O_HTTP_LiveSvr_Init(HI_S32 s32MaxConnNum);

/*ȥ��ʼ��http�Ự����*/
HI_S32 HI_RTSP_O_HTTP_LiveSvr_DeInit();


/*�����Ự��������һ���Ự��Ϣ�ѽ�����ʹpMsgBuffAddrָ����Ϣ�׵�ַ,
 ������pMsgBuffAddrΪnull*/
HI_S32 HI_RTSP_O_HTTP_CreatHttpLiveSession(httpd_conn* hc);

/*����һ���ɼ���ģ��(webserver)�ַ�������
 1 �����Ƿ���http ֱ������
 2 ���������ֱ������
 3 ����ͬ�ķ�ʽ�ֱ�������󷽷�*/
HI_S32 HI_RTSP_O_HTTP_DistribLink(httpd_conn* hc);


#ifndef DEBUG_RTSP_O_HTTP_LIVE
#define DEBUG_RTSP_O_HTTP_LIVE 8
#if (DEBUG_RTSP_LIVE == 0) || !defined(DEBUG_ON)
    #define DEBUG_RTSP_O_HTTP_LIVE_PRINT(pszModeName, u32Level, args ...)
#else
#define DEBUG_RTSP_O_HTTP_LIVE_PRINT(pszModeName, u32Level, args ...)   \
    do  \
    {   \
        if (DEBUG_RTSP_O_HTTP_LIVE >= u32Level)    \
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

