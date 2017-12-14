#ifndef __VGUARD_DID_AUTHZ_H__
#define __VGUARD_DID_AUTHZ_H__


#define ENC_CHIP_H 1 //��˼
#define ENC_CHIP_Z 2 //����΢
#define ENC_CHIP_R 3 //�µļ���ROM

#define VG_UPDATE_TIME (300 * 1000)

#define SOCK_STREAM_PORT		30001				/*ͨ�ŵĶ˿�*/
#define VG_P2P_DID_PFEFIX_MAX_LEN		8				/*DIDǰ׺���ȡֵ*/

#define VGUARDP2P_AESKEY		"VGUARDP2P_AESKEY"	/*VGUARD����ͨ�ż�����Կ*/

#define PACKED __attribute__ ((__packed__))			/*���ֽڶ���*/

#define P2P_DID_LEN				30					/*������Ϊ32n - 2, n > 0, nΪ����*/
#define P2P_AUTHZ_ONLY				1
#define P2P_AUTHZ_AND_RECYCLE		2
#define P2P_DID_SOURCE_NOT_EXIT		-1
#define P2P_DID_ANALYSYS_ERROR		-2
#define P2P_DID_SYSTEM_ERROR		-3
#define P2P_DID_PARAMETER_ERROR		-4
#define P2P_DID_NO_ONE_LEFT			-5
#define P2P_DID_WRITE_BACK_ERROR	-6
#define P2P_DID_READ_ERROR			-7
#define P2P_DID_SPACE_TOO_SMALL		-8
#define P2P_DID_OPEN_FILE_ERROR		-9


typedef struct
{
	unsigned char enc_chip_type; //��˼������΢��
	unsigned char res0;          //��������0
	unsigned char res1;          //��������0
	unsigned char res2;          //��������0
	unsigned int  seq;           //����оƬ���
} seq_t;

typedef struct
{
	unsigned char old_did[P2P_DID_LEN];            
	//��DID��ǰ׺�Ӻ�׺��'0'��β�ַ���������DID������ʱ�����ֶ���'0'��β������ַ�����
	unsigned char res0;                   
	//�����ֶΣ���Ϊ0
	unsigned char checksum0;              
	//У���ֶΣ���checksum֮��������ֽ���unsigned char������ӣ�ȡ����ֽ�
	
	seq_t    new_seq;                     
	//8�ֽ�˳���
	seq_t    old_seq;                     
	//8�ֽ�˳��ţ��ͷ���Ȩʱ����Ҫ����
	unsigned char new_did_prefix[9];      
	//��DIDǰ׺��'0'��β�ַ���
	unsigned char res1[5];                
	//�����ֶΣ���Ϊ0
	unsigned char req;                    
	//1��ʾ�����µ�DID��2��ʾ�ͷ��ϵ�DID�������µġ�
	unsigned char checksum1;              
	//У���ֶ�
}PACKED dev_pack_t;

typedef struct
{
	unsigned char new_did[P2P_DID_LEN];            
	//��DID��ǰ׺�Ӻ�׺��'0'��β�ַ�������ack������1��2ʱ�����ֶ���'0'��β������ַ�����
	unsigned char ack;                    
	//1��ʾ�µ���Ȩ��2��ʾ���վɵĲ���Ȩ�µģ�������ʾʧ�ܡ�
	unsigned char checksum0;              
	//У���ֶ�	
} PACKED server_pack_t;

#ifndef bool
#define bool int
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#define VG_AUTHZ_ERROR_NO_ERROR		0
#define VG_AUTHZ_ERROR_PARAM		-1
#define VG_AUTHZ_ERROR_OPEN_FILE	-2
#define VG_AUTHZ_ERROR_CONN_FAIL	-3
#define VG_AUTHZ_ERROR_SEND_FAIL	-4
#define VG_AUTHZ_ERROR_RECV_FAIL	-5
#define VG_AUTHZ_ERROR_ACK			-6
#define VG_AUTHZ_ERROR_CHECKSUM		-7
#define VG_AUTHZ_ERROR_FORMAT		-8
#define VG_AUTHZ_ERROR_LENGTH		-9
#define VG_AUTHZ_ERROR_HOSTNAME		-10
#define VG_AUTHZ_ERROR_UPDATE_FILE	-11
#define VG_AUTHZ_ERROR_NO_FILE		-12
#define VG_AUTHZ_ERROR_PARAM_NOT_EXIST	-13

//����������Ȩ����
//pdidPrefix ----- ��bin��ȡ��DIDǰ׺���������ֻ��
//pCrcKey ----- ��bin��ȡ��CRCKey���������ֻ��
//encrypType ----- ��bin��ȡ�ļ���оƬ���ͣ��������ֻ��
//encrypSeq ----- ��bin��ȡ�ļ���оƬ��ˮ�ţ��������ֻ��
//pAuthzAddr ----- ��bin��ȡ����Ȩ��������ַ���������ֻ��
//pAuthzHost ----- ��bin��ȡ����Ȩ�������������������ֻ��
//pDidString ----- ��Ȩ�Ժ��DID�����봫������
//didStringLen ----- ����DID��buff����
//pApiLicString ----- ��Ȩ�Ժ��APILICENSE + CRCKEY�����봫������
//apiLicStringLen ----- ����APILICENSE+CRCKEY��buff����

int vg_conn_authz_server(const char *pAuthzAddr, 
	const unsigned int encrypType, const unsigned int encrypSeq, char *crckey, char *p2pconfdid, char *p2pconfapil);

#endif

