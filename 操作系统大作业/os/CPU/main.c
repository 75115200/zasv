/*************************************************************************
    > File Name:     main.c
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  2013/4/30 18:22:54
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "dataStruct.h"


int main(void){
	PCB *p[5];
	QUE *q = newQue();
	char *pn[5] = {"Q1","Q2","Q3","Q4","Q5"};
	int i,tmp;
	for (i = 0; i < 5; ++i) {
		printf("Enter required time by process %s:",pn[i]);
		scanf("%d",&tmp);
		enQue(q,newPcb(pn[i],tmp));
	}
	
	while(!isEmpty(q)) {
		process(q);
	}
	free(q);
	return 0;
}

