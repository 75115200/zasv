//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：records.c
//___________________________________________________________
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "records.h"
#include "manager.h"
#include "odds.h"
#include "menu.h"

CONFIRM newRecord(STU *head,STU* tmp)
{
	CONFIRM confirm;
		STU *find[1];
		int findNum = 0;
	tmp->next = NULL;
	printf("________________________Save New Record_______________________\n");
	do
	{
		modify_name(tmp);

		modify_id(tmp);
		if (head != NULL)
		{
			printf("Checking whether id has been existed...\n");
			if (searchList(head,find,findNum,id,tmp->id) != NULL)
			{
				printf("ID has been existed yet!");
				getch();
				return quit;
			}
		}

		modify_gender(tmp);
		modify_math(tmp);
		modify_english(tmp);
		modify_c(tmp);
		tmp->total = tmp->math + tmp->english + tmp->c;
		printHeader();
		disRecord(tmp,0);
		printBoundary();
	}while( !(confirm = getConfirm() ) );

	if (confirm == quit)
		return quit;
	return yes;
}

void modify_name(STU *tmp)
{
	printf("\nPlease enter name.\n");
	myGets(tmp->name,NAME_ID_LEN-1);
}

void modify_id(STU *tmp)
{
	printf("\nPlease enter ID.\n");
	myGets(tmp->id,NAME_ID_LEN-1);
}

void modify_gender(STU *tmp)
{
	printf("\nPlease enter gender(f for female m for male).\n");
	tmp->gender = getchar();
	newLine();
	while( tmp->gender != 'f' && tmp->gender != 'F' &&
			tmp->gender != 'm' && tmp->gender != 'M')
	{
		printf("Undifined input.Please enter again.\n");
		tmp->gender = getchar();
		newLine();
	}
}

void modify_math(STU *tmp)
{
	tmp->math = getScore("Math",100);
}

void modify_english(STU *tmp)
{
	tmp->english = getScore("English",100);
}

void modify_c(STU *tmp)
{
	tmp->c = getScore("C",100);
}


int getScore(char *s,int max)
{
	int tmp ;

	printf("\nPlease enter %s score.\n",s);
	scanf("%d",&tmp);
	newLine();

	while(tmp <0 || tmp >max)
	{
		printf("Your input is meaningless.Please enter %s score again.\n",s);
		scanf("%d",&tmp);
		newLine();
	}

	return tmp;
}

void addNewRecordToList(STU *head,STU **tail)
{
	STU *tmp;
	tmp = (STU*)malloc(sizeof(STU));

	if ( newRecord(head,tmp) == quit)
	{
		free(tmp);
	}
	else
	{
		(*tail)->next = tmp;
		tmp->prev = *tail;
		*tail = (*tail)->next;
	}
}

void disRecord(STU* record,int n)
{
	char gender[7];

	if (record->gender == 'F' || record->gender =='f')
		strcpy(gender,"Female");
	else
		strcpy(gender,"Male");
	printf("||%-3d||%-10s||%-16s||%-7s||%-4d||%-7d||%-3d||%-5d||\n",n,record->name,record->id,gender,record->math,
		record->english,record->c,record->total);
}

void disAllRecords(STU *head)
{
	int n = 1;
	printHeader();
	
	while (head->next != NULL)
	{
		disRecord(head,n++);
		head = head->next;
		if (n % 21 == 0)
		{
			printf("Press any key to continue...\n");
			getch();
		}
	}
	disRecord(head,n);
	printBoundary();
	printf("All records shown.press any key to back.\n");
	getch();
}