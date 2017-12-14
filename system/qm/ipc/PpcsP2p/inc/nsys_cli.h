/*
*********************************************************************************************************
*
*                       Copyright (c) 2012 Hangzhou QianMing Technology Co.,Ltd
*                                     Red Bull API Library
*
*********************************************************************************************************
*/
#ifndef __NSYS_CLI_H__
#define __NSYS_CLI_H__

#include "libtypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
*
*       Macro Defines
*
**********************************************************************
*/

#ifdef WIN32
// Pascal compatible
#define CLI_STDCALL __stdcall
#define CLI_CALLBACK CALLBACK
#else
#define CLI_STDCALL
#define CLI_CALLBACK
#endif

#define CLI_MAX_CHNUM		64
#define CLI_MAX_ALARM_INNUM 32
#define CLI_MAX_ALARM_OUTNUM 16
#define CLI_MAX_HARDDISK_NUM 16

#define CLI_NAME_LEN		32
#define CLI_ADDR_LEN		64
#define CLI_MAX_PATH		256
#define CLI_ID_LEN			32
#define CLI_URL_LEN			128
#define CLI_USER_LEN		16
#define CLI_MAC_LEN			6
#define CLI_LOG_LEN			20
#define CLI_MANU_PREFIX_LEN	8

#define MAX_MANAGE_HOST		3 /* ������������ */
#define MAX_UART_NUM		4 /* ��󴮿��� */
#define MAX_OSD_NUM			8 /* ���OSD�� */
#define MAX_CALLBACK_DATA_LEN 1024 /* һ�����������������ݳ��� */
#define DISK_DEV_LEN		16 /* �����豸������ */

#define MAX_DISK_PARTNUM 4 /*����û�������*/

#define MAX_USER_ACCOUNT	8 /* ����û��� */
#define MAX_ONLINE_USER_NUM	16 /* ��������û��� */
#define MAX_IP_FILTER_NUM	20 /* ���IP�������� */
#define MAX_REC_BACKUP_NUM	64 /* ��󱸷ݸ��� */

#define VIDEO_H264_IFRAME	0x21 /* H.264 I֡ */
#define VIDEO_H264_BFRAME	0x22 /* H.264 B֡ */
#define VIDEO_H264_PFRAME	0x23 /* H.264 P֡ */

#define AUDIO_RAW_PCM		0x81 /* pcm */
#define AUDIO_G711_A		0x91 /* G711.a */
#define AUDIO_G711_U		0x92 /* G711.�� */
#define AUDIO_IMA_ADPCM		0xA1 /* IMA ADPCM */
#define AUDIO_DVI4_ADPCM	0xA2 /* DVI4 ADPCM */
#define AUDIO_G726_ADPCM	0xA3 /* G726 */

/* �豸���صĴ����� */
#define ERR_NO_ERROR		0 /* û�д��� */
#define ERR_NO_RIGHT		1 /* �޲���Ȩ�� */
#define ERR_NO_EXIST		2 /* ��������� */
#define ERR_NO_MEMORY		3 /* �豸�ڴ治�� */
#define ERR_NO_SUPPORT		4 /* ������֧�� */
#define ERR_SYS_BUSYNOW		5 /* ϵͳ��æ */
#define ERR_MUST_REBOOT		6 /* ��Ҫ���� */
#define ERR_CONFIG_RDWR		7 /* ���ö�д���� */
#define ERR_INVALID_CMD		8 /* ��Ч���� */
#define ERR_INVALID_PARAM	9 /* �������� */
#define ERR_TOO_MANY_ITEMS	10 /* ���������̫�� */
#define ERR_USER_PASSWORD	11 /* ��Ч�û� */
#define ERR_USER_NO_EXIST	12 /* �û������� */
#define ERR_ADMIN_DONT_DEL	13 /* ����Ա����ɾ�� */
#define ERR_USER_AREADY_EXIST 14 /* �û��Ѵ��� */
#define ERR_TOO_MANY_USERS	15 /* ��ӵ��û����� */
#define ERR_VERIFY_OUT_TIMES 16 /* ��֤�������� */
#define ERR_REC_CREATE		17 /* ����¼��ʧ�� */
#define ERR_REC_NO_DISK		18 /* ¼���޿���Ӳ�� */
#define ERR_REC_NO_STOP		19 /* ¼��δֹͣ */
#define ERR_RESOURCE_NOT_ENOUGH 20 /* ��Դ���� */
#define ERR_REC_IN_BACKUP	21 /* ¼���ڱ��� */
#define ERR_REC_NO_BACKUP	22 /* û�н��б��� */
#define ERR_BACKUP_NO_CANCEL 23 /* �����޷�ȡ�� */
#define ERR_DISK_NO_READY	24 /* ���̳�ʼ��δ��� */
#define ERR_IPPORT_IN_USE	25 /* IP�˿�����ʹ�� */

/* CLI���󣬼����豸���صĴ��� */
#define ERR_CLI_NO_INIT		100 /* δ���ÿ��ʼ�� */
#define ERR_CLI_INACTIVE	101 /* ������������ж� */
#define ERR_CLI_TIME_OUT	102 /* ������ʱ */
#define ERR_CLI_PARAMETER	103 /* �������� */
#define ERR_CLI_OUTOF_MEM	104 /* �ڴ治�� */
#define ERR_CLI_SOCK_RDWR	105 /* socket���ʴ��� */
#define ERR_CLI_FILE_RDWR	106 /* �ļ����ʴ��� */
#define ERR_CLI_SOCK_CLOSE	107 /* socket���ӹر� */


enum {
	EVENT_ALL_EVENTS      = 0, /* �¼��������ñ�ʾȫ���¼� */
	/* �豸�¼� */
	EVENT_VIDEO_REC       = LIB_BIT00, /* ��Ƶ¼��peventΪchannel_state_t*���� */
	EVENT_VIDEO_MD        = LIB_BIT01, /* ��Ƶ���죬peventΪchannel_state_t*���� */
	EVENT_VIDEO_LOSS      = LIB_BIT02, /* ��Ƶ��ʧ��peventΪchannel_state_t*���� */
	EVENT_VIDEO_COVER     = LIB_BIT03, /* ��Ƶ�ڵ���peventΪchannel_state_t*���� */
	EVENT_VIDEO_BITRATE   = LIB_BIT04, /* ��Ƶ���ʣ�peventΪstream_bitrate_t*���� */
	EVENT_ALARM_INPUT     = LIB_BIT05, /* �������룬peventΪchannel_state_t*���� */
	EVENT_ALARM_OUTPUT    = LIB_BIT06, /* ���������peventΪchannel_state_t*���� */
	EVENT_NETWORK_CONN    = LIB_BIT07, /* �������ӣ�peventΪnetwork_state_t*���� */
	EVENT_DISK_STATE      = LIB_BIT08, /* ����״̬��peventΪdisk_state_t*���� */
	EVENT_REC_BACKUP      = LIB_BIT09, /* ����¼�񱸷ݣ�peventΪint*���ͣ�ȡֵΪbackup_state_e */
	EVENT_REC_PLAYBACK    = LIB_BIT10, /* ����¼��طţ�peventΪplayback_state_t*���� */
	EVENT_SYS_CONFIG      = LIB_BIT11, /* ϵͳ���ã�peventΪconfig_state_t*���� */
	EVENT_SYS_CONTROL     = LIB_BIT12, /* ϵͳ���ƣ�peventΪint*���� */
	EVENT_SYS_UPGRAND     = LIB_BIT13, /* ϵͳ������peventΪprogress_state_t*���ͣ�stateΪ0 ����֪ͨ 1 �ļ��쳣 2 �̼���ƥ�� 3 ������ȡ�� 4 �����̼��ظ� */
	EVENT_SYS_EXCEPTION   = LIB_BIT14, /* ϵͳ�쳣��peventΪsys_exception_t*���� */
	EVENT_SYS_EXIT        = LIB_BIT15, /* ϵͳ�˳���peventΪint*���ͣ�ȡֵΪsys_exit_e */
	EVENT_USER_BREAK      = LIB_BIT16, /* �û��Ͽ������ӣ�peventΪNULL���յ����¼���Ӧ�ùر����� */
	EVENT_AVC_ONLINE      = LIB_BIT17, /* �豸���ߣ�peventΪcli_dev_t���� */
	EVENT_AVC_CONNECT     = LIB_BIT18, /* ����Ƶͨ�����ӣ�peventΪchannel_state_t*���ͣ�stateȡֵΪconn_state_e */
	EVENT_SYS_INTERNAL    = LIB_BIT19, /* �ڲ��¼����û���ʹ�� */
	EVENT_VIDEO_LOSS_EX   = LIB_BIT20, /* ��Ƶ��ʧ��չ��peventΪvideo_state_t*���� */
	EVENT_AVC_PLAY              = LIB_BIT21,/*����ʵʱ������, peventΪplayback_state_t*���� */
	
