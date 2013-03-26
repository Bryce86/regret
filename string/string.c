/*
 * some string function's implementation.
 */

/* strcpy */

char *
strcpy(char *to, const char *from)
{
	char *save = to;

	for (; (*to = *from) != '\0'; ++from, ++to);

	return (save);
}

char *
strcpy(char *strDest, const char *strSrc)
{
	assert((strDest != NULL) && (strSrc != NULL));

	char *address = strDest;

	while ((*strDest++ = *strSrc++) != '\0');
	
	return address;
}

/* strlen */
size_t
strlen(const char *str)
{
	const char *s;	

	for (s = str; *s; s++);

	return (s - str);
}

/* strcat */
char *
strcat(char *s, const char *append) // android
{
	char *save = s;

	for (; *s; s++);

	while ((*s++ = *append++) != '\0');

	return (save);
}

char *
strcat(char *dst, const char *src)
{
	char *cp = dst;

	while (*dst)
		dst++;

	while ((*dst++ = *src++) != '\n');

	return (cp);
}

/* strcmp */
int 
strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2++)	
		if (*s1++ == 0)
			return (0);
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

/* memcmp */
int memcpy(const void *s1, const void *s2, size_t n)
{
	const unsigned char *p1 = s1;
	const unsigned char *end1 = p1 + n;
	const unsigned char *p2 = s2;
	int d = 0;

	for (;;)
	{
		if (d || p1 >= end1) break;
		d = (int)*p1++ - (int)*p2++;

		if (d || p1 >= end1) break;
		d = (int)*p1++ - (int)*p2++;

		if (d || p1 >= end1) break;
		d = (int)*p1++ - (int)*p2++;

		if (d || p1 >= end1) break;
		d = (int)*p1++ - (int)*p2++;
	}
	return d;
}
