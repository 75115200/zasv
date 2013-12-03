#include <stdio.h>
#include <stdlib.h>
#include "travel.h"
#include "btree.h"
#include "queue.h"

//Pre Order
//Recursion
void preOrder_r(BTNode *b)
{
	if (b != NULL)
	{
		printf("%c ",b->data);
		preOrder_r(b->lchild);
		preOrder_r(b->rchild);
	}
	else
		printf("^ ");
}

//Pre Order
//No Recursion
void preOrder(BTNode *b)
{
	BTNode *stack[STACK_MAX_SIZE];
	BTNode *tmp = b;
	int top = -1;

	while (tmp != NULL || top > -1)
	{
		while (tmp != NULL)
		{
			printf("%c ",tmp->data);//visit
			stack[++top] = tmp;
			tmp = tmp->lchild;
		}

		if (top > -1)
			tmp = stack[top--]->rchild;
	}
}

//In Order
//Recursion
void inOrder_r(BTNode *b)
{
	if (b != NULL)
	{
		inOrder_r(b->lchild);
		printf("%c ",b->data);
		inOrder_r(b->rchild);
	}
	else
		printf("^ ");
}

//In Order
//No Recursion
void inOrder(BTNode *b)
{
	BTNode *tmp = b;
	BTNode *stack[STACK_MAX_SIZE];
	int top = -1;

	if (b != NULL)
	{
		while (tmp != NULL || top > -1)
		{
			while (tmp != NULL)
			{
				stack[++top] = tmp;
				tmp = tmp->lchild;
			}

			if (top > -1)
			{
				printf("%c ",stack[top]->data);
				tmp = stack[top--]->rchild;
			}
		}
	}
}

//Post Order
//Recursion
void postOrder_r(BTNode *b)
{
	if (b != NULL)
	{
		postOrder_r(b->lchild);
		postOrder_r(b->rchild);
		printf("%c ",b->data);
	}
	else
		printf("^ ");
}

//Post Order 
//No Recursion Algorithm 1
void postOrder_1(BTNode *b)
{
	struct s
	{
		BTNode *p;
		char flag;
	};
	struct s stack[STACK_MAX_SIZE];
	int top = -1;
	BTNode *btmp = b;

	while (btmp != NULL)
	{
		stack[++top].p = btmp;
		stack[top].flag = 'F';
		btmp = btmp->lchild;
	}
	
	while (top > -1)
	{
		if (stack[top].flag == 'T' || stack[top].p->rchild == NULL)
		{
			printf("%c ",stack[top].p->data);
			top--;
		}
		else
		{
			btmp = stack[top].p->rchild;
			stack[top].flag = 'T';

			while (btmp != NULL)
			{
				stack[++top].p = btmp;
				stack[top].flag = 'F';
				btmp = btmp->lchild;
			}
		}
	}
}

//Post Order
//No Recorsion Algotithm 2
void postOrder_2(BTNode *b)
{
	
}

//Post Order
//No Recursion Algorithm 3
void postOrder_3(BTNode *b)
{

}

/***************Level Order****************/
void levelOrder(BTNode *b)
{
	QUE *q = newQue();
	BTNode *tmp = b;
	
	enQue(q,tmp);
	while (!queEmpty(q))
	{
		tmp = deQue(q);
		printf("%c ",tmp->data);
		if (tmp->lchild != NULL)
			enQue(q,tmp->lchild);
		if (tmp->rchild != NULL)
			enQue(q,tmp->rchild);
	}
}