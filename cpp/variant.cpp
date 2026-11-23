#include <variant>
#include <iostream>
#include <string>

int main()
{
    std::variant<int, std::string> v = 42;

    // 1. 
    int x = std::get<int>(v);
    std::cout << "get x: " << x << "\n";

    // 2.
    if (auto* p = std::get_if<int>(&v)) {
        std::cout << "get_if *p: " << *p << "\n";
    }

    // 3.
    std::visit([](const auto& val) {
        std::cout << val << "\n";
    }, v);

    return 0;
}

