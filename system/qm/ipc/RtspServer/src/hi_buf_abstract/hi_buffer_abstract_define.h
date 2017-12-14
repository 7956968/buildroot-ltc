


#ifndef __HI_BUFFER_ABSTRACT_DEFINE__
#define __HI_BUFFER_ABSTRACT_DEFINE__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#include "hi_mbuf.h"



/**��ͨ�����û�ģʽ�£���buffer��������Ϣ*/
typedef struct hiLIVE_1CHNnUSER_BUFINFO
{
	HI_S32 chnnum;   /**ͨ����*/
	MBUF_CHENNEL_INFO_S *pMbufCfg;/**����ͨ���ܵ㲥���û����ݣ��Լ�ÿ���û���buffer��Ϣ*/
}LIVE_1CHNnUSER_BUFINFO_S;

/**��ͨ�����û�ģʽ�£��Է���buffer��������Ϣ*/
typedef struct hiLIVE_1CHN1USER_BUFINFO
{
	HI_S32 maxUserNum;  /**֧�ֵ��û������*/
	HI_S32 maxFrameLen;/**����֡����*/
}LIVE_1CHN1USER_BUFINFO_S;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif



