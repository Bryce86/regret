#include <utility>
#include <string>
#include <iostream>

void process(int& x) { std::cout << "lvalue\n"; }
void process(int&& x) { std::cout << "rvalue\n"; }

template<typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg));
}

int main()
{
    std::string s = "hello";
    std::string t = std::move(s);       // 触发移动构造
    std::cout << "s: " << s << "\n";    // 通常为空
    std::cout << "t: " << t << "\n";

    int x = 10;
    // T 推导为 int&，转发为左值，调用 process(int&)
    wrapper(x);
    // T 推导为 int，转发为右值，调用 process(int&&)
    wrapper(20);

    return 0;
}
