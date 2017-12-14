#ifndef _FTP_STREAM_RECORD_H_
#define _FTP_STREAM_RECORD_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
/*
typedef int BOOL;
typedef unsigned int DWORD;
typedef unsigned short WORD;
*/
#include "QMAPIType.h"
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

typedef struct{
	int fd_ctrl;
	int fd_dat;
	FILE *ftpio;
	char msg[512];
}FtpClient;

/* ftpDebug
  �Ƿ�򿪵��Կ���
*/
void ftpDebug(BOOL blOn);

/* connectEx
  5�����ӳ�ʱ
*/
int connectEx(int fd, struct sockaddr *addr, int nLen);

/* ftpInit
   ��ʼ��FtpClient�ṹ
 */
void ftpInit(FtpClient *pFtp);
/* ftpOpen
   ����ֵ: 0:�ɹ�, -1:ʧ��
 */
int ftpOpen(FtpClient *pFtp, char *sIP, WORD nPort, char *sUser, char *sPass);
/* ftpFree()
   �ر�ftp��������
 */
void ftpFree(FtpClient *pFtp);
/* ftpClose()
   ֻ�ر�ftp��������socket,�Ա���������
 */
void ftpClose(FtpClient *pFtp);
/* ftpCheckAndMkdir
   ���Ŀ¼�Ƿ����,���������,�򴴽�Ŀ¼,���ص�'/'
   sFileName:�� /dir1/dir2/dir3/file.dat,���Զ���ftp�������Ͻ���/dir1/dir2/dir3Ŀ¼,�Ա��ϴ����ļ�
   ����ֵ:0:�ɹ�, -1:����
*/
int ftpCheckAndMkdir(FtpClient *pFtp, char *sFileName);

//------------------------------------------------------------------
/* ftpCheck()
   ���ftp�������Ƿ�֧���ļ���д������Ŀ¼
   ����ֵ: TRUE-֧��, FALSE-��֧��
 */
BOOL ftpCheck(char *sIP, WORD nPort, char *user, char *pass);
/* ftpStreamStart()
   ��ȡ���������ļ���Ϣ,������socket��ͨѶ,�ȴ�д������
   nOffset<0,���ȼ����������ļ���С,����׷�ӵ�ʱ�ļ�ĩβ
   ����ֵ: �ļ�д���(�Ѵ����ļ���С������nOffsetλ��), �����򷵻�-1
 */
int ftpStreamStart(FtpClient *pFtp, char *sSrvFile, int nOffset);
/* ftpStreamWrite()
   ��ftp������д������
   ����ֵ: ʵ��д���ֽ���
 */
int ftpStreamWrite(FtpClient *pFtp, char *Buf, int nLen);
/* ftpStreamStop()
   �ر���ftp������������
 */
void ftpStreamStop(FtpClient *pFtp);

#ifdef DEBUG
/* testUploadStream()
   ����ֵ: 0:�ɹ�, -1:����
   �ϴ�ʾ��
 */
int testUploadStream(char *ip, WORD nPort, char *user, char *pass, char *serverfile);
#endif

/* FtpPutFile
   �ļ��ϴ�
   char *localfile-�����ļ���
   char *serverfile-���������ļ���
   BOOL blNeedREST-FALE:��ͷ�ϴ�, TRUE:�ϵ�̴�
   ����ֵ:0:�ϴ��ɹ�, -1:�ϴ�ʧ��
*/

int ftpPutFile(char *ip, WORD nPort, char *user, char *pass, char *localfile, char *serverfile, BOOL blNeedREST);

#endif

