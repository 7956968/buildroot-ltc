#ifndef _QMAPI_NET_NETSDK_H_
#define _QMAPI_NET_NETSDK_H_
#include "QMAPICommon.h"
#include "QMAPIDataType.h"

//////////////////////////////////////////////////////////////////////////
//��1���������ýṹ��

// ��������
typedef enum __LANGUAGE_TYPE_E
{
    QMAPI_LANGUAGE_ENGLISH,                       // ��������
    QMAPI_LANGUAGE_CHINESE_SIMPLIFIED,            // Ӣ��
    QMAPI_LANGUAGE_CHINESE_TRADITIONAL,           // ��������
    QMAPI_LANGUAGE_ITALIAN,                       // �������
    QMAPI_LANGUAGE_SPANISH,                       // ��������
    QMAPI_LANGUAGE_JAPANESE,                      // ���İ�
    QMAPI_LANGUAGE_RUSSIAN,                       // ���İ�
    QMAPI_LANGUAGE_FRENCH,                        // ���İ�
    QMAPI_LANGUAGE_GERMAN,                        // ���İ�
    QMAPI_LANGUAGE_PORTUGUESE,                    // ��������
    QMAPI_LANGUAGE_TURKEY,                        // ��������
    QMAPI_LANGUAGE_POLISH,                        // ������
    QMAPI_LANGUAGE_ROMANIAN,                      // ��������
    QMAPI_LANGUAGE_HUNGARIAN,                     // ��������
    QMAPI_LANGUAGE_FINNISH,                       // ������
    QMAPI_LANGUAGE_ESTONIAN,                      // ��ɳ������
    QMAPI_LANGUAGE_KOREAN,                        // ����
    QMAPI_LANGUAGE_FARSI,                         // ��˹��
    QMAPI_LANGUAGE_DANSK,                         // ������
    QMAPI_LANGUAGE_CZECHISH,                      // �ݿ���
    QMAPI_LANGUAGE_BULGARIA,                      // ����������
    QMAPI_LANGUAGE_SLOVAKIAN,                     // ˹�工����
    QMAPI_LANGUAGE_SLOVENIA,                      // ˹����������
    QMAPI_LANGUAGE_CROATIAN,                      // ���޵�����
    QMAPI_LANGUAGE_DUTCH,                         // ������
    QMAPI_LANGUAGE_GREEK,                         // ϣ����
    QMAPI_LANGUAGE_UKRAINIAN,                     // �ڿ�����
    QMAPI_LANGUAGE_SWEDISH,                       // �����
    QMAPI_LANGUAGE_SERBIAN,                       // ����ά����
    QMAPI_LANGUAGE_VIETNAMESE,                    // Խ����
    QMAPI_LANGUAGE_LITHUANIAN,                    // ��������
    QMAPI_LANGUAGE_FILIPINO,                      // ���ɱ���
    QMAPI_LANGUAGE_ARABIC,                        // ��������
    QMAPI_LANGUAGE_CATALAN,                       // ��̩��������
    QMAPI_LANGUAGE_LATVIAN,                       // ����ά����
}QMAPI_LANGUAGE_TYPE_E;

typedef enum __QMAPI_DDNS_TYPE
{
    DDNS_3322 = 1,
    DDNS_DYNDNS,
    DDNS_NIGHTOWLDVR,
    DDNS_NOIP,
    DDNS_MYEYE,
    DDNS_PEANUTHULL,
    DDNS_ANSHIBAO,
    DDNS_BUTT,
}QMAPI_DDNS_TYPE;

typedef enum __QMAPI_PTZ_LINK_TYPE
{
    QMAPI_PTZ_LINK_GOTO_PRESET=1, //Ԥ��λ
    QMAPI_PTZ_LINK_CRUISE,        //Ѳ��
    QMAPI_PTZ_LINK_TRACK,         //�켣
}QMAPI_PTZ_LINK_TYPE;


typedef enum
{
    QMAPI_PT_PCMU = 0,
    QMAPI_PT_1016 = 1,
    QMAPI_PT_G721 = 2,
    QMAPI_PT_GSM = 3,
    QMAPI_PT_G723 = 4,
    QMAPI_PT_DVI4_8K = 5,
    QMAPI_PT_DVI4_16K = 6,
    QMAPI_PT_LPC = 7,
    QMAPI_PT_PCMA = 8,
    QMAPI_PT_G722 = 9,
    QMAPI_PT_S16BE_STEREO,
    QMAPI_PT_S16BE_MONO = 11,
    QMAPI_PT_QCELP = 12,
    QMAPI_PT_CN = 13,
    QMAPI_PT_MPEGAUDIO = 14,
    QMAPI_PT_G728 = 15,
    QMAPI_PT_DVI4_3 = 16,
    QMAPI_PT_DVI4_4 = 17,
    QMAPI_PT_G729 = 18,
    QMAPI_PT_G711A = 19,
    QMAPI_PT_G711U = 20,
    QMAPI_PT_G726 = 21,
    QMAPI_PT_G729A = 22,
    QMAPI_PT_LPCM = 23,
    QMAPI_PT_CelB = 25,
    QMAPI_PT_JPEG = 26,
    QMAPI_PT_CUSM = 27,
    QMAPI_PT_NV = 28,
    QMAPI_PT_PICW = 29,
    QMAPI_PT_CPV = 30,
    QMAPI_PT_H261 = 31,
    QMAPI_PT_MPEGVIDEO = 32,
    QMAPI_PT_MPEG2TS = 33,
    QMAPI_PT_H263 = 34,
    QMAPI_PT_SPEG = 35,
    QMAPI_PT_MPEG2VIDEO = 36,
    QMAPI_PT_AAC = 37,
    QMAPI_PT_AMR = 0x37A,
	QMAPI_PT_WMA9STD = 38,
    QMAPI_PT_HEAAC = 39,
    QMAPI_PT_PCM_VOICE = 40,
    QMAPI_PT_PCM_AUDIO = 41,
    QMAPI_PT_AACLC = 42,
    QMAPI_PT_MP3 = 43,
    QMAPI_PT_ADPCMA = 49,
    QMAPI_PT_AEC = 50,
    QMAPI_PT_X_LD = 95,
    QMAPI_PT_H264 = 96,
	QMAPI_PT_H264_HIGHPROFILE = 0x96A,
	QMAPI_PT_H264_MAINPROFILE = 0x96B,
	QMAPI_PT_H264_BASELINE = 0x96C,
    QMAPI_PT_MJPEG = 0x96D,
    QMAPI_PT_D_GSM_HR = 200,
    QMAPI_PT_D_GSM_EFR = 201,
    QMAPI_PT_D_L8 = 202,
    QMAPI_PT_D_RED = 203,
    QMAPI_PT_D_VDVI = 204,
    QMAPI_PT_D_BT656 = 220,
    QMAPI_PT_D_H263_1998 = 221,
    QMAPI_PT_D_MP1S = 222,
    QMAPI_PT_D_MP2P = 223,
    QMAPI_PT_D_BMPEG = 224,
    QMAPI_PT_MP4VIDEO = 230,
    QMAPI_PT_MP4AUDIO = 237,
    QMAPI_PT_VC1 = 238,
    QMAPI_PT_JVC_ASF = 255,
    QMAPI_PT_D_AVI = 256,
    QMAPI_PT_MAX = 257,
    QMAPI_PT_H265 = 258,

}QMAPI_PAYLOAD_TYPE_E;

typedef enum 
{ 
    QMAPI_AUDIO_SAMPLE_RATE_8000   = 8000,    /* 8K samplerate*/
    QMAPI_AUDIO_SAMPLE_RATE_11025  = 11025,   /* 11.025K samplerate*/
    QMAPI_AUDIO_SAMPLE_RATE_16000  = 16000,   /* 16K samplerate*/
    QMAPI_AUDIO_SAMPLE_RATE_22050  = 22050,   /* 22.050K samplerate*/
    QMAPI_AUDIO_SAMPLE_RATE_24000  = 24000,   /* 24K samplerate*/
    QMAPI_AUDIO_SAMPLE_RATE_32000  = 32000,   /* 32K samplerate*/
    QMAPI_AUDIO_SAMPLE_RATE_44100  = 44100,   /* 44.1K samplerate*/
    QMAPI_AUDIO_SAMPLE_RATE_48000  = 48000,   /* 48K samplerate*/
    QMAPI_AUDIO_SAMPLE_RATE_BUTT,
}QMAPI_AUDIO_SAMPLE_RATE_E; 
/*
typedef enum
{
    QMAPI_NETPT_RES1 = 1, 
    QMAPI_NETPT_SHDX = 2,//�Ϻ�����
    QMAPI_NETPT_HXHT = 3,//���Ż�ͨ
    QMAPI_NETPT_SHILIAN = 4, //ʰ��ƽ̨
    QMAPI_NETPT_RES5 = 5,//����
    QMAPI_NETPT_LANSHI = 6,//�ɶ�����
    QMAPI_NETPT_RES7 = 7, //����
    QMAPI_NETPT_DITE = 8, //����
    QMAPI_NETPT_RES9 = 9,//����
    QMAPI_NETPT_RES10 = 10,//����
    QMAPI_NETPT_SHIXUN = 11,//����˾����Ѷƽ̨
    QMAPI_NETPT_HIK = 12,//����ƽ̨
    QMAPI_NETPT_HTZN = 13,//��������
    QMAPI_NETPT_XTREAM = 14,//
    QMAPI_NETPT_JIUAN = 15, //���ݾŰ�
    QMAPI_NETPT_RES16 = 16, //����
    QMAPI_NETPT_RES17 = 17,//����
    QMAPI_NETPT_RES18 = 18,//����
    QMAPI_NETPT_RES19 = 19,//����
    QMAPI_NETPT_RES20 = 20,//����
    ///////////////////////////////
    //������ϵͳ�ڲ�ģ����߶���ģ��
    QMAPI_NETPT_ONVIF = 21, //ONVIF �����
    QMAPI_NETPT_CMS = 22,//JBNET �����
    QMAPI_NETPT_CGI = 23,//��������CGI
    QMAPI_NETPT_REC = 24,//¼��ģ��
    QMAPI_NETPT_DDNS = 25,//DDNS ģ��
    QMAPI_NETPT_LANGTAOMOBILE = 26, //�����ֻ���
    QMAPI_NETPT_TUTKP2P =27, //TUTK P2P ��
    QMAPI_NETPT_TLK = 28, //������
    QMAPI_NETPT_RTSP = 29, //RTSP ģ��
    QMAPI_NETPT_BUTT,
}QMAPI_NETPT_TYPE_E;
*/
typedef enum 
{
    QMAPI_FRAME_I, /**<I֡*/
    QMAPI_FRAME_P, /**<P֡*/
    QMAPI_FRAME_B, /**<B֡*/
    QMAPI_FRAME_A, /**<��Ƶ֡*/
    QMAPI_FRAME_BUTT /**<����ֵ*/
}QMAPI_FRAME_TYPE_E;

typedef struct tagQMAPI_RECT
{
    int left;
    int top;
    int right;
    int bottom;
}QMAPI_RECT;

typedef struct tagQMAPI_TIME
{
  DWORD    dwYear;
  DWORD    dwMonth;
  DWORD    dwDay;
  DWORD    dwHour;
  DWORD    dwMinute;
  DWORD    dwSecond;
}QMAPI_TIME, *LPQMAPI_TIME;


typedef struct tagQMAPI_SCHEDTIME
{
	BOOL bEnable;
	BYTE res[3];
    //��ʼʱ��
    BYTE byStartHour;
    BYTE byStartMin;
    //����ʱ��
    BYTE byStopHour;    
    BYTE byStopMin;
}QMAPI_SCHEDTIME;

// ��̨����
typedef struct 
{
    BYTE  byType;//���QMAPI_PTZ_LINK_TYPE��0:��Ч��1:Ԥ�õ㣬2:���Ѳ����3:���ù켣
    BYTE  byValue;
    BYTE  Reserve[2];
} QMAPI_PTZ_LINK, *LPQMAPI_PTZ_LINK;

typedef struct tagQMAPI_RANGE
{
    int         nMin;
    int         nMax;
}QMAPI_RANGE, *LQMAPI_RANGE;

typedef struct tagQMAPI_SIZE
{
    int           nWidth;
    int           nHeight;
}QMAPI_SIZE, *LQMAPI_SIZE;


typedef enum
{
	QMAPI_NETPT_MAIN = 1,
    QMAPI_NETPT_ONVIF, 
	QMAPI_NETPT_REC,
	QMAPI_NETPT_RTSP,
    QMAPI_NETPT_HIK,
    QMAPI_NETPT_DH,
    QMAPI_NETPT_XM,
    QMAPI_NETPT_ZW,
    QMAPI_NETPT_JIUAN,
    QMAPI_NETPT_ZN,
    QMAPI_NETPT_BUTT,
}QMAPI_NETPT_TYPE_E;

typedef enum tagQMAPI_VIDEO_INPUT_TYPE
{
    QMAPI_VIDEO_INPUT_NET = 1,
    QMAPI_VIDEO_INPUT_SC1135,
    QMAPI_VIDEO_INPUT_SC2135,
    QMAPI_VIDEO_INPUT_BUTT,
}QMAPI_VIDEO_INPUT_TYPE;

/* ��Ϣ����ʽ������ͬʱ���ִ���ʽ������
* 0x00000000 - ����Ӧ
* 0x00000001 - �����ϴ�����
* 0x00000002 - ����¼��
* 0x00000004 - ��̨����
* 0x00000008 - ����Email�ʼ�������email�����Ƿ�������Ƿ���Ч�������Ƿ�ͼƬ��
* 0x00000010 - ������Ѳ���ð汾��֧�֣�
* 0x00000020 - ������ʾ���������Ͼ���
* 0x00000040 - �������
* 0x00000080 - Ftpץͼ�ϴ�
* 0x00000100 - ����
* 0x00000200 - ������ʾ
* 0x00000400 - ץͼ���ر���
* 0x00000800 - ��������Խ�
* FTP,EMAIL,ץͼ���ر����������ܵ�ץͼͨ�����Ǹ��ݽṹ���ԱbySnap������
* ���bySnapû��ָ��ץͼͨ������FTP��ץͼ���ر��湦��ʧЧ��EMAILֻ�����ı���Ϣ������ͼƬ������
*/
#define QMAPI_ALARM_EXCEPTION_NORESPONSE                  0x00000000  
#define QMAPI_ALARM_EXCEPTION_UPTOCENTER                  0x00000001
#define QMAPI_ALARM_EXCEPTION_TOREC                       0x00000002
#define QMAPI_ALARM_EXCEPTION_TOPTZ                       0x00000004
#define QMAPI_ALARM_EXCEPTION_TOEMAIL                     0x00000008
#define QMAPI_ALARM_EXCEPTION_TOPOLL                      0x00000010
#define QMAPI_ALARM_EXCEPTION_TOSCREENTIP                 0x00000020
#define QMAPI_ALARM_EXCEPTION_TOALARMOUT                  0x00000040
#define QMAPI_ALARM_EXCEPTION_TOFTP                       0x00000080
#define QMAPI_ALARM_EXCEPTION_TOBEEP                      0x00000100
#define QMAPI_ALARM_EXCEPTION_TOVOICE                     0x00000200
#define QMAPI_ALARM_EXCEPTION_TOSNAP                      0x00000400
#define QMAPI_ALARM_EXCEPTION_TOTALK                      0x00000800