	/* �����¼� */
	EVENT_CONN_RECONNECT  = LIB_BIT24, /* �豸���ӻָ� */
	EVENT_CONN_DISCONNECT = LIB_BIT25, /* �豸������ֹ��peventΪNULL */
	EVENT_PLAY_RECONNECT  = LIB_BIT26, /* �������ӻָ���phandleΪ���ž�� */
	EVENT_PLAY_DISCONNECT = LIB_BIT27 /* ����������ֹ��phandleΪ���ž����peventΪNULL */
};

typedef struct {
	int ch; /* ͨ�� */
	int state; /* ״̬ 0��ʾ�رգ����򴥷� */
} channel_state_t;

typedef struct {
	int ch; /*ͨ��*/
	int type; /*��Ƶ����video_input_e*/
}vinput_type_t;

typedef struct {
	int ch; /* ͨ�� */
	int streamindex; /* �������� */
	unsigned int streambps; /* ������ */
} stream_bitrate_t;

enum network_state_e {
	NETWORK_TYPE_NONE, /* �� */
	NETWORK_TYPE_ETHERNET, /* ��̫�� */
	NETWORK_TYPE_PPPOE, /* PPPOE���� */
	NETWORK_TYPE_WIFI, /* WIFI���� */
	NETWORK_TYPE_WI3G /* 3G���� */
};

typedef struct {
	int type; /* ���ͣ�network_state_e���� */
	int state; /* ״̬ 0��ʾ�����������쳣 */
} network_state_t;

enum disk_state_e {
	DISK_STATE_FORMAT, /* ��ʽ�� */
	DISK_STATE_INSERT, /* �ƶ����̲��� */
	DISK_STATE_REMOVE, /* �ƶ����̰γ� */
	DISK_STATE_READY /* �����Ѿ���������¼���طţ�����״̬�����Դ��̺ţ������򽫷���ERR_DISK_NO_READY���� */
};

typedef struct {
	int state; /* ״̬�� disk_state_e���� */
	int diskindex; /* ���̺� */
	int formatprecent; /* ��ɰٷֱȣ�-1��ʾ��ʽ��ʧ�� */
} disk_state_t;

typedef struct {
	int state; /* ״̬ 0��ʾ�����������쳣 */
	int precent; /* ��ɰٷֱ� */
} progress_state_t;

enum backup_state_e {
	BACKUP_COMPLETE, /* ������� */
	BACKUP_CANCEL, /* ����ȡ�� */
	BACKUP_DEVICE_ERR, /* �����豸�쳣 */
	BACKUP_INTERNAL_ERR, /* �����ڲ����� */
	BACKUP_FILE_OPT_ERR, /* �����ļ������쳣 */
	BACKUP_DVD_ERR /* DVD��¼�쳣 */
};

typedef struct {
	int ch; /* ͨ�� */
	int win; /* ���� */
	int state; /* ״̬ 0 ���Ž�����1 ���²��� */
} playback_state_t;

typedef struct {
	int ch; /* ͨ�� */
	int config; /* ��CONFIG_DEVICE_INFO�ȶ��� */
} config_state_t;

enum sys_exit_e {
	EXIT_REBOOT, /* �����˳� */
	EXIT_POWER_OFF /* �ػ��˳� */
};

enum sys_exception_e {
	EXP_DISK_ERR, /* ���̴��� �쳣���� 0 ������1 ¼��Ӳ���� */
	EXP_SIGNAL_ERR, /* ��Ƶ�ź��쳣 �쳣���� 0 ������1 �ź��쳣 */
	EXP_NETWORK_ERR /* �����쳣 �쳣���� 0 ������1 �����쳣 */
};

typedef struct {
	int exp_type; /* �쳣���ͣ�sys_exception_e���� */
	int exp_code; /* �쳣���룬�������쳣���Ͷ��� */
} sys_exception_t;

enum conn_state_e {
	CONN_STATE_DISCONNECT, /* ���ӶϿ���δ���ӣ� */
	CONN_STATE_CONNECT, /* �����ϣ������ӣ� */
	CONN_STATE_CONNECTING, /* ������ */
	CONN_STATE_REFUSED, /* ���ӱ��ܾ� */
	CONN_STATE_AUTHORIZE_ERR, /* �û���֤���� */
	CONN_STATE_PARAMTER_ERR /* �������� */
};


typedef struct {
	char dev_model[16]; /* ��Ʒ�ͺţ���0��β��ASSIC�ַ��� */
	char serial_no[16]; /* ���кţ���0��β��ASSIC�ַ��� */
	char hardware_ver[16]; /* Ӳ���汾�ţ���0��β��ASSIC�ַ��� */
	char software_ver[16]; /* ����汾�ţ���0��β��ASSIC�ַ��� */
	char issue_date[16]; /* �̼��������ڣ���0��β��ASSIC�ַ��� */
	unsigned int dev_ability; /* �豸���� */
	unsigned char total_ch_num; /* �豸ͨ���� */
	unsigned char analog_ch_num; /* ģ��ͨ���� */
	unsigned char digital_ch_num; /* ����ͨ���� */
	unsigned char disk_num; /* Ӳ���� */
	unsigned char audio_num; /* ��Ƶ�� */
	unsigned char alarmin_num; /* ���������� */
	unsigned char alarmout_num; /* ��������� */
	unsigned char ethernet_num; /* ��̫������ */
	char res[32]; /* ���� */
} dev_info_t;



enum {
	RETURN_WAIT_MOST, /* �ȴ����п�������أ�Ĭ�ϣ� */
	RETURN_WAIT_NORMAL, /* �ȴ���Ҫ������أ�����Ԥ������������������ */
	RETURN_WAIT_LEAST /* �ȴ����������أ�����޶ȵĵȴ� */
};



enum {
	KEEP_ALIVE_SEND,
	KEEP_ALIVE_RECV
};

typedef struct {
	int state; /* ���ͻ����״̬��KEEP_ALIVE_SEND��KEEP_ALIVE_RECV  */
	void *pdata; /* ���ݻ����� */
	size_t len; /* ���ݳ��� */
} keep_alive_t;


/* ͨ������״̬ */
typedef struct {
	unsigned char connstate; /* ͨ������״̬��conn_state_e���� */
	unsigned char recstate; /* ͨ��¼��״̬��0��ʾδ¼��1��ʾ����¼�� */
	unsigned char videosignal; /* ͨ����Ƶ״̬��0��ʾ����Ƶ��1��ʾ����Ƶ */
	unsigned char videodetect; /* ͨ�����״̬���������ܷ�������0��ʾ���¼���1��ʾ���� */
} ch_work_state_t;

enum {
	HDD_STATE_NORMAL, /* ״̬���� */
	HDD_STATE_INVALID, /* �Ƿ����� */
	HDD_STATE_STANDBY, /* ����״̬ */
	HDD_STATE_READONLY /* ����ֻ�� */
};

typedef struct {
	int ch; /* ͨ�� */
	int state; /* ״̬ 0��ʾ�رգ�����Ϊ����video_input_e */
} video_state_t;



