/***********************************************************************************
*              Copyright 2006 - , Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_vs_media_comm.h
* Description:
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.0       2008-01-28   w54723     NULL         Create this file.
***********************************************************************************/


#ifndef __HI_VS_MEDIA_COMM_H__
#define __HI_VS_MEDIA_COMM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"

typedef HI_S32 VS_CHN;       /*���ͨ������*/ 

#define VS_CHN_ALL     0x0000FFFF
#define VS_CHN_DEFAULT 0
#define VS_CHN_INVALID -1

typedef HI_S32 ENC_VE_CHN;

typedef HI_S32 ENC_AE_CHN;

typedef HI_S32 ENC_VGRP_ID;

typedef HI_S32 ENC_SYNC_CHN;

typedef HI_S32 ENC_VI_CHN;

typedef HI_S32 ENC_AI_CHN;

typedef HI_S32 VI_VIDEV_ID;

typedef HI_S32 AI_AIDEV_ID;

#define ENC_MAX_VS_CHN_NUM  16
#define ENC_MAX_VGRP_NUM    16

/*mhua add �����2����δʹ��*/
#define ENC_MAX_VE_CHN_NUM  8   /*�����Ƶ����ͨ��(ve)��*/
#define ENC_MAX_AE_CHN_NUM  8   /*�����Ƶ����ͨ��(ae)��*/

#define VI_MAX_VI_CHN_NUM   8
//#define AI_MAX_AI_CHN_NUM   4
#define MEDIA_MAX_VI_DEV_NUM 4  /*����vi�豸��*/

//mhua add for vs_chn num
#define MEDIA_MAX_VSCHN_NUM   169   /*���������*/

/*format of video encode*/
typedef enum hiMT_VIDEO_FORMAT_E
{
    MT_VIDEO_FORMAT_H261  = 0,  /*H261  */
    MT_VIDEO_FORMAT_H263  = 1,  /*H263  */
    MT_VIDEO_FORMAT_MPEG2 = 2,  /*MPEG2 */
    MT_VIDEO_FORMAT_MPEG4 = 3,  /*MPEG4 */
    MT_VIDEO_FORMAT_H264  = 4,  /*H264  */
    MT_VIDEO_FORMAT_MJPEG = 5,  /*MOTION_JPEG*/
    MT_VIDEO_FORMAT_H265  = 6,  /*H265*/
    MT_VIDEO_FORMAT_BUTT
}MT_VIDEO_FORMAT_E;

/*format of audio encode*/
typedef enum hiMT_AUDIO_FORMAT_E
{
    MT_AUDIO_FORMAT_G711A   = 1,   /* G.711 A            */
    MT_AUDIO_FORMAT_G711Mu  = 2,   /* G.711 Mu           */
    MT_AUDIO_FORMAT_ADPCM   = 3,   /* ADPCM              */
    MT_AUDIO_FORMAT_G726    = 4,   /* G.726              */
    MT_AUDIO_FORMAT_AMR     = 5,   /* AMR encoder format */
    MT_AUDIO_FORMAT_AMRDTX  = 6,   /* AMR encoder formant and VAD1 enable */
    MT_AUDIO_FORMAT_AAC     = 7,   /* AAC encoder        */
    MT_AUDIO_FORMAT_BUTT
}MT_AUDIO_FORMAT_E;

typedef enum hiMT_AUDIO_BITWIDTH_E
{
    MT_AUDIO_BITWIDTH_8   = 0,   /* Bit width is 8 bits   */
    MT_AUDIO_BITWIDTH_16  = 1,   /* Bit width is 16 bits  */
    MT_AUDIO_BITWIDTH_32  = 2,   /* Bit width is 32 bits */ 
    MT_AUDIO_BITWIDTH_BUTT
}MT_AUDIO_BITWIDTH_E;

