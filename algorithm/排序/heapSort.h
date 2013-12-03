#pragma once

template <typename T>
void shiftDown(T arr[],int pos,int right)  {
	while((pos <<= 1) <= right) {
		if(pos + 1 <= right &&
				arr[pos - 1] < arr[(pos + 1) - 1]) pos++;
		if(arr[pos/2 - 1] < arr[pos - 1])
			std::swap(arr[pos - 1],arr[pos/2 - 1]);
		else return;
	}
}

template <typename T>
void heapSort(T arr[],int len) {
	//makeHeap
	for(int i = len/2; i >= 1; --i) {
		shiftDown(arr, i, len);
	}
	//sort
	for(int i = len; i >= 1; --i) {
		std::swap(arr[1 - 1], arr[i - 1]);
		shiftDown(arr, 1, i-1);
	}
}
