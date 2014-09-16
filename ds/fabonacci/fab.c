#include <stdio.h>

#define PRINT_NUM 15

int fab(int i)
{
	if (i == 1 || i == 2)
		return 1;
	return fab(i-1) + fab(i-2);
}

int main()
{
	int i = 1;	
	for (i; i < PRINT_NUM; i++)
	{
		printf("%d ", fab(i));
	}
	printf("\n");

	return 0;
}
