#include <iostream>

// 如果面试官说 n 很小：可以直接用 for 循环，
// 但要主动说明"如果 n 很大需要用字符串模拟"。
void print1ToMaxNDigits(int n) {
    if (n <= 0) return;
    int max = 1;
    for (int i = 0; i < n; ++i)
        max *= 10;
    for (int i = 1; i < max; ++i)
        std::cout << i << " ";
}

int main()
{
    print1ToMaxNDigits(3);
    return 0;
}
