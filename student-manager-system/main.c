//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：mian.c
//___________________________________________________________

#include <stdio.h>
#include "manager.h"
#include "menu.h"
#include "database.h"

int main(void)
{
	STU *head = NULL;
	STU *tail = NULL;

	logo();
	initDb(&head,&tail);
	UI_main(&head,&tail);
	saveDb(head);
	freeNodes(head);

	return 0;
}