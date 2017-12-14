/****************************************************************************
*              Copyright 2007 - 2011, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_mtrans_internal.h
* Description: mtrans internal struct
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.1       2008-02-18   w54723     NULL         Create this file.
*****************************************************************************/

#ifndef __HI_MTRANS_INTERNAL_H__
#define __HI_MTRANS_INTERNAL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_list.h"
//#include "hi_adpt_socket.h"
/************************************************************************************/
#define MTRANS_SEND  "MTRANS_SEND" 

#define MTRANS_CALLOC calloc
#define MTRANS_FREE free 

/*��������������*/
#define MTRANS_STREAM_VIDEO 0
#define MTRANS_STREAM_AUDIO 1
#define MTRANS_STREAM_DATA  2
#define MTRANS_STREAM_MAX   3

/*interleaved��ʽʱ,server�˵�ý�����ݺ��������ݵ�����ͨ����*/
#define MTRANS_TCPITLV_SVR_MEDIADATA_CHNID 0
#define MTRANS_TCPITLV_SVR_ADAPTDATA_CHNID 1

#define MTRANS_PACKAGE_SIZE 512 /*FU-A�����������ݳ���*/

/*tcp��������ͳ����Ϣ*/
typedef struct hiMTRANS_TCP_TRANS_STAT_S
{

}MTRANS_TCP_TRANS_STAT_S;

/*udp��������ͳ����Ϣ*/
typedef struct hiMTRANS_UDP_TRANS_STAT_S
{

}MTRANS_UDP_TRANS_STAT_S;


/*������ͨ����ͨtcp��ʽ�Ĵ������*/
typedef struct hiMTRANS_TCPTRANS_INFO_S
{

                                
}MTRANS_TCPTRANS_INFO_S;

/*������ͨ��udp�������*/
typedef struct hiMTRANS_UDPTRANS_INFO_S
{
    /*[0] ����Ƶ�˿ڣ� 1����Ƶ�˿�*/
    HI_S32     s32SendThdId;    /*udpʱ�����߳�id,���߳ʸ�����ý����*/
    HI_IP_ADDR au8CliIP[MTRANS_STREAM_MAX];         /*�ͻ��˵Ľ���ip��ַ*/
    HI_U32    cliMediaPort[MTRANS_STREAM_MAX];      /*�ͻ��˵�ý�����ݽ��ն˿�*/
    struct sockaddr_in struCliAddr[MTRANS_STREAM_MAX]; /*�ͻ��˵Ľ��յ�ַ*/ 
    HI_U32    cliAdaptDataPort[MTRANS_STREAM_MAX];     /*�ͻ�������״��ͳ�����ݵĽ��ն˿�*/
    //btlib
    int  as32SendSock[MTRANS_STREAM_MAX];    /*svr�����ݷ���socket*/
    int  as32RecvSock[MTRANS_STREAM_MAX];    /*svr�����ݷ���socket*/
    HI_U32    svrMediaSendPort[MTRANS_STREAM_MAX];  /*svr�˷��Ͷ˿�*/ 
    HI_U32    svrAdaptDataSendPort[MTRANS_STREAM_MAX];  /*svr�˷��Ͷ˿�*/ 
    HI_U32     au32SeqNum[MTRANS_STREAM_MAX];      /*svr�����ݷ������*/
    MTRANS_UDP_TRANS_STAT_S struUDPTransStat;          /*udp��ͳ����Ϣ*/
    /* �ಥ��Ҫ����Ϣ */
    HI_U8 InitFlag; /* 0x1��Ƶ�Ѿ���ʼ��,0x2��Ƶ�Ѿ���ʼ��,0x4 �����Ѿ���ʼ��*/
    HI_U8 ttl;
    HI_U8 chno;
    HI_U8 streamType;//0������,1������
    HI_U8 clientNum;
    HI_U8 threadstatus;//0���ݴ����߳�û��������,1�߳���������
    pthread_mutex_t multicastLock;  //�����ಥ��Ϣ
    pthread_cond_t multicastCond;
}MTRANS_UDPTRANS_INFO_S;

/*������ͨ��tcp interleaved��ʽ�Ĵ������*/
typedef struct hiMTRANS_TCPITLV_TRANS_INFO_S
{
    HI_U32                u32ASendSeqNum;       /*���ݷ������*/
    HI_U32                u32VSendSeqNum;
    //btlib
    int             s32TcpTransSock;     /*svr��tcp����sock,Ƕ��ʽtcp��ʱ��ͬ�ڻỰ sock*/
    
    HI_U32                 au32CliITLMediaDataChnId[MTRANS_STREAM_MAX];/*interleaved��ʽ:cli->svrָʾý������chnId*/
    HI_U32                 au32SvrITLMediaDataChnId[MTRANS_STREAM_MAX];   /*interleaved��ʽ:svr->cliָʾý������chnId*/
    MTRANS_TCP_TRANS_STAT_S  strTCPTransStat; /*tcp��ͳ����Ϣ*/
    
}MTRANS_TCPITLV_TRANS_INFO_S;

