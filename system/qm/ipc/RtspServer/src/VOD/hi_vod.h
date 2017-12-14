/****************************************************************************
*              Copyright 2006 - 2006, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_vod.h
* Description: 
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.0       2008-01-31   w54723     NULL         Create this file.
*****************************************************************************/

#ifndef  __HI_VOD_H__
#define  __HI_VOD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "hi_mt_def.h"
#include "hi_mbuf_def.h"
#include "hi_mt_socket.h"
#include "hi_mtrans.h"
#include "hi_vs_media_comm.h"
//#include "hi_vs_enc.h"

/*vodģ�����Ϣ��msg type����*/
#define MSG_VOD_DESCRIBE  0x00050000
#define MSG_VOD_SETUP     0x00050001
#define MSG_VOD_PLAY      0x00050002
#define MSG_VOD_PAUSE     0x00050003
#define MSG_VOD_TEARDOWN  0x00050004

#define VOD_MAX_STRING_LENGTH  32          //���ִ���󳤶�
//#define VOD_MAX_VIDEO_DATAINFO_LEN  64      //sps,pps base64��������󳤶�
//panhn   ����TI��Ŀ
#define VOD_MAX_VIDEO_DATAINFO_LEN  256      //sps,pps base64��������󳤶�
#define VOD_MAX_VERSION_LEN  64          //sps,pps base64��������󳤶�

#define VOD_MAX_TRANSTYPE_NUM  4           //���䷽ʽ��������

#define VOD_STREAM_VIDEO 0
#define VOD_STREAM_AUDIO 1
#define VOD_STREAM_DATA  2
#define VOD_STREAM_MAX   3

/*-------------�ͻ���֧�ֵĸ��ִ���ģʽ������----------*/
typedef struct hiVOD_CLI_SUPPORT_UDP_S
{
    /*client�˵������շ��˿�*/
    /*1)UDP��ʽʱΪ�ͻ��˵ȴ�����ý�����ݵĶ˿ں�
      -1ʱ��ʾ��Ч*/
    HI_U32 u32CliMediaRecvPort;  

    /*client�˵����ذ����ն˿�*/
    /*1)UDP��ʽʱΪ�ͻ��˵ȴ��������ذ��Ķ˿ں�
      -1ʱ��ʾ��Ч*/
    HI_U32 u32CliAdaptRecvPort;

}VOD_CLI_SUPPORT_UDP_S;

/*�ݲ�֧��tcp����ģʽ�����ݲ�����*/
typedef struct hiVOD_CLI_SUPPORT_TCP_S
{

    
}VOD_CLI_SUPPORT_TCP_S;

/*�ݲ�֧��udp interleaved����ģʽ�����ݲ�����*/
typedef struct hiVOD_CLI_SUPPORT_UDP_ITLV_S
{

}VOD_CLI_SUPPORT_UDP_ITLV_S;

typedef struct hiVOD_CLI_SUPPORT_TCP_ITLV_S
{
    /*interleaved��ʽʱ���ݴ���socket(���Ựsocket)*/
    HI_SOCKET s32SessSock;

    /*interleaved��ʽʱ��ʾcli->svr��ý�����ݵ�����ͨ����
      -1ʱ��ʾ��Ч*/
    HI_U32 u32ItlvCliMediaChnId;  

    /*interleaved��ʽʱ��ʾcli->svr�����ذ�������ͨ����
      -1ʱ��ʾ��Ч*/
    HI_U32 u32ItlvCliAdaptChnId;

}VOD_CLI_SUPPORT_TCP_ITLV_S;

/*�ݲ�֧�ֹ㲥����ģʽ�����ݲ�����*/
typedef struct hiVOD_CLI_SUPPORT_BRODCAST_S
{
    

}VOD_CLI_SUPPORT_BRODCAST_S;


