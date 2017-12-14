/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_buf.cpp
  Version       : Initial Draft
  Author        : lizhaozao
  Created       : 2010/05/18
  Description   : buffer
  History       :
******************************************************************************/


#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <malloc.h>

#include "hi_comm_inc.h"
//#include "hi_vs_inc.h"
#include "hi_buf_define.h"
#include "cbuffer.h"
#include "MediaBuffer.h"

#ifdef HI3518
#include "hi_mem.h"
#endif

/*Buffer����*/
CBuffer* g_pBuf[MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT];

#define BUF_ERR_GET_READ_POS		-1
#define BUF_ERR_GET_IFRAME_FAILED	-2
#define BUF_ERR_EMPTY	-3



typedef struct tagDMS_EVENT{
	pthread_mutex_t mutex;
	pthread_cond_t	cond;
}DMS_EVENT;

DMS_EVENT *CreateEvent()
{
	DMS_EVENT *lpEvent = (DMS_EVENT *)malloc(sizeof(DMS_EVENT));
	if(lpEvent == 0)
		return lpEvent;
	pthread_mutex_init(&lpEvent->mutex,NULL);	/*��ʼ��������*/
	pthread_cond_init(&lpEvent->cond,NULL);		//��ʼ����������
	return lpEvent;
}

void SetEvent(DMS_EVENT *lpEvent)
{
	if(lpEvent == 0)
		return ;
	pthread_mutex_lock(&lpEvent->mutex);//
	pthread_cond_broadcast(&lpEvent->cond);/*�����ı䣬�����ź�*/
	pthread_mutex_unlock(&lpEvent->mutex);//*����������*/
}

void WaitForEvent(DMS_EVENT *lpEvent)
{
	if(lpEvent == 0)
		return ;
	pthread_mutex_lock(&lpEvent->mutex);
	pthread_cond_wait(&lpEvent->cond,&lpEvent->mutex);/*�ȴ�*/
	pthread_mutex_unlock(&lpEvent->mutex);
}

void ReleaseEvent(DMS_EVENT *lpEvent)
{
	pthread_mutex_destroy(&lpEvent->mutex);
	pthread_cond_destroy(&lpEvent->cond);
	free(lpEvent);
}

typedef struct tagDMSReaderInfo
{
	int 		s32Index;
	int 		s32BufferReaderID;
	int 		s32With;
	int 		s32Heitht;
	
}DMSReaderInfo;

DMS_EVENT* dmsEvent[MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT ] = {0};

DMSReaderInfo stDMSReaderInfo[MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT * BUF_MAX_READER_NUM]  ;
/*
 Function:
 Description:��ȡ����ָ��
 Parameter:
 Return:
 Author:
 Time:[2011-5-13 9:39:07]
*/
inline static HI_S32 BUF_GetDataPoint(HI_S32 s32ReaderId,
			   BUF_POSITION_POLICY_E enPolicy,
			   HI_S32 s32N,
			   HI_U8 **pu8Frame,
               HI_S32 s32FrameLenth,
               HI_U8  u8IOblock)
{
	HI_S32 s32Ret = 0;
	BUF_READPTR_INFO_S stReadPtrInfo;
	static int count = 0;
	/*�Ȱ�ָ��Ų����I֡*/
	if (BUF_POSITION_LAST_WRITE_nIFRAME == enPolicy
		|| BUF_POSITION_LAST_READ_nIFRAME == enPolicy)
	{
        //printf("#### %s %d\n", __FUNCTION__, __LINE__);
		s32Ret = VS_BUF_GetReadPtrPos(s32ReaderId,enPolicy,s32N,&stReadPtrInfo);

        //printf("#### %s %d, ret=%d, framenum=%d\n",
        //            __FUNCTION__, __LINE__, s32Ret, stReadPtrInfo.stBlockInfo.u32IFrameNum);
		if (HI_SUCCESS != s32Ret)
			return BUF_ERR_GET_READ_POS;		
		if(0 == stReadPtrInfo.stBlockInfo.u32IFrameNum)
			return BUF_ERR_GET_IFRAME_FAILED;		
		VS_BUF_SetReadPtrPos(s32ReaderId,stReadPtrInfo.stBlockInfo.astIFrame[stReadPtrInfo.stBlockInfo.u32IFrameNum - 1].u32Offset);
		enPolicy = BUF_POSITION_CUR_READ;		
	}
	while(1)
	{
        //printf("#### %s %d\n", __FUNCTION__, __LINE__);
		s32Ret = VS_BUF_CanRead(s32ReaderId, s32FrameLenth);
		if ( s32Ret < s32FrameLenth)
		{
            //printf("#### %s %d\n", __FUNCTION__, __LINE__);
			if(u8IOblock)
			{
				DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    			HI_U32 u32Index = pstReaderInfo->s32Index ;
				//[2011-5-13 10:26:44]  һֱ���Զ����ݣ�ֱ��ָ�����ȵ����ݿɶ�
				WaitForEvent(dmsEvent[u32Index]);
			}
			else
			{
                //printf("#### %s %d\n", __FUNCTION__, __LINE__);
				return BUF_ERR_EMPTY;
			}
			continue;
		}
		else if (s32Ret < 0)
		{
			printf("%s %d VS_BUF_CanRead %d failed %d\n",__FUNCTION__,__LINE__,s32FrameLenth,s32Ret);
			return s32Ret;
		}
		else if(s32Ret >= s32FrameLenth)
		{
			s32FrameLenth = s32Ret;
			break;
		}
		
		printf("%s %d BUF_GetDataPoint count  error  %d failed %d\n",__FUNCTION__,__LINE__,s32FrameLenth,s32Ret);
		return -1;
		
	}

	count = 0;
    //printf("#### %s %d\n", __FUNCTION__, __LINE__);
	//[2011-5-13 10:27:23]  ��ȡ���ݵĶ�ָ��
	s32Ret = VS_BUF_GetReadPtrPos(s32ReaderId,enPolicy,s32N,&stReadPtrInfo);
	if (HI_SUCCESS != s32Ret)
		return BUF_ERR_GET_READ_POS;
	if(pu8Frame)
		*pu8Frame = stReadPtrInfo.pu8ReadPos;
	return s32FrameLenth;
}


