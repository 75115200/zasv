#ifndef _HASH_H_
#define _HASH_H_

#define MAXSIZE 100
#define NULLKEY -1
#define DELKEY -2

typedef struct
{
	int key;
	//int data;
	int count;
} HashTable[MAXSIZE];

/******************Functions List***************/
void createHT(HashTable ha,int a[],int n,int m,int p);
void insertHT(HashTable ha,int key,int p);
int searchHT(HashTable ha,int key,int m,int p);
int deleteHT(HashTable ha,int key,int m,int p);

#endif