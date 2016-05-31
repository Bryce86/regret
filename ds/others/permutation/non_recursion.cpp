#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/// 全排列的非递归实现

/*

要考虑全排列的非递归实现，先来考虑如何计算字符串的下一个排列。如"1234"的下一个排列就是"1243"。
只要对字符串反复求出下一个排列，全排列的也就迎刃而解了。

如何计算字符串的下一个排列了？
如何计算字符串的下一个排列了？来考虑"926520"这个字符串，我们从后向前找第一双相邻的递增数字，
"20"、"52"都是非递增的，"26 "即满足要求，称前一个数字2为替换数，替换数的下标称为替换点，
再从后面找一个比替换数大的最小数（这个数必然存在），0、2都不行，5可以，将5和2交换得到"956220"，
然后再将替换点后的字符串"6220"颠倒即得到"950226"。

对于像"4321"这种已经是最“大”的排列，采用STL中的处理方法，将字符串整个颠倒得到最“小”的排列"1234"并返回false。

这样，只要一个循环再加上计算字符串下一个排列的函数就可以轻松的实现非递归的全排列算法。
按上面思路并参考STL中的实现源码，不难写成一份质量较高的代码。

*/

void Swap(char *a, char *b)
{
    if (*a != *b)
    {
        char c = *a;
        *a = *b;
        *b = c;
    }
}

// 反转区间
void Reverse(char *a, char *b)
{
    while (a < b)
    {
        Swap(a++, b--);
    }
}

// 下一个排列
bool Nex_permutation(char *arr)
{
    char *pEnd = arr + strlen(arr);
    if (arr == pEnd)
        return false;

    char *p, *q, *pFind;
    pEnd--; // 指向最后一个元素
    p = pEnd;

    // 从后向前，查找一双相邻的递增数字
    while (p != arr)
    {
        q = p;
        --p;
        if (*p < *q) //找降序的相邻2数,前一个数即替换数
        {
             //从后向前找比替换点大的第一个数
            pFind = pEnd;
            while (*pFind <= *p)
                --pFind;

            // 替换
            Swap(pFind, p);
            // 替换点后的数全部反转
            Reverse(q, pEnd);
            return true;
        }
    }
    Reverse(p, pEnd); // 如果没有下一个排列,全部反转后返回false
    return false;
}

int QsortCmp(const void *pa, const void *pb)
{
    return *(char *)pa - *(char *)pb;
}

int main()
{
    cout << "全排列的非递归实现：" << endl;
    char str[] = "abc";
    cout << str << "的全排列如下: " << endl;
    // 加上排序
    qsort(str, strlen(str), sizeof(str[0]), QsortCmp);

    int i = 1;
    do
    {
        cout << "第" << i++ << "个排列: " << str << endl;
    } while (Nex_permutation(str));

    return 0;
}
