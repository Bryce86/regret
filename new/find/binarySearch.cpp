#include <iostream>
#include <vector>

int binarySearch(const std::vector<int>& nums,
                 int target)
{
    int left = 0;
    int right = static_cast<int>(nums.size())-1;

    while (left <= right)
    {
        // 防止 left + right 溢出
        int mid = left + (right-left)/2;

        if (nums[mid] == target) {
            return mid;     // 找到目标
        } else if (nums[mid] < target) {
            left = mid+1;   // 目标在右半部分
        } else {
            right = mid-1;  // 目标在左半部分
        }
    }
    return -1; // 未找到
}

int main()
{
    std::vector<int> nums = {-3,10,11,21,34,54,60,78};
    int target = 21;
    int pos = binarySearch(nums, target);

    if (pos != -1) {
        std::cout << "找到目标，下标为: "
            << pos << "\n";
    } else {
        std::cout << "未找到目标\n";
    }

    return 0;
}

