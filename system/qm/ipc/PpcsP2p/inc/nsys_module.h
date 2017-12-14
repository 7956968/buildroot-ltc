/*
*********************************************************************************************************
*
*                       Copyright (c) 2012 Hangzhou QianMing Technology Co.,Ltd
*
*********************************************************************************************************
*/
#ifndef __NSYS_COMM_H__
#define __NSYS_COMM_H__

/*********************************************************************
*
*       Message
*
**********************************************************************
*/

#define VER_ID                  0x0100 /* �汾id */

/* �豸��� */
#define DS_TYPES				"device"
#define DS_METAVER				2014
#define DS_IPPORT				13702
#define DS_BUFLEN				512

#define DS_SERIAL				"serial"
#define DS_MODEL				"model"
#define DS_NAME				"name"
#define DS_HARDWARE			"hardware"
#define DS_SOFTWARE			"software"
#define DS_CHANNELS			"channels"
#define DS_MAC					"mac"
#define DS_IPADDR				"ipaddr"
#define DS_CLIPORT				"cliport"
#define DS_P2PID				"p2pid"
#define DS_P2PTYPE				"p2ptype"

/* �������� */
#define OPERATE_MASK            0x000F /* �������� */
#define OPERATE_GET             0x0001 /* ��ȡ */
#define OPERATE_PUT             0x0002 /* ���� */
#define OPERATE_START           0x0004 /* ����(��) */
#define OPERATE_STOP            0x0008 /* ֹͣ(�ر�) */
#define OPERATE_RETURN          0x8000 /* ���ر�־ */

#define NSYS_CLI_SERVER			"/tmp/nsysserv"
#define NSYS_DISP_FBFD			"/tmp/nsysdisp"
#define NSYS_DATA_STREAM		"/tmp/nsysstream"

#define SEC_2_MS(x)             ( (x) * 1000 ) /* ��ת��Ϊ���� */

/* ����ͷ */
typedef struct {
	unsigned short verid;  /* �汾id */
	unsigned short cmdch;  /* ����ͨ�� */
	unsigned short cmdtag; /* �������� */
	unsigned short cmdopt; /* �������� OPERATE_GET ~ OPERATE_STOP */
	unsigned short cmdseq; /* ��ˮ�� */
	unsigned short cmdret; /* ���ش��� */
	unsigned short cbsize; /* �������ݳ��� */
	unsigned short xorsum; /* ���У��� */
} cmd_header_t;

typedef struct {
	unsigned short srcmod; /* ��ϢԴģ�� */
	unsigned short destmod; /* ��ϢĿ��ģ�� */
	void *pconn; /* ��Ӧ���û����ӣ�ΪNULL��ʾ�ڲ���ģ��ͨѶ */
} msg_header_t;

typedef struct {
	msg_header_t msghdr;
	cmd_header_t cmdhdr;
} sys_header_t;

#define CMD_ISRETURN(p)         ( (p).cmdopt & OPERATE_RETURN ) /* �Ƿ񷵻����� */
#define CMD_DOMODULE(p)         CMDTAGMODULE( (p).cmdtag ) /* �����ģ�� */
#define CMD_DOOPERATE(p)        ( (p).cmdopt & OPERATE_MASK ) /* �������� */
#define CMD_XORSUM(cmd)         ( (cmd).cmdtag ^ (cmd).cmdch ^ (cmd).cmdopt ^ (cmd).cmdseq ^ (cmd).cmdret ^ (cmd).cbsize )

/* ����ͷ��ʼ�� */
#define SET_CMDHEADER(cmd, tag, ch, opt, sz) do { \
	(cmd).verid  = VER_ID; \
	(cmd).cmdtag = tag; \
	(cmd).cmdch  = ch; \
	(cmd).cmdopt = opt; \
	(cmd).cmdseq = 0; \
	(cmd).cmdret = ERR_NO_ERROR; \
	(cmd).cbsize = sz; \
	(cmd).xorsum = CMD_XORSUM(cmd); \
} while (0)

/* ��������ͷ���� */
#define SET_CMDRET(p)           ( (p).cmdopt |= OPERATE_RETURN )
#define SET_CMDSIZE(p, cs)      ( (p).cbsize  = cs )
#define SET_CMDRETNO(p, cr)     ( (p).cmdret  = cr )
#define SET_CMDSZRET(p, cs, cr) { SET_CMDRET(p); SET_CMDSIZE(p, cs); SET_CMDRETNO(p, cr); }

/*********************************************************************
*
*       Module
*
**********************************************************************
*/

#define GENCMDTAG(m, t)         ((uint16_t) ((uint16_t)(m) | (uint8_t)(t)))
#define CMDTAGMODULE(x)			( (x) & MODULE_MASK )

