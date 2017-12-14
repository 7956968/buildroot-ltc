
#ifndef __QMAPI_RECORD_H__
#define __QMAPI_RECORD_H__


#include "QMAPIType.h"
#include "QMAPINetSdk.h"
#include "QMAPIErrno.h"
#include "QMAPI.h"

#define EVENT_RECORD "record_notify"

typedef enum {
    RECORD_NOTIFY_START,
    RECORD_NOTIFY_FINISH,
    RECORD_NOTIFY_ERROR,
    RECORD_NOTIFY_HD_FULL,
} RECORD_NOTIFY_TYPE_E;

typedef struct {
    RECORD_NOTIFY_TYPE_E type;
    void *arg;
} RECORD_NOTIFY_T;

typedef struct {
    int trigger;
    char *name;
} RECORD_FILE_T;

typedef int (*record_callback)(RECORD_FILE_T *file);

typedef enum {
    MEDIA_RECMODE_FULLTIME=0, 
    MEDIA_RECMODE_MOTDECT
} MEDIA_REC_MODE_E;

typedef enum {
    MEDIA_REC_STREAM_HIGH = 0,
    MEDIA_REC_STREAM_MID 
} MEDIA_REC_STREAM_E;

typedef enum {
    MEDIA_REC_AV_FORMAT_MKV = 0,
    MEDIA_REC_AV_FORMAT_MP4 
} MEDIA_REC_AV_FORMAT_E;

typedef enum {
    MEDIA_REC_AUDIO_FORMAT_G711A = 0,
    MEDIA_REC_AUDIO_FORMAT_AAC 
} MEDIA_REC_AUDIO_FORMAT_E;

typedef struct {
    int mode;
    int duration;

    int videoEnable;
    int videoStream;

    int audioEnable;
    int audioStream;

    MEDIA_REC_AV_FORMAT_E avFormat;
    MEDIA_REC_AUDIO_FORMAT_E audioFormat;
} RECORD_ATTR_T;

//Triger����
#define TRIGER_UNKNOW	0	//δ֪
#define TRIGER_SCHED	 0x000001 //��ʱ¼��
#define TRIGER_MOTION  0x000002  //�Ƶ����¼��
#define TRIGER_ALARM   0x000004  //����¼��
#define TRIGER_CMD     0x000008  //����¼��
#define TRIGER_MANU    0x000010  //�ֹ�¼��
#define TRIGER_UMOUNT  0x000020  //UMOUNT SD/UDISK

/************************************* ���� ***************************************************************/


//����˵����
//dwDataType��1ϵͳͷ����;2 ������, 3����
//pBuffer��������ݵĻ�����ָ�� (����NULL��ʾ��ȡ���ݽ���)
//dwBufSize: ��������С 
//stFrameHeader:֡ͷ��Ϣ
//dwUser: �û�����
typedef void (*fNetPlayDataCallBack)(DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize, QMAPI_NET_FRAME_HEADER stFrameHeader, ULONGLONG TimeTick, DWORD dwUser);

/**************************************************************************************************
	ģ���ʼ��
		QMAPI_Record_Init ģ���ʼ��, �ɹ����ز��������ʧ�ܷ���0
			lpDeafultParam [in]:

		QMAPI_Record_UnInit ģ�鷴��ʼ��, �ɹ�����QMAPI_RECORD_SUCCESS
			Handle   [in]: ��ʼ���ɹ������ľ��
*/
int QMAPI_Record_Init(void *lpDeafultParam, record_callback callback);
int QMAPI_Record_UnInit(int Handle);

/**************************************************************************************************
	ģ��¼������ͣ
		QMAPI_Record_Start ģ��¼���������ɹ�����QMAPI_RECORD_SUCCESS
			Handle       [in]: ��ʼ���ɹ������ľ��
			nTrigerType  [in]: 
			nChannel     [in]: ͨ����
			
		QMAPI_Record_Stop ģ��¼��ֹͣ���ɹ�����QMAPI_RECORD_SUCCESS
			Handle       [in]: ��ʼ���ɹ������ľ��
			nTrigerType  [in]:
			nChannel     [in]: ͨ����

//Triger����
#define TRIGER_UNKNOW	0	//δ֪
#define TRIGER_SCHED	 0x000001 //��ʱ¼��
#define TRIGER_MOTION  0x000002  //�Ƶ����¼��
#define TRIGER_ALARM   0x000004  //����¼��
#define TRIGER_CMD     0x000008  //����¼��
#define TRIGER_MANU    0x000010  //�ֹ�¼��
#define TRIGER_UMOUNT  0x000020  //UMOUNT SD/UDISK
*/
int QMAPI_Record_Start(int Handle, int nTrigerType, int nChannel);
int QMAPI_Record_Stop(int Handle, int nTrigerType, int nChannel);

