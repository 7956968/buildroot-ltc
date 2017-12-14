
#ifndef __HI_MBUF_DEF_H__
#define __HI_MBUF_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef void*  HI_ADDR;
typedef HI_S32 MBUF_CHN;

/*MBUF payload type*/
typedef enum hiMBUF_PT_E
{
    VIDEO_KEY_FRAME = 1, //��Ƶ�ؼ�֡
    VIDEO_NORMAL_FRAME, //��Ƶ��ͨ֡
    AUDIO_FRAME, //��Ƶ֡
    MD_FRAME, //MD����
    MBUF_PT_BUTT
}MBUF_PT_E;


/*��Ƶslice����Ϣ�ر�ע�⣬һֻ֡��һ��slice�����slice������ʼҲ�ǽ���slice*/
#define CHECK_VIDEO_START_SLICE(x) ((x) & 0x01)/*һ֡����ʼslice*/
#define CHECK_VIDEO_NORMAL_SLICE(x) ((x) & 0x02) /*һ֡���м�slice*/
#define CHECK_VIDEO_END_SLICE(x) ((x) & 0x04) /*һ֡�����һ��slice*/

#define SET_VIDEO_START_SLICE(x) ((x) |= 0x01) /*һ֡����ʼslice*/
#define SET_VIDEO_NORMAL_SLICE(x) ((x) |= 0x02) /*һ֡���м�slice*/
#define SET_VIDEO_END_SLICE(x) ((x) |= 0x04) /*һ֡�����һ��slice*/
#define CLEAR_VIDEO_SLICE(x) ((x) = 0) /*�����Ƶslice��־*/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif
