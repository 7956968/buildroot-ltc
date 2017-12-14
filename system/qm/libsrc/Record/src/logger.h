#ifndef __LOGGER_H__
#define __LOGGER_H__


/*******************************************************/
/* ��غ�ͽṹ����                                    */
/*******************************************************/

#define LOG_TEXT_LEN 36
#define LOG_FILE_SIZE (1024*48)
#define CLR_PAGE_SIZE (56*48)

typedef struct {
	unsigned char log_type; /* ��ͨ���ƻ������졢������ */
	unsigned char log_opt; /* 1<<0 ¼�� 1<<1 ץͼ*/
	unsigned char log_ch; /* ͨ�� */
	unsigned char cres; /* ����Ϊ0 */
	time_t log_time; /* ��¼ʱ�� */
	char log_text[LOG_TEXT_LEN]; /* ��־���� */
	int ires;
} log_content_t;

typedef struct {
	unsigned char log_type; /* �������� */
	unsigned char log_ch;
	unsigned char log_opt;
	unsigned char cres;
	time_t log_begin; /* ��ʼʱ�� */
	time_t log_end; /* ����ʱ�� */
} log_search_t;

typedef struct {
	int log_pos;
	FILE* log_pf;
	int log_mode;
	char log_name[LOG_TEXT_LEN];
}log_head_t;

/*******************************************************/
/* �����ر�˵��,��������LIB_OK��ʾ�ɹ�,LIB_ERR��ʾʧ�� */
/*******************************************************/

/* ָ����־�洢·������ʼ�� */

log_head_t* log_init(const char *logpath, int mode);

/* ����ʼ�����˳� */
int log_exit(log_head_t *head);

/* д����־��¼������д���¼�� */
int log_write(log_head_t *head, log_content_t *pcontent, int num);

/*��־��¼��ѯ�����ط�������������*/
unsigned int log_inquery(log_head_t *head, log_search_t *psearch);

/* ��־��¼���������ط����������ܼ�¼�� */
int log_search(log_head_t *head, log_search_t *psearch);

int log_read(log_head_t *head, log_search_t *psearch, log_content_t *pcont, int num);

/* ���������־��¼ */
int log_clear(log_head_t *head);

#endif /* __LOGGER_H__ */
