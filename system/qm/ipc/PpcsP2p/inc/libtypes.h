
#ifndef __LIBTYPES_H__
#define __LIBTYPES_H__

/***************************************************/
/* ��������                                        */
/***************************************************/

/* ����ֵ */
#define LIB_OK	0
#define LIB_ERR	(-1)

/* λ���� */
#define LIB_BIT00 (1 << 0)
#define LIB_BIT01 (1 << 1)
#define LIB_BIT02 (1 << 2)
#define LIB_BIT03 (1 << 3)
#define LIB_BIT04 (1 << 4)
#define LIB_BIT05 (1 << 5)
#define LIB_BIT06 (1 << 6)
#define LIB_BIT07 (1 << 7)
#define LIB_BIT08 (1 << 8)
#define LIB_BIT09 (1 << 9)
#define LIB_BIT10 (1 << 10)
#define LIB_BIT11 (1 << 11)
#define LIB_BIT12 (1 << 12)
#define LIB_BIT13 (1 << 13)
#define LIB_BIT14 (1 << 14)
#define LIB_BIT15 (1 << 15)
#define LIB_BIT16 (1 << 16)
#define LIB_BIT17 (1 << 17)
#define LIB_BIT18 (1 << 18)
#define LIB_BIT19 (1 << 19)
#define LIB_BIT20 (1 << 20)
#define LIB_BIT21 (1 << 21)
#define LIB_BIT22 (1 << 22)
#define LIB_BIT23 (1 << 23)
#define LIB_BIT24 (1 << 24)
#define LIB_BIT25 (1 << 25)
#define LIB_BIT26 (1 << 26)
#define LIB_BIT27 (1 << 27)
#define LIB_BIT28 (1 << 28)
#define LIB_BIT29 (1 << 29)
#define LIB_BIT30 (1 << 30)
#define LIB_BIT31 (1 << 31)

/***************************************************/
/* ���Ͷ���                                        */
/***************************************************/

/* �ߴ� */
typedef struct {
	int width; /* ��� */
	int height; /* �߶� */
} lib_size_t;

/* ���� */
typedef struct {
	int left; /* ˮƽ��ʼλ�� */
	int top; /* ��ֱ��ʼλ�� */
	int width; /* ��� */
	int height; /* �߶� */
} lib_rect_t;

/* ʱ�� */
typedef struct {
	int hour; /* ʱ */
	int minute; /* �� */
	int second; /* �� */
} lib_time_t;

/* ���� */
typedef struct {
	int year; /* �� */
	int month; /* �� */
	int day; /* �� */
} lib_date_t;

/* ʱ�� */
typedef struct {
	lib_date_t momdate; /* ���� */
	lib_time_t momtime; /* ʱ�� */
} lib_moment_t;

/* ʱ��� */
typedef struct {
	lib_moment_t beginning; /* ��ʼʱ�� */
	lib_moment_t ending; /* ����ʱ�� */
} lib_duration_t;

typedef enum {
	DISP_DEV_NULL   = 0, /* �� */
	DISP_DEV_SPOT   = LIB_BIT00, /* SPOT�豸 */
	DISP_DEV_BT656  = LIB_BIT01, /* BT656��� */
	DISP_DEV_BT1120 = LIB_BIT02, /* BT1120��� */
	DISP_DEV_VGA0   = LIB_BIT03, /* VGA0�豸 */
	DISP_DEV_HDMI0  = LIB_BIT04, /* HDMI0�豸 */
	DISP_DEV_CVBS0  = LIB_BIT05, /* CVBS0�豸 */
	DISP_DEV_VGA1   = LIB_BIT06, /* VGA2�豸 */
	DISP_DEV_HDMI1  = LIB_BIT07, /* HDMI2�豸 */
	DISP_DEV_CVBS1  = LIB_BIT08, /* CVBS2�豸 */
	DISP_DEV_VGA2   = LIB_BIT09, /* VGA2�豸 */
	DISP_DEV_HDMI2  = LIB_BIT10, /* HDMI2�豸 */
	DISP_DEV_CVBS2  = LIB_BIT11  /* CVBS2�豸 */
} disp_dev_e;

