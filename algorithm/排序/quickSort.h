/*************************************************************************
    > File Name:     quickSort.h
    > Author:        Landerl Young
    > Mail:          LanderlYoung@gmail.com 
    > Created Time:  Sun 03 Nov 2013 07:38:14 PM CST
 ************************************************************************/
template<typename T>
void __quickSort_sub(T arr[], int left, int right);

template <typename T>
void quickSort(T arr[], int len) {
	__quickSort_sub(arr, 0, len - 1);
}

template<typename T>
void __quickSort_sub(T arr[], int left, int right) {
	if(left >= right)
		return;
	T tmp = arr[left];
	int i = left, j = right;
	//split so that element int the left < tmp
	//and ones in the right >= tmp
	while(i < j) {
		while(j > i && arr[j] >= tmp) --j;
		arr[i] = arr[j];
		while(i < j && arr[i] < tmp) ++i;
		arr[j] = arr[i];
	}
	arr[i] = tmp;
	__quickSort_sub(arr, left, i - 1);
	__quickSort_sub(arr, i + 1, right);
}
