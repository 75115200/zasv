/*************************************************************************
  > File Name:     binarySearch.cpp
  > Author:        Landerl Young
  > Mail:          LanderlYoung@gmail.com 
  > Created Time:  2013/10/18 14:43:53
 ************************************************************************/

#include <iostream>
#include <ctime>

using namespace std;
int binarySearch(int arr[], int len, int key) ;

int main(void) {
	srand(static_cast<unsigned int>(time(NULL)));
	int *a = new int[100];
	for(int i = 0; i < 100; i++)
		a[i] = i;
	for(int i = 0; i < 10; i++) {
		int key = rand() % 120;
		cout << "key " << key << " found in "<<
			binarySearch(a, 100, key) << endl;
	}
	delete[] a;
	return 0;
}

int binarySearch(int arr[], int len, int key) {
	int left = 0,  right = len, mid;
	while(left <= right) {
		mid  = (left + right) / 2;
		if(arr[mid] < key) left = mid + 1;
		else if(arr[mid] > key) right = mid - 1;
		else return mid;
	}
	return -1;
}