#define MODULE_MASK             0xFF00 /* ģ������ */
#define MAIN_MANAGE_MODULE      0x0100 /* ��ģ�� */
#define AVC_MANAGE_MODULE       0x0200 /* avc����ģ�� */
#define ALARM_EXCEPTION_MODULE  0x0300 /* �������쳣ģ�� */
#define RECORD_MANAGE_MODULE    0x0400 /* ¼�����ģ�� */
#define PLAYBACK_MANAGE_MODULE  0x0500 /* �طŹ���ģ�� */
#define QDATA_MANAGE_MODULE     0x0600 /* ˽������Э��ģ�� */
#define VIDEO_ANALYTICS_MODULE  0x0700 /* ���ܷ���ģ�� */
#define SEARCH_BACKUP_MODULE    0x0800 /* ����������ģ�� */
#define NETWORK_SERVICE_MODULE  0x0900 /* �������ģ�� */
#define ASSIST_MANAGE_MODULE    0x0A00 /* ��������ģ�� */
#define DEV_DISCOVERY_MODULE    0x0B00 /* �豸����ģ�� */
#define P2P_MANAGE_MODULE         0x0C00 /*P2P ����ģ��*/
/* ��ģ������ */
#define USER_ACCOUNT_INFO       GENCMDTAG(MAIN_MANAGE_MODULE, 1) /* �˺���Ϣ */
#define USER_ACCOUNT_GET        GENCMDTAG(MAIN_MANAGE_MODULE, 2) /* ��ȡ�û���Ϣ */
#define USER_ACCOUNT_SET        GENCMDTAG(MAIN_MANAGE_MODULE, 3) /* �޸��û���Ϣ */
#define USER_ACCOUNT_ADD        GENCMDTAG(MAIN_MANAGE_MODULE, 4) /* �����û� */
#define USER_ACCOUNT_DEL        GENCMDTAG(MAIN_MANAGE_MODULE, 5) /* ɾ���û� */
#define ONLINE_USER_INFO        GENCMDTAG(MAIN_MANAGE_MODULE, 6) /* �����û� */
#define BREAK_ONLINE_USER       GENCMDTAG(MAIN_MANAGE_MODULE, 7) /* �Ͽ��û� */
#define NET_IP_FILTER           GENCMDTAG(MAIN_MANAGE_MODULE, 8) /* ip���ʹ��� */
#define ENUM_WORK_MODE          GENCMDTAG(MAIN_MANAGE_MODULE, 9) /* ö�ٹ���ģʽ */
#define WORK_MODE_CONFIG        GENCMDTAG(MAIN_MANAGE_MODULE, 10) /* ����ģʽ���� */
#define VGA_OUTPUT_RANGE        GENCMDTAG(MAIN_MANAGE_MODULE, 11) /* VGA������Χ */
#define HDMI_OUTPUT_RANGE       GENCMDTAG(MAIN_MANAGE_MODULE, 12) /* HDMI������Χ */
#define CVBS_OUTPUT_RANGE       GENCMDTAG(MAIN_MANAGE_MODULE, 13) /* CVBS������Χ */
#define PTZ_PROTOCOL_RANGE      GENCMDTAG(MAIN_MANAGE_MODULE, 14) /* ��̨Э�鷶Χ */
#define AUDIO_SOURCE_RANGE      GENCMDTAG(MAIN_MANAGE_MODULE, 15) /* ��ƵԴ��Χ */
#define AUDIO_ENCODE_RANGE      GENCMDTAG(MAIN_MANAGE_MODULE, 16) /* ��Ƶ���뷶Χ */
#define VIDEO_SOURCE_RANGE      GENCMDTAG(MAIN_MANAGE_MODULE, 17) /* ��ƵԴ��Χ */
#define MANAGE_HOST_CONFIG      GENCMDTAG(MAIN_MANAGE_MODULE, 18) /* ������������ */
#define MANAGE_HOST_REDIRECT    GENCMDTAG(MAIN_MANAGE_MODULE, 19) /* ���������ض��� */
#define SYS_MODULE_COMM         GENCMDTAG(MAIN_MANAGE_MODULE, 20) /* ģ����Ϣ */
#define SYS_REGISTER_EVENT      GENCMDTAG(MAIN_MANAGE_MODULE, 21) /* �¼�ע�� */
#define SYS_EVENT_NOTIFY        GENCMDTAG(MAIN_MANAGE_MODULE, 22) /* �¼�����֪ͨ */
#define SYS_USER_LOGIN          GENCMDTAG(MAIN_MANAGE_MODULE, 23) /* �û����� */
#define SYS_USER_ACCEPT         GENCMDTAG(MAIN_MANAGE_MODULE, 24) /* �û����� */
#define SYS_USER_LOGOUT         GENCMDTAG(MAIN_MANAGE_MODULE, 25) /* �û��ǳ� */
#define SYS_KEEP_ALIVE          GENCMDTAG(MAIN_MANAGE_MODULE, 26) /* ϵͳ���� */
#define SYS_WORK_STATE          GENCMDTAG(MAIN_MANAGE_MODULE, 27) /* ϵͳ����״̬ */
#define SYS_DEVICE_INFO         GENCMDTAG(MAIN_MANAGE_MODULE, 28) /* �豸��Ϣ */
#define SYS_DEVICE_LOCAL        GENCMDTAG(MAIN_MANAGE_MODULE, 29) /* �豸�������� */
#define SYS_CLONE_CONFIG        GENCMDTAG(MAIN_MANAGE_MODULE, 30) /* �������� */
#define SYS_DEFAULT_RESET       GENCMDTAG(MAIN_MANAGE_MODULE, 31) /* ϵͳ�ָ�Ĭ�� */
#define SYS_FILE_UPGRADE        GENCMDTAG(MAIN_MANAGE_MODULE, 32) /* ϵͳ���� */
#define SYS_UPGRADE_REQUEST     GENCMDTAG(MAIN_MANAGE_MODULE, 33) /* ������ȡ�ļ� */
#define SYS_LOG_SEARCH          GENCMDTAG(MAIN_MANAGE_MODULE, 34) /* ��־���� */
#define SYS_LOG_READ            GENCMDTAG(MAIN_MANAGE_MODULE, 35) /* ��־��ȡ */
#define SYS_LOG_CLEAR           GENCMDTAG(MAIN_MANAGE_MODULE, 36) /* ��־��ȡ */
#define SYS_POWER_OFF           GENCMDTAG(MAIN_MANAGE_MODULE, 37) /* ϵͳ�ػ� */
#define SYS_REBOOT              GENCMDTAG(MAIN_MANAGE_MODULE, 38) /* ϵͳ���� */
#define AUDIO_BACK_CHANNEL      GENCMDTAG(MAIN_MANAGE_MODULE, 39) /* ��Ƶ�ش� */
#define VIDEO_BACK_CHANNEL      GENCMDTAG(MAIN_MANAGE_MODULE, 40) /* ��Ƶ�ش� */
#define AVC_PROTOCOL_NAME       GENCMDTAG(MAIN_MANAGE_MODULE, 41) /* avcЭ���� */
#define AVC_PROTOCOL_SCAN       GENCMDTAG(MAIN_MANAGE_MODULE, 42) /* avcЭ��ɨ�� */
#define AVC_PROTOCOL_DEV        GENCMDTAG(MAIN_MANAGE_MODULE, 43) /* avcЭ��ɨ�� */
#define AVC_CHANNEL_CONFIG      GENCMDTAG(MAIN_MANAGE_MODULE, 44) /* ͨ������ */
#define JPEG_PICTURE_CAPTURE    GENCMDTAG(MAIN_MANAGE_MODULE, 45) /* ͨ����ͼ */
#define JPEG_PICTURE_DATA       GENCMDTAG(MAIN_MANAGE_MODULE, 46) /* ��ͼ���� */
#define VIRTUAL_KEY_CTRL        GENCMDTAG(MAIN_MANAGE_MODULE, 47) /* ���ⰴ�� */
#define SYS_WORK_STATE_EX          GENCMDTAG(MAIN_MANAGE_MODULE, 48) /* ϵͳ����״̬ */
#define JPEG_PICTURE_CAPTURE_EX  GENCMDTAG(MAIN_MANAGE_MODULE, 49) /* ��ͼ��չ*/
#define SYS_LOG_INQUERY GENCMDTAG(MAIN_MANAGE_MODULE, 50) /* ����־��ѯ*/

