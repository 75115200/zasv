#ifndef _BTREE_H_
#define _BTREE_H_

typedef struct bt
{
	char data;
	struct bt *lchild;
	struct bt *rchild;
} BTNode;
#define STACK_MAX_SIZE 1024

/********************Functions List********************/
BTNode* createBtree(char *str);
void disBtree(BTNode *b);
int height(BTNode *b);
/******************************************************/
#endif