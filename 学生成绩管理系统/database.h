//\_________________________________________________________/\\
//@	��Ŀ��		ѧ���ɼ�����ϵͳ
//@	���ߣ�	�
//@�ļ�����database.h
//___________________________________________________________
#ifndef DATABASE_H
#define DATABASE_H
#include "manager.h"

void initDb(STU **head,STU **tail);
int loadDb(STU **head,STU **tail);
void saveDb(STU* head);
void addToDb(STU *tail);
void freeNodes(STU *head);
#endif