/*-------------�豸��ѡ�е�cli�˵Ĵ���ģʽ��svr����Ըô���ģʽ������----------*/
typedef struct hiVOD_SVR_SUPPORT_UDP_S
{

     /*svr��ȷ�ϵ�client�˵������շ��˿�*/
    /*UDP��ʽʱΪ�ͻ��˵ȴ�����ý�����ݵĶ˿ں�
      -1ʱ��ʾ��Ч*/
     HI_U32 u32CliMediaRecvPort;   

    /*svr��ȷ�ϵ�client�˵����ذ����ն˿�*/
    /*UDP��ʽʱΪ�ͻ��˵ȴ��������ذ��Ķ˿ں�
      -1ʱ��ʾ��Ч*/
    HI_U32 u32CliAdaptRecvPort;

     /*svr��ý���������ݷ��Ͷ˿�*/
    /*UDP��ʽʱΪsvr�˷���ý�����ݵĶ˿ں�
      -1ʱ��ʾ��Ч*/
    HI_U32 u32SvrMediaSendPort;  

    /*svr�����ذ����Ͷ˿�*/
    /*UDP��ʽʱΪsvr�˷������ذ��Ķ˿ں�
      -1ʱ��ʾ��Ч*/
    HI_U32 u32SvrAdaptSendPort;

    /*���ش��������ĺ���ָ�룬tcpǱ��ʽ������ʱ�ڻỰ�߳��з���ý������*/
    PROC_MEIDA_TRANS pProcMediaTrans;

    /*������Ӧ��ý�崫����������tcpǱ��ʽ������ʱ�ڻỰ�߳��з���ý������ʱ
      ָ����Ӧ�Ĵ�������*/
    HI_U32 u32TransHandle;

}VOD_SVR_SUPPORT_UDP_S;

/*�ݲ�֧��tcp����ģʽ�����ݲ�����*/
typedef struct hiVOD_SVR_SUPPORT_TCP_S
{

    
}VOD_SVR_SUPPORT_TCP_S;

/*�ݲ�֧��udp interleaved����ģʽ�����ݲ�����*/
typedef struct hiVOD_SVR_SUPPORT_UDP_ITLV_S
{

}VOD_SVR_SUPPORT_UDP_ITLV_S;

typedef struct hiVOD_SVR_SUPPORT_TCP_ITLV_S
{
     /*svr��ý���������ݷ��Ͷ˿�*/
    /*interleaved��ʽʱ��ʾsvr->cli��ý�����ݵ�����ͨ����
      -1ʱ��ʾ��Ч*/
    HI_U32 u32SvrMediaChnId;  

    /*svr�����ذ����Ͷ˿�*/
    /*interleaved��ʽʱ��ʾsvr->cli�����ذ�������ͨ����
      -1ʱ��ʾ��Ч*/
    HI_U32 u32SvrAdaptChnId;

    /*���ش��������ĺ���ָ�룬tcpǱ��ʽ������ʱ�ڻỰ�߳��з���ý������*/
    PROC_MEIDA_TRANS pProcMediaTrans;

    /*������Ӧ��ý�崫����������tcpǱ��ʽ������ʱ�ڻỰ�߳��з���ý������ʱ
      ָ����Ӧ�Ĵ�������*/
    HI_U32 u32TransHandle;
    
}VOD_SVR_SUPPORT_TCP_ITLV_S;

/*�ݲ�֧�ֹ㲥����ģʽ�����ݲ�����*/
typedef struct hiVOD_SVR_SUPPORT_BRODCAST_S
{
    

}VOD_SVR_SUPPORT_BRODCAST_S;


/*ý��ỰЭ������*/
typedef enum hiVOD_SESS_PROTOCAL_TYPE_E
{
    SESS_PROTOCAL_TYPE_RTSP = 0,               /*rtsp�ỰЭ��*/
    SESS_PROTOCAL_TYPE_HTTP = 1,               /*http�ỰЭ��*/
    SESS_PROTOCAL_TYPE_SIP  = 2,               /*sip�ỰЭ��*/
    SESS_PROTOCAL_TYPE_OWSP = 3,
    SESS_PROTOCAL_TYPE_USER_DEFIN1 = 101,       /*�û��Զ���ỰЭ��1*/
    SESS_PROTOCAL_TYPE_USER_DEFIN2               /*�û��Զ���ỰЭ��2*/
}VOD_SESS_PROTOCAL_TYPE_E;
/*----------------------------------------------------*/
/*---------------------------------------------------------*/

