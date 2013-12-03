//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：manager.h
//___________________________________________________________
#ifndef MANAGER_H
#define MANAGER_H

#define DB_PATH ".\\Database.DB"
#define NAME_ID_LEN 32
#define MAINMENU_MAX 5
#define DISMENU_MAX 8
#define SEARCHMENU_MAX 2
#define SEARCHMENU_SUB_MAX 2
#define MODIFY_MAX 5

struct student
{
	char name[NAME_ID_LEN];
	char id[NAME_ID_LEN];
	char gender;
	int math;
	int english;
	int c;
	int total;
	struct student* next;
	struct student* prev;
};
typedef struct student STU;
//sizeof(STU) == 

enum confirm{no,quit,yes};
typedef enum confirm CONFIRM;

enum sort{name,id,gender,math,english,c,total};
typedef enum sort SORT;

// add by xinyi
struct Database
{
	STU* head;
	STU* tail;
};

/*****************************Functions List**********************************/

void UI_main(STU **head,STU**tail);
void UI_dis(STU *head,STU **tail);
void UI_search(void);
void UI_search_sub(STU *head,STU *cur);
int getOpt(void (*menu)(void),int max);
//___________________SEARCH__________________//
STU *search(STU *head, SORT by);
STU * searchList(STU *tmp,STU *find[] ,int findNum,SORT by,char *str);
STU *searchFull(STU *find[],int findNum,SORT by,char *str);
int searchCmp(STU *cur,SORT by,char *str);
void modify(STU *head,STU *cur);
void deletNode(STU *cur);
void disFoundOuts(STU *find[],int findNum);
//____________________SORT____________________//
void sort(STU **head,STU **tail,SORT by);
void exchangeNode(STU* tmp);
void exchangeHeadCore(STU *head);
void exchangeHead(STU **head);
int compare(STU *tmp,SORT by);
/*****************************************************************************/

#endif