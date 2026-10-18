#include <iostream>
#include <stack>
#include <stdexcept>

using namespace std;

/*
两个栈实现队列:

核心思路是“入队往 in 栈放，出队从 out 栈取；
out 空了就把 in 全倒过去”。
*/

template<typename T>
class QueueByTwoStacks {
private:
    std::stack<T> in;
    std::stack<T> out;

    // 把 in 栈全部倒入 out 栈
    void transfer() {
        cout << "transferring from in to out ...\n";
        while (!in.empty()) {
            out.push(in.top());
            in.pop();
        }
    }

public:
    void push(const T& val) {
        in.push(val);
    }

    T pop() {
        if (empty()) {
            throw std::underflow_error("Queue empty");
        }

        if (out.empty()) {
            transfer();
        }

        T val = out.top();
        out.pop();
        return val;
    }

    T& front() {
        if (empty()) {
            throw std::underflow_error("Queue empty");
        }

        if (out.empty()) {
            transfer();
        }

        return out.top();
    }

    bool empty() const {
        return in.empty() && out.empty();
    }

    size_t size() const {
        return in.size() + out.size();
    }
};

int main()
{
    QueueByTwoStacks<int> q;
    q.push(1);
    q.push(2);
    q.push(3);

    cout << "front: " << q.front() << "\n";

    q.pop();
    q.pop();

    q.push(4);
    cout << "front: " << q.front() << "\n";
    cout << "size: " << q.size() << "\n";

    q.pop();
    q.pop();

    return 0;
}