/* avc���� */
#define NATIVE_REAL_OPEN        GENCMDTAG(AVC_MANAGE_MODULE, 1) /* ��ʵʱ����ͨ�� */
#define NATIVE_REC_OPEN         GENCMDTAG(AVC_MANAGE_MODULE, 2) /* ��¼������ͨ�� */
#define NATIVE_REC_SEEK         GENCMDTAG(AVC_MANAGE_MODULE, 3) /* ¼��λ */
#define NATIVE_REC_RESTORE      GENCMDTAG(AVC_MANAGE_MODULE, 4) /* ��λ��ȡ������ */
#define NATIVE_DATA_CLOSE       GENCMDTAG(AVC_MANAGE_MODULE, 5) /* �ر�����ͨ�� */
#define NATIVE_AUDIO_STREAM     GENCMDTAG(AVC_MANAGE_MODULE, 6) /* ��Ƶ������ */
#define NATIVE_VIDEO_STREAM     GENCMDTAG(AVC_MANAGE_MODULE, 7) /* ��Ƶ������ */
#define DATE_TIME_MODE          GENCMDTAG(AVC_MANAGE_MODULE, 8) /* ʱ������ģʽ */
#define TIME_OSD_DISPLAY        GENCMDTAG(AVC_MANAGE_MODULE, 9) /* ʱ��OSD��ʾ */
#define NAME_OSD_CONFIG         GENCMDTAG(AVC_MANAGE_MODULE, 10) /* ͨ����OSD���� */
#define NAME_OSD_DISPLAY        GENCMDTAG(AVC_MANAGE_MODULE, 11) /* ͨ����OSD��ʾ */
#define VIDEO_MD_RANGE          GENCMDTAG(AVC_MANAGE_MODULE, 12) /* ���������Χ */
#define VIDEO_EFFECT_RANGE      GENCMDTAG(AVC_MANAGE_MODULE, 13) /* ��ƵЧ����Χ */
#define VIDEO_EFFECT_CONFIG     GENCMDTAG(AVC_MANAGE_MODULE, 14) /* ��ƵЧ������ */
#define STREAM_MAKE_KEYFRAME    GENCMDTAG(AVC_MANAGE_MODULE, 15) /* �������ؼ�֡ */
#define AUDIO_ENCODE_CONFIG     GENCMDTAG(AVC_MANAGE_MODULE, 16) /* ��Ƶ������� */
#define VIDEO_ENCODE_RANGE      GENCMDTAG(AVC_MANAGE_MODULE, 17) /* ��Ƶ���뷶Χ */
#define VIDEO_ENCODE_CONFIG     GENCMDTAG(AVC_MANAGE_MODULE, 18) /* ��Ƶ������� */
#define PRIVACY_AREA_CONFIG     GENCMDTAG(AVC_MANAGE_MODULE, 19) /* ��˽���� */
#define AVC_STREAM_INFO         GENCMDTAG(AVC_MANAGE_MODULE, 20) /* avc����Ϣ */
#define AVC_PTZ_RANGE           GENCMDTAG(AVC_MANAGE_MODULE, 21) /* ptz������Χ */
#define AVC_PTZ_CONFIG          GENCMDTAG(AVC_MANAGE_MODULE, 22) /* ptz�������� */
#define AVC_PTZ_CONTROL         GENCMDTAG(AVC_MANAGE_MODULE, 23) /* ptz���� */
#define AVC_DATETIME_CONFIG     GENCMDTAG(AVC_MANAGE_MODULE, 24) /* ʱ������ */
#define AVC_NET_CONFIG          GENCMDTAG(AVC_MANAGE_MODULE, 25) /* �������� */
#define AUDIO_SOURCE_FROM_CONFIG GENCMDTAG(AVC_MANAGE_MODULE, 26) /* ��ƵԴѡ�� */
#define VIDEO_EFFECT_RESTORE    GENCMDTAG(AVC_MANAGE_MODULE, 27) /* ��ƵЧ���ָ�Ĭ�� */
#define AVC_VIDEO_TYPE         GENCMDTAG(AVC_MANAGE_MODULE, 28) /* avc����Ϣ */


