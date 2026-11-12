#include <stdio.h>
#include <ctype.h>
#include <limits.h> // INT_MAX/INT_MIN
#include <stdlib.h> // strtol
#include <stdbool.h>

int my_atoi(const char* str)
{
    if (!str) return 0;

    // 1. 跳过前导空白
    while (isspace((unsigned char)*str)) {
        str++;
    }

    // 2. 处理正负号
    int sign = 1;
    if (*str == '+' || *str == '-') {
        if (*str == '-') sign = -1;
        str++;
    }

    // 3. 逐位转换
    long result = 0;
    while (isdigit((unsigned char)*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }
    
    result *= sign;

    // 4. 溢出截断
    if (result > INT_MAX) return INT_MAX;
    if (result < INT_MIN) return INT_MIN;

    return (int)result;
}

int my_atoi_strict(const char* str) {
    if (!str) return 0;

    char* end = NULL;
    long val = strtol(str, &end, 10);

    if (val > INT_MAX) return INT_MAX;
    if (val < INT_MIN) return INT_MIN;

    return (int)val;
}

// 标准 atoi 本身无法区分“字符串是 "0"”和“字符串无法转换 / 为空”。
// 改进方案一：用 strtol
bool safe_atoi(const char* str, int* out) {
    if (!str || !out) return false;

    while (isspace((unsigned char)*str))
        str++;

    if (*str == '\0')
        return false;

    char* end = NULL;
    long val = strtol(str, &end, 10);

    if (end == str)    // 没有解析到任何数字
        return false;

    if (val > INT_MAX || val < INT_MIN) 
        return false;

    *out = (int)val;
    return true;
}

// 改进方案二：手动实现时加状态
bool my_safe_atoi(const char* str, int* out)
{
    if (!str || !out) {
        return false;
    }

    while (isspace((unsigned char)*str)) {
        str++;
    }

    int sign = 1;
    if (*str == '+' || *str == '-') {
        if (*str == '-') sign = -1;
        str++;
    }

    if (!isdigit((unsigned char)*str)) {
        return false;
    }

    long result = 0;
    while (isdigit((unsigned char)*str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    result *= sign;

    if (result > INT_MAX || result < INT_MIN) {
        return false;
    }

    *out = (int)result;
    return true;
}

int main()
{
    {
        printf("atoi ==>\n");
        printf("7788: %d\n", my_atoi("7788"));
        printf("-2233: %d\n", my_atoi("-2233"));
        printf("NULL: %d\n", my_atoi(NULL));
        printf("'0': %d\n", my_atoi("0"));
        printf("abc: %d\n", my_atoi_strict("abc"));
        printf("\"\": %d\n", my_atoi_strict(""));
        printf("11a22: %d\n", my_atoi("11a22"));
        printf("--------------------------\n");
    }

    //printf("%d\n", true);
    //printf("%d\n", false);

    {
        printf("safe atoi ==>\n");
        int out = 0;
        bool ret = my_safe_atoi("7788", &out);
        //bool ret = safe_atoi("7788", &out);
        printf("7788 ret: %d, out: %d\n", ret, out);

        out = 0;
        ret = my_safe_atoi("-2233", &out);
        printf("-2233 ret: %d, out: %d\n", ret, out);

        out = 0;
        ret = my_safe_atoi(NULL, &out);
        printf("NULL ret: %d, out: %d\n", ret, out);

        out = 0;
        ret = my_safe_atoi("0", &out);
        printf("\"0\" ret: %d, out: %d\n", ret, out);

        out = 0;
        ret = my_safe_atoi("abc", &out);
        printf("abc ret: %d, out: %d\n", ret, out);

        out = 0;
        ret = my_safe_atoi("", &out);
        printf("\"\" ret: %d, out: %d\n", ret, out);

        out = 0;
        ret = my_safe_atoi("11a22", &out);
        printf("11a22 ret: %d, out: %d\n", ret, out);
    }

    return 0;
}

