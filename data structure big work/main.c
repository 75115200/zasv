#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "code.h"

void pause();

int main(void)
{
	char fileName[MAX_LENGTH];
	BUF *B = newBuf(2);
	int num = 0;//行号
	int sps = 0,nt = 0;//分别记录空行号和注释行数
	FILE *fs;

	FUNC *head = (FUNC*)malloc(sizeof(FUNC));
	FUNC *cur = head;
	head->next = NULL;

	printf("请输入源文件名.\n");
	gets(fileName);
	if ((fs = fopen(fileName,"r")) == NULL)
	{
		printf("打开文件失败!\n");
		pause();
		exit(EXIT_FAILURE);
	}

	while (fgets(B->buf[B->turn],MAX_BUF_SIZE,fs) != NULL)
	{
		num++;
		if (KMP(B->buf[B->turn],"{") != -1 && isFunction(B->buf[getPre(B)]))
		{
			//printf("Found Function at line: %d\n",num-1);//Debuging
			if (aNewFunction(&num,&sps,&nt,B,fs,&cur) == 0)
			{
				printf("大括号匹配出错\n");
				pause();
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			nt+=isNote(B->buf[B->turn]);
			sps+=isSpace(B->buf[B->turn]);
		}
		bufNext(B);	
	}

	analyse(head,num,nt,sps);
	freeNodes(head);
	fclose(fs);
	pause();
	return 0;
}

void pause(void)
{
	fflush(stdin);
	getchar();
}