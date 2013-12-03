#include <iostream>
#include <ctime>
#include <cstdlib>
#include "heapSort.h"
#include "disjoint_set.h"

#include <cstring>

using namespace std;
int *genIntArr(int len) {
	int *arr = new int[len];
	srand(static_cast<unsigned int>(time(0)));
	for(int i = 0; i < len; ++i) {
		arr[i] = rand() % 100;
	}
	return arr;
}

void printArray(int arr[], int len) {
	for(int i = 0; i < len; ++i) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main(void) {
	int len = 10;
	char scale[] = "\n0 1 2 3 4 5 6 7 8 9";


	disjoint_set ds(len);
	ds.UNION(1, 2);
	ds.UNION(3, 4);
	ds.UNION(5, 6);
	ds.UNION(7, 8);
	cout << scale << endl;
	printArray(ds.m_arr, len);
	printArray(ds.m_rank, len);


	ds.UNION(2, 4);
	ds.UNION(6, 8);
	ds.UNION(8, 9);
	cout << scale << endl;
	printArray(ds.m_arr, len);
	printArray(ds.m_rank, len);

	ds.FIND(5);
	cout << scale << endl;
	printArray(ds.m_arr, len);
	printArray(ds.m_rank, len);

	ds.UNION(4, 8);
	cout << scale << endl;
	printArray(ds.m_arr, len);
	printArray(ds.m_rank, len);

	ds.FIND(1);
	cout << scale << endl;
	printArray(ds.m_arr, len);
	printArray(ds.m_rank, len);

	return 0;
}