// ���������ṹ��
typedef struct 
{
    /* ��ǰ������֧�ֵĴ���ʽ����λ�����ʾ */
    WORD                wActionMask;
    
    /* ������������λ�����ʾ�����嶯������Ҫ�Ĳ����ڸ��Ե����������� */
    WORD                wActionFlag;
    
    /* �������������ͨ�������������������Ϊ1��ʾ��������� */
    BYTE                byRelAlarmOut[QMAPI_MAX_ALARMOUT/8];
    
    /* ����¼�� */
    BYTE                byRecordChannel[QMAPI_MAX_CHANNUM/8]; /* ����������¼��ͨ����Ϊ1��ʾ������ͨ�� */
    
    /* ץͼͨ�� */
    BYTE                bySnap[QMAPI_MAX_CHANNUM/8]; /*0��ʾ��ץ�ĸ�ͨ����1��ʾץ�ĵ�ǰͨ��*/
    /* ��Ѳͨ�� */
    BYTE                byTour[QMAPI_MAX_CHANNUM/8]; /* �ð汾�ݲ���Ч*/
    
    /* ��̨���� */
    QMAPI_PTZ_LINK        stPtzLink[QMAPI_MAX_CHANNUM];
    WORD                wDuration;              /* �����������ʱ�� */
    WORD                wRecTime;               /* ����¼�����ʱ�� */
    WORD                wSnapNum;              /* ����ץ��ͼƬ����*/
    BYTE                wDelayTime;             /* �������ʱ�䣬sΪ��λ*/
    BYTE                wBuzzerTime;            /* ���������ʱ��*/
     
} QMAPI_HANDLE_EXCEPTION;

/*¼�����*/
#define QMAPI_NET_RECORD_TYPE_SCHED   0x000001  //��ʱ¼��
#define QMAPI_NET_RECORD_TYPE_MOTION  0x000002  //�Ƶ����¼��
#define QMAPI_NET_RECORD_TYPE_ALARM   0x000004  //����¼��
#define QMAPI_NET_RECORD_TYPE_CMD     0x000008  //����¼��
#define QMAPI_NET_RECORD_TYPE_MANU    0x000010  //�ֹ�¼��

/** ¼��ƻ�*/
typedef struct
{
	unsigned char byUser; /* ʹ�� */
	unsigned char byRecordType; /* ¼������ ��λ��Ч����QMAPI_NET_RECORD_TYPE_*/
	
	unsigned char byStartHour;
	unsigned char byStartMin;

	unsigned char byEndHour;
	unsigned char byEndMin;

	unsigned char res[2]; /* Ԥ�� */

} QMAPI_RECORDSCHED;

#define     CFG_NO_DEFAULT      0
#define     CFG_SOFTRESET       1
#define     CFG_HARDRESET       2

typedef struct tagQMAPI_SYSFLAG_INFO
{
    int     nConfigDefaultFlag; //��λ���ͱ�ʶ��0����Ҫ��λ��1 ��λ��2 Ӳ����λ
    DWORD   dwConfigDefaultMask;   //��λ����������
}QMAPI_SYSFLAG_INFO;

/* DEVICE SYSTEM INFO �豸��Ϣ*/
typedef struct tagQMAPI_NET_DEVICE_INFO {
    DWORD		dwSize;
    char		csDeviceName[QMAPI_NAME_LEN];	//DVR����
    DWORD		dwDeviceID;					//DVR ID,����ң����

    BYTE		byRecordLen;				//¼���ļ����ʱ��,�Է���Ϊ��λ
    BYTE		byLanguage;					//��������,��ϸ�� QMAPI_LANGUAGE_TYPE
    BYTE		byRecycleRecord;			//�Ƿ�ѭ��¼��,0:����; 1:��
    BYTE		byOverWritePeriod;			//¼�񸲸�����/ ��СʱΪ��λ

    BYTE		byVideoStandard;			//��Ƶ��ʽ
    BYTE		byDateFormat;				/*���ڸ�ʽ(�����ո�ʽ)��
    											0��XXXX-XX-XX ������  1��XX-XX-XXXX ������ 2��XX-XX-XXXX ������ */
                                    
    BYTE		byDateSprtr;				//���ڷָ��(0��":"��1��"-"��2��"/"). 2011-01-21 david: ��Ч�ֶ�
    BYTE		byTimeFmt;					//ʱ���ʽ (0-24Сʱ��1��12Сʱ).

	BYTE		byConfigWizard;				//�Ƿ������˿�����
	BYTE		byReserve[3];

    //���²����޸�
    DWORD		dwSoftwareVersion;			//����汾�ţ���16λ�����汾����16λ�Ǵΰ汾
    DWORD		dwSoftwareBuildDate;		//����������ڣ�0xYYYYMMDD
    DWORD		dwDspSoftwareVersion;
    DWORD		dwDspSoftwareBuildDate;
    DWORD		dwPanelVersion;
    DWORD		dwPanelSoftwareBuildDate;
    DWORD		dwHardwareVersion;
    DWORD		dwHardwareBuildDate;
    DWORD		dwWebVersion;
    DWORD		dwWebBuildDate;

    BYTE		csSerialNumber[QMAPI_SERIALNO_LEN];//���к�
    DWORD		dwServerCPUType;			//��ǰCPU����(QMAPI_CPU_TYPE_E)
    DWORD		dwSysFlags;					//ϵͳ֧�ֵĹ���
    DWORD		dwServerType;				//�豸����(QMAPI_SERVER_TYPE_E)

    BYTE		byVideoInNum;				/* ���֧�ֵ�Video Channel���� */
    BYTE		byAudioInNum;				/* ���֧�ֵ�Audio Channel���� */
    BYTE		byAlarmInNum;				//DVR�����������
    BYTE		byAlarmOutNum;				//DVR�����������
    
    BYTE		byDiskNum;					//DVR Ӳ�̸���
    BYTE		byRS232Num;					//DVR 232���ڸ���
    BYTE		byRS485Num;					//DVR 485���ڸ���
    BYTE		byNetworkPortNum;			//����ڸ���

    BYTE		byDecordChans;				//DVR ����·��
    BYTE		byVGANum;					//VGA�ڵĸ���
    BYTE		byUSBNum;					//USB�ڵĸ���
    BYTE		byDiskCtrlNum;				//Ӳ�̿���������

    BYTE		byAuxOutNum;				//���ڵĸ���
    BYTE		byStreamNum;				//ÿ·��Ƶ������֧����Ƶ����
    BYTE      byVideoInputType;
    BYTE		byResvered[1];
} QMAPI_NET_DEVICE_INFO;


//�������ýṹ
typedef struct
{
    char  csIpV4[QMAPI_MAX_IP_LENGTH];    
    BYTE  byRes[QMAPI_MAX_IPV6_LENGTH];
}QMAPI_NET_IPADDR, *LPQMAPI_NET_IPADDR;

typedef struct 
{
    
    QMAPI_NET_IPADDR  strIPAddr;  
    QMAPI_NET_IPADDR  strIPMask;  //�����ַ
    DWORD dwNetInterface;       //����ӿ� 1-10MBase-T 2-10MBase-Tȫ˫�� 3-100MBase-TX 4-100Mȫ˫�� 5-10M/100M����Ӧ
    WORD  wDataPort;             //���ݶ˿�
    WORD  wMTU;                 //MTU��С
    BYTE  byMACAddr[QMAPI_MACADDR_LEN];   //Mac��ַ
    char   csNetName[QMAPI_NAME_LEN]; //�������ƣ����ڶ���������
    BYTE  byRes[2]; 
}QMAPI_NET_ETHERNET, *LPQMAPI_NET_ETHERNET;


typedef struct tagQMAPI_NET_NETWORK_CFG
{
    DWORD       dwSize;
    QMAPI_NET_ETHERNET    stEtherNet[QMAPI_MAX_ETHERNET];

    QMAPI_NET_IPADDR    stMulticastIpAddr;    
    QMAPI_NET_IPADDR    stGatewayIpAddr;
    QMAPI_NET_IPADDR    stManagerIpAddr;    //Զ�̹���������ַ(�������澯ʱ���Զ����ӵĶԽ�IP)
    QMAPI_NET_IPADDR    stDnsServer1IpAddr;
    QMAPI_NET_IPADDR    stDnsServer2IpAddr;                               

    BYTE        byEnableDHCP;         //    
    BYTE        byMaxConnect;         //�������������
    BYTE        byReserve[2];         //����
    WORD            wHttpPort;            //Http�˿�
    WORD        wReserve1;            //david 2013-03-07 Ԥ��
    WORD            wManagerPort;         //Զ�̹��������˿�
    WORD            wMulticastPort;       //�ಥ�˿�
    //BYTE        byAutoDHCPDNS;      //david ������dns��ip��ַ����byEnableDHCP
    DWORD       dwReserve2;
}QMAPI_NET_NETWORK_CFG, *PQMAPI_NET_NETWORK_CFG;

typedef struct tagQMAPI_NET_NETWORK_STATUS
{
    DWORD       dwSize;
    BOOL        bNetBroke;          //0 ����,1 �������������ж�
    BOOL        bIPConflict;        //0 ����,1 ip��ַ��ͻ
    char        byRes[32];
}QMAPI_NET_NETWORK_STATUS, *PQMAPI_NET_NETWORK_STATUS;

typedef struct tagQMAPI_NET_PLATFORM_INFO
{
    DWORD               dwSize;
    BOOL                bEnable;
    QMAPI_NET_IPADDR      strIPAddr;                  //����IP
    DWORD               dwCenterPort;               //���Ķ˿�
    char                    csServerNo[64];             //���������к�

//  int                     nPlatManufacture;                   //��������
    QMAPI_NETPT_TYPE_E     nPlatManufacture;                  //��������
    int                 nNetMode;                   //����ģʽ0: ����Ӧ1: ����ģʽ 2: ����ģʽ
    int                 bEnableUpnp;                //�Ƿ�����upnp������ģʽ��Ч
    int                 nMsgdPort;                  //��������˿ڣ�����ģʽ��Ч
    int                 nVideoPort;                 //����Ƶ�����˿ڣ�����ģʽ��Ч
    int                 nTalkPort;                  //�Խ������˿ڣ�����ģʽ��Ч
    int                 nVodPort;                   // ����Ƶ�㲥�˿ڣ�����ģʽ��Ч
    BYTE                byMsgdPortOK;           //MsgPort UPNP is ok
    BYTE                byVideoPortOK;          //VideoPort UPNP is ok
    BYTE                byTalkPortOK;               //TalkPort UPNP is ok
    BYTE                byVodPortOK;                //VodPort UPNP is ok
    char                pData[252];                 //Ԥ������
}QMAPI_NET_PLATFORM_INFO;

typedef struct tagQMAPI_NET_PLATFORM_INFO_V2
{
    DWORD               dwSize;
    BOOL                bEnable;
    QMAPI_NET_IPADDR      strIPAddr;                  //���ĵ�ַ
    DWORD               dwCenterPort;               //���Ķ˿�
    char                    csServerNo[64];             //���������к�
    QMAPI_NETPT_TYPE_E        enPlatManufacture;              //��������
    char                pPrivateData[280];          //Ԥ������, ���ݳ������;�������˽����Ϣ
}QMAPI_NET_PLATFORM_INFO_V2;

typedef struct
{
    DWORD dwSize;
    BOOL  bPPPoEEnable;              //0-������,1-����
    char  csPPPoEUser[QMAPI_NAME_LEN]; //PPPoE�û���
    char  csPPPoEPassword[QMAPI_PASSWD_LEN]; //PPPoE����
    QMAPI_NET_IPADDR  stPPPoEIP; //PPPoE IP��ַ(ֻ��)
    DWORD dwSecurityProtocol; /**< ����Э�� ֵ��Χ�ο�:HI_CFG_PPPOE_SECURITY_PROTOCOL_E*/
}QMAPI_NET_PPPOECFG, *LPQMAPI_NET_PPPOECFG;


typedef struct tagQMAPI_NET_DDNSCFG
{
    DWORD   dwSize;
    BOOL    bEnableDDNS;                //�Ƿ�����DDNS
    struct {
        QMAPI_DDNS_TYPE    enDDNSType;                  //DDNS����������, �����������ͣ�QMAPI_DDNS_TYPE
        char    csDDNSUsername[QMAPI_NAME_LEN];
        char    csDDNSPassword[QMAPI_PASSWD_LEN];
        char    csDDNSDomain[QMAPI_MAX_DOMAIN_NAME];          //��DDNS������ע���������ַ
        char    csDDNSAddress[QMAPI_MAX_DOMAIN_NAME];         //DNS��������ַ��������IP��ַ������
        int nDDNSPort;                  //DNS�������˿ڣ�Ĭ��Ϊ6500
        int nUpdateTime;              /*����ʱ��*/
        int     nStatus;                        /*״̬,0:�ɹ�,����ֵ��������*/
        
        BYTE byReserve[32];               /**< ������,�����۽��Ԥ��32�ֽ� */
    }stDDNS[QMAPI_MAX_DDNS_NUMS];
}QMAPI_NET_DDNSCFG, *PQMAPI_NET_DDNSCFG;

typedef struct QMAPI_NET_EMAIL_ADDR
{
    char  csName[QMAPI_NAME_LEN];/**< �ʼ���ַ��Ӧ���û��� */
    char  csAddress[QMAPI_MAX_DOMAIN_NAME];   /**< �ʼ���ַ ��: hw@huawei.com */
    BYTE byReserve[32];               /**< ������,�����۽��Ԥ��32�ֽ� */
} QMAPI_NET_EMAIL_ADDR;

typedef struct tagQMAPI_NET_EMAIL_PARAM
{
    DWORD	dwSize;

    BOOL	bEnableEmail;                   //�Ƿ�����

    BYTE	byAttachPicture;                //�Ƿ������
    BYTE	bySmtpServerVerify;             //���ͷ�����Ҫ�������֤
    BYTE	byMailInterval;                 //����2s��(1-2�룻2-3�룻3-4�룻4-5��)
    BYTE	byReserved;

    WORD	wServicePort;					/**< �������˿�,һ��Ϊ25���û����ݾ������������ */
    WORD	wEncryptionType;				/**< �������� ssl*/

    char	csEMailUser[QMAPI_NAME_LEN];      //�˺�
    char	csEmailPass[QMAPI_PASSWD_LEN];    //����

    char    csSmtpServer[QMAPI_MAX_DOMAIN_NAME]; //smtp������ //���ڷ����ʼ�
    char    csPop3Server[QMAPI_MAX_DOMAIN_NAME]; //pop3������ //���ڽ����ʼ�,��IMAP��������

    QMAPI_NET_EMAIL_ADDR stToAddrList[QMAPI_EMAIL_ADDR_MAXNUM]; /**< �ռ��˵�ַ�б�  */
    QMAPI_NET_EMAIL_ADDR stCcAddrList[QMAPI_EMAIL_ADDR_MAXNUM]; /**< ���͵�ַ�б� */
    QMAPI_NET_EMAIL_ADDR stBccAddrList[QMAPI_EMAIL_ADDR_MAXNUM];/**< ���͵�ַ�б� */
    QMAPI_NET_EMAIL_ADDR stSendAddrList;                          /**< �����˵�ַ */

	BYTE    byEmailType[1];					//����Ϊ�����ʼ����� 8 - Motion 4 - Video Loss  2 - IOAlarm  1- Other
    char    csReserved[31];

}QMAPI_NET_EMAIL_PARAM, *PQMAPI_NET_EMAIL_PARAM;

/* ftp�ϴ�����*/

typedef struct tagQMAPI_NET_FTP_PARAM
{
    DWORD   dwSize;
    BOOL    bEnableFTP;         /*�Ƿ�����ftp�ϴ�����*/
    char        csFTPIpAddress[QMAPI_MAX_DOMAIN_NAME];        /*ftp ��������������IP��ַ������*/
    DWORD   dwFTPPort;              /*ftp�˿�*/
    char        csUserName[QMAPI_NAME_LEN];           /*�û���*/
    char        csPassword[QMAPI_PASSWD_LEN];         /*����*/
    WORD    wTopDirMode;            /*0x0 = ʹ���豸ip��ַ,0x1 = ʹ���豸��,0x2 = OFF*/
    WORD    wSubDirMode;            /*0x0 = ʹ��ͨ���� ,0x1 = ʹ��ͨ����,0x2 = OFF*/
    BYTE    reservedData[28]; //����

}QMAPI_NET_FTP_PARAM, *LPQMAPI_NET_FTP_PARAM;

/* ��ʱץͼ */
typedef struct tagQMAPI_NET_SNAP_TIMER
{
    DWORD       dwSize;
    BOOL                bEnable;
    QMAPI_SCHEDTIME stScheduleTime[7][4];/**��ͨ����videoloss�Ĳ���ʱ��*/
    DWORD          dwInterval;      //��λ������
    int                 nPictureQuality;//��������(0-4),0Ϊ���
    int                 nImageSize;     // �����С��0��QCIF��1��CIF��2��D1
    BYTE        byFtpUpload;
    BYTE        byLocalSave;
    BYTE        byRes[6];
}QMAPI_NET_SNAP_TIMER, *LPQMAPI_NET_SNAP_TIMER;

/*¼���ļ�FTP�ϴ�*/
typedef struct tagQMAPI_NET_RECORD_UPLOAD
{
    DWORD           dwSize;
    BOOL            bEanble;
    QMAPI_RECORDSCHED stScheduleTime; //�ϴ�ʱ��Σ�����һ��������
}QMAPI_NET_RECORD_UPLOAD, *LPQMAPI_NET_RECORD_UPLOAD;

/*      WIFI   */
typedef struct tagQMAPI_NET_WIFI_SITE
{
    DWORD           dwSize;
    int             nType;
    char                csEssid[QMAPI_NAME_LEN];
    int             nRSSI;    //wifi �ź�ǿ��
    BYTE            byMac[QMAPI_MACADDR_LEN];
    BYTE                byRes1[2];
    BYTE                bySecurity;  
                            //0: none  (wifi enable)
                            // 1:web 64 assii (wifi enable)
                            // 2:web 64 hex (wifi enable)
                            // 3:web 128 assii (wifi enable)
                            // 4:web 128 hex (wifi enable)
                            //5:  WPAPSK-TKIP 
                                        //6: WPAPSK-AES
                                        //7: WPA2PSK-TKIP
                                        //8: WPA2PSK-AES 
                                        //9:
                                        //10:WPS
    BYTE                byRes2[3];
    int             nChannel;                           
}QMAPI_NET_WIFI_SITE;

typedef struct tagQMAPI_NET_WIFI_SITE_LIST
{
    DWORD           dwSize; //== sizeof(QMAPI_NET_WIFI_SITE)*nCount
    int             nCount;
    QMAPI_NET_WIFI_SITE    stWifiSite[100];// ʵ�ʴ���
}QMAPI_NET_WIFI_SITE_LIST;

//wifi ״̬����ȫ������չ
typedef enum tagWIRELESS_STATUS{
    WL_OK = 0,
    WL_NOT_CONNECT,     //û��������
    WL_DEVICE_NOT_EXIST,    //ipc��wifiӲ��������
    WL_ESSID_NOT_EXIST, //essid������
    WL_DHCP_ERROR,          //dhcp��ȡ����ip
    WL_ENCRYPT_FAIL,        //������֤����
    WL_IP_CONFLICT,         //IP��ַ��ͻ
}WIRELESS_STATUS_E;

typedef struct tagQMAPI_NET_WIFI_CONFIG
{
    DWORD           dwSize;
    BYTE            bWifiEnable;
    BYTE			byWifiMode;		//0:station, 1:ap
    BYTE			byWpsStatus;	//wps״̬(0:�ر�,1:����)
    BYTE            byWifiSetFlag; //0:�ֶ����ù���ɹ���½�� 1:У�� 2:�Զ�����wifi 
    QMAPI_NET_IPADDR  dwNetIpAddr;
    QMAPI_NET_IPADDR  dwNetMask;
    QMAPI_NET_IPADDR  dwGateway;
    QMAPI_NET_IPADDR  dwDNSServer;
    BYTE            byMacAddr[6];
    char            csEssid[32];
    BYTE            byRes1[32];
    BYTE            nSecurity;
						// 0: none  (wifi enable)
						// 1: wep 64 assii (wifi enable)
						// 2: wep 64 hex (wifi enable)
						// 3: wep 128 assii (wifi enable)
						// 4: wep 128 hex (wifi enable)
						// 5: WPAPSK-TKIP 
						// 6: WPAPSK-AES
						// 7: WPA2PSK-TKIP
						// 8: WPA2PSK-AES 
						// 9: AUTOMATCH
    BYTE        	byNetworkType;  // 1. Infra 2. ad-hoc
    BYTE            byEnableDHCP;
    BYTE            byStatus; //    0:  �ɹ�,����ֵ�Ǵ�����
    char            csWebKey[32];
    BYTE            byRes2[64];
}QMAPI_NET_WIFI_CONFIG, *LPQMAPI_NET_WIFI_CONFIG;


#define WIRELESS_TDSCDMA_ZX      0x02
#define WIRELESS_EVDO_HUAWEI    0x03
#define WIRELESS_WCDMA_HUAWEI 0x04

typedef struct tagQMAPI_NET_WANWIRELESS_CONFIG
{
    DWORD       dwSize;
    BOOL        bEnable;
    BYTE        byDevType; //WIRELESS_XXX 0x2---0x4
    BYTE        byStatus;
    BYTE        byReserve[2];
    DWORD       dwNetIpAddr;            //IP  (wifi enable)

}QMAPI_NET_WANWIRELESS_CONFIG, *LPQMAPI_NET_WANWIRELESS_CONFIG;

/**UPNP**/
typedef struct tagQMAPI_UPNP_CONFIG
{
    DWORD       dwSize;
    BOOL        bEnable;                /*�Ƿ�����upnp*/
    DWORD       dwMode;                 /*upnp������ʽ.0Ϊ�Զ��˿�ӳ�䣬1Ϊָ���˿�ӳ��*/
    DWORD       dwLineMode;             /*upnp����������ʽ.0Ϊ��������,1Ϊ��������*/
    char            csServerIp[32];         /*upnpӳ������.������·����IP*/
    DWORD       dwDataPort;             /*upnpӳ�����ݶ˿�*/
    DWORD       dwWebPort;              /*upnpӳ������˿�*/
    DWORD       dwMobilePort;           /*upnpӳ���ֻ��˿�*/

    WORD        dwDataPort1;            /*upnp��ӳ��ɹ������ݶ˿�*/
    WORD        dwWebPort1;             /*upnp��ӳ��ɹ�������˿�*/
    WORD        dwMobilePort1;          /*upnpӳ��ɹ����ֻ��˿�*/
    WORD            wDataPortOK;
    WORD            wWebPortOK;
    WORD            wMobilePortOK;
}QMAPI_UPNP_CONFIG, *LPQMAPI_UPNP_CONFIG;

/*--------------------------ͨ�����ýṹ--------------------------------*/
//ͨ��OSD��ʾ�Լ�ͨ����������

typedef struct tagQMAPI_NET_OSD_S
{
    BOOL        bOsdEnable;         /**< OSDʹ��*/
    DWORD   dwOsdContentType;    /**< OSD��������HI_CFG_OSD_TYPE_E */
    DWORD   dwLayer;             /**< �����Σ��ڶ���������ʱ����,0 ~100*/
    DWORD   dwAreaAlpha;         /**< OSD����Alphaֵ*/
    DWORD   dwFgColor;           /**< OSD��ɫ, ���ظ�ʽRGB8888 */
    DWORD   dwBgColor;           /**< OSD������ɫ, ���ظ�ʽRGB8888 */
    int     nLeftX;       /**< �������Ͻ�����ڴ������Ͻ�X�������:0~255*/
    int     nLeftY;       /**< �������Ͻ�����ڴ������Ͻ�Y�������:0~255*/
    int     nWidth;       /**< �����Ϊ����ֵ,ͼƬʱ��Ч*/
    int     nHeight;       /**< ����ߣ�Ϊ����ֵ,ͼƬʱ��Ч*/
    char        csOsdCotent[QMAPI_MAX_OSD_LEN];/**< OSDΪ�ַ�ʱ��֧������string��
                                                 OSDΪͼƬʱ��֧��path: "/bin/osd.bmp";
                                                 �����ͼƬ�ڴ棬ǰ4λΪ�ڴ��ַ*/
}QMAPI_NET_OSD_S;

typedef struct tagQMAPI_NET_CHANNEL_OSDINFO
{
    DWORD   dwSize;
    DWORD   dwChannel;
    BOOL    bShowTime;
    BOOL    bDispWeek; /*�Ƿ���ʾ����*/
    DWORD   dwTimeTopLeftX; /*OSD���Ͻǵ�x����*/
    DWORD   dwTimeTopLeftY;/*OSD���Ͻǵ�y����*/
    BYTE    byReserve1;// 2011-01-21 david: ��Ч�ֶΣ�ֱ�Ӳ���tagQMAPI_NET_DEVICE_INFO �ṹ��
                 /*OSD����(�����ո�ʽ)��
                */
    BYTE       byOSDAttrib; 
                /*
                OSD���ԣ�͸��/��˸����
                1��͸������˸
                2��͸��������˸
                3����˸����͸��
                4����͸��������˸
                */
    BYTE    byReserve2;  // 2011-01-21 david: ��Ч�ֶΣ�ֱ�Ӳ���tagQMAPI_NET_DEVICE_INFO �ṹ��
                
    BYTE    byShowChanName ;    //Ԥ����ͼ�����Ƿ���ʾͨ�����ƣ�0-����ʾ��1-��ʾ�������С704*576��
    DWORD   dwShowNameTopLeftX ;    //ͨ��������ʾλ�õ�x����
    DWORD   dwShowNameTopLeftY ;    //ͨ��������ʾλ�õ�y����
    char    csChannelName[QMAPI_NAME_LEN];    //ͨ������
    QMAPI_NET_OSD_S stOsd[QMAPI_MAX_OSD_NUM];/**Դͨ������OSD 2011-01-21 david: �ֶ�Ԥ��*/
}QMAPI_NET_CHANNEL_OSDINFO, *LPQMAPI_NET_CHANNEL_OSDINFO;

//��Ƶ�������
typedef struct tagQMAPI_NET_AUDIO_FORMAT_INFO
{
    WORD    wFormatTag;        /* format type */
    WORD    wChannels;         /* number of channels (i.e. mono, stereo...) */
    DWORD   dwSamplesPerSec;    /* sample rate */
    DWORD   dwAvgBytesPerSec;   /* for buffer estimation */
    WORD    wBlockAlign;       /* block size of data */
    WORD    wBitsPerSample;    /* Number of bits per sample of mono data */
}QMAPI_NET_AUDIO_FORMAT_INFO, *LPQMAPI_NET_AUDIO_FORMAT_INFO;

//��Ƶͨ��ѹ������
typedef struct tagQMAPI_NET_COMPRESSION_INFO
{
    DWORD   dwCompressionType;      //
    DWORD   dwFrameRate;            //֡�� (1-25/30) PALΪ25��NTSCΪ30
    DWORD   dwStreamFormat;         //��Ƶ�ֱ��� (0ΪCIF,1ΪD1,2ΪHALF-D1,3ΪQCIF) QMAPI_VIDEO_FORMAT_CIF
    WORD    wHeight;            //
    WORD    wWidth;             //
    DWORD   dwRateType;         //��ģʽ(0Ϊ��������1Ϊ������)
    DWORD   dwBitRate;          //���� (16000-4096000)
    DWORD   dwImageQuality;     //��������(0-4),0Ϊ���
    DWORD   dwMaxKeyInterval;   //�ؼ�֡���(1-100)
    
    WORD    wEncodeAudio;       //�Ƿ������Ƶ
    WORD    wEncodeVideo;       //�Ƿ������Ƶ

    WORD    wFormatTag;        /* format type */
    WORD    wBitsPerSample;    /* Number of bits per sample of mono data */

    BYTE    byReseved[16];
}QMAPI_NET_COMPRESSION_INFO, *LPQMAPI_NET_COMPRESSION_INFO;

typedef struct tagQMAPI_NET_CHANNEL_PIC_INFO
{
    DWORD   dwSize;
    DWORD   dwChannel;
    BYTE	csChannelName[QMAPI_NAME_LEN];    //ͨ������

    QMAPI_NET_COMPRESSION_INFO   stRecordPara; /* ¼�� */
    QMAPI_NET_COMPRESSION_INFO   stNetPara;    /* ���� */
    QMAPI_NET_COMPRESSION_INFO   stPhonePara;  /* �ֻ��࿴ */
    QMAPI_NET_COMPRESSION_INFO   stEventRecordPara; /*�¼�����¼��ѹ������*/
}QMAPI_NET_CHANNEL_PIC_INFO, *LPQMAPI_NET_CHANNEL_PIC_INFO;


//�ڵ���������
typedef struct tagQMAPI_NET_SHELTER_RECT
{
    DWORD   nType;          /* �ڵ�ʹ�� 0-����, 1-�����ڵ�, 2-Ԥ���ڵ�, 3-ȫ���ڵ� */
    WORD    wLeft;          /* �ڵ��������Ͻǵ�x���� */
    WORD    wTop;           /* �ڵ��������Ͻǵ�y���� */
    WORD    wWidth;         /* �ڵ������� */
    WORD    wHeight;        /* �ڵ�����߶� */
    DWORD   dwColor;        /* �ڵ���ɫ, Ĭ�� 0:��ɫ ��RGB��ʽ*/
}QMAPI_NET_SHELTER_RECT;