/*********************************************************************
    Function:
    Description:��ʼ��Buffer����
    Calls:
    Called By:
    parameter:
    Return:HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_Init()
{
    for (HI_U32 u32StreamType = (HI_U32)VS_STREAM_TYPE_MAIN;
         u32StreamType < (HI_U32)VS_STREAM_TYPE_BUTT;
         u32StreamType++)
    {
        for (HI_U32 u32Chn = 0; u32Chn < MAX_CHANNEL_NUM; u32Chn++)
        {
            g_pBuf[u32Chn + u32StreamType * MAX_CHANNEL_NUM] = NULL;
        }
    }
    printf("Module Manager Build:%s %s\n", __DATE__, __TIME__);
    return HI_SUCCESS;
}


/*********************************************************************
    Function:VS_BUF_Exit
    Description:ȥ��ʼ��Buffer����
    Calls:
    Called By:
    parameter:
    Return:HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_Exit()
{
    for (HI_S32 s32StreamType = (HI_S32)VS_STREAM_TYPE_MAIN;
         s32StreamType < (HI_S32)VS_STREAM_TYPE_BUTT;
         s32StreamType++)
    {
        for (HI_S32 s32Chn = 0; s32Chn < MAX_CHANNEL_NUM; s32Chn++)
        {
            if (NULL != g_pBuf[s32Chn + s32StreamType * MAX_CHANNEL_NUM])
            {
                (HI_VOID)VS_BUF_Destroy(s32Chn, (VS_STREAM_TYPE_E)s32StreamType);
            }
            g_pBuf[s32Chn + s32StreamType * MAX_CHANNEL_NUM] = NULL;
        }
    }
    return HI_SUCCESS;
}


/*********************************************************************
    Function:VS_BUF_Create
    Description:����Cbuffer
    Calls:
    Called By:
    parameter:
           [in] s32Chn Դͨ����
           [in] enStreamType buff��������
           [in] u32BlockSize ���С
           [in] u32BlockNum ����
    Return:HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_Create(const HI_S32 s32Chn,
                        const VS_STREAM_TYPE_E enStreamType,
                        const HI_U32 u32BlockSize,
                        const HI_U32 u32BlockNum)
{
    /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_Create param erro!\n");
        return HI_EPAERM;
    }

    /*����Ѿ�����������*/
    if (NULL != g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_Create CBuffer Exit!\n");
        return HI_EEXIST;
    }

    /*����Buffer*/
    g_pBuf[u32Index] = new CBuffer();
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_Create new CBuffer failed!\n");
        return HI_ENORES;
    }

    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_Create(u32BlockSize, u32BlockNum);
    if (HI_SUCCESS != s32Ret)
    {
        delete g_pBuf[u32Index];
        g_pBuf[u32Index] = NULL;
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_Create BUF_Create failed!\n");
        return HI_ENORES;
    }
    
	dmsEvent[u32Index] = CreateEvent();

    return HI_SUCCESS;
}


/*********************************************************************
    Function:   VS_BUF_Destroy
    Description:����buf
    Calls:
    Called By:
    parameter:
            [in] s32Chn Դͨ����
            [in] enStreamType buff��������
    Return:
    Author:
********************************************************************/
HI_S32 VS_BUF_Destroy(const HI_S32 s32Chn,
                         const VS_STREAM_TYPE_E enStreamType)
{
    /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_Destroy param erro!\n");
        return HI_EPAERM;
    }

    /*����Buffer*/
    if (NULL != g_pBuf[u32Index])
    {
        (HI_VOID)g_pBuf[u32Index]->BUF_Destroy();
        delete g_pBuf[u32Index];
        g_pBuf[u32Index] = NULL;
    }
    
	if(dmsEvent[u32Index])
	{
		ReleaseEvent(dmsEvent[u32Index]);
		dmsEvent[u32Index] = 0;
	}

    return HI_SUCCESS;
}

void BUF_Lock(const HI_S32 s32Chn,const VS_STREAM_TYPE_E enStreamType)
{
	HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
	
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "BUF_Lock param erro!\n");
        return ;
    }
	if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "BUF_Lock g_pBuf NULL!\n");
        return ;
    }
	g_pBuf[u32Index]->BUF_Lock();
}

void BUF_UnLock(const HI_S32 s32Chn,const VS_STREAM_TYPE_E enStreamType)
{
	HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
	
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "BUF_Lock param erro!\n");
        return ;
    }
	if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "BUF_Lock g_pBuf NULL!\n");
        return ;
    }
	g_pBuf[u32Index]->BUF_Unlock();
}

/*********************************************************************
    Function:   BUF_Write
    Description:дBuffer,һ��Buffer֧��һ��дָ�����
    Calls:      �ýӿ��ڲ�ʹ��
    Called By:
    parameter:
            [in] s32Chn Դͨ����
            [in] enStreamType ��������
            [in] HI_U8 *pu8Start ��ʼ��ַ
            [in] HI_U32 u32Len   ����
            [in] HI_BOOL bIFrame �Ƿ�ΪI֡
            [in] VS_DATETIME_S *pTime  ʱ��
    Return: HI_SUCCESS
    Author:
********************************************************************/
HI_S32 BUF_Write(const HI_S32 s32Chn,
                       const VS_STREAM_TYPE_E enStreamType,
                       const HI_U8 *pu8Start,
                       HI_U32 u32Len,
                       HI_BOOL bIFrame,
                       VS_DATETIME_S *pTime)
{
    /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
	
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_Write param erro!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_Write g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }
    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_Write(pu8Start,u32Len,bIFrame,pTime);

	if(dmsEvent[u32Index])
		SetEvent(dmsEvent[u32Index]);
	
    return s32Ret;
}


