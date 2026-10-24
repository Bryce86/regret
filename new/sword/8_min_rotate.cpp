#include <vector>
#include <iostream>
#include <stdexcept>

/*
面试要点
* 为什么和 nums[right] 比而不是 nums[left]？ 和右端比能明确区分 mid 在哪一段；和左端比会出现歧义（比如 mid 在第二段但比 left 大）。
* right = mid 还是 mid - 1？ 因为 mid 可能就是最小值，不能跳过，所以是 right = mid。

* 相等时为什么只能 --right？ 无法确定最小值在哪边，但 nums[right] 和 nums[mid] 相等，去掉 right 不会丢掉最小值（mid 还在）。

* 边界检查：空数组、未旋转数组、全相同元素都要覆盖。
*/

int minInRotatedArray(const std::vector<int>& nums)
{
    if (nums.empty()) {
        throw std::runtime_error("array is empty");
    }

    int left = 0, right = (int)nums.size()-1;

    // 如果没旋转（或旋转了 n 个），第一个就是最小
    if (nums[left] < nums[right]) {
        return nums[left];
    }

    while (left < right)
    {
        int mid = left + (right-left)/2;

        if (nums[mid] > nums[right]) {
            // mid 还在第一段，最小值在右边
            left = mid + 1;
        } else if (nums[mid] < nums[right]) {
            // mid 在第二段，最小值在左边（含 mid）
            right = mid;
        } else {
            // nums[mid] == nums[right]，无法判断，右边界收缩
            --right;
        }
    }

    return nums[left];
}

int main()
{
    std::vector<int> v1 = {3,4,5,1,2};
    std::vector<int> v2 = {1,0,1,1,1};

    std::cout << "min(3,4,5,1,2): "
        << minInRotatedArray(v1) << "\n";
    std::cout << "min(1,0,1,1,1): "
        << minInRotatedArray(v2) << "\n";

    return 0;
}