typedef struct tagQMAPI_NET_CHANNEL_SHELTER
{
    DWORD   dwSize;
    DWORD   dwChannel;
    BOOL    bEnable;        //�Ƿ���������ڵ�
    QMAPI_NET_SHELTER_RECT    strcShelter[QMAPI_MAX_VIDEO_HIDE_RECT];   //�ڵ��������֧��5��������ڵ���RECT��D1Ϊ׼
}QMAPI_NET_CHANNEL_SHELTER,*PQMAPI_NET_CHANNEL_SHELTER;

typedef struct tagQMAPI_NET_MOTION_DETECT
{
    DWORD           dwSize;
    DWORD           dwChannel;
    BOOL            bEnable;                //�Ƿ���в���
    DWORD           dwSensitive;            //������ ȡֵ0 - 5, ԽСԽ����*/
    BOOL                bManualDefence;     //(david 20130203 ����) �ֶ�������־��==YES(1)������==NO(0)����ʱ�ж�
    BYTE            byMotionArea[QMAPI_MD_STRIDE_SIZE];   //�����������.����������44*36����,��������BIT Ϊ��λ���ڴ��ȡ�
    QMAPI_HANDLE_EXCEPTION   stHandle;    
    QMAPI_SCHEDTIME stScheduleTime[8][4];/**��ͨ����videoloss�Ĳ���ʱ��*/
}QMAPI_NET_CHANNEL_MOTION_DETECT, *LPQMAPI_NET_CHANNEL_MOTION_DETECT;

//�źŶ�ʧ����
typedef struct{
    DWORD    dwSize;
    DWORD   dwChannel;
    BOOL     bEnable; /* �Ƿ����źŶ�ʧ���� */
    QMAPI_HANDLE_EXCEPTION   stHandle; /* ����ʽ */
    QMAPI_SCHEDTIME stScheduleTime[7][4];/**��ͨ����videoloss�Ĳ���ʱ��*/
}QMAPI_NET_CHANNEL_VILOST,*LPQMAPI_NET_CHANNEL_VILOST;

//�ڵ����������С704*576
typedef struct
{
    DWORD dwSize;
    DWORD   dwChannel;
    BOOL bEnable; /* �Ƿ������ڵ����� ,0-��,1-�������� 2-�������� 3-��������*/
    WORD wHideAlarmAreaTopLeftX; /* �ڵ������x���� */
    WORD wHideAlarmAreaTopLeftY; /* �ڵ������y���� */
    WORD wHideAlarmAreaWidth; /* �ڵ�����Ŀ� */
    WORD wHideAlarmAreaHeight; /*�ڵ�����ĸ�*/
    QMAPI_HANDLE_EXCEPTION stHandle; /* ����ʽ */
    QMAPI_SCHEDTIME stScheduleTime[7][4];/**��ͨ����videoloss�Ĳ���ʱ��*/
}QMAPI_NET_CHANNEL_HIDEALARM,*LPQMAPI_NET_CHANNEL_HIDEALARM;

typedef struct tagQMAPI_NET_TRHD_DETECT
{
	BYTE			byTUplimit;					//�¶ȱ�������
	BYTE			byTDownlimit;				//�¶ȱ�������
	BYTE			byHUplimit;					//ʪ�ȱ�������
	BYTE			byHDownlimit;				//ʪ�ȱ�������
	QMAPI_SCHEDTIME	stTRScheduleTime[7][4];		//�¶ȱ�������ʱ��
	QMAPI_SCHEDTIME	stHDScheduleTime[7][4];		//ʪ�ȱ�������ʱ��
}QMAPI_NET_CHANNEL_TRHD_DETECT, *LPQMAPI_NET_CHANNEL_TRHD_DETECT;


#define MAX_REC_SCHED 8

typedef struct 
{
    DWORD			dwSize;    			/* �˽ṹ�Ĵ�С */
    DWORD			dwChannel;
    DWORD			dwRecord;  			/*�Ƿ�¼�� 0-�� 1-��*/
    QMAPI_RECORDSCHED stRecordSched[7][MAX_REC_SCHED];		/*¼��ʱ��Σ�����һ��������*/
    DWORD			dwPreRecordTime;	/*Ԥ¼ʱ�䣬��λ��s��0��ʾ��Ԥ¼*/
    DWORD			dwRecorderDuration; /*¼�񱣴���ʱ��*/
    BYTE			byRedundancyRec;	/*�Ƿ�����¼��,��Ҫ����˫���ݣ�0/1, Ĭ��Ϊ������*/
    BYTE			byAudioRec;			/*¼��ʱ����������ʱ�Ƿ��¼��Ƶ���ݣ������д˷���,Ŀǰ�汾��֧��*/
    BYTE			byRecordMode;		//0:�Զ�ģʽ������ʱ¼�����ã� 1:�ֶ�¼��ģʽ��ȫ���¼�񣩣�2:��ֹ���з�ʽ����¼��
    BYTE  			byStreamType;		// ¼���������� 0:������ 1:������
	BYTE  			byReserve[8];
}QMAPI_NET_CHANNEL_RECORD, *LPQMAPI_NET_CHANNEL_RECORD;

typedef struct tagQMAPI_NET_RECORD_STREAMMODE
{
    DWORD         dwSize;
    DWORD         dwStreamType;//0:first stream,1:second stream,2,third stream
    unsigned char byRes[16];
}QMAPI_NET_RECORD_STREAMMODE;

#define QMAPI_ENC_ENCRYPT_KEY_LEN 128
#define QMAPI_ENC_WATERMARK_CONTENT_LEN 16
#define QMAPI_ENC_WATERMARK_KEY_LEN  16
#define QMAPI_ENC_MAX_OSD_NUM 4

typedef struct 
{
    DWORD u32EncryptEnable;                 /**< ��������ʹ��: 0 �ر�; 1 ���� */
    char    as8Key[QMAPI_ENC_ENCRYPT_KEY_LEN];   /**< ����������Կ*/
}QMAPI_NET_CHANNEL_ENCRYPT;


typedef struct
{
    int     s32WmEnable;                                /**< ˮӡ������־: 0 �ر�; 1 ����*/
    char    as8WaterMark[QMAPI_ENC_WATERMARK_CONTENT_LEN]; /**< ˮӡ���� */
    char    as8Key[QMAPI_ENC_WATERMARK_KEY_LEN];           /**< ˮӡ��Կ */
}QMAPI_NET_CHANNEL_WATERMARK;


/*��������*/
typedef struct
{
    DWORD   dwSize;                 /* �˽ṹ�Ĵ�С */
    DWORD   dwChannel;
    char    csAlarmInName[QMAPI_NAME_LEN];    /* ���� */
    BYTE    byAlarmType;                /* ���������ͣ�Ŀǰ�汾������,0������,1������ */
    BYTE    byAlarmInHandle;            /* �Ƿ��� 0��������,1������*/
    char    reserve[2];
    QMAPI_HANDLE_EXCEPTION stHandle; /* ����ʽ */
    QMAPI_SCHEDTIME stScheduleTime[7][4];/**��ͨ����videoloss�Ĳ���ʱ��*/
}QMAPI_NET_ALARMINCFG, *LPQMAPI_NET_ALARMINCFG;

/*�������*/
typedef struct
{
    DWORD   dwSize; /* �˽ṹ�Ĵ�С */
    DWORD   dwChannel;
    BYTE    csAlarmOutName[QMAPI_NAME_LEN]; /* ���� */
    QMAPI_SCHEDTIME stScheduleTime[7][4];/**��ͨ����videoloss�Ĳ���ʱ��*/
}QMAPI_NET_ALARMOUTCFG, *LPQMAPI_NET_ALARMOUTCFG;


typedef struct tagQMAPI_NET_ALARM_SERVER
{
    QMAPI_ALARM_TYPE_E eAlarmType;
    char    *pAlarmEntity;
    struct tagDMS_SYSNETAPI *pNext;
    char    reserve[8];
}QMAPI_NET_ALARM_SERVER, *LPQMAPI_NET_ALARM_SERVER;


/*��̨������485���ڲ���*/
typedef struct
{
    DWORD dwSize; /* �˽ṹ�Ĵ�С */
    DWORD   dwChannel;
    DWORD dwBaudRate; /* ������(bps)��0��50��1��75��2��110��3��150��4��300��5��600��6��1200��7��2400��8��4800��9��9600��10��19200��11��38400��12��57600��13��76800��14��115.2k */
    BYTE byDataBit; /* �����м�λ 0��5λ��1��6λ��2��7λ��3��8λ */
    BYTE byStopBit; /* ֹͣλ 0��1λ��1��2λ  */
    BYTE byParity; /* У�� 0����У�飬1����У�飬2��żУ��; */
    BYTE byFlowcontrol; /* 0���ޣ�1��������,2-Ӳ���� */
    char  csDecoderType[QMAPI_NAME_LEN]; /* ����������, ���±�*/
    WORD wDecoderAddress; /*��������ַ:0 - 255*/
    BYTE byHSpeed;      //��̨H�ٶ�
    BYTE byVSpeed;      //��̨V�ٶ�
    DWORD dwRes;
}QMAPI_NET_DECODERCFG,*LPQMAPI_NET_DECODERCFG;

//��̨Э���ṹ����
typedef struct
{ 
    DWORD dwType;               /*����������ֵ����1��ʼ��������*/
    char  csDescribe[QMAPI_NAME_LEN]; /*��������������*/
}QMAPI_PTZ_PROTOCOL;

typedef struct
{
    DWORD   dwSize;    
    QMAPI_PTZ_PROTOCOL stPtz[QMAPI_PTZ_PROTOCOL_NUM];/*���200��PTZЭ��*/
    DWORD   dwPtzNum;           /*��Ч��ptzЭ����Ŀ*/
    BYTE    byRes[8];           // ��������
}QMAPI_NET_PTZ_PROTOCOLCFG, *LQMAPI_NET_PTZ_PROTOCOLCFG;

//���λ����Ϣ
typedef struct
{
    DWORD   dwSize;
    int     nAction;        //
    float   nPanPos;        //ˮƽ����
    float   nTiltPos;       //��ֱ����
    float   nZoomPos;       //�䱶����
    BYTE    byRes[8];       // ��������	
}QMAPI_NET_PTZ_POS;

/*�ϴ���̨Э��*/
typedef struct 
{
    DWORD dwSize;                   /* ����pData������ʵ�ʳ���*/
    BYTE  byDescribe[QMAPI_NAME_LEN]; /*��������������*/
    BYTE  pData[1];                
}QMAPI_NET_PTZ_PROTOCOL_DATA;

/*232���ڲ���*/
typedef struct
{
    DWORD dwSize; /* �˽ṹ�Ĵ�С */
    DWORD dwBaudRate; /* ������(bps) */
    BYTE byDataBit; /* �����м�λ 0��5λ��1��6λ��2��7λ��3��8λ; */
    BYTE byStopBit; /* ֹͣλ 0��1λ��1��2λ; */
    BYTE byParity; /* У�� 0����У�飬1����У�飬2��żУ��; */
    BYTE byFlowcontrol; /* 0���ޣ�1��������,2-Ӳ���� */
    DWORD dwWorkMode; /* ����ģʽ��0��խ�����䣨232��������PPP���ţ���1������̨��232�������ڲ������ƣ���2��͸��ͨ�� */
}QMAPI_NET_RS232CFG, *LPQMAPI_NET_RS232CFG;

/************************************************************************/
/* �û�Ȩ�޹�����֤                                                   */
/************************************************************************/
#define RIGHT_LOCAL_PTZ             0x00000001  //���ؿ�����̨
#define RIGHT_LOCAL_MANUAL_RECORD   0x00000002  //�����ֶ�¼��
#define RIGHT_LOCAL_PLAYBACK        0x00000004  //���ػط�
#define RIGHT_LOCAL_PARAMSET        0x00000008  //�������ò���
#define RIGHT_LOCAL_QUERYLOG        0x00000010  //���ز鿴״̬����־
#define RIGHT_LOCAL_ADVANCED        0x00000020  //���ظ߼�����:��������ʽ�����ָ�����
#define RIGHT_LOCAL_VIEWPARAM       0x00000040  //���ز鿴����
#define RIGHT_LOCAL_MANAGE_CHANNEL  0x00000080  //����ͨ������
#define RIGHT_LOCAL_BACKUP          0x00000100  //���ر���
#define RIGHT_LOCAL_POWER           0x00000200  //���عػ�/����
#define RIGHT_LOCAL_FORMAT          0x00000400  //���ظ�ʽ��
#define RIGHT_LOCAL_USRMNG          0x00000800  //�����û�����
#define RIGHT_LOCAL_ACCESS          0x00002000  //���ط���Ȩ��
#define RIGHT_LOCAL_MAINTAIN		0x00004000  //����ϵͳά��
#define RIGHT_REMOTE_USRMNG         0x00000800  //Զ���û�����
#define RIGHT_REMOTE_ACCESS         0x00002000  //Զ�̷���Ȩ��
#define RIGHT_REMOTE_MAINTAIN		0x00004000  //Զ��ϵͳά��

#define RIGHT_REMOTE_PTZ            0x00010000  //Զ�̿�����̨
#define RIGHT_REMOTE_MANUAL_RECORD  0x00020000  //Զ���ֶ�¼��
#define RIGHT_REMOTE_PLAYBACK       0x00040000  //Զ�̻ط�
#define RIGHT_REMOTE_PARAMSET       0x00080000  //Զ�����ò���
#define RIGHT_REMOTE_QUERYLOG       0x00100000  //Զ�̲鿴״̬����־
#define RIGHT_REMOTE_ADVANCED       0x00200000  //Զ�̸߼�����:��������ʽ�����ָ�����
#define RIGHT_REMOTE_TALK           0x00400000  //Զ�̷��������Խ�
#define RIGHT_REMOTE_ALARM_SEND     0x00800000  //Զ�����󱨾��ϴ����������
#define RIGHT_REMOTE_CONTROL        0x01000000  //Զ�̿��ƣ��������
#define RIGHT_REMOTE_SERIAL_PORT    0x02000000  //Զ�̿��ƴ���
#define RIGHT_REMOTE_VIEWPARAM      0x04000000  //Զ�̲鿴����
#define RIGHT_REMOTE_MANAGE_CHANNEL 0x08000000  //Զ�̹���ģ��
#define RIGHT_REMOTE_POWER          0x10000000  //Զ�̹ػ�/����
#define RIGHT_REMOTE_FORMAT         0x20000000  //Զ�̸�ʽ��
#define RIGHT_REMOTE_BACKUP         0x40000000  //Զ�̱���

