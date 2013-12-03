#include <stdio.h>
#include <stdlib.h>
//用链表实现报数问题

//这里的queque不是指队列，而是说排队==！
typedef struct queue
{
	int data;
	struct queue *next;
} Que;

typedef struct 
{
	Que *pre;
	Que *tmp;
} Tmp;

void delNode(Tmp*);

int main(void)
{
	int total,m,i;
	Que *head = (Que*)malloc(sizeof(Que));
	Tmp tp;
	head->data = 1;
	tp.tmp = head;

	printf("Please enter total number and m\n");
	scanf("%d %d",&total,&m);

	for (i = 2;i <= total;i++)	//Construct List
	{
		tp.tmp->next = (Que*)malloc(sizeof(Que));
		tp.tmp = tp.tmp->next;
		tp.tmp->data = i;
	}
	tp.pre = tp.tmp;
	tp.pre->next = head;
	tp.tmp = head;

	while(total > 0 )
	{
		for (i =1 ;i < m ;i++)//loop = total-1
		{
			tp.pre = tp.pre->next;
			tp.tmp = tp.tmp->next;
		}
		printf("%d ",tp.tmp->data);
		delNode(&tp);
		total--;
	}

	fflush(stdin);
	getchar();
	return 0;
}

void delNode(Tmp *del)
{
	del->pre->next = del->tmp->next;
	free(del->tmp);
	del->tmp = del->pre->next;
}
