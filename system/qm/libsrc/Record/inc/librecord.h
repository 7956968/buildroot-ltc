
#ifndef _LIB_RECORD_H_
#define _LIB_RECORD_H_
#include "hd_mng.h"
#include <stdio.h>
#include "QMAPI.h"

#define MAX_RECORD_TIME (10*60*1000) /*10���� ��λ����*/
#define MAX_PLAY_CALL_BACK 8 /* ���֧��8 ���ص�*/

int REC_FindFile(QMAPI_NET_FINDDATA *pFileDataArray, 
			                int maxNum,
			                unsigned int nFileType,
			                unsigned int nChannel,
			                QMAPI_TIME struStartTime,
			                QMAPI_TIME struStopTime);
int REC_FindNextFile(int Handle, int FindHandle, LPQMAPI_NET_FINDDATA lpFindData);
int PlayBackByName(int Handle,char *csFileName);
int PlayBackStop(int Handle, int PlayHandle);
int PlayBackGetInfo(int Handle, int PlayHandle, QMAPI_RECFILE_INFO *pRecFileInfo);
int PlayBackGetReadPtrPos(int Handle, int PlayHandle, QMAPI_NET_DATA_PACKET *pstReadptr,LPQMAPI_TIME lpFrameTime);
int PlayBackAddDataCallBack(int Handle, int FindHandle, CBPlayProc Callback, DWORD dwUser);
int PlayBackDelDataCallBack(int Handle, int FindHandle, CBPlayProc Callback, DWORD dwUser);
int PlayBackControl(int Handle, int PlayHandle, DWORD dwControlCode, const char *lpInBuffer, DWORD dwInLen, char *lpOutBuffer, DWORD *lpOutLen);

/* FtpModeInit
  ¼��ģ���ʼ��
  ����ֵ:0: �ɹ�, -1:ʧ��
 */
int REC_Init();

void REC_UnInit();

/* 
  Start_Record
  ����¼����
  nTrigerType: TRIGER_XXXX
  nDuration: ¼��ʱ��,��λΪ���룬nDuration==0�����ֶ�ֹͣ��ƻ�ʱ��ʱ��ֹͣ
  ����ֵ: 0:ִ�гɹ�, -1:ִ��ʧ��
  
 */
int REC_StartRecord(int nStartType, int nTrigerType, int nChannel, DWORD nDuration);

/* Stop_Record
  �ر�¼��
  nTrigerType: TRIGER_XXXX
  ����ֵ: 0:ִ�гɹ�, -1:ִ��ʧ��
 */
int REC_StopRecord(int nTrigerType, int nChannel);

/* 	StopAllRecord
  	�ر���������¼�Ƶ��ļ�
 */
void REC_StopAllRecord(int type);

/*
	
*/
int REC_GetDiskRecordStatus(int nDiskNo);

#endif

