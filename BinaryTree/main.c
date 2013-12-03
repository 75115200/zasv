#include <stdio.h>
#include "btree.h"
#include "travel.h"

int main(void)
{
	char s[]="A(B(D(,G),),C(E,F))";
	BTNode *b = createBtree(s);

	printf("The height of given Binary Tree is %d \n\n",height(b));

	printf("Dis\n");
	disBtree(b);
	
	printf("\n\nPreOrder\n");

	preOrder_r(b);
	putchar('\n');
	preOrder(b);
	
	printf("\n\nInOrder\n");

	inOrder_r(b);
	putchar('\n');
	inOrder(b);

	printf("\n\nPostOrder\n");
	postOrder_r(b);
	putchar('\n');
	postOrder_1(b);

	printf("\n\nLevelOrder\n");
	levelOrder(b);
	putchar('\n');

	//Pause
	fflush(stdin);
	getchar();
	return 0;
}