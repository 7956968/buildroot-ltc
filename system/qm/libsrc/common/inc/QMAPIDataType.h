#ifndef _QMAPI_DATATYPE_H
#define _QMAPI_DATATYPE_H


/*       �����������������    ǰ����F����������ֵ������6��F��������ֵ  */
#define QMAPI_SYSCFG_GETBASE						0XF0000000 /* GET �������ֵ */
#define QMAPI_SYSCFG_SETBASE						0XE0000000 /* SET �������ֵ */
#define QMAPI_SYS_FUN_BASE							0xD0000000 /* ���ûص�����   */
#define QMAPI_REC_SEARCH_FILE_BASE					0xC0000000 /* ��ѯ�ļ�����ֵ */
#define QMAPI_PTZ_STA_BASE							0xB0000000 /* ��̨����ֵ     */
#define QMAPI_TL_SERVER_BASE						0x0A000000 /* */



/********************************** PTZ **************************************/

#define QMAPI_PTZ_STA_UP			(QMAPI_PTZ_STA_BASE+1)
#define QMAPI_PTZ_STA_DOWN          (QMAPI_PTZ_STA_BASE+2)
#define QMAPI_PTZ_STA_LEFT			(QMAPI_PTZ_STA_BASE+3)
#define QMAPI_PTZ_STA_RIGHT			(QMAPI_PTZ_STA_BASE+4)
#define QMAPI_PTZ_STA_UP_LEFT		(QMAPI_PTZ_STA_BASE+5)
#define QMAPI_PTZ_STA_UP_RIGHT		(QMAPI_PTZ_STA_BASE+6)
#define QMAPI_PTZ_STA_DOWN_LEFT		(QMAPI_PTZ_STA_BASE+7)
#define QMAPI_PTZ_STA_DOWN_RIGHT	(QMAPI_PTZ_STA_BASE+8)

#define QMAPI_PTZ_STA_FOCUS_SUB		(QMAPI_PTZ_STA_BASE+10)		//Focus Far
#define QMAPI_PTZ_STA_FOCUS_ADD		(QMAPI_PTZ_STA_BASE+11)		//Focus Near
#define QMAPI_PTZ_STA_ZOOM_SUB		(QMAPI_PTZ_STA_BASE+12)		//Zoom Wide
#define QMAPI_PTZ_STA_ZOOM_ADD		(QMAPI_PTZ_STA_BASE+13)		//Zoom Tele
#define QMAPI_PTZ_STA_IRIS_SUB		(QMAPI_PTZ_STA_BASE+14)		//Iris Close
#define QMAPI_PTZ_STA_IRIS_ADD		(QMAPI_PTZ_STA_BASE+15)		//Iris Open
#define QMAPI_PTZ_STA_STOP			(QMAPI_PTZ_STA_BASE+16)
#define QMAPI_PTZ_STA_PRESET		(QMAPI_PTZ_STA_BASE+17)		//Ԥ��
#define QMAPI_PTZ_STA_CALL			(QMAPI_PTZ_STA_BASE+18)		//����

#define QMAPI_PTZ_STA_AUTO_STRAT	(QMAPI_PTZ_STA_BASE+20)
#define QMAPI_PTZ_STA_AUTO_STOP		(QMAPI_PTZ_STA_BASE+21)
#define QMAPI_PTZ_STA_LIGHT_OPEN	(QMAPI_PTZ_STA_BASE+22)      //�ƹ�
#define QMAPI_PTZ_STA_LIGHT_CLOSE	(QMAPI_PTZ_STA_BASE+23)      
#define QMAPI_PTZ_STA_BRUSH_START	(QMAPI_PTZ_STA_BASE+24)      //��ˢ
#define QMAPI_PTZ_STA_BRUSH_STOP	(QMAPI_PTZ_STA_BASE+25)  
#define QMAPI_PTZ_STA_TRACK_START	(QMAPI_PTZ_STA_BASE+26)      //�켣
#define QMAPI_PTZ_STA_TRACK_STOP	(QMAPI_PTZ_STA_BASE+27)
#define QMAPI_PTZ_STA_TRACK_RUN		(QMAPI_PTZ_STA_BASE+28)
#define QMAPI_PTZ_STA_PRESET_CLS	(QMAPI_PTZ_STA_BASE+29)      //���Ԥ�õ�

#define QMAPI_PTZ_STA_ADD_POS_CRU	(QMAPI_PTZ_STA_BASE+30)		/* ��Ԥ�õ����Ѳ������ */
#define QMAPI_PTZ_STA_DEL_POS_CRU	(QMAPI_PTZ_STA_BASE+31)		/* ��Ѳ�����Ѳ��������ɾ�� */
#define QMAPI_PTZ_STA_DEL_PRE_CRU	(QMAPI_PTZ_STA_BASE+32)		/* ��Ԥ�õ��Ѳ��������ɾ�� */
#define QMAPI_PTZ_STA_MOD_POINT_CRU	(QMAPI_PTZ_STA_BASE+33)		/* �޸�Ѳ����*/
#define QMAPI_PTZ_STA_START_CRU		(QMAPI_PTZ_STA_BASE+34)		/* ��ʼѲ�� */
#define QMAPI_PTZ_STA_STOP_CRU		(QMAPI_PTZ_STA_BASE+35)		/* ֹͣѲ�� */
#define QMAPI_PTZ_STA_CRU_STATUS	(QMAPI_PTZ_STA_BASE+36)		/* Ѳ��״̬ */