/* ͨ������״̬��չ */
typedef struct {
	unsigned int connstate; /* ͨ������״̬��conn_state_e���� */
	unsigned int recstate; /* ͨ��¼��״̬��0��ʾδ¼��1��ʾ����¼�� */
	unsigned int videostate; /* ͨ����Ƶ״̬��0��ʾ����Ƶ������Ϊ����video_input_e */
	unsigned int videodetect; /* ͨ�����״̬���������ܷ�������0��ʾ���¼���1��ʾ���� */
	int res[4];
} ch_work_state_ex_t;

/* ϵͳ״̬��չ */
typedef struct {
	unsigned char alarmin[CLI_MAX_ALARM_INNUM]; /* ��������״̬��0��ʾδ������1��ʾ���� */
	unsigned char alarmout[CLI_MAX_ALARM_OUTNUM]; /* �������״̬��0��ʾδ������1��ʾ���� */
	unsigned char hddstate[CLI_MAX_HARDDISK_NUM]; /* Ӳ��״̬��HDD_STATE_NORMAL ~ HDD_STATE_READONLY */
	ch_work_state_ex_t chstate[CLI_MAX_CHNUM]; /* ͨ������״̬ */
	unsigned char res[64];
} cli_work_state_ex_t;

/* ϵͳ״̬ */
typedef struct {
	unsigned char alarmin[CLI_MAX_ALARM_INNUM]; /* ��������״̬��0��ʾδ������1��ʾ���� */
	unsigned char alarmout[CLI_MAX_ALARM_OUTNUM]; /* �������״̬��0��ʾδ������1��ʾ���� */
	unsigned char hddstate[CLI_MAX_HARDDISK_NUM]; /* Ӳ��״̬��HDD_STATE_NORMAL ~ HDD_STATE_READONLY */
	ch_work_state_t chstate[CLI_MAX_CHNUM]; /* ͨ������״̬ */
} cli_work_state_t;


enum {
	ATTRIB_PTZ_CONFIG        = LIB_BIT00, /* ֧����̨���� */
	ATTRIB_PTZ_CONTROL       = LIB_BIT01, /* ֧����̨���� */
	ATTRIB_VIDEO_LOSS        = LIB_BIT02, /* ֧����Ƶ��ʧ */
	ATTRIB_MOTION_DETECT     = LIB_BIT03, /* ֧���ƶ���� */
	ATTRIB_RECORD_OSD        = LIB_BIT04, /* ֧��¼��OSD */
	ATTRIB_DIGITAL_WATERMARK = LIB_BIT05, /* ֧������ˮӡ */
	ATTRIB_VIDEO_ROTATE      = LIB_BIT06, /* ֧����Ƶ��ת */
	ATTRIB_VIDEO_EFFECT      = LIB_BIT07, /* ֧����ƵЧ������ */
	ATTRIB_PRIVACY_AREA      = LIB_BIT08, /* ֧����˽���� */
	ATTRIB_IRCUT_FILTER      = LIB_BIT09, /* ֧�ֺ������ */
	ATTRIB_WIDE_DYNAMIC      = LIB_BIT10, /* ֧�ֿ�̬ */
	ATTRIB_WHITE_BANLANCE    = LIB_BIT11, /* ֧�ְ�ƽ�� */
	ATTRIB_TIME_COFIG        = LIB_BIT12, /* ֧��ʱ�����ã�IPCʱ��ͬ�� */
	ATTRIB_JPEG_SNAPSHOT     = LIB_BIT13, /* ֧��jpeg���� */
	ATTRIB_NETWORK_CONFIG    = LIB_BIT14, /* ֧���������ã�IPC������� */
	ATTRIB_AUDIO_SOURCE_FROM = LIB_BIT15 /* ֧����ƵԴѡ�� */
};

typedef struct {
	int audionum; /* ��Ƶ������Ϊ0��ʾ����Ƶ */
	int videonum; /* ��Ƶ���� */
	unsigned int chattrib; /* ͨ������ */
	char res[4];
} channel_info_t;



typedef struct {
	int win; /* ���ں� */
	lib_rect_t rc; /* ����λ�úͳߴ磬���������������ص������������صĴ��ڣ� */
} win_rect_t;

typedef struct {
	int ch; /* ͨ�� */
	int index; /* ���������� */
	int win; /* ���� */
} cli_preview_t;


typedef struct {
	int ch; /* ͨ�� */
	int win; /* ���� */
	int rectype; /* ¼�����ͣ�REC_TYPE_ALL�� */
	lib_duration_t playdur; /* ����ʱ�� */
} cli_playback_t;


enum {
	PLAY_CMD_START, /* ��ʼ��ָ����ţ�param��Ϊ0ʱ�ָ���������״̬ */
	PLAY_CMD_PAUSE, /* ��ͣ���ţ�param����Ϊ0 */
	PLAY_CMD_STOP, /* ֹͣ���ţ��ͷ���Դ��param����Ϊ0 */
	PLAY_CMD_SEEK, /* ��ʱ�䶨λ��playmomΪ��λʱ�� */
	PLAY_CMD_STEP, /* ��֡�������ţ�param����Ϊ0 */
	PLAY_CMD_SLOW, /* ���ţ�paramΪ���ű��� */
	PLAY_CMD_FAST, /* ��ţ�paramΪ��ű��� */
	PLAY_CMD_SOUND, /* �������ƣ�paramΪ0������Ϊ1������ */
	PLAY_CMD_GET_VOLUME, /* ������ȡ�����Դ��ںţ�paramΪ������С[OUT] */
	PLAY_CMD_SET_VOLUME, /* �������ڣ����Դ��ںţ�paramΪ������С[0, 100] */
	PLAY_CMD_REVERSE, /* ���ţ�param����Ϊ0 */
	PLAY_CMD_ONEFRAME, /* ����һ֡����ͣ��param����Ϊ0 */
	PLAY_CMD_POSITION /* ��ǰ����λ�ã�playmomΪ����ʱ��[OUT] */
						/* param����cli_native_play_control���ô���0��ʾ��ȡ��ǰ���ڲ���λ�ã�����1��ʾͬ��ģʽ����λ��[IN] */
						/* param����cli_remote_play_control���÷���0��ʾ���ڲ����У�����1��ʾ�����ѽ���[OUT] */
};

typedef struct {
	int win; /* ���� */
	int param; /* ���Ʋ��� */
	lib_moment_t playmom; /* ����ʱ�� */
} native_play_control_t;


enum {
	FLAGS_FRAME_COMPLETE = LIB_BIT00, /* ֡�߽磬һ֡���ܷ�Ϊ������ݿ� */
	FLAGS_FRAME_FINISH   = LIB_BIT01 /* ֡������¼�������ѽ����������ݲ���ʵ�����ݣ���ȻҪ�ͷţ� */
};

typedef struct {
	int datatype; /* �������ͣ�VIDEO_H264_IFRAME��AUDIO_IMA_ADPCM�� */
	int dataflags; /* ���ݱ�־��FLAGS_FRAME_COMPLETE�� */
	unsigned int timestamp; /* ʱ���(ms)��������ʼ��ѭ������ */
	char *databuf; /* ���ݻ�����ָ�� */
	size_t len; /* ���ݳ��� */
	void *pnode; /* ֡����ָ�룬�����ͷŽӿ��ã������޸� */
} stream_data_t;



enum {
	DEV_SD_CARD,    /* SD�� */
	DEV_USB_DISK,   /* U�� */
	DEV_ESATA_DISK, /* ESATAӲ�� */
	DEV_DVD_WRITER  /* DVD��¼�� */
};

/* �����豸 */
typedef struct {
	int devtype; /* �豸���� DEV_SD_CARD ~ DEV_DVD_WRITER */
	char devname[CLI_NAME_LEN]; /* �豸���� */
	unsigned int freecapacity; /* ��������(MB) */
	unsigned int totalcapacity; /* ������(MB) */
} backup_dev_t;


typedef struct {
	int ch; /* ¼��ͨ�� */
	int type; /* ¼������ REC_TYPE_ALL ~ REC_TYPE_ALARM */
	lib_duration_t dur; /* ¼��ʱ��� */
} rec_duration_t;


