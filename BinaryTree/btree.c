#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

/*
*This file defines some basic operations of an binary tree,
*including create a binary tree,display a binary tree,
*find out the height of a binary tree.
*Given that traversal of a Binary Tree contains plenty of codes,
*I moved this part to another file(travel.c).	*^_^*
*/

//Create a binary tree without recursion.
BTNode* createBtree(char *str)
{
	BTNode *b = NULL;
	BTNode *stack[1024];
	BTNode *tmp;
	int top = -1,j = 0,k = 0;
	char dt = str[0];

	while (dt != '\0')
	{
		switch (dt)
		{
		case '(':
			stack[++top] = tmp;
			k = 1;
			break;
		case ',':
			k=2;
			break;
		case ')':
			top--;
			break;
		default:
			tmp = (BTNode*)malloc(sizeof(BTNode));
			tmp->lchild = tmp->rchild = NULL;
			tmp->data = dt;
			if (b == NULL)
			{
				b = tmp;
			}
			else
			{
				if ( k == 1)
					stack[top]->lchild = tmp;
				else
					stack[top]->rchild = tmp;
			}
		}

		//Test stack
		//printf("j= %d k = %d dt = %c top = %d \n",j,k,dt,top);

		j++;
		dt = str[j];
	}
	return b;
}

//显示一个二叉树，用括号表示法
void disBtree(BTNode *b)
{
	if (b != NULL)
	{
		printf("%c",b->data);
		if (b->lchild != NULL || b->rchild != NULL)
		{
			printf("(");
			disBtree(b->lchild);
			printf(",");
			disBtree(b->rchild);
			printf(")");
		}
	}
}

//Find out the heightn of a given Binary Tree
int height(BTNode* b)
{
	int l,r;

	if (b == NULL)
		return 0;

	l = height(b->lchild);
	r = height(b->rchild);

	return l>r ? (l + 1) : (r + 1);
}