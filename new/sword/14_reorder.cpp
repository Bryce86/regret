#include <iostream>
#include <vector>
#include <functional>


/*
复杂度
首尾双指针：时间 O(n)，空间 O(1)，每个元素最多被访问一次。
快慢指针：时间 O(n²)，空间 O(1)，但保证了稳定性。
*/


/*
这道题最经典的解法是双指针：一个从前往后找偶数，一个从后往前找奇数，找到后交换，直到两个指针相遇。

解法一：首尾双指针（面试推荐）
*/

void reorderOddEven(std::vector<int>& nums)
{
    if (nums.empty()) return;

    int left = 0;
    int right = static_cast<int>(nums.size())-1;

    while (left < right)
    {
        // 左指针找偶数
        while (left < right && nums[left] % 2 != 0) {
            ++left;
        }
        // 右指针找奇数
        while (left < right && nums[right] % 2 == 0) {
            --right;
        }
        if (left < right) {
            std::swap(nums[left], nums[right]);
        }
    }
}

/*
可扩展性：面试官可能会问"如果不是奇偶，而是把能被 3 整除的放前面怎么办？"这时可以把判断条件抽成一个函数指针或 lambda，体现解耦思维：
*/

// 调用：reorder(nums, [](int x) { return x % 2 != 0; });
void reorderPredicate(std::vector<int>& nums,
                      std::function<bool(int)> predicate)
{
    int left = 0;
    int right = static_cast<int>(nums.size())-1;

    while (left < right) {
        while (left < right && predicate(nums[left])) ++left;
        while (left < right && !predicate(nums[right])) --right; 
        if (left < right)
            std::swap(nums[left], nums[right]);
    }
}

/*
解法二：快慢指针（保持奇数相对顺序）
如果面试官要求奇数之间、偶数之间的相对顺序不变，就不能用首尾双指针了，可以用类似插入排序的思路：
*/

void reorderOddEvenStable(std::vector<int>& nums)
{
    // 指向下一个奇数应该放的位置
    int pos = 0;    
    for (int i = 0; i < static_cast<int>(nums.size()); ++i)
    {
        if (nums[i] % 2 != 0) {
            // 把 nums[i] 插入到 pos 位置，中间元素后移
            int temp = nums[i];
            for (int j = i; j > pos; --j) {
                nums[j] = nums[j-1];
            }
            nums[pos] = temp;
            ++pos;
        }

    }
}

int main()
{
    std::vector<int> nums = {1,2,3,4,5,6,7,8};
    reorderOddEven(nums);
    for (auto x : nums) std::cout << x << " ";
    std::cout << std::endl;

    std::vector<int> nums1 = {1,2,3,4,5,6,7,8};
    reorderPredicate(nums1,
                     [](int x) {return x % 2 != 0;});
    for (auto x : nums1) std::cout << x << " ";
    std::cout << std::endl;

    std::vector<int> nums2 = {1,2,3,4,5,6,7,8};
    reorderOddEvenStable(nums2);
    for (auto x : nums2) std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}
