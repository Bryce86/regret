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

void bubblesort1(int a[], int n)
{
	int i, j;
	for (i = 0; i < n; i++)
		for(j = 1 ; j < n-1; j++)
			if (a[j-1] > a[j])
				Swap(a[j-1], a[j]);
}

void bubblesort2(int a[], int n)
{
	int k, j;
	bool flag;

	k = n;
	flag = true;
	while (flag)
	{
		flag = false;
		for (j = 1; j < k; j++)
			if (a[j-1] > a[j])
			{
				Swap(a[j-1], a[j]);	
				flag = true;
			}
		k--;
	}
}

void bubblesort3(int a[], int n)
{
	int j, k;
	int flag;

	flag = n;

	while (flag > 0)
	{
		k = flag;
		flag = 0;
		for (j = 1; j < k; j++)
			if (a[j-1] > a[j])
			{
				Swap(a[j-1], a[j]);
				flag = j;
			}
	}
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
			bubblesort1(array, NUM);
			break;
		case 2:
			bubblesort2(array, NUM);
			break;
		case 3:
			bubblesort3(array, NUM);
			break;
	}

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}






