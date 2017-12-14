/****
*
*
*
****/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "QMAPIAV.h"
#include "QMAPIType.h"
#include "QMAPIErrno.h"
#include "QMAPIDataType.h"
#include "QMAPIErrno.h"
#include "MediaBuffer.h"
#include "MediaBufferErrno.h"
#include "Q3AV.h"
#include "basic.h"

#define VS_MAIN_BUF_SIZE 		 	(256*1024)
#define VS_NET_BUF_SIZE 			(128*1024) 	/* KBytes */
#define VS_MOBILE_BUF_SIZE 			(64*1024)	/* KBytes */

#define VS_MAX_MAIN_BUF_TIME 		8
#define VS_MAX_NET_BUF_TIME 		5
#define VS_MAX_MOBILE_BUF_TIME 	4

/* main stream min bitrate */
#define VS_MAINSTREAM_BITRATE_MIN    (512*1024)

/* main stream max bitrate */
#define VS_MAINSTREAM_BITRATE_MAX   (8192*1024)

/* sub stream min bitrate */
#define VS_SUBSTREAM_BITRATE_MIN 	    (256*1024)

/* sub stream max bitrate */
#define VS_SUBSTREAM_BITRATE_MAX	    (1024*1024)

/* mobile stream min bitrate */
#define VS_MOBILESTREAM_BITRATE_MIN    (16*1024)

/* mobile stream max bitrate */
#define VS_MOBILESTREAM_BITRATE_MAX	(512*1024)


void StreamGetBufBlockInfo(VS_STREAM_TYPE_E enStreamType, DEVICE_TYPE_E enDeviceType, unsigned int *pu32BlockNum, unsigned int* pu32BlockSize)
{
	unsigned int u32BufNum = 0;
	  
	if(VS_STREAM_TYPE_MAIN == enStreamType)
	{
		//TODO: should malloc mediabuffer depend on bitrate, not resolution
        if ((enDeviceType == QMAPI_VIDEO_FORMAT_1080P) || (enDeviceType == QMAPI_VIDEO_FORMAT_960P) 
                || (enDeviceType == QMAPI_VIDEO_FORMAT_720P) || enDeviceType == (QMAPI_VIDEO_FORMAT_300H))
		{
			//*pu32BlockSize = VS_MAIN_BUF_SIZE;
			//u32BufNum = VS_MAINSTREAM_BITRATE_MAX * VS_MAX_MAIN_BUF_TIME/8/VS_MAIN_BUF_SIZE;
			*pu32BlockSize = VS_MAIN_BUF_SIZE;
			u32BufNum = VS_MAINSTREAM_BITRATE_MAX * VS_MAX_MAIN_BUF_TIME/8/VS_MAIN_BUF_SIZE/4;
			if((0 != ((VS_MAINSTREAM_BITRATE_MAX * VS_MAX_MAIN_BUF_TIME/8)%VS_MAIN_BUF_SIZE)) ||0 == u32BufNum)
			{
				u32BufNum += 1;
			}
		}
		else
		{
			*pu32BlockSize = VS_NET_BUF_SIZE;
			u32BufNum = VS_SUBSTREAM_BITRATE_MAX * VS_MAX_NET_BUF_TIME/8/VS_NET_BUF_SIZE;
			if((0 != ((VS_SUBSTREAM_BITRATE_MAX * VS_MAX_NET_BUF_TIME/8)%VS_NET_BUF_SIZE)) ||
			(0 == u32BufNum))
			{
				u32BufNum += 1;
			}
		}
	}
	else if(VS_STREAM_TYPE_NETSUB == enStreamType)
	{
		*pu32BlockSize = VS_NET_BUF_SIZE;	
		u32BufNum = VS_SUBSTREAM_BITRATE_MAX * VS_MAX_NET_BUF_TIME/8/VS_NET_BUF_SIZE;
		if((0 != ((VS_SUBSTREAM_BITRATE_MAX * VS_MAX_NET_BUF_TIME/8)%VS_NET_BUF_SIZE)) ||
			(0 == u32BufNum))
		{
			u32BufNum += 1;
		}
	}
	else if(VS_STREAM_TYPE_MOBILE == enStreamType)
	{
		*pu32BlockSize = VS_MOBILE_BUF_SIZE;			
		u32BufNum = VS_MOBILESTREAM_BITRATE_MAX * VS_MAX_MOBILE_BUF_TIME/8/VS_MOBILE_BUF_SIZE;
		if((0 != ((VS_MOBILESTREAM_BITRATE_MAX * VS_MAX_MOBILE_BUF_TIME/8)%VS_MOBILE_BUF_SIZE)) ||
			(0 == u32BufNum))
		{
			u32BufNum += 1; 
		}
	}
	else if(VS_STREAM_TYPE_SNAP == enStreamType)
	{
		*pu32BlockSize = VS_MOBILE_BUF_SIZE;			
		u32BufNum = VS_MOBILESTREAM_BITRATE_MAX * VS_MAX_MOBILE_BUF_TIME/8/VS_MOBILE_BUF_SIZE;
		if((0 != ((VS_MOBILESTREAM_BITRATE_MAX * VS_MAX_MOBILE_BUF_TIME/8)%VS_MOBILE_BUF_SIZE)) ||
			(0 == u32BufNum))
		{
			u32BufNum += 1; 
		}
	}
	else
	{
		*pu32BlockSize = VS_MAIN_BUF_SIZE;	
		u32BufNum = 1;
	}

	if(u32BufNum == 1)
	{
		u32BufNum = 2; 
	}

	*pu32BlockNum = u32BufNum;
}

