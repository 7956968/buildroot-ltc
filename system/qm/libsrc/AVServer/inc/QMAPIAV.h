#ifndef __QMAPI_AV_H__
#define __QMAPI_AV_H__

#include "QMAPICommon.h"
#include "QMAPINetSdk.h"
#include "QMAPI.h"

/*********************************************************************
    Function:   QMAPI_AVServer_Init
    Description: ��ʼ������Ƶ����,��ʼ������Ƶbuffer
    Calls:
    Called By:
    parameter:
            [in] lpDeafultParam QMAPI_NET_CHANNEL_PIC_INFO
    Return: ģ����
********************************************************************/
int QMAPI_AVServer_Init(void *lpDeafultParam, int Resolution);

/*********************************************************************
    Function:   QMAPI_AVServer_Init
    Description: ����ʼ������Ƶ����,����ʼ������Ƶbuffer
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: 
********************************************************************/
int QMAPI_AVServer_UnInit(int Handle);

/*********************************************************************
    Function:   QMAPI_AVServer_Start
    Description: ��������Ƶ����
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
            [in] VidoeCount ��Ƶ�����򿪸�����1<<0������QMAPI_MAIN_STREAM��1<<1������QMAPI_SECOND_STREAM
    Return: QMAPI_SUCCESS/QMAPI_FAILURE
********************************************************************/
int QMAPI_AVServer_Start(int Handle, int VidoeCount);


/*********************************************************************
    Function:   QMAPI_AVServer_Stop
    Description: �ر�����Ƶ����
    Calls:
    Called By:
    parameter:
            [in] Handle ģ����
    Return: 
********************************************************************/
int QMAPI_AVServer_Stop(int Handle);

/*********************************************************************
    Function:   QMAPI_AVServer_IOCtrl
    Description: ��������Ƶ�������
    Calls:
    Called By:
    parameter:
            [in] Handle ���ƾ��
            [in] nCmd ��������
                    ��ЧֵΪ: QMAPI_SYSCFG_GET_PICCFG/QMAPI_SYSCFG_SET_PICCFG/QMAPI_SYSCFG_GET_DEF_PICCFG
            [in/out] Param QMAPI_NET_CHANNEL_PIC_INFO
            [in/out] nSize ���ýṹ���С
    Return: QMAPI_SUCCESS
********************************************************************/
int QMAPI_AVServer_IOCtrl(int Handle, int nCmd, int nChannel, void* Param, int nSize);



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
int QMapi_buf_add_reader(int Handle,const int nChannel,
	                           const QMAPI_STREAM_TYPE_E enStreamType,
	                           int *pReaderId);

/*********************************************************************
    Function:   QMapi_buf_del_reader
    Description:ɾ����ָ��
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_del_reader(int Handle,int nReaderId);

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
int QMapi_buf_get_frame(int Handle,int nReaderId,
		                       QMAPI_MBUF_POS_POLICY_E enPolicy,
		                       int nOffset,
		                       char* pStart,
		                       unsigned int *pdwLen,
		                       QMAPI_NET_FRAME_HEADER *pstFrameHeader);

/*********************************************************************
    Function:   QMapi_buf_find_nextframe
    Description:����������������Ѱ��һ֡
    Calls:
    Called By:
    parameter:
            [in] int nReaderId  ��ָ��ID
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_find_nextframe(int Handle,int nReaderId);

/*********************************************************************
    Function:   QMapi_buf_get_next_frametype
    Description:��ȡ��һ֡������
    Calls:
    Called By:
    parameter:
			[in] int nReaderId  ��ָ��ID
			[in] QMAPI_MBUF_POS_POLICY_E enPolicy	��ȡ��ָ�뷽ʽ
			[in] int nOffset  ���I֡��
			[out] HI_MBUF_READPTR_INFO_S *pstReadptr ���ض�ָ��λ����Ϣ
    Return: QMAPI_SUCCESS
********************************************************************/
int QMapi_buf_get_next_frametype(int Handle,int nReaderId,
										QMAPI_MBUF_POS_POLICY_E enPolicy,
										int nOffset,
										QMAPI_FRAME_TYPE_E *penFrameType);

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
                                   QMAPI_NET_DATA_PACKET *pstReadptr);

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
int QMapi_buf_can_read(int Handle,int nReaderId, unsigned int dwLen);


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
int QMapi_buf_set_readptrpos(int Handle, int nReaderId, unsigned int dwLen);


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
int QMapi_buf_get_readptrLeftnum(int Handle, int nReaderId, unsigned int *pdwLeaveCount,unsigned long *dwTimeTick);








#endif