enum {
	CONFIG_DEVICE_INFO, /* �豸��Ϣ��pconfigΪdev_info_t*���ͣ�ֻ���� */
	CONFIG_DEVICE_LOCAL, /* �豸�������ã�pconfigΪdev_local_t*���� */
	CONFIG_DEVICE_TIME, /* �豸ʱ�䣬pconfigΪlib_moment_t*���� */
	CONFIG_DATETIME_MODE, /* ʱ������ģʽ��pconfigΪdate_time_mode_t*���� */
	CONFIG_DST_TIME, /* ����ʱʱ�䣬pconfigΪcli_dst_t*���� */
	CONFIG_USER_INFO, /* �û��˺���Ϣ��pconfigΪuser_info_t*���ͣ�ֻ������ǰΪ����Ա���ܻ���˺����룩 */
	CONFIG_ONLINE_USER, /* �����û���Ϣ��pconfigΪonline_user_t*���� */
	CONFIG_MANAGE_HOST, /* ����������pconfigΪmanage_host_t*���� */
	CONFIG_VIDEO_SOURCE, /* ��ƵԴ������pconfigΪvideo_source_t*���� */
	CONFIG_VIDEO_EFFECT, /* ��ƵЧ��������pconfigΪeffect_value_t*���� */
	CONFIG_VIDEO_ENCODE, /* ��Ƶ���������pconfigΪvideo_encode_t*���ͣ�index��ʾ��Ƶ�������� */
	CONFIG_PRIVACY_AREA, /* ��˽����pconfigΪlib_rect_t*���� */
	CONFIG_VIDEO_MD, /* ��Ƶ���죬pconfigΪvideo_md_t*���� */
	CONFIG_VIDEO_LOSS, /* ��Ƶ��ʧ��pconfigΪevent_trigger_t*���� */
	CONFIG_VIDEO_COVER, /* ��Ƶ�ڵ���pconfigΪevent_trigger_t*���� */
	CONFIG_AUDIO_SOURCE, /* ��ƵԴ������pconfigΪaudio_source_t*���� */
	CONFIG_AUDIO_ENCODE, /* ��Ƶ���������pconfigΪaudio_encode_t*���ͣ�index��ʾ��Ƶ�������� */
	CONFIG_REC_CHANNEL, /* ¼�����ã�pconfigΪrec_channel_t*���� */
	CONFIG_ALARM_INPUT, /* �������룬pconfigΪalarm_input_t*���� */
	CONFIG_SYS_EXCEPTION, /* �쳣����pconfigΪexception_trigger_t*���ͣ�index��ʾ�쳣���룬sys_exception_e���� */
	CONFIG_REC_SCHEDULE, /* ¼��ƻ���pconfigΪschedule_config_t*���� */
	CONFIG_ALARMIN_SCHEDULE,  /* �������벼���ƻ���pconfigΪschedule_config_t*���� */
	CONFIG_ALARMOUT_SCHEDULE, /* ��������ƻ���pconfigΪschedule_config_t*���� */
	CONFIG_BUZZEROUT_SCHEDULE, /* ����������ƻ���pconfigΪschedule_config_t*���� */
	CONFIG_EMAILSEND_SCHEDULE, /* �ʼ����ͼƻ���pconfigΪschedule_config_t*���� */
	CONFIG_NAMEOSD_INFO, /* ͨ����OSD��Ϣ��pconfigΪvenc_osd_t*���ͣ�Windowsϵͳֻ�õ�osdname��Ա����index��ʾOSD������ */
	CONFIG_NAMEOSD_DISPLAY, /* ͨ����OSD��ʾ��pconfigΪosd_display_t*���ͣ�index��ʾOSD������ */
	CONFIG_TIMEOSD_DISPLAY, /* ʱ��OSD��ʾ��pconfigΪosd_display_t*���� */
	CONFIG_DISK_MANAGE, /* Ӳ�̹���pconfigΪdisk_manage_t*���� */
	CONFIG_UART_INFO, /* UART��Ϣ��pconfigΪuart_param_t*���ͣ���δʵ�֣� */
	CONFIG_PTZ_PARAM, /* PTZ������pconfigΪptz_param_t*���� */
	CONFIG_AVC_CHANNEL, /* ͨ�����룬pconfigΪavc_channel_t*���� */
	CONFIG_AVC_TIME, /* IPCʱ�䣬pconfigΪavc_time_t*���� */
	CONFIG_AVC_NETWORK, /* IPC���������pconfigΪavc_network_t*���� */
	CONFIG_NET_IP_FILTER, /* ����IP���ˣ�pconfigΪcli_ip_filter_t*���� */
	CONFIG_NET_GLOBAL, /* ����ȫ�ֲ�����pconfigΪcli_net_global_t*���� */
	CONFIG_NET_ETHERNET, /* ��̫����pconfigΪcli_net_ethernet_t*���� */
	CONFIG_NET_PPPOE, /* PPPOE������pconfigΪcli_net_pppoe_t*���� */
	CONFIG_NET_WIFI_AP, /* WIFI����㣬pconfigΪcli_wifi_ap_t*���� */
	CONFIG_NET_WIFI_CARD, /* WIFI������pconfigΪcli_net_ethernet_t*���� */
	CONFIG_NET_WIFI, /* WIFI������pconfigΪcli_net_wifi_t*���� */
	CONFIG_NET_WI3G, /* Wireless 3G������pconfigΪcli_net_wi3g_t*���� */
	CONFIG_NET_NTP, /* NTP������pconfigΪcli_net_ntp_t*���� */
	CONFIG_NET_P2P, /* P2P������pconfigΪcli_net_p2p_t*���� */
	CONFIG_NET_FTP, /* FTP������pconfigΪcli_net_ftp_t*���ͣ���δʵ�֣� */
	CONFIG_NET_EMAIL, /* EMAIL������pconfigΪcli_net_email_t*���� */
	CONFIG_NET_DDNS_SERVICE, /* DDNS�����б�pconfigΪcli_service_ddns_t*���� */
	CONFIG_NET_DDNS, /* DDNS������pconfigΪcli_net_ddns_t*���� */
	CONFIG_AUDIO_SOURCE_FROM /* ��ƵԴѡ��pconfigΪint*���ͣ�AUDIO_FROM_CAMERA�ȣ� */
};

typedef struct {
	char devname[CLI_NAME_LEN]; /* �豸�� */
	unsigned char remoteraddr; /* ң�ص�ַ[0, 255] */
	char res[3];
} dev_local_t;

typedef struct {
	char dstenable; /* �Ƿ���������ʱ */
	unsigned char dstbias; /* ����ʱƫ��ֵ��30��60��90��120���ӣ� */
	unsigned char beginmonth; /* ��ʼ�·ݣ�[0, 11]��ʾ1�µ�12�£� */
	unsigned char beginweekno; /* ��ʼ������[0, 4]��ʾ���µ�1�ܵ����һ�ܣ� */
	unsigned char beginweekday; /* ��ʼ���ڵ�������[0, 6]��ʾ�����쵽�������� */
	unsigned char beginhour; /* ��ʼСʱ[0, 23] */
	unsigned char beginminute; /* ��ʼ����[0, 59] */
	unsigned char endmonth; /* �����·ݣ�[0, 11]��ʾ1�µ�12�£� */
	unsigned char endweekno; /* ����������[0, 4]��ʾ���µ�1�ܵ����һ�ܣ� */
	unsigned char endweekday; /* �������ڵ�������[0, 6]��ʾ�����쵽�������� */
	unsigned char endhour; /* ����Сʱ[0, 23] */
	unsigned char endminute; /* ��������[0, 59] */
} cli_dst_t;

typedef struct {
	lib_rect_t rc; /* λ�ü��ߴ� */
	effect_value_t effect; /* Ч������ */
} video_source_t;

enum {
	PTZ_RELATE_NONE, /* ����̨���� */
	PTZ_RELATE_PRESET = LIB_BIT00, /* Ԥ�õ���������ʱptzpreset��Ч */
	PTZ_RELATE_TOUR   = LIB_BIT01 /* Ѳ����������ʱptztour��Ч */
};