/*********************************************************************
    Function:   QMAPI_AVServer_Init
    Description: ��ʼ������Ƶ����,��ʼ������Ƶbuffer
    Calls:
    Called By:
    parameter:
            [in] lpDeafultParam QMAPI_NET_CHANNEL_PIC_INFO
            [in] Resolution
    Return: ģ����
********************************************************************/
int QMAPI_AVServer_Init(void *lpDeafultParam, int Resolution)
{
	int i;
	unsigned int u32BlockNum, u32BlockSize;
     int ManBlockSize = 0, SubBlockSize = 0;
	BUF_STREAM_ATTR_S stStreamInfo;
	QMAPI_NET_CHANNEL_PIC_INFO *Param = (QMAPI_NET_CHANNEL_PIC_INFO *)lpDeafultParam;

	memset(&stStreamInfo ,  0 , sizeof(stStreamInfo));
	
	VS_BUF_Init();
	for (i=0; i<QMAPI_MAX_CHANNUM; i++)
	{
		StreamGetBufBlockInfo(VS_STREAM_TYPE_MAIN, Param->stRecordPara.dwStreamFormat, &u32BlockNum, &u32BlockSize);
		VS_BUF_Create(i, VS_STREAM_TYPE_MAIN , u32BlockSize, u32BlockNum);
		printf("#### %s %d, u32BlockSize=%d, u32BlockNum=%d\n", __FUNCTION__, __LINE__, u32BlockSize, u32BlockNum);
		stStreamInfo.u32Height = Get_Q3_Vi_Height(QMAPI_PAL, Param->stRecordPara.dwStreamFormat);
        stStreamInfo.u32Width = Get_Q3_Vi_Width(QMAPI_PAL, Param->stRecordPara.dwStreamFormat);
        VS_BUF_SetStreamAttr(i, VS_STREAM_TYPE_MAIN, &stStreamInfo);
        ManBlockSize = u32BlockSize * u32BlockNum;
          
		StreamGetBufBlockInfo(VS_STREAM_TYPE_NETSUB, Param->stNetPara.dwStreamFormat, &u32BlockNum, &u32BlockSize);
		VS_BUF_Create(i, VS_STREAM_TYPE_NETSUB , u32BlockSize, u32BlockNum);
		printf("#### %s %d, u32BlockSize=%d, u32BlockNum=%d\n", __FUNCTION__, __LINE__, u32BlockSize, u32BlockNum);
		stStreamInfo.u32Height = Get_Q3_Vi_Height(QMAPI_PAL, Param->stNetPara.dwStreamFormat);
        stStreamInfo.u32Width = Get_Q3_Vi_Width(QMAPI_PAL, Param->stNetPara.dwStreamFormat);
        VS_BUF_SetStreamAttr(i, VS_STREAM_TYPE_NETSUB, &stStreamInfo);
        SubBlockSize = u32BlockSize * u32BlockNum;
	}

	/** ��ʼ��������� **/
    Q3_Codec_Init(Param, Resolution, ManBlockSize, SubBlockSize);

    return 0;
}