typedef enum {
	DISP_RESO_NULL         = 0, /* �� */
	DISP_RESO_720_480I60   = LIB_BIT00, /* �ֱ���720x480��ˢ��Ƶ��I60��ʾ��Ƶ60Hz����ͬ */
	DISP_RESO_720_480P60   = LIB_BIT01, /* �ֱ���720x480��ˢ��Ƶ��P60��ʾ֡Ƶ60Hz����ͬ */
	DISP_RESO_720_576I50   = LIB_BIT02,
	DISP_RESO_720_576P50   = LIB_BIT03,
	DISP_RESO_800_600P60   = LIB_BIT04,
	DISP_RESO_1024_768P60  = LIB_BIT05,
	DISP_RESO_1280_720P50  = LIB_BIT06,
	DISP_RESO_1280_720P60  = LIB_BIT07,
	DISP_RESO_1280_800P60  = LIB_BIT08,
	DISP_RESO_1280_1024P60 = LIB_BIT09,
	DISP_RESO_1366_768P60  = LIB_BIT10,
	DISP_RESO_1440_900P60  = LIB_BIT11,
	DISP_RESO_1920_1080P24 = LIB_BIT12,
	DISP_RESO_1920_1080P25 = LIB_BIT13,
	DISP_RESO_1920_1080P30 = LIB_BIT14,
	DISP_RESO_1920_1080I50 = LIB_BIT15,
	DISP_RESO_1920_1080P50 = LIB_BIT16,
	DISP_RESO_1920_1080I60 = LIB_BIT17,
	DISP_RESO_1920_1080P60 = LIB_BIT18
} disp_resolution_e;

typedef struct {
	int dispdev; /* ��ʾ�豸��disp_dev_e���� */
	int dispreso; /* ��ʾ�ֱ��ʣ�disp_resolution_e���ͣ�ö���豸ʱΪλ���� */
} display_dev_t;

typedef struct {
	int brightness; /* ���� */
	int contrast; /* �Աȶ� */
	int saturation; /* ���Ͷ� */
	int hue; /* ɫ�� */
	int sharpness; /* ������ */
	int denoise;  /* ȥ��ǿ�� */
	int enhance; /* ��ǿ */
} effect_value_t;

typedef enum {
	VIDEO_PROFILE_H264_BP    = LIB_BIT00, /* h.264 base line */
	VIDEO_PROFILE_H264_MP    = LIB_BIT01, /* h.264 main profile */
	VIDEO_PROFILE_H264_HP    = LIB_BIT02, /* h.264 high profile */
	VIDEO_PROFILE_MPEG4_SP   = LIB_BIT03, /* mpeg4 simple profile */
	VIDEO_PROFILE_MPEG4_ASP  = LIB_BIT04, /* mpeg4 advance simple profile */
	VIDEO_PROFILE_MJPEG      = LIB_BIT05, /* motion jpeg */
	VIDEO_PROFILE_JPEG       = LIB_BIT06, /* jpeg */
	VIDEO_PROFILE_RAW_YUV420 = LIB_BIT07, /* yuv 420 */
	VIDEO_PROFILE_RAW_YUV422 = LIB_BIT08  /* yuv 422 */
} venc_type_e, vdec_type_e;

enum {
	ENCODE_MODE_CBR, /* �̶����� */
	ENCODE_MODE_VBR /* �ɱ����� */
};

