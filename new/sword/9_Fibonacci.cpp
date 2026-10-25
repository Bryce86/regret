#include <cstdint>
#include <vector>
#include <iostream>

/*
面试题9：斐波那契数列
题目一：写个数，输入n，求斐波那契数列的第n项。
题目二：一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙调上一个n级台阶总共 有多少种跳法。
*/

// 迭代写法，O(n) 时间，O(1) 空间
long long fibonacci(unsigned n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;

    long long a = 0, b = 1;
    // 因为斐波那契数列默认从第 0 项开始编号，
    // 所以 fibonacci(10) 算的是 F(10)，
    // 也就是第 11 个数。

    // “我这里的 n 表示下标，从 0 开始；
    // 如果题目要求从 1 开始，就把循环条件改成 < n，
    // 或者入参减 1。”
    for (unsigned i = 2; i <= n; ++i)
    {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

/*
为什么面试不推荐用？
递归展开后是一棵树，大量节点被重复计算

F(3) 算了 2 次，F(2) 算了 3 次。
时间复杂度是 O(2^n)，n=40 左右就开始明显卡顿。
*/
long long fibonacciRecursive(unsigned n)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacciRecursive(n-1) +\
           fibonacciRecursive(n-2);
}

// 加个缓存（记忆化递归），降到 O(n)：
long long fiboMemo(unsigned n,
                   std::vector<long long>& memo)
{
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (memo[n] != -1) return memo[n]; // 已经计算过，直接返回
    memo[n] = fiboMemo(n-1, memo) + fiboMemo(n-2, memo);
    return memo[n];
}

long long fibonacciMemo(unsigned n)
{
    std::vector<long long> memo(n+1, -1);
    return fiboMemo(n, memo);
}

long long jumpFloor(unsigned n)
{
    if (n == 0) return 1;
    if (n == 1) return 1;
    if (n == 2) return 2;

    long long a = 1, b = 2;
    for (unsigned i = 3; i <= n; ++i)
    {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

std::vector<long long> fibonacciSequence(unsigned n) {
    std::vector<long long> seq;
    if (n == 0) return seq;

    seq.push_back(0);
    if (n == 1) return seq;

    seq.push_back(1);
    for (unsigned i = 2; i < n; ++i) {
        seq.push_back(seq[i-1]+seq[i-2]);
    }

    return seq;
}

int main()
{
    std::cout << "输出10个斐波那契数列: \n";

    auto seq = fibonacciSequence(10);
    for (size_t i = 0; i < seq.size(); ++i) {
        if (i > 0) std::cout << ", ";

        std::cout << seq[i];
    }
    std::cout << "\n";

    std::cout << "输出第0项斐波那契数列："
        << fibonacci(0) << "\n";
    std::cout << "输出第1项斐波那契数列："
        << fibonacci(1) << "\n";
    std::cout << "输出第9项斐波那契数列："
        << fibonacci(9) << "\n";

    std::cout << "递归-输出第9项斐波那契数列："
        << fibonacciRecursive(9) << "\n";

    std::cout << "递归Memo-输出第9项斐波那契数列："
        << fibonacciMemo(9) << "\n";



    return 0;
}


