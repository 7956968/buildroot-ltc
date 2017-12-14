/****************************************************************************
*              Copyright 2006 - , Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_rtsp_o_http_session.h
* Description: The rtsp server.
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.0       2008-01-30   W54723     NULL         creat this file.
*****************************************************************************/
#ifndef  __HI_RTSP_O_HTTP_SESSION_H__
#define  __HI_RTSP_O_HTTP_SESSION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_list.h"
#include "hi_mtrans.h"

#define RTSP_O_HTTP_SESS_MODEL  "RTSP_O_HTTP_SESS"

#define RTSP_O_HTTP_MAX_SESS_NUM   16  /*���session�������ݱ���·����ͼ���С�Ĳ�ͬ��
                                  ʵ��֧�ֵ����session������С�ڸ�ֵ */
#define RTSP_O_HTTP_MAX_SESSID_LEN 16  /*sessionid�ŵ���󳤶�*/
#define RTSP_O_HTTP_MAX_VERSION_LEN 128 /*�汾�ŵ���󳤶�*/

#define RTSP_TRACKID_VIDEO 0        /*Setup ��Ϣ�е�track ��Ϣ*/
#define RTSP_TRACKID_AUDIO 1

typedef char  RTSP_O_HTTP_URI[256];         /*URI�������� rtsp://xxx:333/222 */
typedef char  RTSP_O_HTTP_SESSION_ID[RTSP_O_HTTP_MAX_SESSID_LEN];

/*rtsp_o_http��socket�շ�buffer��С*/
#define RTSP_O_HTTP_MAX_PROTOCOL_BUFFER 1024
/*rtsp_o_http����buffer*/
typedef char RTSP_O_HTTP_REQ_BUFFER[RTSP_O_HTTP_MAX_PROTOCOL_BUFFER];
/*RTSP�ظ�buffer*/
typedef RTSP_O_HTTP_REQ_BUFFER RTSP_O_HTTP_RESP_BUFFER;

/*rtsp_o_http�Ự��״̬��*/
typedef enum hiRTSP_O_HTTP_SESSION_STATE
{
    RTSP_O_HTTP_SESSION_STATE_INIT    = 0, /*�ѱ�����*/
    RTSP_O_HTTP_SESSION_STATE_READY   = 1, 
    RTSP_O_HTTP_SESSION_STATE_PLAY = 2, /*����������*/
    RTSP_O_HTTP_SESSION_STATE_STOP = 3,    /*��ֹͣ������*/
    RTSP_O_HTTP_SESSION_STATE_BUTT
    
}RTSP_O_HTTP_SESSION_STATE;

