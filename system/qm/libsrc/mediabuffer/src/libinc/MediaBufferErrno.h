

#ifndef __HI_COMMON_ERRNO_H__
#define __HI_COMMON_ERRNO_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/

//#define HI_ERR_APPID         (0x80UL + 0x28UL)
/******************************************************************************
|----------------------------------------------------------------| 
| 1 |   APP_ID   |   MOD_ID    | ERR_LEVEL |   ERR_ID            | 
|----------------------------------------------------------------| 
|<--><--7bits----><----8bits---><--4bits---><------12bits------->|
******************************************************************************/

#define HI_COMMON_ERR(appid, modid, level, errid) \
    ( (HI_S32)((((HI_U32)(appid))<<24) | (((HI_U32)(modid) ) << 16) | (((HI_U32)(level))<<12) | (((HI_U32)(errid)) & 0xFFF )))


/*************************************************************************
  ģ������붨�巽��
*************************************************************************/

/* ����4���ȼ�*/
typedef enum hiERRLEVEL_E
{
    HI_ERRLEVEL_DEBUG = 0,   /* debug-level                                  */
    HI_ERRLEVEL_INFO,        /* informational                                */
    HI_ERRLEVEL_ERROR,       /* error conditions                             */
    HI_ERRLEVEL_FATAL,       /* fatal error,make system disable */
    HI_ERRLEVEL_BUTT
} HI_ERRLEVEL_E;


/*----------------------------------------------*
 * ���������붨��                               *
 *----------------------------------------------*/

#define HI_ERRNO_COMMON_BASE    0x10000000
#define HI_ERRNO_COMMON_COUNT   0x100

#define HI_EUNKNOWN             (HI_ERRNO_COMMON_BASE + 1)    /* ����ԭ��δ֪��ȷ���Ѿ������ǲ����ж������ԭ�� */
#define HI_EOTHER               (HI_ERRNO_COMMON_BASE + 2)    /* ��������֪������ԭ�������Թ��� */
#define HI_EINTER               (HI_ERRNO_COMMON_BASE + 3)    /* �ڲ����������ڲ��������Դ���ĳЩ�ڴ������CPU�Բ��I/O����ѧ����������ȵ� */
#define HI_EVERSION             (HI_ERRNO_COMMON_BASE + 4)    /* �汾���� */
#define HI_EPAERM               (HI_ERRNO_COMMON_BASE + 5)    /* �������󣬰������������������ò����������ò�����һ�»��г�ͻ�����ʵ��ı�š�ͨ���š��豸�š���ָ�롢��ַ��������ȵ� */
#define HI_EINVAL               (HI_ERRNO_COMMON_BASE + 6)    /* ��֧�ֵĲ���/����/���ԣ����������汾����δ���İ汾����������Ʒ����֧�� */
#define HI_ENOTINIT             (HI_ERRNO_COMMON_BASE + 7)    /* û�г�ʼ����ĳЩ�����������Ƚ��г�ʼ������ܽ��У�����δ���� */
#define HI_ENOTREADY            (HI_ERRNO_COMMON_BASE + 8)    /* û��׼���ã�ĳЩ���������ھ߱�һ����������ܽ��У�������Ҫ�Ļ�������ȷ������ȱ���������Դ */
#define HI_ENORES               (HI_ERRNO_COMMON_BASE + 9)    /* û����Դ�����������ڴ�ʧ�ܡ�û�п��л�������û�п��ж˿ڡ�û�п���ͨ���� */
#define HI_EEXIST               (HI_ERRNO_COMMON_BASE + 0xA)  /* ��Դ�Ѵ��ڣ���������½�����Դ�Ѿ����ڣ������������� */
#define HI_ELOST                (HI_ERRNO_COMMON_BASE + 0xB)  /* ��Դ�����ڣ�������ĳ����Դ����ַ���Ự������ */
#define HI_ENOOP                (HI_ERRNO_COMMON_BASE + 0xC)  /* ��Դ���ɲ������������𻵲���ʹ�á�У�����δ����Ԥ�ڵ����á��豸�����ݵȵ� */
#define HI_EBUSY                (HI_ERRNO_COMMON_BASE + 0xD)  /* ��Դ��æµ�����类���� */
#define HI_EIDLE                (HI_ERRNO_COMMON_BASE + 0xE)  /* ��Դ������ */
#define HI_EFULL                (HI_ERRNO_COMMON_BASE + 0xF)  /* ����ĳ���������Ѿ������� */
#define HI_EEMPTY               (HI_ERRNO_COMMON_BASE + 0x10) /* �գ�ĳ���������ǿյ� */
#define HI_EUNDERFLOW           (HI_ERRNO_COMMON_BASE + 0x11) /* ���磬ĳ�������е������Ѿ��½�������ˮ��֮�� */
#define HI_EOVERFLOW            (HI_ERRNO_COMMON_BASE + 0x12) /* ���磬ĳ�������е���������������ˮ��֮�� */
#define HI_EACCES               (HI_ERRNO_COMMON_BASE + 0x13) /* Ȩ�޴�������û��Ȩ�ޡ��������ȵ� */
#define HI_EINTR                (HI_ERRNO_COMMON_BASE + 0x14) /* ����δ��ɣ��Ѿ��ж� */
#define HI_ECONTINUE            (HI_ERRNO_COMMON_BASE + 0x15) /* ����δ��ɣ����ڼ��� */
#define HI_EOVER                (HI_ERRNO_COMMON_BASE + 0x16) /* ������ɣ���û�к����Ĳ������� */
#define HI_ERRNO_COMMON_BUTTOM  (HI_ERRNO_COMMON_BASE + 0x17) /* �Ѷ���Ĵ���Ÿ��� */
#define HI_ENOSYS               (HI_ERRNO_COMMON_BASE + 0x18) /* ϵͳ��֧�� */

