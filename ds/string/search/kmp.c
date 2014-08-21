/*
 * Knuth, Morris, Pratt
 *
 *
 * */
#include <stdio.h>
#include <string.h>

void GetNext(char *p, int *next)
{
	int pLen = strlen(p);
	int i = 0;
	int j = -1;	
	next[0] = -1;

	while (i < pLen - 1)
	{
		if (j == -1 || p[i] == p[j])
		{
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}

void GetNextVal(char *p, int *nextval)
{
	int pLen = strlen(p);
	int i = 0;
	int j = -1;
	nextval[0] = -1;

	while (i < strlen(p) - 1)
	{
		if (j == -1 || p[i] == p[j])
		{
			++i;
			++j;

			if (p[i] != p[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];
		}
		else
			j = nextval[j];
	}
}

int KMP_Search(char *s, char *p, int pos)
{
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i = 0; // i = pos; search from pos.
	int j = 0;
	int next[100];

	//GetNext(p, next);
	GetNextVal(p, next);

	while (i < sLen && j < pLen)
	{
		if (j == -1 || s[i] == p[j])	
		{
			i++;	
			j++;
		}
		else
		{
			j = next[j];	
		}
	}

	if (j == pLen)
		return i - pLen;
	else
		return -1;
}

int main()
{
	char *t = "BBC ABCDAB ABCDABCDABDE";
	char *p = "ABCDABD";

	printf("idx: %d\n", KMP_Search(t, p, 0)); // 15

	return 0;
}