typedef struct
{
    DWORD   dwSize;
    int             bEnable;              /*0:��Ч�û�������, 1:����*/
    DWORD   dwIndex;          /*�û����*/

    char        csUserName[QMAPI_NAME_LEN]; /* �û������32�ֽ�*/
    char        csPassword[QMAPI_PASSWD_LEN]; /* ���� */
    
    DWORD   dwUserRight; /* Ȩ�� */
    
    BYTE  byLocalPreviewRight[QMAPI_MAX_CHANNUM]; //���ؿ���Ԥ����ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
    
    BYTE  byNetPreviewRight[QMAPI_MAX_CHANNUM]; //Զ�̿���Ԥ����ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
    
    BYTE  byLocalPlaybackRight[QMAPI_MAX_CHANNUM]; //���ؿ��Իطŵ�ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
    
    BYTE  byNetPlaybackRight[QMAPI_MAX_CHANNUM]; //Զ�̿��Իطŵ�ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
    
    BYTE  byLocalRecordRight[QMAPI_MAX_CHANNUM]; //���ؿ���¼���ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
    
    BYTE  byNetRecordRight[QMAPI_MAX_CHANNUM];//Զ�̿���¼���ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
    
    BYTE  byLocalPTZRight[QMAPI_MAX_CHANNUM];//���ؿ���PTZ��ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
    
    BYTE  byNetPTZRight[QMAPI_MAX_CHANNUM];//Զ�̿���PTZ��ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
    
    BYTE  byLocalBackupRight[QMAPI_MAX_CHANNUM];//���ر���Ȩ��ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��

    BYTE  byNetBackupRight[QMAPI_MAX_CHANNUM];//Զ�̱���Ȩ��ͨ�� 1-��Ȩ�ޣ�0-��Ȩ��
  
    QMAPI_NET_IPADDR   stIPAddr;
    BYTE    byMACAddr[QMAPI_MACADDR_LEN]; /* �����ַ */
    BYTE    byPriority;                                 /* ���ȼ���0xff-�ޣ�0--�ͣ�1--�У�2--�ߣ�3--��� */
                                                                    /*
                                                                    �ޡ�����ʾ��֧�����ȼ�������
                                                                    �͡���Ĭ��Ȩ��:�������غ�Զ�̻ط�,���غ�Զ�̲鿴��־��״̬,���غ�Զ�̹ػ�/����
                                                                    �С����������غ�Զ�̿�����̨,���غ�Զ���ֶ�¼��,���غ�Զ�̻ط�,�����Խ���Զ��Ԥ��
                                                                                    ���ر���,����/Զ�̹ػ�/����
                                                                    �ߡ�������ִ�г���Ϊ Administrators �鱣����������������κβ���ϵͳ����
                                                                    ��ߡ�������Ա
                                                                    */

    BYTE    byRes[17];  
}QMAPI_NET_USER_INFO,*LPQMAPI_NET_USER_INFO;


typedef struct
{
    DWORD dwSize;
    QMAPI_NET_USER_INFO stUser[QMAPI_MAX_USERNUM];
}QMAPI_NET_USER,*LPQMAPI_NET_USER;

typedef enum __QMAPI_EXCEPTION_TYPE_E
{
    QMAPI_DISK_FULL = 0,
    QMAPI_DISK_ERROR,
    QMAPI_NETWORK_DISCONNECT,
    QMAPI_IPADDR_CONFLICT,
    QMAPI_ILLEGAL_ACCESS,
    QMAPI_VMODE_NOT_MATCH,
}QMAPI_EXCEPTION_TYPE_E;
/*�쳣��������*/
typedef struct
{
    DWORD dwSize;
    QMAPI_HANDLE_EXCEPTION stExceptionHandleType[QMAPI_MAX_EXCEPTIONNUM];
    /*����0-����,1- Ӳ�̳���,2-���߶�,3-��������IP ��ַ��ͻ,4-�Ƿ�����, 5-����/�����Ƶ��ʽ��ƥ��*/
}QMAPI_NET_EXCEPTION,*LPQMAPI_NET_EXCEPTION;

//���������Ԥ��
typedef struct 
{
    DWORD dwSize;
    BYTE  byEnableAudio;		//�Ƿ�����Ԥ����0����Ԥ����1��Ԥ��
    BYTE  byVolume;				//Ԥ��������С
    BYTE  byMenuTransparency;	//�˵��뱳��ͼ��Աȶ�
    BYTE  byTimeOsd;			//�Ƿ���ʾʱ��
    BYTE  byChOsd;				//�Ƿ���ʾͨ������
	BYTE  byAlarmFullScreenTime;//�����Ƿ�ȫ����ʾ����ʾʱ��. 0 ��ȫ����ʾ��1-60 ȫ����ʾʱ�� ��λΪ��
	BYTE  byScreenSaveTime;		//����ʱ�� GUI ����ʱ��	. 0 �Ӳ���1-60 ��Ļ����ʱ������ ��λΪ����
	BYTE  byVgaType;			// VGA�������:0-VGA, 1-BT1120
	BYTE  byPreview[QMAPI_MAX_CHANNUM];
								//Ԥ������
    BYTE  byRes[20];
}QMAPI_NET_PREVIEWCFG, *LPQMAPI_NET_PREVIEWCFG;

//TV����,��Ƶ���
typedef struct 
{
    DWORD dwSize;
    DWORD dwBrightness;			/* ���� */
    WORD  wResolution;			/* �ֱ��� SVGA(800*600), XGA(1024*768), SXGA(1280*1024)*/
    BYTE  byVideoStandard;		/* �����ʽ,1-PAL,0-N */
    BYTE  byIsStartPoll;		/* �Ƿ񿪻���ѯ */
    BYTE  byPollMode;			/* ������ѭ���棬0-�����棬1-4���棬2-9���棬3-16���棬4-25���棬5-32���� */
	BYTE  byPollTime;			/* �����ѯʱ����  ��λ��1�룬0��ʾ����ѯ */
	BYTE  byStaticOrDynamic;	/* 0-static��1-dynamic(�û��ֶ�����) */
	BYTE  byOutputMode;			/* �����Ԥ��ģʽ:0-һ���棬1-�Ļ��棬2-�Ż��棬3-ʮ������ */
	BYTE  byMargin[4];	
								/* byMargin[0]-OD_VOUT, byMargin[1]-OD_VSPOT, byMargin[2]-OD_VGA*/
								/* ����߾���� 0:��߾�  1:�ұ߾�  2:�ϱ߾�  3:�±߾� ��λΪ���� */
	BYTE  byPic32Chn[QMAPI_MAX_CHANNUM];
								/* ����ͨ��λ�õ������ */
	BYTE  byRes[4];
}QMAPI_NET_VIDEOOUTCFG, *LPQMAPI_NET_VIDEOOUTCFG;


typedef enum __QMAPI_HDSTATUS_TYPE_E
{
    QMAPI_HDSTATUS_OK = 0,		//����
    QMAPI_HDSTATUS_UNFORMAT,		//δ��ʽ��
    QMAPI_HDSTATUS_ERROR,			//����
    QMAPI_HDSTATUS_SMART,			//S.M.A.R.T״̬
    QMAPI_HDSTATUS_UNMATCH,		//��ƥ��
    QMAPI_HDSTATUS_SLEEP,			//����
    QMAPI_HDSTATUS_NONE,			//�ݶ���
    QMAPI_HDSTATUS_BUTT,
}QMAPI_HDSTATUS_TYPE_E;

/*Ӳ����Ϣ*/
/*����Ӳ����Ϣ*/
typedef struct
{
    DWORD  dwSize;
    DWORD  dwHDNo;      //Ӳ�̺�, ȡֵ0��QMAPI_MAX_DISKNUM-1
    DWORD  dwHDType;    //Ӳ������(��������) 0:SD��,1:U��,2:Ӳ��
    DWORD  dwCapacity;  //Ӳ������(��������)
    DWORD  dwFreeSpace; //Ӳ��ʣ��ռ�(��������)
    DWORD  dwHdStatus;  //Ӳ��״̬(��������)�� 0��������1��δ��ʽ����2������3��S.M.A.R.T״̬��4����ƥ�䣻5������
    BYTE  byHDAttr;     //0��Ĭ�ϣ�1�����ࣻ2��ֻ��
    BYTE  byRecStatus;  //�Ƿ�����¼��--0:����,1:����¼��
    BYTE  byRes1[2];    //��������
    DWORD  dwHdGroup;   //�����ĸ����飬ȡֵ 0��QMAPI_MAX_HD_GROUP-1
    BYTE   byPath[64];  //Ӳ��mount֮���·��
    BYTE  byRes2[56];   //����
}QMAPI_NET_SINGLE_HD, *LPQMAPI_NET_SINGLE_HD;
/*����Ӳ����Ϣ����*/
typedef struct
{    
    DWORD  dwSize;  
    DWORD  dwHDCount; //Ӳ����
    QMAPI_NET_SINGLE_HD  stHDInfo[QMAPI_MAX_DISKNUM]; 
}QMAPI_NET_HDCFG, *LPQMAPI_NET_HDCFG;
/*��ʽ����������*/
typedef struct
{
    DWORD  dwSize;  
    DWORD  dwHDNo; //Ӳ�̺�
    BYTE  byRes2[32];//����
}QMAPI_NET_DISK_FORMAT, *LPQMAPI_NET_DISK_FORMAT;
//��ʽ��Ӳ��״̬�Լ�����
typedef struct
{
    DWORD  dwSize;  
    DWORD  dwHDNo; //Ӳ�̺�
    DWORD  dwHdStatus;//Ӳ��״̬�� 0����ʽ����ʼ��1�����ڸ�ʽ�����̣�2����ʽ�����
    DWORD  dwProcess;//��ʽ������ 0-100
    DWORD  dwResult;//��ʽ����� 0���ɹ���1��ʧ��
    BYTE  byRes[16];//����
}QMAPI_NET_DISK_FORMAT_STATUS, *LPQMAPI_NET_DISK_FORMAT_STATUS;


/*����������Ϣ ��һ�汾��֧��*/
typedef struct
{
    
    DWORD dwHDGroupNo;          //�����(��������) 0��QMAPI_MAX_HD_GROUP-1
    BYTE  byHDGroupChans[64];  //�����Ӧ��¼��ͨ��, 0����ʾ��ͨ����¼�󵽸����飻1����ʾ¼�󵽸�����
    BYTE  byRes[8];
}QMAPI_NET_SINGLE_HDGROUP, *LPQMAPI_NET_SINGLE_HDGROUP;

/*����������Ϣ���� ��һ�汾��֧��*/
typedef struct
{
    DWORD  dwSize;
    DWORD  dwHDGroupCount;
    QMAPI_NET_SINGLE_HDGROUP  stHDGroupAttr[QMAPI_MAX_HD_GROUP];    
}QMAPI_NET_HDGROUP_CFG, *LPQMAPI_NET_HDGROUP_CFG;


/*ϵͳʱ��*/
typedef struct
{
    DWORD  dwYear;
    DWORD  dwMonth;
    DWORD  dwDay;
    DWORD  dwHour;
    DWORD  dwMinute;
    DWORD  dwSecond;
}QMAPI_NET_TIME, *LPQMAPI_NET_TIME;

/*ʱ������ʱ�Ʋ���*/
typedef struct 
{
    DWORD dwMonth;  //�� 0-11��ʾ1-12����
    DWORD dwWeekNo;  //�ڼ��ܣ�0����1�ܣ�1����2�ܣ�2����3�ܣ� 3����4�ܣ�4�����һ��
    DWORD dwWeekDate;  //���ڼ���0�������գ�1������һ��2�����ڶ���3����������4�������ģ�5�������壻6��������
    DWORD dwHour; //Сʱ����ʼʱ��ȡֵ��Χ0��23�� ����ʱ��ȡֵ��Χ1��23
    DWORD dwMin; //��0��59
}QMAPI_NET_TIMEPOINT;

typedef enum __QMAPI_TIME_ZONE_E
{
    QMAPI_GMT_N12 = 0, //(GMT-12:00) International Date Line West
    QMAPI_GMT_N11, //(GMT-11:00) Midway Island,Samoa
    QMAPI_GMT_N10, //(GMT-10:00) Hawaii
    QMAPI_GMT_N09, //(GMT-09:00) Alaska
    QMAPI_GMT_N08, //(GMT-08:00) Pacific Time (US&amp;Canada)
    QMAPI_GMT_N07, //(GMT-07:00) Mountain Time (US&amp;Canada)
    QMAPI_GMT_N06, //(GMT-06:00) Central Time (US&amp;Canada)
    QMAPI_GMT_N05, //(GMT-05:00) Eastern Time(US&amp;Canada)
    QMAPI_GMT_N0430, //(GMT-04:30) Caracas
    QMAPI_GMT_N04, //(GMT-04:00) Atlantic Time (Canada)
    QMAPI_GMT_N0330, //(GMT-03:30) Newfoundland
    QMAPI_GMT_N03, //(GMT-03:00) Georgetown, Brasilia
    QMAPI_GMT_N02, //(GMT-02:00) Mid-Atlantic
    QMAPI_GMT_N01, //(GMT-01:00) Cape Verde Islands, Azores
    QMAPI_GMT_00, //(GMT+00:00) Dublin, Edinburgh, London
    QMAPI_GMT_01, //(GMT+01:00) Amsterdam, Berlin, Rome, Paris
    QMAPI_GMT_02, //(GMT+02:00) Athens, Jerusalem, Istanbul
    QMAPI_GMT_03, //(GMT+03:00) Baghdad, Kuwait, Moscow
    QMAPI_GMT_0330, //(GMT+03:30) Tehran
    QMAPI_GMT_04, //(GMT+04:00) Caucasus Standard Time
    QMAPI_GMT_0430, //(GMT+04:30) Kabul
    QMAPI_GMT_05, //(GMT+05:00) Islamabad, Karachi, Tashkent
    QMAPI_GMT_0530, //(GMT+05:30) Madras, Bombay, New Delhi
    QMAPI_GMT_0545, //(GMT+05:45) Kathmandu
    QMAPI_GMT_06, //(GMT+06:00) Almaty, Novosibirsk, Dhaka
    QMAPI_GMT_0630, //(GMT+06:30) Yangon
    QMAPI_GMT_07, //(GMT+07:00) Bangkok, Hanoi, Jakarta
    QMAPI_GMT_08, //(GMT+08:00) Beijing, Urumqi, Singapore
    QMAPI_GMT_09, //(GMT+09:00) Seoul, Tokyo, Osaka, Sapporo
    QMAPI_GMT_0930, //(GMT+09:30) Adelaide, Darwin
    QMAPI_GMT_10, //(GMT+10:00) Melbourne, Sydney, Canberra
    QMAPI_GMT_11, //(GMT+11:00) Magadan, Solomon Islands
    QMAPI_GMT_12, //(GMT+12:00) Auckland, Wellington, Fiji
    QMAPI_GMT_13, //(GMT+13:00) Nuku'alofa
}QMAPI_TIME_ZONE_E;


typedef struct 
{
    DWORD				dwSize;			//���ṹ��С
    int					nTimeZone;		//ʱ��
    BYTE				byRes1[12];		//����
    DWORD				dwEnableDST;	//�Ƿ�������ʱ�� 0�������� 1������
    BYTE				byDSTBias;		//����ʱƫ��ֵ��30min, 60min, 90min, 120min, �Է��Ӽƣ�����ԭʼ��ֵ
    BYTE				byRes2[3];		//����
    QMAPI_NET_TIMEPOINT	stBeginPoint;	//��ʱ�ƿ�ʼʱ��
    QMAPI_NET_TIMEPOINT	stEndPoint;		//��ʱ��ֹͣʱ��
}QMAPI_NET_ZONEANDDST, *LPQMAPI_NET_ZONEANDDST;

