//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：manager.c
//___________________________________________________________
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "database.h"
#include "manager.h"
#include "records.h"
#include "menu.h"
#include "odds.h"

void UI_main(STU **head,STU **tail)
{
	int choice = 1;
	do
	{
		while ( (choice = getOpt(mainMenu,MAINMENU_MAX) ) != 0)
		{
			switch (choice)
			{
			case 1:
				addNewRecordToList(*head,tail);	//completed
				addToDb(*tail);//save
				break;
			case 2:
				UI_dis(head,tail);				//completed
				break;
			case 3:
				UI_search(*head);			//undone
				break;
			case 4:
				help();					//completed
				printf("Press key to back to Main Menu\n");
				getch();
				break;
			case 5:
				about();					//completed
				printf("Press key to back to Main Menu\n");
				getch();
				break;
			default:
				break;
			}
			system("cls");
			logo();
		}
	}while (QuDo("Are you sure to Exit program?") == no);
}

void UI_dis(STU **head,STU **tail)
{
	int choice = 1;
	while ( (choice = getOpt(disMenu,DISMENU_MAX)) != 0) 
	{
		switch (choice)
		{
		case 1:
			disAllRecords(*head);
			break;
		case 2:
			sort(head,tail,name);
			disAllRecords(*head);
			break;
		case 3:
			sort(head,tail,gender);
			disAllRecords(*head);
			break;
		case 4:
			sort(head,tail,id);
			disAllRecords(*head);
			break;
		case 5:
			sort(head,tail,math);	
			disAllRecords(*head);
			break;
		case 6:
			sort(head,tail,english);
			disAllRecords(*head);
			break;
		case 7:
			sort(head,tail,c);
			disAllRecords(*head);
			break;
		case 8:
			sort(head,tail,total);
			disAllRecords(*head);
			break;
		default:
			break;
		}
		system("cls");
	}

}

void UI_search(STU *head)
{
	int choice;
	STU *found;
	while ( (choice = getOpt(searchMenu,SEARCHMENU_MAX) ) != 0)
	{
		switch (choice)
		{
		case 1:
			if ( (found = search(head,id)) != NULL)
				UI_search_sub(head,found);
			break;
		case 2:
			if ( (found = search(head,name)) != NULL)
				UI_search_sub(head,found);
			break;
		default:
			break;
		}
	}
}

void UI_search_sub(STU *head,STU *cur)
{
	int choice;
	 choice = getOpt(searchMenu_sub,SEARCHMENU_SUB_MAX);
	
	switch (choice)
	{
	case 1:
		modify(head,cur);
		break;
	case 2:
		deletNode(cur);
		break;
	default:
		break;
	}
}

/********************************************SORT********************************************/
void sort(STU **head,STU **tail,SORT by)
{
	int mark;
	STU *tmp;
	if ((*head)->next == NULL)
		return;
	
	printf("Sorting...\n");

	do
	{
		mark = 0;
		tmp =(*head);
	
		if(compare(*head,by))
		{
			exchangeHead(head);
			mark = 1;
		}
		tmp=(*head)->next;
		
		while (tmp->next != NULL)
		{
			if (compare(tmp,by))
			{
				exchangeNode(tmp);
				mark = 1;
			}
			else
				tmp = tmp->next;
		}

	}while (mark);
	tmp= *head;
	while ( tmp->next != NULL)
		tmp = tmp->next;
	*tail = tmp;
}

void exchangeNode(STU* tmp)
{
	STU *tmp_n = tmp->next;
	if ( tmp_n->next != NULL)
		(tmp_n->next)->prev = tmp;
	(tmp->prev)->next = tmp_n;
	tmp_n->prev = tmp->prev;
	tmp->next = tmp_n->next;
	tmp->prev = tmp_n;
	tmp_n->next = tmp;
}

void exchangeHeadCore(STU *head)
{
	STU *head_n = head->next;
	if (head_n->next != NULL)
		(head_n->next)->prev = head;
	head->next = head_n->next;
	head->prev = head_n;
	head_n->next = head;
	head_n->prev = NULL;
}

void exchangeHead(STU **head)
{
	exchangeHeadCore(*head);
	*head = (*head)->prev;
}

