#include <queue>
#include <stdexcept>
#include <iostream>

template <typename T>
class CStack {
public:
    void push(const T& value) {
        q1.push(value);
    }

    T pop() {
        if (q1.empty()) {
            throw std::runtime_error("stack is empty");
        }

        // 把前 n-1 个元素挪到 q2
        while (q1.size() > 1) {
            q2.push(q1.front());
            q1.pop();
        }

        // 剩下的最后一个就是栈顶
        T val = q1.front();
        q1.pop();

        // 交换 q1 和 q2，保证下次操作仍在 q1 上
        std::swap(q1, q2);
        return val;
    }

    T top() const {
        if (q1.empty()) {
            throw std::runtime_error("stack is empty");
        }
        // 队列尾部就是栈顶
        return q1.back();
    }

    bool empty() const {
        return q1.empty();
    }

private:

    std::queue<T> q1; // 主队列
    std::queue<T> q2; // 辅助队列
};

int main()
{
    CStack<int> cs;
    cs.push(1);
    cs.push(2);
    cs.push(3);

    std::cout << "top: " << cs.top() << "\n";

    while (!cs.empty()) {
        std::cout << cs.pop() << " ";
    }
    std::cout << "\n";

    return 0;
}

