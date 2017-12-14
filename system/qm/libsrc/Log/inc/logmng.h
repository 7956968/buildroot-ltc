
#ifndef _LOG_MNG_H_
#define _LOG_MNG_H_

#include "QMAPIType.h"
#include "QMAPICommon.h"
#include "QMAPINetSdk.h"

/******************************************************************************************************
  ͷ��Ϣ����256�ֽڶ���               ��־������Ϣ             ��չ��
|              QMAPI_LOG_HEADER           |    QMAPI_LOG_INDEX * index_max     | block_size  *  block_max |

*******************************************************************************************************/

typedef struct tagQMAPI_LOG_HEADER
{
	char			magic[8];			//log_dms
	char			version[8];			//1.0

	unsigned long	ver_date;			//20151026
	unsigned long	file_size;			//�ļ���С

	unsigned long	offset_index;		//������ʼƫ��
	unsigned long	index_size;			//һ��������С
	unsigned long	index_max;			//���������
	unsigned long	curr_index;			//��ǰд����������   д��indexĩβ����д������չblock�Ż�д��

	unsigned long	offset_block;		//����ʼƫ��
	unsigned long 	block_size; 			//���С
	unsigned long	block_max;			//�������
	unsigned long	curr_block;			//��ǰд��Ŀ����  �����ʵʱ����
	
	BYTE 		index_used_flag; 		//ÿ��д���ļ�ĩβ����������ǣ�1����2
	BYTE 		recv[3];

	BYTE 		block_used[QMAPI_LOG_BLOCK_MAX]; 		//���Ƿ�ʹ��
}QMAPI_LOG_HEADER;

/*
typedef struct tagQMAPI_LOG_INDEX
{
	BYTE bUsed;//��ӦQMAPI_LOG_HEADER��currUsedFlag
	BYTE mainType;//��־������//QMAPI_LOG_MAIN_TYPE_E
	BYTE subType;//��ϸ����
	BYTE chnn;
	
	unsigned long time;//����������ʱ��
	unsigned long ip;
	
	BYTE userID;
	BYTE blockID;//��1��ʼ0��ʾ����չ
	BYTE recv[2];//3//Ԥ��
}QMAPI_LOG_INDEX;*/

typedef struct tagQMAPI_LOG_INFO
{
	QMAPI_LOG_MAIN_TYPE_E maintype;
	unsigned long subtype;
	unsigned long ip;
	BYTE chnn;
       union
        {
            BYTE byUserID;
            BYTE byAlarmEnd;
        };
	
	BYTE byUsedExInfo;
	BYTE recv;
	char pExInfo[QMAPI_LOG_BLOCK_SIZE];
}QMAPI_LOG_INFO;

int DmsLog_Init(const char * plogPath);
void DmsLog_Quit();

int Update_PowerOnTime();
int Repair_LogTime();

int Wirte_Log(const QMAPI_LOG_INFO* pLogInfo);

void Search_Log(QMAPI_LOG_MAIN_TYPE_E maintype, unsigned long subType, QMAPI_LOG_INDEX* pLogIndex, unsigned int* pNum, char (*pLogExtInfo)[QMAPI_LOG_BLOCK_SIZE], unsigned int extInfoBufLen);

int Get_LogExtInfo(const QMAPI_LOG_INDEX *logInfo, char* pBuf, unsigned int* pLen);

#endif

