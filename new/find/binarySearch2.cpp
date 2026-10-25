#include <iostream>
#include <vector>

/*
常见变体

二分查找在面试里经常不会只考“找是否存在”，还会考：
@ 找第一个等于 target 的位置；
@ 找最后一个等于 target 的位置；
@ 找第一个大于等于 target 的位置，类似 lower_bound；
@ 找第一个大于 target 的位置，类似 upper_bound；
@ 在旋转有序数组中查找目标。

这五个变体在面试中非常高频，建议统一用 [left, right] 闭区间 + while (left <= right) 来写，不容易出错。
*/


// 1. 找第一个等于 target 的位置
int lowerEqual(const std::vector<int>& nums,
               int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size())-1;
    int ans = -1;

    while (left <= right)
    {
        int mid = left + (right-left)/2;

        if (nums[mid] == target) {
            ans = mid;
            // 继续向左找更早出现的target
            // => [left, mid-1]
            right = mid-1;
        } else if (nums[mid] < target) {
            left = mid+1;
        } else {
            right = mid-1;
        }
    }
    return ans;
}

// 2. 找最后一个等于 target 的位置
int upperEqual(const std::vector<int>& nums,
               int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size())-1;
    int ans = -1;

    while (left <= right)
    {
        int mid = left + (right-left)/2;

        if (nums[mid] == target) {
            ans = mid;
            // 继续向右找更晚出现的 target
            // => [mid+1, right]
            left = mid+1;
        } else if (nums[mid] < target) {
            left = mid+1;
        } else {
            right = mid-1;
        }
    }
    return ans;
}

// 3. 找第一个大于等于 target 的位置（类似lower_bound）
int lowerBound(const std::vector<int>& nums,
               int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size())-1;
    // 未找到时返回越界位置
    int ans = static_cast<int>(nums.size());

    while (left <= right)
    {
        int mid = left + (right-left)/2;

        if (nums[mid] >= target) {
            ans = mid;
            // 尝试找更靠左的 >= target
            right = mid-1;
        } else {
            left = mid+1;
        }
    }
    return ans;
}

// 4. 找第一个大于 target 的位置（类似upper_bound）
int upperBound(const std::vector<int>& nums,
               int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size())-1;
    int ans = static_cast<int>(nums.size());

    while (left <= right)
    {
        int mid = left + (right-left)/2;

        if (nums[mid] > target) {
            ans = mid;
            // 尝试找更靠左的 > target
            right = mid-1;
        } else {
            left = mid+1;
        }
    }
    return ans;
}

// 5. 在旋转有序数组中查找 target
int searchRotated(const std::vector<int>& nums,
                  int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size())-1;

    while (left <= right)
    {
        int mid = left + (right-left)/2;

        if (nums[mid] == target) {
            return mid;
        }

        // 判断左半部分是否有序
        if (nums[left] <= nums[mid]) {
            if (nums[left] <= target && target < nums[mid])
            {
                right = mid-1;  // target 在有序左半部分
            } else {
                left = mid+1;
            }
        }
        // 右半部分有序
        else {
            if (nums[mid] < target && target <= nums[right])
            {
                left = mid+1; // target 在有序右半部分
            } else {
                right = mid-1;
            }
        }
    }
    return -1;
}

int main()
{
    std::vector<int> nums1 = {1,2,2,2,3,4,5};
    std::cout << "第一个等于2："
        << lowerEqual(nums1, 2) << "\n";
    std::cout << "最后一个等于2："
        << upperEqual(nums1, 2) << "\n";
    std::cout << "第一个>=2："
        << lowerBound(nums1, 2) << "\n";
    std::cout << "第一个>2："
        << upperBound(nums1, 2) << "\n";

    std::vector<int> num2 = {4,5,6,7,0,1,2};
    std::cout << "旋转数组找0："
        << searchRotated(num2, 0) << "\n";

    return 0;
}

















