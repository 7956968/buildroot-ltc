#include <stdio.h>


#define SEED 'g'
#define CLIENT	    1L
#define SERVER	    2L
#define MSG_HEART   3L
#define DEAMON_BUFFERSIZE 1024

#define SYSTEM_MSG_BLOCK_RUN 0//����
#define SYSTEM_MSG_NOBLOCK_RUN 1//������

typedef struct
{
	long msg_to;
	long msg_fm;
	int	 msg_no;						//����ţ�DeamonӦ���ʱ��ԭֵ����
	int  msg_flag;                      //�Ƿ��������еı��
	char buffer[DEAMON_BUFFERSIZE];		//DeamonӦ���ʱ��ԭֵ����
	int	 result;						//0:��ʾ�ɹ�������ֵ��ʾʧ��
}DMS_DEAMON_MESSAGE;
typedef struct
{
	long msg_to;
	long msg_fm;
	int	msg_no;						//����ţ�DeamonӦ���ʱ��ԭֵ����
	int msg_flag;                      //�Ƿ��������еı��
	int	 result;						//0:��ʾ�ɹ�������ֵ��ʾʧ��
}DMS_DEAMON_HEART;

int ipc_msg_get_mid();
int ipc_msg_snd(int mid, char *snd_cmd);