typedef enum {
	VIDEO_INPUT_NULL            = 1,  /* �� */
		
	VIDEO_INPUT_AHD_1080P_PAL   = 2,  /* AHD ������Ƶ�������� */
	VIDEO_INPUT_AHD_1080P_NTSC  = 3,
	VIDEO_INPUT_AHD_720P_PAL    = 4,
	VIDEO_INPUT_AHD_720P_NTSC   = 5,
	VIDEO_INPUT_AHD_1080H_PAL   = 6,
	VIDEO_INPUT_AHD_1080H_NTSC  = 7,	
	
	VIDEO_INPUT_SDI_1080P_PAL   = 8,  /* SDI ������Ƶ�������� */
	VIDEO_INPUT_SDI_1080P_NTSC  = 9,
	VIDEO_INPUT_SDI_720P_PAL    = 10,	
	VIDEO_INPUT_SDI_720P_NTSC   = 11,
	VIDEO_INPUT_SDI_1080H_PAL   = 12,
	VIDEO_INPUT_SDI_1080H_NTSC  = 13,	
	
	VIDEO_INPUT_CVI_1080P_PAL   = 14,  /* CVI ������Ƶ�������� */
	VIDEO_INPUT_CVI_1080P_NTSC  = 15,
	VIDEO_INPUT_CVI_720P_PAL    = 16,
	VIDEO_INPUT_CVI_720P_NTSC   = 17,
	VIDEO_INPUT_CVI_1080H_PAL   = 18,
	VIDEO_INPUT_CVI_1080H_NTSC  = 19,	
	
	VIDEO_INPUT_CVBS            = 20,  /* ��ͨ960H\D1������Ƶ�������� */	
	VIDEO_INPUT_CVBS_PAL        = 21,
	VIDEO_INPUT_CVBS_NTSC       = 22,

    VIDEO_INPUT_TVI_1080P_NTSC  = 23,  /* TVI ������Ƶ�������� */
    VIDEO_INPUT_TVI_1080P_PAL   = 24,
    VIDEO_INPUT_TVI_720P_NTSC   = 25,
    VIDEO_INPUT_TVI_720P_PAL   = 26,
    
	VIDEO_INPUT_IPC_720P             = 27,  /* IPC 720P ��Ƶ�������� */	
	VIDEO_INPUT_IPC_1080P             = 28,  /* IPC 1080P ��Ƶ�������� */	
} video_input_e;

typedef struct {
	int encformat; /* �����ʽ */
	int framerate; /* ֡�� */
	int bitrate; /* ���� */
	int gop; /* �ؼ�֡��� */
	int quality; /* ��������,VBR��Ч */
	int encmode; /* ����ģʽ ENCODE_MODE_CBR��ENCODE_MODE_VBR */
	lib_size_t picsz; /* ͼ��ߴ� */
} video_encode_t;

typedef enum {
	AUDIO_PROFILE_PCM        = LIB_BIT00,
	AUDIO_PROFILE_G711A      = LIB_BIT01,
	AUDIO_PROFILE_G711U      = LIB_BIT02,
	AUDIO_PROFILE_IMA_ADPCM  = LIB_BIT03, /* sampleΪ���� */
	AUDIO_PROFILE_DVI4_ADPCM = LIB_BIT04, /* sampleΪż�� */
	AUDIO_PROFILE_G726_ADPCM = LIB_BIT05,
	AUDIO_PROFILE_AMR        = LIB_BIT06,
	AUDIO_PROFILE_VORBIS     = LIB_BIT07,
	AUDIO_PROFILE_AAC        = LIB_BIT08,
	AUDIO_PROFILE_HEAAC      = LIB_BIT09,
	AUDIO_PROFILE_MP3        = LIB_BIT10
} aenc_type_e, adec_type_e;

typedef struct {
	int samplerate; /* ��ƵԴ����Ƶ�� */
	int samplebits; /* ��ƵԴ�������� */
	int audiochs; /* ��ƵԴͨ���� */
} asrc_param_t, audio_source_t;

enum {
	AUDIO_FROM_CAMERA = LIB_BIT00, /* ��Ƶ���������ȡ */
	AUDIO_FROM_BOARD  = LIB_BIT01 /* ��Ƶ�Ӱ��������ȡ */
};

typedef struct {
	int profile; /* ��Ƶ�����㷨�����ͼ�aenc_type_e���� */
	int encbitrate; /* ��Ƶ�������� */
} aenc_param_t, audio_encode_t;

enum {
	PIC_QUALITY_HIGH, /* ������ */
	PIC_QUALITY_NORMAL, /* һ������ */
	PIC_QUALITY_LOW /* ������ */
};

typedef struct {
	int picquality; /* ͼƬ���� PIC_QUALITY_HIGH�� */
	lib_size_t picsz; /* ͼƬ�ߴ� */
} pic_param_t;

