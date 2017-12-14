/**
 */

#ifndef __CBUFFER_H__
#define __CBUFFER_H__

class CBuffer
{
public:

private:
    /*���С*/
    HI_U32 m_u32BlockSize;
    /*�����*/
    HI_U32 m_u32BlockNum;
    /*buffer������ʶ*/
    HI_BOOL m_bBufCreate;
    /*��ָ�����*/
    HI_U32 m_u32ReaderCnt;

    HI_U32 m_u32VideoPacketNo;

    HI_U32 m_u32AudioPacketNo;

    HI_U32 m_u32ReadVideoPacketNo[BUF_MAX_READER_NUM];

    HI_U32 m_u32ReadAudioPacketNo[BUF_MAX_READER_NUM];

	HI_U32 m_bLock;
    /*buffer��Ϣ*/
    BUF_STREAM_INFO_S m_stBufferInfo;
    /*��ָ��λ��*/
    HI_U32 m_au32ReadPos[BUF_MAX_READER_NUM];
    /*��ָ��Ȧ��*/
    HI_U32 m_au32ReadCycle[BUF_MAX_READER_NUM];
    /*��ָ��ʹ�����*/
    HI_BOOL m_abReaderUsed[BUF_MAX_READER_NUM];
    /*I֡��Ϣ*/
    BUF_IFRAME_MNG_S m_stIFrameManager;
    /*��¼ÿһ��д���I֡��ʱ��*/
    VS_DATETIME_S m_stKeyTime;
    /*��������*/
    BUF_STREAM_ATTR_S m_stStreamAttr;
    /*��ָ����������*/
    BUF_STREAM_ATTR_S m_astReaderStreamAttr[BUF_MAX_READER_NUM];
    /*buf��*/
    pthread_mutex_t m_BufLock;
private:
    /*��ʼ��I֡����*/
    HI_S32 InitIFrameManager(HI_U32 u32ExpectIFrameNum);
    /*ȥ��ʼ��I֡����*/
    HI_S32 DeinitIFrameManager();
    /*����I֡����*/
    HI_S32 SetIFrameManager(HI_U32 u32Size, HI_BOOL bIFrameHeader);
    /*���ÿ���Ϣ*/
    HI_S32 SetBlockInfo(HI_BOOL bIFrame,HI_U32 u32WritePos,HI_U32 u32DataLen,VS_DATETIME_S *pTime);
    /*��ȡ�뵱ǰдָ�����I֡���ڿ����ʼλ��*/
    HI_S32 GetLastWriteNIFramPos(HI_U32 u32N,BUF_IFRAME_MNG_S stIFramManager,HI_U32 *pu32ReadPos,HI_U32 *pu32ReadCycle);
public:
    CBuffer();
    ~CBuffer();
public:
 /**
 \brief ����Buffer,��Buffer�������
 \attention \n
 \param[in] HI_U32 u32BlockSize  ���С
 \param[in] HI_U32 u32BlockNum   �����
 \retval ::HI_SUCCESS
 */
    HI_S32 BUF_Create(HI_U32 u32BlockSize, HI_U32 u32BlockNum);

 /**
 \brief ����Buffer
 \attention \n
 \param
 \retval ::HI_SUCCESS
 */
    HI_S32 BUF_Destroy();

 /**
 \brief дBuffer
 \attention \n
 \param[in] HI_U8 *pu8Start ��ʼ��ַ
 \param[in] HI_U32 u32Len   ����
 \param[in] HI_BOOL bIFrame �Ƿ�ΪI֡
 \param[in] VS_DATETIME_S *pTime  ʱ��
 \retval ::HI_SUCCESS
 \see \n
 */
	void BUF_Lock();
    HI_S32 BUF_Write(const HI_U8 *pu8Start,HI_U32 u32Len,HI_BOOL bIFrame,VS_DATETIME_S *pTime);
	void BUF_Unlock();
 /**
 \brief д��Ƶ���ݽ�Buffer
 \attention \n
 \param[in] HI_U8 *pu8Start ��ʼ��ַ
 \param[in] HI_U32 u32Len   ����
 \param[in] VS_FRAME_TYPE_E enFrameType ֡����
 \param[in] VS_DATETIME_S *pTime  ʱ��
 \param[in] HI_S32 s32Chn  ͨ����
 \param[in] HI_U64 u64Pts  ʱ���
 \retval ::HI_SUCCESS
 \see \n
    ::BUF_WriteAudioData
 */
    HI_S32 BUF_WriteVideoData(const HI_U8 *pu8Start,HI_U32 u32Len,VS_FRAME_TYPE_E enFrameType,VS_DATETIME_S *pTime,HI_S32 s32Chn,HI_U64 u64Pts);

