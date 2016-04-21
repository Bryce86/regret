#include <stdio.h>
#include <string.h>
#include <assert.h>

void* my_memcpy(void *dst, const void *src, int n)
{
    assert(dst != NULL && src != NULL);

    char *d = dst;
    const char *s = src;

    while (n-- > 0) 
        *d++ = *s++;

    return dst;
}

void* my_memmove(void *dst, const void *src, int n)
{
    assert(dst != NULL && src != NULL);

    char *d = dst;
    const char *s = src;

    if (d < s)
    {
        while (n-- > 0)
            *d++ = *s++;
    }
    else if (d > s)
    {
        d = d + n - 1;   
        s = s + n - 1;

        while (n-- > 0)
            *d-- = *s--;
    }

    return dst;
}

int main()
{
    char buff[32] = {0};
    const char *str = "hello, world";
    my_memcpy(buff, str, strlen(str)+1);
    //my_memmove(buff, str, strlen(str)+1);

    printf("%s\n", buff);

    return 0;
}

