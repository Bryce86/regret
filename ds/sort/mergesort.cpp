#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int NUM = 10;
const int RAND_VALUE = 100;

void mergearray(int s[], int l, int mid, int r, int temp[])
{
	int i = l, m = mid, j = mid + 1, n = r, k = 0;

	while (i <=m && j <= n)
	{
		if (s[i] < s[j])		
			temp[k++] = s[i++];
		else
			temp[k++] = s[j++];
	}

	while (i <= m)
		temp[k++] = s[i++];

	while (j <= n)
		temp[k++] = s[j++];

	for (i = 0; i < k; i++)		
		s[l+i] = temp[i];
}

void recursion(int s[], int l, int r, int temp[])
{
	if (l < r)
	{
		int mid = (l + r) / 2;
		recursion(s, l, mid, temp); 				
		recursion(s, mid + 1, r, temp); 				
		mergearray(s, l, mid, r, temp);
	}
}

void mergesort(int s[], int n)
{
	int *tempArray = new int[n];	
		if(NULL == tempArray)
			return;

	recursion(s, 0, n - 1, tempArray);

	delete []tempArray;
	tempArray = NULL;
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

	mergesort(array, NUM);

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}






