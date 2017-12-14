/*
2008-11-10 10:00 v0.1
*/

//#include "hi_type.h"
//#include "hi_mbuf_def.h"
//#include "hi_vs_media_comm.h"
//#include "hi_buffer_abstract_define.h"
//#include "hi_msession_http.h"
#ifndef  __HI_MT_DEF_H__
#define  __HI_MT_DEF_H__
#ifdef __cplusplus
#if __cplusplus

extern "C"
{
#endif
#endif /* __cplusplus */


#define PROTONAME_MAX_LEN   32
/*VSCHN�ŵı�ʾ��ʽ*/
/*xxy xx������ͷ��, ��1��ʼ���, y��������, ��1��ʼ���*/
#define VS_MAX_CAM_CNT 1 /*֧�ֵ��������ͷ��*/
#define VS_STREAM_PER_CAM 6 /*ÿ������ͷ֧�ֵ����������*/
#define VS_MAX_STREAM_CNT (VS_MAX_CAM_CNT * VS_STREAM_PER_CAM )


/*ý�������Э������*/
typedef enum hiPACK_TYPE_E
{
    PACK_TYPE_RAW = 0, /*��˼ý���ͷ����MEDIA_HDR_S��ͷ��8���ֽڣ�����TCP����*/
    PACK_TYPE_RTP,     /*��ͨRTP�����ʽ��ͷ��12���ֽ�*/
    PACK_TYPE_RTP_STAP,/* STAP-A�����ʽ������3���ֽڵľ���ͷ��ͷ��15���ֽ�*/
    PACK_TYPE_RTP_FUA, /*FU-A�����ʽ,һ��slice��Ϊ����rtp�����ͣ�����ǰ����2typeͷ*/
    PACK_TYPE_RTSP_ITLV, /*rtsp interleaved �����ʽ,��rtpͷ��ǰ����4������ͷ*/
    PACK_TYPE_HISI_ITLV, /*hisi interleaved �����ʽ,��rtpͷ��ǰ����8������ͷ*/
    PACK_TYPE_LANGTAO,
    PACK_TYPE_OWSP,
    PACK_TYPE_RTSP_O_HTTP,
    PACK_TYPE_BUTT     
} PACK_TYPE_E;

/*����ģʽ,Ŀǰ��֧��MTRANS_MODE_UDP �� MTRANS_MODE_TCP_ITLV��ʽ:
 MTRANS_MODE_UDP: ��ͨudp����ģʽ:ý�����ݺ����������������˿��Ϸ���
 MTRANS_MODE_TCP_ITLV:interleaved��ʽ��tcp����ģʽ:�Ự,ý�����ݺ�����������ͬһ�������Ϸ���
*/
typedef enum hiMTRANS_MODE_E
{
    MTRANS_MODE_UDP = 0,
    MTRANS_MODE_UDP_ITLV,
    MTRANS_MODE_TCP,
    MTRANS_MODE_TCP_ITLV,
    MTRANS_MODE_BROADCAST,
    MTRANS_MODE_MULTICAST,
    MTRANS_MODE_BUTT
}MTRANS_MODE_E;

typedef enum hiLIVE_MODE_E
{
	LIVE_MODE_1CHN1USER = 0,/**��ͨ�����û�ģʽ*/
	LIVE_MODE_1CHNnUSER,/**��ͨ�����û�ģʽ*/
	LIVE_MODE_BUTT
}LIVE_MODE_E;

/*Ϊ�˴���hi3510��hi3511���ݶ����ӵ�һ���ص�*/
typedef struct hiHTTP_LIVE_PACKPROTO_S
{
    PACK_TYPE_E enPackType;
    char aszPackProtoName[PROTONAME_MAX_LEN];  /*���Э�������*/
}HTTP_LIVE_PACKPROTO_S;

typedef int (*HI_HTTP_GetPackProtoInfo_PTR)(HTTP_LIVE_PACKPROTO_S *pstruProto);

typedef struct hiMT_CONFIG_RTSP_STREAMSVR_S
{
    int bEnable;
    int listen_port;
    int max_connections;
    /*udp�Ķ˿ڷ�Χ*/
    int udp_send_port_min;
    int udp_send_port_max;    
}MT_CONFIG_RTSP_STREAMSVR_S;

typedef struct hiMT_CONFIG_RTSPoHTTP_SVR_S
{
    int bEnable;
    //int listen_port;
    int max_connections;
}MT_CONFIG_RTSPoHTTP_SVR_S;

typedef struct hiMBUF_CHENNEL_INFO_S
{
    int  chnid; /* 011 */
    unsigned int max_connect_num;     //��ͨ��֧�ֵ����������
    unsigned int buf_size;            //��ͨ��ÿ��buf�Ĵ�С(4bytes����)
    /*T41030 2010-02-11 Add Config of Buffer leftspace*/
    unsigned int buf_discard_threshold;
}MBUF_CHENNEL_INFO_S;

typedef struct hiMT_CONFIG_S
{
    MT_CONFIG_RTSP_STREAMSVR_S rtspsvr;
    MT_CONFIG_RTSPoHTTP_SVR_S rtspOhttpsvr;
    
    /*�������, Ŀǰ������rtsp/rtp��udp������*/
    int              packet_len;
    
    LIVE_MODE_E         enLiveMode;
    int              maxUserNum;
    int 				maxFrameLen;    
    int              chn_cnt;
    MBUF_CHENNEL_INFO_S mbuf[VS_MAX_STREAM_CNT];

}MT_CONFIG_S;

typedef struct tagMT_MulticastInfo_s
{
    unsigned int channel;
    unsigned int streamType;
    char multicastAddr[32];
    unsigned short port[2];
}MT_MulticastInfo_s;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

