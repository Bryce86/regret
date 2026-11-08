#include <iostream>
#include <vector>
#include <stack>

bool isPopOrder(const std::vector<int>& pushSeq,
                const std::vector<int>& popSeq)
{
    // 先判断相等，再判断空
    if (pushSeq.size() != popSeq.size()) return false;
    if (pushSeq.empty()) return true;

    std::stack<int> stk;
    int popIdx = 0;

    for (int val : pushSeq)
    {
        stk.push(val);
        // 栈顶等于当前要弹出的元素，就持续弹出
        while (!stk.empty() && stk.top() == popSeq[popIdx])
        {
            stk.pop();
            ++popIdx;
        }
    }

    return stk.empty();
}

int main()
{
    std::vector<int> pushSeq = {1,2,3,4,5};

    std::vector<int> popSeq1 = {4,5,3,2,1};
    std::cout << std::boolalpha << isPopOrder(pushSeq, popSeq1) << std::endl; // true

    std::vector<int> popSeq2 = {4,3,5,1,2};
    std::cout << std::boolalpha << isPopOrder(pushSeq, popSeq2) << std::endl; // false

    return 0;
}