/*********************************************************************
    Function:   VS_BUF_WriteFrame
    Description:д��Ƶ���ݽ�Buffer
    Calls:
    Called By:
    parameter:
            [in] s32Chn Դͨ����
            [in] enStreamType ��������
            [in] HI_U8 *pu8Start ��ʼ��ַ
            [in] HI_U32 u32Len   ����
            [in] HI_VS_VIDEO_FRAME_TYPE_E enFrameType ֡����
            [in] VS_DATETIME_S *pTime  ʱ��
            [in] HI_U64 u64Pts  ʱ���
    Return: HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_WriteFrame(const HI_S32 s32Chn,
                         const VS_STREAM_TYPE_E enStreamType,
                         VS_FRAME_TYPE_E enFrameType,
                         const HI_U8 *pu8Start,
                         HI_U32 u32Len,
                         HI_U64 u64Pts,
                         VS_DATETIME_S *pTime)
{
    /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_WriteFrame CBuffer Exit!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_WriteFrame g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }

    HI_S32 s32Ret = HI_SUCCESS;
	g_pBuf[u32Index]->BUF_Lock();
    if (VS_FRAME_A == enFrameType)
    {
        s32Ret = g_pBuf[u32Index]->BUF_WriteAudioData(pu8Start,
                                    u32Len,
                                    s32Chn,
                                    u64Pts);
    }
    else
    {
        s32Ret = g_pBuf[u32Index]->BUF_WriteVideoData(pu8Start,
                                    u32Len,
                                    (VS_FRAME_TYPE_E)enFrameType,
                                    pTime,
                                    s32Chn,
                                    u64Pts);
    }
	g_pBuf[u32Index]->BUF_Unlock();
	
	if(dmsEvent[u32Index])
		SetEvent(dmsEvent[u32Index]);
		
    return s32Ret;
}


/*********************************************************************
    Function:   VS_BUF_AddReader
    Description:��Ӷ�ָ��,һ��Buffer֧�ֶ����ָ�����
    Calls:
    Called By:
    parameter:
            [in] s32Chn Դͨ����
            [in] enStreamType ��������
            [out] HI_S32 *ps32ReaderId  ���ض�ָ��ID
    Return: HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_AddReader(const HI_S32 s32Chn,
                           const VS_STREAM_TYPE_E enStreamType,
                           HI_S32 *ps32ReaderId)
{
    /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;

    printf("######## %s %d, u32Index=%d, s32Chn=%d, enStreamType=%d\n", __FUNCTION__, __LINE__, u32Index, s32Chn, enStreamType);
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        *ps32ReaderId = 0;
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_AddReader Para erro!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        return HI_ENOTINIT;
    }
	HI_S32 s32DMSReaderIndex = 0;
    HI_S32 s32BuferReaderID = -1;
    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_AddReader(&s32BuferReaderID);
    if (HI_SUCCESS == s32Ret && s32BuferReaderID < BUF_MAX_READER_NUM && s32BuferReaderID >= 0)
    {
        s32DMSReaderIndex = (HI_S32)(BUF_MAX_READER_NUM * u32Index) + s32BuferReaderID;		
        s32Ret = HI_SUCCESS;
    }
    else
    {
        *ps32ReaderId = 0;
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_AddReader BUF_AddReader erro!\n");
        s32Ret = HI_FAILURE;
    }

	stDMSReaderInfo[s32DMSReaderIndex].s32Index = u32Index;
	stDMSReaderInfo[s32DMSReaderIndex].s32BufferReaderID = s32BuferReaderID;
	BUF_STREAM_ATTR_S stStreamAttr;
	 g_pBuf[u32Index]->BUF_GetStreamAttr((BUF_STREAM_ATTR_S *)&stStreamAttr);
	stDMSReaderInfo[s32DMSReaderIndex].s32With = stStreamAttr.u32Width;
	stDMSReaderInfo[s32DMSReaderIndex].s32Heitht = stStreamAttr.u32Height;
	*ps32ReaderId = (HI_S32)&stDMSReaderInfo[s32DMSReaderIndex];
	
    printf("s32Chn %d enStreamType %d reader %d index %d bufferid %d\n" , s32Chn , enStreamType  , *ps32ReaderId  , u32Index , s32BuferReaderID );
    return s32Ret;
}


/*********************************************************************
    Function:   VS_BUF_DelReader
    Description:ɾ����ָ��
    Calls:
    Called By:
    parameter:
            [in] HI_S32 s32ReaderId  ��ָ��ID
    Return: HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_DelReader(HI_S32 s32ReaderId)
{
    /*����������*/
    if (s32ReaderId == 0)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_DelReader Para erro\n");
        return HI_EPAERM;
    }
    
    DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_S32 s32BufferReaderID = pstReaderInfo->s32BufferReaderID;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_DelReader Para erro!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_DelReader g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }

    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_DelReader(s32BufferReaderID);

    return s32Ret;
}



