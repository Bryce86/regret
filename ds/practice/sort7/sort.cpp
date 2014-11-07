#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

void Swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void BubbleSort(int *array, int len) {

}

void BubbleSort1(int *array, int len) {

}

void BubbleSort2(int *array, int len) {

}

void selectSort(int *array, int len) {

}

void insertSort(int *array, int len) {

}

void insertSort1(int *array, int len) {

}

void mergearray(int *array, int l, int mid , int r, int *temp) {

}

void mergesort(int *array, int l, int r, int *temp) {

}

void MergeSort(int *array, int len) {

}

void quicksort(int *array, int l, int r) {

}

void QuickSort(int *array, int len) {

}

void ShellSort(int *array, int len) {

}

void MaxHeapDownAdjust(int *array, int i, int n) {

}

void MakeMaxHeap(int *array, int len) {

}

void MaxHeapSort(int *array, int len) {

}

int main()
{
	int array[] = {51, 4, 13, -2, 100, 0, 1, -10, 1, 1, 3, 69};
	int len = sizeof(array)/sizeof(int);
	cout << "origin sort array: ";
	for (int z = 0; z < len; z++)
	{
		cout << array[z] << " ";	
	}
	cout << endl;
	cout << "sorted array:      ";

	BubbleSort(array, len);
	//BubbleSort1(array, len);
	//BubbleSort2(array, len);
	//selectSort(array, len);
	//insertSort(array, len);
	//insertSort1(array, len);
	//MergeSort(array, len);
	//QuickSort(array, len);
	//ShellSort(array, len);	
	//MaxHeapSort(array, len);

	for (int i = 0; i < len; i++)
	{
		cout << array[i] << " ";	
	}
	cout << endl;

	return 0;
}