typedef struct
{
    DWORD			dwSize;				//���ṹ��С
    BYTE			csNTPServer[64];	//NTP��������������IP��ַ
    WORD			wInterval;			//Уʱ���ʱ�䣨��СʱΪ��λ��
    BYTE			byEnableNTP;		//NTPУʱ�Ƿ����ã�0����1����
    signed char		cTimeDifferenceH;	//����ʱ�׼ʱ���ʱ�Сʱ����-12 ... +13
    signed char		cTimeDifferenceM;	//����ʱ�׼ʱ���ʱ����ӣ���0, 30, 45
    BYTE			res1;
    WORD			wNtpPort;			//NTP�������˿ڣ��豸Ĭ��Ϊ123
    BYTE			res2[8];
}QMAPI_NET_NTP_CFG,*LQMAPI_NET_NTP_CFG;


typedef enum __RESTORE_MASK_E
{
    NORMAL_CFG = 0x00000001,       //�豸��������
    VENCODER_CFG = 0x00000002,     //��Ƶ�������
    RECORD_CFG = 0x00000004,           //¼�����
    RS232_CFG = 0x00000008,            //RS232����
    NETWORK_CFG = 0x00000010,          //�������
    ALARM_CFG = 0x00000020,          //��������/�������
    VALARM_CFG = 0x00000040,           //��Ƶ����������
    PTZ_CFG = 0x00000080,              //��̨����
    PREVIEW_CFG = 0x00000100,          //�����������
    USER_CFG = 0x00000200,            //�û�����
}RESTORE_MASK_E;

typedef struct  
{
    DWORD   dwSize;           //���ṹ��С
    DWORD   dwMask;           //���룬��λ��Ч
    BYTE        byRes[16];
}QMAPI_NET_RESTORECFG, *LPQMAPI_NET_RESTORECFG;

/* 
2013-04-10 david: 
�޸�: ���ӵ�ǰ֧�ֵ���������byStreamCount ��Ա.
˵��: �ṹ���С����

*/
typedef struct tagQMAPI_NET_SUPPORT_STREAM_FMT
{
    DWORD       dwSize;                     //struct size
    DWORD           dwChannel;
    DWORD       dwVideoSupportFmt[QMAPI_MAX_STREAMNUM][4];        // Video Format.
    QMAPI_RANGE   stVideoBitRate[QMAPI_MAX_STREAMNUM];
    QMAPI_SIZE    stVideoSize[QMAPI_MAX_STREAMNUM][10];     // Video Size(height,width)
    DWORD       dwAudioFmt[4];              //Audio Format
    DWORD       dwAudioSampleRate[4];       //Audio Sample Rate
    BOOL        bSupportAudioAEC;           //b Support Audio Echo Cancellation
    BYTE        byStreamCount;              //max is QMAPI_MAX_STREAMNUM
    BYTE   		stMAXFrameRate[QMAPI_MAX_STREAMNUM];
    BYTE   		stMINFrameRate[QMAPI_MAX_STREAMNUM];
	BYTE		dwEncodeCapability;
	BYTE            byReserve[25];
}QMAPI_NET_SUPPORT_STREAM_FMT;

//Save Flag
#define QMAPI_COLOR_NO_SAVE               0
#define QMAPI_COLOR_SAVE                  1
#define QMAPI_COLOR_SET_DEF               2
typedef struct tagQMAPI_NET_CHANNEL_COLOR_SINGLE
{
    DWORD       dwSize;                     //struct size
    DWORD           dwChannel;
    DWORD       dwSetFlag;
    DWORD       dwSaveFlag;
    int             nValue;             
    int             nParam;             
}QMAPI_NET_CHANNEL_COLOR_SINGLE;

//ͨ����ɫ����
typedef struct tagQMAPI_NET_CHANNEL_COLOR
{
    DWORD   dwSize;
    DWORD   dwChannel;
    DWORD   dwSetFlag;      //0,���õ�������;1,�������;2,�ָ���һ�α����
    int     nHue;           //ɫ�� 0-255
    int     nSaturation;        //���Ͷ� 0-255
    int     nContrast;      //�Աȶ� 0-255
    int     nBrightness;    //���� 0-255
    int     nDefinition;    //������ 0-255
}QMAPI_NET_CHANNEL_COLOR, *PQMAPI_NET_CHANNEL_COLOR;

typedef struct 
{
    QMAPI_NET_CHANNEL_OSDINFO         stOsdInfo[QMAPI_MAX_CHANNUM];
    QMAPI_NET_CHANNEL_PIC_INFO        stPicInfo[QMAPI_MAX_CHANNUM];
    QMAPI_NET_CHANNEL_COLOR           stColor[QMAPI_MAX_CHANNUM];
    QMAPI_NET_CHANNEL_SHELTER         stShelter[QMAPI_MAX_CHANNUM];
    QMAPI_NET_CHANNEL_MOTION_DETECT           stMotionDetect[QMAPI_MAX_CHANNUM];
    QMAPI_NET_CHANNEL_VILOST                  stVLost[QMAPI_MAX_CHANNUM];
    QMAPI_NET_CHANNEL_HIDEALARM               stHideAlarm[QMAPI_MAX_CHANNUM];
    QMAPI_NET_CHANNEL_RECORD                  stRecord[QMAPI_MAX_CHANNUM];
    QMAPI_NET_CHANNEL_ENCRYPT         stEncrypt;         /**< ������������ */
    QMAPI_NET_CHANNEL_WATERMARK       stWaterMark;     /**< ˮӡ */
}QMAPI_NET_CHANNEL_CFG, *LPQMAPI_NET_CHANNEL_CFG;

typedef enum 
{   
    QMAPI_SHUTTER_AUTO=0, 
    QMAPI_SHUTTER_1_200000,       // 1/200000s
    QMAPI_SHUTTER_1_100000,       // 1/100000s
    QMAPI_SHUTTER_1_50000,        // 1/50000s
    QMAPI_SHUTTER_1_20000,        // 1/20000s
    QMAPI_SHUTTER_1_10000,        // 1/10000s
    QMAPI_SHUTTER_1_5000,     // 1/5000s
    QMAPI_SHUTTER_1_2000,     // 1/2000s
    QMAPI_SHUTTER_1_1000,     // 1/1000s
    QMAPI_SHUTTER_1_500,      // 1/500s
    QMAPI_SHUTTER_1_250,      // 1/250s
    QMAPI_SHUTTER_1_200,      // 1/200s
    QMAPI_SHUTTER_1_175,      // 1/175s
    QMAPI_SHUTTER_1_150,      // 1/150s
    QMAPI_SHUTTER_1_125,      // 1/125s
    QMAPI_SHUTTER_1_100,      // 1/100s || 1/120s
    QMAPI_SHUTTER_1_50,           // 1/50s   || 1/60s
    QMAPI_SHUTTER_1_25,           // 1/25s   || 1/30s
    QMAPI_SHUTTER_1_20,           // 1/20s   || 1/20s
    QMAPI_SHUTTER_1_15,           // 1/17s   || 1/15s
    QMAPI_SHUTTER_1_13,           // 1/13s
    QMAPI_SHUTTER_1_10,           // 1/10s
    QMAPI_SHUTTER_1_5,            // 1/5s
    QMAPI_SHUTTER_Max
} QMAPI_SHUTTER_MODE_E;


//Color QMAPI_RANGE
typedef struct tagQMAPI_NET_COLOR_SUPPORT
{
    DWORD           dwSize;                     //struct size
    DWORD           dwMask;              //��λ��Ч(QMAPI_COLOR_SET_BRIGHTNESS)
    
    QMAPI_RANGE       strBrightness;          
    QMAPI_RANGE       strHue;                 
    QMAPI_RANGE       strSaturation;          
    QMAPI_RANGE       strContrast;                
    QMAPI_RANGE       strDefinition;
    BYTE                byReseved[32];
}QMAPI_NET_COLOR_SUPPORT;

typedef struct tagQMAPI_NET_ENHANCED_COLOR_SUPPORT
{
    DWORD           dwSize;                     //struct size
    DWORD           dwMask;              //��λ��Ч(QMAPI_COLOR_SET_BRIGHTNESS)

    QMAPI_RANGE       strDenoise; //����
    QMAPI_RANGE       strIrisBasic;
    QMAPI_RANGE       strRed;
    QMAPI_RANGE       strBlue;
    QMAPI_RANGE       strGreen;
    QMAPI_RANGE       strGamma;

    QMAPI_RANGE       strEC;
    QMAPI_RANGE       strGC;
    QMAPI_RANGE       strWD;
    BYTE                byReseved[32];
}QMAPI_NET_ENHANCED_COLOR_SUPPORT;

typedef enum
{
    DN_MODE_AUTO = 0,
    DN_MODE_NIGHT,
    DN_MODE_DAY,
    DN_MODE_BUTT
}QMAPI_DN_MODE_E;

//ͨ����ɫ����
typedef struct tagQMAPI_NET_CHANNEL_ENHANCED_COLOR
{
    DWORD   dwSize;
    DWORD   dwChannel;
    DWORD   dwSetFlag;              //0,���õ�������;1,�������;2,�ָ���һ�α����

    BOOL    bEnableAutoDenoise;     //�Զ�����ʹ��
    int     nDenoise;               //���뷧ֵ

    BOOL    bEnableAWB;             //�Զ���ƽ��
    int     nRed;
    int     nBlue;
    int     nGreen; 

    BOOL    bEnableAEC;             //�Զ��ع�(���ӿ���)ʹ��
    int     nEC;                    //�Զ��ع�(���ӿ���)��ֵ

    BOOL    bEnableAGC;             //�Զ�����/�ֶ�����
    int     GC;                     //�Զ�����/�ֶ����淧ֵ

    int     nMirror;                //0:������, 1: ���¾���, 2: ���Ҿ���  3: �������Ҿ���
    BOOL    bEnableBAW;             //�ֶ���ת��ʹ��0,�Զ�1,ҹ��,2 ����

    int     nIrisBasic;             //���
    int     nGamma;
    BOOL    bWideDynamic;           //��̬ʹ��
    int     nWDLevel;               //��̬�ȼ�

    int     nSceneMode;             //����ģʽ
                                    //0x00    /*scene��outdoor*/
                                    //0x01    /*scene��indoor*/
                                    //0x02    /*scene��manual*/
                                    //0x03    /*scene��auto*/
    BOOL    bEnableAIris;           //�Զ���Ȧ
    BOOL    bEnableBLC;             //�������ʹ��

    char	nRotate;				//0 none ,1 90�� ,2 180�� ,3 270��

    BYTE    byReseved[27];
}QMAPI_NET_CHANNEL_ENHANCED_COLOR, *PQMAPI_NET_CHANNEL_ENHANCED_COLOR;


//////////////////////////////////////////////////////////////////////////
//��2������ͨ�Žṹ��

//�������������
typedef struct tagQMAPI_NET_ALARMOUT_CONTROL
{
    DWORD   dwSize;
    int     nChannel;
    WORD    wAction;     //0:ֹͣ��� 1:��ʼ���
    WORD    wDuration;   //����ʱ������Ϊ��λ��0xFFFFFFFF��ʾ��ֹͣ��0��ʾ����ֹͣ
}QMAPI_NET_ALARMOUT_CONTROL;

//��̨����
typedef struct tagQMAPI_NET_PTZ_CONTROL
{
    DWORD   dwSize;
    int     nChannel;		//ͨ����
    DWORD  	dwCommand;		//��̨����������QMAPI_PTZ_CMD_UP
    DWORD  	dwParam;		//��̨���Ʋ���(Ѳ�����)
    BYTE    byRes[64];		//Ԥ�õ�����  (����Ѳ�����ʱ��ΪQMAPI_NET_CRUISE_POINT����)
}QMAPI_NET_PTZ_CONTROL;

typedef struct
{
	BYTE 	byPointIndex;	//Ѳ�����е��±�,���ֵ����QMAPI_MAX_CRUISE_POINT_NUM��ʾ��ӵ�ĩβ
	BYTE 	byPresetNo;	//Ԥ�õ���
	BYTE 	byRemainTime;	//Ԥ�õ�����ʱ��
	BYTE 	bySpeed;		//��Ԥ�õ��ٶ�
}QMAPI_NET_CRUISE_POINT;

typedef struct
{
	BYTE byPointNum; 		//Ԥ�õ�����
	BYTE byCruiseIndex;	//��Ѳ�������
	BYTE byRes[2];
	QMAPI_NET_CRUISE_POINT struCruisePoint[QMAPI_MAX_CRUISE_POINT_NUM];
}QMAPI_NET_CRUISE_INFO;

typedef struct
{
	DWORD dwSize;
	int     nChannel;
	BYTE     byIsCruising;		//�Ƿ���Ѳ��
	BYTE     byCruisingIndex;	//����Ѳ����Ѳ�����
	BYTE     byPointIndex;		//����Ѳ����Ԥ�õ����(�����±�)
	BYTE     byEnableCruise;;	//�Ƿ���Ѳ��
	QMAPI_NET_CRUISE_INFO struCruise[QMAPI_MAX_CRUISE_GROUP_NUM];
}QMAPI_NET_CRUISE_CFG;

typedef struct tagQMAPI_NET_PRESET_INFO
{
    DWORD 		dwSize;
    unsigned short   nChannel;
    unsigned short   nPresetNum;                   //Ԥ�õ����
    unsigned int   no[QMAPI_MAX_PRESET];        //Ԥ�õ����
    char           csName[QMAPI_MAX_PRESET][64];//Ԥ�õ�����
}QMAPI_NET_PRESET_INFO;

#define REC_ACTION_STOP   0
#define REC_ACTION_START  1
//¼�����
typedef struct tagQMAPI_NET_REC_CONTROL
{
    DWORD   dwSize;
    int     nChannel;
    int     nRecordType; //¼�����ͣ��μ�QMAPI_NET_RECORD_TYPE_
    WORD        wAction;     //������0 ֹͣ¼��1 ��ʼ¼��
    WORD     wDuration;  //0xFFFFFFFF��ʾ��ֹͣ��ֱ�������ٴ�ֹͣ���
}QMAPI_NET_REC_CONTROL;

//������״̬��ȡ
typedef struct tagQMAPI_NET_SENSOR_STATE
{
    DWORD   dwSize;
    //0xfffffff��ʶ���б����������ͨ������λ��Ч��
    //�ӵ͵���ǰ16λ��ʾ��������ͨ����λ��������16λ��ʾ�������ͨ��������
    DWORD   dwSensorID; 
    //0xfffffff��ʶ���б����������ͨ��״̬����λ��Ч��
    //�ӵ͵���ǰ16λ��ʾ��������ͨ��״̬λ����16λ��ʾ�������ͨ��״̬����
    DWORD   dwSensorOut;
}QMAPI_NET_SENSOR_STATE;

typedef struct tagQMAPI_NET_VIDEO_STATE
{
    DWORD   dwSize;
    int     nChannelNum;
    int     nState[QMAPI_MAX_CHANNUM];
}QMAPI_NET_VIDEO_STATE;