/*********************************************************************
    Function:   VS_BUF_GetFrame
    Description:��ȡ֡����
    Calls:      ��Buffer�л�ȡ֡���ݣ�������Ƶ����Ƶԭʼ������֡����
    Called By:
    parameter:
        [in] HI_S32 s32ReaderId  ��ָ��ID
        [in] VS_BUF_POSITION_POLICY_E enPolicy  ��ȡ֡��ʽ
        [in] HI_S32 s32N  ���֡��
        [out] VS_FRAME_TYPE_E *penFrameType ����֡����
        [in] HI_U8 *pu8Start   �����������ݻ�����ʼ��ַ
        [in/out] HI_U32 *pu32Len  �������뻺�泤�ȣ�����ʵ��֡���ݳ���
        [out] HI_U64 *pu64Pts  ʱ���
    Return: HI_SUCCESS
            HI_EPAERM   �����������
            HI_ENOTINIT Bufferδ����
            BUF_NO_DATA Buffer����ʱ�����ݣ���Ҫ���������»�ȡ
    Author:
********************************************************************/
HI_S32 VS_BUF_GetFrame(HI_S32 s32ReaderId,
                       BUF_POSITION_POLICY_E enPolicy,
                       HI_S32 s32N,
                       VS_FRAME_TYPE_E *penFrameType,
                       HI_U8 *pu8Start,
                       HI_U32 *pu32Len,
                       HI_U64 *pu64Pts,
                       HI_U32 *pu32PacketNo, 
                       HI_S32 *ps32Width,
                       HI_S32 *ps32Height,
                       HI_U8   u8IOblock)
{
    if (enPolicy >= BUF_POSITION_BUTT || enPolicy < 0
        || NULL == penFrameType
        || NULL == pu8Start
        || NULL == pu32Len || *pu32Len < 24)
    {
      //  printf("VS_BUF_GetFrame para erro readid:%d\n", s32ReaderId);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetFrame para erro readid:%d\n", s32ReaderId);
    }
	HI_S32 s32Ret = 0;
	
	HI_U8  * pu8FrameAddr = NULL;
	HI_U32  u32FrameLen = 0;
	HI_U32  u32FrameOffset = 0;
	s32Ret = VS_BUF_GetFramePtr( s32ReaderId , enPolicy , s32N ,penFrameType, &pu8FrameAddr , &u32FrameOffset , &u32FrameLen , pu64Pts , pu32PacketNo ,ps32Width,ps32Height ,  u8IOblock);
	if(s32Ret)
	{
		printf("LINE .%d VS_BUF_GetFramePtr failed \n" , __LINE__);
		return s32Ret;
	}

	if(*pu32Len < u32FrameLen)
	{
		printf("LINE .%d VS_BUF_GetFrame Mem failed \n" , __LINE__);
		return -1;
	}

	memcpy(pu8Start , pu8FrameAddr , u32FrameLen );

	*pu32Len = u32FrameLen;

    return s32Ret;
}

inline HI_U8 *  VS_BUF_GetBufAddr(HI_U32 u32Reader)
{
	 /*����������*/
	 if(u32Reader == 0 )
	 {
	 	HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetBufPhyAddr Para Error Exit\n");
	 	return NULL;
	 }
	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)u32Reader;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetBufPhyAddr Para Error Exit\n");
        return NULL;
    }

     if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetBufPhyAddr g_pBuf NULL!\n");
        return NULL;
    }
    
    return g_pBuf[u32Index]->BUF_GetBufAddr();
    
}