/* �������쳣���� */
#define VIDEO_MD_CONFIG         GENCMDTAG(ALARM_EXCEPTION_MODULE, 1) /* ��Ƶ�������� */
#define VIDEO_LOSS_CONFIG       GENCMDTAG(ALARM_EXCEPTION_MODULE, 2) /* ��Ƶ��ʧ���� */
#define VIDEO_COVER_CONFIG      GENCMDTAG(ALARM_EXCEPTION_MODULE, 3) /* ��Ƶ�ڵ����� */
#define ALARM_INPUT_CONFIG      GENCMDTAG(ALARM_EXCEPTION_MODULE, 4) /* ������������ */
#define ALARMIN_SCHEDULE_CONFIG GENCMDTAG(ALARM_EXCEPTION_MODULE, 5) /* ��������ƻ� */
#define ALARMOUT_SCHEDULE_CONFIG GENCMDTAG(ALARM_EXCEPTION_MODULE, 6) /* ��������ƻ� */
#define BUZZEROUT_SCHEDULE_CONFIG GENCMDTAG(ALARM_EXCEPTION_MODULE, 7) /* ��������ƻ� */
#define EMAILSEND_SCHEDULE_CONFIG GENCMDTAG(ALARM_EXCEPTION_MODULE, 8) /* ��������ƻ� */
#define ALARMIN_SCHEDULE_CTRL   GENCMDTAG(ALARM_EXCEPTION_MODULE, 9) /* ��������ƻ����� */
#define ALARMOUT_SCHEDULE_CTRL  GENCMDTAG(ALARM_EXCEPTION_MODULE, 10) /* ��������ƻ����� */
#define BUZZEROUT_SCHEDULE_CTRL GENCMDTAG(ALARM_EXCEPTION_MODULE, 11) /* ����������ƻ����� */
#define EMAILSEND_SCHEDULE_CTRL GENCMDTAG(ALARM_EXCEPTION_MODULE, 12) /* �ʼ����ͼƻ����� */
#define ALARMIN_MODE_CONFIG     GENCMDTAG(ALARM_EXCEPTION_MODULE, 13) /* ����������� */
#define ALARMOUT_MODE_CONFIG    GENCMDTAG(ALARM_EXCEPTION_MODULE, 14) /* ����������� */
#define SYS_EXCEPTION_CONFIG    GENCMDTAG(ALARM_EXCEPTION_MODULE, 15) /* ϵͳ�쳣���� */
#define ALARMIN_TRIGGER_CLEAR   GENCMDTAG(ALARM_EXCEPTION_MODULE, 16) /* �������봥����� */
#define BUZZER_BEEP_OUT         GENCMDTAG(ALARM_EXCEPTION_MODULE, 17) /* ��������� */

/* ¼����� */
#define REC_DISK_INFO           GENCMDTAG(RECORD_MANAGE_MODULE, 1) /* ¼�������Ϣ */
#define REC_DISK_FORMAT         GENCMDTAG(RECORD_MANAGE_MODULE, 2) /* ¼����̸�ʽ�� */
#define REC_DISK_MANAGE         GENCMDTAG(RECORD_MANAGE_MODULE, 3) /* ¼����̹��� */
#define CHANNEL_REC_CONFIG      GENCMDTAG(RECORD_MANAGE_MODULE, 4) /* ¼������ */
#define CHANNEL_REC_CONTROL     GENCMDTAG(RECORD_MANAGE_MODULE, 5) /* ¼����� */
#define CHANNEL_PREREC_CONTROL  GENCMDTAG(RECORD_MANAGE_MODULE, 6) /* Ԥ¼����� */
#define REC_MODE_CONFIG         GENCMDTAG(RECORD_MANAGE_MODULE, 7) /* ¼��ģʽ */
#define REC_STREAM_BITRATE      GENCMDTAG(RECORD_MANAGE_MODULE, 8) /* ¼�������� */
#define REC_SCHEDULE_CONFIG     GENCMDTAG(RECORD_MANAGE_MODULE, 9) /* ¼��ƻ����� */
#define REC_SCHEDULE_NORMAL     GENCMDTAG(RECORD_MANAGE_MODULE, 10) /* ��ͨ¼��ƻ����� */
#define REC_SCHEDULE_DETECT     GENCMDTAG(RECORD_MANAGE_MODULE, 11) /* ��Ƶ���¼��ƻ����� */
#define REC_DISK_REMOVE         GENCMDTAG(RECORD_MANAGE_MODULE, 12) /* ¼������Ƴ� */

