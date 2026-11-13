#include <stddef.h>
#include <stdio.h>

size_t my_strlen(const char* s)
{
    size_t len = 0;

    while (s[len] != '\0') {
        len++;
    }

    return len;
}


char* my_strcpy(char* dst, const char* src)
{
    char* ret = dst;
    while ((*dst++ = *src++) != '\0')
        ;
    return ret;
}

char* my_strncpy(char* dst, const char* src, size_t n)
{
    char* ret = dst;
    size_t i = 0;

    while (i < n && src[i] != '\0')
    {
        dst[i] = src[i];
        i++;
    }
    return ret;
}

char* my_strcat(char* dst, const char* src)
{
    char* ret = dst;
    while (*dst) dst++;
    while ((*dst++ = *src++) != '\0')
        ;
    return ret;
}

char* my_strncat(char* dst, const char* src, size_t n)
{
    char* ret = dst;
    while (*dst) dst++;

    while (n-- && (*dst++ = *src++) != '\0')
        ;

    if (n == (size_t)-1)
        *dst = '\0';

    return ret;
}

int my_strcmp(const char* s1, const char* s2) 
{
    while(*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

int my_strncmp(const char* s1, const char* s2, size_t n)
{
    if (n == 0) return 0;

    while (--n && *s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

// 用于在字符串中从左到右查找第一个匹配字符的位置
char* my_strchr(const char* s, int c)
{
    while (*s != (char)c) {
        if (*s == '\0')
            return NULL;
        s++;
    }
    return (char*)s;
}

// 用于查找指定字符在字符串中最后一次出现位置的函数
char* my_strrchr(const char* s, int c)
{
    const char* last = NULL;
    while (*s)
    {
        if (*s == (char)c)
            last = s;
        s++;
    }

    if ((char)c == '\0')
        return (char*)s;

    return (char*)last;
}

// 用于在主字符串中查找子字符串首次出现的位置,
// 找到时返回指向该位置的指针，找不到则返回NULL
char* my_strstr(const char* haystack, const char* needle)
{
    if (!*needle) return (char*)haystack;

    for (; *haystack; haystack++) {
        const char* h = haystack;
        const char* n = needle;
        while (*h && *n && *h == *n) {
            h++;
            n++;
        }
        if (!*n)
            return (char*)haystack;
    }
    return NULL;
}

void* my_memset(void* s, int c, size_t n)
{
    unsigned char* p = (unsigned char*)s;
    while (n--)
        *p++ = (unsigned char)c;
    return s;
}

int my_memcmp(const void* s1, const void* s2, size_t n)
{
    const unsigned char* a = (const unsigned char*)s1;
    const unsigned char* b = (const unsigned char*)s2;

    while(n--) {
        if (*a != *b)
            return (int)*a - (int)*b;
        a++;
        b++;
    }

    return 0;
}

int main()
{
    // 1.
    char str[] = "hello, world";
    int len = my_strlen(str);
    printf("my_strlen: %d\n", len);

    // 2.
    char temp1[len+1] = {0};
    my_strcpy(temp1, str);
    printf("my_strcpy: %s\n", temp1);

    // 3.
    int ret = my_strcmp(str, temp1);
    printf("str == temp1: %d\n", ret);

    // 4.
    char temp2[256] = {"He say, "};
    my_strcat(temp2, str);
    printf("my_strcat: %s\n", temp2);

    // 5.
    char* p = my_strchr(str, 'o');
    printf("my_strchr: %p, %c\n", p, *p);

    // 6.
    char*q = my_strstr(str, "world");
    printf("my_strstr: %p, %s\n", q, q);

    // 7.
    my_memset(temp1, 0, len+1);
    printf("my_memset: %d\n", my_strlen(temp1));

    return 0;
}




