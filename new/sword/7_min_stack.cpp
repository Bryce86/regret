#include <stack>
#include <stdexcept>
#include <algorithm>
#include <iostream>

class MinStack {
public:
    void push(int value) {
        data.push(value);
        // 辅助栈为空，或新值更小/相等时，压入辅助栈
        if (minStack.empty() ||
            value <= minStack.top())
        {
            minStack.push(value);
        }
    }

    void pop() {
        if (data.empty()) {
            throw std::runtime_error("stack is empty");
        }

        // 只有弹出的元素正好是当前最小值时，辅助栈才弹
        if (data.top() == minStack.top()) {
            minStack.pop();
        }
        data.pop();
    }

    int top() const {
        if (data.empty()) {
            throw std::runtime_error("stack is empty");
        }
        return data.top();
    }

    int min() const {
        if (minStack.empty()) {
            throw std::runtime_error("stack is empty");
        }
        return minStack.top();
    }

private:

    std::stack<int> data;
    std::stack<int> minStack;
};

int main()
{
    MinStack ms;
    ms.push(3);
    ms.push(4);
    ms.push(5);

    std::cout << "min => " << ms.min() << "\n";

    ms.push(1);
    std::cout << "min => " << ms.min() << "\n";

    return 0;
}

