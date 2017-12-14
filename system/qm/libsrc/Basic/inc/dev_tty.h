#ifndef __DEV_TTY_H__
#define __DEV_TTY_H__

//#define __Dacheng_serial
//#endif
/************************************************************************/
/* ����ģ��                                                             */
/* serial comm function, support select()								*/
/************************************************************************/

typedef struct tagDev_Inter_Serial_Attr
{
	BYTE    byMode;    //���ڴ�ģʽ��0:232��ģʽ,1:485��д,2:485ֻд,3:485ֻ��
	DWORD	dwBaudRate;/* ������(bps)��0��50��1��75��2��110��3��150��4��300��5��600��6��1200��7��2400��8��4800��9��9600��10��19200��11��38400��12��57600��13��76800��14��115.2k */
	BYTE	byDataBit; /* �����м�λ 0��5λ��1��6λ��2��7λ��3��8λ */
	BYTE	byStopBit; /* ֹͣλ 0��1λ��1��2λ  */
	BYTE	byParity;  /* У�� 0����У�飬1����У�飬2��żУ��; */
	BYTE	byFlowcontrol; /* 0���ޣ�1��������,2-Ӳ���� */
} DEV_INTER_SERIAL_ATTR;


/* �򿪴����豸�����ش��ھ����<0ʧ�ܴ����룬�ɹ�����>=0���*/
 int DMS_DEV_TTY_Open(int deviceno);
/* �رմ����豸 */
 int DMS_DEV_TTY_Close(int fd);
/* ������ʽ�����봮������ */
 int DMS_DEV_TTY_ReadBlock(int fd, void *data, int maxlen);
/* ��������ʽ�����봮������ */
 int DMS_DEV_TTY_Read(int fd, void *data, int maxlen);
/* ������ʽ��д�봮������ */
 int DMS_DEV_TTY_Write(int fd, void *data, int len);
/* ���ô��ڲ��� */
 int DMS_DEV_TTY_SetAttr(int fd, DEV_INTER_SERIAL_ATTR *attr);
/* ��ȡ���ڲ��� */
 int DMS_DEV_TTY_GetAttr(int fd, DEV_INTER_SERIAL_ATTR *attr);


/************************�궨��****************************************/
/*�����豸��*/
#ifdef __Dacheng_serial					//���485���ӡ���ڵ���
#define  COM_PORT_0		1    //��ӡ����
#define  COM_PORT_1		0   // 485 ����
#define  COM_PORT_2		2
#define  COM_PORT_3		3
#else
#define  COM_PORT_0		0    //��ӡ����
#define  COM_PORT_1		1   // 485 ����
#define  COM_PORT_2		2
#define  COM_PORT_3		3
#endif

/*���ڴ򿪷�ʽ*/
#define COM_OPEN_MODE_232       0
#define COM_OPEN_MODE_485_RW    1
#define COM_OPEN_MODE_485_W		2
#define COM_OPEN_MODE_485_R		3


#endif //__DEV_TTY_H__
