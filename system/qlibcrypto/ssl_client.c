#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "crypto.h" 

#define MAXBUF 1024

void ShowCerts(SSL * ssl)
{
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl);
    if (cert != NULL) {
        printf("[client]subject info:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("[client]certs is :%s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("[client]wrote by%s\n", line);//�䷢��: 
        free(line);
        X509_free(cert);
    } else
        printf("[client]no certs infomation\n");
}
/************���ڱ��ĵ�********************************************
*filename: ssl-client.c
*purpose: ��ʾ���� OpenSSL ����л��� IP��� SSL ����ͨѶ�ķ��������ǿͻ�������
*wrote by: zhoulifa(zhoulifa@163.com) ������(http://zhoulifa.bokee.com)
Linux������ Linux֪ʶ������ SOHO�� ������ ���ó�C����
*date time:2007-02-02 20:10
*Note: �κ��˿������⸴�ƴ��벢������Щ�ĵ�����Ȼ���������ҵ��;
* ������ѭGPL
*Thanks to:Google
*Hope:ϣ��Խ��Խ����˹����Լ���������Ϊ��ѧ������չ����
* �Ƽ�վ�ھ��˵ļ���Ͻ������죡��л�п�Դǰ���Ĺ��ף�
*********************************************************************/
int main(int argc, char **argv)
{
    int sockfd, len;
    struct sockaddr_in dest;
   // char buffer[MAXBUF + 1];
    SSL_CTX *ctx;
    SSL *ssl;
    char text[MAXBUF];
    char sign[MAXBUF];//


    if (argc != 3) {
        printf("[client]paramter is error,\n\t\t%s IP port\n\t example\t%s 127.0.0.1 80\n�˳���������ĳ�� IP ��ַ�ķ�����ĳ���˿ڽ������ MAXBUF ���ֽڵ���Ϣ",
             argv[0], argv[0]);
        exit(0);
    }
    memset((char*)text, 0 ,MAXBUF);
    memset((char*)sign, 0 ,MAXBUF);
	
    /* SSL ���ʼ�����ο� ssl-server.c ���� */
    SSL_library_init();
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    ctx = SSL_CTX_new(SSLv23_client_method());
    if (ctx == NULL) {
        ERR_print_errors_fp(stdout);
        exit(1);
    }

    /* ����һ�� socket ���� tcp ͨ�� */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket");
        exit(errno);
    }
    printf("[client]socket created\n");

    /* ��ʼ���������ˣ��Է����ĵ�ַ�Ͷ˿���Ϣ */
    bzero(&dest, sizeof(dest));
    dest.sin_family = AF_INET;
    dest.sin_port = htons(atoi(argv[2]));
    if (inet_aton(argv[1], (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
        perror(argv[1]);
        exit(errno);
    }
    printf("[client]address created\n");

    /* ���ӷ����� */
    if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
        perror("Connect ");
        exit(errno);
    }
    printf("[client]server connected\n");

    /* ���� ctx ����һ���µ� SSL */
    ssl = SSL_new(ctx);
    SSL_set_fd(ssl, sockfd);
    /* ���� SSL ���� */
    if (SSL_connect(ssl) == -1)
        ERR_print_errors_fp(stderr);
    else {
        printf("[client]Connected with %s encryption\n", SSL_get_cipher(ssl));
        ShowCerts(ssl);
    }

    strcpy(text, "0123456789876543210");
    /* ����Ϣ�������� */
    len = SSL_write(ssl, text, strlen(text));
    if (len < 0)
    {
        printf("[client]message '%s' send fail!error code is %d,error message is '%s'\n",text, errno, strerror(errno));
    }
    else
    {
        printf("[client]message '%s' send success, send %d bytes\n", text, len);

	    /* ���նԷ�����������Ϣ�������� MAXBUF ���ֽ� */
	   // bzero(sign, MAXBUF + 1);
	    /* ���շ�����������Ϣ */
	    len = SSL_read(ssl, sign, MAXBUF);
	    if (len > 0)
	    {
	        printf("[client]receive message success:'%s',%d bytes data.\n",sign, len);
		    if(crypto_verify_data(text,sign)!=0)
		    {
		 //   	printf("verify error\n");
		    	return -1;
		    }	
	    }
	    else {
	        printf("[client]message receive fail,error message is %d,error info is '%s'\n\n",errno, strerror(errno));
	        goto finish;
	    }

    }
  finish:
    /* �ر����� */
    SSL_shutdown(ssl);
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
    return 0;
}
 

