#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/*
用C++写一个函数, 如 Foo(const char *str), 打印出 str 的全排列,
如 abc 的全排列: abc, acb, bca, dac, cab, cba
*/

/// 全排列的递归实现 (全排列数f(n)=n!(定义0!=1) => 3! = 3*2*1 = 6)

/*
为方便起见，用123来示例下。123的全排列有123、132、213、231、312、321这六种。
首先考虑213和321这二个数是如何得出的。显然这二个都是123中的1与后面两数交换得到的。
然后可以将123的第二个数和每三个数交换得到132。同理可以根据213和321来得231和312。
因此可以知道——全排列就是从第一个数字起每个数分别与它后面的数字交换。

在全排列中去掉重复的规则——去重的全排列就是从第一个数字起每个数分别与它后面非重复出现的数字交换。
用编程的话描述就是第i个数与第j个数交换时，要求[i,j)中没有与第j个数相等的数。
*/

void Swap(char *a, char *b)
{
    char t = *a;
    *a = *b;
    *b = t;
}

// 在数组arr中，[l, r)中是否有数字与下标为r的数字相等
bool IsSwap(char *arr, int l, int r)
{
    for (int i = l; i < r; ++i)
        if (arr[i] == arr[r])
            return false;
    return true;
}

#define DEBUG_LOG

#ifdef DEBUG_LOG
int x = 0;
std::string space("");
#endif

//k表示当前选取到第几个数,m表示共有多少数.
void AllRange(char *arr, int k, int m)
{
#ifdef DEBUG_LOG
    ++x;
    space.clear();
    for (int j = 1; j < x; ++j)
        space += "\t";
    cout << space.c_str() << "#" << x << ": IN, k=" << k << endl;
#endif

    if (k == m)
    {
        static int line = 1;

#ifdef DEBUG_LOG
        cout << space.c_str() << "#" << x << ": 第" << line++ << "个排列：" << "<<< " << arr << " >>>" << endl;
#else
        cout << "\t第" << line++ << "个排列：" << arr << endl;
#endif
    }
    else
    {
        /// 第i个数分别与它后面的数字交换就能得到新的排列
        for (int i = k; i <= m; ++i)
        {
            if (IsSwap(arr, k, i))
            {
#ifdef DEBUG_LOG
                cout << space.c_str() << "#" << x << ": LOOP : k=" << k << ", i=" << i << endl;
                std::string old = arr;
#endif

                Swap(arr+k, arr+i);

#ifdef DEBUG_LOG
                cout << space.c_str() << "#" << x << ": SWAP 1: " << old.c_str() << " => " << arr << ", DOWN >>" << endl;
#endif

                AllRange(arr, k+1, m);

#ifdef DEBUG_LOG
                old.clear(); old = arr;
#endif

                Swap(arr+k, arr+i);

#ifdef DEBUG_LOG
                cout << space.c_str() << "#" << x << ": SWAP 2: " << old.c_str() << " => " << arr << endl;
#endif
            }
        }
    }

#ifdef DEBUG_LOG
    cout << space.c_str() << "#" << x-- << ": OUR OF AR ! UP <<" << endl;
    space.clear();
    for (int j = 1; j < x; ++j)
        space += "\t";
#endif
}

void Foo(char *str)
{
    AllRange(str, 0, strlen(str)-1);
}

int main()
{
    cout << "去重全排列的递归实现" << endl;
    char str[] = "123";
    cout << "string(" << str << ")的全排列如下：" << endl;
    Foo(str);

    return 0;
}
