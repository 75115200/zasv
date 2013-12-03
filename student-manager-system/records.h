//\_________________________________________________________/\\
//@	项目：		学生成绩管理系统
//@	作者：	杨超
//@文件名：records.h
//___________________________________________________________
#ifndef RECORDS_H
#define RECORDS_H

#include "manager.h"

CONFIRM newRecord(STU *head,STU*  tmp);
void modify_name(STU *tmp);
void modify_id(STU *tmp);
void modify_gender(STU *tmp);
void modify_math(STU *tmp);
void modify_english(STU *tmp);
void modify_c(STU *tmp);
int getScore(char *s,int max);
void disRecord(STU* record);
void addNewRecordToList(STU *head,STU **tail);
void disRecord(STU* record,int n);
void disAllRecords(STU *head);

#endif