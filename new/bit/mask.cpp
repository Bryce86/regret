#include <cstdio>

void printBinary(unsigned n)
{
	for (int i = sizeof(n)*8-1; i >=0; i--)
	{
		if ((n >> i) & 1) 
			printf("1");
		else
			printf("0");

		if (i % 8 == 0)
			printf(" ");
	}
	printf("\n");
}

int main()
{
    printf("1 %X\n", 1);
    printf("-1 %X\n", -1);

	printf("1的原码：");
	printBinary(1);

	printf("1的反码：");
	printBinary(~1);

	printf("1的补码：");
	printBinary(~1+1);

    return 0;
}
