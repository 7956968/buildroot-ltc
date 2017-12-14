#ifndef __VS_BUFFER_H__
#define __VS_BUFFER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**���������С*/
#define BUF_MAX_IFRAME_IN_BLOCK 128

#define MAX_CHANNEL_NUM 16

/**����ָ�����*/    
#define BUF_MAX_READER_NUM 8   


typedef enum tagVS_FRAME_TYPE_E
{
    VS_FRAME_I, /**<I֡*/
    VS_FRAME_P, /**<P֡*/
    VS_FRAME_B, /**<B֡*/
    VS_FRAME_A, /**<��Ƶ֡*/
    VS_FRAME_BUTT /**<����ֵ*/
    
}VS_FRAME_TYPE_E;

typedef enum tagVS_AUDIO_FORMAT_E
{
    VS_AUDIO_FORMAT_G711A   = 1,   /* G.711 A            */
    VS_AUDIO_FORMAT_G711Mu  = 2,   /* G.711 Mu           */
    VS_AUDIO_FORMAT_ADPCM   = 3,   /* ADPCM              */
    VS_AUDIO_FORMAT_G726    = 4,   /* G.726              */
    VS_AUDIO_FORMAT_AMR     = 5,   /* AMR encoder format */
    VS_AUDIO_FORMAT_AMRDTX  = 6,   /* AMR encoder formant and VAD1 enable */
    VS_AUDIO_FORMAT_AAC     = 7,   /* AAC encoder        */
    VS_AUDIO_FORMAT_BUTT
}VS_AUDIO_FORMAT_E;

typedef enum tagVS_STREAM_TYPE_E
{
    VS_STREAM_TYPE_MAIN = 0,    /**< ������ */
    VS_STREAM_TYPE_NETSUB,  /**< ���������� */
    VS_STREAM_TYPE_SNAP,    /**< ץ������ */
    VS_STREAM_TYPE_MOBILE,  /**< �ֻ����� */
    VS_STREAM_TYPE_IP,      /**< IP����*/
    VS_STREAM_TYPE_BUTT     /**< �Ƿ�ֵ*/
}VS_STREAM_TYPE_E;


/*����*/
typedef enum tagVS_WEEKDAY_E
{
    VS_WEEKDAY_SUNDAY,   /**<������*/
    VS_WEEKDAY_MONDAY,   /**<����һ*/
    VS_WEEKDAY_TUESDAY,  /**<���ڶ�*/
    VS_WEEKDAY_WEDNESDAY,/**<������*/
    VS_WEEKDAY_THURSDAY, /**<������*/
    VS_WEEKDAY_FRIDAY,   /**<������*/
    VS_WEEKDAY_SATURDAY  /**<������*/
}VS_WEEKDAY_E;


/**����ʱ��*/
typedef struct tagVS_DATETIME_S
{
    int s32Year;   /**<��*/
    int s32Month;  /**<��*/
    int s32Day;    /**<��*/
    int s32Hour;   /**<ʱ*/
    int s32Minute; /**<��*/
    int s32Second; /**<��*/
    VS_WEEKDAY_E enWeek; /**<����,���::VS_WEEKDAY_E*/
}VS_DATETIME_S;

typedef enum tagPOSITION_POLICY_E
{
    BUF_POSITION_CUR_READ = 0,/**<��ǰ��ָ���λ��*/
    BUF_POSITION_LAST_READ_nIFRAME,/**<�뵱ǰ��ָ������ĵ�n��I֡���ڵĿ����ʼλ��*/
    BUF_POSITION_CUR_WRITE,/**<��ǰдָ���λ��*/
    BUF_POSITION_LAST_WRITE_nBLOCK,/**<�뵱ǰдָ������ĵ�n�������ʼλ��*/
    BUF_POSITION_LAST_WRITE_nIFRAME,/**<�뵱ǰдָ������ĵ�n��I֡���ڵĿ����ʼλ��, n=0��ʾ�����I֡*/
    BUF_POSITION_BUTT
}BUF_POSITION_POLICY_E;

typedef enum tagVS_TVSYSTEM_E
{
    VS_TVSYSTEM_PAL,    /**<PAL*/
    VS_TVSYSTEM_NTSC,   /**<NTSC*/
    VS_TVSYSTEM_BUTT /**<�Ƿ�ֵ*/
}VS_TVSYSTEM_E;

