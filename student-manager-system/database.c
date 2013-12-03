//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：database.c
//___________________________________________________________
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "database.h"
#include "manager.h"
#include "records.h"
#include "menu.h"
#include "odds.h"

void initDb(STU **head,STU **tail)
{
	FILE *fr = NULL;
	int recordNum;
	int firstUse = 0;

	if ( (fr = fopen(DB_PATH,"rb")) == NULL)
		firstUse = 1;
	else 
	{
		fseek(fr,0,SEEK_END);
		if ((ftell(fr) % sizeof(STU) ) !=0 || ftell(fr) == 0)
			firstUse = 1;
		fclose(fr);
	}

	if (firstUse)
	{
		printf("Progran detected you are using this program for \nthe first time.\n"
			"Please save new record first.\n");
		*tail = (STU*) malloc(sizeof(STU));
		
		if (newRecord(*head,*tail) == quit)
		{
			free(*tail);
			printf("You choose to quit.\n");
			printf("Press \"Enter\" to exit program\n");
			getchar();
			exit(EXIT_FAILURE);
		}
		
		*head = *tail;
	}
	else
	{
		recordNum = loadDb(head,tail);
		
		printBoundary();
		if ( recordNum == 1)
			printf("There is [  1] record in the database.\n");
		else
			printf("There are [%3d] records in the database.\n",recordNum);

		printBoundary();
		printf("\n");
	}
}

int loadDb(STU **head,STU **tail)
{
	FILE *fr = NULL;
	int i = 1;
	STU *tmp = (STU*)malloc(sizeof(STU));
	
	if ( (fr = fopen(DB_PATH,"rb") ) == NULL)
	{
		printf("System failed!\nPress \"Enter\" to exit\n");
		getchar();
		exit(EXIT_FAILURE);
	}
	
	fread(tmp,sizeof(STU),1,fr);
	tmp->prev = NULL;
	*head = tmp;

	tmp->next = (STU*)malloc(sizeof(STU));
	while( fread(tmp->next,sizeof(STU),1,fr) !=0)
	{
		(tmp->next)->prev = tmp;
		 tmp = tmp->next;
		 tmp->next = (STU*)malloc(sizeof(STU));
		 ++i;
	}

	fclose(fr);
	free(tmp->next);
	tmp ->next = NULL;

	*tail = tmp;
	return i;
}

void saveDb(STU* head)
{
	FILE *fw;

	if( QuDo("\nSave database before exit?") ==no)
		return;

	fw = fopen(DB_PATH,"wb");
	printf("\nSaving Database...\n");
	while(head->next != NULL)
	{
		fwrite(head,sizeof(STU),1,fw);
		head = head ->next;
	}
	fwrite(head,sizeof(STU),1,fw);
	fclose(fw);
	printf("Saving Database Done!\n");
}

void addToDb(STU *tail)
{
	FILE *fw;
	fw = fopen(DB_PATH,"ab");
	fwrite(tail,sizeof(STU),1,fw);
	fclose(fw);
}

void freeNodes(STU *head)
{
	STU *tmp = head;
	printf("\nFreeing All Nodes...\n");
	while(tmp->next != NULL)
	{
		tmp = tmp->next;
		free(tmp->prev);
	}
	free(tmp);
	printf("Freeing Nodes Done!\n");
}