//�����ϴ�����
typedef struct tagQMAPI_NET_ALARM_NOTIFY
{
    DWORD   dwSize;
    DWORD   dwAlarmType;        //�������ͣ����QMAPI_ALARM_TYPE_E���壩
    DWORD   dwAlarmInput;       //����ͨ���ţ�����������1/4/5ʱ����λ��Ч��ÿλ��ʾӲ�̺�
    BYTE    byRes[32];
}QMAPI_NET_ALARM_NOTIFY;

//����͸������
typedef struct tagQMAPI_NET_SERIAL_DATA
{
    DWORD   dwSize;
    int         nPort;  //1-232, 2-485
    DWORD  dwBufSize;     //���ݳ���
    char    *pDataBuffer;     //����
}QMAPI_NET_SERIAL_DATA;

//�ϴ�ץ��ͼƬ
typedef struct tagQMAPI_NET_SNAP_DATA
{
    DWORD   dwSize;
    int          nChannel;
    int          nLevel;          // 0-5 :0 ���
    DWORD  dwFileType;    // 0:jpgͼƬ��1:bmpͼƬ
    DWORD  dwBufSize;     // ���ݳ���
    char    *pDataBuffer;     //����
}QMAPI_NET_SNAP_DATA;
typedef struct tagQMAPI_NET_SNAP_DATA_V2
{
    DWORD   dwSize;
    int     nChannel;
    int     nLevel;       // 0-5 :0 ���
    DWORD   dwFileType;   // 0:jpgͼƬ��1:bmpͼƬ
    DWORD   dwBufSize;    // ���ݳ���
    char   *pDataBuffer;  //����
    int     nWidth;
    int     nHeight;
}QMAPI_NET_SNAP_DATA_V2;

typedef struct tagQMAPI_NET_VIDEOCALLBACK
{
    DWORD       dwSize;
    int                 nChannel;//ͨ����
    int                 nStreamType;//�������ͣ�0,��������1,������
    void            *pCallBack; //�ص�����ָ��
    DWORD       dwUserData; // �û�����
}QMAPI_NET_VIDEOCALLBACK;


//�û���½
typedef struct tagQMAPI_NET_USER_LOGON
{
    DWORD   dwSize;
    char        csUserName[QMAPI_NAME_LEN];
    char        csPassword[QMAPI_PASSWD_LEN];
    char        csUserIP[QMAPI_MAX_IP_LENGTH]; /*�û�IP��ַ(Ϊ0ʱ��ʾ�����κε�ַ) */
    BYTE    byMACAddr[QMAPI_MACADDR_LEN]; /* �����ַ */
}QMAPI_NET_USER_LOGON;

//
#define QMAPI_UPGRADE_FILE_FLAG               0x38291231
#define QMAPI_UPGRADE_FILE_FLAG2             0x38291232
#define QMAPI_UPGRADE_FILE_FLAG3             0x6851e685

typedef enum
{
	QMAPI_ROM_FILETYPE_ARMBOOT = 0,
	QMAPI_ROM_FILETYPE_KERNEL =  1,
	QMAPI_ROM_FILETYPE_ROOTFS = 2,
	QMAPI_ROM_FILETYPE_USERDATA =  3,
	QMAPI_ROM_FILETYPE_SETTING = 4,
	QMAPI_ROM_FILETYPE_APP = 5,
	QMAPI_ROM_FILETYPE_WEB  =  6,
	QMAPI_ROM_FILETYPE_LOGO = 7,
	QMAPI_ROM_FILETYPE_FACTORY_PARA =8,
	QMAPI_ROM_FILETYPE_BUTT,
}QMAPI_ROM_FILETYPE_E;

//�����ļ�����ͷ��Ϣ
typedef struct tagUPGRADE_ITEM_HEADER
{
    DWORD   dwSize;
    DWORD   dwDataType;    //����������
    DWORD   dwDataLen;     //���ݳ���
    DWORD   dwCRC;         //����CRCУ��
    DWORD   dwDataPos;     //����λ��
    DWORD   dwVersion;
}UPGRADE_ITEM_HEADER;

//�����ļ�ͷ��Ϣ
typedef struct tagQMAPI_UPGRADE_FILE_HEADER
{
    DWORD   dwFlag;         //�����ļ�����(QMAPI_UPGRADE_FILE_FLAG)
    DWORD   dwSize;         //���ṹ���С
    DWORD   dwVersion;      //�ļ��汾
    DWORD   dwItemCount;    //���ڰ������ļ�����
    DWORD   dwPackVer;      //����İ汾
    DWORD   dwCPUType;      //CPU����
    DWORD   dwChannel;      //������ͨ������0x01 | 0x04 | 0x08
    DWORD   dwServerType;   //����������
    char        csDescrip[64];      //������Ϣ
    BYTE    byReserved[32]; 
}QMAPI_UPGRADE_FILE_HEADER, *LPQMAPI_UPGRADE_FILE_HEADER;

//������������
typedef struct tagQMAPI_NET_UPGRADE_REQ
{
    QMAPI_UPGRADE_FILE_HEADER  FileHdr;
    UPGRADE_ITEM_HEADER         stItemHdr[10];
}QMAPI_NET_UPGRADE_REQ;

//��������Ӧ��
typedef struct tagQMAPI_NET_UPGRADE_RESP
{
    DWORD   dwSize;
    int     nResult;        //����Ӧ����
    char 	state;			//����״̬0 ��ͨ״̬1 ��ʼ����2 ������3�������
    char 	progress;		//��������0 - 100%
    char        reserved[30];
}QMAPI_NET_UPGRADE_RESP;

//��������
typedef struct tagQMAPI_NET_UPGRADE_DATA
{
    DWORD   dwSize;
    DWORD   dwFileLength;       //���������ļ�����
    DWORD   dwPackNo;           //�ְ���ţ���0��ʼ
    DWORD   dwPackSize;         //�ְ���С
    BOOL    bEndFile;           //�Ƿ������һ���ְ�
    char        reserved[32];
    BYTE    *pData;
}QMAPI_NET_UPGRADE_DATA;

///Video New Protocol Frame Header
typedef struct QMAPI_NET_FRAME_HEADER
{
    DWORD  dwSize;
    DWORD   dwFrameIndex;
    DWORD   dwVideoSize;
    DWORD   dwTimeTick;
    WORD    wAudioSize;
    BYTE    byFrameType; //0��I֡��1��P֡��2��B֡��ֻ�����Ƶ
    BYTE    byVideoCode;
    BYTE    byAudioCode;
    BYTE    byReserved1;// ��4λ����
    BYTE    byReserved2; // ��4λ����
    BYTE    byReserved3; // ��4λ����
    WORD    wVideoWidth;
    WORD    wVideoHeight;
}QMAPI_NET_FRAME_HEADER;

///Video New Protocol DATAPACK
typedef struct tagQMAPI_NET_DATA_PACKET
{
    QMAPI_NET_FRAME_HEADER    stFrameHeader;
    DWORD                   dwPacketNO;         //�����, 0 ��ʼ
    DWORD                   dwPacketSize;   //����С
    unsigned char               *pData;
}QMAPI_NET_DATA_PACKET,*PQMAPI_NET_DATA_PACKET;

typedef  struct
{
    DWORD            dwSize;
    DWORD            dwChannel;     // 0xff ��������ͨ��
    DWORD            dwFileType; // ȡֵ��Χ QMAPI_NET_RECORD_TYPE_
    DWORD            dwIsLocked;// �Ƿ�������0-δ�����ļ���1-�����ļ���0xff��ʾ�����ļ�������������δ������
    QMAPI_TIME       stStartTime;
    QMAPI_TIME       stStopTime;
}QMAPI_NET_FILECOND,*LPQMAPI_NET_FILECOND;

typedef  struct
{
    DWORD          dwSize;
    char               csFileName[48];
    DWORD          dwFileType; // ȡֵ��Χ QMAPI_NET_RECORD_TYPE_
    QMAPI_TIME     stStartTime;
    QMAPI_TIME     stStopTime;
    DWORD          dwFileSize;
    BYTE              byLocked;// �Ƿ�������0-δ�����ļ���1-�����ļ���0xff��ʾ�����ļ�������������δ������
    BYTE              nChannel;	//0731���
    BYTE              byRes[2];
}QMAPI_NET_FINDDATA,*LPQMAPI_NET_FINDDATA;

typedef  struct _qmapi_net_finddata_list
{
    QMAPI_NET_FINDDATA data;
	struct _qmapi_net_finddata_list *pPre;
	struct _qmapi_net_finddata_list *pNext;
}QMAPI_NET_FINDDATA_LIST,*LPQMAPI_NET_FINDDATA_LIST;


typedef struct
{
    char szBuf[QMAPI_FILES_SIZE];
    int TotalNum;
    int CurNum;
    int StartIndex;
    int EndIndex;
		/*
			�ļ��طŵĿ�ʼʱ��, Ŀǰֻ����������ģʽ��ʹ�� ��ʾ�ʼʱ��㲥��
		*/
	QMAPI_TIME StartTime; 
}QMAPI_FILES_INFO, *LPQMAPI_FILES_INFO;

//�ط����ݻص�ע��ṹ��
typedef struct tagQMAPI_NET_PLAYDATACALLBACK
{
    DWORD       dwSize;
    int             PlayHandle;// �طž��
    DWORD       dwUser;//�û����ݣ����������ݻص�ʱ��ֵ����
    void            *pCallback; //�ص�����ָ��
}QMAPI_NET_PLAYDATACALLBACK;


//��Ƶ�Խ�����ṹ��
typedef struct tagQMAPI_NET_AUDIOTALK
{
    DWORD                   dwSize;
    QMAPI_PAYLOAD_TYPE_E      enFormatTag;// ��Ƶ��������(QMAPI_PT_)
    int                                 nNumPerFrm; //ÿ�βɼ���Ƶ�����ֽڳ���
    DWORD                   dwUser;//�û����ݣ����������ݻص�ʱ��ֵ����
}QMAPI_NET_AUDIOTALK;
//david add 2012-05-11---��ȡSPSPPS base64����������
typedef struct tagQMAPI_NET_SPSPPS_BASE64ENCODE_DATA
{
    DWORD dwSize;
    WORD  chn;
    WORD  streamtype;
    int SPS_LEN;
    int PPS_LEN;
    int SEL_LEN;
    int SPS_PPS_BASE64_LEN;
//  unsigned char SPS_VALUE[64];
    unsigned char SPS_VALUE[128]; //david 2013-03-19:Ϊ��֧��TI ����������������ݳ���
    unsigned char PPS_VALUE[64];
//  unsigned char SEL_VALUE[64];

    unsigned char SEI_VALUE[64];
    char SPS_PPS_BASE64[256];
    unsigned char profile_level_id[8];
}QMAPI_NET_SPSPPS_BASE64ENCODE_DATA;

/**��ȡ��ָ�뷽ʽ*/
typedef enum tagQMAPI_MBUF_POS_POLICY_E
{
    QMAPI_MBUF_POS_CUR_READ = 0,/**<��ǰ��ָ���λ��*/
    QMAPI_MBUF_POS_LAST_READ_nIFRAME,/**<�뵱ǰ��ָ������ĵ�n��I֡���ڵĿ����ʼλ��*/
    QMAPI_MBUF_POS_CUR_WRITE,/**<��ǰдָ���λ��*/
    QMAPI_MBUF_POS_LAST_WRITE_nBLOCK,/**<�뵱ǰдָ������ĵ�n�������ʼλ��*/
    QMAPI_MBUF_POS_LAST_WRITE_nIFRAME,/**<�뵱ǰдָ������ĵ�n��I֡���ڵĿ����ʼλ��, n=0��ʾ�����I֡*/
    QMAPI_MBUF_POS_BUTT
}QMAPI_MBUF_POS_POLICY_E;
/*¼���ļ�����Ϣ--���������Ժ��������������Ϣ*/
typedef struct tagQMAPI_RECFILE_INFO
{
    UINT16  u16Width;           //��Ƶ֡��
    UINT16  u16Height;          //��Ƶ֡��
    UINT16  u16FrameRate;       //��Ƶ��֡��
    UINT16  u16VideoTag;        //��Ƶ����ʶ   QMAPI_PT_H264
    DWORD   u32TotalTime;		  //��Ƶ��ʱ��
    UINT16  u16HaveAudio;       //�Ƿ�����Ƶ��
    UINT16  u16AudioTag;        //��Ƶ����ʶ   QMAPI_PT_G711A
    UINT16  u16AudioBitWidth;   //��Ƶ����
    UINT16  u16AudioSampleRate; //
    DWORD   u32TotalSize;       // �ļ���С
}QMAPI_RECFILE_INFO;

//RTSP����
typedef struct tagQMAPI_NET_RTSP_CFG
{
	DWORD		dwSize;
	DWORD		dwPort;			//RTSP�˿�
	int			nAuthenticate;	//0 ����֤ 1 basic64 2 digest 
	BYTE		byReserve[28];
}QMAPI_NET_RTSP_CFG,*PQMAPI_NET_RTSP_CFG;

//
typedef struct tagQMAPI_NET_SPRCIAL_OSD
{
    int nIndex;         //OSD ����
    BOOL bShow;         //FALSE,����
    int nStartX;        //��ʼx����
    int nStartY;        //��ʼy����
    char csText[64];    //��Ҫ��ʾ���ı�
    int  nLen;          //�ı��ĳ���
}QMAPI_NET_SPECIAL_OSD,*PQMAPI_NET_SPECIAL_OSD;

typedef struct tagQMAPI_NET_UPDATE_FLASH
{
    DWORD dwSize;
    char *pBuff;
    DWORD dwBuffSize;
}QMAPI_NET_UPDATE_FLASH;

typedef struct tagQMAPI_NET_P2P_CFG
{
    DWORD dwSize;
    DWORD dwEnable;
    char  csID[64];
    char  csRes[64];
}QMAPI_NET_P2P_CFG;

typedef struct tagQMAPI_NET_COM_DATA
{
    DWORD       dwSize;
    DWORD       dwChannel;
    BOOL        bIs485;         //485 or 232
    char            byData[128];        //
}QMAPI_NET_COM_DATA;

typedef enum __QMAPI_AUTO_TEST_TYPE_E
{
    CMD_TEST_PTZ         = 0x00000001,
    CMD_TEST_ALARM_IN  = 0x00000002,
    CMD_TEST_ALARM_OUT = 0x00000003,
    CMD_TEST_LED         = 0x00000005,
    CMD_TEST_DISK      = 0x00000006,
    CMD_TEST_CLOCK     = 0x00000007,
    CMD_TEST_REBOOT    = 0x0000000A,
    CMD_TEST_DEFAULT   = 0x0000000B,
    CMD_TEST_AUDIO     = 0x0000000C,
	CMD_TEST_WIFI		= 0x0000000D,
	CMD_TEST_3G		= 0x0000000E,   
	CMD_TEST_RUN_STATUS = 0x0000000F, //���4��������ʱ��
	CMD_TEST_WRITE_MACADDR = 0x00000010, 
	CMD_TEST_WRITE_DOMAIN = 0x00000011	
}QMAPI_AUTO_TEST_TYPE_E;
typedef struct tagQMAPI_NET_AUTO_TEST
{
	DWORD	dwSize;
	DWORD	dwCommand;
	DWORD	dwChannel;
	DWORD	dwErrorCode;
	DWORD	dwBufSize;
    char szPrivateBuffer[256];
}QMAPI_NET_AUTO_TEST;

