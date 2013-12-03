#include <iostream>
#include <ctime>
#include <cstdlib>
#include "heapSort.h"

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
	int len = 20;
	int *arr = genIntArr(len);
	printArray(arr, len);
	heapSort(arr, len);
	printArray(arr,len);
	return 0;
}