/* �طſ��� */
#define DISPLAY_DEV_ENUM        GENCMDTAG(PLAYBACK_MANAGE_MODULE, 1) /* ö����ʾ�豸 */
#define DISPLAY_DEV_OPEN        GENCMDTAG(PLAYBACK_MANAGE_MODULE, 2) /* ����ʾ�豸 */
#define DISPLAY_DEV_CLOSE       GENCMDTAG(PLAYBACK_MANAGE_MODULE, 3) /* �ر���ʾ�豸 */
#define DISPLAY_DEV_EFFECT      GENCMDTAG(PLAYBACK_MANAGE_MODULE, 4) /* ��ʾ�豸Ч������ */
#define DISPLAY_WINDOW_CREATE   GENCMDTAG(PLAYBACK_MANAGE_MODULE, 5) /* �������� */
#define DISPLAY_WINDOW_DESTROY  GENCMDTAG(PLAYBACK_MANAGE_MODULE, 6) /* ���ٴ��� */
#define DISPLAY_WINDOW_ZOOM     GENCMDTAG(PLAYBACK_MANAGE_MODULE, 7) /* ���ӷŴ� */
#define DISPLAY_WINDOW_SHOW     GENCMDTAG(PLAYBACK_MANAGE_MODULE, 8) /* ������ʾ */
#define DISPLAY_WINDOW_SET      GENCMDTAG(PLAYBACK_MANAGE_MODULE, 9) /* ����λ������ */
#define DISPLAY_WINDOW_SWAP     GENCMDTAG(PLAYBACK_MANAGE_MODULE, 10) /* ���ڽ��� */
#define NATIVE_PREVIEW          GENCMDTAG(PLAYBACK_MANAGE_MODULE, 11) /* ����Ԥ�� */
#define NATIVE_PLAYBACK         GENCMDTAG(PLAYBACK_MANAGE_MODULE, 12) /* ���ػط� */
#define NATIVE_PLAYBACK_CONTROL GENCMDTAG(PLAYBACK_MANAGE_MODULE, 13) /* �طſ��� */
#define RESTORE_DEV_EFFECT      GENCMDTAG(PLAYBACK_MANAGE_MODULE, 14) /* �豸Ч���ָ�Ĭ�� */
#define DISPLAY_JPEG_FILE       GENCMDTAG(PLAYBACK_MANAGE_MODULE, 15) /* ��ʾjpeg�ļ� */

/* ˽������Э�� */
#define QDATA_SEND_REPORT       GENCMDTAG(QDATA_MANAGE_MODULE, 1) /* ���ͱ��� */
#define QDATA_RECV_REPORT       GENCMDTAG(QDATA_MANAGE_MODULE, 2) /* ���ձ��� */
#define QDATA_REAL_PLAY         GENCMDTAG(QDATA_MANAGE_MODULE, 3) /* ʵʱ���� */
#define QDATA_REC_PLAY          GENCMDTAG(QDATA_MANAGE_MODULE, 4) /* ¼�񲥷� */
#define QDATA_PLAY_CONTROL      GENCMDTAG(QDATA_MANAGE_MODULE, 5) /* ���ſ��� */
#define QDATA_REC_TSSYNC        GENCMDTAG(QDATA_MANAGE_MODULE, 6) /* ¼��ʱ���ͬ��ʵ��ʱ�� */
#define QDATA_REC_GET_FRAME     GENCMDTAG(QDATA_MANAGE_MODULE, 7) /* ��ȡ¼������ */
#define QDATA_VOICE_COM         GENCMDTAG(QDATA_MANAGE_MODULE, 8) /* �����Խ� */
#define QDATA_HEAVY_CONDING         GENCMDTAG(QDATA_MANAGE_MODULE, 9) /* �ر��� */


/* ¼������ͱ��� */
#define REC_INFO_SEARCH         GENCMDTAG(SEARCH_BACKUP_MODULE, 1) /* ¼����Ϣ���� */
#define REC_INFO_READ           GENCMDTAG(SEARCH_BACKUP_MODULE, 2) /* ¼����Ϣ��ȡ*/
#define REC_BACKUP_DEV          GENCMDTAG(SEARCH_BACKUP_MODULE, 3) /* �����豸 */
#define REC_BACKUP_INFO         GENCMDTAG(SEARCH_BACKUP_MODULE, 4) /* ¼�񱸷���Ϣ */
#define REC_BACKUP_START        GENCMDTAG(SEARCH_BACKUP_MODULE, 5) /* ¼�񱸷����� */
#define REC_BACKUP_PROGRESS     GENCMDTAG(SEARCH_BACKUP_MODULE, 6) /* ¼�񱸷ݽ��� */
#define REC_BACKUP_CANCEL       GENCMDTAG(SEARCH_BACKUP_MODULE, 7) /* ¼�񱸷�ȡ�� */
#define REC_STREAM_OPEN         GENCMDTAG(SEARCH_BACKUP_MODULE, 8) /* ��¼�� */
#define REC_STREAM_SEEK         GENCMDTAG(SEARCH_BACKUP_MODULE, 9) /* ¼��λ */
#define REC_MONTH_INFO          GENCMDTAG(SEARCH_BACKUP_MODULE, 10) /* ¼������Ϣ */