enum {
	LINK_MODE_AUTO, /* �Զ� */
	LINK_MODE_UDP, /* udp����ģʽ */
	LINK_MODE_TCP /* tcp����ģʽ */
};

#define DEV_PROTOCOL_LEN	16
#define DEV_SN_LEN			48
#define DEV_NAME_LEN		32
#define DEV_VER_LEN			16
#define DEV_ADDR_LEN		64
#define DEV_MAC_LEN			6
#define DEV_MANU_PREFIX		8
#define DEV_P2P_ID			20

typedef struct {
	char protocol[DEV_PROTOCOL_LEN]; /* �豸Э����������cli_dev_scanΪ�豸�ͺţ� */
	char sn[DEV_SN_LEN]; /* �豸��� */
	char name[DEV_NAME_LEN]; /* �豸�� */
	char softwarever[DEV_VER_LEN]; /* ����ͺ� */
	char hardwarever[DEV_VER_LEN]; /* Ӳ���ͺ� */
	char ipaddr[DEV_ADDR_LEN]; /* ip������ */
	unsigned short ipport; /* ���Ӷ˿ں� */
	unsigned short httpport; /* http�˿ںţ�0��ʾ�޸���Ϣ */
	unsigned short chnum; /* ͨ������0��ʾ��ͨ����Ϣ */
	unsigned char mac[DEV_MAC_LEN]; /* �����ַ,0��ʾ�޸���Ϣ */
	char manuprefix[DEV_MANU_PREFIX]; /* p2p����ǰ׺ */
	char p2pid[DEV_P2P_ID]; /* p2p id */
	unsigned char p2ptype; /* p2p���� */
	char res[3]; /* ���� */
} dev_param_t;

/* ϵͳģʽ */
typedef struct {
	unsigned char analogcif; /* ģ��cifͨ������Ϊ0��ʾ�ޣ���ͬ */
	unsigned char digitalcif; /* ����cifͨ���� */
	unsigned char analoghd1; /* ģ��half d1ͨ���� */
	unsigned char digitalhd1; /* ����half d1ͨ���� */
	unsigned char analogd1; /* ģ��d1ͨ���� */
	unsigned char digitald1; /* ����d1ͨ���� */
	unsigned char analog960h; /* ģ��960hͨ���� */
	unsigned char digital960h; /* ����960hͨ���� */
	unsigned char analog720p; /* ģ��720pͨ���� */
	unsigned char digital720p; /* ����720pͨ���� */
	unsigned char analog960p; /* ģ��960pͨ���� */
	unsigned char digital960p; /* ����960pͨ���� */
	unsigned char analog1080p; /* ģ��1080pͨ���� */
	unsigned char digital1080p; /* ����1080pͨ���� */
	unsigned char previewwinnum; /* ���Ԥ�������� */
	unsigned char playbackwinnum; /* ���طŴ����� */
	unsigned char previewdigitalmainstreamnum; /* Ԥ����������������ͬʱ���ܴ���������������Ԥ���� */
	unsigned char previewalldigitalmainstreamnum; /* Ԥ������ȫ������������ʾ��Ԥ����������������ȫ�����ز�����ʱ��Ԥ�������������� */
	unsigned char previewmainstreamhiddenfreeze; /* Ԥ������������ʱ��������ͨ����0 ������ 1 �Զ����� */
	unsigned char suggeststreammanagememsz; /* ��������������ʹ�õ��ڴ��С��Ϊ0Ĭ��ʹ��64MB */
	unsigned char externallivestreamnum; /* �ⲿ����ʵʱ������ */
	unsigned char externalrecordstreamnum; /* �ⲿ����¼�������� */
	char analogmodename[24]; /* ģ��ͨ��ģʽ��ʾ������0��β���ַ��������մ���ʾ����ԭ������ʾ */
	char digitalmodename[24]; /* ����ͨ��ģʽ��ʾ������0��β���ַ��������մ���ʾ����ԭ������ʾ */
	unsigned char analog1080h; /* ģ��1080hͨ���� */
	unsigned char digital1080h; /* ����1080hͨ���� */
	char res[28];
} cli_work_mode_t;

