#ifndef _QMAPI_ERRNO_H_
#define _QMAPI_ERRNO_H_

/************************************************************************/
/* ������                                                      
   ����Ĵ������ֵռ��4���ֽڣ����λΪ1
*/
/************************************************************************/
#define		QMAPI_ERR_BASE						0xE0000000
#define 	QMAPI_SUCCESS						0x00000000					//�ɹ�
#define 	QMAPI_FAILURE						-1							//ʧ��
#define 	QMAPI_ERR_ENCRYPT_IC_NO_MATCH		(QMAPI_ERR_BASE+0xF001)		//����оƬУ��ʧ��
#define 	QMAPI_ERR_ENCRYPT_IC_NO_FIND		(QMAPI_ERR_BASE+0xF002)		//����оƬû���ҵ�
#define 	QMAPI_ERR_DEVICE_NOT_OPENED			(QMAPI_ERR_BASE+0xF003)		//�豸û�д�
#define 	QMAPI_ERR_DEVICE_NOT_STARTED		(QMAPI_ERR_BASE+0xF004)		//�豸û������
#define 	QMAPI_ERR_MEMORY_ALLOC				(QMAPI_ERR_BASE+0xF005)		//�����ڴ�ʧ��
#define 	QMAPI_ERR_INVALID_HANDLE			(QMAPI_ERR_BASE+0xF006)		//��Ч�ľ��
#define 	QMAPI_ERR_INVALID_PARAM				(QMAPI_ERR_BASE+0xF007)		//��Ч�Ĳ���
#define 	QMAPI_ERR_UNKNOW_COMMNAD			(QMAPI_ERR_BASE+0xF008)		//�޷�ʶ�������
#define 	QMAPI_ERR_TIMEOUT					(QMAPI_ERR_BASE+0xF009)		//��ʱ�˳�
#define 	QMAPI_ERR_READDATA_FAILED			(QMAPI_ERR_BASE+0xF00a)		//������ʧ��
#define 	QMAPI_ERR_DATA_TOO_BIG				(QMAPI_ERR_BASE+0xF00b)		//���ݰ�̫��
#define     QMAPI_ERR_INVALID_CHANNEL			(QMAPI_ERR_BASE+0xF00c)		//��Ч��ͨ������
#define     QMAPI_ERR_FILE_OPEN_FAILED			(QMAPI_ERR_BASE+0xF00d)		//���ļ�ʧ��
#define     QMAPI_ERR_FILE_READ_FAILED			(QMAPI_ERR_BASE+0xF00e)		//���ļ�����ʧ��
#define     QMAPI_ERR_FILE_WRITE_FAILED			(QMAPI_ERR_BASE+0xF00f)		//д�ļ�����ʧ��
#define 	QMAPI_ERR_LOGIN_USRNAME				(QMAPI_ERR_BASE+0xF010)		//��½�û�������
#define 	QMAPI_ERR_LOGIN_PSW					(QMAPI_ERR_BASE+0xF011)		//��½�������
#define 	QMAPI_ERR_NOT_SUPPORT				(QMAPI_ERR_BASE+0xF012)		//ϵͳ��֧��
#define 	QMAPI_ERR_CHANNEL_ID				(QMAPI_ERR_BASE+0xF013)		//�����ͨ����
#define		QMAPI_ERR_SYSTEM_BUSY				(QMAPI_ERR_BASE+0xF014)		//ϵͳæ
#define		QMAPI_ERR_NO_FILE					(QMAPI_ERR_BASE+0xF015)		//�޴��ļ�
#define		QMAPI_ERR_ILLEGAL_PARAM				(QMAPI_ERR_BASE+0xF016)		//���������Ϸ���Χ
#define     QMAPI_ERR_UNINIT					(QMAPI_ERR_BASE+0xF017)		//ģ��δ��ʼ��
#define		QMAPI_ERR_LOGOUT					(QMAPI_ERR_BASE+0xF018)		//��ȷ��Ҫע��ϵͳ
#define		QMAPI_ERR_LOGOFF					(QMAPI_ERR_BASE+0xF019)		//��ȷ��Ҫ�ر�ϵͳ
#define     QMAPI_ERR_RESTART					(QMAPI_ERR_BASE+0xF020)		//��ȷ��Ҫ����ϵͳ
#define     QMAPI_ERR_RESTORE					(QMAPI_ERR_BASE+0xF021)		//��ȷ��Ҫ�ָ�Ĭ�ϲ���
#define     QMAPI_ERR_UPGRADE					(QMAPI_ERR_BASE+0xF022)		//��ȷ��Ҫ�����豸
#define     QMAPI_ERR_INVALID_DATA				(QMAPI_ERR_BASE+0xF023) 
//��Ƶ���롢�ɼ�������
#define     QMAPI_ERR_INVALID_VENC_NUM			(QMAPI_ERR_BASE+0xF100)		//��Ч�ı���ͨ��
#define     QMAPI_ERR_VENC_NUM_EXCEED_SYS		(QMAPI_ERR_BASE+0xF101)		//����ϵͳ���ͨ����
#define     QMAPI_ERR_VENC_INVALID_STREAM_MODE	(QMAPI_ERR_BASE+0xF102)		//��Ч��������ģʽ
#define     QMAPI_ERR_VENC_NOT_OPENED			(QMAPI_ERR_BASE+0xF103)		//������û�д�
#define     QMAPI_ERR_VENC_VB_SETCONF			(QMAPI_ERR_BASE+0xF104)		//ý����������ʧ��
#define     QMAPI_ERR_VENC_VB_INIT				(QMAPI_ERR_BASE+0xF105)		//ý����ʼ��ʧ��
#define     QMAPI_ERR_VENC_SYS_SETCONF			(QMAPI_ERR_BASE+0xF106)		//����ͨ����������ʧ��
#define     QMAPI_ERR_VENC_SYS_INIT				(QMAPI_ERR_BASE+0xF107)		//����ͨ����ʼ��ʧ��
#define     QMAPI_ERR_VENC_CREATE_GROUP			(QMAPI_ERR_BASE+0xF108)		//��������ͨ����ʧ��
#define     QMAPI_ERR_VENC_CREATE_BINDINPUT		(QMAPI_ERR_BASE+0xF109)		//��Ƶ����ͨ����ʧ��
#define     QMAPI_ERR_VENC_VI_ENABLECHN			(QMAPI_ERR_BASE+0xF10a)		//������Ƶ����ͨ��ʧ��
#define     QMAPI_ERR_VENC_MD_DISABLED			(QMAPI_ERR_BASE+0xF10b)		//��Ƶ�ƶ����δ����
#define     QMAPI_ERR_VENC_NODATA				(QMAPI_ERR_BASE+0xF10c)		//��Ƶ��������
//��Ƶ�������������
//��Ƶ���롢�ɼ�������
#define     QMAPI_ERR_INVALID_AENC_NUM			(QMAPI_ERR_BASE+0xF200)		//��Ч����Ƶ����ͨ��
//��Ƶ���롢���������
//���ڴ�����
//IO����������


