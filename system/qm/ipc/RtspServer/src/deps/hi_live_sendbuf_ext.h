#ifndef __HI_LIVE_SENDBUF_EXT_H__
#define __HI_LIVE_SENDBUF_EXT_H__



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

 





HI_S32 HI_LiveSendBuf_Init(HI_S32 maxUserNum,HI_S32 maxBufSize);


/*MBUF���٣������ͷ��ڴ��Լ��������*/
HI_S32 HI_LiveSendBuf_Deinit();

/*
����һ��mbuf
ChanID ���������MBUFͨ����
pphandle �������������ָ��buf handle��ָ��
*/
HI_S32 HI_LiveSendBuf_Alloc(HI_S32 ChanID, HI_VOID **pphandle);

/*
�ͷ�һ��mbuf
pphandle �������������ָ����ͷ�mbuf handle��ָ�룬
                �ɹ��ͷź�*pphandle = NULL
*/
HI_S32 HI_LiveSendBuf_Free(HI_VOID **pphandle);

/*MBUF ��Ƶ����Ƶ������ע�ắ��
HI_TRUE ʹ�ܣ�HI_FALSE ��ֹ*/
HI_S32 HI_LiveSendBuf_Register(HI_VOID *phandle, MBUF_VIDEO_STATUS_E video_status, HI_BOOL audio_enable, HI_BOOL data_enable);

/*MBUF ��ȡ��Ƶ����Ƶ������ע��״̬����
HI_TRUE ʹ�ܣ�HI_FALSE ��ֹ*/
HI_VOID HI_LiveSendBuf_GetRegister(HI_VOID *phandle, MBUF_VIDEO_STATUS_E* pvideo_status, HI_BOOL* paudio_enable, HI_BOOL* pdata_enable);

/*�ṩ��ý�崦��ģ��Ľӿں���������������bufд������
�ú���������ChanID������Ӧ��busy list*/

                   
HI_S32 HI_LiveSendBuf_Read(HI_VOID *phandle, HI_ADDR*paddr, HI_U32 *plen, 
            HI_U64 *ppts, MBUF_PT_E *ppayload_type,HI_U8 *pslice_type, 
            HI_U32 *pslicenum, HI_U32 *pframe_len);

HI_VOID HI_LiveSendBuf_Set(HI_VOID *phandle);

HI_S32 HI_LiveSendBuf_GetPts(HI_VOID *phandle,HI_U64* pU64Pts);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */



#endif




