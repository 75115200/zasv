//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：odds.c
//___________________________________________________________
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "odds.h"
#include "manager.h"

/***********************************************************************************
@description:		get the left letters
@parament:		void
@return:			void
***********************************************************************************/
void newLine(void)
{
	char c;
	c=getchar();
	
	while (c != '\n') 
		c = getchar();
}

void myGets(char* s,unsigned length)
{
	unsigned i=0;
	char temp;

	temp=getchar();
	while (temp =='\n')
	{
		temp =getchar();
	}
	while (i < length && temp != '\n')
	{
		s[i++] = temp;
		temp = getchar();
	}
	if (temp != '\n')
		newLine();
	 s[i]='\0';
}

CONFIRM getConfirm(void)
{
	char confirm;
	printf("Is that right?(y for yes,n for no,q for quit)\n");
	confirm = getchar();
	newLine();

	while(confirm != 'y' && confirm != 'Y' && confirm != 'n'
		&& confirm != 'N' && confirm != 'q' && confirm != 'Q')
	{
		printf("Undifined choice.Please enter again.\n");
		confirm = getchar();
		newLine();
	}

	switch (confirm)
	{
	case 'y':
	case 'Y':
		return yes;
		break;
	case 'n':
	case 'N':
		return no;
		break;
	case 'q':
	case 'Q':
		return quit;
		break;
	}
}

CONFIRM QuDo(char *question)
{
	char confirm;
	printf("%s(Enter for yes others for no)\n",question);
	confirm = getch();
	fflush(stdin);

	printf("%c\n",confirm);
	switch (confirm)
	{
	case '\r':
		return yes;
		break;
	default:
		return no;
		break;
	}
}