/************************************ALARM IO************************************/
#define QMAPI_STATE_ALARMOUT_STOP	0
#define QMAPI_STATE_ALARMOUT_START	1
#define QMAPI_STATE_ALARMIN_NORMAL	0
#define QMAPI_STATE_ALARMIN_WARNN	1

/***********************************FILE SEARCH**********************************/

#define QMAPI_SEARCH_FILE_SUCCESS	(QMAPI_REC_SEARCH_FILE_BASE+1)	// ��ȡ�ļ���Ϣ�ɹ� 
#define QMAPI_SEARCH_FILE_NOFIND	(QMAPI_REC_SEARCH_FILE_BASE+2)	// δ���ҵ��ļ� 
#define QMAPI_SEARCH_ISFINDING		(QMAPI_REC_SEARCH_FILE_BASE+3)	// ���ڲ�����ȴ� 
#define QMAPI_SEARCH_NOMOREFILE		(QMAPI_REC_SEARCH_FILE_BASE+4)	// û�и�����ļ������ҽ��� 
#define QMAPI_SEARCH_FILE_EXCEPTION	(QMAPI_REC_SEARCH_FILE_BASE+5)	// �����ļ�ʱ�쳣 

/************************************************************************/
/*       �豸�����¼�����                                               */
/************************************************************************/
typedef enum __QMAPI_ALARM_TYPE_E
{
    QMAPI_ALARM_TYPE_ALARMIN = 0,		//0:�ź���������ʼ
    QMAPI_ALARM_TYPE_ALARMIN_RESUME,	//1:�ź��������ָ�
    QMAPI_ALARM_TYPE_VMOTION,			//2:�ƶ����
    QMAPI_ALARM_TYPE_VMOTION_RESUME,	//3:��Ƶ�ƶ���ⱨ���ָ�
    QMAPI_ALARM_TYPE_VLOST,			//4:�źŶ�ʧ
    QMAPI_ALARM_TYPE_VLOST_RESUME,		//5:��Ƶ��ʧ�����ָ�
    QMAPI_ALARM_TYPE_VSHELTER,			//6:�ڵ�����
	QMAPI_ALARM_TYPE_VSHELTER_RESUME,	//7
    QMAPI_ALARM_TYPE_ILLEGAL_ACCESS,	//8:�Ƿ�����
    QMAPI_ALARM_TYPE_NET_BROKEN,		//9:����Ͽ�
    QMAPI_ALARM_TYPE_IP_CONFLICT,		//10:IP��ͻ
    QMAPI_ALARM_TYPE_DISK_FULL,			//11:Ӳ����
    QMAPI_ALARM_TYPE_DISK_UNFORMAT,		//12:Ӳ��δ��ʽ��
    QMAPI_ALARM_TYPE_DISK_RWERR,		//13:��дӲ�̳���,
    QMAPI_ALARM_TYPE_BUTT,
}QMAPI_ALARM_TYPE_E;

typedef  enum
{
    QMAPI_REC_PLAYSTART = 0,
    QMAPI_REC_PLAYPAUSE,
    QMAPI_REC_PLAYRESTART,
    QMAPI_REC_FASTFORWARD2X,
    QMAPI_REC_FASTFORWARD4X,
    QMAPI_REC_FASTFORWARD8X,
    QMAPI_REC_FASTFORWARD16X,
    QMAPI_REC_FASTFORWARD32X,
    QMAPI_REC_SLOWPLAY2X,
    QMAPI_REC_SLOWPLAY4X,
    QMAPI_REC_SLOWPLAY8X,
    QMAPI_REC_SLOWPLAY16X,
    QMAPI_REC_SLOWPLAY32X,
    QMAPI_REC_PLAYNORMAL,
    QMAPI_REC_PLAYFRAME,
    QMAPI_REC_PLAYSETPOS,
    QMAPI_REC_PLAYGETPOS,
    QMAPI_REC_PLAYGETTIME,
    QMAPI_REC_PLAYGETFRAME,
    QMAPI_REC_GETTOTALFRAMES,
    QMAPI_REC_GETTOTALTIME,
    QMAPI_REC_THROWBFRAME,
	QMAPI_REC_PLAYJUMPTIME,
}QMAPI_PLAYBACK_CONTROL_E;

/************************************************************************/

//1) �豸��QMAPI_NET_DEVICE_INFO�ṹ��
#define QMAPI_SYSCFG_GET_DEVICECFG				(QMAPI_SYSCFG_GETBASE+0xF000)		//��ȡ�豸����
#define QMAPI_SYSCFG_SET_DEVICECFG				(QMAPI_SYSCFG_SETBASE+0xF001)		//�����豸����
#define QMAPI_SYSCFG_GET_DEF_DEVICECFG			(QMAPI_SYSCFG_GETBASE+0xF002)		//�����豸����

#define QMAPI_SYSCFG_GET_RESTORECFG				(QMAPI_SYSCFG_GETBASE+0xF010)		//�ָ�����ֵ����
#define QMAPI_SYSCFG_SET_RESTORECFG				(QMAPI_SYSCFG_SETBASE+0xF011)
#define QMAPI_SYSCFG_SET_SAVECFG				(QMAPI_SYSCFG_SETBASE+0xF012)		//��������
#define QMAPI_SYSCFG_SET_SAVECFG_ASYN			(QMAPI_SYSCFG_SETBASE+0xF013)		//��������,�첽����

