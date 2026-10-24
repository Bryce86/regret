#include <stack>
#include <stdexcept>
#include <iostream>

template <typename T>
class CQueue {
public:
    void appendTail(const T& value) {
        stackIn.push(value);
    }

    T deleteHead() {
        // 出队栈有元素，直接弹
        if (!stackOut.empty()) {
            T val = stackOut.top();
            stackOut.pop();
            return val;
        }

        // 出队栈空了，把入队栈全部倒过来
        if (stackIn.empty()) {
            throw std::runtime_error("queue is empty");
        }

        while (!stackIn.empty()) {
            stackOut.push(stackIn.top());
            stackIn.pop();
        }

        T val = stackOut.top();
        stackOut.pop();
        return val;
    }

    bool isEmpty() {
        return stackIn.empty() && stackOut.empty();
    }

private:

    std::stack<T> stackIn;
    std::stack<T> stackOut;
};

int main()
{
    CQueue<int> cq;
    cq.appendTail(1);
    cq.appendTail(2);
    cq.appendTail(3);

    while (!cq.isEmpty()) {
        int val = cq.deleteHead();
        std::cout << val << " ";
    }
    std::cout << "\n";


    return 0;
}

