/****************************************************************************
*              Copyright 2006 - , Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_RTSP_session.h
* Description: The rtsp server.
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.0       2008-01-30   W54723     NULL         creat this file.
*****************************************************************************/
#ifndef  __HI_RTSP_SESSION_H__
#define  __HI_RTSP_SESSION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_list.h"
#include "hi_mtrans.h"

#define GT_PRINTF(fmt...) fprintf(stderr,##fmt)

#if 1
#define DEBUG_MSGRTSP(fmt...) do{ \
		GT_PRINTF("[FILE]:%s [Line]:%d:",__FILE__, __LINE__);\
		GT_PRINTF(fmt); \
}while(0)
#else
#define DEBUG_MSG(fmt...) {}
#endif



#define RTSP_SESS_MODEL  "RTSP_SESS"

#define RTSP_MAX_SESS_NUM   32  /*���session�������ݱ���·����ͼ���С�Ĳ�ͬ��
                                  ʵ��֧�ֵ����session������С�ڸ�ֵ */
#define RTSP_MAX_SESSID_LEN 16  /*sessionid�ŵ���󳤶�*/
#define RTSP_MAX_VERSION_LEN 128 /*�汾�ŵ���󳤶�*/

#define RTSP_TRACKID_VIDEO 0        /*Setup ��Ϣ�е�track ��Ϣ*/
#define RTSP_TRACKID_AUDIO 1

typedef char  RTSP_URI[256];         /*URI�������� rtsp://xxx:333/222 */
typedef char  RTSP_SESSION_ID[RTSP_MAX_SESSID_LEN];

/*RTSP��socket�շ�buffer��С*/
#define RTSP_MAX_PROTOCOL_BUFFER 1024*2
/*RTSP����buffer*/
typedef char RTSP_REQ_BUFFER[RTSP_MAX_PROTOCOL_BUFFER];
/*RTSP�ظ�buffer*/
typedef RTSP_REQ_BUFFER RTSP_RESP_BUFFER;

/*RTSP�Ự��״̬��*/
typedef enum hiRTSP_SESSION_STATE
{
    RTSP_SESSION_STATE_INIT    = 0, /*�ѱ�����*/
    RTSP_SESSION_STATE_READY   = 1, 
    RTSP_SESSION_STATE_PLAY = 2, /*����������*/
    RTSP_SESSION_STATE_STOP = 3,    /*��ֹͣ������*/
    RTSP_SESSION_STATE_PAUSE   = 4, 
    RTSP_SESSION_STATE_BUTT
    
}RTSP_SESSION_STATE;

/*RTSP�Ự�߳�״̬��*/
typedef enum hiRTSP_LIVESESS_THREAD_STATE
{
    RTSPSESS_THREAD_STATE_INIT    = 0, /*�ѱ�����*/
    RTSPSESS_THREAD_STATE_RUNNING = 1, /*����������*/
    RTSPSESS_THREAD_STATE_STOP = 2, /*��ֹͣ������*/
    RTSPSESS_THREAD_STATE_BUTT
}RTSPSESS_THREAD_STATE; 