typedef struct {
	unsigned char ptzrelate[CLI_MAX_CHNUM]; /* ��̨�������� PTZ_RELATE_NONE ~ PTZ_RELATE_TOUR */
	unsigned char ptzpreset[CLI_MAX_CHNUM]; /* ��̨Ԥ�õ� */
	unsigned char ptztour[CLI_MAX_CHNUM]; /* ��̨Ѳ���� */
} ptz_relate_t;

typedef struct {
	unsigned char recch[CLI_MAX_CHNUM]; /* ¼��ͨ�� */
	unsigned char alarmout[CLI_MAX_ALARM_OUTNUM]; /* ������� */
	unsigned char beepout; /* ������ */
	unsigned char emailsend; /* �ʼ����� */
	char res[2]; /* ���� */
} event_trigger_t;

typedef struct {
	int mdsensitive; /* ���������� */
	ptz_relate_t mdrelate; /* �������� */
	event_trigger_t mdtrigger; /* ���촥�� */
	unsigned int mdregion[24]; /* �������򣬰�λ�������� */
} video_md_t;

typedef struct {
	int streamindex; /* ¼����Ƶ�������ţ���0��ʼ */
	unsigned char audiorec; /* ¼����0 ��¼����1 ¼�� */
	unsigned char prerectime; /* ����Ԥ¼ʱ��[0, 30](��)��Ϊ0��ʾ��Ԥ¼ */
	char res[2]; /* ���� */
} rec_channel_t;

enum {
	ALARM_TYPE_NO, /* ����(Normal Open) */
	ALARM_TYPE_NC  /* ����(Normal Close) */
};

typedef struct {
	int alarmtype; /* �������� */
	int autoclear; /* �Զ����[0, 900](����)��0��ʾ�����ֶ���� */
	ptz_relate_t alarmrelate; /* �������� */
	event_trigger_t alarmtrigger; /* �������� */
} alarm_input_t;

typedef struct {
	unsigned char alarmout[CLI_MAX_ALARM_OUTNUM]; /* ������� */
	unsigned char beepout; /* ������ */
	unsigned char emailsend; /* �ʼ����� */
	char res[2]; /* ���� */
} exception_trigger_t;

typedef struct {
	unsigned short xpos; /* ˮƽλ�� */
	unsigned short ypos; /* ��ֱλ�� */
	char osddisp; /* �Ƿ���ʾ 0 ����ʾ��1 ��ʾ */
	char res[3];
} osd_display_t;

typedef struct {
	char recoverwrite; /* ¼�񸲸� 0 �����ǣ�1 �Զ����� */
	unsigned char recpacktime; /* ¼����ʱ��[5, 120](����) */
	char res[2];
} disk_manage_t;

enum {
	OUTPUT_TYPE_ALARM, /* ������� */
	OUTPUT_TYPE_EMAIL, /* �����ʼ� */
	OUTPUT_TYPE_BEEPER /* ��������� */
};

typedef struct {
	int type; /* ���� ¼��ƻ�ΪREC_TYPE_NORMAL ~ REC_TYPE_VIDEODETECT������Ϊ0 */
	int wday; /* ���� [0, 6]����ʾ�������쵽�������� */
	lib_time_t beginning; /* ��ʼʱ�� */
	lib_time_t ending; /* ����ʱ�� */
} schedule_config_t;

/* AVCͨ������ */
typedef struct {
	char protocol[DEV_PROTOCOL_LEN]; /* Э���� */
	char username[CLI_USER_LEN]; /* �û��� */
	char password[CLI_USER_LEN]; /* ���� */
	char ipaddr[DEV_ADDR_LEN]; /* ip������ */
	unsigned short ipport; /* ip�˿� */
	unsigned char inport; /* ����ţ�����ͬһ�豸�Ķ������ */
	unsigned char linkmode; /* ����ģʽ��LINK_MODE_AUTO��LINK_MODE_UDP�� */
	unsigned char enable; /* ʹ�� */
	char res[31]; /* ���� */
} avc_channel_t;

/* ip���ʲ��� */
typedef struct {
	int ipenable; /* ip���Ƿ�����0 ������1 ���� */
	char ipbegin[CLI_ADDR_LEN]; /* ��ʼip */
	char ipend[CLI_ADDR_LEN]; /* ����ip */
} cli_ip_filter_t;

/* ����ȫ�ֲ��� */
typedef struct {
	char upnpenable; /* UPNP�Ƿ����ã�0 �����ã�1 ���� */
	char multiipenable; /* ��IP�����Ƿ����ã�0 �����ã�1 ���� */
	char netpriority[6]; /* �����������ȼ��ߵ��ͣ���ʾ����ʹ�ö�Ӧ���͵����磬NETWORK_TYPE_ETHERNET�ȣ�NETWORK_TYPE_NONE��ʾ���� */
	unsigned short cmdport; /* ����˿ڣ��豸���Ӷ˿ں� */
	unsigned short qdataport; /* ���ݶ˿ڣ��豸���ݴ���˿ں� */
	unsigned short httpport; /* http�˿� */
	unsigned short rtspport; /* rtsp�˿ڣ���δʹ�ã� */
	unsigned short mobileport; /* �ƶ��豸�˿ڣ���δʹ�ã� */
	unsigned short multicastport; /* �鲥�˿ڣ���δʹ�ã� */
	char res[64]; /* ���� */
} cli_net_global_t;

/* ��̫��/WIFI���� */
typedef struct {
	char ipaddr[CLI_ADDR_LEN]; /* IP��ַ */
	char ipmask[CLI_ADDR_LEN]; /* �������� */
	char gatewayaddr[CLI_ADDR_LEN]; /* ���ص�ַ */
	char dnsaddr[2][CLI_ADDR_LEN]; /* DNS��������ַ */
	char dhcpenable; /* �Ƿ�����dhcp */
	char autodns; /* �Ƿ��Զ���ȡdns */
	unsigned char macaddr[CLI_MAC_LEN]; /* mac��ַ */
} cli_net_ethernet_t;

/* ��̫��״̬ */
typedef struct {
	int etherstate; /* ��̫��״̬��0 δ���ӣ� 1 �����ӣ���ʱipaddr��Ч�� */
	char ipaddr[CLI_ADDR_LEN]; /* ��̫��IP��ַ */
} cli_status_ethernet_t;

/* PPPOE���� */
typedef struct {
	int pppoeenable; /* PPPoE�Ƿ����ã�0 �����ã�1 ���� */
	char username[CLI_NAME_LEN]; /* PPPoE�����û��� */
	char password[CLI_NAME_LEN]; /* PPPoE�������� */
} cli_net_pppoe_t;

/* PPPOE״̬ */
typedef struct {
	int pppoestate; /* PPPoE״̬��0 δ���ӣ� 1 �����ӣ���ʱipaddr��Ч���� 2 �������� */
	char ipaddr[CLI_ADDR_LEN]; /* PPPoE����IP��ַ */
} cli_status_pppoe_t;

enum {
	SECURITY_NONE, /* �޼��� */
	SECURITY_WEP, /* WEP��Ŀǰ֧���Զ��͹�����Կ���֣�����ϵͳ�ݲ�֧�� */
	SECURITY_WPA, /* WPA */
	SECURITY_WPA2, /* WPA2 */
	SECURITY_WPA_AND_WPA2, /* WPA+WPA2 */
	SECURITY_WPA_PSK, /* WPA-PSK */
	SECURITY_WPA2_PSK, /* WPA2-PSK */
	SECURITY_WPA_AND_WPA2_PSK, /* WPA-PSK+WPA2-PSK */
	SECURITY_WPA_EAP, /* WPA-EAP */
	SECURITY_WPA2_EAP, /* WPA2-EAP */
	SECURITY_WPA_AND_WPA2_EAP, /* WPA-EAP+WPA2-EAP */
	SECURITY_WPS /* WPS */
};

/* Wifi�������Ϣ */
typedef struct {
	char ssid[CLI_NAME_LEN]; /* SSID���� */
	int netspeed; /* ��������(Kbps) */
	int signalch; /* �ŵ� */
	int workmode; /* ����ģʽ��0 Unknown��1 ad-hocģʽ��2 mangeģʽ */
	int signalstrength; /* �ź�ǿ�ȣ�[0, 100] */
	int netsecurity; /* ����������ͣ�SECURITY_NONE�� */
} cli_wifi_ap_t;

