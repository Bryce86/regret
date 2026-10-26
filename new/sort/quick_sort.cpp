#include <iostream>
#include <vector>
#include <algorithm>

/*
快速排序是面试里最常考的原地排序算法之一。它的核心思路是：选一个基准值 pivot，把数组分成“小于 pivot / 大于 pivot”两部分，然后递归排序左右区间。
*/

// 1. 基础版：Lomuto 分区法
int partition(std::vector<int>& nums,
              int left, int right)
{
    // 选最右元素作为基准
    int pivot = nums[right];
    // i 指向“小于 pivot 区域”的最后一个位置
    int i = left-1;

    for (int j = left; j < right; ++j)
    {
        if (nums[j] < pivot) {
            ++i;
            std::swap(nums[i], nums[j]);
        }
    }

    std::swap(nums[i+1], nums[right]);
    return i+1; // pivot 的最终位置
}

void quickSort(std::vector<int>& nums, int left,
               int right)
{
    if (left >= right) return;

    int pivotPos = partition(nums, left, right);
    quickSort(nums, left, pivotPos-1);
    quickSort(nums, pivotPos+1, right);
}

int main()
{
    std::vector<int> nums = {10,7,8,9,1,5,7,3};
    quickSort(nums, 0, static_cast<int>(nums.size())-1);

    for (int x : nums) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}