/*****************************************************************************************************
	ģ���������
	Handle     [in ]: QMAPI_Record_Init �ɹ������ľ��
	nCmd       [in ]: ��������
	nChannel   [in ]:
	Param      [in ][out]: ���롢������棻
	nSize      [in ]: ���뻺���С

	//ͼ��¼��QMAPI_NET_CHANNEL_RECORD�ṹ��
#define QMAPI_SYSCFG_GET_RECORDCFG				(QMAPI_RECORD_MODULE+0xF300)	// ��ȡͼ��¼����� 
#define QMAPI_SYSCFG_SET_RECORDCFG				(QMAPI_RECORD_MODULE+0xF301)	// ����ͼ��¼����� 
#define QMAPI_SYSCFG_GET_DEF_RECORDCFG			(QMAPI_RECORD_MODULE+0xF302)

	//ͼ���ֶ�¼��QMAPI_NET_CHANNEL_RECORD�ṹ)
#define QMAPI_SYSCFG_GET_RECORDMODECFG			(QMAPI_RECORD_MODULE+0xF320)	// ��ȡͼ���ֶ�¼����� 
#define QMAPI_SYSCFG_SET_RECORDMODECFG			(QMAPI_RECORD_MODULE+0xF321)	// ����ͼ���ֶ�¼����� 

*/
int QMAPI_Record_IOCtrl(int Handle, int nCmd, int nChannel, void* Param, int nSize);


/*********************************************************************************
�ļ���ѯϵ�к�����
	QMAPI_Record_FindFile ��ʼ�����ļ����ɹ����ز�ѯ�����ʧ�ܷ���0��
		Channel   [in]:  ͨ����
		pFindCond [in]:  ��ѯ����

	QMAPI_Record_FindFileNumber ��ȡ��ѯ�ļ��������ɹ�����ʵ�ʲ�ѯ������ʧ�ܷ���QMAPI_FAILURE��
		Channel   [in]:  ͨ����
		FindHandle[in]:  QMAPI_Record_FindFile ���صĲ�ѯ���

	QMAPI_Record_FindNextFile ��ѯ�¸��ļ���Ϣ.�ɹ�����QMAPI_NET_FILE_SUCCESS��
		Channel    [in]:  ͨ����
		FindHandle [in]:  QMAPI_Record_FindFile ���صĲ�ѯ���
		lpFindData [out]: ʵ���ļ�����Ϣ��(���ȡ���ʼʱ�䡢���͵�)

	QMAPI_Record_FindClose �رղ�ѯ
		Channel   [in]:  ͨ����
		FindHandle[in]:  QMAPI_Record_FindFile ���صĲ�ѯ���
		
**********************************************************************************/
int QMAPI_Record_FindFile(int Channel, LPQMAPI_NET_FILECOND pFindCond);
int QMAPI_Record_FindFileNumber(int Channel, int FindHandle);
int QMAPI_Record_FindNextFile(int Channel, int FindHandle, LPQMAPI_NET_FINDDATA lpFindData);
int QMAPI_Record_FindClose(int Channel, int FindHandle);



/*********************************************************************
�ط�ϵ��1�����ݻ�ȡ��ʽ
	QMAPI_Record_PlayBackByName
		Channel   [in]:
		csFileName[in]:

	QMAPI_Record_PlayBackGetReadPtrPos
		Channel    [in ]:
		PlayHandle [in ]:
		pstReadptr [out]:
		lpFrameTime[out]:

	QMAPI_Record_PlayBackGetInfo
		Channel     [in ]:
		PlayHandle  [in ]:
		pRecFileInfo[out]:

	QMAPI_Record_PlayBackControl
		Channel       [in ]:
		PlayHandle    [in ]:
		dwControlCode [in ]:
		lpInBuffer    [in ]:
		dwInLen       [in ]:
		lpOutBuffer   [out]:
		lpOutLen      [out]:

	QMAPI_Record_PlayBackStop
		Channel       [in ]:
		PlayHandle    [in ]:
********************************************************************/
int QMAPI_Record_PlayBackByName(int Channel,char *csFileName);
int QMAPI_Record_PlayBackGetReadPtrPos(int Channel, int PlayHandle, QMAPI_NET_DATA_PACKET *pstReadptr, LPQMAPI_TIME lpFrameTime);
int QMAPI_Record_PlayBackGetInfo(int Channel,int PlayHandle,QMAPI_RECFILE_INFO *pRecFileInfo);
int QMAPI_Record_PlayBackControl(int Channel, int PlayHandle,DWORD dwControlCode,char *lpInBuffer,DWORD dwInLen,char *lpOutBuffer,DWORD *lpOutLen);
int QMAPI_Record_PlayBackStop(int Channel, int PlayHandle);



/*********************************************************************
�ط�ϵ��2���������ͷ�ʽ
	QMAPI_Record_PlayBackAddCallBack ����������ͻص��������ɹ�����QMAPI_SUCCESS
		Channel       [in ]:  ͨ����
		FindHandle    [in ]:  ��ѯ�����ľ��
		Callback      [in ]:  ���ݻص�����
		dwUser        [in ]:  �û�ָ��

	QMAPI_Record_PlayBackDelCallBack ɾ���������ͻص��������ɹ�����QMAPI_SUCCESS
		Channel       [in ]:  ͨ����
		FindHandle    [in ]:  ��ѯ�����ľ��
		Callback      [in ]:  ���ݻص�����
		dwUser        [in ]:  �û�ָ��

	QMAPI_Record_PlayBackDelAll ɾ�������������ͻص��������ɹ�����QMAPI_SUCCESS
		
		
********************************************************************/
int QMAPI_Record_PlayBackAddCallBack(int Channel, int FindHandle, CBPlayProc Callback, DWORD dwUser);
int QMAPI_Record_PlayBackDelCallBack(int Channel, int FindHandle, CBPlayProc Callback, DWORD dwUser);
int QMAPI_Record_PlayBackDelAll(void);


#endif //