/*********************************************************************
Function:   QMAPI_AVServer_Init
Description: ����ʼ������Ƶ����,����ʼ������Ƶbuffer
Calls:
Called By:
parameter:
            [in] Handle ģ����
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AVServer_UnInit(int Handle)
{
	int i;

    Q3_Codec_Deinit();

	for (i=0; i<QMAPI_MAX_CHANNUM; i++) {
		VS_BUF_Destroy(i, VS_STREAM_TYPE_MAIN);
		VS_BUF_Destroy(i, VS_STREAM_TYPE_NETSUB);
	}
	VS_BUF_Exit();
	
    return 0;
}

/*********************************************************************
    Function:   QMAPI_AVServer_Start
    Description: ��������Ƶ����
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
            [in] VidoeCount ��Ƶ�����򿪸�����1<<0������QMAPI_MAIN_STREAM��1<<1������QMAPI_SECOND_STREAM
            [in] Audio ��Ƶ��,1 ����0 ��
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AVServer_Start(int Handle, int VidoeCount)
{	
    /** ��ʼ����������buffer��ע�������ص����� **/
   	if ((VidoeCount & (1<<QMAPI_MAIN_STREAM)) == (1<<QMAPI_MAIN_STREAM)) {
        Q3_Video_Start(QMAPI_MAIN_STREAM);
	}

	/** ��ʼ����������buffer��ע�������ص����� **/
   	if ((VidoeCount & (1<<QMAPI_SECOND_STREAM)) == (1<<QMAPI_SECOND_STREAM)) {
        Q3_Video_Start(QMAPI_SECOND_STREAM);
	}

    return 0;
}

/*********************************************************************
Function:   QMAPI_AVServer_Stop
Description: �ر�����Ƶ����
Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AVServer_Stop(int Handle)
{
    Q3_Video_Stop(QMAPI_SECOND_STREAM);
    Q3_Video_Stop(QMAPI_MAIN_STREAM);
	
    return 0;
}

/*********************************************************************
    Function:   QMAPI_AVServer_IOCtrl
    Description: ��������Ƶ�������
    Calls:
    Called By:
    parameter:
            [in] Handle ���ƾ��
            [in] nCmd ��������
                    ��ЧֵΪ: QMAPI_SYSCFG_GET_PICCFG/QMAPI_SYSCFG_SET_PICCFG/QMAPI_SYSCFG_GET_DEF_PICCFG
            [in/out] lpInParam QMAPI_NET_CHANNEL_PIC_INFO
            [in/out] nSize ���ýṹ���С
    Return: QMAPI_SUCCESS/QMAPI_FAILURE/QMAPI_ERR_UNKNOW_COMMNAD
********************************************************************/
int QMAPI_AVServer_IOCtrl(int Handle, int nCmd, int nChannel, void *lpInParam, int nInSize)
{
    int ret = QMAPI_FAILURE;


#if 0
    /** Ŀǰ��֧�����������֣�֮���������صĻص��ӿ� **/
    if(QMAPI_SYSCFG_GET_PICCFG != nCmd
        && QMAPI_SYSCFG_SET_PICCFG != nCmd
        && QMAPI_SYSCFG_GET_DEF_PICCFG != nCmd
        && QMAPI_NET_STA_GET_SPSPPSENCODE_DATA != nCmd)
    {
        printf("<fun:%s>-<line:%d>, unspport cmd!\n", __FUNCTION__, __LINE__);
        return QMAPI_ERR_UNKNOW_COMMNAD;
    }
#endif

   	switch(nCmd)
   	{
		case QMAPI_SYSCFG_SET_PICCFG:
		{
			if (Q3_Video_StreamPIC_Set((QMAPI_NET_CHANNEL_PIC_INFO *)lpInParam) == 0)
			{
				ret = QMAPI_SUCCESS;
			}
			break;
		}
		case QMAPI_NET_STA_GET_SPSPPSENCODE_DATA:
		{
			QMAPI_NET_SPSPPS_BASE64ENCODE_DATA *pSpsppsInfo = (QMAPI_NET_SPSPPS_BASE64ENCODE_DATA*)lpInParam;
			if (pSpsppsInfo)
			{
		        char *pBuff = (char*)pSpsppsInfo;
		        SPS_PPS_VALUE *pstValue = (SPS_PPS_VALUE*)(pBuff+sizeof(DWORD) + sizeof(WORD)*2);
				Q3_Get_SPSPPSValue(pSpsppsInfo->chn, pSpsppsInfo->streamtype, pstValue);
				ret = QMAPI_SUCCESS;
			}
			break;
		}
        case QMAPI_SYSCFG_SET_VIEWMODE:
        {
            Q3_Video_ViewMode_Set(nChannel);
            ret = QMAPI_SUCCESS;
            break;
        }
#if 0
        case QMAPI_SYSCFG_SET_ROICFG:
        {
            struct v_roi_info roiInfo;
            struct v_roi_info roiInfo_tmp;
            //TL_CHANNEL_SHELTER *pShelter = (TL_CHANNEL_SHELTER *)lpInParam;
            roiInfo.roi[0].enable = 1; 
            roiInfo.roi[0].x = 0; 
            roiInfo.roi[0].y = 0; 
            roiInfo.roi[0].w = 400; 
            roiInfo.roi[0].h = 400; 
            roiInfo.roi[0].qp_offset = -10;
#if 1 
            roiInfo.roi[1].enable = 1; 
            roiInfo.roi[1].x = 400;//1920-160; 
            roiInfo.roi[1].y = 400;//1080-160; 
            roiInfo.roi[1].w = 400; 
            roiInfo.roi[1].h = 400; 
            roiInfo.roi[1].qp_offset = -10; 
#endif
            video_set_roi(Q3_GetChannelName(nChannel), &roiInfo);
            //printf("#7777777 %s %d QMAPI_SYSCFG_SET_ROICFG \n", __FUNCTION__, __LINE__);

            ret = QMAPI_SUCCESS;
            break;
        }
#endif
        default:
        {
            printf("<fun:%s>-<line:%d>, unspport cmd:%d\n", __FUNCTION__, __LINE__, nCmd);
            ret = QMAPI_ERR_UNKNOW_COMMNAD;
			break;
        }
	}

    return ret;
}


