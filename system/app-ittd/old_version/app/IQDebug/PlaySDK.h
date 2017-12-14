/*
*********************************************************************************************************
*
*                       Copyright (c) 2012 Hangzhou QianMing Technology Co.,Ltd
*
*********************************************************************************************************
*/
#ifndef __PLAY_SDK_H__
#define __PLAY_SDK_H__

#ifdef __cplusplus
extern "C" {
#endif

#define PB_OK		0
#define PB_ERR		(-1)

#define PLAY_CONTROL_START		(1 << 0) /* ���ſ�ʼ */
#define PLAY_CONTROL_PAUSE		(1 << 1) /* ������ͣ */
#define PLAY_CONTROL_STOP		(1 << 2) /* ����ֹͣ */
#define PLAY_CONTROL_SLOW		(1 << 3) /* ���ٲ��� */
#define PLAY_CONTROL_FAST		(1 << 4) /* ���ٲ��� */
#define PLAY_CONTROL_STEP		(1 << 5) /* ��֡���� */
#define PLAY_CONTROL_SOUND		(1 << 6) /* �������� */
#define PLAY_CONTROL_REVERSE	(1 << 7) /* �ؼ�֡���� */
#define PLAY_CONTROL_ONEFRAME	(1 << 8) /* ������һ֡ */
#define PLAY_CONTROL_KEYFRAME	(1 << 9) /* �����ؼ�֡ */

#define DISP_TYPE_YUV420		(1 << 0) /* YUV420ͼ�� */
#define DISP_TYPE_BMP24			(1 << 1) /* BMP24λλͼ */
#define DISP_TYPE_JPEG			(1 << 2) /* JPEGͼ�� */

typedef struct {
	int nEncProfile; /* �����㷨 */
	LONG lPicWidth; /* ��Ƶ��� */
	LONG lPicHeight; /* ��Ƶ�߶� */
} video_format_t;

typedef struct {
	int nEncProfile; /* �����㷨 */
	WORD uChannels; /* ������ */
	WORD uDataBits; /* ��������λ�� */
	DWORD dwDataBitrate; /* ������������ */
	DWORD dwSampleFreq; /* ����Ƶ�� */
} audio_format_t;

typedef struct {
	int nDispType; /* ͼ������(DISP_TYPE_YUV420��) */
	WORD uPicWidth; /* ͼ���� */
	WORD uPicHeight; /* ͼ��߶� */
	DWORD dwTimestamp; /* ͼ��ʱ��� */
	union {
		struct {
			BYTE *pY; /* Y���� */
			BYTE *pU; /* U���� */
			BYTE *pV; /* V���� */		
			WORD uYStride; /* Y������� */
			WORD uUVStride; /* UV������� */
		} yuv;
		struct {
			BYTE *pBMP; /* RGB���� */
			DWORD uBMPSize; /* RGB������� */
		} bmp;
		struct {
			BYTE *pJPEG; /* JPEG���ݻ��� */
			DWORD uJPEGSize; /* JPEG���ݴ�С */
		} jpeg;
	};
} disp_info_t;

typedef void (CALLBACK *pGetDataFunc)(void *pPlay, UINT *pLastTimestamp, void *pUser); /* ��ȡ���ݻص����� */
typedef void (CALLBACK *pCaptureDataFunc)(int nType, void *pData, int nLen, void *pUser); /* �������ݻص����� */

typedef void (CALLBACK *pDrawFunc)(void *pPlay, HDC hDC, void *pUser); /* �û����ƻص����� */
typedef void (CALLBACK *pDisplayFunc)(void *pPlay, disp_info_t *pInfo, void *pUser); /* ����ͼ��ص����� */
typedef void (CALLBACK *pPlayEndFunc)(void *pPlay, void *pUser); /* �ļ����Ž����ص����� */

int __stdcall play_init(void);
void __stdcall play_exit(void);
void* __stdcall play_open_file(HWND hWnd, const char *sFileName);
void* __stdcall play_open_stream(HWND hWnd, int bLivePlay, pGetDataFunc pFunc, void *pUser);
void* __stdcall play_create(HWND hWnd, video_format_t *pvFormat, audio_format_t *paFormat, int bLivePlay);
int __stdcall play_destroy(void *pPlay);
int __stdcall capture_audio_stream(pCaptureDataFunc pFunc, audio_format_t *paFormat, void *pUser);
int __stdcall play_get_error(void *pPlay);
int __stdcall play_config_audio(void *pPlay, audio_format_t *paFormat);
int __stdcall play_control(void *pPlay, int nControl, int nParam);
int __stdcall play_refresh(void *pPlay);
int __stdcall play_input_data(void *pPlay, DWORD dwType, DWORD dwTimestamp, const BYTE *pData, DWORD dwLen);
int __stdcall play_clear_data(void *pPlay);
int __stdcall play_draw_func(void *pPlay, pDrawFunc pFunc, void *pUser);
int __stdcall play_display_func(void *pPlay, int nType, ULONG uJpegQuality, pDisplayFunc pFunc, void *pUser);
int __stdcall play_capture_bmp(void *pPlay, const char *sFileName);
int __stdcall play_capture_bmp_buffer(void *pPlay, void *pBmpBuffer, DWORD dwBufferSize, DWORD *pSizeReturned/*[OUT]*/);
int __stdcall play_capture_jpeg(void *pPlay, ULONG uJpegQuality, const char *sFileName);
int __stdcall play_capture_jpeg_buffer(void *pPlay, ULONG uJpegQuality, void *pJpegBuffer, DWORD dwBufferSize, DWORD *pSizeReturned/*[OUT]*/);
int __stdcall play_pic_enhance(void *pPlay, DWORD dwVaule);
int __stdcall play_set_rect(void *pPlay, HWND hWnd, RECT *pRect);
int __stdcall play_get_pic_size(void *pPlay, LONG *pWidth/*[OUT]*/, LONG *pHeight/*[OUT]*/);
int __stdcall play_get_file_info(void *pPlay, LONG *pTotalFrames/*[OUT]*/, LONG *pTotalTime/*[OUT]*/);
int __stdcall play_get_position(void *pPlay, DWORD *pCurrentFrame/*[OUT]*/, DWORD *pCurrentTime/*[OUT]*/);
int __stdcall play_set_position(void *pPlay, DWORD *pCurrentFrame,/*Choose one(OR)*/DWORD *pCurrentTime);
int __stdcall play_end_msg(void *pPlay, HWND hWnd, UINT uMsg, int nUser);
int __stdcall play_end_callback(void *pPlay, pPlayEndFunc pFunc, void *pUser);
int __stdcall play_get_volume(void *pPlay, LONG *pVolume/*[OUT]*/);
int __stdcall play_set_volume(void *pPlay, LONG lVolume);
int __stdcall play_get_balance(void *pPlay, LONG *pBalance/*[OUT]*/);
int __stdcall play_set_balance(void *pPlay, LONG lBalance);
int __stdcall play_get_vision(void);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __PLAY_SDK_H__ */
