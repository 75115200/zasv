/*************************************************************************
    > File Name:     dataStruct.h
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/4/30 16:41:39
 ************************************************************************/
#ifndef __DATA_STRUCT_H
#define __DATA_STRUCT_H

typedef struct PCB {
	char name[7];
	char statue;
	//either R for ready
	//or E for done.
	struct PCB *next;
	int reqTime;
	int ranTime;
} PCB;


typedef struct {
	PCB *front;
	PCB *tail;
} QUE;

PCB *newPcb(char *name,int reqTime);
int isFinished(PCB *p);
QUE *newQue();
void enQue(QUE* q, PCB *p);
PCB *deQue(QUE *q);
int isEmpty(QUE *q);

void process(QUE *q);

#endif