#define REC_DISK_FORMAT_EX   GENCMDTAG(RECORD_MANAGE_MODULE, 13) /* ¼����̸�ʽ����չ*/
#define REC_DISK_FORMAT_PARTTION GENCMDTAG(RECORD_MANAGE_MODULE, 14) /* ¼����̷�����ʽ��*/
#define REC_DISK_PARTTION_INFO GENCMDTAG(RECORD_MANAGE_MODULE, 15) /* ¼����̷�����Ϣ��ȡ*/

/* ����������*/
#define NET_GLOBAL_CONFIG       GENCMDTAG(NETWORK_SERVICE_MODULE, 1) /* ��ȡ����ȫ������ */
#define NET_ETHERNET_CONFIG     GENCMDTAG(NETWORK_SERVICE_MODULE, 2) /* ��̫������ */
#define NET_3G_CONFIG           GENCMDTAG(NETWORK_SERVICE_MODULE, 3) /* 3G���� */
#define NET_WIFI_CONFIG         GENCMDTAG(NETWORK_SERVICE_MODULE, 4) /* WIFI���� */
#define NET_WIFI_CARD           GENCMDTAG(NETWORK_SERVICE_MODULE, 5) /* WIFI���� */
#define NET_WIFI_AP             GENCMDTAG(NETWORK_SERVICE_MODULE, 6) /* WIFI���� */
#define NET_NTP_CONFIG          GENCMDTAG(NETWORK_SERVICE_MODULE, 7) /* NTP���� */
#define NET_P2P_CONFIG          GENCMDTAG(NETWORK_SERVICE_MODULE, 8) /* P2P���� */
#define NET_FTP_CONFIG          GENCMDTAG(NETWORK_SERVICE_MODULE, 9) /* FTP���� */
#define NET_RTP_CONFIG          GENCMDTAG(NETWORK_SERVICE_MODULE, 10) /* RTP���� */
#define NET_DHCP_CONFIG         GENCMDTAG(NETWORK_SERVICE_MODULE, 11) /* DHCP���� */
#define NET_UPNP_CONFIG         GENCMDTAG(NETWORK_SERVICE_MODULE, 12) /* UPNP���� */
#define NET_PPPOE_CONFIG        GENCMDTAG(NETWORK_SERVICE_MODULE, 13) /* PPPOE���� */
#define NET_DDNS_CONFIG         GENCMDTAG(NETWORK_SERVICE_MODULE, 14) /* DDNS���� */
#define NET_DDNS_SERVICE        GENCMDTAG(NETWORK_SERVICE_MODULE, 15) /* DDNS������ */
#define NET_EMAIL_CONFIG        GENCMDTAG(NETWORK_SERVICE_MODULE, 16) /* EMAIL���� */
#define NET_STATUS_GET          GENCMDTAG(NETWORK_SERVICE_MODULE, 17) /* ��ȡ����״̬ */

/* �������� */
#define SYS_DEVICE_TIME         GENCMDTAG(ASSIST_MANAGE_MODULE, 1) /* �豸ʱ�� */
#define DST_SCHEDULE_CONFIG     GENCMDTAG(ASSIST_MANAGE_MODULE, 2) /* ����ʱ���� */


#define P2P_SERVE_CONFIG          GENCMDTAG(P2P_MANAGE_MODULE, 1) /* P2P���� */
#define P2P_EXTRA_CONFIG        GENCMDTAG(P2P_MANAGE_MODULE, 2) /* P2P��չ���� */

/*********************************************************************
*
*       Struct
*
**********************************************************************
*/

enum {
	MODULE_CONNECT, /* ģ������ */
	CLIENT_CONNECT, /* �ͻ����� */
	MODULE_DISCONNECT, /* ģ��Ͽ� */
	CLIENT_DISCONNECT, /* �ͻ��Ͽ� */
	MODULE_READY, /* ģ����� */
	SYSTEM_READY /* ϵͳ���� */
};

typedef struct {
	int msg; /* ģ����Ϣ */
	union {
		int data; /* ��Ϣ���� */
		void *pdata; /* ��Ϣָ�� */
	};
} comm_module_msg_t;

enum {
	AVC_DISCONNECT_ACK, /* avc�Ͽ���Ӧ */
	AVC_STREAM_CLEAR, /* avc��ȫ���ر� */
};

typedef struct {
	int eventcode; /* �¼����� */
	int eventch; /* �¼�ͨ�� */
} internal_state_t;

/* ϵͳ�¼� */
typedef struct {
	int eventtype; /* �¼����� */
	union {
		int eventstate; /* ͨ���¼�״̬ */
		internal_state_t internalstate; /* �ڲ��¼� */
		channel_state_t chstate; /* ͨ��״̬ */
		stream_bitrate_t streambitrate; /* ������ */
		network_state_t netstate; /* ����״̬ */
		disk_state_t diskstate; /* ����״̬ */
		progress_state_t progstate; /* ����״̬ */
		playback_state_t playstate; /* ����״̬ */
		config_state_t configstate; /* ����״̬ */
		sys_exception_t sysexcption; /* �쳣״̬ */
		video_state_t type;/*��Ƶ��������*/
	};
} comm_sys_event_t;