typedef struct tagQMAPI_NET_LOG_INFO
{
    QMAPI_TIME   stSysStartTime;
    QMAPI_TIME   stSysRunTime;
    char       szReserve[16];
}QMAPI_NET_LOG_INFO;

typedef enum __QMAPI_DN_MODE_E
{
    QMAPI_DN_DT_MODE_AUTO = 0,
    QMAPI_DN_DT_MODE_IR,
    QMAPI_DN_DT_MODE_VIDEO,
    QMAPI_DN_DT_MODE_TIME,
    QMAPI_DN_DT_MODE_BUTT
}QMAPI_DN_DT_MODE_E;
typedef struct tagQMAPI_NET_DAY_NIGHT_DETECTION_EX
{
    DWORD dwSize;
    DWORD dwChannel;
    BYTE byMode;      // 0���Զ���⣬1�����������⣬2����Ƶ��⣬3��ʱ����
    //����������
    BYTE byTrigger;    // ����������-0���͵�ƽ��Ч��1���ߵ�ƽ��Ч
    //��Ƶ���
    BYTE byAGCSensitivity;// ������,0-5
    BYTE byDelay;      // �л���ʱʱ��0-10s��
	
    BYTE byIRCutLevel;// IRCUT����-0���͵�ƽ��Ч��1���ߵ�ƽ��Ч
    BYTE byLedLevel; // ����ƿ���: 0:�͵�ƽ 1:�ߵ�ƽ
    BYTE reserve[2];
    //ʱ����
    QMAPI_SCHEDTIME stColorTime; //��ɫ��ʱ��Σ����ڴ�ʱ�������Ϊ�Ǻڰס�
}QMAPI_NET_DAY_NIGHT_DETECTION_EX;

typedef struct tagQMAPI_NET_USER_KEY
{
    DWORD dwSize;
    int   nLen;
    BYTE  byData[128];
}QMAPI_NET_USER_KEY;


typedef enum __QMAPILogMainType
{
	QMAPI_LOG_TYPE_ALL = 1,         /* ������־���� */
	QMAPI_LOG_TYPE_OPER,            /* �������� */
	QMAPI_LOG_TYPE_ALARM,           /* �澯���� */
	QMAPI_LOG_TYPE_SMART,           /* ���ܷ������� */
	QMAPI_LOG_TYPE_ACCESS,	        /* �������� */
	QMAPI_LOG_TYPE_INFO,            /* ��ʾ��Ϣ���� */
	QMAPI_LOG_TYPE_ABNORMAL,        /* �쳣���� */
	QMAPI_LOG_TYPE_BUTT,
}QMAPI_LOG_MAIN_TYPE_E;

typedef enum __QMAPILogOperType
{
	QMAPI_LOG_OPER_ALL = 1,   	    /* ���в������� */
	QMAPI_LOG_OPER_POWERON,		    /* �������� */
	QMAPI_LOG_OPER_POWEROFF,     	/* �ػ����� */
	QMAPI_LOG_OPER_REBOOT,		    /* �������� */
	QMAPI_LOG_OPER_SAVEPARA,        /* ����������� */
	QMAPI_LOG_OPER_RECMANUAL,  	    /* �ֶ�¼����� */
	QMAPI_LOG_OPER_PTZCONTROL,	    /* ��̨�������� */
	QMAPI_LOG_OPER_STARTCRUISE,	    /* ����Ѳ������ */
	QMAPI_LOG_OPER_STOPCRUISE,	    /* ֹͣѲ������ */
	QMAPI_LOG_OPER_SNAPMAUNAL,	    /* �ֶ�ץ�Ĳ��� */
	QMAPI_LOG_OPER_STARTTALKBACK,	/* �����Խ����� */
	QMAPI_LOG_OPER_STOPTALKBACK,	/* ֹͣ�Խ����� */
	QMAPI_LOG_OPER_UPGRADEAPP,	    /* ����APP���� */
	QMAPI_LOG_OPER_UPGRADEKERNEL,	/* ����KERNEL���� */
	QMAPI_LOG_OPER_UPGRADEWEB,	    /* ����WEB���� */
	QMAPI_LOG_OPER_FORMAT,		    /* ��ʽ�����̲��� */
	QMAPI_LOG_OPER_UNINSTALLDISK,	/* ж�ش��̲��� */
 	QMAPI_LOG_OPER_BUTT,
}QMAPI_LOG_OPER_TYPE_E;
	
typedef enum __QMAPILogAlarmType
{
	QMAPI_LOG_ALARM_ALL = 1,		/* ���б������� */
	QMAPI_LOG_ALARM_SENSOR,			/* ����������*/
	QMAPI_LOG_ALARM_MOTION,			/* �ƶ���ⱨ�� */
	QMAPI_LOG_ALARM_VLOST,			/* ��Ƶ��ʧ���� */
	QMAPI_LOG_ALARM_SHELTER,		/* ��Ƶ�ڵ�����*/
	QMAPI_LOG_ALARM_NET_BROKEN,	    /* ����Ͽ� */
	QMAPI_LOG_ALARM_IP_CONFLICT, 	/* �����ͻ*/
	QMAPI_LOG_ALARM_BUTT,
}QMAPI_LOG_ALARM_TYPE_E;

typedef enum __QMAPILogSmartType
{
    QMAPI_LOG_SMART_ALL = 1,        /* ����ֻ�ܷ������� */
    QMAPI_LOG_SMART_AUDIO_ABNORMAL, /* ��Ƶ�쳣��� */
    QMAPI_LOG_SMART_DEFOCUS,        /* �齹��� */
    QMAPI_LOG_SMART_SCENE_CHANGE,   /* �����任*/
    QMAPI_LOG_SMART_FACE_DETECTION, /* ������� */
    QMAPI_LOG_SMART_BORDER_DETECTION,       /* Խ����� */
    QMAPI_LOG_SMART_REGIONAL_INVASION,      /* �������� */
    QMAPI_LOG_SMART_ENTER_REGION,   /* �������� */
    QMAPI_LOG_SMART_LEAVE_REGION,   /* �뿪���� */
    QMAPI_LOG_SMART_LINGER_DETECTION,       /* �ǻ���� */
    QMAPI_LOG_SMART_PERSONNEL_GATHERS,      /* ��Ա�ۼ� */
    QMAPI_LOG_SMART_FAST_MOVING,            /* �����ƶ� */
    QMAPI_LOG_SMART_PARKING_DETECTION,      /* ͣ����� */
    QMAPI_LOG_SMART_ARTICLES_LEFT,  /* ��Ʒ���� */
    QMAPI_LOG_SMART_ARTICLES_TAKE,  /* ��Ʒ��ȡ */
    QMAPI_LOG_SMART_BUTT,
}QMAPI_LOG_SMART_TYPE_E;

typedef enum __QMAPILogAccessType
{
	QMAPI_LOG_ACCESS_ALL = 1,		/* ���з������� */
	QMAPI_LOG_ACCESS_CLIENT,		/* �ͻ��˷��� */
	QMAPI_LOG_ACCESS_MOBILE,		/* �ֻ����� */
	QMAPI_LOG_ACCESS_RTSP,		    /* RTSP���� */
	QMAPI_LOG_ACCESS_ONVIF,		    /* ONVIF���� */
	QMAPI_LOG_ACCESS_G28181,		/* ������� */
	QMAPI_LOG_ACCESS_ZN,			/* ��ŵNVR���� */
	QMAPI_LOG_ACCESS_BUTT,
}QMAPI_LOG_ACCESS_TYPE_E;

typedef enum __QMAPILogInfoType
{
	QMAPI_LOG_INFO_ALL = 1,		    /* ������ʾ��Ϣ */
	QMAPI_LOG_INFO_RECSCH,		    /* ���ƻ�¼�� */
	QMAPI_LOG_INFO_RECALARM,		/* ��������¼�� */
	QMAPI_LOG_INFO_SNAPFTP,		    /* ץ��FTP�ϴ� */
	QMAPI_LOG_INFO_EMAIL,			/* ������ϢEMAIL�ϴ� */
	QMAPI_LOG_INFO_UPNP_SUCC,		/* UPNPӳ��ɹ� */
	QMAPI_LOG_INFO_DDNS_SUCC,		/* DDNSע��ɹ� */
	QMAPI_LOG_INFO_PPPOE_SUCC,	    /* PPPOE���ųɹ� */
	QMAPI_LOG_INFO_3G_SUCC,		    /* 3G���ųɹ� */
	QMAPI_LOG_INFO_NTP,			    /* NTPУʱ�ɹ� */
	QMAPI_LOG_INFO_BUTT,
}QMAPI_LOG_INFO_TYPE_E;

typedef enum __QMAPILogErrorType
{
	QMAPI_LOG_ERROR_ALL = 1,		/* ���д�����Ϣ */
	QMAPI_LOG_ERROR_MEM,			/* �ڴ���� */
	QMAPI_LOG_ERROR_BUTT,
}QMAPI_LOG_ERROR_TYPE_E;

typedef struct __QMAPI_LOG_INDEX
{
	BYTE byUsed;                    //��ӦQMAPI_LOG_HEADER��currUsedFlag
	BYTE byMainType;                //��־������//QMAPI_LOG_MAIN_TYPE_E
	BYTE bySubType;                 //��ϸ����
	BYTE byChnn;
	
	unsigned long time;             //����������ʱ��
	unsigned long ip;
	
	union
        {
            BYTE byUserID;
            BYTE byAlarmEnd;
        };
	BYTE byBlockID;                 //��1��ʼ0��ʾ����չ
	BYTE byBlockNum;                //ʹ�õĿ����
	BYTE byRecv[1];                 //1//Ԥ��
}QMAPI_LOG_INDEX;


typedef struct _QMAPI_LOG_QUERY_S
{
    DWORD dwSize;
    UINT32 u32SearchMainType;
    UINT32 u32SearchSubType;
    UINT32 u32Num;
    QMAPI_LOG_INDEX logIndex[QMAPI_LOG_INDEX_MAXNUM];//�����һ���ں���
    char logExtInfo[QMAPI_LOG_BLOCK_MAX][QMAPI_LOG_BLOCK_SIZE];
}QMAPI_LOG_QUERY_S;


typedef struct tagQMAPI_NET_DEVICEMAINTAIN
{
    DWORD   dwSize;
    BYTE    byEnable;   //�豸ά�����ܿ���
    BYTE    byIndex;	 //0-6 ���������������������豸ά��ʱ�䣬7����ÿ���豸ά��ʱ��
    BYTE    byReserve1[2];
    QMAPI_SYSTEMTIME stDeviceMaintain; 
}QMAPI_NET_DEVICEMAINTAIN;


typedef struct tagQMAPI_NET_NOTIFY_USER_INFO
{
    DWORD	dwSize;
    UINT32	u32Type; //��ʾ���� QMAPI_NOTIFY_TYPE
    char 	szText[32];//��ʾ�ı���Ϣ
}QMAPI_NET_NOTIFY_USER_INFO;


typedef enum
{
    QMAPI_BITRATE_AUTO,
    QMAPI_BITRATE_SMOOTH, //
    QMAPI_BITRATE_NORMAL, //
    QMAPI_BITRATE_HD,     //high definition
}QMAPI_BITRATE_CONTROL_TYPE;

typedef struct tagQMAPI_SIMPLIFYL_RECORD
{
    BOOL                bEnable;                            /*�Ƿ�¼�� 0-�� 1-��*/
    QMAPI_RECORDSCHED     stRecordSched[7][MAX_REC_SCHED];    /*¼��ʱ��Σ�����һ��������*/
    BYTE                byReserve[8];
}QMAPI_SIMPLIFYL_RECORD, *LPDMS_SIMPLIFY_RECORD; 

/*��ʱʹ��*/
typedef struct tagQMAPI_SET_TIME{
	WORD	bHour;
	WORD	bMinute;
}QMAPI_SET_TIME;
/*��ʱʹ��*/
typedef struct tagQMAPI_SCHED_TIME
{
	BOOL            bEnable;		//
	QMAPI_SET_TIME	BeginTime1;		//
	QMAPI_SET_TIME	EndTime1;
	QMAPI_SET_TIME	BeginTime2;		//
	QMAPI_SET_TIME	EndTime2;
}QMAPI_SCHED_TIME;

typedef struct tagQMAPI_SIMPLIFY_MOTION
{
    BOOL                bEnable;                //�Ƿ���в���
    DWORD               dwSensitive;            //������ ȡֵ0 - 5, ԽСԽ����*/
    BOOL                bPushAlarm;             //�ƶ������Ϣ���Ϳ���
    QMAPI_SCHED_TIME      stSchedTime[8];         /*����ʱ��*/    /*��ʱʹ�ã�֮�����*/
}QMAPI_SIMPLIFY_MOTION, *LPQMAPI_SIMPLIFY_MOTION;

typedef struct tagQMAPI_CONSUMER_PRIVACY_INFO
{
    DWORD   dwSize;
    BOOL    bSpeakerMute;           //1:mute
    BOOL    bPreviewAudioEnable;    // �Ƿ�ʹ��ʵʱ�鿴��Ƶ
    BOOL    bMotdectReportEnable;   // �Ƿ�ʹ���ƶ�����ϱ�
    DWORD   dwSceneMode;            //����ģʽ��0:outdoor, 1:indoor, 2:manual, 3:auto
    QMAPI_BITRATE_CONTROL_TYPE        enBitrateType;
    QMAPI_SIMPLIFYL_RECORD            stRecordInfo;
    QMAPI_SIMPLIFY_MOTION             stMotionInfo;
    char    byRes[12];
}QMAPI_CONSUMER_PRIVACY_INFO;

typedef struct tagQMAPI_NET_CONSUMER_INFO
{
    DWORD   dwSize;
    BOOL    bPrivacyMode;   //0 public, 1 private
    QMAPI_CONSUMER_PRIVACY_INFO   stPrivacyInfo[2]; //0 public, 1 private
    DWORD   dwN1ListenPort; // ����N1Э��Ҫʹ�õĶ˿ںţ�����Ĭ��ֵ��8089
    char    byRes[56];
}QMAPI_NET_CONSUMER_INFO;


typedef struct tagQMAPI_SYSCFG_ONVIFTESTINFO
{
	DWORD	dwSize;
	DWORD	dwDiscoveryMode;		//0 �ر�,1����(Ĭ��)
	char	szDeviceScopes1[64];
	char	szDeviceScopes2[64];
	char	szDeviceScopes3[64];
	BOOL	bAuthEnable;
	BYTE	byReserve[124];
}QMAPI_SYSCFG_ONVIFTESTINFO, *LPQMAPI_SYSCFG_ONVIFTESTINFO;


#endif //_QMAPI_NET_NETSDK_H_