typedef struct hiVOD_CLI_SUPPORT_TRANS_INFO_S{

    /*�ô�������ṹ�Ƿ���Ч 0-��Ч��1-��Ч*/
    HI_BOOL bValidFlag;

    /*�����������ý�����ʲô���Ĵ����ʽ*/
    PACK_TYPE_E enPackType;
    
    /*������ý����ú��ִ���ģʽ:tcp udp or broadcast*/
    MTRANS_MODE_E enMediaTransMode;

    /*udp����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_UDPʱ��Ч*/
    VOD_CLI_SUPPORT_UDP_S stUdpTransInfo;

    /*tcp����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_TCPʱ��Ч*/
    VOD_CLI_SUPPORT_TCP_S stTcpTransInfo;

    /*udp interleaved����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_UDP_ITLVʱ��Ч*/
    VOD_CLI_SUPPORT_UDP_ITLV_S stUdpItlvTransInfo;

    /*tcp interleaved����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_TCP_ITLVʱ��Ч*/
    VOD_CLI_SUPPORT_TCP_ITLV_S stTcpItlvTransInfo;

    /*�㲥����ģʽʱ�����������Ϣ
      ��enMediaTransMode = MTRANS_MODE_BROADCASTʱ��Ч*/
    VOD_CLI_SUPPORT_BRODCAST_S stBroadcastTransInfo;
 
}VOD_CLI_SUPPORT_TRANS_INFO_S;

typedef struct hiVOD_SVR_SUPPORT_TRANS_INFO_S{
     
    /*svr��ѡ�е�ý�崫��ģʽ*/
    MTRANS_MODE_E enMediaTransMode;

    /*udp����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_UDPʱ��Ч*/
    VOD_SVR_SUPPORT_UDP_S stUdpTransInfo;

    /*tcp����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_TCPʱ��Ч*/
    VOD_SVR_SUPPORT_TCP_S stTcpTransInfo;

    /*udp interleaved����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_UDP_ITLVʱ��Ч*/
    VOD_SVR_SUPPORT_UDP_ITLV_S stUdpItlvTransInfo;

    /*tcp interleaved����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_TCP_ITLVʱ��Ч*/
    VOD_SVR_SUPPORT_TCP_ITLV_S stTcpItlvTransInfo;

    /*�㲥����ģʽʱ��svr�˴��������Ϣ
      ��enMediaTransMode = MTRANS_MODE_BROADCASTʱ��Ч*/
    VOD_SVR_SUPPORT_BRODCAST_S stBroadcastTransInfo;

}VOD_SVR_SUPPORT_TRANS_INFO_S;

 typedef struct hiVOD_DESCRIBE_MSG_S{
    /*ý����Դ,����ֱ��Ϊͨ���ţ����ڵ㲥Ϊý��·��*/
    //HI_CHAR au8MediaFile[VOD_MAX_STRING_LENGTH];           
    HI_BOOL bLive;                  //�Ƿ�ʵʱ����
    HI_S32 s32PlayBackType;    //bLive=0ʱ��Ч
    HI_CHAR au8MediaFile[128]; 
    HI_CHAR au8UserName[VOD_MAX_STRING_LENGTH];            //�û���
    HI_CHAR au8PassWord[VOD_MAX_STRING_LENGTH];            //����
    HI_CHAR au8ClientVersion[VOD_MAX_VERSION_LEN];      //�ͻ��˰汾��Ϣ  
}VOD_DESCRIBE_MSG_S;

typedef struct hiVOD_ReDESCRIBE_MSG_S{
    HI_S32 s32ErrCode; //0 �ɹ���>0 ��Ӧ������
    HI_U32  u32MediaDurTime;          //ý��ʱ������λ�롣����ֱ��ͨ��ʱ��Ϊ0
    MT_AUDIO_FORMAT_E enAudioType;    //��Ƶ��ʽ
    HI_U32  u32AudioSampleRate;       //��Ƶ�����ʣ���λ����
    HI_U32  u32AudioChannelNum;       // 1������ 2˫����
    MT_VIDEO_FORMAT_E enVideoType;    //��Ƶ��ʽ
    HI_U32  u32VideoPicWidth;              //��Ƶ��
    HI_U32  u32VideoPicHeight;             //��Ƶ��
    HI_U32  u32VideoSampleRate;       //��Ƶ������
    HI_U32  u32Framerate;
    HI_U32  u32Bitrate;
    unsigned long u32TotalTime;            //�ط��ļ�����
    HI_CHAR au8VideoDataInfo[VOD_MAX_VIDEO_DATAINFO_LEN]; /*��Ƶ������Ϣ,sps,pps��base64����ַ���*/
    int SPS_LEN;
    int PPS_LEN;
    int SEL_LEN;
    HI_U32  u32DataInfoLen;
    HI_CHAR au8BoardVersion[VOD_MAX_VERSION_LEN];      //�豸�汾��Ϣ 
    unsigned char profile_level_id[8];
    char RealFileName[64];//�ط�by time ��ʽʱ��Ч
    HI_U32 start_offset;
}VOD_ReDESCRIBE_MSG_S;