#define QMAPI_DEV_GET_DEVICEMAINTAINCFG			(QMAPI_SYSCFG_GETBASE+0xF020)
#define QMAPI_DEV_SET_DEVICEMAINTAINCFG			(QMAPI_SYSCFG_SETBASE+0xF021)

/*####################################### ADVANCE ###############################################*/
//�û���Կ����
#define QMAPI_SYSCFG_GET_USERKEY				(QMAPI_SYSCFG_GETBASE+0xF030)
#define QMAPI_SYSCFG_SET_USERKEY				(QMAPI_SYSCFG_SETBASE+0xF031)

#define QMAPI_SYSCFG_STA_AUTO_TEST				(QMAPI_SYSCFG_SETBASE+0xF040)
#define QMAPI_SYSCFG_GET_LOGINFO				(QMAPI_SYSCFG_GETBASE+0xF050)
/*###############################################################################################*/

//2������
//�������磨QMAPI_NET_NETWORK_CFG�ṹ��
#define QMAPI_SYSCFG_GET_NETCFG					(QMAPI_SYSCFG_GETBASE+0xF100)		//��ȡ�������
#define QMAPI_SYSCFG_SET_NETCFG					(QMAPI_SYSCFG_SETBASE+0xF101)		//�����������
#define QMAPI_SYSCFG_GET_DEF_NETCFG				(QMAPI_SYSCFG_GETBASE+0xF102)
#define QMAPI_SYSCFG_GET_NETSTATUS              (QMAPI_SYSCFG_GETBASE+0xF103)


//DDNS��QMAPI_NET_DDNSCFG�ṹ��
#define QMAPI_SYSCFG_GET_DDNSCFG				(QMAPI_SYSCFG_GETBASE+0xF110)		//��ȡDDNS����
#define QMAPI_SYSCFG_SET_DDNSCFG				(QMAPI_SYSCFG_SETBASE+0xF111)		//����DDNS����
/*####################################### ADVANCE ###############################################*/
//EMAIL��QMAPI_NET_EMAIL_PARAM�ṹ��
#define QMAPI_SYSCFG_GET_EMAILCFG				(QMAPI_SYSCFG_GETBASE+0xF120)		//��ȡEMAIL����
#define QMAPI_SYSCFG_SET_EMAILCFG				(QMAPI_SYSCFG_SETBASE+0xF121)		//����EMAIL����
//FTP��QMAPI_NET_FTP_PARAM�ṹ��
#define QMAPI_SYSCFG_GET_FTPCFG					(QMAPI_SYSCFG_GETBASE+0xF130)		//��ȡFTP����
#define QMAPI_SYSCFG_SET_FTPCFG					(QMAPI_SYSCFG_SETBASE+0xF131)		//����FTP����
//RTSP 
#define QMAPI_SYSCFG_GET_RTSPCFG				(QMAPI_SYSCFG_GETBASE+0xF133)
#define QMAPI_SYSCFG_SET_RTSPCFG				(QMAPI_SYSCFG_SETBASE+0xF134)		//rtsp����
//P2P
#define QMAPI_SYSCFG_GET_P2PCFG					(QMAPI_SYSCFG_GETBASE+0xF135)
#define QMAPI_SYSCFG_SET_P2PCFG					(QMAPI_SYSCFG_SETBASE+0xF136)
//PPPOE��QMAPI_NET_PPPOECFG�ṹ��
#define QMAPI_SYSCFG_GET_PPPOECFG				(QMAPI_SYSCFG_GETBASE+0xF137)		//��ȡPPPOE����
#define QMAPI_SYSCFG_SET_PPPOECFG				(QMAPI_SYSCFG_SETBASE+0xF138)			//����PPPOE����

//���Ĺ���ƽ̨��QMAPI_NET_PLATFORM_INFO_V2�ṹ��
#define QMAPI_SYSCFG_GET_PLATFORMCFG            (QMAPI_SYSCFG_GETBASE+0xF160)        //��ȡ���Ĺ���ƽ̨����
#define QMAPI_SYSCFG_SET_PLATFORMCFG            (QMAPI_SYSCFG_SETBASE+0xF161)        //�������Ĺ���ƽ̨����
/*###############################################################################################*/

//WIFI��QMAPI_NET_WIFI_CONFIG�ṹ��
#define QMAPI_SYSCFG_GET_WIFICFG				(QMAPI_SYSCFG_GETBASE+0xF170)		//��ȡWIFI����
#define QMAPI_SYSCFG_SET_WIFICFG				(QMAPI_SYSCFG_SETBASE+0xF171)		//����WIFI����
#define QMAPI_SYSCFG_GET_WIFI_SITE_LIST			(QMAPI_SYSCFG_GETBASE+0xF172)		//��ȡWIFI վ���б�
#define QMAPI_SYSCFG_SET_WIFI_WPS_START			(QMAPI_SYSCFG_SETBASE+0xF173)		//����WPS��ʼ

/*####################################### ADVANCE ###############################################*/
//���������ߣ�QMAPI_NET_WANWIRELESS_CONFIG�ṹ��
#define QMAPI_SYSCFG_GET_WANWIRELESSCFG			(QMAPI_SYSCFG_GETBASE+0xF180)		//��ȡWANWIRELESS����
#define QMAPI_SYSCFG_SET_WANWIRELESSCFG			(QMAPI_SYSCFG_SETBASE+0xF181)		//����WANWIRELESS����
/*###############################################################################################*/

