/*************************************************************************
    > File Name:     dataStruct.c
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/4/30 18:07:20
 ************************************************************************/

#include "dataStruct.h"
#include <stdio.h>
#include <stdlib.h>

void strcp(char *a,char *b) {
	while(*a++ = *b++);
}
int isFinished(PCB *p) {
	if (p->reqTime <= p->ranTime) {
		p->statue = 'E';
		return 1;
	}
	return 0;
}

PCB *newPcb(char *name,int reqTime) {
	PCB *p = (PCB*)malloc(sizeof(PCB));
	strcp(p->name,name);
	p->next = NULL;
	p->reqTime = reqTime;
	p->ranTime = 0;
	p->statue = 'R';

	return p;
}

QUE *newQue() {
	QUE *q = (QUE*)malloc(sizeof(QUE));
	q->front = q->tail = NULL;
	return q;
}

void enQue(QUE* q, PCB *p){
	if (q->front == NULL) {
		q->front = q->tail = p;
		p->next = NULL;
	} else {
		p->next = q->tail;
		q->tail = p;
	}
}

PCB *deQue(QUE *q) {
	if(q->front == NULL) {
		return NULL;
	} else if(q->front == q->tail) {
		PCB *p = q->front;
		q->front = q->tail = NULL;
		return p;
	} else {
		PCB *tmp1 = q->tail,*tmp2;
		while ((tmp1)->next != q->front)
			tmp1 = tmp1->next;
		tmp2 = q->front;
		q->front = tmp1;
		return tmp2;
	}
}

int isEmpty(QUE *q) {
	return q->front == NULL;
}


void process(QUE *q) {
	PCB *tmp;
	if (q == NULL)
		return;
	tmp = deQue(q);
	tmp->ranTime += 1;
	printf("Processing %s reqTime = %d ranTime = %d\n",
			tmp->name, tmp->reqTime, tmp->ranTime);

	if (isFinished(tmp)) {
		printf("Process %s is finished.\n",tmp->name);
		free(tmp);
	} else {
		enQue(q,tmp);
	}
}
