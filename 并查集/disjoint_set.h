/*************************************************************************
    > File Name:     disjoint_set.h
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  Fri 01 Nov 2013 08:17:07 PM CST
 ************************************************************************/
#pragma once

class disjoint_set {
	public:
		int m_length;
		int *m_arr;
		int *m_rank;
	public:
		disjoint_set(int length);
		virtual ~disjoint_set();
		bool UNION(int x, int y);
		int FIND(int x);
};