//¼�������

//��̨���ƴ���
#define     QMAPI_ERR_PTZ_COMMAND_NOT_SUPPORT	(QMAPI_ERR_BASE+0xF500)		//�������֧��
#define     QMAPI_ERR_PTZ_PROTOCOL_NOT_SUPPORT	(QMAPI_ERR_BASE+0xF501)		//��̨Э�鲻֧��
#define     QMAPI_ERR_PTZ_PARSE_FAILED			(QMAPI_ERR_BASE+0xF502)		//�ļ�����ʧ��
//�û���֤������
#define     QMAPI_ERR_USER_INVALID_USERID		(QMAPI_ERR_BASE+0xF600)		//��Ч�û�ID
#define     QMAPI_ERR_USER_NO_USER				(QMAPI_ERR_BASE+0xF601)		//û�и��û�
#define     QMAPI_ERR_USER_INVALID_PASSWORD		(QMAPI_ERR_BASE+0xF602)		//�������
#define     QMAPI_ERR_USER_NO_RIGHT				(QMAPI_ERR_BASE+0xF603)		//û�в���Ȩ��
#define     QMAPI_ERR_USER_IP_NOT_MATCH			(QMAPI_ERR_BASE+0xF604)		//�����û������ַ����
#define     QMAPI_ERR_USER_MAC_NOT_MATCH		(QMAPI_ERR_BASE+0xF605)		//�����û�����������

//���������
#define     QMAPI_ERR_SOCKET_TIMEOUT			(QMAPI_ERR_BASE+0xF700)     
#define     QMAPI_ERR_SOCKET_ERR				(QMAPI_ERR_BASE+0xF701)		//7 creat socket error.
#define     QMAPI_ERR_BIND_ERR					(QMAPI_ERR_BASE+0xF702)		//8 connect to server error.		
#define     QMAPI_ERR_CONNECT_ERR				(QMAPI_ERR_BASE+0xF703)		//9 connect to server error.
#define     QMAPI_ERR_SEND_ERR					(QMAPI_ERR_BASE+0xF704)		//10 send data error.
#define     QMAPI_ERR_RECV_ERR					(QMAPI_ERR_BASE+0xF705)		//10 recv data error.  
#define     QMAPI_ERR_SOCKET_INVALID			(QMAPI_ERR_BASE+0xF706)

//����
#define 	QMAPI_ERR_NOFIND_DISK				(QMAPI_ERR_BASE+0xF700) 	//ϵͳ�ҵ�Ӳ��
#define 	QMAPI_ERR_DISK_NOT_EXIST			(QMAPI_ERR_BASE+0xF701) 	//Ӳ�̺Ų�����
#define 	QMAPI_ERR_DISK_NO_USBDISK			(QMAPI_ERR_BASE+0xF702) 	//�޴洢�豸
#define 	QMAPI_ERR_DISK_FULL					(QMAPI_ERR_BASE+0xF703)
#define 	QMAPI_ERR_DISK_UNMOUNTED			(QMAPI_ERR_BASE+0xF704)
#define 	QMAPI_ERR_DISK_OPERATE				(QMAPI_ERR_BASE+0xF705)
#define 	QMAPI_ERR_DISK_READ_ONLY			(QMAPI_ERR_BASE+0xF706)
#define 	QMAPI_ERR_DISK_WRITE				(QMAPI_ERR_BASE+0xF707)

