#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<openssl/rsa.h>
#include<openssl/pem.h>
#include<openssl/err.h>
#include "crypto.h"  
#include <openssl/crypto.h>
#include <openssl/rand.h>

//#define KEY_FROM_FILE 1

#ifdef  KEY_FROM_FILE	
//���ļ��ж�ȡ��˽Կ
static  char pubkey_path[]="/usr/share/crypto/id_rsa.pub";
static  char prikey_path[]="/usr/share/crypto/id_rsa.prv";
#else
//���ڴ��ж�ȡ˽Կ
//�ַ���ÿ��64���ַ�Ҫ��һ�����У�����ᱨ��Կ��ʽ����
char privateKey[]="-----BEGIN RSA PRIVATE KEY-----\n"\
"MIICXQIBAAKBgQC4v6XcPOIy+td8iCZNvlr0noSkozBe4M+h702IqDULS26qTXSF\n"\
"rr+voSif8jGB1HBcr5aBCcF1cPdvMNijGsRFD/2Xtd9mZhZP6PTPoERP+jzYfc/X\n"\
"TbTapEPRR26MN22EvXmp9QFWBvPuipDw9zCTYAswosIshK4zh0HDH72CewIDAQAB\n"\
"AoGAEtkKdMOJWCYbIctKDRhkcxxQ7/LuFl/dDuo5AL4YW0Sgz6MDRjgjuik42ch9\n"\
"oH8pz2ricduq7u5Nb/yNvWYXq7946Oi1DYsaikvVMDINot4+uZQfyqjKP5uAEdqK\n"\
"gZQANJsGk+klz875/n1q56ENnOW8m7f3Buo+ZQaA+PEK6IECQQDvJGOabKy0X6wV\n"\
"mLWcg6C8/Pfc7jZvAJYATuPjZb7P8KrBgfGAZu4NOT0/rWqk7J0sDwiKqxyOSSY1\n"\
"aGjAXktbAkEAxcWpXNje57KastV5/u9JAyR4JMXM9OCD061aCAzu2XGl3TbwI11W\n"\
"QX2G96v3MuXF1KoV//CCjQzJIYdIYEvvYQJBANcit3BfP+dtAlTTct6BFAOw2BMr\n"\
"QlEOB+PzFNSn3ccXzaYUDnzjHFlNGyrECeKg8qyGQbruQNxINlVpvoMA0W0CQHIl\n"\
"KB/XZ6ewlMq8nUG/V5OBu/n1U9rNrihA+CKHXF+R0VpA+A5hM4Ru77QIw47TwP+B\n"\
"/1qNtLu18mvwiZxSl2ECQQCWumQuZPMIth5YXcck4aP4xLdZeB1tevgTVmwi941R\n"\
"Ugb+w51uXDuysuIFN0OhL6S+rgMeZ0Sh+TTk5V/NaSFM\n"\
"-----END RSA PRIVATE KEY-----\n";


 char publicKey[]="-----BEGIN RSA PUBLIC KEY-----\n"\
"MIGJAoGBALi/pdw84jL613yIJk2+WvSehKSjMF7gz6HvTYioNQtLbqpNdIWuv6+h\n"\
"KJ/yMYHUcFyvloEJwXVw928w2KMaxEUP/Ze132ZmFk/o9M+gRE/6PNh9z9dNtNqk\n"\
"Q9FHbow3bYS9ean1AVYG8+6KkPD3MJNgCzCiwiyErjOHQcMfvYJ7AgMBAAE=\n"\
"-----END RSA PUBLIC KEY-----\n";
 
#endif
void hexprint(char *str,int len)
{
    int i=0;
    for(i=0;i<len;i++){
        printf("%s%02x%s",((i%16==0?"|":"")),*((unsigned char*)str+i),(((i+1)%16==0)?"|\n":" "));
    }
    if(i%16!=0)
        printf("|\n");
}
	

