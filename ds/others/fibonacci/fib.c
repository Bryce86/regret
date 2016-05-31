#include <stdio.h>

#define PRINT_NUM 15

// F（0）=0，F（1）=1，F（n）=F(n-1)+F(n-2)(n≥2，n∈N*)

int fab(int i)
{   
    if (i == 0)
        return 0
	else if (i == 1)
		return 1;
        
	return fab(i-1) + fab(i-2);
}

int main()
{
	for (i = 0; i < PRINT_NUM; i++)
	{
		printf("%d ", fab(i));
	}
	printf("\n");

	return 0;
}