/*####################################### ADVANCE ###############################################*/
//UPNP (QMAPI_UPNP_CONFIG�ṹ)
#define QMAPI_SYSCFG_GET_UPNPCFG                (QMAPI_SYSCFG_GETBASE+0xF190)		//��ȡUPNP����
#define QMAPI_SYSCFG_SET_UPNPCFG				(QMAPI_SYSCFG_SETBASE+0xF191)		//����UPNP����
/*###############################################################################################*/

//3������Ƶͨ��
//ͼ��ѹ����QMAPI_NET_CHANNEL_PIC_INFO�ṹ��
#define QMAPI_SYSCFG_GET_PICCFG					(QMAPI_SYSCFG_GETBASE+0xF200)		//��ȡͼ��ѹ������
#define QMAPI_SYSCFG_SET_PICCFG					(QMAPI_SYSCFG_SETBASE+0xF201)		//����ͼ��ѹ������
#define QMAPI_SYSCFG_GET_DEF_PICCFG				(QMAPI_SYSCFG_GETBASE+0xF202)
//QMAPI_NET_SUPPORT_STREAM_FMT  ͼ������
#define QMAPI_SYSCFG_GET_SUPPORT_STREAM_FMT		(QMAPI_SYSCFG_GETBASE+0xF203)		//��ȡϵͳ֧�ֵ�ͼ������

#define QMAPI_SYSCFG_GET_VIEWMODE				(QMAPI_SYSCFG_GETBASE+0xF204)		//
#define QMAPI_SYSCFG_SET_VIEWMODE				(QMAPI_SYSCFG_SETBASE+0xF205)		//

//ͼ���ַ����ӣ�QMAPI_NET_CHANNEL_OSDINFO�ṹ��
#define QMAPI_SYSCFG_GET_OSDCFG					(QMAPI_SYSCFG_GETBASE+0xF210)		//��ȡͼ���ַ����Ӳ���
#define QMAPI_SYSCFG_SET_OSDCFG					(QMAPI_SYSCFG_SETBASE+0xF211)		//����ͼ���ַ����Ӳ���
#define QMAPI_SYSCFG_GET_ROICFG					(QMAPI_SYSCFG_GETBASE+0xF212)		//��ȡͼ���ַ����Ӳ���
#define QMAPI_SYSCFG_SET_ROICFG					(QMAPI_SYSCFG_SETBASE+0xF213)		//����ͼ���ַ����Ӳ���

//ͼ��ɫ�ʣ�QMAPI_NET_CHANNEL_COLOR�ṹ��
#define QMAPI_SYSCFG_GET_COLORCFG				(QMAPI_SYSCFG_GETBASE+0xF220)		//��ȡͼ��ɫ�ʲ���
#define QMAPI_SYSCFG_SET_COLORCFG				(QMAPI_SYSCFG_SETBASE+0xF221)		//����ͼ��ɫ�ʲ���

//(QMAPI_NET_COLOR_SUPPORT�ṹ)
#define QMAPI_SYSCFG_GET_COLOR_SUPPORT			(QMAPI_SYSCFG_GETBASE+0xF222)		//��ȡͼ��ɫ�ʲ���
//ͼ��ɫ��(QMAPI_NET_CHANNEL_COLOR_SINGLE�ṹ)
#define QMAPI_SYSCFG_SET_COLORCFG_SINGLE		(QMAPI_SYSCFG_SETBASE+0xF223)		//��������ĳ��ͼ��ɫ�ʲ���,
#define QMAPI_SYSCFG_GET_DEF_COLORCFG			(QMAPI_SYSCFG_GETBASE+0xF224)

//(QMAPI_NET_ENHANCED_COLOR_SUPPORT�ṹ) 
#define QMAPI_SYSCFG_GET_ENHANCED_COLORSUPPORT	(QMAPI_SYSCFG_GETBASE+0xF225)		//��ȡͼ��ɫ��֧�ָ߼�����
//(QMAPI_NET_CHANNEL_ENHANCED_COLOR�ṹ)
#define QMAPI_SYSCFG_GET_ENHANCED_COLOR			(QMAPI_SYSCFG_GETBASE+0xF226)		//��ȡͼ��ɫ�ʸ߼�����

/*####################################### ADVANCE ###############################################*/
#define QMAPI_SYSCFG_SET_COLOR_BLACK_DETECTION	(QMAPI_SYSCFG_SETBASE+0xF227)		//���ò�ת�ڼ�����
#define QMAPI_SYSCFG_GET_COLOR_BLACK_DETECTION	(QMAPI_SYSCFG_GETBASE+0xF228)		//��ȡ��ת�ڼ�����
/*###############################################################################################*/


//ͼ���ڵ���QMAPI_NET_CHANNEL_SHELTER�ṹ��
#define QMAPI_SYSCFG_GET_SHELTERCFG				(QMAPI_SYSCFG_GETBASE+0xF230)		//��ȡͼ���ڵ�����
#define QMAPI_SYSCFG_SET_SHELTERCFG				(QMAPI_SYSCFG_SETBASE+0xF231)		//����ͼ���ڵ�����
//ͼ���ƶ���⣨QMAPI_NET_CHANNEL_MOTION_DETECT�ṹ��
#define QMAPI_SYSCFG_GET_MOTIONCFG				(QMAPI_SYSCFG_GETBASE+0xF240)		//��ȡͼ���ƶ�������
#define QMAPI_SYSCFG_SET_MOTIONCFG				(QMAPI_SYSCFG_SETBASE+0xF241)		//����ͼ���ƶ�������
#define QMAPI_SYSCFG_DEF_MOTIONCFG				(QMAPI_SYSCFG_GETBASE+0xF242)