typedef struct hiVOD_SETUP_MSG_S{
    VOD_SESS_PROTOCAL_TYPE_E enSessType;  //�ỰЭ������
    HI_CHAR aszSessID[VOD_MAX_STRING_LENGTH];  //�Ựid����ͬ�ỰЭ��ά�����ԻỰid
    HI_IP_ADDR au8ClientIp; //�ͻ��˵�ַ
    /*ý����Դ,����ֱ��Ϊͨ���ţ����ڵ㲥Ϊý��·��*/
    //HI_CHAR au8MediaFile[VOD_MAX_STRING_LENGTH];
    HI_CHAR au8MediaFile[128];
    /*��������ý������*/
    /*0x01��ʾ��������Ƶ��,Ox02��ʾ��������Ƶ�� 0x04��ʾ������data��*/
    HI_U8   u8SetupMeidaType;
    HI_U8   resv1;
    HI_U16  resv2;
    /*�����ý�����Ͷ�Ӧ��ͬԴ��ʶ
	ע:��MeidaTypeΪ���ý�����ͣ���ʾ���ǵ�ssrc��ͬ*/
	HI_U32 u32Ssrc;	
    VOD_CLI_SUPPORT_TRANS_INFO_S astCliSupptTransList[VOD_MAX_TRANSTYPE_NUM];   //�ͻ���֧�ֵĴ��䷽ʽ
    HI_CHAR au8UserName[VOD_MAX_STRING_LENGTH];            //�û���
    HI_CHAR au8PassWord[VOD_MAX_STRING_LENGTH];            //����
    HI_CHAR au8ClientVersion[VOD_MAX_VERSION_LEN];      //�ͻ��˰汾��Ϣ
    HI_BOOL bIsPlayBack;
    HI_S32 s32PlayBackType;
}VOD_SETUP_MSG_S;

typedef struct hiVOD_ReSETUP_MSG_S{
    HI_S32 s32ErrCode; //0 �ɹ���>0 ��Ӧ������    
    /*�ѽ��ܽ�������ĵ�ý������*/
    /*0x01��ʾ��������Ƶ��,Ox02��ʾ��������Ƶ�� 0x04��ʾ������data��*/
    HI_U8   u8SetupMeidaType;
    HI_U8   resv1;
    HI_U16  resv2;

    /*�����������ý�����ʲô���Ĵ����ʽ*/
    PACK_TYPE_E enPackType;
    
    VOD_SVR_SUPPORT_TRANS_INFO_S stTransInfo;  //���ѡ���Ŀͻ��˴��䷽ʽ��svr�˴�����Ϣ
    
    HI_CHAR au8BoardVersion[VOD_MAX_VERSION_LEN];      //�豸�汾��Ϣ 
}VOD_ReSETUP_MSG_S;

typedef struct hiVOD_PLAY_MSG_S{
    VOD_SESS_PROTOCAL_TYPE_E enSessType;  //�ỰЭ������
    HI_CHAR aszSessID[VOD_MAX_STRING_LENGTH];  //�Ựid����ͬ�ỰЭ��ά�����ԻỰid
    HI_U32  u32StartTime;  //������ʼʱ��(�����ý���ļ�����ʼƫ��)����λ����,ֱ��ʱ���ֶ���Ч
    HI_U32  u32Duration;      //����ʱ������λ����,ֱ��ʱ���ֶ���Ч
    /*���󲥷�ý������*/
    /*0x01��ʾ��������Ƶ��,Ox02��ʾ��������Ƶ�� 0x04��ʾ������data��*/
    HI_U8   u8PlayMediaType;  
    HI_U8   resv1;
    HI_U16  resv2;
}VOD_PLAY_MSG_S;

