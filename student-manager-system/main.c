//\_________________________________________________________/\\
//@	��Ŀ��		ѧ���ɼ�����ϵͳ
//@	���ߣ�	�
//@�ļ�����mian.c
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