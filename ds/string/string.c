/*
 * some string function's implementation.
 */

#include <stdio.h>
#include <assert.h>

/* strcpy */

char * strcpy_android(char *to, const char *from)
{
	char *save = to;

	for (; (*to = *from) != '\0'; ++from, ++to);

	return (save);
}

char * strcpy(char *strDest, const char *strSrc)
{
	assert((strDest != NULL) && (strSrc != NULL));

	char *address = strDest;

	while ((*strDest++ = *strSrc++) != '\0');
	
	return address;
}

/* strlen */
size_t strlen(const char *str)
{
	const char *s;	

	for (s = str; *s; s++);

	return (s - str);
}

/* strcat */
char * strcat_android(char *s, const char *append) // android
{
	char *save = s;

	for (; *s; s++);

	while ((*s++ = *append++) != '\0');

	return (save);
}

char * strcat(char *dst, const char *src)
{
	char *cp = dst;

	while (*dst)
		dst++;

	while ((*dst++ = *src++) != '\n');

	return (cp);
}

/* strcmp */
int strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)	
		if (*s1++ == 0)
			return (0);

	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

int __cdecl strcmp_ms(const char *src, const char *dst) // Microsoft
{
	int ret = 0;
	while (!(ret = *(unsigned char *)src - *(unsigned char *)dst) && *dst)
	{
		++src;
		++dst;
	}
	
	if (ret < 0)
		ret = -1;
	else if (ret > 0)
		ret = 1;

	return ret;
}

/* memcmp */
void * __cdecl memcpy(void *dst, const void *src, size_t n)
{
	void *ret = dst;

	while (n--)
		*(char *)dst++ = *(char *)src++;

	return ret;
}

/* memmove */
void * __cdecl memmove(void *dst, const void *src, size_t n)
{
	void *ret = dst;

	// ensure every bit of src isn't overlapped before assigned to dst 
	if (dst <= src || (char *)dst >= ((char *)src + n))
	{
		// Non-Overlapping Buffers
		// copy from lower addresses to higher addresses
		while (n--)	
			*(char *)dst++ = *(char *)src++;
	}
	else
	{
		// Overlapping Buffers	
		// copy from higher address to lower addresses
		dst = (char *)dst + (n - 1);
		src = (char *)src + (n - 1);

		while (n--)
			*(char *)dst-- = *(char *)src--;
	}

	return ret;
}

int main()
{
	char s1[] = "hello, memmove";

	char *s2 = memmove(s1+5, s1+7, strlen("memmove"));

	printf("s1--%p\n", s1);
	printf("s2--%p\n", s2);
	printf("memmove: %s\n", s2);

	return 0;
}
