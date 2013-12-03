#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "btree.h"

QUE *newQue(void)
{
	QUE *q = (QUE*)malloc(sizeof(QUE));
	q->front = q->rear = 0;
	return q;
}

int enQue(QUE *q,BTNode *node)
{
	if (queFull(q))
		return 0;
	q->rear = (q->rear + 1) % QUE_MAX_SIZE;
	q->que[q->rear] = node;
		return 1;
}

BTNode *deQue(QUE *q)
{
	q->front = (q->front + 1 ) % QUE_MAX_SIZE;
	return q->que[q->front];
}

int queEmpty(QUE *q)
{
	return q->rear == q->front;
}

int queFull(QUE *q)
{
	return ((q->rear + 1) % QUE_MAX_SIZE) == q->front;
}

//Get how many elements does this Queue contains
int elmNum(QUE *q)
{
	return (q->rear - q->front + QUE_MAX_SIZE) % QUE_MAX_SIZE;
}

void disQue(QUE *q)
{
	int f = q->front;
	while (f != q->rear)
	{
		printf("%c ",q->que[f]->data);
		f = (f + 1)%QUE_MAX_SIZE;
	}
}