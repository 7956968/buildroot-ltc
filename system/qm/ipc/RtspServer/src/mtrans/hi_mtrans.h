/***********************************************************************************
*              Copyright 2006 - , Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_mtrans.h
* Description:
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.0       2008-02-13   w54723     NULL         Create this file.
***********************************************************************************/

#ifndef _HI_MTRANS_H_
#define _HI_MTRANS_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include "hi_type.h"
#include "hi_mt_def.h"
//#include "hi_adpt_socket.h"
#include "hi_mt_socket.h"
#include "hi_vs_media_comm.h"

typedef int (*PROC_MEIDA_TRANS)(HI_U32,HI_U32);        /*interleavedʱ����ý�����Ĵ�������ָ��*/


/*-------------�ͻ���֧�ֵĸ��ִ���ģʽ������----------*/
typedef struct hiMTRANS_CLI_SUPPORT_UDP_S
{
    /*client�˵������շ��˿�*/
    /*1)UDP��ʽʱΪ�ͻ��˵ȴ�����ý�����ݵĶ˿ں�
      -1ʱ��ʾ��Ч*/
    HI_U32 u32CliMDataPort;
    HI_U32 u32CliAdaptDataPort;

}MTRANS_CLI_SUPPORT_UDP_S;

/*�ݲ�֧��tcp����ģʽ�����ݲ�����*/
typedef struct hiMTRANS_CLI_SUPPORT_TCP_S
{

    
}MTRANS_CLI_SUPPORT_TCP_S;

/*�ݲ�֧��udp interleaved����ģʽ�����ݲ�����*/
typedef struct hiMTRANS_CLI_SUPPORT_UDP_ITLV_S
{

}MTRANS_CLI_SUPPORT_UDP_ITLV_S;

typedef struct hiMTRANS_CLI_SUPPORT_TCP_ITLV_S
{
    /*interleaved��ʽʱ���ݴ���socket(���Ựsocket)*/
    //btlib
    int s32SessSock;

    /*interleaved��ʽʱ��ʾcli->svr��ý�����ݵ�����ͨ����
      -1ʱ��ʾ��Ч*/
    HI_U32 u32ItlvCliMDataId;  

}MTRANS_CLI_SUPPORT_TCP_ITLV_S;

/*�ݲ�֧�ֹ㲥����ģʽ�����ݲ�����*/
typedef struct hiMTRANS_CLI_SUPPORT_BRODCAST_S
{
    

}MTRANS_CLI_SUPPORT_BRODCAST_S;


/*-------------�豸��ѡ�е�cli�˵Ĵ���ģʽ��svr����Ըô���ģʽ������----------*/
typedef struct hiMTRANS_SVR_SUPPORT_UDP_S
{

     /*svr��ý���������ݷ��Ͷ˿�*/
    /*UDP��ʽʱΪsvr�˷���ý�����ݵĶ˿ں�
      -1ʱ��ʾ��Ч*/
    HI_U32 u32SvrMediaSendPort;

    /*���ش��������ĺ���ָ�룬Ŀǰudp����ʱ�ڻỰ�߳��з���ý������*/
    PROC_MEIDA_TRANS pProcMediaTrans;

}MTRANS_SVR_SUPPORT_UDP_S;

/*�ݲ�֧��tcp����ģʽ�����ݲ�����*/
typedef struct hiMTRANS_SVR_SUPPORT_TCP_S
{

    
}MTRANS_SVR_SUPPORT_TCP_S;

/*�ݲ�֧��udp interleaved����ģʽ�����ݲ�����*/
typedef struct hiMTRANS_SVR_SUPPORT_UDP_ITLV_S
{

}MTRANS_SVR_SUPPORT_UDP_ITLV_S;

typedef struct hiMTRANS_SVR_SUPPORT_TCP_ITLV_S
{
     /*svr��ý���������ݷ��Ͷ˿�*/
    /*interleaved��ʽʱ��ʾsvr->cli��ý�����ݵ�����ͨ����
      -1ʱ��ʾ��Ч*/
    HI_U32 u32SvrMediaDataId;  

    /*���ش��������ĺ���ָ�룬tcpǱ��ʽ������ʱ�ڻỰ�߳��з���ý������*/
    PROC_MEIDA_TRANS pProcMediaTrans;
    
}MTRANS_SVR_SUPPORT_TCP_ITLV_S;