//return onewhole frame pointer    --vinsent
 HI_S32 VS_BUF_GetFramePtr(HI_S32 s32ReaderId,
                       BUF_POSITION_POLICY_E enPolicy,
                       HI_S32 s32N,
                       VS_FRAME_TYPE_E *penFrameType,
                       HI_U8 **pu8Start,
                       HI_U32 * Pu8StartOffset,
                       HI_U32 *pu32Len,
                       HI_U64 *pu64Pts,
                       HI_U32 * pu32PacketNo,
                       HI_S32 * ps32Width,
                       HI_S32 * ps32Height,
                       HI_U8 	  u8IOblock)
{
    if (enPolicy >= BUF_POSITION_BUTT || enPolicy < 0
        || NULL == penFrameType
        || NULL == pu8Start
        || NULL == pu32Len )
    {
        printf("#### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetFrame para erro readid:%d\n", s32ReaderId);
        return HI_EPAERM;
    }

    //printf("#### %s %d\n", __FUNCTION__, __LINE__);
    HI_S32 s32Ret = HI_SUCCESS;
	HI_U32 nHeaderLength = 0;
    *pu32Len = 0;
    HI_U8 *pu8FrameHeader = NULL;
	HI_U8 *pu8Frame = NULL;

GetHeader:
	if(	BUF_POSITION_CUR_READ == enPolicy || BUF_POSITION_CUR_WRITE == enPolicy)
	{
        //printf("#### %s %d\n", __FUNCTION__, __LINE__);
		BUF_READPTR_INFO_S stReaderInfo;
	    //check the reset buffer is enough for hearder
	    s32Ret = VS_BUF_GetReadPtrPos(s32ReaderId ,enPolicy , s32N , &stReaderInfo);
	    if (s32Ret )
		{
            printf("#### %s %d\n", __FUNCTION__, __LINE__);
			printf("%s %d Return %d\n",__FUNCTION__,__LINE__,s32Ret);
			return HI_EINTER;
		}
		
	    if(stReaderInfo.u32BufferSize - stReaderInfo.u32ReadOffset < sizeof(VIDEO_HEAD_S)  ) //ʣ��ռ䲻��֡ͷ��С
	    {
            //printf("#### %s %d\n", __FUNCTION__, __LINE__);
            s32Ret = VS_BUF_SetReadPtrPos(s32ReaderId , stReaderInfo.u32BufferSize - stReaderInfo.u32ReadOffset ); //������������
            if(s32Ret )
            {
                printf("#### %s %d\n", __FUNCTION__, __LINE__);
                printf("LINE .%d BUF_SetReadPtrPos failed \n" , __LINE__);
                return HI_EINTER;
            }
			//printf("jump the left buffer\n");
	    }
	}
    //get header pointer  -- Vinsent.Mo
    unsigned int u32MaxHeaderLen = 0;
    u32MaxHeaderLen = sizeof(VIDEO_HEAD_S) > sizeof(AUDIO_HEAD_S) ? sizeof(VIDEO_HEAD_S)  : sizeof(AUDIO_HEAD_S) ;
	s32Ret = BUF_GetDataPoint(s32ReaderId, enPolicy, s32N,&pu8FrameHeader, u32MaxHeaderLen , u8IOblock);
    //printf("#### %s %d\n", __FUNCTION__, __LINE__);
	if(s32Ret == BUF_ERR_EMPTY)
	{
        //printf("#### %s %d\n", __FUNCTION__, __LINE__);
		return HI_EEMPTY;
	}
	else if(s32Ret < 0)
	{
		printf("BUF_GetDataPoint failed \n");
		return HI_EINTER;
	}
	HI_S32 s32FrameLenth = 0;
	HI_S32 s32RealFrameLenth = 0;
	/*�ж�֡ͷ����*/
    if(pu8FrameHeader[2] == 'w' && pu8FrameHeader[3] == 'b')
    {
		AUDIO_HEAD_S *lpFrameA = (AUDIO_HEAD_S *)pu8FrameHeader;
        *penFrameType = VS_FRAME_A;
        s32FrameLenth = ((lpFrameA->u16FrameLen + 7) >> 3) * 8;
        s32RealFrameLenth = lpFrameA->u16FrameLen ;
        *pu64Pts = lpFrameA->u64Pts;
        *pu32PacketNo = lpFrameA->u32PacketNo;
		nHeaderLength = sizeof(AUDIO_HEAD_S);
    }			
	else if(memcmp(pu8FrameHeader + 1, "1dcH264", 7) == 0)
	{
		VIDEO_HEAD_S *lpFrameP = (VIDEO_HEAD_S *)pu8FrameHeader;
        *penFrameType = VS_FRAME_P;
        s32FrameLenth = ((lpFrameP->u32FrameLen + 7) >> 3) * 8;
        s32RealFrameLenth = lpFrameP->u32FrameLen ;
        *pu64Pts = lpFrameP->u64Pts;
        *pu32PacketNo  = lpFrameP->u32PacketNo;
		nHeaderLength = sizeof(VIDEO_HEAD_S);
	}
	else if(memcmp(pu8FrameHeader + 1, "0dcH264", 7) == 0)
    {
		VIDEO_HEAD_S *lpFrameI = (VIDEO_HEAD_S *)pu8FrameHeader;
        *penFrameType = VS_FRAME_I;
        s32FrameLenth = ((lpFrameI->u32FrameLen + 7) >> 3 ) * 8;
        s32RealFrameLenth = lpFrameI->u32FrameLen ;
        *pu64Pts = lpFrameI->u64Pts;
        *pu32PacketNo  = lpFrameI->u32PacketNo;
		nHeaderLength = sizeof(VIDEO_HEAD_S);
    }
    else if(memcmp(pu8FrameHeader + 2, "dcdumy", 6) == 0 )
    {
		DUMMY_HEAD_S *pstDummyHead = (DUMMY_HEAD_S *)pu8FrameHeader;
		s32FrameLenth = pstDummyHead->u32FrameLen ;
		nHeaderLength = sizeof(DUMMY_HEAD_S) ;
		s32Ret = BUF_GetDataPoint(s32ReaderId, enPolicy, 0,&pu8Frame, s32FrameLenth + nHeaderLength , u8IOblock);
		if(s32Ret == BUF_ERR_EMPTY)
		{
			return HI_EEMPTY;
		}
	    else if(s32Ret < 0)
	    {
	        printf("BUF_GetDataPoint failed \n");
	        return HI_EINTER;
	    }

	    s32Ret = VS_BUF_SetReadPtrPos(s32ReaderId , s32FrameLenth + nHeaderLength);
		if(s32Ret )
		{
		    printf("BUF_SetReadPtrPos failed \n");
		    return HI_EINTER;
		}

		goto GetHeader;
    }
    else
    {       
        printf("read data frame type failed  s32ReaderId %d enPolicy %d \n" , s32ReaderId , enPolicy);
        enPolicy = BUF_POSITION_LAST_WRITE_nIFRAME;  //����Ҳ���֡ͷ���ݣ���������I֡
        goto GetHeader;
	  	return HI_EINTER;
    }
 #if 0
	if(*penFrameType == VS_FRAME_A)
	{
	    VS_BUF_CheckReaderPacketNo(s32ReaderId, HI_FALSE , *pu32PacketNo );
    }
    else
    {
    	VS_BUF_CheckReaderPacketNo(s32ReaderId, HI_TRUE , *pu32PacketNo );
    }
 #endif
	*pu8Start = pu8FrameHeader + nHeaderLength;
	*pu32Len = s32RealFrameLenth;
	HI_U8 *u32BufAddr = NULL;
	u32BufAddr = VS_BUF_GetBufAddr(s32ReaderId);
	*Pu8StartOffset = (pu8FrameHeader + nHeaderLength)-u32BufAddr ;
	if(enPolicy == BUF_POSITION_LAST_READ_nIFRAME || enPolicy == BUF_POSITION_LAST_WRITE_nIFRAME)
		enPolicy = BUF_POSITION_CUR_READ;
	s32Ret = BUF_GetDataPoint(s32ReaderId, enPolicy, 0,&pu8Frame, s32FrameLenth + nHeaderLength , u8IOblock);
    if(s32Ret == BUF_ERR_EMPTY)
	{
        printf("#### %s %d\n", __FUNCTION__, __LINE__);
		return HI_EEMPTY;
	}
	else if(s32Ret < 0)
	{
        printf("BUF_GetDataPoint failed \n");
        return HI_EINTER;
	}
    //printf("#### %s %d\n", __FUNCTION__, __LINE__);
	//move the read poiter --vinsent
    s32Ret = VS_BUF_SetReadPtrPos(s32ReaderId , s32FrameLenth + nHeaderLength);
    if(s32Ret )
    {
        printf("VS_BUF_SetReadPtrPos failed \n");
        return HI_EINTER;
    }
    //printf("#### %s %d\n", __FUNCTION__, __LINE__);
	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
	*ps32Height = pstReaderInfo->s32Heitht;
	*ps32Width = pstReaderInfo->s32With;

    return 0;
}

 HI_S32 VS_BUF_GetNextFrameType(HI_S32 s32ReaderId,
                       BUF_POSITION_POLICY_E enPolicy,
                       HI_S32 s32N,
                       VS_FRAME_TYPE_E *penFrameType,
                       HI_U8 	  u8IOblock)
{
	  if (enPolicy >= BUF_POSITION_BUTT || enPolicy < 0|| NULL == penFrameType)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetNextFrameType para erro readid:%d\n", s32ReaderId);
        return HI_EPAERM;
    }
    HI_S32 s32Ret = HI_SUCCESS;
	HI_U32 nHeaderLength = 0;
    HI_U8 *pu8FrameHeader = NULL;
	HI_U8 *pu8Frame = NULL;
    GetHeader:
	if(	BUF_POSITION_CUR_READ == enPolicy || BUF_POSITION_CUR_WRITE == enPolicy)
	{
    
		BUF_READPTR_INFO_S stReaderInfo;
	    //check the reset buffer is enough for hearder
	    s32Ret = VS_BUF_GetReadPtrPos(s32ReaderId ,enPolicy , s32N , &stReaderInfo);
	    if (s32Ret )
		{
			printf("%s %d Return %d\n",__FUNCTION__,__LINE__,s32Ret);
			return HI_EINTER;
		}
		
	    if(stReaderInfo.u32BufferSize - stReaderInfo.u32ReadOffset < sizeof(VIDEO_HEAD_S)  ) //ʣ��ռ䲻��֡ͷ��С
	    {
			s32Ret = VS_BUF_SetReadPtrPos(s32ReaderId , stReaderInfo.u32BufferSize - stReaderInfo.u32ReadOffset ); //������������
			 if(s32Ret )
			{
			    printf("LINE .%d BUF_SetReadPtrPos failed \n" , __LINE__);
			    return HI_EINTER;
			}
	    }
	}
    unsigned int u32MaxHeaderLen = 0;
    u32MaxHeaderLen = sizeof(VIDEO_HEAD_S) > sizeof(AUDIO_HEAD_S) ? sizeof(VIDEO_HEAD_S)  : sizeof(AUDIO_HEAD_S) ;
	s32Ret = BUF_GetDataPoint(s32ReaderId, enPolicy, s32N,&pu8FrameHeader, u32MaxHeaderLen , u8IOblock);
	if(s32Ret == BUF_ERR_EMPTY)
	{
		return HI_EEMPTY;
	}
	else if(s32Ret < 0)
	{
		printf("BUF_GetDataPoint failed \n");
		return HI_EINTER;
	}
	HI_S32 s32FrameLenth = 0;
	/*�ж�֡ͷ����*/
    if(pu8FrameHeader[2] == 'w' && pu8FrameHeader[3] == 'b')
    {
        *penFrameType = VS_FRAME_A;

    }			
	else if(memcmp(pu8FrameHeader + 1, "1dcH264", 7) == 0)
	{
        *penFrameType = VS_FRAME_P;
	}
	else if(memcmp(pu8FrameHeader + 1, "0dcH264", 7) == 0)
    {
        *penFrameType = VS_FRAME_I;
    }
    else if(memcmp(pu8FrameHeader + 2, "dcdumy", 6) == 0 )
    {
    
    		DUMMY_HEAD_S *pstDummyHead = (DUMMY_HEAD_S *)pu8FrameHeader;
			s32FrameLenth = pstDummyHead->u32FrameLen ;
			nHeaderLength = sizeof(DUMMY_HEAD_S) ;
    		s32Ret = BUF_GetDataPoint(s32ReaderId, enPolicy, 0,&pu8Frame, s32FrameLenth + nHeaderLength , u8IOblock);
    		if(s32Ret == BUF_ERR_EMPTY)
    		{
    			return HI_EEMPTY;
    		}
		else if(s32Ret < 0)
		{
		    printf("BUF_GetDataPoint failed \n");
		    return HI_EINTER;
		}

	     s32Ret = VS_BUF_SetReadPtrPos(s32ReaderId , s32FrameLenth + nHeaderLength);
		 if(s32Ret )
		{
		    printf("BUF_SetReadPtrPos failed \n");
		    return HI_EINTER;
		}

		goto GetHeader;
    }
    else
    {       
	  	 return HI_EINTER;
    }
	return 0;
}
 