//¼��
#define 	QMAPI_ERR_NO_RECORD					(QMAPI_ERR_BASE+0xF800) 	//ϵͳû��¼��
#define 	QMAPI_ERR_NOT_IFRAME				(QMAPI_ERR_BASE+0xF801)		//��IFrame
#define 	QMAPI_ERR_PACKET_DATA				(QMAPI_ERR_BASE+0xF802)
//����
#define 	QMAPI_ERR_UPGRADE_WAITING			(QMAPI_ERR_BASE+0xF900)		//���ڵȴ�����
#define 	QMAPI_ERR_UPGRADING					(QMAPI_ERR_BASE+0xF901)		//��������
#define 	QMAPI_ERR_UPGRADE_FINDING_FILE		(QMAPI_ERR_BASE+0xF902)		//���ڲ��������ļ�
#define 	QMAPI_ERR_UPGRADE_SERVERTYPE		(QMAPI_ERR_BASE+0xF903)		//���������Ͳ�ƥ��
#define 	QMAPI_ERR_UPGRADE_CHANNELNUM		(QMAPI_ERR_BASE+0xF904)		//ͨ��������ƥ��
#define 	QMAPI_ERR_UPGRADE_UNSUPPORT			(QMAPI_ERR_BASE+0xF905)		//��֧�ֵ��������ݰ�����
#define 	QMAPI_ERR_UPGRADE_NO_FILE			(QMAPI_ERR_BASE+0xF906)		//û���ҵ������ļ�
#define 	QMAPI_ERR_UPGRADE_CRC_FAILED		(QMAPI_ERR_BASE+0xF907)		//CRCУ��ʧ��
#define 	QMAPI_ERR_UPGRADE_FILE_READ			(QMAPI_ERR_BASE+0xF908)		//��Ч�����ļ�
#define 	QMAPI_ERR_UPGRADE_NO_ITEM			(QMAPI_ERR_BASE+0xF909)		//û�а�����������
#define 	QMAPI_ERR_UPGRADE_NO_USBDISK		(QMAPI_ERR_BASE+0xF90a)		//û�в�������Ӳ��
#define 	QMAPI_ERR_UPGRADE_DISK_READ			(QMAPI_ERR_BASE+0xF90b)		//Ӳ�̲��ɶ�
#define 	QMAPI_ERR_UPGRADE_CPUTYPE			(QMAPI_ERR_BASE+0xF90c)		//CPU���Ͳ�ƥ�� 
#define 	QMAPI_ERR_UPGRADE_SYSTEM_BUSY		(QMAPI_ERR_BASE+0xF90d)		//ϵͳæ
#define 	QMAPI_ERR_UPGRADE_INVALID_FILE		(QMAPI_ERR_BASE+0xF90e)		//�Ƿ������ļ�
#define 	QMAPI_ERR_UPGRADE_ALLOC				(QMAPI_ERR_BASE+0xF90f)		//�����ڴ�ʧ��
#define 	QMAPI_ERR_UPGRADE_DATA				(QMAPI_ERR_BASE+0xF910)		//���ݴ���
#define 	QMAPI_ERR_UPGRADE_OPEN				(QMAPI_ERR_BASE+0xF911)		//���豸ʧ��
#define 	QMAPI_ERR_UPGRADE_WRITE				(QMAPI_ERR_BASE+0xF912)		//д���ݴ���
#define 	QMAPI_ERR_UPGRADE_NO_SUPORT			(QMAPI_ERR_BASE+0xF913)		//д���ݴ���


//����Ƶ���ݻ������
#define 	QMAPI_ERR_MBUF_NODATA				(QMAPI_ERR_BASE+0xFA00)		//������������

//DDNS
#define 	QMAPI_ERR_DDNS_CONNECT				(QMAPI_ERR_BASE+0xFB00)		// ��������ʧ��
#define 	QMAPI_ERR_DDNS_DATA					(QMAPI_ERR_BASE+0xFB01)		// ����ʧ��
#define 	QMAPI_ERR_DDNS_RS					(QMAPI_ERR_BASE+0xFB02)		// ����dns����������
#define 	QMAPI_ERR_DDNS_EXISTED				(QMAPI_ERR_BASE+0xFB03)		// �����Ѵ���(ע���������ͻ)

//�û����ù���
#define		QMAPI_ERR_USER_CFG_NO_USER			(QMAPI_ERR_BASE+0xFC00)		//�û�������

#endif //_QMAPI_ERRNO_H_