/*�ݲ�֧�ֹ㲥����ģʽ�����ݲ�����*/
typedef struct hiMTRANS_SVR_SUPPORT_BRODCAST_S
{
    

}MTRANS_SVR_SUPPORT_BRODCAST_S;

/* ���ضಥ����ģʽ*/
typedef struct hiMTRANS_SVR_SUPPORT_MULTICAST_S
{
    /* ����ಥ�Ѿ��������򷵻ط���˺Ϳͻ��˵Ķ˿ں�*/
    HI_U16    cliMediaPort;
    HI_U16    svrMediaPort;
    HI_U32 u32MediaHandle;    /*ý����Դ���*/
}MTRANS_SVR_SUPPORT_MULTICAST_S;

/*----------------------------------------------------*/
typedef struct hiMTRANS_SEND_CREATE_MSG_S{
    HI_IP_ADDR   au8CliIP;    /*�ִ���ʾ�ͻ��˵�ip��ַ*/

    HI_U32 u32MediaHandle;    /*ý����Դ���*/

    HI_U32 enLiveMode;//����ģʽ
    /*��������ý������*/
    /*0x01��ʾ��������Ƶ��,Ox02��ʾ��������Ƶ�� 0x04��ʾ������data��*/
    HI_U8   u8MeidaType;

    /*ý����Դ,����ֱ��Ϊͨ���ţ����ڵ㲥Ϊý��·��*/
    HI_CHAR au8MediaFile[32];

    HI_U8   resv1;/**��ʱ���������Ƶ֡��*/
    HI_U8  SPS_LEN;
    HI_U8  PPS_LEN;
    HI_U8  SEL_LEN;

    /*�����������ý�����ʲô���Ĵ����ʽ*/
    PACK_TYPE_E enPackType;

    MT_VIDEO_FORMAT_E  enVideoFormat;           /*ý����Դ�е���Ƶ��ʽ*/
    MT_AUDIO_FORMAT_E  enAudioFormat;           /*ý����Դ�е���ƵƵ��ʽ*/

	/*�����ý�����Ͷ�Ӧ��ͬԴ��ʶ
	ע:��MeidaTypeΪ���ý�����ͣ���ʾ���ǵ�ssrc��ͬ*/
	HI_U32 u32Ssrc;							    
	
    /*ý�崫�䷽ʽ:tcp udp or broadcast*/
    MTRANS_MODE_E enMediaTransMode;
    
    /*udp����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_UDPʱ��Ч*/
    MTRANS_CLI_SUPPORT_UDP_S stUdpTransInfo;

    /*tcp����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_TCPʱ��Ч*/
    MTRANS_CLI_SUPPORT_TCP_S stTcpTransInfo;

    /*udp interleaved����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_UDP_ITLVʱ��Ч*/
    MTRANS_CLI_SUPPORT_UDP_ITLV_S stUdpItlvTransInfo;

    /*tcp interleaved����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_TCP_ITLVʱ��Ч*/
    MTRANS_CLI_SUPPORT_TCP_ITLV_S stTcpItlvTransInfo;

    /*�㲥����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_BROADCASTʱ��Ч*/
    MTRANS_CLI_SUPPORT_BRODCAST_S stBroadcastTransInfo;

	HI_U32  AudioSampleRate;
    
}MTRANS_SEND_CREATE_MSG_S;

