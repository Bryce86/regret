#include <iostream>
#include <stdexcept>

using namespace std;

/*
2. 链式栈（单链表实现）

要点：
栈顶就是链表头部，push 是头插，pop 是删头节点，都是 O(1)。
析构函数必须遍历链表逐个 delete，否则内存泄漏。
同样要删除拷贝构造和赋值。

*/

template <typename T>
class StackList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& val, Node* n = nullptr)
            : data(val), next(n) {}
    };

    Node* head_;
    size_t size_;

public:

    StackList() : head_(nullptr), size_(0) {}

    ~StackList() {
        while (head_) {
            Node* tmp = head_;
            head_ = head_->next;
            delete tmp;
        }
    }

    // 禁止拷贝
    StackList(const StackList&) = delete;
    StackList& operator=(const StackList&) = delete;

    // 头插
    void push(const T& val) {
        head_ = new Node(val, head_);
        ++size_;
    }

    void pop() {
        if (empty()) {
            throw std::underflow_error("Stack empty");
        }

        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
    }

    T& top() {
        if (empty()) {
            throw std::underflow_error("Stack empty");
        }
        return head_->data;
    }

    const T* top() const {
        if (empty()) {
            throw std::underflow_error("Stack empty");
        }
        return head_->data;
    }

    bool empty() const { return size_ == 0; }
    size_t size() const { return size_; }
};

int main()
{
    StackList<int> st;
    st.push(1);
    st.push(2);
    st.push(3);
    st.push(4);
    st.push(5);

    cout << "size: " << st.size() << "\n";
    cout << "top: " << st.top() << "\n";

    cout << "pop\n";
    st.pop();

    cout << "size: " << st.size() << "\n";
    cout << "top: " << st.top() << "\n";

    while (!st.empty()) {
        st.pop();
    }

    cout << "empty: " << (st.empty() ? "yes" : "no") << "\n";

    return 0;
}

