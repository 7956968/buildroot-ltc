/***********************************************************************************
*              Copyright 2006 - 2006, Hisilicon Tech. Co., Ltd.
*                           ALL RIGHTS RESERVED
* FileName: hi_mbuf.h
* Description: The MBUF module.
*
* History:
* Version   Date         Author     DefectNum    Description
* 1.1       2007-05-04   h48078     NULL         Create this file.
***********************************************************************************/

#ifndef __HI_MBUF_H__
#define __HI_MBUF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <pthread.h>
#include "hi_type.h"
#include "hi_list.h"
#include "hi_mt_def.h"
#include "hi_mbuf_def.h"
#include "hi_vs_media_comm.h"

/*����vschn�Ż�ȡenc�ڲ�������±�
 vschn��ŷ�ʽΪCCS. CCΪcamera���(01~08), SΪ��camera�µ�������(1~2)
 enc�ڲ�������±� = (CC-1)*ÿcamera֧�ֵ���������� + (S-1)
 */
#define MBUF_GET_MBUFCHN_BY_VSCHN VS_CHN2IDX

//typedef void*              HI_ADDR;


/*���ͨ������ÿ����Ƶ����ͨ����Ӧһ��ͨ��*/
//#define MAX_MBUF_CHN_NUM	IDM_MAX_VSCHN_CNT	//BT HI3511	
#define MAX_MBUF_CHN_NUM	VS_MAX_STREAM_CNT

/*֧��Э������packet header size(4bytes����)*/
#define MAX_PROTOCOL_HEADER_SIZE 	100

/*p�����дָ�룬len����֡���ݳ���
NEXT_POINT(p, len) ָ����֡payload�����һ���ֽ�*/
#define NEXT_POINT(p, len) ((HI_ADDR)p + ALIGN_LENGTH(len, ALIGNTYPE_4BYTE) \
                                    + MAX_PROTOCOL_HEADER_SIZE \
                                    + ALIGN_LENGTH(sizeof(MBUF_PT_HEADER_S), ALIGNTYPE_4BYTE)) 

/*lenΪ����֡���ȣ�PT_LENGTH��������payload�ĳ���*/
#define PT_LENGTH(len) (ALIGN_LENGTH(len, ALIGNTYPE_4BYTE) \
                            + MAX_PROTOCOL_HEADER_SIZE \
                            + ALIGN_LENGTH(sizeof(MBUF_PT_HEADER_S), ALIGNTYPE_4BYTE))
                                    
/*pΪָ��MBUF_PT_HEADER_S��ָ�룬PAYLOAD_ADDR����
����֡����ʼ��ַ*/
#define PAYLOAD_ADDR(p) ((HI_ADDR)p + MAX_PROTOCOL_HEADER_SIZE \
                        + ALIGN_LENGTH(sizeof(MBUF_PT_HEADER_S), ALIGNTYPE_4BYTE))

//typedef HI_S32 MBUF_CHN;
#if 0
typedef struct hiMBUF_CHENNEL_INFO_S{
    int  chnnum; /* 011 */
    HI_U32 max_connect_num;     //��ͨ��֧�ֵ����������
    HI_U32 buf_size;            //��ͨ��ÿ��buf�Ĵ�С(4bytes����)
}MBUF_CHENNEL_INFO_S;
#endif
/*����ͼ���С��ö�ٱ���*/
typedef enum hiMBUF_PIC_FORMAT_E
{
    D1 = 0, 
    CIF,
    QCIF,
    VGA,
    QVGA,
    PIC_FORMAT_NUM
}MBUF_PIC_FORMAT_E; 

typedef enum hiMBUF_VIDEO_STATUS_E
{
    VIDEO_DISABLE = 0,
    VIDEO_REGISTER,       //��ע��
    VIDEO_READY           //��ʼд��
}MBUF_VIDEO_STATUS_E;



#define SET_VIDEO_DISCARD(x)    ((x) |= 0x1)
#define SET_AUDIO_DISCARD(x)    ((x) |= 0x2)
#define SET_DATA_DISCARD(x)     ((x) |= 0x4)
#define SET_ALL_DISCARD(x)      ((x) |= 0x7)

#define CLEAR_VIDEO_DISCARD(x)  ((x) &= (~0x1))
#define CLEAR_AUDIO_DISCARD(x)  ((x) &= (~0x2))
#define CLEAR_DATA_DISCARD(x)   ((x) &= (~0x4))
#define CLEAR_ALL_DISCARD(x)    ((x) = 0)

#define CHECK_VIDEO_DISCARD(x)  ((x) & 0x1)
/*MBUF header*/
typedef struct hiMBUF_HEADER_S{
    HI_ADDR start_addr; //��������ʼ��ַ
    HI_U32 len; //����������
    MBUF_CHN ChanID; //MBUFͨ����
    volatile HI_U8 discard_flag; //��֡״̬��־λ,���3bit�ֱ��ʾ�Ƿ�����Ƶ����Ƶ��DATA
    volatile MBUF_VIDEO_STATUS_E video_status; //�������Ƿ�����Ƶ
    volatile HI_BOOL audio_enable; //�������Ƿ�����Ƶ
    volatile HI_BOOL data_enable; //�������Ƿ�������
    /*start <= w/r < start + len*/
    volatile HI_ADDR writepointer; //дָ�룬ָ��ǰ��д�ֽ�
    volatile HI_ADDR readpointer; //��ָ�룬ָ����һ������ȡ�ֽ�
    volatile HI_ADDR flagpointer; //�����Ƿ����������յ�ָ��
    volatile HI_ADDR tempWriterpointer; //��ʱ����Ƶдָ��
    volatile HI_ADDR last_framestart; //��¼�ϸ���Ƶ֡��ʼ
    volatile HI_U64 discard_count; //��¼�����Ӷ���
    List_Head_S list;
}MBUF_HEADER_S;

/*T41030 2010-02-11 Add Config of Buffer leftspace*/
#define MBUF_DEFAULT_BUF_DISCARD_THRESHOLD 20480 //16kbps*10s + u32VideoFrameLen

/*MBUF info*/
typedef struct hiMBUF_INFO_S{
    List_Head_S buf_free; //��ͨ������buf����
    List_Head_S buf_busy; //��ͨ��ռ��buf����
    HI_U32 max_connect_num; //��ͨ��֧�ֵ����������
    HI_U32 buf_size; //��ͨ��ÿ��buf�Ĵ�С(4bytes����)
    /*T41030 2010-02-11 Add Config of Buffer leftspace*/
    HI_U32 buf_discard_threshold;/*��ʼ��֡������ֵ*/
    
    HI_ADDR start_addr; //��ͨ���ڴ���ʼ��ַ(4bytes����)
    HI_U32 total_size; //��ͨ�����ڴ��С(4bytes����)
    pthread_mutex_t lock; //�����������ʱ����
}MBUF_INFO_S;
#if 0
/*MBUF payload type*/
typedef enum hiMBUF_PT_E
{
    VIDEO_KEY_FRAME = 1, //��Ƶ�ؼ�֡
    VIDEO_NORMAL_FRAME, //��Ƶ��ͨ֡
    AUDIO_FRAME, //��Ƶ֡
    MD_FRAME, //MD����
    MBUF_PT_BUTT
}MBUF_PT_E;
#endif
/*BUF payload header*/
typedef struct hiMBUF_PT_HEADER_S{
    MBUF_PT_E payload_type; //payload���ͣ���ƵI����Ƶ����Ƶ��
    HI_U32 payload_len; //payload����
    HI_U64 pts; //ʱ���
    /*��Ƶslice����Ϣ�ر�ע�⣬һֻ֡��һ��slice�����slice������ʼҲ�ǽ���slice*/
    HI_U32 slice_num; //ÿ֡slice����
    HI_U32 frame_len; //��֡�������ݳ���
    HI_U8 slice_type; //slice���� 0x01����ʼ  0x02 �м�slice 0x04 - һ֡�����һ��slice*/
    HI_U8 resv[3];
}MBUF_PT_HEADER_S;

/*MBUF��ʼ������������ڴ��Լ������ʼ��*/
HI_S32 MBUF_Init(HI_S32 chnnum, MBUF_CHENNEL_INFO_S *pinfo);

/*MBUF���٣������ͷ��ڴ��Լ��������*/
HI_VOID MBUF_DEInit();

/*
����һ��mbuf
ChanID ���������MBUFͨ����
pphandle �������������ָ��buf handle��ָ��
*/
HI_S32 MBUF_Alloc(MBUF_CHN ChanID, MBUF_HEADER_S **pphandle);

/*
�ͷ�һ��mbuf
pphandle �������������ָ����ͷ�mbuf handle��ָ�룬
                �ɹ��ͷź�*pphandle = NULL
*/
HI_S32 MBUF_Free(MBUF_HEADER_S **pphandle);

/*MBUF ��Ƶ����Ƶ������ע�ắ��
HI_TRUE ʹ�ܣ�HI_FALSE ��ֹ*/
HI_VOID MBUF_Register(MBUF_HEADER_S *phandle, MBUF_VIDEO_STATUS_E video_status, HI_BOOL audio_enable, HI_BOOL data_enable);

/*MBUF ��ȡ��Ƶ����Ƶ������ע��״̬����
HI_TRUE ʹ�ܣ�HI_FALSE ��ֹ*/
HI_VOID MBUF_GetRegister(MBUF_HEADER_S *phandle, MBUF_VIDEO_STATUS_E* pvideo_status, HI_BOOL* paudio_enable, HI_BOOL* pdata_enable);

/*�ṩ��ý�崦��ģ��Ľӿں���������������bufд������
�ú���������ChanID������Ӧ��busy list*/

HI_VOID MBUF_Write(HI_S32 ChanID, MBUF_PT_E payload_type, 
                   const HI_ADDR addr, HI_U32 len, HI_U64 pts, 
                   HI_U8 *pslice_type, HI_U32 slicenum, HI_U32 frame_len);
                   
HI_S32 MBUF_Read(MBUF_HEADER_S *phandle, HI_ADDR*paddr, HI_U32 *plen, 
            HI_U64 *ppts, MBUF_PT_E *ppayload_type,HI_U8 *pslice_type, 
            HI_U32 *pslicenum, HI_U32 *pframe_len);

HI_VOID MBUF_Set(MBUF_HEADER_S *phandle);

#define MBUFF_MOD "MBUFF"

#ifndef DEBUG_MBUF
#define DEBUG_MBUF 8
#if (DEBUG_MBUF == 0) || !defined(DEBUG_ON)
    #define DEBUG_MBUF_PRINT(pszModeName, u32Level, args ...)
#else
#define DEBUG_MBUF_PRINT(pszModeName, u32Level, args ...)   \
    do  \
    {   \
        if (DEBUG_MBUF >= u32Level)    \
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

