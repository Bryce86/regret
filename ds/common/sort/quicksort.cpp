#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

const int NUM = 10;
const int RAND_VALUE = 100;

void quicksort(int s[], int l, int r)
{
	if (l < r)
	{
		int i = l, j = r, x = s[i];	

		while(i < j)
		{
			while (i < j && s[j] >= x)	
				j--;

			if (i < j)
				s[i++] = s[j];

			while (i < j && s[i] <= x)
				i++;

			if (i < j)
				s[j--] = s[i];
		}
		s[i] = x;

		quicksort(s, l, i - 1);
		quicksort(s, i + 1, r);
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

	quicksort(array, 0, NUM-1);

	for (int i = 0; i < NUM; i++)
		cout << array[i] << " ";
	cout << endl;

	return 0;
}