/*####################################### ADVANCE ###############################################*/
//ͼ����Ƶ��ʧ��QMAPI_NET_CHANNEL_VILOST�ṹ��
#define QMAPI_SYSCFG_GET_VLOSTCFG				(QMAPI_SYSCFG_GETBASE+0xF250)		//��ȡͼ����Ƶ��ʧ����
#define QMAPI_SYSCFG_SET_VLOSTCFG				(QMAPI_SYSCFG_SETBASE+0xF251)		//����ͼ����Ƶ��ʧ����
#define QMAPI_SYSCFG_DEF_VLOSTCFG				(QMAPI_SYSCFG_GETBASE+0xF252)
//ͼ���ڵ�������QMAPI_NET_CHANNEL_HIDEALARM�ṹ��
#define QMAPI_SYSCFG_GET_HIDEALARMCFG			(QMAPI_SYSCFG_GETBASE+0xF260)		//��ȡͼ���ڵ���������
#define QMAPI_SYSCFG_SET_HIDEALARMCFG			(QMAPI_SYSCFG_SETBASE+0xF261)		//����ͼ���ڵ���������
#define QMAPI_SYSCFG_DEF_HIDEALARMCFG			(QMAPI_SYSCFG_GETBASE+0xF262)
/*###############################################################################################*/

/*####################################### ADVANCE ###############################################*/
//ͼ��¼��QMAPI_NET_CHANNEL_RECORD�ṹ��
#define QMAPI_SYSCFG_GET_RECORDCFG				(QMAPI_SYSCFG_GETBASE+0xF300)		//��ȡͼ��¼�����
#define QMAPI_SYSCFG_SET_RECORDCFG				(QMAPI_SYSCFG_SETBASE+0xF301)		//����ͼ��¼�����
#define QMAPI_SYSCFG_GET_DEF_RECORDCFG			(QMAPI_SYSCFG_GETBASE+0xF302)

#define QMAPI_SYSCFG_GET_RECORD_ATTR		    		(QMAPI_SYSCFG_GETBASE+0xF303)		//��ȡͼ��¼������
#define QMAPI_SYSCFG_SET_RECORD_ATTR		    		(QMAPI_SYSCFG_SETBASE+0xF304)		//����ͼ��¼������


//ͼ���ֶ�¼��QMAPI_NET_CHANNEL_RECORD�ṹ)
#define QMAPI_SYSCFG_GET_RECORDMODECFG			(QMAPI_SYSCFG_GETBASE+0xF320)		//��ȡͼ���ֶ�¼�����
#define QMAPI_SYSCFG_SET_RECORDMODECFG			(QMAPI_SYSCFG_SETBASE+0xF321)		//����ͼ���ֶ�¼�����

//ͼ��ʱץ�ģ�QMAPI_NET_SNAP_TIMER�ṹ��
#define QMAPI_SYSCFG_GET_SNAPTIMERCFG			(QMAPI_SYSCFG_GETBASE+0xF330)		//��ȡͼ��ʱץ�Ĳ���
#define QMAPI_SYSCFG_SET_SNAPTIMERCFG			(QMAPI_SYSCFG_SETBASE+0xF331)		//����ͼ��ʱץ�Ĳ���
/*###############################################################################################*/

//4�����ڣ�QMAPI_NET_RS232CFG�ṹ��
/*####################################### ADVANCE ###############################################*/
//��������QMAPI_NET_DECODERCFG�ṹ��
#define QMAPI_SYSCFG_GET_DECODERCFG				(QMAPI_SYSCFG_GETBASE+0xF400)		//��ȡ����������
#define QMAPI_SYSCFG_SET_DECODERCFG				(QMAPI_SYSCFG_SETBASE+0xF401)		//���ý���������
#define QMAPI_SYSCFG_GET_DEF_DECODERCFG			(QMAPI_SYSCFG_GETBASE+0xF402)		//���ý���������

#define QMAPI_SYSCFG_GET_RS232CFG				(QMAPI_SYSCFG_GETBASE+0xF410)		//��ȡ232���ڲ���
#define QMAPI_SYSCFG_SET_RS232CFG				(QMAPI_SYSCFG_SETBASE+0xF411)		//����232���ڲ���
#define QMAPI_SYSCFG_GET_DEF_SERIAL				(QMAPI_SYSCFG_GETBASE+0xF412)
//(QMAPI_NET_PTZ_PROTOCOLCFG�ṹ)
#define QMAPI_SYSCFG_GET_PTZ_PROTOCOLCFG		(QMAPI_SYSCFG_GETBASE+0xF420)		//��ȡ֧�ֵ���̨Э����Ϣ
//(QMAPI_NET_PTZ_PROTOCOL_DATA �ṹ)
#define QMAPI_SYSCFG_ADD_PTZ_PROTOCOL			(QMAPI_SYSCFG_SETBASE+0xF421)		//�����̨Э��
//(QMAPI_NET_PTZ_PROTOCOL_DATA �ṹ)
#define QMAPI_SYSCFG_GET_PTZ_PROTOCOL_DATA		(QMAPI_SYSCFG_GETBASE+0xF422)		//��ȡ��̨Э������
//(QMAPI_NET_PTZ_POS �ṹ)
#define	QMAPI_SYSCFG_GET_PTZPOS					(QMAPI_SYSCFG_GETBASE+0xF430)		//��̨��ȡPTZλ��
#define	QMAPI_SYSCFG_SET_PTZPOS					(QMAPI_SYSCFG_GETBASE+0xF431)		//��̨����PTZλ��
/*###############################################################################################*/

