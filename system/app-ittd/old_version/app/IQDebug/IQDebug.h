
// IQDebug.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#include "IQTest.h"
#include "PlaySDK.h"
#include "liveRTSpClient.h"
#include "IQDebugDlg.h"
#include "ManageDlg.h"
#include "TestDlg.h"

#define RTSP_CLIENT_VERBOSITY_LEVEL 1 // by default, print verbose output from each "RTSPClient"
// By default, we request that the server stream its data using RTP/UDP.
// If, instead, you want to request that the server stream via RTP-over-TCP, change the following to True:
#define REQUEST_STREAMING_OVER_TCP False
#define VIDEO_DATA_SINK_DATA_BUFSZ 4 * 1024 * 1024 // 4M buffer, for 1080P YUV data.

#define WM_SOCKET (WM_USER + 1000)
#define WM_ITTCONNECT (WM_USER + 2000)
#define WM_ITTDDATA  (WM_USER + 3000)
#define WM_VIDEOPLAY  (WM_USER + 4000)

// CIQDebugApp:
// �йش����ʵ�֣������ IQDebug.cpp
//

class CIQDebugApp : public CWinApp
{
public:
	CIQDebugApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern CIQDebugApp theApp;