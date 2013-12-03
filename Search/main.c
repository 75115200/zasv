#include <stdio.h>
#include "BinarySearchTree.h"
#include "Hash.h"

int main(void)
{
	/*//Test BST
	BSTNode *b = NULL;
	BSTNode *s = NULL;
	BSTNode *prt;
	b = createBST(a,15);
	preOrder(b);
	putchar('\n');
	inOrder(b);
	
	s = searchBST_P_nRec(b,74,&prt);
	printf("\n(s)%p -> key = %d",s,s == NULL? 0 :s->key);
	printf("\n(p)%p -> key = %d",prt,prt == NULL? 0 :prt->key);
	printf("\nMaxNode of left child tree is %d \n",maxNode(b)->key);

	{
		int d;
		while(1)
		{
			printf("\nPlease enter num\n");
			scanf("%d",&d);getchar();
			printf("Find %d at %p",d,searchBST(b,d));
			printf("\n\nb->lchild = %p\nÏÖÔÚÉ¾³ý%d \n",b->lchild,d);
			printf("%s\n",delBST(&b,d) == 1?"É¾³ý³É¹¦":"É¾³ýÊ§°Ü");
			preOrder(b);
			putchar('\n');
			inOrder(b);
			printf("\nb = %p",b);
		}
	}
	*/
	//Test HashTable
	int a[] = {74,25,18,46,2,39,53,4,32,53,32,74,11,67,60};
	HashTable ha;
	int p = 17;
	int k = 74,i;
	createHT(ha,a,15,20,p);
	for(i = 0;i < 20;i++)
	{
		printf("Node %2d,key %2d,count %2d\n",i,ha[i].key,ha[i].count);
	}
	printf("\n");
	for(i = 0;i < 15;i++)
	{
		k = a[i];
		printf("Search  %2d ,at %2d ,is %2d\n",k,searchHT(ha,k,20,17),ha[searchHT(ha,k,20,17)].key);
	}


	fflush(stdin);
	getchar();
	return 0;
}