#define MAX_NET_CARDS		4
#define MAC_ADDR_LEN		6

/* �û���¼ */
typedef struct {
	int libver; /* �汾�� */
	char username[CLI_USER_LEN]; /* �û��� */
	char password[CLI_USER_LEN]; /* ���� */
	unsigned char macaddr[MAX_NET_CARDS][MAC_ADDR_LEN]; /* �û�MAC��ַ */
} comm_user_login_t;

/* �û����� */
typedef struct {
	int libver; /* �汾�� */
	unsigned short tcpport; /* TCP���ݶ˿� */
	unsigned char res[2]; /* ���� */
} comm_user_accept_t;

/* �û���Ϣ */
typedef struct {
	char username[CLI_USER_LEN]; /* �û��� */
	char password[CLI_USER_LEN]; /* ���� */
	unsigned int userright; /* ����Ȩ�� */
	unsigned int ptzchlow; /* ��̨���Ƶ�ͨ�� */
	unsigned int ptzchhigh; /* ��̨���Ƹ�ͨ�� */
	unsigned int previewchlow; /* Ԥ����ͨ�� */
	unsigned int previewchhigh; /* Ԥ����ͨ�� */
	unsigned int playbackchlow; /* �طŵ�ͨ�� */
	unsigned int playbackchhigh; /* �طŸ�ͨ�� */
	unsigned int remotechlow; /* Զ�̵�ͨ�� */
	unsigned int remotechhigh; /* Զ�̸�ͨ�� */
	char ipaddr[CLI_ADDR_LEN]; /* ip��ַ����ʾ���û�ֻ�����ض���ַ��0�����ַ */
	unsigned char macaddr[6]; /* mac��ַ����ʾ���û�ֻ�����ض���ַ��0�����ַ */
	char res[18]; /* ���� */
} comm_user_info_t;

/* ʱ�� */
typedef struct {
	unsigned char hour; /* ʱ */
	unsigned char minute; /* �� */
	unsigned char second; /* �� */
	unsigned char res; /* ���� */
} comm_time_t;

/* ���� */
typedef struct {
	unsigned short year; /* �� */
	unsigned char month; /* �� */
	unsigned char day; /* �� */
} comm_date_t;

/* ʱ�� */
typedef struct {
	comm_date_t momdate; /* ���� */
	comm_time_t momtime; /* ʱ�� */
} comm_moment_t;

/* ʱ��� */
typedef struct {
	comm_moment_t beginning; /* ��ʼʱ�� */
	comm_moment_t ending; /* ����ʱ�� */
} comm_duration_t;

typedef struct {
	int ch; /* ͨ�� */
	int win; /* ���� */
	int type; /* ���� */
	comm_duration_t playdur; /* ��ֹʱ�� */
} comm_playback_t;

typedef struct {
	unsigned short type; /* ���� ¼������ REC_TYPE_NORMAL ~ REC_TYPE_VIDEODETECT������Ϊ0 */
	unsigned short wday; /* ���� 0 ~ 6�������� ~ �������� */
	comm_time_t beginning; /* ��ʼʱ�� */
	comm_time_t ending; /* ����ʱ�� */
} comm_schedule_config_t;

typedef struct {
	int ch; /* ¼��ͨ�� */
	int type; /* ¼������ */
	comm_duration_t dur; /* ��ֹʱ�� */
} comm_rec_duration_t;

typedef struct {
	unsigned int samplenum; /* ��֡�� */
	unsigned int samplelen; /* �ܳ��� */
	comm_rec_duration_t recdur; /* ¼��� */
} comm_rec_info_t;

typedef struct {
	char logtype; /* ��־���� */
	char logopt; /* ��־���� */
	char logch; /* ��־ͨ�� */
	char res; /* ����Ϊ0 */
	int logcmd; /* ��־���� */
	comm_moment_t logmom; /* ��¼ʱ�� */
	char logtext[CLI_LOG_LEN]; /* ��־���� */
} comm_log_info_t;

#define UPGRADE_NAME_LEN	64

typedef struct {
	unsigned short connid; /* ��������ID */
	unsigned short dataid; /* ���ݴ���ID */
} comm_link_id_t;

typedef struct {
	comm_link_id_t linkid; /* ����ID */
	union {
		int streamindex; /* ����Ƶ�������� */
		struct {
			comm_duration_t recdur; /* ¼��ط�ʱ��� */
			int rectype; /* ¼������ */
			char sendrequest; /* ���ݷ������� 0 �����󣨷�������ֱ�������� 1 ���� */
		} recch;
		struct {
			audio_source_t src;
			audio_encode_t enc;
		} audioch; /* ��Ƶ�ش����� */
		struct {
			int win;
			video_encode_t enc;
		} videoch; /* ��Ƶ�ش����� */
		struct {
			unsigned short tcpport; /* TCP���ݶ˿� */
			unsigned short udpport; /* UDP���ݶ˿� */
			unsigned short httpport; /* HTTP�˿� */
			unsigned short rtspport; /* RTSP�˿� */
		} portin; /* �˿���Ϣ */
	};
} comm_link_info_t;

