#ifndef _CODE_H_
#define _CODE_H_

#define MAX_LENGTH 256
#define MAX_BUF_SIZE 1024

/*****************Functions********************/
typedef struct func
{
	char name[MAX_LENGTH];
	int start;//函数的开始行数
	int end;//函数的结束行数
	int sps;//空行数
	int nt;//注释数
	struct func *next;
} FUNC;

FUNC *addNode(FUNC *p);
void freeNodes(FUNC *head);
void disFun(FUNC *head);
/******************************************/
/**********************Buffer*****************/
typedef struct
{
	char **buf;//通过newBuf 函数构造成二维字符数组
	int turn;//指明当前使用的是第几个字符数组
	int Len;//定义了Buf的长度
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