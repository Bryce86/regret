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

void insertsort1(int a[], int n)
{
	int i, j, k;
	for (i = 1; i < n; i++)
	{
		for (j = i - 1; j >= 0; j--)	
			if (a[j] < a[i])
				break;

		if (j != i - 1)
		{
			int temp = a[i];
			for (k = i - 1; k > j; k--)
				a[k+1] = a[k];

			a[k+1] = temp;
		}
	}
}

void insertsort2(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
		if (a[i] < a[i - 1])
		{
			int temp = a[i];
			for (j = i - 1; j >= 0 && a[j] > temp; j--)
				a[j+1] = a[j];

			a[j+1] = temp;
		}
}

void insertsort3(int a[], int n)
{
	int i, j;
	for (i = 1; i < n; i++)
		for(j = i -1; j >= 0 && a[j] > a[j+1]; j--)
			Swap(a[j], a[j+1]);
}

int main(int argc, char **argv)
{
	int which;
	if (argc < 2)
		which = 3;
	else
	{
		which = atoi(argv[1]);
		if (which > 3)
		{
			cout << "options: a.out 1..3" << endl;
			exit(0);
		}
	}

	int array[NUM];

	srand((unsigned int)time(NULL));
	for (int i = 0; i < NUM; i++)
	{
		array[i] = rand() % RAND_VALUE;	
	}

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	switch(which)
	{
		case 1:
			insertsort1(array, NUM);
			break;
		case 2:
			insertsort2(array, NUM);
			break;
		case 3:
			insertsort3(array, NUM);
			break;
	}

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}