typedef struct {
	comm_link_id_t linkid; /* ����ID */
	comm_duration_t recdur; /* ¼��ط�ʱ��� */
	int rectype; /* ¼������ */
	video_encode_t enc;/*�ر�����Ҫָ���Ĳ���
						���������в���ֵΪ0�����п�͸߱���ָ��*/
	char res[36];/*Ԥ��*/
}comm_heavy_conding_t;


/* ���ſ��� */
typedef struct {
	union {
		int win; /* ���ںţ����أ� */
		comm_link_id_t id; /* ����id��Զ�̣� */
	};
	int param; /* ������� */
	comm_moment_t playmom; /* ����ʱ�� */
} comm_play_control_t;

/* ¼��ʱ���ͬ�� */
typedef struct {
	unsigned int ts; /* ����ʱ��� */
	comm_moment_t mom; /* ��Ӧʱ�� */
} comm_ts_time_t;

/* Ԫ��������,����ֵ���ܳ���15 */
#define DATA_TYPE_NULL			0 /* ���������� */
#define DATA_CONN_AUTH			1 /* ����������֤ */
#define DATA_SEND_REPORT		2 /* ���ݷ��ͱ��� */
#define DATA_RECV_REPORT		3 /* ���ݽ��ձ��� */
#define DATA_UPGRADE_FILE		4 /* ���������ļ� */

enum {
	RECV_STATE_ACTIVE      = LIB_BIT00, /* �״̬ */
	RECV_STATE_INIT_BUFFER = LIB_BIT01, /* �����ʼ�� */
	RECV_STATE_INIT_REPORT = LIB_BIT02, /* ͳ�Ʊ����ʼ�� */
	RECV_STATE_LIST_FULL   = LIB_BIT03, /* ���������� */
	RECV_STATE_DATA_HEADER = LIB_BIT08, /* ��������ͷ */
	RECV_STATE_EXT_HEADER  = LIB_BIT09, /* ������չͷ */
	RECV_STATE_EXT_DATA    = LIB_BIT10, /* ������չ���� */
	RECV_STATE_DATA_DATA   = LIB_BIT11  /* ���ո������� */
};

typedef struct {
	unsigned char vf:2; /* �汾��� */
	unsigned char cf:1; /* У���� */
	unsigned char mf:1; /* ֡�߽��� */
	unsigned char xf:1; /* ��չ��� */
	unsigned char tf:1; /* ������Ʊ�� */
	unsigned char wf:1; /* ��Ƶ��Ƚ�λ��ǣ���ʾ��Ȳ�С��4096 */
	unsigned char hf:1; /* ��Ƶ�߶Ƚ�λ��ǣ���ʾ�߶Ȳ�С��2048 */
	unsigned char dt; /* �������ͣ���ǰ������ */
	union {
		unsigned char any0; /* ���ݶ��� */
		struct {
			unsigned char fm:1; /* ��Ƶ���� */
			unsigned char fs:1; /* ����ʽ */
			unsigned char fps:6; /* ��Ƶ֡�� */
		} vdo;
		struct {
			unsigned char chs:2; /* ������ */
			unsigned char KBps:6; /* ��Ƶ����ƽ������(KBytesÿ��) */
		} ado;
	};
	unsigned char eb; /* ����ĩβ�ֽ� */
	unsigned short sn; /* �����к� */
	unsigned short sz; /* ���ݰ���С */
	unsigned short id; /* ������id */
	union {
		unsigned short any1; /* �û����� */
		unsigned short hz; /* ��Ƶ������ */
		struct {
			unsigned char w; /* ��Ƶ���(��16����Ϊ��λ����) */
			unsigned char h; /* ��Ƶ�߶�(��8����Ϊ��λ����) */
		} pic;
	};
	unsigned int ts; /* ����ʱ��� */
} comm_data_header_t;

#define INIT_DATAHEADER(hdr) do { \
	memset(&hdr, 0, sizeof(comm_data_header_t)); \
	(hdr).vf = 1; \
} while (0)

#define SET_DATAHEADER(hdr, type, size)	do { \
	INIT_DATAHEADER(hdr); \
	(hdr).dt = type; \
	(hdr).sz = size; \
} while (0)

#define GET_PICWIDTH(hdr) ( ((hdr).wf == 0) ? (hdr).pic.w * 16 : (hdr).pic.w * 16 + 4096 )
#define GET_PICHEIGHT(hdr) ( ((hdr).hf == 0) ? (hdr).pic.h * 8 : (hdr).pic.h * 8 + 2048 )

#define SET_DATAENDBYTE(hdr, x) { (hdr).cf = 1; (hdr).eb = x; }
#define SET_TRANSFEREND(hdr) { (hdr).tf = 1; }

typedef struct {
	unsigned short xt; /* ��չͷ���� */
	unsigned short sz; /* ��չͷ���� */
} comm_extension_header_t;

typedef struct {
	int bps; /* ��������ƽ������ */
	int jit; /* �����������ݶ��� */
	unsigned short recvpkt; /* �������ڽ��հ��� */
	unsigned short losspkt; /* �������ڶ�ʧ���� */
	unsigned int lastts; /* ������������ʱ��� */
} comm_recv_report_t;

#endif /* #ifndef __NSYS_COMM_H__ */
