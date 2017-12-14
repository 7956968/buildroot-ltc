/******************************************************************************

  Copyright (C), 2007-, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_vod_session.h
  Version       : Initial Draft
  Author        : W54723
  Created       : 2008/02/15
  Description   : 
  History       :
  1.Date        : 
    Author      : 
    Modification: 
******************************************************************************/
#ifndef __HI_VOD_SESSION_H__
#define __HI_VOD_SESSION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_type.h"
#include "hi_vod.h"
#include "hi_list.h"

/*========================VOD�ڲ����ݽṹ=================*/
#define HI_VOD_MODEL "VOD"
#define HI_VOD_MAX_SUPPORT_CHN 4
#define VOD_DEFAULT_SESS_NUM 32
#define VOD_MAX_SESS_NUM 32
#define VOD_MAX_SESSID_LEN 64       /*vod session length*/

#define HI_VOD_CALLOC calloc
#define HI_VOD_FREE   free

typedef char  VOD_SESSION_ID[VOD_MAX_SESSID_LEN];

typedef enum hiVOD_SVR_STATE
{
    VODSVR_STATE_STOP = 0,         /*׼���׶Σ� ��û����*/        
    VODSVR_STATE_Running = 1,      /*׼���׶Σ� ��û����*/
    VODSVR_STATE_BUTT              /*׼���׶Σ� ��û����*/
    
}VOD_SVR_STATE_E;

/*VOD����session��״̬��*/
typedef enum hiVOD_SESSION_STATE_E
{
    VOD_SESS_STATE_INIT        = 0,
    VOD_SESS_STATE_READY       = 1,
    VOD_SESS_STATE_PLAYED      = 2,
    VOD_SESS_STATE_BUTT  
}VOD_SESSION_STATE_E;

typedef enum hiVOD_SESSION_THREAD_STATE
{
    SESSION_THREAD_STATE_INIT    = 0, /*�ѱ�����*/
    SESSION_THREAD_STATE_RUNNING = 1, /*����������*/
    SESSION_THREAD_STATE_STOP = 2, /*��ֹͣ������*/
    SESSION_THREAD_STATE_BUTT
    
}VOD_SESSION_THREAD_STATE; 

typedef struct hiVOD_SESSION_S
{           
    /*����ά������*/
    List_Head_S vod_sess_list;

    /*�ỰЭ������. '�ỰЭ������+session id'��Ϊsession��keyֵ*/
    VOD_SESS_PROTOCAL_TYPE_E   enSessType;

    /*session id, �����Ӵ���ʱ�򰴻ỰЭ���������*/
    VOD_SESSION_ID        aszSessID;

    /*���û��Ƿ���ͨ����Ȩ�ı�־,0-��δͨ����Ȩ 1-��ͨ����Ȩ
      ����session����setup״̬ʱ�����û���δͨ����Ȩ����Ϊ��
      �û�Ϊ�Ƿ��û�*/
    HI_BOOL       bPassedVarifyFlag;

    /*��Session����Ӧ���ļ���,�㲥ʱ��ʾ�ļ���,ֱ��ʱ��ʾ���ͨ����*/
    //HI_CHAR       au8MediaFile[VOD_MAX_STRING_LENGTH];
    HI_CHAR       au8MediaFile[128];

    /*ý����Դ�е���Ƶ��ʽ*/
    MT_VIDEO_FORMAT_E  enVideoFormat;

    /*ý����Դ�е���ƵƵ��ʽ*/
    MT_AUDIO_FORMAT_E  enAudioFormat;           

    /*�ûỰ����������ý������:a v data*/
    HI_U8      enMediaType;

    /*��session�ĸ�ý��״̬ 0����Ƶ�Ự״̬��1����Ƶ�Ự״̬, 2��Data�����ݻỰ״̬ */
    volatile VOD_SESSION_STATE_E enSessState[VOD_STREAM_MAX];

    /*��session��Ӧ��ý��ַ������handle*/
    HI_U32     u32MbuffHandle; 

    /*��session��Ӧ��ý�崫�������handle*/
    HI_U32     u32MTransHandle;

    /*��session��Ӧ������Ӧ���������handle*/
    HI_U32     u32MAdaptHandle;
    
}VOD_SESSION_S;

