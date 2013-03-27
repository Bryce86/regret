#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int NUM = 10;
const int RAND_VALUE = 100;

inline void Swap(int &a, int &b)
{
	int c = a;
	a = b;
	b = c;
}

void selectsort(int s[], int n)
{
	int i, j, nMinIndex;
	for (i = 0; i < n; i++)
	{
		nMinIndex = i;	
		for (j = i + 1; j < n; j++)
			if (s[j] < s[nMinIndex])
				nMinIndex = j;

		Swap(s[i], s[nMinIndex]);
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

	selectsort(array, NUM);

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}






