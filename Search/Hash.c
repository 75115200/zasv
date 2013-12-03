#include <stdio.h>
#include "Hash.h"

void createHT(HashTable ha,int a[],int n,int m,int p)
{
	int i;
	for (i = 0;i < m;i++)
	{
		ha[i].key = NULLKEY;
		ha[i].count = 0;
	}

	for (i = 1;i < n;i++)
		insertHT(ha,a[i],p);

}

void insertHT(HashTable ha,int key,int p)
{
	int adr = key % p;
	int i = 1;
	
	while (ha[adr].key != NULLKEY && ha[adr].key != DELKEY)
	{
		adr = (adr + 1) % p;
		i++;
	}
	ha[adr].key = key;
	ha[adr].count = i;						
}

int searchHT(HashTable ha,int key,int m,int p)
{
	int adr = key % p;
	int i = 1;
	while (ha[adr].key != key && ha[adr].key != NULLKEY 
		&& ha[adr].key != DELKEY && i < m)
	{
		adr = (adr + 1) % p;
		i++;
	}

	if (ha[adr].key == key)
		return adr;
	else 
		return -1;
}

int deleteHT(HashTable ha,int key,int m,int p)
{
	int adr = searchHT(ha,key,m,p);
	if (adr == -1)
		return -1;
	else
		ha[adr].key = DELKEY;
}