typedef enum hiMT_AUDIO_SAMPLE_RATE_E
{
    MT_AUDIO_SAMPLE_RATE_8     = 0,   /* 8K Sample rate     */
    MT_AUDIO_SAMPLE_RATE_11025 = 1,   /* 11.025K Sample rate*/
    MT_AUDIO_SAMPLE_RATE_16    = 2,   /* 16K Sample rate    */
    MT_AUDIO_SAMPLE_RATE_22050 = 3,   /* 22.050K Sample rate*/
    MT_AUDIO_SAMPLE_RATE_24    = 4,   /* 24K Sample rate    */
    MT_AUDIO_SAMPLE_RATE_32    = 5,   /* 32K Sample rate    */
    MT_AUDIO_SAMPLE_RATE_441   = 6,   /* 44.1K Sample rate  */
    MT_AUDIO_SAMPLE_RATE_48    = 7,   /* 48K Sample rate    */
    MT_AUDIO_SAMPLE_RATE_64    = 8,   /* 64K Sample rate    */
    MT_AUDIO_SAMPLE_RATE_882   = 9,   /* 88.2K Sample rate  */
    MT_AUDIO_SAMPLE_RATE_96    = 10,  /* 96K Sample rate    */
    MT_AUDIO_SAMPLE_RATE_1764  = 11,  /* 176.4K Sample rate */
    MT_AUDIO_SAMPLE_RATE_192   = 12,  /* 192K Sample rate   */
    MT_AUDIO_SAMPLE_RATE_BUTT
}MT_AUDIO_SAMPLE_RATE_E;


typedef enum hiMT_SOUND_MODE_E
{
    MT_SOUND_MODE_MOMO =0,          /*������*/
    MT_SOUND_MODE_STEREO =1,        /*˫����*/
    MT_SOUND_MODE_BUTT    
}MT_SOUND_MODE_E;


typedef struct hiVS_AUDIO_ATTR_S{
    MT_AUDIO_FORMAT_E enAFormat;              /*��Ƶ�����ʽ*/
    HI_U32          u32TargetBps;             /*Ŀ������*/
    MT_AUDIO_SAMPLE_RATE_E  enSampleRate;     /*��Ƶ��������ʣ���λ����*/
    MT_AUDIO_BITWIDTH_E  enBitwidth;          /*��Ƶ����λ��*/
    MT_SOUND_MODE_E      enSoundMode;         /*��Ƶ����������*/
}VS_AUDIO_ATTR_S;



typedef struct hiMT_MEDIAINFO_S
{
    /*include "hi_vs_media_comm.h"*/
    MT_AUDIO_FORMAT_E enAudioType;    //��Ƶ��ʽ
    HI_U32  u32AudioSampleRate;       //��Ƶ�����ʣ���λ����
    HI_U32  u32AudioChannelNum;       // 1������ 2˫����
    MT_VIDEO_FORMAT_E enVideoType;    //��Ƶ��ʽ
    HI_U32  u32VideoPicWidth;         //��Ƶ��
    HI_U32  u32VideoPicHeight;        //��Ƶ��
    HI_U32  u32VideoSampleRate;       //��Ƶ����Ƶ�ʣ���λ���ȣ��㶨Ϊ90000
    HI_U32  u32Framerate;
    HI_U32  u32Bitrate;
    HI_U32  u16EncodeVideo;       //�Ƿ������Ƶ
    HI_U32  u16EncodeAudio;       //�Ƿ������Ƶ

    unsigned long u32TotalTime;         //�ط��ļ�����
    //HI_CHAR auVideoDataInfo[128];
    HI_CHAR auVideoDataInfo[256];		//����TI��Ŀ
    HI_U32  u32VideoDataLen;
    int SPS_LEN;
    int PPS_LEN;
    int SEL_LEN;
    unsigned char profile_level_id[8];
}MT_MEDIAINFO_S;

//mhua add to check vs_chn
#define HI_CHECK_VSCHN(s32VsChn) \
    (((s32VsChn) < 0 || (s32VsChn) >= MEDIA_MAX_VSCHN_NUM)?HI_FALSE:HI_TRUE)