/*********************************************************************
    Function:   VS_BUF_GetReadPtrPos
    Description:��ȡ��ָ��λ��
    Calls:
    Called By:
    parameter:
            [in] HI_S32 s32ReaderId  ��ָ��ID
            [in] VS_BUF_POSITION_POLICY_E enPolicy  ��ȡ��ָ�뷽ʽ
            [in] HI_S32 s32N  ���I֡��
            [out] VS_BUF_READPTR_INFO_S *pstReadptr ���ض�ָ��λ����Ϣ
    Return: HI_SUCCESS
    Author:
********************************************************************/
inline HI_S32 VS_BUF_GetReadPtrPos(HI_S32 s32ReaderId,
                           BUF_POSITION_POLICY_E enPolicy,
                           HI_S32 s32N,
                           BUF_READPTR_INFO_S *pstReadptr)
{
    /*����������*/
	HI_S32 s32Ret;

    //printf("#### %s %d\n", __FUNCTION__, __LINE__);

    if (s32ReaderId == 0)
    {
        printf("######## %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReadPtrPos Para erro!\n");
        return HI_EPAERM;
    }

	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_S32 s32BufferReaderID = pstReaderInfo->s32BufferReaderID;
    HI_U32 u32Index = pstReaderInfo->s32Index ;

    //printf("#### %s %d, BufferReaderID=%d, s32Index=%d, s32Heitht=%d, s32With=%d\n",
    //            __FUNCTION__, __LINE__, pstReaderInfo->s32BufferReaderID, pstReaderInfo->s32Index, pstReaderInfo->s32Heitht, pstReaderInfo->s32With);
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        printf("######## %s %d, u32Index=%d\n", __FUNCTION__, __LINE__, u32Index);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReadPtrPos Para erro!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        printf("#### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReadPtrPos g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }
	if(enPolicy == BUF_POSITION_CUR_READ)
	{
        //printf("#### %s %d\n", __FUNCTION__, __LINE__);
		s32Ret = g_pBuf[u32Index]->BUF_GetReadPtrPos(s32BufferReaderID,
			BUF_POSITION_CUR_READ,s32N,(BUF_READPTR_INFO_S*)pstReadptr);
	}
	else
	{
        //printf("#### %s %d\n", __FUNCTION__, __LINE__);
		g_pBuf[u32Index]->BUF_Lock();
		s32Ret = g_pBuf[u32Index]->BUF_GetReadPtrPos(s32BufferReaderID,
			(BUF_POSITION_POLICY_E)enPolicy,s32N,(BUF_READPTR_INFO_S*)pstReadptr);
		g_pBuf[u32Index]->BUF_Unlock();
	}

    //printf("#### %s %d\n", __FUNCTION__, __LINE__);
    return s32Ret;
}


/*********************************************************************
    Function:   VS_BUF_CanRead
    Description:�����Ƿ��ܶ�
    Calls:
    Called By:
    parameter:
            [in] HI_S32 s32ReaderId  ��ָ��ID
            [in] HI_U32 u32Len ����
    Return: ���ؿ������ݳ��ȣ����ܺ���������ݳ��Ȳ�һ��
    Author:
********************************************************************/
HI_S32 VS_BUF_CanRead(HI_S32 s32ReaderId,
                     HI_U32 u32Len)
{
    /*����������*/

    if (s32ReaderId == 0)
    {
        printf("#### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_CanRead Para erro\n");
        return HI_EPAERM;
    }

	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_S32 s32BufferReaderID = pstReaderInfo->s32BufferReaderID;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        printf("#### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_CanRead Para erro!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        printf("#### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_CanRead g_pBuf NULL\n");
        return HI_ENOTINIT;
    }
    //printf("#### %s %d\n", __FUNCTION__, __LINE__);
	//g_pBuf[u32Index]->BUF_Lock();
    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_CanRead(s32BufferReaderID, u32Len);
	//g_pBuf[u32Index]->BUF_Unlock();
    return s32Ret;
}

HI_S32 VS_BUF_CheckReaderPacketNo(HI_S32 s32ReaderId,
                     HI_BOOL bVideo , HI_U32 u32PacketNo)
{
    /*����������*/
    if (s32ReaderId == 0)
    {
        printf("####################################### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_CheckReaderPacketNo Para erro\n");
        return HI_EPAERM;
    }
	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_S32 s32BufferReaderID = pstReaderInfo->s32BufferReaderID;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_CheckReaderPacketNo Para erro!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_CheckReaderPacketNo g_pBuf NULL\n");
        return HI_ENOTINIT;
    }
    
    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_CheckReaderPacketNo(s32BufferReaderID, bVideo , u32PacketNo);
    
    return s32Ret;
}


