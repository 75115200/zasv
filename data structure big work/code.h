#ifndef _CODE_H_
#define _CODE_H_

#define MAX_LENGTH 256
#define MAX_BUF_SIZE 1024

/*****************Functions********************/
typedef struct func
{
	char name[MAX_LENGTH];
	int start;//�����Ŀ�ʼ����
	int end;//�����Ľ�������
	int sps;//������
	int nt;//ע����
	struct func *next;
} FUNC;

FUNC *addNode(FUNC *p);
void freeNodes(FUNC *head);
void disFun(FUNC *head);
/******************************************/
/**********************Buffer*****************/
typedef struct
{
	char **buf;//ͨ��newBuf ��������ɶ�ά�ַ�����
	int turn;//ָ����ǰʹ�õ��ǵڼ����ַ�����
	int Len;//������Buf�ĳ���
}BUF;
BUF* newBuf(int len);
int bufNext(BUF *B);
int getPre(BUF *B);
/*****************************************/

int isSpace(char s[]);
int isNote(char s[]);
int isFunction(char s[]);

int aNewFunction(int *num,int *sps,int *nt,BUF *B,FILE *fs,FUNC **cur);
void catFuncName(char s[],char name[]);
int KMP(char s[],char t[]);

void analyse(FUNC *head,int num,int nt,int sps);
#endif