/*************************************************************************
  > File Name:     disjoint_set.cpp
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  Fri 01 Nov 2013 08:22:54 PM CST
 ************************************************************************/
#include <cstring>
#include "disjoint_set.h"



disjoint_set::disjoint_set(int length) :
	m_length(length)
{
	m_arr = new int[length];
	m_rank = new int[length];
	memset(m_arr, 0, sizeof(int) * length);
	memset(m_rank, 0, sizeof(int) * length);
}

disjoint_set::~disjoint_set() {
	delete[] m_arr;
	delete[] m_rank;
}

bool disjoint_set::UNION(int x, int y) {
	if(x >= m_length || y >= m_length)
		return false;
	x = FIND(x);
	y = FIND(y);
	if(m_rank[x] < m_rank[y]) {
		//make y the father node of x
		m_arr[x] = y;
	} else if(m_rank[x] > m_rank[y]) {
		m_arr[y] = x;
	} else {
		m_arr[x] = y;
		++m_rank[y];
	}
	return true;
}

int disjoint_set::FIND(int x) {
	if(x >= m_length)
		return -1;
	int p = x;

	//find root(x)
	while(m_arr[p] != 0) {
		p = m_arr[p];	
	}
	
	//condense path
	while(m_arr[x] != 0) {
		int x_f = m_arr[x];
		m_arr[x] = p;
		x = x_f;
	}
	
	return p;
}
