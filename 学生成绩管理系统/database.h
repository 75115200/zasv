//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：database.h
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