#include <iostream>
#include <vector>

/*
1. 基础版冒泡排序
这是最直观的实现，通过两层循环，每次比较相邻元素，如果顺序错误就交换。
*/
void bubbleSortBasic(std::vector<int>& arr)
{
    int n = arr.size();

    for (int i = 0; i < n-1; ++i) { // 外层控制轮数
        for (int j = 0; j < n-1-i; ++j) { // 内层负责相邻比较
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

/*
2. 优化版：提前终止（面试高频）
如果某一轮遍历中没有发生任何交换，说明数组已经完全有序，可以直接跳出循环。这个优化在面试中经常被问到，最好能主动提出来。
*/
void bubbleSortOptimized(std::vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        // 标记本轮是否发生交换
        bool swapped = false;
        for (int j = 0; j < n-1-i; ++j) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        // 如果没有交换，说明已经有序
        if (!swapped) break;
    }
}

/*
3. 进阶优化：记录最后交换位置
如果在某一轮中，最后发生交换的位置是 lastSwapIndex，那么该位置之后的元素已经是有序的了，下一轮只需要遍历到 lastSwapIndex 即可。
*/
void bubbleSortAdvanced(std::vector<int>& arr)
{
    int n = arr.size();
    int lastSwapIndex = n-1; // 记录最后一次交换的位置

    for (int i = 0; i < n-1; ++i) {
        int currSwapIndex = 0;
        bool swapped = false;

        for (int j = 0; j < lastSwapIndex; ++j) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                swapped = true;
                currSwapIndex = j;
            }
        }
        if (!swapped) break;
        lastSwapIndex = currSwapIndex;
    }
}

/*
4. 泛型模板实现
在 C++ 中，使用模板可以让排序函数支持 int、double、string 等多种数据类型，这在考察 C++ 语言特性时很有用。
*/
template <typename T>
void bubbleSortGeneric(std::vector<T>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n-1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n-1-i; ++j) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// 递归函数1：负责单轮遍历，将当前未排序部分的最大值“冒泡”到末尾
// 作用相当于内层 for (int j = 0; j < n - 1 - i; ++j)
void bubblePass(std::vector<int>& arr, int j , int n)
{
    // 边界条件：当 j 到达本轮末尾时，单轮结束
    if (j >= n-1) return;

    // 比较相邻元素，逆序则交换
    if (arr[j] > arr[j+1]) {
        std::swap(arr[j], arr[j+1]);
    }

    bubblePass(arr, j+1, n);
}

// 递归函数2：负责控制整体排序的轮数
// 作用相当于外层 for (int i = 0; i < n - 1; ++i)
void bubbleSortRecursive(std::vector<int>& arr, int n)
{
    // 边界条件：如果只需要排序1个或0个元素，直接返回
    if (n <= 1) return;

    // 执行一轮冒泡，将最大的元素沉底到 arr[n-1] 的位置
    bubblePass(arr, 0, n);

    // 递归处理剩下的前 n-1 个元素
    bubbleSortRecursive(arr, n-1);

}

// 封装调用接口
void bubbleSort(std::vector<int>& arr) {
    bubbleSortRecursive(arr, arr.size());
}

int main()
{
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};

    std::cout << "排序前：";
    for (auto x : arr) std::cout << x << " ";
    std::cout << "\n";

    auto copy = arr;
    bubbleSortBasic(copy);
    std::cout << "基础排序：";
    for (auto x : copy) std::cout << x << " ";
    std::cout << "\n";

    copy = arr;
    bubbleSortOptimized(copy);
    std::cout << "优化排序：";
    for (auto x : copy) std::cout << x << " ";
    std::cout << "\n";

    copy = arr;
    bubbleSortAdvanced(copy);
    std::cout << "进阶优化排序：";
    for (auto x : copy) std::cout << x << " ";
    std::cout << "\n";

    copy = arr;
    bubbleSort(copy);
    std::cout << "递归排序：";
    for (auto x : copy) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}