typedef struct hiVOD_RePLAY_MSG_S{
    HI_U64 video_pts;
	HI_U64 audio_pts;
    HI_S32 s32ErrCode; //0 �ɹ���>0 ��Ӧ������
}VOD_RePLAY_MSG_S;

typedef struct hiVOD_PAUSE_MSG_S{
    VOD_SESS_PROTOCAL_TYPE_E enSessType;  //�ỰЭ������
    HI_CHAR aszSessID[VOD_MAX_STRING_LENGTH];  //�Ựid����ͬ�ỰЭ��ά�����ԻỰid
    HI_U32 u32PauseTime;  //������ͣʱ��(�����ý���ļ�����ʼƫ��)����λ����,ֱ��ʱ���ֶ���Ч
    /*���󲥷�ý������*/
    /*0x01��ʾ��������ͣ��Ƶ��,Ox02��ʾ��������ͣ��Ƶ�� 0x04��ʾ����ͣdata��*/
    HI_U8 u8PauseMediasType;  //������ͣý������
    HI_U8   resv1;
    HI_U16  resv2;
    
}VOD_PAUSE_MSG_S;

typedef struct hiVOD_RePAUSE_MSG_S{
    HI_S32 s32ErrCode; //0 �ɹ���>0 ��Ӧ������
}VOD_RePAUSE_MSG_S;

typedef struct tagVOD_RESUME_MSG_S{
    VOD_SESS_PROTOCAL_TYPE_E enSessType;  //�ỰЭ������
    HI_CHAR aszSessID[VOD_MAX_STRING_LENGTH];  //�Ựid����ͬ�ỰЭ��ά�����ԻỰid
    HI_U8 u8MediasType;
    HI_U8   resv1;
    HI_U16  resv2;
}VOD_RESUME_MSG_S;

typedef struct hiVOD_RESUME_RespMSG_S{
    HI_S32 s32ErrCode; //0 �ɹ���>0 ��Ӧ������
}VOD_RESUME_RespMSG_S;


typedef struct hiVOD_TEAWDOWN_MSG_S{
    VOD_SESS_PROTOCAL_TYPE_E enSessType;  //�ỰЭ������
    MTRANS_MODE_E      enTransMode;                 /*ý�崫��ģʽ*/
    HI_CHAR aszSessID[VOD_MAX_STRING_LENGTH];  //�Ựid����ͬ�ỰЭ��ά�����ԻỰid        
    HI_U32 u32Reason;  //�ر����ӵ�ԭ��
}VOD_TEAWDOWN_MSG_S;

typedef struct hiVOD_ReTEAWDOWN_MSG_S{
    HI_S32 s32ErrCode; //0 �ɹ���>0 ��Ӧ������
}VOD_ReTEAWDOWN_MSG_S;

#define VOD_DEFAULT_MAX_CHNNUM 16

typedef struct hiVOD_GET_BASEPTS_MSG_S{
    VOD_SESS_PROTOCAL_TYPE_E enSessType;  //�ỰЭ������
    HI_CHAR aszSessID[VOD_MAX_STRING_LENGTH];  //�Ựid����ͬ�ỰЭ��ά�����ԻỰid        
}VOD_GET_BASEPTS_MSG_S;

typedef struct hiVOD_ReGET_BASEPTS_MSG_S{
    HI_S32 s32ErrCode; //0 �ɹ���>0 ��Ӧ������
    HI_U64 u64BaseTimeStamp; //��׼ʱ���
}VOD_ReGET_BASEPTS_MSG_S;

typedef struct hiVOD_CONFIG_S
{
    /*mtrans�������:udp�Ķ˿ڷ�Χ*/
    HI_U16              u16UdpSendPortMin;
    HI_U16              u16UdpSendPortMax;
    /*ý�������ݰ�payload����*/
    HI_U32              u32PackPayloadLen;           

    /*mbuf�������:udp�Ķ˿ڷ�Χ*/
    //#define MT_MAX_CHN_CNT 16
    int enLiveMode;/**�㲥ģʽ*/
    HI_S32              maxUserNum;//���֧�ֵ��û���
    HI_S32              maxFrameLen;//���֡���ȣ�
    HI_S32              s32SupportChnNum;
    MBUF_CHENNEL_INFO_S stMbufConfig[VS_MAX_STREAM_CNT];
}VOD_CONFIG_S;