/*********************************************************************
    Function:   VS_BUF_SetReadPtrPos
    Description:���ö�ָ��λ��
    Calls:
    Called By:
    parameter:
            [in] HI_S32 s32ReaderId  ��ָ��ID
            [in] HI_U32 u32Len   ����
    Return: HI_SUCCESS
    Author:
********************************************************************/
inline HI_S32 VS_BUF_SetReadPtrPos(HI_S32 s32ReaderId,
                               HI_U32 u32Len)
{

    /*����������*/
    if (s32ReaderId == 0)
    {
        printf("####################################### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "BUF_SetReadPtrPos Para erro!\n");
        return HI_EPAERM;
    }

	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_S32 s32BufferReaderID = pstReaderInfo->s32BufferReaderID;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "BUF_SetReadPtrPos Para erro!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "BUF_SetReadPtrPos g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }
	//g_pBuf[u32Index]->BUF_Lock();
    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_SetReadPtrPos(s32BufferReaderID,
                                                           u32Len);
	//g_pBuf[u32Index]->BUF_Unlock();
    return s32Ret;
}


/*********************************************************************
    Function:   VS_BUF_GetReadPtrLeftNum
    Description:��ȡ��ָ����дָ��֮��֡������I֡����������
                ������Э���ⲿ�Ĳ��ſ��ƻ���������
    Calls:
    Called By:
    parameter:
            [in] HI_S32 s32ReaderId  ��ָ��ID
            [out] HI_U32 *pu32IFrameNum  I֡����
            [out] HI_U32 *pu32LeaveCount ʣ�����ݳ���
    Return: HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_GetReadPtrLeftNum(HI_S32 s32ReaderId,
                                HI_U32 *pu32LeaveCount)
{
    printf("######## %s %d\n", __FUNCTION__, __LINE__);
    /*����������*/
    if (s32ReaderId == 0
        || NULL == pu32LeaveCount)
    {
        printf("####################################### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReadPtrLeftNum Para erro!\n");
        return HI_EPAERM;
    }
	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_S32 s32BufferReaderID = pstReaderInfo->s32BufferReaderID;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        printf("######## %s %d, u32Index=%d\n", __FUNCTION__, __LINE__, u32Index);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReadPtrLeftNum Para erro\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReadPtrLeftNum g_pBuf NULL\n");
        return HI_ENOTINIT;
    }
	g_pBuf[u32Index]->BUF_Lock();
    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_GetReadPtrLeftNum(s32BufferReaderID,
                                                            pu32LeaveCount);
	g_pBuf[u32Index]->BUF_Unlock();
    return s32Ret;
}


/*********************************************************************
    Function:   VS_BUF_GetReaderStreamAttr
    Description:��ȡ��ָ�����������
    Calls:
    Called By:
    parameter:
            [in] s32ReaderId  ��ָ��ID
            [out] pstStreamAttr  ������������
    Return: HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_GetReaderStreamAttr(HI_S32 s32ReaderId,
                                     BUF_STREAM_ATTR_S *pstStreamAttr)
{
    /*����������*/
    if (s32ReaderId == 0
        || NULL == pstStreamAttr)
    {
        printf("####################################### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReaderStreamAttr Para erro!\n");
        return HI_EPAERM;
    }
	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_S32 s32BufferReaderID = pstReaderInfo->s32BufferReaderID;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReaderStreamAttr Para erro!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetReaderStreamAttr g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }

    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_GetReaderStreamAttr(s32BufferReaderID,
                                         (BUF_STREAM_ATTR_S *)pstStreamAttr);
    return s32Ret;
}



