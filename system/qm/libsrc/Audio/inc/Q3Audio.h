
#ifndef __Q3AUDIO_H__
#define __Q3AUDIO_H__

#include "QMAPICommon.h"
#include "QMAPINetSdk.h"
#include "QMAPIDataType.h"
#include "QMAPIErrno.h"
#include "QMAPI.h"

#define AUDIO_BUF_SIZE			1024

typedef struct{
	int wFormatTag; /*������Ƶ��ʽ QMAPI_PT_G726 ��*/
	int channel;    /*ͨ����*/
	int bitwidth;   /*λ��*/
	int sample_rate; /**/
	int volume;    /*���� Ĭ�� 256*/
	int res[4];
}Q3_Audio_Info;

/*
	��Ƶ�����ʼ��,�ɹ����ط�0��handle��ʧ�ܷ���0
		Info [in]:
*/
int QMAPI_Audio_Decoder_Init(Q3_Audio_Info *Info);
int QMAPI_Audio_Decoder_UnInit(int handle);
/*
	��Ƶ���ݽ��룬�ɹ�����TRUE��ʧ�ܷ���FALSE��ʧ����ҪQ3_Audio_Decoder_UnInit
		handle   [in]:
		data     [in]:
		dataSize [in]:
*/
int QMAPI_Audio_Decoder_Data(int handle, char *data, int dataSize);

// ������Ƶ��ʼ������
int QMAPI_Audio_Init(void *param);
int QMAPI_Audio_UnInit(int handle);

int QMAPI_Audio_Start(int handle);
int QMAPI_Audio_Stop(int handle);

/*
	������Ƶ���ݻص�����
		pfun    [in]:
*/
int QMAPI_AudioStreamCallBackSet(CBAudioProc pfun);
#endif