/* Wifi���� */
typedef struct {
	int wifienable; /* wifi�Ƿ����ã�0 �����ã�1 ���� */
	char ssid[CLI_NAME_LEN]; /* SSID���� */
	char password[CLI_NAME_LEN]; /* ���� */
	int netsecurity; /* ����������ͣ�SECURITY_NONE�� */
} cli_net_wifi_t;

/* Wifi����״̬ */
typedef struct {
	int wifistate; /* WIFI״̬��0 δ���ӣ� 1 �����ӣ���ʱipaddr��Ч���� 2 �������� */
	int signalch; /* �ŵ� */
	int signalstrength; /* �������� */
	int netspeed; /* ��������(Kbps) */
	char ipaddr[CLI_ADDR_LEN]; /* WIFI IP��ַ */
} cli_status_wifi_t;

/* Wireless 3G���� */
typedef struct {
	int wi3genable; /* 3G�Ƿ����ã�0 �����ã�1 ���� */
	char apn[CLI_NAME_LEN]; /* ���Ž�������� */
	char dialnumber[CLI_NAME_LEN]; /* ���ź��� */
	char username[CLI_NAME_LEN]; /* 3G�����û��� */
	char password[CLI_NAME_LEN]; /* 3G�������� */
} cli_net_wi3g_t;

/* Wireless 3G����״̬ */
typedef struct {
	int wi3gstate; /* 3G״̬��0 δ���ӣ� 1 �����ӣ���ʱipaddr��Ч���� 2 �������� */
	int strength; /* 3G�ź�ǿ�� */
	char network_mode[CLI_NAME_LEN]; /* 3G����ϵͳģʽ */
	char network_type[CLI_NAME_LEN]; /* 3G�������� */
	char ipaddr[CLI_ADDR_LEN]; /* 3G����IP��ַ */
} cli_status_wi3g_t;

/* NTP���� */
typedef struct {
	int ntpenable; /* NTP�Ƿ����ã�0 �����ã�1 ���� */
	int zonebias; /* ��ǰʱ����UTCʱ���(����) */
	char ntpaddr[CLI_ADDR_LEN]; /* NTP�������������ַ */
	unsigned short ntpport; /* NTP�˿� */
	unsigned short checkperiod; /* �������(����)������5�������� */
} cli_net_ntp_t;

/* P2P���� */
typedef struct {
	int p2penable; /* P2P�Ƿ����ã�0 �����ã�1 ���� */
	char p2pid[CLI_ID_LEN]; /* P2P ID�ţ�ֻ���� */
	char p2paddr[CLI_ADDR_LEN]; /* P2P�����������ַ��ֻ������Ϊ�ձ�ʾ��Ч */
	unsigned short remoteport; /* P2PԶ�̷���˿ںţ�����P2P�������ַʹ�ã�0 ��Ч */
	unsigned short localport; /* P2P�豸���ؼ��ض˿ں� */
	char iosappurl[CLI_URL_LEN]; /* P2P iOSӦ�����ص�ַ��ֻ������Ϊ�ձ�ʾ��Ч */
	char androidappurl[CLI_URL_LEN]; /* P2P AndroidӦ�����ص�ַ��ֻ������Ϊ�ձ�ʾ��Ч */
	char res[112]; /* ����Ϊ�� */
} cli_net_p2p_t;

/* P2P��չ���� */
typedef struct {
	unsigned int p2ptype; /* P2P���� */
	//char p2pmanuprefix[CLI_MANU_PREFIX_LEN]; /* P2P����ǰ׺ */
	char p2pid[CLI_ID_LEN]; /* P2P ID�ţ�ֻ���� */
	char res[128]; /* ����Ϊ�� */
} cli_net_p2p_extra_t;

/* EMAIL���� */
typedef struct {
	char username[CLI_NAME_LEN]; /* �û��� */
	char password[CLI_NAME_LEN]; /* ���� */
	char smtpaddr[CLI_ADDR_LEN]; /* SMTP��������ַ */
	unsigned short smtpport; /* SMTP�˿� */
	char sslenable; /* SSL�Ƿ����ã�0 �����ã�1 ���� */
	char smtpverify; /* SMTP�Ƿ�����֤��0 ����֤��1 ��֤ */
	char senderaddr[CLI_ADDR_LEN]; /* �ʼ������ߵ�ַ */
	char receiveraddr[2][CLI_ADDR_LEN]; /* �ʼ������ߵ�ַ */
} cli_net_email_t;

enum {
	DDNS_DOMAIN_SUBMIT  = LIB_BIT00, /* �豸֧��DDNS����ע�� */
	DDNS_DOMAIN_FIXED   = LIB_BIT01, /* DDNS�����̶��������޸� */
	DDNS_POSTFIX_FIXED  = LIB_BIT02, /* ������׺�̶�����DDNS���������������޸� */
	DDNS_ACCOUNT_FIXED  = LIB_BIT03, /* �����˺Ź̶��������޸� */
	DDNS_ACCOUNT_HIDDEN = LIB_BIT04, /* �����˺����أ�������ʾ */
	DDNS_ALIASNAME_SET  = LIB_BIT05 /* ����֧�����ñ�����ͨ�����DDNS_DOMAIN_FIXEDʹ�� */
};

/* DDNS���÷����б�ֻ���� */
typedef struct {
	char ddnsname[CLI_NAME_LEN]; /* ������ */
	char ddnsaddr[CLI_ADDR_LEN]; /* ������IP������ */
	unsigned short ddnsport; /* �������˿� */
	unsigned short ddnscapabilties; /* DDNS���ԣ�DDNS_DOMAIN_SUBMIT�� */
	char ddnsdomain[CLI_ADDR_LEN]; /* DDNS�̶�����������DDNS_DOMAIN_FIXED��Ч */
} cli_service_ddns_t;

/* DDNS���� */
typedef struct {
	int ddnsenable; /* DDNS�Ƿ����ã�0 �����ã�1 ���� */
	char ddnsname[CLI_NAME_LEN]; /* ��Ӧ��DDNS������ */
	char ddnsdomain[CLI_ADDR_LEN]; /* DDNS�ɱ��������������DDNS_DOMAIN_FIXED���Ի���DDNS_ALIASNAME_SET������Ч */
	char username[CLI_NAME_LEN]; /* DDNS�û��� */
	char password[CLI_NAME_LEN]; /* DDNS���� */
} cli_net_ddns_t;

/* DDNS״̬ */
typedef struct {
	int ddnsstate; /* DDNS״̬ */
	char ipaddr[CLI_ADDR_LEN]; /* ������ӦIP��ַ */
} cli_status_ddns_t;

enum {
	P2P_STATUS_UNCONNECTED, /* δ���� */
	P2P_STATUS_CONNECTING, /* �������� */
	P2P_STATUS_CONNECTED, /* ������ */
	P2P_STATUS_CONNECT_FAIL, /* ����ʧ�� */
	P2P_STATUS_CONNECT_UNKNOW /* ����״̬δ֪ */
};

/* P2P״̬ */
typedef struct {
	char p2pid[CLI_ID_LEN]; /* P2P ID�ţ�ֻ���� */
	unsigned short connstate; /* ����״̬(ֻ��),P2P_STATUS_* */
	unsigned short connerrnum; /* ����ʧ�ܴ�����(ֻ��) */
} cli_status_p2p_t;

/* ����״̬ */
typedef struct {
	union {
		cli_status_ethernet_t ethernetstate; /* ��̫��״̬��CONFIG_NET_ETHRENET��Ч */
		cli_status_pppoe_t pppoestate; /* PPPOE״̬��CONFIG_NET_PPPOE��Ч */
		cli_status_wifi_t wifistate; /* WIFI״̬��CONFIG_NET_WIFI��Ч */
		cli_status_wi3g_t wi3gstate; /* 3G״̬��CONFIG_NET_WI3G��Ч */
		cli_status_ddns_t ddnsstate; /* DDNS״̬��CONFIG_NET_DDNS��Ч */
		cli_status_p2p_t p2pstate; /* P2P״̬��CONFIG_NET_P2P��Ч */
	};
} cli_net_status_t;