/*��ȡ�׸��������ݵ�ʱ������������׸����ݰ��ýӿڻ�����,ֱ���ɹ����ڻ�׼ʱ����������*/
HI_U32 HI_VOD_GetBaseTimeStamp(VOD_GET_BASEPTS_MSG_S *stVodGetPtsReqInfo,
                                            VOD_ReGET_BASEPTS_MSG_S 
                                            *stVodGetPtsRespInfo);

HI_S32 HI_VOD_Init(VOD_CONFIG_S* pstVodConfig);

HI_S32 HI_VOD_DeInit();

HI_S32 HI_VOD_DESCRIBE(VOD_DESCRIBE_MSG_S *stDesReqInfo,VOD_ReDESCRIBE_MSG_S *stDesRespInfo);

HI_S32 HI_VOD_SetUp(VOD_SETUP_MSG_S *stVodSetupReqInfo, VOD_ReSETUP_MSG_S *stVodSetupRespInfo);

//HI_S32 HI_VOD_SetUp_Add(VOD_SETUP_MSG_S *stVodSetupReqInfo, VOD_ReSETUP_MSG_S *stVodSetupRespInfo);

HI_S32 HI_VOD_Play(VOD_PLAY_MSG_S *stVodPlayReqInfo, VOD_RePLAY_MSG_S *stVodPlayRespInfo);

HI_S32 HI_VOD_Pause(VOD_PAUSE_MSG_S*stVodPauseReqInfo, VOD_RePAUSE_MSG_S *stVodPauseRespInfo);

HI_S32 HI_VOD_Resume(VOD_RESUME_MSG_S*stVodResumeReqInfo, VOD_RESUME_RespMSG_S *stVodResumeRespInfo);


HI_S32 HI_VOD_Teardown(VOD_TEAWDOWN_MSG_S *stVodCloseReqInfo, VOD_ReTEAWDOWN_MSG_S *stVodCloseRespInfo);
#if 0
HI_S32 HI_VOD_Run(HI_S32 s32Chn, ENC_STREAM_S* pAvenc_Stream);

HI_S32 HI_VOD_DATA(HI_S32 s32Chn,HI_CHAR * pszAlarmInfo, HI_S32 s32Len);
#endif
HI_S32 HI_VOD_GetVersion(HI_CHAR *pszSvrVersion, HI_U32 u32VersionLen);
/*debug ���Դ�ӡ�ӿ�*/
HI_VOID DEBUGPrtVODDes(VOD_DESCRIBE_MSG_S *stDesReqInfo,VOD_ReDESCRIBE_MSG_S *stDesRespInfo);

HI_VOID DEBUGPrtVODSetup(VOD_SETUP_MSG_S *stVodSetupReqInfo, VOD_ReSETUP_MSG_S *stVodSetupRespInfo);

HI_VOID DEBUGPrtVODPlay(VOD_PLAY_MSG_S * stVodPlayReqInfo, VOD_RePLAY_MSG_S * stVodPlayRespInfo);

HI_VOID DEBUGPrtVODPause(VOD_PAUSE_MSG_S*stVodPauseReqInfo, VOD_RePAUSE_MSG_S *stVodPauseRespInfo);

HI_VOID DEBUGPrtVODTeawdown(VOD_TEAWDOWN_MSG_S *stVodCloseReqInfo, VOD_ReTEAWDOWN_MSG_S *stVodCloseRespInfo);

HI_BOOL HI_VOD_IsRunning();



typedef void (*NW_LogoffFunc)(int id);

typedef struct NW_ClientInfotag
{
	int 				DmsHandle;
	int 				ClientSocket;
	struct sockaddr_in	ClientAddr;
	int					id;
	NW_LogoffFunc 		OnLogoff; //�ڿͻ����˳�ʱ�����������
}NW_ClientInfo;


#ifndef DEBUG_VOD
#define DEBUG_VOD 8
#if (DEBUG_VOD == 0) || !defined(DEBUG_ON)
    #define DEBUG_VOD_PRINT(pszModeName, u32Level, args ...)
#else
#define DEBUG_VOD_PRINT(pszModeName, u32Level, args ...)   \
    do  \
    {   \
        if (DEBUG_VOD >= u32Level)    \
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
#endif /* __cplusplus */

#endif /*__HI_VOD_H__*/

