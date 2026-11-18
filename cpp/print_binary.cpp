#include <iostream>
#include <algorithm>
#include <string>

// 核心思路是不断除以 2，余数倒序拼接；
// 面试里还要额外处理 0 和负数两种边界。

// 基础版：非负整数
std::string decToBin(unsigned int n)
{
    if (n == 0) return "0";

    std::string result;
    while (n > 0) {
        result.push_back('0' + (n % 2));
        n /= 2;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

// 完整版：支持负数
std::string decToBin(int n)
{
    if (n == 0) return "0";

    bool negative = false;
    unsigned int num = static_cast<unsigned int>(n);

    if (n < 0) {
        negative = true;
        num = static_cast<unsigned int>(-static_cast<long long>(n));
    }

    std::string result;
    while (num > 0) {
        result.push_back('0' + (num % 2));
        num /= 2;
    }

    std::reverse(result.begin(), result.end());

    if (negative) {
        result.insert(result.begin(), '-');
    }

    return result;
}

std::string printBinary(unsigned int val)
{
    if (val == 0) return "0";

    std::string result;
    bool started = false;

    for (int i = 31; i >= 0; i--)
    {
        if (val & (1U << i)) {
            result.push_back('1');
            started = true;
        } else if (started) {
            result.push_back('0');
        }
    }
    return result;
}

std::string printBinary32(unsigned int val)
{
    std::string result(32, '0');
    for (int i = 0; i < 32; i++)
    {
        if (val & (1U << (31-i))) {
            result[i] = '1';
        }
    }
    return result;
}

int main()
{
    std::string bin = decToBin(0); // 0
    std::cout << "decToBin(0) => " << bin << "\n";

    bin = decToBin(1); // 1
    std::cout << "decToBin(1) => " << bin << "\n";

    bin = decToBin(10); // 1010
    std::cout << "decToBin(10) => " << bin << "\n";

    bin = decToBin(255); // 11111111
    std::cout << "decToBin(255) => " << bin << "\n";

    bin = decToBin(-5); // -101
    std::cout << "decToBin(-5) => " << bin << "\n";

    bin = printBinary(10);
    std::cout << "printBinary(10) => " << bin << "\n";

    bin = printBinary32(10);
    std::cout << "printBinary32(10) => " << bin << "\n";

    return 0;
}
