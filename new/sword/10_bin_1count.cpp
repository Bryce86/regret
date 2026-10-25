#include <iostream>
#include <bitset>

class Solution
{
public:

/*
解法一：利用 n & (n - 1) （最优解）
核心思路：
把一个整数减去1，再和原整数做与运算，会把该整数最右边的一个1变成0。那么一个整数的二进制表示中有多少个1，就可以进行多少次这样的操作。这种方法的时间复杂度只与1的个数有关，非常高效。
*/
    int hammingWeight1(unsigned n)
    {
        int count = 0;
        while (n)
        {
            count++;
            n = n & (n-1); // 每次消除最右边的一个1
        }
        return count;
    }

/*
解法二：逐位判断（常规解法）
核心思路：
利用位运算 & 和右移操作 >>。每次将数字与1进行与运算，判断最低位是否为1，然后将数字无符号右移一位，直到数字变为0。
*/
    int hammingWeight2(unsigned n)
    {
        int count = 0;
        while (n)
        {
            if (n & 1) { // 判断最低位是否为1
                count++;
            }
            n = n >> 1; // 无符号右移一位
        }
        return count;
    }

/*
解法三：使用C++标准库（一行代码）
核心思路：
C++ 标准库 <bitset> 提供了非常方便的位操作容器，可以直接调用 .count() 方法统计1的个数。在实际工程开发中，直接使用标准库是最简洁的。
*/
    int hammingWeight3(unsigned n)
    {
        return std::bitset<32>(n).count();
    }

};

int main()
{
    std::cout << "unsigned size: "
        << sizeof(unsigned) << "\n";

    Solution sol;

    std::cout << "S1 - 9(1001)的二进制中1的个数: "
        << sol.hammingWeight1(9) << "\n";
    std::cout << "S2 - 9(1001)的二进制中1的个数: "
        << sol.hammingWeight2(9) << "\n";
    std::cout << "S3 - 9(1001)的二进制中1的个数: "
        << sol.hammingWeight3(9) << "\n";
}
