#include <iostream>
#include <string>
#include <any>

int main()
{
    std::any a = 42;

    // 判断是否有值
    if (a.has_value()) {
        // 获取类型信息, 如 "i" 表示 int
        std::cout << "type: " << a.type().name() << "\n";

        // 安全取值：类型不匹配抛 std::bad_any_cast
        try {
            int x = std::any_cast<int>(a);
            std::cout << "value: " << x << "\n";
        } catch (const std::bad_any_cast& e) {
            std::cerr << e.what() << "\n";
        }
    }

    // 安全取值：指针版本，失败返回 nullptr
    if (auto* p = std::any_cast<int>(&a)) {
        std::cout << "*p: " << *p << "\n";
    }

    a = std::string("hello");
    if (a.has_value()) {
        std::cout << "type: " << a.type().name() << "\n";
        std::string s = std::any_cast<std::string>(a);
        std::cout << "value: " << s << "\n";
    }

    a = 3.14;
    if (a.has_value()) {
        std::cout << "type: " << a.type().name() << "\n";
        double d = std::any_cast<double>(a);
        std::cout << "value: " << d << "\n";
    }

    // 清空
    a.reset();
    if (!a.has_value()) {
        std::cout << "any a is empty!\n";
    }

    return 0;
}