//5������
/*####################################### ADVANCE ###############################################*/
//���루QMAPI_NET_ALARMINCFG�ṹ��
#define QMAPI_SYSCFG_GET_ALARMINCFG				(QMAPI_SYSCFG_GETBASE+0xF500)		//��ȡ�����������
#define QMAPI_SYSCFG_SET_ALARMINCFG				(QMAPI_SYSCFG_SETBASE+0xF501)		//���ñ����������
#define QMAPI_SYSCFG_DEF_ALARMINCFG				(QMAPI_SYSCFG_GETBASE+0xF502)
//�����QMAPI_NET_ALARMOUTCFG�ṹ��
#define QMAPI_SYSCFG_GET_ALARMOUTCFG			(QMAPI_SYSCFG_GETBASE+0xF510)		//��ȡ�����������
#define QMAPI_SYSCFG_SET_ALARMOUTCFG			(QMAPI_SYSCFG_SETBASE+0xF511)		//���ñ����������
#define QMAPI_SYSCFG_DEF_ALARMOUTCFG			(QMAPI_SYSCFG_GETBASE+0xF512)

//RESET ����״̬��ȡ
#define QMAPI_SYSCFG_GET_RESETSTATE             (QMAPI_SYSCFG_GETBASE+0xF520)
/*###############################################################################################*/

/*####################################### ADVANCE ###############################################*/
//Ĭ������
#define QMAPI_SYSCFG_GET_DEFAULTCFG_FILE		(QMAPI_SYSCFG_GETBASE+0xF600)
#define QMAPI_SYSCFG_SET_DEFAULTCFG_FILE		(QMAPI_SYSCFG_SETBASE+0xF601)
//logo�ļ�
#define QMAPI_SYSCFG_GET_LOGO_FILE				(QMAPI_SYSCFG_GETBASE+0xF701)
#define QMAPI_SYSCFG_SET_LOGO_FILE				(QMAPI_SYSCFG_SETBASE+0xF702)
/*###############################################################################################*/

/*####################################### ADVANCE ###############################################*/
//��ȡ���������õ�Ԥ�õ����Ϣ-QMAPI_NET_PRESET_INFO
#define QMAPI_SYSCFG_GET_ALL_PRESET				(QMAPI_SYSCFG_GETBASE+0xF780)
//��ȡͨ���������Ѿ����õ�Ѳ���� QMAPI_NET_CRUISE_CFG
#define QMAPI_SYSCFG_GET_CRUISE_CFG				(QMAPI_SYSCFG_GETBASE+0xF781)
//����һ��Ѳ��   QMAPI_NET_CRUISE_INFO
#define QMAPI_SYSCFG_SET_CRUISE_INFO			(QMAPI_SYSCFG_SETBASE+0xF782)
/*###############################################################################################*/


//6��ʱ��
//ʱ������ʱ�ƣ�QMAPI_NET_ZONEANDDST�ṹ��
#define QMAPI_SYSCFG_GET_ZONEANDDSTCFG			(QMAPI_SYSCFG_GETBASE+0xF800)		//��ȡʱ������ʱ�Ʋ���
#define QMAPI_SYSCFG_SET_ZONEANDDSTCFG			(QMAPI_SYSCFG_SETBASE+0xF801)		//����ʱ������ʱ�Ʋ���
//NTP ��QMAPI_NET_NTP_CFG�ṹ��
#define QMAPI_SYSCFG_GET_NTPCFG					(QMAPI_SYSCFG_GETBASE+0xF802)		//��ȡNTP ����      
#define QMAPI_SYSCFG_SET_NTPCFG					(QMAPI_SYSCFG_SETBASE+0xF803)		//����NTP ����      
#define QMAPI_SYSCFG_DEF_NTPCFG					(QMAPI_SYSCFG_GETBASE+0xF804)