//[2011-4-12 15:42:14] 
#define HI_ERROR_NO_FINDDEV		(HI_ERRNO_COMMON_BASE + 0x80)	//û�з����豸
#define HI_ERROR_NO_FINDFILE	(HI_ERRNO_COMMON_BASE + 0x81)	//û�з����ļ�
#define HI_ERROR_FILE_CRC		(HI_ERRNO_COMMON_BASE + 0x82)	//�ļ�CRCУ���
#define HI_ERROR_FILE_READ		(HI_ERRNO_COMMON_BASE + 0x83)	//�ļ�������
/*************************************************************************
  ģ���Զ���������
*************************************************************************/
#define HI_ERRNO_BASE           (-HI_ERRNO_COMMON_BASE + HI_ERRNO_COMMON_COUNT)

#define HI_ERR_AUTHMNG_PARAM    (HI_ERRNO_COMMON_BASE + 0x10000)	/*�����������*/
#define HI_ERR_AUTHMNG_NO_EXIST (HI_ERRNO_COMMON_BASE + 0x10001)	/*�û�������*/
#define HI_ERR_AUTHMNG_PASSWORD (HI_ERRNO_COMMON_BASE + 0x10002)	/*�û��������*/

#define HI_S2_ERR_APPID         (0x80UL + 0x38UL)

/* ����4���ȼ�*/
typedef enum hiS2_ERRLEVEL_E
{
    HI_S2_ERRLEVEL_DEBUG = 0,   /* debug-level                                  */
		HI_S2_ERRLEVEL_INFO,        /* informational                                */
		HI_S2_ERRLEVEL_ERROR,       /* error conditions                             */
		HI_S2_ERRLEVEL_FATAL,       /* just for compatibility with previous version */
		HI_S2_ERRLEVEL_BUTT
} HI_S2_ERRLEVEL_E;

/* ==Ϊ���ּ���==*/
typedef enum hiSVR_ERRLEVEL_E
{
    HI_SVR_ERRLEVEL_DEBUG = 0,  /* debug-level                                  */
		HI_SVR_ERRLEVEL_INFO,       /* informational                                */
		HI_SVR_ERRLEVEL_ERROR,      /* error conditions                             */
		HI_SVR_ERRLEVEL_FATAL,      /* just for compatibility with previous version */
		HI_SVR_ERRLEVEL_BUTT
} HI_SVR_ERRLEVEL_E;


#define HI_S2_ERR( modid, level, errid) \
( (HI_S32)((HI_S2_ERR_APPID)<<24) | ((modid) << 16 ) | ((level)<<12) | ((errid) & 0xFFF) )

/* ==Ϊ���ּ���==*/
#define HI_SVR_ERR( modid, level, errid) \
( (HI_S32)((HI_S2_ERR_APPID)<<24) | ((modid) << 16 ) | ((level)<<12) | ((errid) & 0xFFF) )


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __HI_COMMON_ERRNO_H__ */