/*********************************************************************
    Function:   QMapi_buf_add_reader
    Description:��Ӷ�ָ��,һ��Buffer֧�ֶ����ָ�����
    Calls:
    Called By:
    parameter:
            [in] s32Chn Դͨ����
            [in] enStreamType ��������
            [out] int *pnReaderId  ���ض�ָ��ID
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_add_reader(int Handle, const int nChannel,
                               const QMAPI_STREAM_TYPE_E enStreamType,
                               int *pReaderId)
{
    int s32Ret = 0;
    printf("#### %s %d\n", __FUNCTION__, __LINE__);
    s32Ret = VS_BUF_AddReader(nChannel , enStreamType, pReaderId); 
    printf("#### %s %d\n", __FUNCTION__, __LINE__);

    return s32Ret;      //return QMAPI_SUCCESS;
}

/*********************************************************************
    Function:   QMapi_buf_del_reader
    Description:ɾ����ָ��
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_del_reader(int Handle, int nReaderId)
{
    return VS_BUF_DelReader(nReaderId);
}

/*********************************************************************
    Function:   QMapi_buf_get_frame
    Description:��ȡ֡����
    Calls:      ��Buffer�л�ȡ֡���ݣ�������Ƶ����Ƶԭʼ������֡����
    Called By:
    parameter:
        [in] int nReaderId  ��ָ��ID
        [in] QMAPI_MBUF_POS_POLICY_E enPolicy  ��ȡ֡��ʽ
        [in] int nPosIndex  ���֡��
        [in] char* pStart   �����������ݻ�����ʼ��ַ
        [in/out] unsigned int *pdwLen �������뻺�泤�ȣ�����ʵ��֡���ݳ���
        [out] QMAPI_NET_FRAME_HEADER *pstFrameHeader ����Ƶ����
    Return: QMAPI_SUCCESS
            HI_EPAERM   �����������
            HI_ENOTINIT Bufferδ����
            BUF_NO_DATA Buffer����ʱ�����ݣ���Ҫ���������»�ȡ
********************************************************************/
int QMapi_buf_get_frame(int Handle, int nReaderId,
                               QMAPI_MBUF_POS_POLICY_E enPolicy,
                               int nOffset,
                               char* pStart,
                               unsigned int *pdwLen,
                               QMAPI_NET_FRAME_HEADER *pstFrameHeader)
{
    int s32Ret = 0;
//#ifndef TL_Q3_PLATFORM

    if( NULL == pstFrameHeader)
    {
        printf("FUN:%sLINE:%d parameter error \n" , __FUNCTION__ , __LINE__);

        return 1;
    }
    
    memset(pstFrameHeader,  0 , sizeof(QMAPI_NET_FRAME_HEADER));
    VS_FRAME_TYPE_E enFrameType = VS_FRAME_I;
    unsigned long long timestick = 0;
    unsigned int u32PacketNo = 0;
    int s32Width = 0;
    int s32Height = 0;
    s32Ret = VS_BUF_GetFrame(nReaderId , enPolicy , nOffset ,&enFrameType ,(unsigned char *)pStart , pdwLen  , &timestick , &u32PacketNo ,&s32Width ,  & s32Height , 1);
    if(s32Ret)
    {
        printf("FUN:%sLINE:%d VS_BUF_GetFrame error%d \n" ,__FUNCTION__ , __LINE__ , s32Ret);
        return s32Ret;
    }

    pstFrameHeader->wVideoWidth =   s32Width;
    pstFrameHeader->wVideoHeight =  s32Height;
    pstFrameHeader->byFrameType =   enFrameType ;
    pstFrameHeader->dwFrameIndex = u32PacketNo;
    pstFrameHeader->dwSize =                sizeof(QMAPI_NET_FRAME_HEADER);
    pstFrameHeader->dwTimeTick = timestick;

    
    if(VS_FRAME_A == enFrameType)
    {
        pstFrameHeader->wAudioSize =*pdwLen;
        pstFrameHeader->byVideoCode = (unsigned char)QMAPI_PT_G711A;

    }
    else
    {
        pstFrameHeader->byVideoCode = (unsigned char)QMAPI_PT_H264;
        pstFrameHeader->dwVideoSize =*pdwLen;
    }
//#endif
	return s32Ret;
}