typedef struct hiVOD_SVR_S
{
    HI_S32              s32MaxChnNum;                                /*channel number support to vod*/
    HI_S32              s32MaxUserNum;                              /*max connecting user number  */
    HI_S32              s32CurrUserNum;                             /*current connected user number
                                                                      which should be less than Max User Num */
    VOD_SVR_STATE_E    enSvrState;                                  /*vod server state*/
    int        enLiveMode;
    VOD_SESSION_S       *pVODSessList;                                  /*vod session list*/

}VOD_SVR_S;

HI_S32 HI_VOD_SessionGetInfo(HI_CHAR **ppInfoStr,HI_U32* pu32InfoLen);

/*get flag of user passed varify or not */
HI_S32 HI_VOD_SessionGetVarifyFlag(VOD_SESSION_S *pSession,HI_BOOL *bVarifyFlag);

/*get media video format of pointed vod session */
HI_VOID HI_VOD_SessionGetVideoFormat(VOD_SESSION_S *pSession,MT_VIDEO_FORMAT_E* penVideoFormat);

/*set media video format of pointed vod session */
HI_VOID HI_VOD_SessionSetVideoFormat(VOD_SESSION_S *pSession,MT_VIDEO_FORMAT_E enVideoFormat);

/*get media audio format of pointed vod session */
HI_VOID HI_VOD_SessionGetAudioFormat(VOD_SESSION_S *pSession,MT_AUDIO_FORMAT_E* penAudioFormat);

/*set media video format of pointed vod session */
HI_VOID HI_VOD_SessionSetAudioFormat(VOD_SESSION_S *pSession,MT_AUDIO_FORMAT_E enAudioFormat);

/*get media type's state of pointed vod session */
HI_VOID HI_VOD_SessionGetState(VOD_SESSION_S *pSession,HI_U8 u8Type, VOD_SESSION_STATE_E* penState);


/*set media type's state of pointed vod session */
HI_VOID HI_VOD_SessionSetState(VOD_SESSION_S *pSession,HI_U8 u8Type, VOD_SESSION_STATE_E enState);


/*get mbuff handle of pointed vod session */
HI_S32 HI_VOD_SessionGetMbufHdl(VOD_SESSION_S *pSession, HI_U32 *pMbufHandle );
/*set mbuff handle of pointed vod session */
HI_VOID HI_VOD_SessionSetMbufHdl(VOD_SESSION_S *pSession,HI_U32 pMbufHandle);

/*get mtrans task handle of pointed vod session */
HI_S32 HI_VOD_SessionGetMtransHdl(VOD_SESSION_S *pSession, HI_U32 *pMtransHandle );

/*set mtrans task  handle of pointed vod session */
HI_VOID HI_VOD_SessionSetMtransHdl(VOD_SESSION_S *pSession,HI_U32 pMtransHandle);

/*get currect valid connect number*/
HI_S32 HI_VOD_SessionGetConnNum();

/*init session list*/
HI_S32 HI_VOD_SessionListInit(HI_S32 s32TotalConnNum);

/*create session: get a unused node from the free session list*/
HI_S32 HI_VOD_SessionCreat(VOD_SESSION_S **ppSession );

/*init a appointed session*/
HI_VOID HI_VOD_SessionInit(VOD_SESSION_S *pSession, VOD_SETUP_MSG_S *stSetupReqInfo,HI_BOOL bUserPassed);

/*free the resource the session:here just
 need to remove the session from busy list*/
HI_S32 HI_VOD_SessionDestroy(VOD_SESSION_S *pSession);

/*2 get session handle according to protocal type+session id
    return pointer to vod session if success, otherwise return NULL 
*/
HI_S32 HI_VOD_SessionFind(VOD_SESS_PROTOCAL_TYPE_E enSessType,HI_CHAR* pau8SessID,
                          VOD_SESSION_S **ppSession);
                          
/*all busy session destroy: */
HI_VOID HI_VOD_SessionAllDestroy();


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*End of #ifndef __HI_VOD_SESSION_H__*/
