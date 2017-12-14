

/*
	����֧�ֵ� sensor �͵�ǰ�ķֱ���


*/
#ifndef __BASIC_H__
#define __BASIC_H__

#define TL_Q3_SC1135              31
#define TL_Q3_SC2135              32

typedef enum 
{
    DEVICE_MEGA_CIF = 0, /* 352 * 288 */
    DEVICE_MEGA_VGA,    /* 640 * 480 */
    DEVICE_MEGA_640x360, /* 640 * 360 */
    DEVICE_MEGA_D1, /* 720 * 576 */
    DEVICE_MEGA_IPCAM, /* 1280 * 720*/
    DEVICE_MEGA_1080P, /*1920 * 1080*/
    DEVICE_1CH_CIF,    /* 352 * 288 */
    DEVICE_MEGA_300M,  /**/
    DEVICE_MEGA_960P,  /* 1280 * 960*/
    DEVICE_IPCAM_AUTO,
    DEVICE_IPCAM_SVGA,
} DEVICE_TYPE_E;

/*
	��ȡ sensor �͵�ǰ���������ķֱ��ʣ�0 ���سɹ�������ֵʧ��

	sensor        [out]: TL_Q3_SC1135 ���� TL_Q3_SC2135
	manresolution [out]: DEVICE_TYPE_E һ��
	subresolution [out]: DEVICE_TYPE_E һ��
*/
int check_sensor_resolution(int *sensor, int *manresolution, int *subresolution);

#endif