/*������ͨ���㲥��ʽ�Ĵ������*/
typedef struct hiMTRANS_BRODCAST_TRANS_S
{
   
    
}MTRANS_BRODCAST_TRANS_S;


/*��������״̬*/
typedef enum hiMTRANS_TASK_STATE_E
{
    TRANS_TASK_STATE_INIT = 0,          /*���������ѳ�ʼ��*/
    TRANS_TASK_STATE_READY,              /*����������*/
    TRANS_TASK_STATE_PLAYING,           /*����������������*/
    TRANS_TASK_STATE_BUTT

}MTRANS_TASK_STATE_E;

typedef struct hiMTRANS_TASK_S
{
    /*����ά������*/
    List_Head_S        mtrans_sendtask_list;   /*ý�崫����������*/
    HI_IP_ADDR         au8CliIP;               /*�ִ���ʾ�ͻ��˵�ip��ַ*/
    HI_U32             u32MbuffHandle;         /*ý����Դ���*/
    MT_VIDEO_FORMAT_E  enVideoFormat;           /*ý����Դ�е���Ƶ��ʽ*/
    MT_AUDIO_FORMAT_E  enAudioFormat;           /*ý����Դ�е���ƵƵ��ʽ*/
    MTRANS_MODE_E      enTransMode;                 /*ý�崫��ģʽ*/
    MTRANS_TCPTRANS_INFO_S struTcpTransInfo;  /*udp��ʽʱ�Ĵ����������enTransMode=TRANS_TYPE_UDP��Ч*/
    MTRANS_UDPTRANS_INFO_S struUdpTransInfo;  /*tcp��ʽʱ�Ĵ����������enTransMode=TRANS_TYPE_TDP��Ч*/
    MTRANS_TCPITLV_TRANS_INFO_S struTcpItlvTransInfo; /*tcp interleaved��ʽʱ�Ĵ����������enTransMode=TRANS_MODE_TCP_ITLV��Ч*/
    MTRANS_BRODCAST_TRANS_S struBrodTransInfo; /*�㲥��ʽʱ�Ĵ����������enTransMode=TRANS_TYPE_BROADCAST��Ч*/
    volatile MTRANS_TASK_STATE_E enTaskState[MTRANS_STREAM_MAX];        /*��������״̬��0����Ƶ����״̬��1����Ƶ����״̬, 2��Data�����ݴ���״̬ */
    PACK_TYPE_E         aenPackType[MTRANS_STREAM_MAX];      /*ý�����ݵĴ����ʽ*/                                                            
	HI_U32        au32Ssrc[MTRANS_STREAM_MAX];      /*ý�����ݵĴ��ssrc ��ʾ*/  
	HI_U32        u32VideoPacketIndex;      //�ѷ��͵���Ƶ���ܸ���
	HI_U32        u32FrameIndex;           //�ѷ��͵���Ƶ֡��֡��
	HI_U32        u32FramePacketIndex;     //��ǰ֡�ѷ��Ͱ��ĸ���
    HI_U32        u32PackDataLen;         //��ǰpu8PackBuff�����е����ݳ���
	HI_CHAR*             pu8PackBuff;           /*FU-A�����buff*/

    HI_U32     videoFrame;//֡��
    
    HI_U32        liveMode;//����ģʽ
    int SPS_LEN;
    int PPS_LEN; 
    int SEL_LEN;
	HI_U32		audioSampleRate; //������
}MTRANS_TASK_S;

typedef enum hiMTRANS_SVR_STATE
{
    MTRANSSVR_STATE_STOP = 0,         /*׼���׶Σ� ��û����*/        
    MTRANSSVR_STATE_Running = 1,      /*׼���׶Σ� ��û����*/
    MTRANSSVR_STATE_BUTT              /*׼���׶Σ� ��û����*/
    
}MTRANS_SVR_STATE_E;

typedef struct hiMTRANS_ATTR_S
{
    HI_U32  u32MaxTransTaskNum;          /*�����������*/
    HI_PORT u16MinSendPort;           /*udpʱ�豸����С���Ͷ˿�*/
    HI_PORT u16MaxSendPort;           /*udpʱ�豸������Ͷ˿�*/
    HI_U32 u32PackPayloadLen;           /*ý�������ݰ�payload����*/
    HI_U32* pTransTaskListHead;         /*ý�崫������������׵�ַ*/
    MTRANS_SVR_STATE_E    enSvrState;   /*����server state*/
    pthread_mutex_t  MutexGetPort; 
}MTRANS_ATTR_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
