/*************************************************************************
  > File Name:     mergeSort.cpp
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013/10/18 15:01:31
 ************************************************************************/

#include <iostream>
#include <ctime>

using namespace std;

void mergeSort_r(int arr[], int left, int right);
void mergeSort(int arr[], int len);
void merge(int arr[], int left, int mid, int right);

void _printArr(int arr[], int len);

int main(void) {
	srand(static_cast<unsigned int>(time(0)));
	int len = rand() % 20 + 10;
	int *arr = new int[len];
	for(int i = 0; i < len; i++) {
		arr[i] = rand() % (len * 2);
	}

	_printArr(arr, len);
	mergeSort(arr, len);
	_printArr(arr, len);
	delete[] arr;
	return 0;
}

void mergeSort_r(int arr[], int left, int right) {
	if(left < right) {
		int mid = (left + right) / 2;
		mergeSort_r(arr, left , mid);
		mergeSort_r(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

void mergeSort(int arr[], int len) {
	mergeSort_r(arr, 0, len - 1);
}

void merge(int arr[], int left, int mid, int right) {
	int i = left, j = mid + 1, index = 0;
	int *ass = new int[right - left + 1];
	while(i <= mid && j <= right)
		if(arr[i] < arr[j])
			ass[index++] = arr[i++];
		else
			ass[index++] = arr[j++];
	if(i == mid+1) {
		while(j <= right)
			ass[index++] = arr[j++];
	} else {
		while(i <= mid)
			ass[index++] = arr[i++];
	}
	for(i = left;i <= right; i++)
		arr[i] = ass[i - left];
	delete[] ass;
}

void _printArr(int arr[], int len) {
	for(int i = 0; i < len; i++)
		cout << arr[i] << " ";
	cout << endl;
}


