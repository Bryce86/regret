#include <iostream>
#include <cstring>

void removeDuplicates(char str[]) {
    if (str == nullptr) return;

    bool appeared[256] = {false}; // ASCII 字符出现标记
    int slow = 0;

    for (int fast = 0; str[fast] != '\0'; ++fast)
    {
        unsigned char ch = str[fast];
        if (!appeared[ch]) {
            appeared[ch] = true;
            str[slow++]  = str[fast]; // 保留该字符
        }
        // 如果已出现过，fast 继续前进，slow 不动，相当于跳过
    }
    str[slow] = '\0'; // 截断尾部
}

void removeConsecutiveDuplicates(char str[])
{
    if (str == nullptr || str[0] == '\0') return;

    int slow = 0; // 慢指针指向结果串的末尾

    for (int fast = 1; str[fast] != '\0'; ++fast) {
        if (str[fast] != str[slow]) {
            str[++slow] = str[fast]; // 与上一个保留字符不同，写入
        }
        // 相同则跳过，相当于删除连续重复
    }
    str[slow+1] = '\0';
}

int main()
{
    char s1[] = "google";
    removeDuplicates(s1);
    std::cout << s1 << std::endl; // gole

    char s2[] = "abacbc";
    removeDuplicates(s2);
    std::cout << s2 << std::endl; // abc

    // consecutive
    char s3[] = "aabbc";
    removeConsecutiveDuplicates(s1);
    std::cout << s3 << std::endl; // abc

    char s4[] = "aaabbbccc";
    removeConsecutiveDuplicates(s4);
    std::cout << s4 << std::endl; // abc

    char s5[] = "abcabc";
    removeConsecutiveDuplicates(s5);
    std::cout << s5 << std::endl; // abcabc

    return 0;
}