typedef struct hiMTRANS_ReSEND_CREATE_MSG_S{
    HI_S32 s32ErrCode; /*0 �ɹ���>0 ��Ӧ������*/

    HI_U32 u32TransTaskHandle;    /*���صĴ�����������0��ʾ����ʧ��*/

    /*ý�崫�䷽ʽ:tcp udp or broadcast*/
    MTRANS_MODE_E enMediaTransMode;

    /*udp����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_UDPʱ��Ч*/
    MTRANS_SVR_SUPPORT_UDP_S stUdpTransInfo;

    /*tcp����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_TCPʱ��Ч*/
    MTRANS_SVR_SUPPORT_TCP_S stTcpTransInfo;

    /*udp interleaved����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_UDP_ITLVʱ��Ч*/
    MTRANS_SVR_SUPPORT_UDP_ITLV_S stUdpItlvTransInfo;

    /*tcp interleaved����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_TCP_ITLVʱ��Ч*/
    MTRANS_SVR_SUPPORT_TCP_ITLV_S stTcpItlvTransInfo;

    /*�㲥����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_BROADCASTʱ��Ч*/
    MTRANS_SVR_SUPPORT_BRODCAST_S stBroadcastTransInfo;

    /*�ಥ����ģʽʱ�������ѽ����ಥ���������Ϣ
      ��enMediaTransMode = MTRANS_MODE_MULTICASTʱ��Ч*/
    MTRANS_SVR_SUPPORT_MULTICAST_S stMulticastTransInfo;
}MTRANS_ReSEND_CREATE_MSG_S;

typedef struct hiMTRANS_START_MSG_S{
    HI_U32 u32TransTaskHandle;    /*���ͻ��������ľ��*/
    /*����ʼ�����ý������*/
    /*0x01��ʾ��������Ƶ��,Ox02��ʾ��������Ƶ�� 0x04��ʾ������data��*/
    HI_U8   u8MeidaType;

    HI_U8   rsv1;
    HI_U16  rsv2;
}MTRANS_START_MSG_S;

typedef struct hiMTRANS_ReSTART_MSG_S{
    HI_S32 s32ErrCode; /*0 �ɹ���>0 ��Ӧ������*/
}MTRANS_ReSTART_MSG_S;

typedef struct hiMTRANS_RESUME_MSG_S{
    HI_U32 u32TransTaskHandle;    /*���ͻ��������ľ��*/
    /*����ʼ�����ý������*/
    /*0x01��ʾ��������Ƶ��,Ox02��ʾ��������Ƶ�� 0x04��ʾ������data��*/
    HI_U8   u8MeidaType;

    HI_U8   rsv1;
    HI_U16  rsv2;
}MTRANS_RESUME_MSG_S;

typedef struct hiMTRANS_RESUME_RespMSG_S{
    HI_S32 s32ErrCode; /*0 �ɹ���>0 ��Ӧ������*/
}MTRANS_RESUME_RespMSG_S;


typedef struct hiMTRANS_STOP_MSG_S{
    HI_U32 u32TransTaskHandle;    /*���ͻ��������ľ��*/
    /*����ֹͣ�����ý������*/
    /*0x01��ʾ��ֹͣ������Ƶ��,Ox02��ʾ��ֹͣ������Ƶ�� 0x04��ʾ��ֹͣ����data��*/
    HI_U8   u8MeidaType;
    HI_U8   rsv1;
    HI_U16  rsv2;
}MTRANS_STOP_MSG_S;

typedef struct hiMTRANS_ReSTOP_MSG_S{
    HI_S32 s32ErrCode; /*0 �ɹ���>0 ��Ӧ������*/
}MTRANS_ReSTOP_MSG_S;


typedef struct hiMTRANS_DESTROY_MSG_S{
    HI_U32 u32TransTaskHandle;    /*��������ľ��*/
}MTRANS_DESTROY_MSG_S;

typedef struct hiMTRANS_ReDESTROY_MSG_S{
    HI_S32 s32ErrCode; /*0 �ɹ���>0 ��Ӧ������*/
}MTRANS_ReDESTROY_MSG_S;

typedef struct hiMTRANS_INIT_CONFIG_S
{
    HI_U32 u32MaxTransTaskNum;          /*�����������*/
    HI_U32 u32PackPayloadLen;           /*ý�������ݰ�payload����*/
    HI_PORT u16MinSendPort;           /*udpʱ�豸����С���Ͷ˿�*/
    HI_PORT u16MaxSendPort;           /*udpʱ�豸������Ͷ˿�*/

}MTRANS_INIT_CONFIG_S;

#define RTSP_SEEK_FLAG   9

struct MTRANS_PlayBackInfo{
    int cmd;
    int videoframe;
    unsigned long tick;
    unsigned long VideoTick;
    unsigned long datalen;
    unsigned long timestamp;
    void *pData;
    
};

typedef struct tgSeekResp{
    unsigned long vseq;
    unsigned long aseq;
    unsigned long vtime;
    unsigned long atime;
}SeekResp_S;

