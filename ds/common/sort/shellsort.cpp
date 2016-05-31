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

void shellsort(int s[], int n)
{
	int i, j, gap;

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = 0; i < gap; i++)
		{
			for (j = i + gap; j < n; j += gap)
			{
				int temp = s[j];
				int k = j - gap;
				while (k >= 0 && s[k] > temp)
				{
					s[k+gap] = s[k];		
					k -= gap;
				}
				s[k+gap] = temp;
			}
		}
}

void shellsort1(int s[], int n)
{		
	int j, gap;

	for (gap = n/2; gap > 0; gap /= 2)
		for (j = gap; j < n; j++)
			if (s[j] < s[j-gap])
			{
				int temp = s[j];	
				int k = j - gap;
				while (k >= 0 && s[k] > temp)
				{
					s[k+gap] = s[k];
					k -= gap;
				}
				s[k+gap] = temp;
			}
}

void shellsort2(int s[], int n)
{
	int i, j, gap;
	for (gap = n/2; gap > 0; gap /= 2)
		for(i = gap; i < n; i++ )
			for (j = i - gap; j >=0 && s[j] > s[j+gap]; j-=gap)
				Swap(s[j], s[j+gap]);
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

	//shellsort(array, NUM);
	shellsort1(array, NUM);
	//shellsort2(array, NUM);

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}






