#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

void getNextval(char t[],int nextval[]);

/**************About Buf*********************/
BUF* newBuf(int len)
{
	int i;
	BUF *B = (BUF*)malloc(sizeof(BUF));
	B->Len = len;
	B->buf = (char**)malloc(sizeof(char*)*len);
	
	for (i = 0;i < len;i++)
	{
		B->buf[i] = (char *)malloc(sizeof(char)*MAX_BUF_SIZE);
		B->buf[i][0] = '\0';
	}
	B->turn = 0;
	return B;
}

int bufNext(BUF *B)
{
	B->turn = (B->turn + 1)%B->Len;
	return B->turn;
}

int getPre(BUF *B)
{

	return (B->turn + B->Len +1) % B->Len;
}
/********************************************/
FUNC *addNode(FUNC *p)
{
	p->next = (FUNC*)malloc(sizeof(FUNC));
	p->next->nt = p->next->sps = 0;
	p->next->next = NULL;
	return p->next;
}

void freeNodes(FUNC *head)
{
	FUNC *tmp;
	if (head->next != NULL)
	{
		tmp = head;
		head = head->next;
	}
	else
	{
		free(head);
		return;
	}

	while (head->next != NULL)
	{
		free(tmp);
		tmp = head;
		head = head->next;
	}
}
/*********************************************/
int isSpace(char s[])
{
	int l = strlen(s);
	int i;


	for(i = 0;i < l;i++)
	{
		if (s[i] != ' ' && s[i] != '\n' &&s[i] != '\t')
			return 0;
	}
	return 1;
}

int isNote(char s[])
{
	int l = strlen(s);
	int i = 0;

	while (s[i] == ' ' || s[i] == '\t')
		i++;

	if (i < l - 1 && s[i] == '/' && s[i+1] == '/')
		return 1;
	return 0;
}

int isFunction(char s[])
{
	if (KMP(s,"(") != -1 && KMP(s,"(") < KMP(s,")") &&
		KMP(s,"while") == -1 && KMP(s,"if") == -1 && KMP(s,"switch"))
		return 1;
	return 0;
}

void catFuncName(char s[],char name[])
{
	int i = 0,j = 0;
	i = strlen(s) -1;
	while (s[i] == ' ')
		i--;
	while (s[i] != '(')
		i--;
	while (s[i] == ' ')
		i--;
	while (s[i] != ' ' && s[i] != '*')
		i--;
	i++;
	while (s[i] != ' ' && s[i] != '(' && i > -1)
		name[j++] = s[i++];
	name[j] = '\0';
}

int aNewFunction(int *num,int *sps,int *nt,BUF *B,FILE *fs,FUNC **cur)
{
	int n = 1;//控制大括号匹配
	*cur = addNode(*cur);
	catFuncName(B->buf[getPre(B)],(*cur)->name);
	(*cur)->start = *num - 1;
	
	while (n != 0)
	{
		bufNext(B);
		(*num)++;
		//printf("Current Line :%d||n = %d\n",*num,n);//Debuging
		if (fgets(B->buf[B->turn],MAX_BUF_SIZE,fs) == NULL)
		{
			//printf("源文件括号匹配出错\n");
			return 0;
		}

		if (isSpace(B->buf[B->turn]))
		{
			(*cur)->sps ++;
			(*sps)++;
		}
		if (isNote(B->buf[B->turn]))
		{
			(*cur)->nt ++;
			(*nt)++;
		}
		
		if (KMP(B->buf[B->turn],"{") != -1)
			n++;
		if (KMP(B->buf[B->turn],"}") != -1)
			n--;
	}
	(*cur)->end = *num;
	return 1;
}

/********************KMP**********************/
void getNextval(char t[],int nextval[])
{
	int j = 0,k = -1;
	int tlen= strlen(t);
	nextval[0] = -1;

	while (j < tlen)
	{
		if (k == -1 || t[j] == t[k])
		{
			j++;
			k++;
			if (t[j] != t[k])
				nextval[j] = k;
			else
				nextval[j] = nextval[k];
		}
		else
			k = nextval[k];
	}
}

int KMP(char s[],char t[])
{
	int nextval[MAX_BUF_SIZE];
	int i = 0,j = 0;
	int slen = strlen(s),tlen = strlen(t);
	
	getNextval(t,nextval);
	while (i < slen && j < tlen)
	{
		if (j == -1 || s[i] == t[j])
		{
			i++;
			j++;
		}
		else
			j = nextval[j];
	}
	
	if (j >= tlen)
		return (i-tlen);
	else
		return -1;
}

/****************Analyse Statistics***********/
void analyse(FUNC *head,int num,int nt,int sps)
{
	FUNC *tmp = head;
	int t = 0;//函数总长度,然后变为平均长度
	double u;
	int fn = 0;//函数个数
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		t += tmp->end - tmp->start + 1;
		fn++;
	}

	printf("\n_______________________统计报告___________________________\n");
	printf("总行数： %d\t注释行数：%d  空行数：%d  函数个数：%d\n\n",num,nt,sps,fn);
	if (fn != 0)
	{
		t = t/fn;
		printf("代码(函数平均长度)：%d\n评级：",t);
		if ( t > 9 && t < 16)
			printf("A级\n\n");
		else if ((t > 15 && t < 21) || (t > 7 && t < 10))
			printf("B级\n\n");
		else if ((t > 4 && t< 8) || (t> 20 && t< 25))
			printf("C级\n\n");
		else 
			printf("D级\n\n");
	}

	printf("注释(占总行数比率)： %.2lf%%\n评级：",100*(u = (double)nt/num));
	if ( u > 0.15 && u < 0.25)
		printf("A级\n\n");
	else if ((u > 0.1 && u < 0.14) || (u > 0.26 && u < 0.3))
		printf("B级\n\n");
	else if ((u > 0.05 && u < 0.09) || (u > 0.31 && u < 0.35))
		printf("C级\n\n");
	else 
		printf("D级\n\n");

	printf("空行(占总行数比率): %.2lf%%\n评级：",100*(u = (double)sps/num));
	if ( u > 0.15 && u < 0.25)
		printf("A级\n\n");
	else if ((u > 0.1 && u < 0.14) || (u > 0.26 && u < 0.3))
		printf("B级\n\n");
	else if ((u > 0.05 && u < 0.09) || (u > 0.31 && u < 0.35))
		printf("C级\n\n");
	else 
		printf("D级\n\n");
	if (fn != 0)
	disFun(head);
	printf("__________________________________________________________\n");
}

void disFun(FUNC *head)
{
	int n = 0;
	printf("________________________详细函数信息______________________\n");
	printf("%5s|%20s|%5s|%6s|%6s|%8s|\n","序号","函数名   ","长度","注释数","空行数","起始行号");
	while (head->next != NULL)
	{
		head = head->next;
		printf("%5d|%-20s|%5d|%6d|%6d|%3d/%-4d|\n",++n,head->name,head->end - head->start +1,
			head->nt,head->sps,head->start,head->end);

	}
}