enum {
	RANGE_VGA_OUTPUT, /* VGA���������Χ��display_range_tָ�� */
	RANGE_HDMI_OUTPUT, /* HDMI���������Χ��display_range_tָ�� */
	RANGE_CVBS_OUTPUT, /* CVBS���������Χ��display_range_tָ�� */
	RANGE_VIDEO_MD, /* ���������Χ��md_range_tָ�� */
	RANGE_PTZ_PROTOCOL, /* ��̨Э�鷶Χ��ptz_param_tָ�루λ���ԣ� */
	RANGE_AUDIO_SOURCE, /* ��ƵԴ������Χ��adsrc_range_tָ�� */
	RANGE_VIDEO_SOURCE, /* ��ƵԴ������Χ��effect_range_tָ�� */
	RANGE_VIDEO_EFFECT, /* ��ƵЧ��������Χ��effect_range_tָ�� */
	RANGE_VIDEO_ENCODE /* ��Ƶ���������Χ��vdenc_range_tָ�룬indexΪ��Ӧ�������� */
};

typedef struct {
	effect_value_t minval; /* ��Сֵ */
	effect_value_t maxval; /* ���ֵ */
} effect_range_t;

typedef struct {
	int dispreso; /* �ֱ���֧�֣�0��ʾ��֧�ֵ��� */
	int refreshfreq; /* ˢ��Ƶ��֧�֣�0��ʾ��֧�ֵ��� */
	effect_range_t dispeffect; /* ��ʾЧ����Χ */
} display_range_t;

typedef struct {
	int horznum; /* ˮƽ���� */
	int vertnum; /* ��ֱ���� */
	int minsensitive; /* ��С������ */
	int maxsensitive; /* ��������� */
} md_range_t;

typedef struct {
	audio_source_t minval; /* ��Сֵ */
	audio_source_t maxval; /* ���ֵ */
} adsrc_range_t;

typedef struct {
	video_encode_t minenc; /* ��Сֵ */
	video_encode_t maxenc; /* ���ֵ */
} vdenc_range_t;



typedef struct {
	int ch; /* ͨ�� */
	int type; /* ���� */
	unsigned int ts; /* ���ʱ��� */
	size_t len; /* ���� */
	char *pdata; /* ���� */
} data_info_t;


typedef struct {
	void* hplaywnd; /* ���Ŵ��� */
	int streamindex; /* ��Ƶ�������ţ���0��ʼ */
	int autoplay; /* �Զ����ţ�����ȴ�IPC���Ӻ�����ͨ��Ԥ�� */
} real_play_info_t;


typedef struct {
	void* hplaywnd; /* ���Ŵ��� */
	int rectype; /* ¼�����ͣ�REC_TYPE_ALL�� */
	lib_duration_t recdur; /* ¼��ʱ��� */
} rec_play_info_t;



typedef struct {
	int recvbps; /* ������������ */
	int recvjitter; /* �������ն��� */
} play_recv_info_t;


typedef struct {
	int param; /* ���Ʋ��� */
	lib_moment_t playmom; /* ����ʱ�� */
} remote_play_control_t;



enum {
	RIGHT_DATE_TIME        = LIB_BIT00, /* ����ϵͳʱ�䡢ʱ���ʽ������ʱ����Ȩ�� */
	RIGHT_NETWORK_CONFIG   = LIB_BIT01, /* ������̫����3G��WIFI�������������IP���˵Ȳ�������Ȩ�� */
	RIGHT_ENCODE_CONFIG    = LIB_BIT02, /* ��������Ƶ�����������Ȩ�� */
	RIGHT_RECODE_CONFIG    = LIB_BIT03, /* ����¼�������¼��ƻ����� */
	RIGHT_RECODE_CONTROL   = LIB_BIT04, /* ¼�����Ȩ�� */
	RIGHT_RECORD_BACKUP    = LIB_BIT05, /* ¼�񱸷�Ȩ�� */
	RIGHT_ALARM_CONFIG     = LIB_BIT06, /* �����������롢�������Ȩ�� */
	RIGHT_ALARM_CONTROL    = LIB_BIT07, /* �����������롢��������������������Ȩ�� */
	RIGHT_REMOTE_CHANNEL   = LIB_BIT08, /* Զ��IPͨ������Ȩ�� */
	RIGHT_CHANNEL_OSD      = LIB_BIT09, /* ����ͨ��ʱ�䡢����OSD����Ȩ�� */
	RIGHT_PRIVACY_CONFIG   = LIB_BIT10, /* ��˽��������Ȩ�� */
	RIGHT_EXCEPTION_CONFIG = LIB_BIT11, /* �쳣��������Ȩ�� */
	RIGHT_VIDEO_DETECT     = LIB_BIT12, /* ������Ƶ��ʧ�����졢�ڵ�����Ȩ�� */
	RIGHT_VIDEO_EFFECT     = LIB_BIT13, /* ��ƵЧ������Ȩ�� */
	RIGHT_DISK_MANAGE      = LIB_BIT14, /* ����Ӳ��ʹ�ò�������ʽ��Ȩ�� */
	RIGHT_LOG_VIEW         = LIB_BIT15, /* ��־�鿴Ȩ�� */
	RIGHT_WORK_MODE        = LIB_BIT16, /* ͨ������ģʽ����Ƶ��ʽ����Ȩ�� */
	RIGHT_REMOTE_LOGIN     = LIB_BIT17, /* �û�Զ�̵�¼Ȩ�� */
	RIGHT_ONLINE_USER      = LIB_BIT18, /* �����û�����Ȩ�� */
	RIGHT_SYSTEM_UPGRADE   = LIB_BIT19, /* ϵͳ����Ȩ�� */
	RIGHT_REBOOT_POWEROFF  = LIB_BIT20 /* ϵͳ�������ػ�Ȩ�� */
};

typedef struct {
	char username[CLI_USER_LEN]; /* �û��� */
	char password[CLI_USER_LEN]; /* ���� */
	unsigned int userright; /* �û�Ȩ�ޣ�λ���ԣ���RIGHT_DATE_TIME�� */
	unsigned char ptzch[CLI_MAX_CHNUM]; /* ��̨����ͨ��Ȩ�� */
	unsigned char previewch[CLI_MAX_CHNUM]; /* Ԥ��ͨ��Ȩ�� */
	unsigned char playbackch[CLI_MAX_CHNUM]; /* �ط�ͨ��Ȩ�� */
	unsigned char remotech[CLI_MAX_CHNUM]; /* Զ��ͨ��Ȩ�ޣ��������ͨ��Ȩ��ʹ�� */
	char ipaddr[CLI_ADDR_LEN]; /* ip��ַ����ʾ���û�ֻ�����ض���ַ��Ϊ�������ַ */
	unsigned char macaddr[6]; /* mac��ַ����ʾ���û�ֻ�����ض���ַ��0�����ַ */
	char res[18]; /* ���� */
} user_info_t;


typedef struct {
	char username[CLI_USER_LEN]; /* �����û��� */
	char ipaddr[CLI_ADDR_LEN]; /* ����ip��ַ */
} online_user_t;


enum {
	ALARMIN_MODE_DISARMING, /* ���� */
	ALARMIN_MODE_SCHEDULE, /* �ƻ����� */
	ALARMIN_MODE_ARMING /* �ֶ����� */
};


enum {
	REC_MODE_STOP, /* ֹͣ¼�� */
	REC_MODE_SCHEDULE, /* �ƻ�¼�� */
	REC_MODE_MANUAL /* �ֶ�¼�� */
};



/* PTZ���������� */
enum {
	CAMERA_MENU_CONTROL, /* �˵����� */
	PTZ_DIR_CONTROL, /* ������� */
	PTZ_LENS_CONTROL, /* ��ͷ���� */
	PTZ_PRESET_CONTROL, /* Ԥ��λ���� */
	PTZ_TOUR_CONTROL, /* Ѳ������ */
	PTZ_AUX_CONTROL, /* �������ؿ��� */
	PTZ_HOME_POSITION /* ����λ���� */
};