enum {
	STANDARD_AUTO, /* �Զ�ʶ�� */
	STANDARD_PAL, /* pal�� */
	STANDARD_NTSC /* ntsc�� */
};

enum {
	DATE_MMDDYY, /* ��/��/�� */
	DATE_DDMMYY, /* ��/��/�� */
	DATE_YYMMDD /* ��/��/�� */
};

enum {
	TIME_HOUR12, /* 12Сʱ�� */
	TIME_HOUR24 /* 24Сʱ�� */
};

typedef struct {
	unsigned char datemode; /* ���ڸ�ʽ DATE_MMDDYY ~ DATE_YYMMDD */
	unsigned char timemode; /* ʱ���ʽ TIME_HOUR12 ~ TIME_HOUR24 */
	char res[2];
} date_time_mode_t;

#define OSD_NAME_SZ 32
#define OSD_DATA_SZ 1024

/* ����OSD���ã���ɸ�����Ҫѡȡ�ַ��������ʽ��Windowsϵͳֻ�õ�osdname��Ա */
typedef struct {
	char osdname[OSD_NAME_SZ]; /* utf8�ַ��� */
	lib_size_t sz; /* ����ߴ� */
	unsigned short linebytes; /* ÿ�е��ֽ��� */
	unsigned char pixelbits; /* ÿ�����λ�� */
	unsigned char osdisempty; /* ������Ϊ1��ʾ��ǰ�Ĳ���δ���ã�д�������ԣ� */
	unsigned char osddata[OSD_DATA_SZ]; /* �������ݣ�������ʾģʽ���� */
} venc_osd_t;

enum {
	BAUD_RATE_1200   = LIB_BIT00, /* ������ */
	BAUD_RATE_2400   = LIB_BIT01, /* ������ */
	BAUD_RATE_4800   = LIB_BIT02, /* ������ */
	BAUD_RATE_9600   = LIB_BIT03, /* ������ */
	BAUD_RATE_14400  = LIB_BIT04, /* ������ */
	BAUD_RATE_19200  = LIB_BIT05, /* ������ */
	BAUD_RATE_38400  = LIB_BIT06, /* ������ */
	BAUD_RATE_57600  = LIB_BIT07, /* ������ */
	BAUD_RATE_115200 = LIB_BIT08 /* ������ */
};

enum {
	DATA_BIT_4 = LIB_BIT00, /* ����λ�� */
	DATA_BIT_5 = LIB_BIT01, /* ����λ�� */
	DATA_BIT_6 = LIB_BIT02, /* ����λ�� */
	DATA_BIT_7 = LIB_BIT03, /* ����λ�� */
	DATA_BIT_8 = LIB_BIT04 /* ����λ�� */
};

enum {
	DATA_CHECK_NULL  = LIB_BIT00, /* ��У�� */
	DATA_CHECK_ODD   = LIB_BIT01, /* ��У�� */
	DATA_CHECK_EVEN  = LIB_BIT02, /* żУ�� */
	DATA_CHECK_FLAG  = LIB_BIT03, /* ��־,ʼ��Ϊ1 */
	DATA_CHECK_SPACE = LIB_BIT04 /* �ո�,ʼ��Ϊ0 */
};

enum {
	FLOW_CTRL_NONE = LIB_BIT00, /* �� */
	FLOW_CTRL_SW   = LIB_BIT01, /* �����Xon/Xoff */
	FLOW_CTRL_HW   = LIB_BIT02 /* Ӳ�� */
};

typedef struct {
	int baudrate; /* ������(λ����)��BAUD_RATE_1200�� */
	int databits; /* ����λ(λ����)��DATA_BIT_4�� */
	int datacheck; /* ����У��(λ����)��DATA_CHECK_NULL�� */
	int flowctrl; /* ��������(λ����)��FLOW_CTRL_NONE�� */
} uart_param_t;

#define PTZ_PROTOCOL_LEN 16

