/*
 * Brute Force
 *
 * T: ababcababa
 * P: ababa
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * pos set 0, search from string head.
 */
int BF_Search(char *s, char *p, int pos)
{
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i = 0; 
	int j = 0;

	while (i < sLen && j < pLen)
	{
		if (s[i] == p[j])	
		{
			i++;
			j++;
		}
		else
		{
			i = i - j + 1;	
			j = 0;
		}
	}

	if (j == pLen)
		return i - pLen;
	else
		return -1;
}

int main()
{
	char *s = "ababcababa";
	char *p = "ababa";

	printf("idx: %d\n", BF_Search(s, p, 0));

	return 0;
}

