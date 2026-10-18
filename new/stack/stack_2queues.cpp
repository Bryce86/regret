#include <iostream>
#include <queue>
#include <stdexcept>

using namespace std;

/*
核心点：
每次 push 时，把新元素放进 aux_，再把 main_ 所有元素依次搬到 aux_ 后面；
交换后，main_ 的队首就是最新元素，也就是栈顶；
pop / top 直接取 main_.front()，O(1)。
*/

template<typename T>
class StackByTwoQueues {
private:
    std::queue<T> main;
    std::queue<T> aux;

public:
    void push(const T& val) {
        aux.push(val);
        while (!main.empty())
        {
            aux.push(main.front());
            main.pop();
        }
        cout << "swap ...\n";
        std::swap(main, aux);
    }

    T pop() {
        if (empty())
            throw std::underflow_error("Stack empty");

        T val = main.front();
        main.pop();
        return val;
    }

    T& top() {
        if (empty())
            throw std::underflow_error("Stack empty");

        return main.front();
    }

    bool empty() const {
        return main.empty();
    }
};

/*
执行过程:

push(1): main = [1]
push(2): aux = [2], 搬 main → aux → [2,1], 交换 → main = [2,1]
push(3): aux = [3], 搬 main → aux → [3,2,1], 交换 → main = [3,2,1]

pop(): 取 main.front() → 3
pop(): 取 main.front() → 2
*/

int main()
{
    StackByTwoQueues<int> st;
    st.push(1);
    st.push(2);
    st.push(3);

    cout << "top: " << st.top() << "\n";
    st.pop();
    cout << "top: " << st.top() << "\n";
    st.pop();
    cout << "top: " << st.top() << "\n";

    return 0;
}