/**��������*/
typedef struct tagBUF_STREAM_ATTR_S
{
    VS_TVSYSTEM_E enNorm;/**��ʽ*/
    unsigned int u32Width;
    unsigned int u32Height;
    unsigned int u32Fps; /**֡��*/
    unsigned int u32Bps; /**����*/
    unsigned int u32Gop; /**����I֡��� */
    VS_AUDIO_FORMAT_E enCodecType;  /**<��Ƶ����*/
}BUF_STREAM_ATTR_S;

typedef struct tagIFRAME_INFO_S
{
    unsigned int u32Offset;/**<I֡�Ŀ���ƫ�� <unit:Byte*/
    BUF_STREAM_ATTR_S stStreamAttr; /**<��������*/
}BUF_IFRAME_INFO_S;

/**������������(64Kһ����)�������Ϣ*/
typedef struct tagBLOCK_INFO_S
{
    unsigned int u32Cycle;/**<BLOCK��Ȧ��*/
    unsigned int u32IFrameNum;/**<һ�����ڵ�I֡�ĸ���*/
    unsigned int u32FrameNum;/**<һ������֡����*/
    BUF_IFRAME_INFO_S astIFrame[BUF_MAX_IFRAME_IN_BLOCK];/**<I֡��Ϣ*/
} BUF_BLOCK_INFO_S;

/**��ָ����Ϣ*/
typedef struct tagREADPTR_INFO_S
{
    unsigned char *pu8ReadPos;/**<��ָ��*/
    unsigned int u32ReadOffset; //��ƫ��
    unsigned int u32BufferSize;
    BUF_BLOCK_INFO_S stBlockInfo;/**<��ָ�����ڵĿ���Ϣ*/
}BUF_READPTR_INFO_S;

/*��Ƶͷ*/
typedef struct hiVIDEO_HEAD_S
{
    unsigned int u32FrameType;    /*I֡Ϊx0dc��x�ڵ�һ���ֽڣ�0Ϊ�ڶ����ֽڣ�dΪ�������ֽڣ�cΪ���ĸ��ֽڣ�p ֡Ϊx1dc*/
    unsigned int u32StreamType;   /*����ʽ����ʱ�̶�ΪH264��ASCII*/
    unsigned int u32FrameLen;     /*����Ƶ֡���ݳ���*/
    unsigned int u32PacketNo;    
    unsigned long long u64Pts;          /*ʱ���*/
    unsigned char   u8Time[8];
} VIDEO_HEAD_S;

typedef struct hiDUMMY_HEAD_S  //this struct must tightly align with video header
{
    unsigned int u32FrameType;    /*I֡Ϊx0dc��x�ڵ�һ���ֽڣ�0Ϊ�ڶ����ֽڣ�dΪ�������ֽڣ�cΪ���ĸ��ֽڣ�p ֡Ϊx1dc*/
    unsigned int u32StreamType;   /*����ʽ����ʱ�̶�ΪH264��dum frame Ϊdumy ASCII*/
    unsigned int u32FrameLen;     /*����Ƶ֡���ݳ���*/
	unsigned int u32PacketNo;    
    unsigned long long  u64Pts;          /*ʱ���*/
    unsigned char  u8Align[8];    //align with Video header;
} DUMMY_HEAD_S;

/*��Ƶͷ*/
typedef struct hiAUDIO_HEAD_S
{
    unsigned int u32FrameType;    /*��Ƶ֡��ʶ*/
    unsigned short u16FrameLen;     /*һ����Ƶ֡����*/
    unsigned short u16PacketLen;    /*�˰���Ƶ���ݳ���*/
    unsigned int u32PacketNo;
    unsigned int u32Reserved;
    unsigned long long  u64Pts;          /*ʱ���*/
} AUDIO_HEAD_S;

/*----------------------------------------------*
* ��������
*----------------------------------------------*/

/** @defgroup buffer_API_routine_prototypes buffer_APIģ��
 *  @ingroup H1
 *  @brief ��ϸ����ģ��(buffer_API)�ĺ�������
 *  @{  */

/**
 \brief ��ʼ��Buf
 \attention \n
��
 \retval ::HI_SUCCESS
 \see \n
    ::VS_BUF_Exit
 */
int VS_BUF_Init();



int VS_BUF_Exit();