/*********************************************************************
    Function:   QMapi_buf_find_nextframe
    Description:����������������Ѱ��һ֡
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_find_nextframe(int Handle, int nReaderId)
{
//#ifndef TL_Q3_PLATFORM

//    if(g_dms_sysnet_stop != 0)
    {
//        return QMAPI_FAILURE;
    }
//#endif
    return 0;
}

/*********************************************************************
    Function:   QMapi_buf_get_next_frametype
    Description:��ȡ��һ֡������
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
            [in] QMAPI_MBUF_POS_POLICY_E enPolicy ��ȡ��ָ�뷽ʽ
            [in] int nOffset  ���I֡��
            [out] HI_MBUF_READPTR_INFO_S *pstReadptr ���ض�ָ��λ����Ϣ
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_get_next_frametype(int Handle, int nReaderId,
                                        QMAPI_MBUF_POS_POLICY_E enPolicy,
                                        int nOffset,
                                        QMAPI_FRAME_TYPE_E *penFrameType)
{

//    if(g_dms_sysnet_stop != 0)
    {
//        return QMAPI_FAILURE;
    }
    int ret = 0;
//#ifndef TL_Q3_PLATFORM
	VS_FRAME_TYPE_E enNextFrameType = 0;
	ret = VS_BUF_GetNextFrameType(nReaderId,enPolicy,nReaderId,&enNextFrameType ,1);
	*penFrameType = enNextFrameType ;
//#endif
	return ret;
}



/*********************************************************************
    Function:   QMapi_buf_get_readptrpos
    Description:��ȡ��ָ��λ��
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
            [in] QMAPI_MBUF_POS_POLICY_E enPolicy  ��ȡ��ָ�뷽ʽ
            [in] int nOffset  ���I֡��
            [out] QMAPI_NET_DATA_PACKET *pstReadptr ���ض�ָ��λ����Ϣ
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_get_readptrpos(int Handle, int nReaderId,
                                   QMAPI_MBUF_POS_POLICY_E enPolicy,
                                   int nOffset,
                                   QMAPI_NET_DATA_PACKET *pstReadptr)
{
    if(NULL == pstReadptr)
    {
        printf("FUN:%sLINE:%d parameter error \n" , __FUNCTION__ , __LINE__);
        return 1;
    }

//#ifndef TL_Q3_PLATFORM

    int s32Ret = 0;

    VS_FRAME_TYPE_E enFrameType = VS_FRAME_I;
    memset(pstReadptr , 0 , sizeof(QMAPI_NET_DATA_PACKET));
    unsigned int startoffset = 0;
    unsigned int u32PacketNo , u32PacketSize;
    unsigned long long timetick = 0;
    int s32Width = 0;
    int s32Height = 0;
    do
    {
        s32Ret = VS_BUF_GetFramePtr(nReaderId , enPolicy , nOffset , &enFrameType , &pstReadptr->pData ,
        &startoffset , &u32PacketSize, &timetick,&u32PacketNo ,&s32Width , &s32Height , 0);
        if(HI_EEMPTY == s32Ret)
            usleep(10000);
    }while(HI_EEMPTY == s32Ret);
    
    if (s32Ret)
    {
    	printf("FUN:%s LINE:%d s32Ret:%d. \n" , __FUNCTION__ , __LINE__, s32Ret);
        return s32Ret;
    }

    pstReadptr->dwPacketSize =u32PacketSize;
    pstReadptr->dwPacketNO = 0;
    pstReadptr->stFrameHeader.wVideoWidth = s32Width;
    pstReadptr->stFrameHeader.wVideoHeight = s32Height;
    pstReadptr->stFrameHeader.byFrameType = enFrameType;
    pstReadptr->stFrameHeader.dwFrameIndex = u32PacketNo;
    pstReadptr->stFrameHeader.dwSize = sizeof(pstReadptr->stFrameHeader);
    pstReadptr->stFrameHeader.dwTimeTick = timetick;

    if(VS_FRAME_A == enFrameType)
    {
        pstReadptr->stFrameHeader.wAudioSize =u32PacketSize;
        pstReadptr->stFrameHeader.byVideoCode = (unsigned char)QMAPI_PT_G711A;
    }
    else
    {
        pstReadptr->stFrameHeader.byVideoCode = (unsigned char)QMAPI_PT_H264;
        pstReadptr->stFrameHeader.dwVideoSize =u32PacketSize;
    }
//#endif
    return 0;
}

//#ifndef TL_Q3_PLATFORM
/*********************************************************************
    Function:QMapi_buf_can_read
    Description:�����Ƿ��ܶ�
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
            [in] unsigned int u32Len ����
    Return: ���ؿ������ݳ��ȣ����ܺ���������ݳ��Ȳ�һ��
********************************************************************/
int QMapi_buf_can_read(int Handle, int nReaderId, unsigned int dwLen)
{
//    if(g_dms_sysnet_stop != 0)
    {
//        return QMAPI_FAILURE;
    }
    return VS_BUF_CanRead(nReaderId, dwLen);
}

/*********************************************************************
    Function:QMapi_buf_set_readptrpos
    Description:���ö�ָ��λ��
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
            [in] unsigned int u32Len   ����
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_set_readptrpos(int Handle, int nReaderId, unsigned int dwLen)
{
 //   if(g_dms_sysnet_stop != 0)
    {
//        return QMAPI_FAILURE;
    }
    return 0;
}


/*********************************************************************
    Function:   QMapi_buf_get_readptrLeftnum
    Description:��ȡ��ָ����дָ��֮��֡������I֡����������
                ������Э���ⲿ�Ĳ��ſ��ƻ���������
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
            [out] unsigned int *pu32IFrameNum  I֡����
            [out] unsigned int *pu32LeaveCount ʣ�����ݳ���
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_get_readptrLeftnum(int Handle, int nReaderId, unsigned int *pdwLeaveCount,unsigned long *dwTimeTick)
{
    *dwTimeTick = 0;
    return VS_BUF_GetReadPtrLeftNum(nReaderId, pdwLeaveCount);
}