#define MTRANS_SEND_IFRAME 'i'


HI_S32 HI_MTRANS_Init(MTRANS_INIT_CONFIG_S* pstruInitCfg);

HI_S32 HI_MTRANS_DeInit();

HI_S32 HI_MTRANS_CreatSendTask(HI_U32* mtransHandle,MTRANS_SEND_CREATE_MSG_S *pstSendInfo,MTRANS_ReSEND_CREATE_MSG_S *pstReSendInfo);

HI_S32 HI_MTRANS_Add2CreatedTask(HI_U32 u32TransTaskHandle,
                                        MTRANS_SEND_CREATE_MSG_S *pstSendInfo,MTRANS_ReSEND_CREATE_MSG_S *pstReSendInfo);

HI_S32 HI_MTRANS_DestroySendTask(MTRANS_DESTROY_MSG_S *pstDestroyInfo,MTRANS_ReDESTROY_MSG_S *pstReDestroyInfo);

HI_S32 HI_MTRANS_StartSendTask(MTRANS_START_MSG_S *pstStartSendInfo, MTRANS_ReSTART_MSG_S *pstReStartInfo);

HI_S32 HI_MTRANS_StopSendTask(MTRANS_STOP_MSG_S *pstStopSendInfo,MTRANS_ReSTOP_MSG_S *pstReStopInfo);

HI_S32 OnProcItlvTrans(HI_U32 pTask,HI_U32 privData);

/*����Ϊ���Դ�ӡ�ӿ�*/
HI_VOID DEBUGPrtMtransCreat(MTRANS_SEND_CREATE_MSG_S *pstSendInfo,MTRANS_ReSEND_CREATE_MSG_S *pstReSendInfo);

HI_VOID DEBUGPrtMtransStart(MTRANS_START_MSG_S *pstStartSendInfo, MTRANS_ReSTART_MSG_S *pstReStartInfo);

HI_VOID DEBUGPrtMtransStop(MTRANS_STOP_MSG_S *pstStopSendInfo,MTRANS_ReSTOP_MSG_S *pstReStopInfo);


HI_VOID DEBUGPrtMtransDestroy(MTRANS_DESTROY_MSG_S *pstDestroyInfo,MTRANS_ReDESTROY_MSG_S *pstReDestroyInfo);

/*��ȡ�׸��������ݵ�ʱ������������׸����ݰ�*/
HI_U32 HI_MTRANS_GetBaseTimeStamp(HI_U32 u32TransTaskHandle,HI_U64 *u64BasePts);

HI_S32 HI_MTRANS_SetMbufHandle(HI_U32 mtransHandle, HI_U32 pMbufHandle);

HI_S32 MTRANS_GetTaskStatusMulticast(HI_U32 u32TransTaskHandle);

HI_S32 MTRANS_StartMulticastSendTask(HI_U32 u32TransTaskHandle);

int MTRANS_StartMulticastStreaming(MT_MulticastInfo_s *pInfo);

int MTRANS_StopMulticastStreaming(MT_MulticastInfo_s *pInfo);

HI_S32 HI_MTRANS_ResumeSendTask(MTRANS_RESUME_MSG_S *pstResumeInfo, MTRANS_RESUME_RespMSG_S *pstResumeResp);

int MTRANS_Register_StunServer(char *pServerAddr, unsigned short port);

int MTRANS_Deregister_StunServer();
int MTRANS_Get_NatAddr(unsigned int TaskHandle,unsigned char stream, unsigned short MediaPort, unsigned short AdaptPort, char *pNatAddr, unsigned short *pMapedPortPair);
int MTRANS_Check_Redirect(unsigned int TaskHandle, int IsRequestVideo, int IsRequestAudio);


#ifndef DEBUG_MTRANS 

    #define DEBUG_MTRANS 8
    #if (DEBUG_MTRANS == 0) || !defined(DEBUG_ON)
        #define DEBUG_MTRANS_PRINT(pszModeName, u32Level, args ...)
    #else
    #define DEBUG_MTRANS_PRINT(pszModeName, u32Level, args ...)   \
        do  \
        {   \
            if (DEBUG_MTRANS >= u32Level)    \
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

