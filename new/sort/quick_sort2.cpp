#include <iostream>
#include <vector>
#include <algorithm>

/*
medianOfThree 要找的不是最小值，而是 左端、中间、右端三个元素里的中位数。而且这个函数还有一个隐藏目的：顺便把这三个位置排成 nums[left] ≤ nums[mid] ≤ nums[right]，这样后面把 nums[mid] 换到 nums[right] 时，pivot 更稳定，也能避免一些极端情况。
*/

int medianOfThree(std::vector<int>& nums,
                  int left,
                  int right)
{
    int mid = left + (right-left)/2;

    if (nums[left] > nums[mid])
        std::swap(nums[left], nums[mid]);
    if (nums[left] > nums[right])
        std::swap(nums[left], nums[right]);
    if (nums[mid] > nums[right])
        std::swap(nums[mid], nums[right]);

    return mid;
}

void insertSort(std::vector<int>& nums,
                int left, int right)
{
    for (int i = left+1; i <= right; ++i)
    {
        int key = nums[i];
        int j = i-1;
        while (j >= left && nums[j] > key) {
            nums[j+1] = nums[j];
            --j;
        }
        nums[j+1] = key;
    }
}

int partition(std::vector<int>& nums,
              int left, int right)
{
    int mid = medianOfThree(nums, left, right);
    // 把基准放到最右
    std::swap(nums[mid], nums[right]);

    int pivot = nums[right];
    int i = left-1;

    for (int j = left; j < right; ++j) {
        if (nums[j] < pivot) {
            ++i;
            std::swap(nums[i], nums[j]);
        }
    }

    std::swap(nums[i+1], nums[right]);
    return i+1;
}

void quickSort(std::vector<int>& nums,
               int left, int right)
{
    if (left >= right) return;

    if (right - left + 1 <= 16) {
        std::cout << "use insert sort ...\n";
        insertSort(nums, left, right);
        return;
    }

    std::cout << "use quick sort ...\n";

    int pivotPos = partition(nums, left, right);
    quickSort(nums, left, pivotPos-1);
    quickSort(nums, pivotPos+1, right);
}

int main()
{
    std::vector<int> nums = {22,10,7,12,8,19,9,1,5,7,3,21,2,11,6,17,0};

    quickSort(nums, 0, static_cast<int>(nums.size())-1);

    for (auto x : nums) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}