typedef struct hiRTSP_LIVE_SESSION 
{           
    /*����ά������*/
    List_Head_S RTSP_sess_list;

    /*��Session����Ӧ�ļ��ͨ����*/
    HI_S32         s32VsChn;
    HI_CHAR        auFileName[128];

    /*�߳�id,���߳ʸ���rtsp���������ݷ���*/
    HI_S32          s32SessThdId;

    /*�����߳ʵ�״̬*/
    RTSPSESS_THREAD_STATE enSessThdState;
    
    /*��session����Ӧ��session id, �����Ӵ���ʱ���������*/
    RTSP_SESSION_ID aszSessID;

    /*�ͻ��˵�ip��ַ*/
    HI_IP_ADDR     au8CliIP;
    
    /*�ͻ��˵�RTSP���Ӷ˿�*/
    HI_PORT        s32CliRTSPPort;

    /*����ip*/
    HI_IP_ADDR      au8HostIP; 

    /*��session��Ӧ��svr�˻Ựsocket�������Ӵ���ʱ�򱻸�ֵ*/
    HI_SOCKET       s32SessSock;

    /*��RTSP session��״̬*/
    RTSP_SESSION_STATE enSessState;

    /*�Ƿ�������Ƶ�� ��Ƶ�ı�־*/
    HI_BOOL    bRequestStreamFlag[2]; //0:��Ƶ��1:��Ƶ

    /*��session�У� �û������url�� rtsp://xxxxxx:553/1 */
    RTSP_URI         au8CliUrl[2];//0:��Ƶ��1:��Ƶ�����setup��url

    HI_CHAR         au8UserAgent[RTSP_MAX_VERSION_LEN];

    HI_CHAR         au8SvrVersion[RTSP_MAX_VERSION_LEN];

    /*�Ƿ�Ự����ʱ����һ����Ϣ�Ѿ����գ����ѽ��գ���Ự�߳��ȴ���
      ����Ϣ�ٽ�������Ϣ������ֱ�ӽ�����Ϣ���մ���
      note:�����webserver������������������RTSP�㲥�Ự�ĵ�һ����Ϣ*/
    HI_BOOL         bIsFirstMsgHasInRecvBuff;
    /*rtsp���������buffer*/
    RTSP_REQ_BUFFER  au8RecvBuff;
    
    /*rtsp���������buffer*/
    RTSP_RESP_BUFFER au8SendBuff;

    /*��������buffer�Ƿ�ɷ��ͱ�־*/
    HI_BOOL readyToSend;

    /*ý�����ݴ����Ƿ���Э���߳��з��ͣ���Э�̴��䷽ʽ
      ʱ��ֵ 0-���ǣ�1-��*/
    volatile HI_BOOL bIsTransData;

    /*��������handle*/
    HI_U32 u32TransHandle;

    /*ý�����ݴ��䴦������interleaved��ʽ��udp��ʽʱ��Ч*/
    PROC_MEIDA_TRANS    CBonTransMeidaDatas;
    
    /*�����յ�Req*/
    HI_S32 last_recv_req;

    /*����͵�Req*/
    HI_S32 last_send_req;

    /*����͵�Cseq*/
    HI_U32 last_send_seq;
    
    /*�����������Cseq*/
    HI_U32 last_recv_seq;

    HI_PORT remoteRTPPort[2]; //0:��¼��Ƶ�Ķ˿�,1:��¼��Ƶ�Ķ˿�
    
    HI_PORT remoteRTCPPort[2];
    HI_S32 heartTime;//������������heartTime>=3ʱ�������û���յ��ظ�������Ϊ���ӶϿ�

    MTRANS_MODE_E enMediaTransMode; //rtp���䷽ʽ

    HI_BOOL bIsTurnRelay;   //�Ƿ�ͨ��turn��������������
    HI_IP_ADDR au8DestIP;   //ʵ�ʵĿͻ��˵�ַ

    /* �ط���ز��� */
    HI_BOOL bIsPlayback;        // �Ƿ��ǻط�
    HI_S32 s32WaitDoPause;
    HI_S32 last_send_frametype; // 1:I֡
    HI_S32 s32PlayBackType;     // 0:by name  1:by time
    HI_U32 start_offset;        //��ʼʱ��ƫ��,by time ʱ��Ч
    HI_CHAR RealFileName[64];   //��Ӧ���ļ���,by time ʱ��Ч

	/*������֤��ʽ*/
	HI_S32 s32AuthenticateType;  //0 ����֤  1 basic  2 digest
}RTSP_LIVE_SESSION ;


/*get currect valid connect number*/
HI_S32 HI_RTSP_SessionGetConnNum();

/*init session*/
HI_S32 HI_RTSP_SessionListInit(HI_S32 s32TotalConnNum);

/*create session: get a unused node from the free session list*/
/*to do : ��η���һ��session ��ָ��*/
HI_S32 HI_RTSP_SessionCreat(RTSP_LIVE_SESSION **ppSession );


/*init a appointed session*/
HI_VOID HI_RTSP_SessionInit(RTSP_LIVE_SESSION *pSession, HI_SOCKET s32SockFd);

/*free the resource the session possess: close socket,
  and remove the session from busy list*/
HI_VOID HI_RTSP_SessionClose(RTSP_LIVE_SESSION *pSession);

/*all busy session destroy: */
HI_VOID HI_RTSP_SessionAllDestroy();

/*copy the first msg,  which is recived by RTSP lisnsvr,
  to its corresponding session's recvbuff */
HI_S32 HI_RTSP_SessionCopyMsg(RTSP_LIVE_SESSION *pSession,HI_CHAR* pMsgBuffAddr,HI_U32 u32MsgLen);

HI_VOID HI_RTSP_ClearSendBuff(RTSP_LIVE_SESSION *pSession);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__HI_RTSP_SESSION_H__*/