/**
 \brief ����һ������Buffer
 \attention \n
    һ���ڴ�������ͨ���������������ͨ��ʱ����
    һ��ͨ���ź��������Ͷ�Ӧһ��Buffer
 \param[in] s32Chn Դͨ����
 \param[in] enStreamType ��������
 \param[in] u32BlockSize ���С
 \param[in] u32BlockNum ����

 \retval ::HI_SUCCESS

 \see \n
    ::VS_BUF_Destroy
 */
int VS_BUF_Create(const int s32Chn,
                     const VS_STREAM_TYPE_E enStreamType,
                     const unsigned int u32BlockSize,
                     const unsigned int u32BlockNum);

/**
 \brief ����һ������Buffer
 \attention \n
��
 \param[in] s32Chn Դͨ����
 \param[in] enStreamType ��������
 \retval ::HI_SUCCESS  �ɹ�
 \see \n
    ::VS_BUF_Create
 */
int VS_BUF_Destroy(const int s32Chn,
                      const VS_STREAM_TYPE_E enStreamType);

 /**
 \brief д֡���ݽ�Buffer
 \attention \n
        ͨ��ʹ��VS_BUF_WriteFrame����ԭʼ������֡���ݣ�������Ƶ֡����Ƶ֡
        ��VS_BUF_GetFrame��ȡ����Ƶԭʼ������֡��ʹ�����֮���ٵ���VS_BUF_SetFrame
        ����BUF_Write��������Ϊ�ڲ�����ʹ��
        BUF_GetReadPtrPos��BUF_CanRead��BUF_SetReadPtrPos������Ϊ�ڲ�ʹ��
 \param[in] s32Chn Դͨ����
 \param[in] enStreamType ��������
 \param[in] HI_VS_VIDEO_FRAME_TYPE_E enFrameType ֡����
 \param[in] unsigned char *pu8Start ��ʼ��ַ
 \param[in] unsigned int u32Len   ����
 \param[in] unsigned long long u64Pts  ʱ���
 \param[in] VS_DATETIME_S *pTime  ʱ��
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
    ::VS_BUF_GetFrame
 */
int VS_BUF_WriteFrame(const int s32Chn,
                         const VS_STREAM_TYPE_E enStreamType,
                         VS_FRAME_TYPE_E enFrameType,
                         const unsigned char *pu8Start,
                         unsigned int u32Len,
                         unsigned long long u64Pts,
                         VS_DATETIME_S *pTime);


 /**
 \brief ��Ӷ�ָ��
 \attention \n
       һ��Buffer֧�ֶ����ָ�����
 \param[in] s32Chn Դͨ����
 \param[in] enStreamType ��������
 \param[out] int *ps32ReaderId  ���ض�ָ��ID
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
    ::VS_BUF_DelReader
 */
int VS_BUF_AddReader(const int s32Chn,
                       const VS_STREAM_TYPE_E enStreamType,
                       int *ps32ReaderId);

 /**
 \brief ɾ����ָ��
 \attention \n
 \param[in] int s32ReaderId  ��ָ��ID
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
    ::VS_BUF_AddReader
 */
int VS_BUF_DelReader(int s32ReaderId);



 /**
 \brief ��ȡ֡����
 \attention \n
        ��Buffer�л�ȡ֡���ݣ�������Ƶ����Ƶԭʼ������֡���ݣ�
 \param[in] int s32ReaderId  ��ָ��ID
 \param[in] VS_BUF_POSITION_POLICY_E enPolicy  ��ȡ֡��ʽ
 \param[in] int s32N  ���֡��
 \param[out] VS_FRAME_TYPE_E *penFrameType ����֡����
 \param[in] unsigned char *pu8Start   �����������ݻ�����ʼ��ַ
 \param[in/out] unsigned int *pu32Len  �������뻺�泤�ȣ�����ʵ��֡���ݳ���
 \param[out] unsigned long long *pu64Pts  ʱ���
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
         ::BUF_NO_DATA Buffer����ʱ�����ݣ���Ҫ���������»�ȡ
 \see \n
    ::VS_BUF_SetFrame
 */
int VS_BUF_GetFrame(int s32ReaderId,
                       BUF_POSITION_POLICY_E enPolicy,
                       int s32N,
                       VS_FRAME_TYPE_E *penFrameType,
                       unsigned char *pu8Start,
                       unsigned int *pu32Len,
                       unsigned long long *pu64Pts,
                       unsigned int  *pu32PacketNo , 
                       int * ps32Width , int * ps32Height ,
                       unsigned char u8IOblock);


 /**
 \brief ��ȡ��ָ����дָ��֮��֡������I֡����������
 \attention \n
 ��ȡ��ǰ��ָ�����дָ��ʣ��I֡������������
 ������Э���ⲿ�Ĳ��ſ��ƻ���������
 \param[in] int s32ReaderId  ��ָ��ID
 \param[out] unsigned int *pu32FrameNum  ֡����
 \param[out] unsigned int *pu32IFrameNum  I֡����
 \param[out] unsigned int *pu32BlockNum   �����
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
    ::VS_BUF_GetFrame
 */
