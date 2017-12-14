
#ifndef __MAIN_H__
#define __MAIN_H__

#define IQ_TEST_DATA 1 /* �R�O */
#define MAX_DATA_BUFSZ 1024 * 1024 /* �����ƾڽw�Ĥj�p */

typedef struct
{
    int cmd; /* �R�O */
    int len; /* �t���ƾڪ��סA���]�Aiq_test_msg_t�Y���� */
    int xorcheck; /* �Y���� */
} iq_test_msg_t;

#define IQ_TEST_MSG_XOR(msg) (msg.cmd ^ msg.len)
#define SET_IQ_TEST_MSG(msg, msgcmd, datalen) do { msg.cmd=msgcmd;msg.len=datalen;msg.xorcheck=IQ_TEST_MSG_XOR(msg); } while (0)

/* �ƾڦ^�ը�ơApuser�������P���Τ�Apbuf��ܱ����쪺�ƾڦs��w�İϡAlen��ܼƾڪ��� */
/* �Ұʰ�ť�᤹�\�h�ӥΤ�s���Apuser��ܸӼƾڹ������Τ�s�� */
typedef void (*data_pcallback)(void* puser, void* pbuf, int len);

/* �ҰʪA�ȡA�b���w�����ݤf��ť */
int iq_test_start(unsigned short ipport);

/* ����A�ȡA����귽 */
int iq_test_stop(void);

/* �]�m�ƾڦ^�ը�� */
int iq_test_set_callback(data_pcallback pcallback);

/* �ƾڦ^�ǡApuser��data_pcallback������puser�ѼơA�p�Gpuser���Ū�ܵo�e���Ҧ��w�s���Τ� */
int iq_test_data_send(void* puser, void* pbuf, int len);

#endif // #ifndef __MAIN_H__
