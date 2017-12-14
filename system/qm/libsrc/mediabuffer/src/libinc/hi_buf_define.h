/**
 \file hi_buf_define.h
 \brief buffer
 \author Shenzhen Hisilicon Co., Ltd.
 \date 2010 - 2050
 \version �ݸ�
 \author 
 */

#ifndef __HI_BUF_DEFINE_H__
#define __HI_BUF_DEFINE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "MediaBuffer.h"

/*----------------------------------------------*
* �궨��
*----------------------------------------------*/

/** @defgroup Buffer_API_macro Buffer_APIģ��
 *  @ingroup H2
 *  @brief ��ϸ����ģ��(Buffer_API)�궨��
 *  @{  */

/**���������С*/

/**Buffer��û�������������룬����ɼ���ѭ����*/
#define BUF_NO_DATA 1

/** @} */  /*! <!-- Macro Definition end */

/*----------------------------------------------*
* ����/�ṹ����
*----------------------------------------------*/

/** @defgroup Buffer_API_types Buffer_APIģ��
 *  @ingroup H2
 *  @brief ��ϸ����ģ��(Buffer_API)���Ͷ���
 *  @{  */

//#define MAX_CHANNEL_NUM 4
//#define VS_STREAM_TYPE_BUTT 5

 
/**Buf������Ϣ*/
typedef struct hiBUF_STREAM_INFO_S
{
    HI_U8 *pu8BufferStart;/**<�������׵�ַ*/
    HI_U32 pu8BufferStartPhy;/**<�������׵�ַ�����ַ*/
    HI_U32 u32BufferSize;/**<��������С*/
    BUF_BLOCK_INFO_S *pstBlockInfo;/**<������������(64Kһ����)�������Ϣ*/
    HI_U32 u32WritePos;/**<дָ��*/
    HI_U32 u32WriteCycle;/**<д��Ȧ��*/
} BUF_STREAM_INFO_S;

/**I֡����*/
typedef struct hiIFRAME_MNG_S
{
    HI_U32 u32ExpectNumber;/**<the expectant number of I-frame*/
    HI_U32 u32ValidNumber;/**<the valid I-frame number*/
    HI_U32 u32OldestIFrameIndex;/**<the oldest I-frame index(the index of I-frame position array)*/
    HI_U32 *pu32Position;/**<I-frame position*/
    HI_U32 *pu32Cycle;/**<Ȧ��*/
} BUF_IFRAME_MNG_S;

/** @} */  /*! <!-- types Definition end */


HI_S32 VS_BUF_GetReadPtrPos(HI_S32 s32ReaderId,
                           BUF_POSITION_POLICY_E enPolicy,
                           HI_S32 s32N,
                           BUF_READPTR_INFO_S *pstReadptr);
						   
HI_S32 VS_BUF_SetReadPtrPos(HI_S32 s32ReaderId,
                               HI_U32 u32Len);
							   
HI_S32 VS_BUF_CanRead(HI_S32 s32ReaderId, HI_U32 u32Len);

HI_S32 VS_BUF_CheckReaderPacketNo(HI_S32 s32ReaderId,
                     HI_BOOL bVideo , HI_U32 u32PacketNo);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif  /*__HI_BUF_DEFINE_H__*/




