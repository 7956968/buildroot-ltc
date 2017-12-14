// FileRander_ASF.h: interface for the CFileRander_ASF class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _FILE_RANDER_ASF_H
#define _FILE_RANDER_ASF_H

//#include "JB_common.h"
#include "QMAPIType.h"
#include "QMAPINetSdk.h"
#include "JBFileFormat.h"

/*#include "jb_xtream_producer_config.h"
#include "jb_xtream_producer_keytypes.h"
*/
#define TRACE printf
#define TRACE0(fmt, args...) do {} while(0)

#define MAX_STREAM_BUFF_SIZE 512*1024
#define VIDEO_XVID  0x58564944
#define VIDEO_H264  0x34363248
#define VIDEO_MJPEG 0x47504A4D
#define VIDEO_H265	0x35363248

#define	ENCODE_FORMAT_MGPE4				0x0
//#define	ENCODE_FORMAT_H264				0x2
#define	ENCODE_FORMAT_H264				0x4
#define  ENCODE_FORMAT_MJPEG				0x5
#define  ENCODE_FORMAT_H265				265

typedef struct tagJB_STREAM_BUFFER
{
	DWORD dwSize;
	DWORD dwPosition;
	DWORD dwTimeTick;
	DWORD FrameType;
	BYTE  pBuffer[MAX_STREAM_BUFF_SIZE];
}JB_STREAM_BUFFER,*PJB_STREAM_BUFFER;
typedef struct tagFilePlay_INFO
{
	DWORD   dwSize;
	DWORD   dwStream1Height;			//��Ƶ��(1)
	DWORD   dwStream1Width;			//��Ƶ��
	DWORD   dwStream1CodecID;			//��Ƶ�������ͺţ�MPEG4Ϊ0��JPEG2000Ϊ1,H264Ϊ2��
	DWORD   dwAudioChannels;			//��Ƶͨ����
	DWORD   dwAudioBits;				//��Ƶ������
	DWORD   dwAudioSamples;			//��Ƶ������
	DWORD   dwWaveFormatTag;			//��Ƶ�������ͺ�
	char	csChannelName[MAX_CHANNEL_NAME_LEN];			//ͨ������
	DWORD	dwFileSize;
	DWORD	dwTotalTime;			/*�ļ�����ʱ�䳤��*/
	DWORD	dwPlayStamp;			/*ʱ���*/
	DWORD  dwFrameRate;
} FilePlay_INFO, *PFilePlay_INFO;

typedef struct tagPLAYFILE_INFO
{
    HANDLE hFileHandle;	//FILE_RANDER_ASF
    QMAPI_TIME BeginTime;//�ļ���ʼʱ��
    QMAPI_TIME EndTime;//�ļ�����ʱ��
    QMAPI_TIME CurTime;
    QMAPI_TIME StartTime;//������ʼʱ��
    QMAPI_TIME StopTime;//��������ʱ��
    int index;
    unsigned int firstReads;//0:δ��ʼ����1:�Ѿ���ʼ
    unsigned long lastTimeTick;//��һ��I֡��ʱ���
    unsigned long firstStamp;//��һ��I֡��ʱ���
    unsigned long dwTotalTime;//�ļ���ʱ��,����ʱ�ܻ�ȡ��
    unsigned long filesize;
    char reserve[12];
    int width;
    int height;
    int Mode; //0:�������ţ�1:I֡�ط�
    int IFrameIndex;
    int VideoFormat;
    //int AudioFormat;
    char sFileName[128];
    int framerate;
    WORD bHaveAudio;
	WORD formatTag;
    JB_STREAM_BUFFER *pStreamBuffer;
}PLAYFILE_INFO;

#define MY_FRAME_TYPE_A        0x0d
#define MY_FRAME_TYPE_I        0x0e
#define MY_FRAME_TYPE_P        0x0b

#define WAVE_FORMAT_CG729		0x7101
#define WAVE_FORMAT_MP3			0x7102
#define WAVE_FORMAT_TM722		0x0065
#define WAVE_FORMAT_CT729		0x8102
#define WAVE_FORMAT_JBG711		0x9101
#define WAVE_FORMAT_JBADPCM		0x9102

#endif //_FILE_RANDER_ASF_H
