#ifndef 	__LOG_H__
#define 	__LOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

typedef enum TagSYSLOGLEVEL
{
	SLOG_ERROR,
	SLOG_WARNING,
	SLOG_TRACE,	
	SLOG_DEBUG,  
}SYSLOGLEVEL_E;

/*
��������־ģ���ʼ������һ��Ӧ�ó�����ֻҪ��ʼ��һ�Ρ�
������
		server_ip:��־��������ip��ַ��ֵ����"0.0.0.0" ���� "127.0.0.1" ����Ϊ��ָ�붼��ʾ����
*/
int SystemLogInit(char *server_ip);
/*
�����������־
������
	level����־�ȼ�,ȡֵ��ΧSYSLOGLEVEL_E
	format:��־�����Ϣ����ʽͬprintf
*/
int SYSTEMLOG(int level, const char *format, ...);
/*
 ��־ģ�鷴��ʼ��
*/
int SystemLogUnInit();

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

