#ifndef _NW_COMMON_H_
#define _NW_COMMON_H_

#include <netinet/in.h>

typedef void (*NW_LogoffFunc)(int id);
typedef int (*NW_CreateSockFunc)();

typedef struct NW_ClientInfotag
{
	int 				DmsHandle;
	int 				ClientSocket;
	struct sockaddr_in	ClientAddr;
	int					id;
	NW_LogoffFunc 		OnLogoff; //�ڿͻ����˳�ʱ�����������
}NW_ClientInfo;

typedef struct NW_Server_Cfgtag
{
	NW_CreateSockFunc	CreateSocket;
	void *				InitPara;	   		//��Ҫ����InitFuncName�Ĳ���
	const char *		InitFuncName;		//��ʼ����ĺ�����
	const char *		UnInitFuncName;	
	const char *		ThreadFuncName;	//��������ĺ�����
	const char *		LibPath;			//��·��
} NW_Server_Cfg;

//�ο���������
//void NW_Server_Cfg_Init(NW_Server_Cfg *para);

#endif

