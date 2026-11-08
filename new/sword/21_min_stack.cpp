#include <iostream>
#include <stack>
#include <stdexcept>

class MinStack {
private:
    std::stack<int> dataStack;
    std::stack<int> minStack;

public:
    void push(int value) {
        dataStack.push(value);
        if (minStack.empty() || value <= minStack.top()) {
            minStack.push(value); // 只在更小或相等时才压入
        }
    }

    void pop() {
        if (dataStack.empty()) {
            throw std::runtime_error("stack is empty");
        }
        if (dataStack.top() == minStack.top()) {
            minStack.pop(); // 只有弹出的元素是当前最小值时，才弹出辅助栈
        }
        dataStack.pop();
    }

    int top() {
        if (dataStack.empty()) {
            throw std::runtime_error("stack is empty");
        }
        return dataStack.top();
    }

    int min() {
        if (minStack.empty()) {
            throw std::runtime_error("stack is empty");
        }
        return minStack.top();
    }
};

int main()
{
    MinStack stack;
    stack.push(3);
    stack.push(4);
    stack.push(2);
    stack.push(1);
    std::cout << stack.min() << std::endl; // 1
    stack.pop();
    std::cout << stack.min() << std::endl; // 2
    stack.pop();
    std::cout << stack.min() << std::endl; // 3

    return 0;
}