int compare(STU *tmp,SORT by)
{
	switch (by)
	{
	case name:
		if (strcmp(tmp->name,(tmp->next)->name) >0 )
			return 1;
		else
			return 0;
		break;
	case id:
		if (strcmp(tmp->id,(tmp->next)->id) >0)
			return 1;
		else
			return 0;
		break;
	case gender:
		if( (tmp->gender == 'm' || tmp->gender == 'M') &&
				( (tmp->next)->gender == 'f' || (tmp->next)->gender == 'F'))
			return 1;
		else
			return 0;
		break;
	case math:
		if ( (tmp->math) < ( (tmp->next)->math) )
			return 1;
		else
			return 0;
		break;
	case english:
		if ( (tmp->english) < ( (tmp->next)->english))
			return 1;
		else
			return 0;
		break;
	case c:
		if ( (tmp->c) < ( (tmp->next)->english))
			return 1;
		else 
			return 0;
		break;
	case total:
		if ( (tmp->total) < ( (tmp->next)->total))
			return 1;
		else
			return 0;
		break;
	default:
		printf("Program Can't Reach Here!\n");
	}
}

/******************************************Search************************************************/
STU *search(STU *head, SORT by)
{
	STU *find[10];
	STU *tmp = head;
	int findNum = 0;
	char str[NAME_ID_LEN];

	printf("Please enter %s .\n",by == name?"Name":"ID");
	myGets(str,NAME_ID_LEN);

	return searchList(tmp,find,findNum,by,str);
}

STU *searchList(STU *tmp,STU *find[] ,int findNum,SORT by,char *str)
{
	char choice;
	findNum = 0;
	while (tmp != NULL && findNum < 9 )
	{
		if (searchCmp(tmp,by,str))
			find[findNum++] = tmp;
		tmp = tmp->next;
	}

	if (findNum == 0)
	{
		printf("Not Found!\n");
		return NULL;
	}

	if (findNum == 9 && tmp != NULL && tmp->next != NULL)
		return searchFull(find,findNum,by,str);
	else
	{
		disFoundOuts(find,findNum);
		if (findNum !=1)
		{
			printf("%d resaults found.\n",findNum);
			printf("Enter letter to quit .\n"
				"Enter num to choose.\n");
			choice = getch();
			fflush(stdin);
			choice -= 48;//'0' == 48

			if (choice >0 && choice <findNum)
				return find[choice - 1];
			else
				return NULL;
		}
		else
		{
			printf("1 resault found.\n");
			choice = getch();
			fflush(stdin);
				return find[0];

		}
	}
}

STU *searchFull(STU *find[],int findNum,SORT by,char *str)
{
	char choice;
	disFoundOuts(find,findNum);
	printf("Program have find 9 records without reaching the end.\n"
			"Press Enter to contiune search,or enter num to choose,or enter letter to quit.\n");
	choice = getch();
	fflush(stdin);

	if ( choice == '\r')
		return searchList(find[findNum-1]->next,find,findNum,by,str);
	else
	{
		choice-=48;//'0' == 48
		if (choice >0 && choice < findNum)
		{
			disRecord(find[choice-1],0);
			return find[choice-1];
		}
		else
			return NULL;
	}
}

void disFoundOuts(STU *find[],int findNum)
{
	int i;
	printHeader();
	for(i=0;i<findNum;i++)
	{
		disRecord(find[i],i+1);
	}
	printBoundary();
}

int searchCmp(STU *cur,SORT by,char *str)
{
	switch (by)
	{
	case name:
		if (strcmp(cur->name,str) == 0)
			return 1;
		else
			return 0;
		break;
	case id:
		if (strcmp(cur->id,str) == 0)
			return 1;
		else
			return 0;
		break;
	default:
		printf("Program can't reach that far.\n");
		break;
	}
}

void modify(STU *head,STU *cur)
{
	int choice;
	if ( (choice = getOpt(modifyMenu,MODIFY_MAX) ) == 0)
		return;
	switch (choice)
	{
	case 1:
		newRecord(head,cur);
		break;
	case 2:
		modify_name(cur);
		break;
	case 3:
		modify_id(cur);
		break;
	case 4:
		modify_gender(cur);
		break;
	case 5:
		modify_math(cur);
		break;
	default:
		printf("Program can't reach here!\n");
	}
}

void deletNode(STU *cur)
{
	if (cur->next != NULL)
		(cur->next)->prev = cur->prev;
	(cur->prev)->next = cur->next;
	free(cur);
}
/**************************************************************************************************/
int getOpt(void (*menu)(void),int max)
{
	char choice;
	menu();
	printf("Please enter your choice.\n");
	choice = getch();
	fflush(stdin);

	choice-= 48;
	//change char Num into int Num
	while (choice < 0 || choice > max)
	{
		printf("Undifined choice!Please choose again.\n");
		choice = getch();
		fflush(stdin);
		choice-=48;
	}
	printf("You chose [%d].\n",choice);
	return choice;
}
