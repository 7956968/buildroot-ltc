
#ifndef __SYS_TIME_H__
#define __SYS_TIME_H__

int QMAPI_SysTime_Init(int nTimeZone);
int QMAPI_SysTime_UnInit();
/*
	��ȡϵͳʱ��
	����ϵͳʱ��
	��ȡʱ��
	����ʱ��
	����NTP����
	ֹͣNTP����
*/
int QMapi_SysTime_ioctrl(int Handle, int nCmd, int nChannel, void* Param, int nSize);

#endif
