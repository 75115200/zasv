#ifndef _BINARYSEARCHTREE_H_
#define _BINARYSEARCHTREE_H_

typedef struct node
{
	int key;
	//int data;
	struct node *lchild,*rchild;
}BSTNode;
#define MAX_STACK_SIZE 128

int insertBSTNode(BSTNode **p,int k);
BSTNode *createBST(int a[],int n);
BSTNode *searchBST(BSTNode *p,int key);
BSTNode *searchBST_nRec(BSTNode *p,int key);
BSTNode *searchBST_P_nRec(BSTNode *p,int key,BSTNode **parent);
///
int delNode(BSTNode **p,int key);
void delSingle(BSTNode **p,BSTNode *parent,char flag);
BSTNode* maxNode(BSTNode *p);
//
int delBST(BSTNode **bt,int key);
void Delete(BSTNode **p);
void Delete_1(BSTNode *p,BSTNode **r);
//
void preOrder(BSTNode *p);
void inOrder(BSTNode *p);

#endif