int VS_BUF_GetReadPtrLeftNum(int s32ReaderId,
							 	unsigned int *pu32BlockNum);
/*
int VS_BUF_GetReadPtrLeftNum(int s32ReaderId,
                                unsigned int *pu32FrameNum,
                                unsigned int *pu32IFrameNum,
                                unsigned int *pu32LeaveCount,
                                unsigned long long *pu64Pts);
*/

 /**
 \brief ��ȡ��ָ�����������
 \attention \n
 \param[in] int s32ReaderId  ��ָ��ID
 \param[out] BUF_STREAM_ATTR_S pstStreamAttr  ������������
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
 */
int VS_BUF_GetReaderStreamAttr(int s32ReaderId,
                                  BUF_STREAM_ATTR_S *pstStreamAttr);
 
 /**
 \brief ����Buffer��������
 \attention \n
 \param[in] s32Chn Դͨ����
 \param[in] enStreamType ��������
 \param[in] BUF_STREAM_ATTR_S stStreamAttr  ��������
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
 */
int VS_BUF_SetStreamAttr(const int s32Chn,
                            const VS_STREAM_TYPE_E enStreamType,
                            const BUF_STREAM_ATTR_S *pstStreamAttr);


 /**
 \brief ��ȡ��������
 \attention \n
 \param[in] s32Chn Դͨ����
 \param[in] enStreamType ��������
 \param[out] BUF_STREAM_ATTR_S pstStreamAttr  ������������
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
 */
int VS_BUF_GetStreamAttr(const int s32Chn,
                            const VS_STREAM_TYPE_E enStreamType,
                            BUF_STREAM_ATTR_S *pstStreamAttr);
 
 /**
 \brief ��ȡ��ָ��λ��
 \attention \n
 \param[in] int s32ReaderId  ��ָ��ID
 \param[in] VS_BUF_POSITION_POLICY_E enPolicy  ��ȡ��ָ�뷽ʽ
 \param[in] int s32N  ���I֡��
 \param[out] VS_BUF_READPTR_INFO_S *pstReadptr ���ض�ָ��λ����Ϣ
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
    ::BUF_CanRead
    ::BUF_SetReadPtrPos
 */
int VS_BUF_GetReadPtrPos(int s32ReaderId,
                           BUF_POSITION_POLICY_E enPolicy,
                           int s32N,
                           BUF_READPTR_INFO_S *pstReadptr);

 /**
 \brief �����Ƿ��ܶ�
 \attention \n
 \param[in] int s32ReaderId  ��ָ��ID
 \param[in] unsigned int u32Len   ����
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
    ::BUF_GetReadPtrPos
 */
int VS_BUF_CanRead(int s32ReaderId,
                      unsigned int u32Len);

 /**
 \brief ���ö�ָ��λ��
 \attention \n
 \param[in] int s32ReaderId  ��ָ��ID
 \param[in] unsigned int u32Len   ����
 \retval ::HI_SUCCESS  �ɹ�
         ::HI_EPAERM   �����������
         ::HI_ENOTINIT Bufferδ����
 \see \n
    ::BUF_GetReadPtrPos
 */
int VS_BUF_SetReadPtrPos(int s32ReaderId,
                            unsigned int u32Len);

 /**
 \brief ��ȡBUF�����ַ
 \attention \n
 \param[in] int s32Chn  ͨ����
 \param[in] VS_STREAM_TYPE_E enStreamType ��������
 \retval 
         ::BUF�����ַ   
         ::NULL ʧ��
 \see \n
    ::VS_BUF_GetBufPhyAddr
 */
unsigned int VS_BUF_GetBufPhyAddr(const int s32Chn,const VS_STREAM_TYPE_E enStreamType);

 /**
 \brief ��ȡBUF��С
 \attention \n
 \param[in] int s32Chn  ͨ����
 \param[in] VS_STREAM_TYPE_E enStreamType ��������
 \retval 
         ::BUF��С
         ::0 ʧ��
 \see \n
    ::VS_BUF_GetBufSize
 */