const HI_CHAR* HI_VS_GetVFmtCap(MT_VIDEO_FORMAT_E fmt);
const HI_CHAR* HI_VS_GetAFmtCap(MT_AUDIO_FORMAT_E fmt);

const MT_VIDEO_FORMAT_E HI_VS_GetVFmt_byCap(const HI_CHAR* cap);
const MT_AUDIO_FORMAT_E HI_VS_GetAFmt_byCap(const HI_CHAR* cap);



#define ENC_VI_CH_STARTX    0
#define ENC_VI_CH_STARTY    0

#define ENC_VGA_WIDTH       640 /*ͼ��Ϊvgaʱ�ı�׼��*/
#define ENC_VGA_HEIGHT      480 /*ͼ��Ϊvgaʱ�ı�׼��*/
#define ENC_QVGA_WIDTH      320 /*ͼ��Ϊqvgaʱ�ı�׼��*/
#define ENC_QVGA_HEIGHT     240 /*ͼ��Ϊqvgaʱ�ı�׼��*/
#define ENC_QQVGA_WIDTH      160 /*ͼ��Ϊqvgaʱ�ı�׼��*/
#define ENC_QQVGA_HEIGHT     128 /*ͼ��Ϊqvgaʱ�ı�׼��*/

#define ENC_CIF_WIDTH_PAL       352 /*ͼ��Ϊcifʱ�ı�׼��(P��)*/
#define ENC_CIF_HEIGHT_PAL      288 /*ͼ��Ϊcifʱ�ı�׼��(P��)*/
#define ENC_CIF_WIDTH_NTSC       352 /*ͼ��Ϊcifʱ�ı�׼��(N��)*/
#define ENC_CIF_HEIGHT_NTSC      240 /*ͼ��Ϊcifʱ�ı�׼��(N��)*/

#define ENC_QCIF_WIDTH_PAL       176 /*ͼ��Ϊcifʱ�ı�׼��(P��)*/
#define ENC_QCIF_HEIGHT_PAL      144 /*ͼ��Ϊcifʱ�ı�׼��(P��)*/
#define ENC_QCIF_WIDTH_NTSC       176 /*ͼ��Ϊcifʱ�ı�׼��(N��)*/
#define ENC_QCIF_HEIGHT_NTSC      112 /*ͼ��Ϊcifʱ�ı�׼��(N��)*/


#define ENC_D1_WIDTH_PAL       704 /*ͼ��Ϊcifʱ�ı�׼��(P��)*/
#define ENC_D1_HEIGHT_PAL      576 /*ͼ��Ϊcifʱ�ı�׼��(P��)*/
#define ENC_D1_WIDTH_NTSC       704 /*ͼ��Ϊcifʱ�ı�׼��(N��)*/
#define ENC_D1_HEIGHT_NTSC      480 /*ͼ��Ϊcifʱ�ı�׼��(N��)*/

#define ENC_XGA_WIDTH           1280    /*ͼ��Ϊ����ı�׼��*/
#define ENC_XGA_HEIGHT          720    /*ͼ��Ϊ����ı�׼��*/



/*VSCHN�ŵ������±��ת��*/
#define VS_CHN2IDX(vschn) ((vschn/10 - 1)*VS_STREAM_PER_CAM + (vschn%10 -1 ))


/*���vschn���Ƿ�Ϸ�*/
//#define VS_CHECK_VSCHN(vschn) ( ( (vschn) > 0) && ( (vschn) <=(VS_MAX_CAM_CNT*10+VS_STREAM_PER_CAM)))

#define VS_CHECK_VSCHN(vschn) (( (vschn) > 0) && ( (vschn) <=(VS_MAX_CAM_CNT*10+VS_STREAM_PER_CAM))&&((vschn/10 >= 1)&&(vschn/10 <= VS_MAX_CAM_CNT))&&((vschn%10 >= 1)&&(vschn%10 <= VS_STREAM_PER_CAM)))


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */

#endif /*__HI_VS_MEDIA_COMM_H__*/

