#include <stdio.h>
#include <stdlib.h>
#include "BinarySearchTree.h"

BSTNode *createBST(int a[],int n)
{
	BSTNode *bt = NULL;
	int i;
	for (i = 0;i < n;i++)
		insertBSTNode(&bt,a[i]);
	return bt;
}

int insertBSTNode(BSTNode **p,int k)
{
	if (*p == NULL)
	{
		*p = (BSTNode*)malloc(sizeof(BSTNode));
		(*p)->key = k;
		(*p)->lchild = (*p)->rchild = NULL;
		return 1;
	}
	else if (k == (*p)->key)
		return 0;
	else if (k < (*p)->key)
		return insertBSTNode(&(*p)->lchild,k);
	else
		return insertBSTNode(&(*p)->rchild,k);
}

BSTNode *searchBST(BSTNode *p,int key)
{
	if (p == NULL || p->key == key)
		return p;

	if(key < p->key)
		return searchBST(p->lchild,key);
	else 
		return searchBST(p->rchild,key);
}

//Written by Young
BSTNode *searchBST_nRec(BSTNode *p,int key)
{
	//Use p as a temporary variable to reduce the usage of mamory
	while (p!= NULL && p->key != key)
	{
		if (key > p->key)
			p = p->rchild;
		else
			p = p->lchild;
	}
	return p;
}

//Written by Young
BSTNode *searchBST_P_nRec(BSTNode *p,int key,BSTNode **parent)
{
	*parent = NULL;
	while (p!= NULL && p->key != key)
	{
		if (key > p->key)
		{
			*parent = p;
			p = p->rchild;
		}
		else
		{
			*parent = p;
			p = p->lchild;
		}
	}
	return p;
}

/*_________________________删除节点（原创版）________________________*/
//这段代码是自己写的，虽然没书上简洁，但还是能正常执行de

int delNode(BSTNode **p,int key)
{
	BSTNode *parent,*res;//res 即resault 是要被删除掉的节点
	char flag;//判断res 是 parent的左子树'L'，还是右子树'R'
	res = searchBST_P_nRec(*p,key,&parent);	

	//res == NULL说明查找失败，即没有这个节点，函数直接退出
	if (res == NULL)
		return 0 ;
	
	if (parent != NULL && res == parent->lchild)
		flag = 'L';
	else
		flag = 'R';

	//此时删除的节点不同时有左右子树（即只有左子树||只有右子树||没有子树--本身就是叶子节点）
	if (!(res->lchild != NULL && res->rchild != NULL))
	{
		if (parent != NULL)
			delSingle(&res,parent,flag);
		else
			delSingle(p,NULL,flag);
	}
	else//同时据有左右子树的情况
	{
		int tmp;
		BSTNode *t = maxNode(res->lchild);
		tmp = t->key;
		delNode(p,t->key);
		res->key = tmp;
	}
	return 1;
}

//当要删除的节点不同时有左右子树时调用该函数
//p为要删除的节点
//当parent为NULL时flag为无用变量，值为任意
void delSingle(BSTNode **p,BSTNode *parent,char flag)
{
    BSTNode *next;
    if ((*p)->lchild != NULL)
        next = (*p)->lchild;
	else
		next = (*p)->rchild;

    if (parent != NULL)
	{
		if (flag == 'L')
			parent->lchild = next;
		else
			parent->rchild = next;
		free(*p);
	}
	else
	{
		BSTNode *tmp = *p;
		*p = next;
		free(tmp);
	}
}

//查找树中最大的节点
BSTNode* maxNode(BSTNode *p)
{
	BSTNode *tmp = p;
	while (p->rchild != NULL)
		p = p->rchild;
	return p;
}
/*_______________________________________________________________*/

/*____________Delete BST Node (adapted from text book)___________*/
int delBST(BSTNode **bt,int key)
{
	if (*bt == NULL)
		return 0;
	else
	{
		if (key < (*bt)->key)
			return delBST(&(*bt)->lchild,key);
		else if (key > (*bt)->key)
			return delBST(&(*bt)->rchild,key);
		else
		{
			Delete(bt);
			return 1;
		}
	}
}

//This function is difficult to understand
//unless you read together with the 
//function that called it.
void Delete(BSTNode **p)
{
	BSTNode *q;
	if ((*p)->rchild == NULL)
	{
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if ((*p)->lchild == NULL)
	{
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else 
		Delete_1(*p,&(*p)->lchild);
}

//Same as The Previous one
void Delete_1(BSTNode *p,BSTNode **r)
{
	BSTNode *q;
	if ((*r)->rchild == NULL)
		Delete_1(p,&(*r)->rchild);
	else
	{
		p->key = (*r)->key;
		q = *r;
		*r = (*r)->lchild;
		free(q);
	}
}
/*_______________________________________________________________*/

//This function is to display the created Binary Search Tree,
//thus,checking whether the Tree is created correctly
void preOrder(BSTNode *p)
{
	if (p != NULL)
	{
		printf("%2d ",p->key);
		preOrder(p->lchild);
		preOrder(p->rchild);
	}

}

//This function is to check whether after inorder travelan BST 
//the output is an in-order-number list.
void inOrder(BSTNode *p)
{
	if (p != NULL)
	{
		inOrder(p->lchild);
		printf("%2d ",p->key);
		inOrder(p->rchild);
	}
}