unsigned int VS_BUF_GetBufSize(const int s32Chn,const VS_STREAM_TYPE_E enStreamType);

 /**
 \brief ��ȡһ֡����
 \attention \n
 \����һ֡���ݵ�ָ��
 \param[in] int s32ReaderId  readerid
\param[in] BUF_POSITION_POLICY_E enPolicy ��ȡ֡��ʽ
\param[in] int  s32N ���֡��
\param[out] VS_FRAME_TYPE_E *penFrameType ����֡����
\param[out] unsigned char **pu8Start ����֡��ַ
\param[out] unsigned int * Pu8StartOffset ����֡��Ե�ַ
\param[out] unsigned int *pu32Len ����֡����
\param[out] unsigned long long *pu64Pts  ����֡ʱ���
\param[out] unsigned int * pu32PacketNo ����֡���
\param[out] int * ps32Width ����֡���
\param[out] int * ps32Height  ����֡�߶�
\param[in] unsigned char u8IOblock �Ƿ�������ȡ
 \retval 
         :: HI_SUCCESS  �ɹ�
         ::���� ʧ��
 \see \n
    ::VS_BUF_GetFramePtr
 */

  int VS_BUF_GetFramePtr(int s32ReaderId, BUF_POSITION_POLICY_E enPolicy,int s32N,VS_FRAME_TYPE_E *penFrameType,unsigned char **pu8Start,
  unsigned int * Pu8StartOffset,unsigned int *pu32Len,unsigned long long *pu64Pts , unsigned int * pu32PacketNo , int * ps32Width , int * ps32Height ,unsigned char u8IOblock);

   /**
 \brief ��ȡ��д�ڴ�ָ��
 \attention \n
 \����д�ڴ�ָ�룬��VS_BUF_ReleaseWriteMemPos�ɶ�ʹ��
 \param[in] int s32Chn ͨ����
\param[in] VS_STREAM_TYPE_E enStreamType ��������
\param[in] unsigned int u32Size �����ڴ��С
 \retval 
         :: ��д�ڴ�ָ��
         ::0 ʧ��
 \see \n
    ::VS_BUF_GetWriteMemPos
 */

unsigned char * VS_BUF_GetWriteMemPos(const int s32Chn,const VS_STREAM_TYPE_E enStreamType , unsigned int u32Size);

   /**
 \brief �ͷſ�д�ڴ�ָ��
 \attention \n
 \�ͷſ�д�ڴ�ָ�룬дָ����ǰ�ƶ�һ֡�����֡ͷ��Ϣ(��������֡����)��VS_BUF_GetWriteMemPos����ʹ��
 \���u32Len = 0 �����֡ͷ��Ϣ
 \param[in] int s32Chn ͨ����
\param[in] VS_STREAM_TYPE_E enStreamType ��������
\param[in] VS_FRAME_TYPE_E enFrameType ֡����
\param[in] unsigned int u32Len ֡��С
\param[in] unsigned long long u64Pts ʱ���
\param[in] VS_DATETIME_S *pTime ʱ����Ϣ

 \retval 
         :: ��д�ڴ�ָ��
         ::0 ʧ��
 \see \n
    ::VS_BUF_GetWriteMemPos
 */
int VS_BUF_ReleaseWriteMemPos(const int s32Chn,const VS_STREAM_TYPE_E enStreamType,
VS_FRAME_TYPE_E enFrameType,unsigned int u32Len,unsigned long long u64Pts, VS_DATETIME_S *pTime);


   /**
 \brief��ȡ��һ֡������
 \attention \n
 \param[in] int s32ReaderId readerid
\param[in] BUF_POSITION_POLICY_E enPolicy ��һ֡��֡��ʽ
\param[in] unsigned int s32N ���֡��
\param[out] VS_FRAME_TYPE_E *penFrameType ֡����
\param[in] unsigned char u8IOblock  �Ƿ�����

 \retval 
         :: ��д�ڴ�ָ��
         ::0 ʧ��
 \see \n
    ::VS_BUF_GetWriteMemPos
 */
 int VS_BUF_GetNextFrameType(int s32ReaderId, BUF_POSITION_POLICY_E enPolicy,
                        int s32N,VS_FRAME_TYPE_E *penFrameType, unsigned char u8IOblock);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /*__VS_BUFFER_H__*/
