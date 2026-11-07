#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
解法一：字符串模拟大数（面试推荐）
核心思路：用一个长度为 n 的字符数组表示当前数字，
每次给它 +1，然后打印。
*/


// 对数字字符串 +1，返回是否溢出（即已经超过最大 n 位数）
bool increment(std::string& num)
{
    bool overflow = false;
    int carry = 1; // 初始进位为 1，相当于 +1

    for (int i = static_cast<int>(num.size())-1; i >= 0; --i)
    {
        int sum = num[i] - '0' + carry;
        if (sum >= 10) {
            if (i == 0) {
                overflow = true; // 最高位也进位，说明已经溢出
            } else {
                num[i] = '0';
                carry = 1;
            }
        } else {
            num[i] = sum + '0'; // 没有进位了，直接退出
            break;
        }
    }
    return overflow;
}

// 打印数字字符串，去掉前导零
void printNumber(const std::string& num) {
    bool leadingZero = true;
    for (char c : num) {
        if (leadingZero && c == '0')
            continue;
        leadingZero = false;
        std::cout << c;
    }
    if (!leadingZero) 
        std::cout << " ";
}

void print1ToMaxNDigits(int n) {
    if (n <= 0) return;

    std::string num(n, '0');  // 初始化为 "000...0"

    // 从1一个一个的递增+输出到N
    while (!increment(num)) {
        printNumber(num);
    }
}

int main()
{
    print1ToMaxNDigits(3);
    std::cout << std::endl;

    return 0;
}