static int rsa_do_operation(RSA* rsa_ctx,char *instr,char* path_key,int inlen,char** outstr,int type)
{
    int rsa_len,num=-1;
    if(rsa_ctx == NULL || instr == NULL || path_key == NULL)
    {
        printf("input elems error,please check them!");
        return -1;
    }

    rsa_len=RSA_size(rsa_ctx);
    *outstr=( char *)malloc(rsa_len+1);
    memset(*outstr,0,rsa_len+1);
    switch(type){
        case RSA_PUB_ENC: //pub enc
        if(inlen == 0){
            perror("input str len is zero!");
            goto err;
        }
        num = RSA_public_encrypt(inlen,(unsigned char *)instr,(unsigned char*)*outstr,rsa_ctx,RSA_PKCS1_OAEP_PADDING);
        break;
		
        case RSA_PRV_DEC: //prv dec
        num = RSA_private_decrypt(inlen,(unsigned char *)instr,(unsigned char*)*outstr,rsa_ctx,RSA_PKCS1_OAEP_PADDING);        

	case RSA_PRV_ENC://prv enc
        if(inlen == 0){
            perror("input str len is zero!");
            goto err;
        }
        num = RSA_private_encrypt(inlen,(unsigned char *)instr,(unsigned char*)*outstr,rsa_ctx,RSA_PKCS1_OAEP_PADDING);
        break;
		
      case RSA_PUB_DEC: //prv dec
        num = RSA_public_decrypt(inlen,(unsigned char *)instr,(unsigned char*)*outstr,rsa_ctx,RSA_PKCS1_OAEP_PADDING);        
		
	 default:
       	 break;
    }

    if(num == -1)
    {
        printf("Got error on enc/dec!\n");
err:
        free(*outstr);
        *outstr = NULL;
        num = -1;
    }
    return num;
}
//ʹ�ù�Կ����
int rsa_pub_encrypt(char *str,char *path_key,char** outstr){
    RSA *p_rsa;
    FILE *file;
    int num;
    if((file=fopen(path_key,"r"))==NULL){
        perror("open key file error");
        return -1; 
    } 
#ifdef RSAPUBKEY
    if((p_rsa=PEM_read_RSA_PUBKEY(file,NULL,NULL,NULL))==NULL){
#else
    if((p_rsa=PEM_read_RSAPublicKey(file,NULL,NULL,NULL))==NULL){
#endif
        ERR_print_errors_fp(stdout);
        return -1;
    } 

    num = rsa_do_operation(p_rsa,str,path_key,strlen(str),outstr,RSA_PUB_ENC);
    RSA_free(p_rsa);
    fclose(file);
    return num;
}
//ʹ��˽Կ����
int rsa_prv_decrypt(char *str,char *path_key,int inlen,char** outstr){    
    RSA *p_rsa;
    FILE *file;
    int num;
        
    if((file=fopen(path_key,"r"))==NULL){
        perror("open key file error");
        return -1;
    }
    if((p_rsa=PEM_read_RSAPrivateKey(file,NULL,NULL,NULL))==NULL){
        ERR_print_errors_fp(stdout);
        return -1;
    }    
    num = rsa_do_operation(p_rsa,str,path_key,inlen,outstr,RSA_PRV_DEC);
    RSA_free(p_rsa);
    fclose(file);
    return num;
}

//ʹ��˽Կ����
int rsa_prv_encrypt(char *str,char *path_key,char** outstr){
    RSA *p_rsa;
    FILE *file;
    int num;
    if((file=fopen(path_key,"r"))==NULL){
        perror("open key file error");
        return -1; 
    } 

    if((p_rsa=PEM_read_RSAPrivateKey(file,NULL,NULL,NULL))==NULL){
        ERR_print_errors_fp(stdout);
        return -1;
    } 

    num = rsa_do_operation(p_rsa,str,path_key,strlen(str),outstr,RSA_PRV_ENC);
    RSA_free(p_rsa);
    fclose(file);
    return num;
}
//ʹ�ù�Կ����
int rsa_pub_decrypt(char *str,char *path_key,int inlen,char** outstr){    
    RSA *p_rsa;
    FILE *file;
    int num;
        
    if((file=fopen(path_key,"r"))==NULL){
        perror("open key file error");
        return -1;
    }
#ifdef RSAPUBKEY
    if((p_rsa=PEM_read_RSA_PUBKEY(file,NULL,NULL,NULL))==NULL){
#else
    if((p_rsa=PEM_read_RSAPublicKey(file,NULL,NULL,NULL))==NULL){
#endif  
        ERR_print_errors_fp(stdout);
        return -1;
    } 
    num = rsa_do_operation(p_rsa,str,path_key,inlen,outstr,RSA_PUB_DEC);

    RSA_free(p_rsa);
    fclose(file);
    return num;
}

//����RSA��Կ��˽Կ�ļ��ķ���
//openssl genrsa -out id_rsa.prv 1024
//openssl rsa -in id_rsa.prv -pubout -out id_rsa.pub
int create_rsa_pem(char *rsa_pub_file,char *rsa_prv_file)
{
	int ret=0;
	BIO *bpub, *bpri;
	RSA *pRSA=NULL;
		
    bpub = BIO_new_file(rsa_pub_file, "w");//��Կfile
    if (!bpub)
        printf("failed to create public bio file\n");
    bpri = BIO_new_file(rsa_prv_file, "w");
    if (!bpri)
        printf("failed to create private bio file\n");
    if (!bpub || !bpri) goto EXIT;

    printf("waiting.......\n");	
    pRSA = RSA_generate_key( 1024, RSA_F4, NULL, NULL);
    if (pRSA != NULL)
    {
        if (!PEM_write_bio_RSAPublicKey(bpub, pRSA))//PEM_write_bio_RSA_PUBKEY
        {
            printf("PEM_write_bio_RSAPublicKey: failed\n");
            goto EXIT;
        }
        //if (!PEM_write_bio_RSAPrivateKey(bpri, pRSA, EVP_aes_256_cbc(), NULL, 0, NULL, NULL))
        if (!PEM_write_bio_RSAPrivateKey(bpri, pRSA, NULL, NULL, 0, NULL, NULL))//��ʱ��������
        {
            printf("PEM_write_bio_PrivateKey: failed\n");
            goto EXIT;
        }
        ret =1;
    }
    printf("create_rsa_pem complete.\n");		
EXIT:
    if (bpub)
        BIO_free(bpub);
    if (bpri)
        BIO_free(bpri);
    if (pRSA) RSA_free(pRSA);
    return ret;
}	
#ifdef  KEY_FROM_FILE	
RSA * createRSAWithFilename(char * filename,int public)
{
    RSA *p_rsa;

    printf("use file to get key.\n");
    FILE * file = fopen(filename,"r");
    if(file == NULL)
    {
        printf("Unable to open file %s \n",filename);
        return NULL;    
    }
    
    if(public == PUBLIC_KEY)
    {
        p_rsa = PEM_read_RSAPublicKey(file,NULL,NULL,NULL);//PEM_read_RSA_PUBKEY
    }
    else
    {
        p_rsa = PEM_read_RSAPrivateKey(file,NULL,NULL,NULL);
    }
    fclose(file);
	
    return p_rsa;
}

#else
RSA * createRSA( char * key,int public)
{
    RSA *rsa= NULL;
    BIO *keybio ;

    printf("use code to get key.\n");
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio==NULL)
    {
        printf( "Failed to create key BIO\n");
        return 0;
    }
    if(public == PUBLIC_KEY)
    {
        rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa,NULL, NULL);
    }
    else
    {
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa,NULL, NULL);
    }
    if(rsa == NULL)
    {
        printf( "Failed to create RSA\n");
    }
    BIO_set_close(keybio, BIO_CLOSE);  
    BIO_free(keybio); 	
    return rsa;
}
#endif