/*********************************************************************
    Function:   VS_BUF_SetStreamAttr
    Description:����Buffer��������
    Calls:
    Called By:
    parameter:
            [in] s32Chn Դͨ����
            [in] enStreamType ��������
            [in] stStreamAttr  ��������
    Return: HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_SetStreamAttr(const HI_S32 s32Chn,
                            const VS_STREAM_TYPE_E enStreamType,
                            const BUF_STREAM_ATTR_S *pstStreamAttr)
{
    /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT
        || NULL == pstStreamAttr)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_SetStreamAttr CBuffer Exit!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_SetStreamAttr g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }
    
    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_SetStreamAttr((BUF_STREAM_ATTR_S *)pstStreamAttr);
    return s32Ret;
}


/*********************************************************************
    Function:   VS_BUF_GetStreamAttr
    Description:��ȡ��������
    Calls:
    Called By:
    parameter:
            [in] s32Chn Դͨ����
            [in] enStreamType ��������
            [out] pstStreamAttr  ������������
    Return: HI_SUCCESS
    Author:
********************************************************************/
HI_S32 VS_BUF_GetStreamAttr(const HI_S32 s32Chn,
                               const VS_STREAM_TYPE_E enStreamType,
                               BUF_STREAM_ATTR_S *pstStreamAttr)
{
    /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT
        || NULL == pstStreamAttr)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetStreamAttr CBuffer Exit\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetStreamAttr g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }

    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_GetStreamAttr((BUF_STREAM_ATTR_S *)pstStreamAttr);
    return s32Ret;
}

HI_S32 VS_BUF_GetStreamAttrByReaderId(HI_S32 s32ReaderId,BUF_STREAM_ATTR_S *pstStreamAttr)
{
    /*����������*/
    if(NULL == pstStreamAttr || s32ReaderId == 0)
    {
        printf("####################################### %s %d\n", __FUNCTION__, __LINE__);
    	HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetStreamAttr Para Error Exit\n");
        return HI_EPAERM;
    }
	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT
        || NULL == pstStreamAttr)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetStreamAttr CBuffer Exit\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetStreamAttr g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }

    HI_S32 s32Ret = g_pBuf[u32Index]->BUF_GetStreamAttr((BUF_STREAM_ATTR_S *)pstStreamAttr);
    return s32Ret;
}




HI_U32 VS_BUF_GetBufPhyAddr(const HI_S32 s32Chn,const VS_STREAM_TYPE_E enStreamType)
{
	 /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetBufPhyAddr Para Error Exit\n");
        return 0;
    }

     if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetBufPhyAddr g_pBuf NULL!\n");
        return 0;
    }
    
    return g_pBuf[u32Index]->BUF_GetBufPhyAddr();
    
}

HI_U32 VS_BUF_GetBufSize(const HI_S32 s32Chn,const VS_STREAM_TYPE_E enStreamType)
{
	 /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetBufSize Para Error Exit\n");
        return 0;
    }

     if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetBufSize g_pBuf NULL!\n");
        return 0;
    }
    
    return g_pBuf[u32Index]->BUF_GetBufSize();
    
}

HI_U32 VS_BUF_GetBufIndex(HI_S32 s32ReaderId)
{

	DMSReaderInfo *pstReaderInfo = (DMSReaderInfo *)s32ReaderId;
    HI_U32 u32Index = pstReaderInfo->s32Index ;
    
    return u32Index;
    
}

unsigned char * VS_BUF_GetWriteMemPos(const HI_S32 s32Chn,const VS_STREAM_TYPE_E enStreamType , HI_U32 u32Size)
{
	 /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetWriteMemPos Para Error Exit\n");
        return 0;
    }

     if (NULL == g_pBuf[u32Index])
    {
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetWriteMemPos g_pBuf NULL!\n");
        return 0;
    }
    g_pBuf[u32Index]->BUF_Lock();
    u32Size += sizeof(VIDEO_HEAD_S);
    unsigned char * pMemAddr = NULL;
    pMemAddr = g_pBuf[u32Index]->BUF_GetWriteMemPos(u32Size);
    if(NULL == pMemAddr)
    {
		g_pBuf[u32Index]->BUF_Unlock();
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_GetWriteMemPos pMemAddr NULL!\n");
        return 0;
    }
    pMemAddr +=sizeof(VIDEO_HEAD_S);
    
    return pMemAddr;
    
}

HI_S32 VS_BUF_ReleaseWriteMemPos(const HI_S32 s32Chn,
                         const VS_STREAM_TYPE_E enStreamType,
                         VS_FRAME_TYPE_E enFrameType,
                         HI_U32 u32Len,
                         HI_U64 u64Pts,
                         VS_DATETIME_S *pTime)
{
	HI_S32 s32Ret = HI_SUCCESS;
    /*����������*/
    HI_U32 u32Index = s32Chn + enStreamType * MAX_CHANNEL_NUM;
    if (u32Index >= MAX_CHANNEL_NUM * VS_STREAM_TYPE_BUTT)
    {
        printf("#### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_ReleaseWriteMemPos CBuffer Exit!\n");
        return HI_EPAERM;
    }
    if (NULL == g_pBuf[u32Index])
    {
        printf("#### %s %d\n", __FUNCTION__, __LINE__);
        HI_Debug("Buffer", LOG_LEVEL_ERR, "VS_BUF_ReleaseWriteMemPos g_pBuf NULL!\n");
        return HI_ENOTINIT;
    }
    
	if( 0 == u32Len)
		goto out;
		
    if (VS_FRAME_A == enFrameType)
    {
        s32Ret = g_pBuf[u32Index]->BUF_WriteAudioData(NULL,
                                    u32Len,
                                    s32Chn,
                                    u64Pts);
    }
    else
    {
        //printf("#### %s %d\n", __FUNCTION__, __LINE__);
        s32Ret = g_pBuf[u32Index]->BUF_WriteVideoData(NULL,
                                    u32Len,
                                    (VS_FRAME_TYPE_E)enFrameType,
                                    pTime,
                                    s32Chn,
                                    u64Pts);
    }
	
	if(dmsEvent[u32Index])
		SetEvent(dmsEvent[u32Index]);
		
out:
	g_pBuf[u32Index]->BUF_Unlock();	
	
    return s32Ret;
}




