#include <utility>
#include <iostream>
#include <vector>
#include <string>

auto call = [](auto&& func, auto&&... args) {
    return std::forward<decltype(func)>(func)(
           std::forward<decltype(args)>(args)...);
};

void greet(const char* name) {
    std::cout << "Hello, " << name << "\n";
}

void log(int x) {
    std::cout << "value: " << x << "\n";
}

template<typename F>
void invoke(F&& f) {
    std::forward<F>(f)();
}

int main() {
    // 1.
    call(greet, "world"); // 函数指针 + 字符串字面量

    // 2.
    std::vector<std::string> v = {"hello, world"};

    for (auto&& s : v) {
        std::cout << s << "\n";
    }

    // 3. 
    //invoke([&]{log(42);});
    invoke([]{log(42);});


    return 0;
}