//��֤�����ù�Կ���н���
int rsa_verify(char *text_data, char* sign_data, int sign_len)
{
    RSA *p_rsa;
#ifdef  KEY_FROM_FILE	
     p_rsa = createRSAWithFilename(pubkey_path,PUBLIC_KEY);
#else
     p_rsa = createRSA(publicKey, PUBLIC_KEY);
#endif
     if(p_rsa == NULL)
     {
	   return 0;
     }
    if(!RSA_verify(NID_md5,(unsigned char*)text_data,strlen(text_data),(unsigned char*)sign_data,sign_len,p_rsa))
    {
        return 0;
    }
    RSA_free(p_rsa);
    return 1;
}

//ǩ������������˽Կ���м���
int rsa_sign(char *text_data,  int text_len, char* sign_data)
{
    RSA *p_rsa;
    unsigned int out_len = 0;
	
#ifdef  KEY_FROM_FILE		
	p_rsa = createRSAWithFilename(prikey_path,PRIVATE_KEY);
#else
	p_rsa=createRSA(privateKey, PRIVATE_KEY);
#endif
    if(p_rsa == NULL)
	   return 0;
    if(!RSA_sign(NID_md5,(unsigned char*)text_data,text_len,(unsigned char*)sign_data,&out_len,p_rsa))
    {
        return 0;
    }
    printf("get sign data len is %d.\n",out_len);
    RSA_free(p_rsa);

    return 1;
}
/*
paramter:
out:The output buffer for signed data  //data
in:The input buffer for unsigned data  //zaiyao
len:The length of unsigned data

Return Value
0 if successful, -1 if failed
*/
int crypto_sign_data(char *out, char *in, int len)
{
    if(!rsa_sign(in,len,out))
    {
    	printf("sign error\n");
    	return -1;
    }
    printf("sign ok\n");	
    return 0;
}

/*
crypto_verify_data
paramter:
text:need verify data  
sign:signed data  

Return Value
0 if successful, -1 if failed
*/
int crypto_verify_data(char *text, char *sign)
{
    if(!rsa_verify(text,sign,strlen(sign)))
    {
    	printf("verify error\n");
    	return -1;
    }
    printf("verify ok\n");
    return 0;	
}

