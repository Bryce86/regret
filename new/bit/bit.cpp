#include <iostream>
#include <vector>

using namespace std;


template<class T>
void printBinary(T a)
{
    // index [31, 0]
    for (int i = sizeof(a)*8-1; i >= 0; --i)
    {
        if ((a >> i) & 1)
            cout << "1";
        else
            cout << "0";

        if (i == 8)
            cout << " ";
    }
    cout << "\n";
}

int hammingWeight(unsigned int n) {
    int cnt = 0;
    while (n)
    {
        n &= (n-1);
        ++cnt;
    }
    return cnt;
}

int main()
{
    {
//各二进位全部右移若干位，对无符号数，高位补0，有符号数，
//各编译器处理 方法不一样，有的补符号位（算术右移），
//有的补0（逻辑右移）
        cout << "验证负数右移后高位按符号位补位：\n";
        cout << "15>>2 = " << (15 >> 2) << "\n";
        cout << "-15>>2 = " << (-15 >> 2) << "\n";
    }

    {
//判断奇偶(Odd/Even)
//只要根据最未位是0还是1来决定，为0就是偶数，为1就是奇数。
        cout << "判断奇偶：\n";
        // even
        cout << "10以内偶数：";
        for (int i = 0; i < 10; i++) {
            if ((i & 1) == 0)
                cout << i << " ";
        }
        cout << "\n";
        // odd
        cout << "10以内奇数：";
        for (int i = 0; i < 10; i++) {
            if ((i & 1) == 1)
                cout << i << " ";
        }
        cout << "\n";
    }

    {
//交换两数
        cout << "交换两数：\n";
        int a = 10;
        int b = 20;
        cout << "before: " << "a: " << a
             << ", b: " << b << endl;
        if (a != b)
        {
            a^=b;
            b^=a;
            a^=b;
        }
        cout << "after: " << "a: " << a
             << ", b: " << b << endl;
    }

    {
        auto signReversal = [](int x) {
            return ~x+1;
        };
//变换符号
// 变换符号只需要取反后加1即可。
        cout << "变换符号：\n";
        int a = 7;
        int b = -8;
        cout << "7  => " << signReversal(a) << "\n";
        cout << "-8 => " << signReversal(b) << "\n";

//求绝对值
        auto my_abs = [](int x) {
            int i = x >> 31;
            return i == 0 ? x : (~x+1);
        };
        cout << "求10和-10的绝对值：\n";
        cout << "abs(10) "  << my_abs(10) << "\n";
        cout << "abs(-10) " << my_abs(-10) << "\n";

//对于任何数，与0异或都会保持不变，与1即0xFFFFFFFF异或就相当于取反
//因此，a与i异或后再减i（因为i为0或1，所以减i即是要么加0要么加1）也可以得到 绝对值。
        // 这种方法没用任何判断表达式
        auto my_abs1 = [](int x) {
            int i = x >> 31;
            return ((x^i)-i);
        };
        cout << "求20和-20的绝对值：\n";
        cout << "abs(20) "  << my_abs1(20) << "\n";
        cout << "abs(-20) " << my_abs1(-20) << "\n";
    }

//高低位交换
//给出一个16位的无符号整数。称这个二进制数的前8位为“高位”，后8位为“低位”。现在写 一程序将它的高低位交换。


    {
        cout << "高低位交换: \n";
        unsigned short a = 34520;
        cout << "before swapping: ";
        printBinary(a);

        a = (a >> 8) | (a << 8);
        cout << "after swapping: ";
        printBinary(a);
    }

//二进制逆序

    {
        cout << "二进制逆序：\n" ;
    }

//二进制中1的个数（求余法、位运算法、快速法 和 查表法）
//缺失的数字 （只有一个数字出现一次，其他数字都出现两次）
//数组中只出现1次的两个数字
//数组中只出现一次的数

    {
        cout << "数字2026的二进制中1的个数：\n";
        cout << "2026 => ";
        printBinary(short(2026));
        cout << "hammingWeight(2026) => " << hammingWeight(2026) << endl;
    }

// 判断 2 的幂
// 要点：2 的幂二进制里只有一个 1，所以 n & (n - 1) 为 0。别忘了 n > 0。

    {
        auto isPowerOfTwo = [](int n) {
            return n > 0 && (n & (n-1)) == 0;
        };

        cout << "8是2的幂：" << (isPowerOfTwo(8) ? "yes" : "no") << endl;
        cout << "10是2的幂：" << (isPowerOfTwo(10) ? "yes" : "no") << endl;
    }


// 只出现一次的数字

    {
        // 版本 A：其他数字都出现两次，只有一个出现一次
        // 要点：a ^ a = 0，a ^ 0 = a，异或满足交换律，成对的会消掉。
        auto singleNumber1 = [](std::vector<int> nums) {
            int res = 0;
            for (int x : nums) res ^= x;
            return res;
        };

        cout << "singleNumber1(1,1,2,3,3) => " <<
            singleNumber1({1,1,2,3,3}) << endl;

        // 版本 B：其他数字都出现三次，只有一个出现一次
        // 要点：用两个变量记录每一位出现 1 次和 2 次的状态，出现 3 次时清零。
        auto singleNumber2 = [](std::vector<int> nums) {
            int ones = 0;
            int twos = 0;
            for (int x : nums) {
                ones = (ones ^ x) & ~twos;
                twos = (twos ^ x) & ~ones;
            }
            return ones;
        };

        cout << "singleNumber1(1,1,1,2,3,3,3) => " <<
            singleNumber2({1,1,1,2,3,3,3}) << endl;
    }

// 数组中只出现1次的两个数字
// 核心思路是分组异或：先把两个目标数分到不同组，再分别异或求解

    {
        // need to specify return type
        auto singleTwoNumbers = [](std::vector<int> nums) -> std::vector<int> {
            int xor_all = 0;
            // 1. 全部异或，得到 a ^ b
            for (int x : nums)
                xor_all ^= x;

            // 2. 取最低位的 1 作为分组依据
            int mask = xor_all & (-xor_all);

            // 3. 按 mask 分组异或
            int a = 0, b = 0;
            for (int x : nums) {
                if (x & mask)
                    a ^= x;
                else
                    b ^= x;
            }
            return {a, b};
        };

        std::vector<int> res = singleTwoNumbers({1,1,2,3,3,5});
        cout << "singleTwoNumbers({1,1,2,3,3,5}) => ";
        for (auto x : res) cout << x << " ";
        cout << "\n";
    }


// 不用加减法做加法
// 要点：a ^ b 是不进位加法，(a & b) << 1 是进位，
// 反复迭代直到进位为 0。注意进位转 unsigned 避免左移未定义行为。
    {
        auto getSum = [](int a, int b) {
            while (b) {
                // 进位
                unsigned carry = (unsigned)(a & b) << 1;
                a = a ^ b;
                b = carry;
            }
            return a;
        };

        cout << "不用加减法做加法: ";
        cout << "a, b => " << getSum(2, 3) << endl;
    }

// 二进制逆序
// 要点：每次取 n 最低位，左移拼入 res。进阶可用分治位交换或查表法。
    {
        auto reverseBits = [](unsigned int n)
            -> unsigned int {
            unsigned int res = 0;
            for (int i = 0; i < 32; ++i) {
                res = (res << 1) | (n & 1);
                n >>= 1;
            }
            return res;
        };
        cout << "二进制逆序（基础版）：\n";
        printBinary(13);
        int res = reverseBits(13);
        printBinary(res);

    }

    return 0;
}

