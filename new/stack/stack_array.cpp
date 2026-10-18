#include <iostream>
#include <stdexcept>

using namespace std;

/*
1. 顺序栈（数组实现）

要点：
top_ 指向栈顶下一个空位，push 先赋值再 ++，pop 先 -- 再访问。
必须写析构函数 delete[] data_，否则内存泄漏。
删除拷贝构造和赋值，防止两个对象共享同一块内存导致 double free。
面试时如果问扩容，可以补一句：可以像 std::vector 一样，满时 new 一块 2 倍大小的数组，memcpy 过去再 delete[] 旧数组
*/

template<typename T>
class StackArray {
private:
    T* data;
    size_t capacity_;
    size_t top_;  // 指向栈顶元素的下一个位置

public:
    explicit StackArray(size_t c = 1024)
        : data(new T[capacity_]), capacity_(c), top_(0) {}

    ~StackArray() {
        delete []data;
    }

    // 禁止拷贝（避免double free）
    StackArray(const StackArray&) = delete;
    StackArray& operator=(const StackArray&) = delete;

    void push(const T& val) {
        if (top_ == capacity_) {
            throw std::overflow_error("Stack overflow");
        }
        data[top_++] = val;
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Stack underflow");
        }
        --top_;
    }

    T& top() {
        if (empty()) {
            throw std::underflow_error("Stack empty");
        }
        return data[top_-1];
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Stack empty");
        }
        return data[top_-1];
    }

    bool empty() const { return top_ == 0; }
    size_t size() const { return top_; }
    size_t capacity() const { return capacity_; }
};

int main()
{
    StackArray<int> st(100);
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    cout << "capacity: " << st.capacity() << "\n";
    cout << "size: " << st.size() << "\n";
    cout << "top: " << st.top() << "\n";
    cout << "empty: " << (st.empty() ? "yes" : "no") << "\n";

    st.pop();
    cout << "pop\n";
    cout << "size: " << st.size() << "\n";
    cout << "top: " << st.top() << "\n";

    return 0;
}