typedef struct {
	char protocol[PTZ_PROTOCOL_LEN]; /* ��̨Э���� */
	int ptzaddr; /* ��̨��ַ */
	uart_param_t uartpara; /* ���ڲ��� */
} ptz_param_t;

typedef struct {
	int autodst; /* ��ǰʱ������ʱ�Զ����� */
	int tzbias; /* ��ǰʱ����UTCʱ���(����) */
	lib_moment_t utctime; /* UTCʱ�� */
} avc_time_t;

typedef struct {
	char dhcpenable; /* �Ƿ�����dhcp */
	char isipv6; /* �Ƿ�ipv6����ǰӦΪ0��ʾʹ��ipv4 */
	unsigned short httpport; /* http�˿� */
	unsigned short httpsport; /* https�˿� */
	unsigned short rtspport; /* rtsp�˿� */
	char ipaddr[DEV_ADDR_LEN]; /* ip��ַ */
	char netmask[DEV_ADDR_LEN]; /* �������� */
	char gateway[DEV_ADDR_LEN]; /* Ĭ������ */
	char dnsaddr[DEV_ADDR_LEN]; /* dns��ַ */
} avc_network_t;

enum key_state_e {
	KEY_STATE_UP, /* key up */
	KEY_STATE_DOWN, /* key down */
	KEY_STATE_CLICK /* key down & up */
};

enum key_value_e {
	KEY_VALUE_ESCAPE, /* ESC */
	KEY_VALUE_ENTER, /* enter */
	KEY_VALUE_BACKSPACE, /* backspace */
	KEY_VALUE_FN, /* FN */

	KEY_VALUE_UP, /* up */
	KEY_VALUE_DOWN, /* down */
	KEY_VALUE_LEFT, /* left */
	KEY_VALUE_RIGHT, /* right */

	KEY_VALUE_NUM1, /* 1 */
	KEY_VALUE_NUM2, /* 2 */
	KEY_VALUE_NUM3, /* 3 */
	KEY_VALUE_NUM4, /* 4 */
	KEY_VALUE_NUM5, /* 5 */
	KEY_VALUE_NUM6, /* 6 */
	KEY_VALUE_NUM7, /* 7 */
	KEY_VALUE_NUM8, /* 8 */
	KEY_VALUE_NUM9, /* 9 */
	KEY_VALUE_NUM0, /* 0 */

	KEY_VALUE_INC, /* + */
	KEY_VALUE_DEC, /* - */

	KEY_VALUE_MENU, /* menu */
	KEY_VALUE_WIZARD, /* wizard */
	KEY_VALUE_REC, /* rec menu */
	KEY_VALUE_PTZ, /* ptz menu */
	KEY_VALUE_BACKUP, /* backup menu */
	KEY_VALUE_ALARM, /* alarm menu */
	KEY_VALUE_CLRALARM, /* alarm clear menu */
	KEY_VALUE_SEQ, /* seq display */
	KEY_VALUE_DISPLAY, /* display menu */
	KEY_VALUE_PLAYBACK, /* playback menu */
	KEY_VALUE_SEARCH, /* rec search menu */

	KEY_VALUE_PLAY, /* play start or restore */
	KEY_VALUE_PAUSE, /* play pause */
	KEY_VALUE_STOP, /* play stop */
	KEY_VALUE_MUTE, /* mute or voice */
	KEY_VALUE_SLOW, /* play speed slow */
	KEY_VALUE_FAST, /* play speed fast */
	KEY_VALUE_FORWARD, /* play forward */
	KEY_VALUE_BACKWRAD, /* play backward */

	KEY_VALUE_WIN1, /* win 1 */
	KEY_VALUE_WIN4, /* win 4 */
	KEY_VALUE_WIN8, /* win 8 */
	KEY_VALUE_WIN9, /* win 9 */
	KEY_VALUE_WIN16, /* win 16 */
	KEY_VALUE_WIN25, /* win 25 */
	KEY_VALUE_WIN36, /* win 36 */
	KEY_VALUE_WINMAX, /* win max */
	KEY_VALUE_WINSW /* win 1/4/8/9... switch */
};

#endif /* #ifndef __LIBTYPES_H__ */
