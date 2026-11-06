#include <iostream>
#include <cstdint>
#include <cmath>

bool isEqualToZero(double x) {
    const double EPS = 1e-7;
    return x > -EPS && x < EPS;
}

double Power(double base, int exponent)
{
    // double 是浮点数，计算过程中会有精度误差。
    //if (base == 0.0) return 0.0;

    //if (isEqualToZero(base)) return 0.0;
    if (std::fabs(base) < 1e-7) return 0.0;

    // 用无符号整数处理负指数，避免 INT_MIN 取反溢出
    // INT_MAX =  2,147,483,647
    // INT_MIN = -2,147,483,648
    // -INT_MIN = 2,147,483,648
    // 所以 -2,147,483,648 取反后得到的 2,147,483,648 无法用 int 表示。
    uint32_t n;
    bool negative = false;

    if (exponent < 0) {
        negative = true;
        n = static_cast<uint32_t>(-(static_cast<int64_t>(exponent)));
    } else {
        n = static_cast<uint32_t>(exponent);
    }

    double result = 1.0;
    double cur = base;

    /* 快速幂的本质是把指数按二进制展开:
     * 10 = 1010(二进制)
     * = 1×2³ + 0×2² + 1×2¹ + 0×2⁰
     */

    while (n > 0) {
        // 看当前二进制最低位是不是 1：
        // 如果是 1，说明这一位对应的 cur 需要乘进结果；
        // 如果是 0，说明这一位不需要。cur自乘。
        if (n & 1) {               
            result *= cur;
        }
        cur *= cur;                 // base自乘
        n >>= 1;                    // 指数右移
    }
    
    return negative ? 1.0 / result : result;
}

int main()
{
    std::cout << Power(2.0, 10) << std::endl;   // 1024
    std::cout << Power(2.0, -2) << std::endl;   // 0.25
    std::cout << Power(0.0, 5)  << std::endl;   // 0
}