 /**
 \brief д��Ƶ���ݽ�Buffer
 \attention \n
 \param[in] HI_U8 *pu8Start ��ʼ��ַ
 \param[in] HI_U32 u32Len   ����
 \param[in] VS_AUDIO_FORMAT_E enCodecType ��Ƶ����
 \param[in] HI_S32 s32Chn  ͨ����
 \param[in] HI_U64 u64Pts  ʱ���
 \retval ::HI_SUCCESS
 \see \n
    ::BUF_WriteVideoData
 */
    HI_S32 BUF_WriteAudioData(const HI_U8 *pu8Start,HI_U32 u32Len,HI_S32 s32Chn,HI_U64 u64Pts);

  /**
 \brief ��Ӷ�ָ��
 \attention \n
 \param[out] HI_S32 *ps32ReaderId  ���ض�ָ��ID
 
 \retval ::HI_SUCCESS
 \see \n
    ::BUF_DelReader
 */
    HI_S32 BUF_AddReader(HI_S32 *ps32ReaderId);

 /**
 \brief ɾ����ָ��
 \attention \n
 \param[in] HI_S32 s32ReaderId  ��ָ��ID
 \retval ::HI_SUCCESS
 \see \n
    ::BUF_AddReader
 */
    HI_S32 BUF_DelReader(HI_S32 s32ReaderId);

 /**
 \brief ��ȡ��ָ��λ��
 \attention \n
 \param[in] HI_S32 s32ReaderId  ��ָ��ID
 \param[in] BUF_POSITION_POLICY_E enPolicy  ��ȡ��ָ�뷽ʽ
 \param[in] HI_S32 s32N  ���I֡��
 \param[out] BUF_READPTR_INFO_S *pstReadptr ���ض�ָ��λ����Ϣ
 \retval ::HI_SUCCESS
 \see \n
    ::BUF_WriteVideoData
 */
    HI_S32 BUF_GetReadPtrPos(HI_S32 s32ReaderId,
                            BUF_POSITION_POLICY_E enPolicy,
                            HI_S32 s32N,
                            BUF_READPTR_INFO_S *pstReadptr);

 /**
 \brief �����Ƿ��ܶ�
 \attention \n
 \param[in] HI_S32 s32ReaderId  ��ָ��ID
 \param[in] HI_U32 u32Len ����
 \retval ::HI_SUCCESS
 */
    HI_S32 BUF_CanRead(HI_S32 s32ReaderId, HI_U32 u32Len);

 /**
 \brief ���ö�ָ��λ��
 \attention \n
 \param[in] HI_S32 s32ReaderId  ��ָ��ID
 \param[in] HI_U32 u32Len   ����
 \retval ::HI_SUCCESS
 */
    HI_S32 BUF_SetReadPtrPos(HI_S32 s32ReaderId, HI_U32 u32Len);

 /**
 \brief ��ȡ��ָ����дָ��֮��I֡����������
        ������Э���ⲿ�Ĳ��ſ��ƻ���������
 \attention \n
 \param[in] HI_S32 s32ReaderId  ��ָ��ID
 \param[out] HI_U32 *pu32IFrameNum  I֡����
 \param[out] HI_U32 *pu32BlockNum   �����
 \retval ::HI_SUCCESS
 */
    HI_S32 BUF_GetReadPtrLeftNum(HI_S32 s32ReaderId,
                                 HI_U32 *pu32BlockNum);

 /**
 \brief ��ȡ��ָ�����������
 \attention \n
 \param[in] HI_S32 s32ReaderId  ��ָ��ID
 \param[out] BUF_STREAM_ATTR_S pstStreamAttr  ������������
 \retval ::HI_SUCCESS
 \see \n
 */
    HI_S32 BUF_GetReaderStreamAttr(HI_S32 s32ReaderId,
                                      BUF_STREAM_ATTR_S *pstStreamAttr);

 /**
 \brief ����Buffer��������
 \attention \n
 \param[out] stStreamAttr  ��������
 \retval ::HI_SUCCESS
 \see \n
 */
    HI_S32 BUF_SetStreamAttr(const BUF_STREAM_ATTR_S *pstStreamAttr);

 /**
 \brief ��ȡBuffer����������
 \attention \n
 \param[out] BUF_STREAM_ATTR_S *pstStreamAttr  ������������
 \retval ::HI_SUCCESS
 \see \n
 */
    HI_U32 BUF_GetStreamAttr(BUF_STREAM_ATTR_S *pstStreamAttr);

    HI_U32  BUF_GetBufPhyAddr();

    HI_U32  BUF_GetBufSize();

    HI_U8 * BUF_GetBufAddr();

    HI_S32  BUF_CheckReaderPacketNo(HI_S32 s32ReaderId , HI_BOOL bVideo ,  HI_U32 u32PacketNo);
    
	unsigned char  *   BUF_GetWriteMemPos(HI_U32 u32Size);


/** @} */  /*! <!-- function Definition end */
};


#endif /*__CBUFFER_H__*/