/*####################################### ADVANCE ###############################################*/
//7������Ԥ����QMAPI_NET_PREVIEWCFG�ṹ��
#define QMAPI_SYSCFG_GET_PREVIEWCFG				(QMAPI_SYSCFG_GETBASE+0xF900)		//��ȡԤ������
#define QMAPI_SYSCFG_SET_PREVIEWCFG				(QMAPI_SYSCFG_SETBASE+0xF901)		//����Ԥ������
#define QMAPI_SYSCFG_GET_DEF_PREVIEWCFG			(QMAPI_SYSCFG_GETBASE+0xF902)
//8����Ƶ�����QMAPI_NET_VIDEOOUT�ṹ��
#define QMAPI_SYSCFG_GET_VIDEOOUTCFG			(QMAPI_SYSCFG_GETBASE+0xF910)		//��ȡ��Ƶ�������
#define QMAPI_SYSCFG_SET_VIDEOOUTCFG			(QMAPI_SYSCFG_SETBASE+0xF911)		//������Ƶ�������
#define QMAPI_SYSCFG_GET_DEF_VIDEOOUTCFG		(QMAPI_SYSCFG_GETBASE+0xF912)		//������Ƶ�������
//����Ӳ����Ϣ��QMAPI_NET_HDCFG�ṹ��
#define QMAPI_SYSCFG_GET_HDCFG					(QMAPI_SYSCFG_GETBASE+0xF920)		//��ȡӲ�̲���
#define QMAPI_SYSCFG_SET_HDCFG					(QMAPI_SYSCFG_SETBASE+0xF921)		//����(����)Ӳ�̲���
#define QMAPI_SYSCFG_HD_FORMAT					(QMAPI_SYSCFG_GETBASE+0xF922)		//��ʽ��Ӳ��
#define QMAPI_SYSCFG_GET_HD_FORMAT_STATUS		(QMAPI_SYSCFG_GETBASE+0xF923)		//��ʽ��Ӳ��״̬�Լ�����
#define QMAPI_SYSCFG_UNLOAD_DISK				(QMAPI_SYSCFG_GETBASE+0xF924)		//ж�ش���

//����������Ϣ���ã�QMAPI_NET_HDGROUP_CFG�ṹ��
#define QMAPI_SYSCFG_GET_HDGROUPCFG				(QMAPI_SYSCFG_GETBASE+0xF930)		//��ȡӲ�������
#define QMAPI_SYSCFG_SET_HDGROUPCFG				(QMAPI_SYSCFG_GETBASE+0xF931)		//����Ӳ�������
/*###############################################################################################*/

//9) �û����û���
//�û���QMAPI_NET_USER_INFO�ṹ��
#define QMAPI_SYSCFG_GET_USERCFG				(QMAPI_SYSCFG_GETBASE+0xFA00)		//��ȡ�û�����
#define QMAPI_SYSCFG_SET_USERCFG				(QMAPI_SYSCFG_SETBASE+0xFA01)		//�����û�����
/*####################################### ADVANCE ###############################################*/
//�û��飨QMAPI_NET_USER_GROUP_INFO�ṹ��
#define QMAPI_SYSCFG_GET_USERGROUPCFG			(QMAPI_SYSCFG_GETBASE+0xFA02)		//��ȡ�û������
#define QMAPI_SYSCFG_SET_USERGROUPCFG			(QMAPI_SYSCFG_SETBASE+0xFA03)		//�����û������
/*###############################################################################################*/

/*####################################### ADVANCE ###############################################*/
//10)�쳣��QMAPI_NET_EXCEPTION�ṹ��
#define QMAPI_SYSCFG_GET_EXCEPTIONCFG			(QMAPI_SYSCFG_GETBASE+0xFB00)		//��ȡ�쳣����
#define QMAPI_SYSCFG_SET_EXCEPTIONCFG			(QMAPI_SYSCFG_SETBASE+0xFB01)		//�����쳣����
/*###############################################################################################*/

//��������������    //QMAPI_NET_CONSUMER_INFO
#define QMAPI_SYSCFG_GET_CONSUMER				(QMAPI_SYSCFG_GETBASE+0xFB02)
#define QMAPI_SYSCFG_SET_CONSUMER				(QMAPI_SYSCFG_GETBASE+0xFB03)

//ONVIF (QMAPI_SYSCFG_ONVIFTESTINFO)
#define QMAPI_SYSCFG_GET_ONVIFTESTINFO          (QMAPI_SYSCFG_GETBASE+0xFB05)       //��ȡONVIF ������֤����
#define QMAPI_SYSCFG_SET_ONVIFTESTINFO          (QMAPI_SYSCFG_GETBASE+0xFB06)


//��Ϣ֪ͨ�û����ṹ�壺QMAPI_NET_NOTIFY_USER_INFO
#define QMAPI_SYSCFG_NOTIFY_USER 				(QMAPI_SYSCFG_GETBASE+0xFC00)


/*####################################### ADVANCE ###############################################*/
// ������Ƶ���ؼ�֡ 
#define QMAPI_NET_STA_IFRAME_REQUEST          	(QMAPI_SYS_FUN_BASE+0xF001)
// ������Ƶ�Խ����ݻص�����(OnNetAudioStreamCallBack)
#define QMAPI_NET_REG_AUDIOCALLBACK				(QMAPI_SYS_FUN_BASE+0xF002)
#define QMAPI_NET_UNREG_AUDIOCALLBACK			(QMAPI_SYS_FUN_BASE+0xF003)
// ������Ƶ���ݻص�����(QMAPI_NET_VIDEOCALLBACK)
#define QMAPI_NET_REG_VIDEOCALLBACK				(QMAPI_SYS_FUN_BASE+0xF004)
#define QMAPI_NET_UNREG_VIDEOCALLBACK			(QMAPI_SYS_FUN_BASE+0xF005)
// ���ñ�����Ϣ�ص�����(OnNetAlarmCallback)
#define QMAPI_NET_REG_ALARMCALLBACK				(QMAPI_SYS_FUN_BASE+0xF006)
#define QMAPI_NET_UNREG_ALARMCALLBACK			(QMAPI_SYS_FUN_BASE+0xF007)
// ���ô������ݻص�����(OnNetSerialDataCallback)
#define QMAPI_NET_REG_SERIALDATACALLBACK		(QMAPI_SYS_FUN_BASE+0xF008)
#define QMAPI_NET_UNREG_SERIALDATACALLBACK		(QMAPI_SYS_FUN_BASE+0xF009)
//ע��طŻص�����
#define QMAPI_NET_REG_PLAYBACKCALLBACK			(QMAPI_SYS_FUN_BASE+0xF00A)
#define QMAPI_NET_UNREG_PLAYBACKCALLBACK		(QMAPI_SYS_FUN_BASE+0xF00B)

//��ĳͨ����Ƶ
#define QMAPI_NET_STA_START_VIDEO				(QMAPI_SYS_FUN_BASE+0xF010)
//�ر�ĳͨ����Ƶ
#define QMAPI_NET_STA_STOP_VIDEO				(QMAPI_SYS_FUN_BASE+0xF011)
//��ʼ��Ƶ�Խ�
#define QMAPI_NET_STA_START_TALKAUDIO			(QMAPI_SYS_FUN_BASE+0xF020)
//ֹͣ��Ƶ�Խ�
#define QMAPI_NET_STA_STOP_TALKAUDIO			(QMAPI_SYS_FUN_BASE+0xF021)
//��ȡ��Ƶ������Ϣ
#define QMAPI_NET_STA_GET_SPSPPSENCODE_DATA		(QMAPI_SYS_FUN_BASE+0xF030)

// ��͸�����ڴ���
#define QMAPI_NET_STA_OPEN_SERIALTRANSP			(QMAPI_SYS_FUN_BASE+0xF100)
// �ر�͸�����ڴ���
#define QMAPI_NET_STA_CLOSE_SERIALTRANSP		(QMAPI_SYS_FUN_BASE+0xF101)
// ��̨����( QMAPI_NET_PTZ_CONTROL �ṹ��)
#define QMAPI_NET_STA_PTZ_CONTROL				(QMAPI_SYS_FUN_BASE+0xF110)
// �����������(����ģʽQMAPI_NET_ALARMOUT_CONTROL)
#define QMAPI_NET_STA_ALARMOUT_CONTROL			(QMAPI_SYS_FUN_BASE+0xF120)
// ��ȡ�������״̬(QMAPI_NET_SENSOR_STATE)
#define QMAPI_NET_GET_ALARMOUT_STATE			(QMAPI_SYS_FUN_BASE+0xF121) 
// ��ȡ��������״̬(QMAPI_NET_SENSOR_STATE)
#define QMAPI_NET_GET_ALARMIN_STATE				(QMAPI_SYS_FUN_BASE+0xF122)

// �����豸
#define QMAPI_NET_STA_REBOOT					(QMAPI_SYS_FUN_BASE+0xF130)
// �豸�ػ�
#define QMAPI_NET_STA_SHUTDOWN					(QMAPI_SYS_FUN_BASE+0xF131)
//��ȡϵͳʱ��
#define QMAPI_NET_STA_GET_SYSTIME				(QMAPI_SYS_FUN_BASE+0xF132)
//����ϵͳʱ��
#define QMAPI_NET_STA_SET_SYSTIME				(QMAPI_SYS_FUN_BASE+0xF133)

// ץ��ͼƬ(QMAPI_NET_SNAP_DATA)
#define QMAPI_NET_STA_SNAPSHOT					(QMAPI_SYS_FUN_BASE+0xF140)
//¼�����(QMAPI_NET_REC_CONTROL)
#define QMAPI_NET_STA_REC_CONTROL				(QMAPI_SYS_FUN_BASE+0xF150)

#define QMAPI_NET_STA_CLOSE_RS485				(QMAPI_SYS_FUN_BASE+0xF200)
#define QMAPI_NET_STA_GET_VIDEO_STATE			(QMAPI_SYS_FUN_BASE+0xF201)

//�ļ�ϵͳ��������(QMAPI_NET_UPGRADE_REQ)
#define QMAPI_NET_STA_UPGRADE_REQ				(QMAPI_SYS_FUN_BASE+0xF300)
//�ļ�ϵͳ��������(QMAPI_NET_UPGRADE_RESP)
#define QMAPI_NET_STA_UPGRADE_RESP				(QMAPI_SYS_FUN_BASE+0xF301)
//�ļ�ϵͳ��������(QMAPI_NET_UPGRADE_DATA)
#define QMAPI_NET_STA_UPGRADE_DATA				(QMAPI_SYS_FUN_BASE+0xF302)

//�ļ�ϵͳ����׼��
#define QMAPI_NET_STA_UPGRADE_PREPARE           (QMAPI_SYS_FUN_BASE+0xF303)
//�ļ�ϵͳ������ʼ
#define QMAPI_NET_STA_UPGRADE_START             (QMAPI_SYS_FUN_BASE+0xF304)



/*###############################################################################################*/

/*########################################yi zhangy#######################################################*/
// ��ȡ����оƬ��Ϣ
#define QMAPI_SYSCFG_GET_ENCRYPT				(QMAPI_TL_SERVER_BASE+0x0001)
#define QMAPI_SYSCFG_SET_ENCRYPT				(QMAPI_TL_SERVER_BASE+0x0002)

// ��ȡ
#define QMAPI_SYSCFG_GET_TLSERVER				(QMAPI_TL_SERVER_BASE+0x0003)
#define QMAPI_SYSCFG_SET_TLSERVER				(QMAPI_TL_SERVER_BASE+0x0004)




#endif  //_QMAPI_DATATYPE_H



