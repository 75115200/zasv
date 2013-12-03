#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "btree.h"

#define QUE_MAX_SIZE 1024
typedef struct que
{
	BTNode *que[QUE_MAX_SIZE];
	int front,rear;
}QUE;

QUE *newQue(void);
int enQue(QUE *q,BTNode *node);
BTNode *deQue(QUE *q);

int queEmpty(QUE *q);
int queFull(QUE *q);
int elmNum(QUE *q);

void disQue(QUE *q);

#endif