/* CAMERA_MENU_CONTROL������ */
enum {
	MENU_OPEN, /* �˵��� */
	MENU_CLOSE, /* �˵��ر� */
	MENU_MOVE_UP, /* ���� */
	MENU_MOVE_DOWN, /* ���� */
	MENU_MOVE_LEFT, /* ���� */
	MENU_MOVE_RIGHT, /* ���� */
	MENU_UPPER_LEVEL, /* ��һ���˵� */
	MENU_LOWER_LEVEL, /* ��һ���˵� */
	MENU_SEL_CONFIRM /* �˵�ѡ��ȷ�� */
};

/* PTZ_DIR_CONTROL�����majorparam��ʾת���ٶ�[0, 15] */
enum {
	DIR_STOP, /* ֹͣ */
	DIR_UP, /* ���� */
	DIR_DOWN, /* ���� */
	DIR_LEFT, /* ���� */
	DIR_RIGHT, /* ���� */
	DIR_UP_LEFT, /* ���� */
	DIR_UP_RIGHT, /* ���� */
	DIR_DOWN_LEFT, /* ���� */
	DIR_DOWN_RIGHT /* ���� */
};

/* PTZ_LENS_CONTROL�����majorparam��ʾ�����ٶ�[0, 15] */
enum {
	LENS_STOP, /* ֹͣ */
	IRIS_CLOSE, /* ��ȦС */
	IRIS_OPEN, /* ��Ȧ�� */
	FOCUS_NEAR, /* �۽��� */
	FOCUS_FAR, /* �۽�Զ */
	ZOOM_WIDE, /* ����� */
	ZOOM_TELE /* ����խ */
};

/* PTZ_PRESET_CONTROL�����majorparam��ʾ��Ӧ��Ԥ�õ� */
enum {
	PRESET_SET, /* �趨Ԥ��λ */
	PRESET_GOTO, /* ����Ԥ��λ */
	PRESET_REMOVE /* �Ƴ�Ԥ��λ */
};

/* PTZ_TOUR_CONTROL�����majorparam��ʾ��Ӧ��Ѳ���� */
/* ��ӻ�ɾ��ʱminorparam��ʾ��Ӧ��Ԥ�õ㣬���ʱstaytime��ʾ��Ԥ�õ�ͣ��ʱ�� */
enum {
	TOUR_PRESET_ADD, /* ����Ԥ�õ� */
	TOUR_PRESET_DEL, /* ɾ��Ԥ�õ� */
	TOUR_CLEAR, /* ���Ѳ���� */
	TOUR_START, /* ��ʼѲ�� */
	TOUR_STOP /* ֹͣѲ�� */
};

/* PTZ_AUX_CONTROL������ */
enum {
	AUX_LIGHT_ON, /* �ƹ���ƿ� */
	AUX_LIGHT_OFF, /* �ƹ���ƹ� */
	AUX_WIPER_ON, /* ��ˢ���ƿ� */
	AUX_WIPER_OFF, /* ��ˢ���ƹ� */
	AUX_WASHER_ON, /* ��ϴ���ƿ� */
	AUX_WASHER_OFF, /* ��ϴ���ƹ� */
	AUX_HEATER_ON, /* ���ȿ��ƿ� */
	AUX_HEATER_OFF /* ���ȿ��ƹ� */
};

/* PTZ_HOME_POSITION������ */
enum {
	HOME_POSITION_SET, /* ���ÿ���λ */
	HOME_POSITION_GOTO /* ���ÿ���λ */
};

/* ��̨���� */
typedef struct {
	unsigned char majorcmd; /* ���������� PTZ_DIRECTION_CONTROL ~ PTZ_TOUR_CONFIG */
	unsigned char minorcmd; /* �ο�������������Ӧ�������� */
	unsigned char majorparam; /* �����Ʋ��� */
	unsigned char minorparam; /* �ο��Ʋ��� */
	unsigned short staytime; /* Ԥ�õ�Ѳ����ͣ��ʱ��(��) */
	char res[2]; /* ���� */
} ptz_control_t;


enum {
	REC_TYPE_ALL         = 0, /* ȫ������ */
	REC_TYPE_NORMAL      = LIB_BIT00, /* ��ͨ¼�� */
	REC_TYPE_VIDEODETECT = LIB_BIT01, /* ��Ƶ���¼�񣬰�����Ƶ���졢��ʧ���ڵ����µ�¼�� */
	REC_TYPE_ALARM       = LIB_BIT02 /* ����¼�� */
};

typedef struct {
	unsigned int samplenum; /* ��֡�� */
	unsigned int samplelen; /* �ܳ���(Bytes) */
	rec_duration_t recdur; /* ¼��� */
} rec_info_t;


enum {
	LOG_TYPE_ALL       = 0, /* ȫ������ */
	LOG_SYSTEM_CONTROL = LIB_BIT00, /* ϵͳ��������CONTROL_USER_ADD�ȶ��壩 */
	LOG_SYSTEM_CONFIG  = LIB_BIT01, /* ϵͳ���ã���CONFIG_DEVICE_INFO�ȶ��壩 */
	LOG_SYSTEM_EVENT   = LIB_BIT02 /* ϵͳ�¼�����EVENT_VIDEO_REC�ȶ��壩����LOG_SYSTEM_CONTROL�غϵĳ��� */
};

enum {
	CONTROL_USER_ADD, /* ����û� */
	CONTROL_USER_SET, /* �޸��û� */
	CONTROL_USER_DEL, /* ɾ���û� */
	CONTROL_USER_BREAK, /* �Ͽ������û� */
	CONTROL_USER_LOGIN, /* �û���¼����־����Ϊ�û��� */
	CONTROL_USER_LOGOUT, /* �û��ǳ�����־����Ϊ�û��� */
	CONTROL_ALARM_CLEAR, /* �ֶ�������� */
	CONTROL_ALARM_INPUT, /* �������벼�� */
	CONTROL_ALARM_OUTPUT, /* ����������� */
	CONTROL_PTZ, /* ��̨���� */
	CONTROL_REC, /* ¼����� */
	CONTROL_REC_BACKUP, /* ¼�񱸷� */
	CONTROL_REC_PLAY, /* ¼�񲥷� */
	CONTROL_REAL_PLAY, /* ʵʱ���� */
	CONTROL_WORK_MODE, /* ����ģʽ���� */
	CONTROL_FORMAT_DISK, /* Ӳ�̸�ʽ�� */
	CONTROL_DEFAULT_RESET, /* �ָ�Ĭ������ */
	CONTROL_LOG_CLEAR, /* ��־��� */
	CONTROL_DEV_UPGRADE, /* �豸���� */
	CONTROL_DEV_BOOTUP, /* �豸���� */
	CONTROL_DEV_REBOOT, /* �豸���� */
	CONTROL_DEV_SHUTDOWN /* �豸�ػ� */
};

enum {
	OPERATE_CONTROL_START, /* ���ƿ�ʼ */
	OPERATE_CONTROL_STOP, /* ���ƽ��� */
	OPERATE_CONFIG_GET, /* ������ȡ */
	OPERATE_CONFIG_PUT, /* �������� */
	OPERATE_EVENT_START, /* �¼���ʼ */
	OPERATE_EVENT_STOP /* �¼����� */
};

typedef struct {
	int logtype; /* ��־���ͣ�LOG_SYSTEM_CONTROL�� */
	int logcmd; /* ��־�������־������ض��� */
	int logopt; /* ��־������OPERATE_CONTROL_START�� */
	int logch; /* ��־ͨ�� */
	lib_moment_t logmom; /* ��¼ʱ�� */
	char logtext[CLI_LOG_LEN]; /* ������Ϣ�������û��� */
} log_info_t;


enum {
	UPGRADE_FROM_FILE, /* �ļ�������ʹ�������ļ�·�� */
	UPGRADE_FROM_URL /* URL���� */
};


#ifdef __cplusplus
}
#endif

#endif /* #ifndef __NSYS_CLI_H__ */