/*rtsp_o_http�Ự�߳�״̬��*/
typedef enum hiRTSP_O_HTTP_LIVESESS_THREAD_STATE
{
    RTSP_O_HTTPSESS_THREAD_STATE_INIT    = 0, /*�ѱ�����*/
    RTSP_O_HTTPSESS_THREAD_STATE_RUNNING = 1, /*����������*/
    RTSP_O_HTTPSESS_THREAD_STATE_STOP = 2, /*��ֹͣ������*/
    RTSP_O_HTTPSESS_THREAD_STATE_BUTT
}RTSP_O_HTTPSESS_THREAD_STATE; 
#define RTSP_O_HTTP_COOKIE_LEN 64
typedef struct hiRTSP_O_HTTP_LIVE_SESSION 
{           
    /*����ά������*/
    List_Head_S rtsp_o_http_sess_list;

    /*��Session����Ӧ�ļ��ͨ����*/
    HI_S32         s32VsChn;

    /*�߳�id,���߳ʸ���rtsp���������ݷ���*/
    pthread_t          s32SessThdId;

    /*�����߳ʵ�״̬*/
    RTSP_O_HTTPSESS_THREAD_STATE enSessThdState;
    
    /*��session����Ӧ��session id, �����Ӵ���ʱ���������*/
    RTSP_O_HTTP_SESSION_ID aszSessID;

    //mhua add
    HI_CHAR SessCookie[RTSP_O_HTTP_COOKIE_LEN];
    HI_SOCKET s32PostConnSock;//��������rtsp�����fd
    HI_BOOL bIsCmdMsgInRecvBuff;//��¼��ǰrecvBuf������s32CmdSock���յ�������
    HI_CHAR au8CmdRecvBuf[RTSP_O_HTTP_MAX_PROTOCOL_BUFFER];
    /*�ͻ��˵�ip��ַ*/
    HI_IP_ADDR     au8CliIP;
    
    /*�ͻ��˵�rtsp_o_http���Ӷ˿�*/
    HI_PORT        s32CliHttpPort;

    /*����ip*/
    HI_IP_ADDR      au8HostIP; 

    /*��session��Ӧ��svr�˻Ựsocket�������Ӵ���ʱ�򱻸�ֵ*/
    HI_SOCKET       s32GetConnSock;

    /*��rtsp_o_http session��״̬*/
    RTSP_O_HTTP_SESSION_STATE enSessState;

    /*�Ƿ�������Ƶ�� ��Ƶ�ı�־*/
    //HI_BOOL    bRequestStreamFlag[VOD_RTP_STREAM_MAX];

    /*��session�У� �û������url�� rtsp://xxxxxx:553/1 */
    RTSP_O_HTTP_URI         au8CliUrl;

    HI_CHAR         au8UserAgent[RTSP_O_HTTP_MAX_VERSION_LEN];

    HI_CHAR         au8SvrVersion[RTSP_O_HTTP_MAX_VERSION_LEN];

    HI_CHAR         au8FileName[8];

    HI_BOOL         bIsFirstMsgHasInRecvBuff;

    /*rtsp���������buffer*/
    RTSP_O_HTTP_REQ_BUFFER  au8RecvBuff;
    HI_U8                   sessMediaType;
    /*rtsp���������buffer*/
    RTSP_O_HTTP_RESP_BUFFER au8SendBuff;

    /*��������buffer�Ƿ�ɷ��ͱ�־*/
    HI_BOOL readyToSend;

    /*ý�����ݴ����Ƿ���interleaved��ʽ�ģ���Э�̴��䷽ʽ
       ʱ��ֵ 0-���ǣ�1-��*/
    HI_BOOL bIsIntlvTrans;

    /*��������handle,ֻ�е�ý��������interleaved��ʽʱ��Ч*/
    /*note:��ý��������interleaved��ʽʱ��ý�������ڻỰ�߳��д���*/
    HI_U32 u32TransHandle;

    /*ý�����ݴ��䴦������interleaved��ʽʱ��Ч*/
    PROC_MEIDA_TRANS    CBonTransItlvMeidaDatas;
    
    /*�����յ�Req*/
    HI_S32 last_recv_req;

    /*����͵�Req*/
    HI_S32 last_send_req;

    /*����͵�Cseq*/
    HI_U32 last_send_seq;
    
    /*�����������Cseq*/
    HI_U32 last_recv_seq;

    HI_U32 pGetConnHandle;
    HI_U32 pPostConnHandle;

}RTSP_O_HTTP_LIVE_SESSION ;


/*get currect valid connect number*/
HI_S32 HI_RTSP_O_HTTP_SessionGetConnNum();

/*init session*/
HI_S32 HI_RTSP_O_HTTP_SessionListInit(HI_S32 s32TotalConnNum);

/*create session: get a unused node from the free session list*/
/*to do : ��η���һ��session ��ָ��*/
HI_S32 HI_RTSP_O_HTTP_SessionCreat(RTSP_O_HTTP_LIVE_SESSION **ppSession );


/*init a appointed session*/
HI_VOID HI_RTSP_O_HTTP_SessionInit(RTSP_O_HTTP_LIVE_SESSION *pSession, HI_SOCKET s32SockFd);

/*free the resource the session possess: close socket,
  and remove the session from busy list*/
HI_VOID HI_RTSP_O_HTTP_SessionClose(RTSP_O_HTTP_LIVE_SESSION *pSession);

/*all busy session destroy: */
HI_VOID HI_RTSP_O_HTTP_SessionAllDestroy();

/*copy the first msg,  which is recived by rtsp_o_http lisnsvr,
  to its corresponding session's recvbuff */
HI_S32 HI_RTSP_O_HTTP_SessionCopyMsg(RTSP_O_HTTP_LIVE_SESSION *pSession,HI_CHAR* pMsgBuffAddr,HI_U32 u32MsgLen);

HI_VOID HI_RTSP_O_HTTP_ClearSendBuff(RTSP_O_HTTP_LIVE_SESSION *pSession);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__HI_RTSP_O_HTTP_SESSION_H__*/

