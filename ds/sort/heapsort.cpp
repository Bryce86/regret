#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int NUM = 10;
const int RAND_VALUE = 100;

void Swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

/* Max Heap */
void MaxHeapFixup(int a[], int i)
{
	int j, temp;
	
	temp = a[i];
	j = (i-1)/2;

	while (j >= 0 && i != 0)
	{
		if (a[j] >=  temp)	
			break;

		a[i] = a[j];
		i = j;		
		j = (i-1)/2;
	}
	a[i] = temp;
}

void MaxHeapFixdown(int a[], int i, int n)
{
	int j, temp;

	temp = a[i];
	j = 2*i + 1;

	while (j < n)
	{
		if (j+1 < n && a[j+1] > a[j])	
			j++;

		if (a[j] <= temp)
			break;

		a[i] = a[j];
		i = j;
		j = 2*i + 1;
	}
	a[i] = temp;
}

void MakeMaxHeap(int a[], int n)
{
	for (int i = n/2 -1; i >= 0; i--)
		MaxHeapFixdown(a, i, n);
}

/* Min Heap */
/* Insert */
void MinHeapFixup(int a[], int i)
{
	int j, temp;	

	temp = a[i];

	j = (i-1)/2;

	while (j >= 0 && i != 0)
	{
		if (a[j] <= temp)	
			break;
		
		a[i] = a[j];
		i = j;
		j = (i-1)/2;
	}
	a[i] = temp;
}
/*
void MinHeapFixup(int a[], int i)
{
	for (j = (i-1)/2; (j >= 0 && x != 0) && a[i] < a[j]; i = j, j = (i-1)/2)
		Swap(a[i], a[ij]);
}
*/

/* Delete */
void MinHeapFixdown(int a[], int i, int n)
{
	int j, temp;

	temp = a[i];
	j = 2*i + 1;

	while (j < n)
	{
		if (j+1 < n && a[j+1] < a[j])
			j++;

		if (a[j] >=  temp)
			break;

		a[i] = a[j];
		i = j;
		j = 2*i + 1;
	}
	a[i] = temp;
}

void MakeMinHeap(int a[], int n)
{
	for (int i = n/2 - 1; i >= 0; i--)
		MinHeapFixdown(a, i, n);
}

void heapsort(int a[], int n)
{
	MakeMaxHeap(a, n);
	//MakeMinHeap(a, n);
	
	for (int i = n-1; i >= 1; i--)
	{
		Swap(a[i], a[0]);	
		MaxHeapFixdown(a, 0, i);
		//MinHeapFixdown(a, 0, i);
	}
}

int main(void)
{
	int array[NUM];

	srand((unsigned int)time(NULL));
	for (int i = 0; i < NUM; i++)
	{
		array[i] = rand() % RAND_VALUE;	
	}

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	heapsort(array, NUM);

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}






