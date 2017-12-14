
#ifndef __IQ_TEST_H__
#define __IQ_TEST_H__

#define IQ_TEST_DATA 1 /* ���� */
#define MAX_DATA_BUFSZ 1024 * 1024 /* �������ݻ����С */

typedef struct {
    int cmd; /* ���� */
    int len; /* �������ݳ��ȣ�������iq_test_msg_tͷ���� */
    int xorcheck; /* ͷУ�� */
} iq_test_msg_t;

#define IQ_TEST_MSG_XOR(msg) (msg.cmd ^ msg.len)
#define SET_IQ_TEST_MSG(msg, msgcmd, datalen) do { msg.cmd=msgcmd;msg.len=datalen;msg.xorcheck=IQ_TEST_MSG_XOR(msg); } while (0)

/* ���ݻص�������puser��Ӧ��ͬ���û���pbuf��ʾ���յ������ݴ�Ż�������len��ʾ���ݳ��� */
/* �����������������û����ӣ�puser��ʾ�����ݶ�Ӧ���û����� */
typedef void (*data_pcallback)(void *puser, void *pbuf, int len);

/* ����������ָ������˿����� */
int iq_test_start(unsigned short ipport);

/* ֹͣ�����ͷ���Դ */
int iq_test_stop(void);

/* �������ݻص����� */
int iq_test_set_callback(data_pcallback pcallback);

/* ���ݻش���puserΪdata_pcallback��Ӧ��puser���������puserΪ�ձ�ʾ���͸������������û� */
int iq_test_data_send(void *puser, void *pbuf, int len);

#endif // #ifndef __IQ_TEST_H__
