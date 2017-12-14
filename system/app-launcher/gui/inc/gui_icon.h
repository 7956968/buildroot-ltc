#ifndef __GUI_ICON_H_
#define __GUI_ICON_H_

#define SECONDARYDC_ENABLED 1
typedef enum
{
    //video
    //top left
    MWV_MODE,
    MWI_VIDEO_BEGIN = MWV_MODE,
    MWV_RESOLUTION,
	MWV_PREVIEW_MODE,
	MWV_LOOP,
	MWV_LOCKED,

    //top right
    MWV_WIFI,

	//internal left
	MWV_LAPSE,

	//internal right
    MWV_BATTERY,
	
	//bottom left
    MWV_DATETIME,

	//bottom right
	MWV_VIDEO_MODE,
    MWI_VIDEO_END = MWV_VIDEO_MODE,

    //photo
    //top left
    MWP_MODE,
    MWI_PHOTO_BEGIN = MWP_MODE,
    MWP_RESOLUTION,
	MWP_PREVIEW_MODE,
	MWP_SEQUENCE,

	//top right
    MWP_WIFI,
	
	//internal left
	MWP_COUNT_LAPSE,
	
	//internal right
	MWP_BATTERY,

	//bottom left
    MWP_DATETIME,

	//bottom right
	MWP_PHOTO_MODE,
    MWI_PHOTO_END = MWP_PHOTO_MODE,
	MWI_MAX = MWI_PHOTO_END,

} MWI_TYPE;



typedef enum
{
    IC_VIDEO = 1,
    IC_VIDEO_RECORDING,
    IC_VIDEO_FOCUS,
    IC_VIDEO_FOLDER,
    IC_VIDEO_1MIN,
    IC_VIDEO_3MIN,
    IC_VIDEO_5MIN,
    IC_VIDEO_10MIN,
    IC_LOCKED,
    IC_VIDEO_LOCKED_FOLDER,
    IC_PHOTO,
    IC_PHOTO_RECORDING,
    IC_PHOTO_FOCUS,
    IC_PHOTO_FOLDER,
    IC_PHOTO_SEQUENCE,
    IC_PHOTO_TIMER_2S,
    IC_PHOTO_TIMER_5S,
    IC_PHOTO_TIMER_10S,
    IC_PLAYBACK_MODE,
    IC_PLAYBACK_FOLDER,
    IC_GRID,
    IC_PLAY,
    IC_PAUSE,
    IC_PREV,
    IC_NEXT,
    IC_REWIND,
    IC_FAST_FORWARD,
    IC_VOLUME,
    IC_VOLUME_MUTE,
    IC_VOLUME_MAX,
    IC_SETUP,
    IC_SETUP_MODE,
    IC_WIFI,
    IC_BATTERY_LOW,
    IC_BATTERY_MEDIUM,
    IC_BATTERY_HIGH,
    IC_BATTERY_FULL,
    IC_BATTERY_LOW_CHARGING,
    IC_BATTERY_MEDIUM_CHARGING,
    IC_BATTERY_HIGH_CHARGING,
    IC_BATTERY_FULL_CHARGING,
    IC_WDR,
    IC_AUDIO_RECORD,
    IC_AUDIO_MUTE,
    IC_EV_NEGATIVE_2P0,
    IC_EV_NEGATIVE_1P5,
    IC_EV_NEGATIVE_1P0,
    IC_EV_NEGATIVE_0P5,
    IC_EV_ZERO,
    IC_EV_POSITIVE_0P5,
    IC_EV_POSITIVE_1P0,
    IC_EV_POSITIVE_1P5,
    IC_EV_POSITIVE_2P0,
    IC_QUALITY_FINE,
    IC_QUALITY_NORMAL,
    IC_QUALITY_ECONOMY,
    IC_WB_AUTO,
    IC_WB_DAYLIGHT,
    IC_WB_CLOUDY,
    IC_WB_TUNGSTEN,
    IC_WB_FLUORESCENT,
    IC_ISO_AUTO,
    IC_ISO_100,
    IC_ISO_200,
    IC_ISO_400,
    IC_ISO_800,
    IC_IR_DAYTIME,
    IC_IR_NIGHT,
    IC_HEADLAMP,
    IC_ANTI_SHAKING,
    IC_SETTINGS,
    IC_EXIT,
    IC_BACK,
    IC_BRIGHTNESS,
    IC_DATE_TIME,
    IC_DELETE,
    IC_DELETED,
    IC_DELETING,
    IC_MORE,
    IC_CARD,
    IC_CAMERA_BUSY,
    IC_DEFAULT_THUMB,
    IC_SHUTDOWN,
    IC_REVERSE_IMAGE,
	
	//add new
	IC_CARDV,
	IC_CARDV_RECORDING,
	IC_VIDEO_PANORAMA_ROUND,
	IC_VIDEO_PANORAMA_EXPAND,
	IC_VIDEO_TWO_SEGMENT,
	IC_VIDEO_THREE_SEGMENT,
	IC_VIDEO_FOUR_SEGMENT,
	IC_VIDEO_ROUND,
	IC_VIDEO_VR,
	IC_VIDEO_TIMELAPSED_1S,
	IC_VIDEO_TIMELAPSED_2S,
	IC_VIDEO_TIMELAPSED_3S,
	IC_VIDEO_TIMELAPSED_5S,
	IC_VIDEO_TIMELAPSED_10S,
	IC_VIDEO_HIGH_SPEED,
	IC_VIDEO_2448_30FPS,
	IC_VIDEO_1080P_60FPS,
	IC_VIDEO_1080P_30FPS,
	IC_VIDEO_720P_30FPS,
	IC_PHOTO_16M,
	IC_PHOTO_10M,
	IC_PHOTO_8M,
	IC_PHOTO_4M,
	IC_PHOTO_PANORAMA_ROUND,
	IC_PHOTO_PANORAMA_EXPAND,
	IC_PHOTO_TWO_SEGMENT,
	IC_PHOTO_THREE_SEGMENT,
	IC_PHOTO_FOUR_SEGMENT,
	IC_PHOTO_ROUND,
	IC_PHOTO_VR,
	IC_PHOTO_AUTO_3S,
	IC_PHOTO_AUTO_10S,
	IC_PHOTO_AUTO_15S,
	IC_PHOTO_AUTO_20S,
	IC_PHOTO_AUTO_30S,
    IC_MAX, 
} ICON_ENUM;
#endif