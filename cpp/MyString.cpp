#include <iostream>
#include <cstring>
#include <algorithm>
#include <utility>
#include <ostream>


class MyString {
public:
    // 1. 默认构造函数
    MyString() : m_data(new char[1]) {
        m_data[0] = '\0'; // 保证是空字符串
        std::cout << "Default Constructor called" << std::endl;
    }

    // 2. 带参构造函数（从 C 风格字符串构造）
    MyString(const char* str) {
        if (str) {
            size_t len = std::strlen(str);
            m_data = new char[len+1]; // +1 用于存放 '\0'
            std::strcpy(m_data, str);
        } else {
            m_data = new char[1];
            m_data[0] = '\0';
        }
        std::cout << "Parameterized Constructor called" << std::endl;
    }

    // 3. 拷贝构造函数（深拷贝）
    MyString(const MyString& other) 
        : m_data(new char[std::strlen(other.m_data)+1])
    {
        std::strcpy(m_data, other.m_data);
        std::cout << "Copy Constructor called" << std::endl;
    }

    // 4. 移动构造函数（C++11 新增，窃取资源）
    MyString(MyString&& other) noexcept
        : m_data(other.m_data)
    {
        // 关键：将源对象置空，防止其析构时释放我们窃取的内存
        other.m_data = nullptr;
        std::cout << "Move Constructor called" << std::endl;
    }

    // 5. 析构函数
    ~MyString() {
        delete[] m_data;
        std::cout << "Destructor called" << std::endl;
    }

    // 6. 拷贝赋值运算符（深拷贝 + 异常安全）
    MyString& operator=(const MyString& other) {
        std::cout << "Copy Assignment called" << std::endl;
        // 防止自我赋值
        if (this != &other) {
            // 异常安全策略：先分配新内存，成功后再释放旧内存
            char* newData = new char[std::strlen(other.m_data)+1];
            std::strcpy(newData, other.m_data);
            delete[] m_data; // 释放旧内存
            m_data = newData;
        }
        return *this;
    }

    // 7. 移动赋值运算符（C++11 新增，窃取资源）
    MyString& operator=(MyString&& other) noexcept {
        std::cout << "Move Assignment called" << std::endl;
        if (this != &other) {
            delete[] m_data;        // 释放自己的旧资源
            m_data = other.m_data;  // 窃取资源
            other.m_data = nullptr; // 源对象置空
        }
        return *this;
    }

    // 辅助函数：获取长度
    size_t length() const {
        return std::strlen(m_data);
    }

    // 辅助函数：获取 C 风格字符串
    const char* c_str() const {
        return m_data;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const MyString& str);

private:
    char* m_data;
};

std::ostream& operator<<(std::ostream& os,
                                const MyString& str)
{
    os << str.m_data;
    return os;
}


int main()
{
    std::cout << "=== 1. 测试默认构造与带参构造 ===" << std::endl;
    MyString s1;                  // 默认构造
    MyString s2("Hello, World!"); // 带参构造
    std::cout << "s1: '" << s1.c_str() << "' (长度: " << s1.length() << ")\n";
    std::cout << "s2: '" << s2.c_str() << "' (长度: " << s2.length() << ")\n";

    std::cout << "\n=== 2. 测试拷贝构造 (深拷贝) ===" << std::endl;
    MyString s3(s2);              // 拷贝构造
    // 或者 MyString s3 = s2;
    std::cout << "s3: '" << s3.c_str() << "'\n";
    
    // 验证深拷贝：修改 s3 不应影响 s2
    // 假设你的类提供了修改字符串的方法，这里仅作逻辑演示
    // s3 = "Modified String"; 
    // std::cout << "修改 s3 后，s2 仍为: '" << s2.c_str() << "'\n";

    std::cout << "\n=== 3. 测试移动构造 (窃取资源) ===" << std::endl;
    MyString s4("Move me!");
    std::cout << "移动前 s4: '" << s4.c_str() << "'\n";
    MyString s5(std::move(s4));   // 移动构造
    std::cout << "移动后 s5: '" << s5.c_str() << "'\n";
    // 注意：移动后 s4 处于有效但未指定状态，通常指针被置空
    // std::cout << "移动后 s4: '" << s4.c_str() << "' (预期为空或 nullptr)\n";

    std::cout << "\n=== 4. 测试拷贝赋值 ===" << std::endl;
    MyString s6("Initial s6");
    s6 = s2;                      // 拷贝赋值
    std::cout << "s6 拷贝赋值后: '" << s6.c_str() << "'\n";

    std::cout << "\n=== 5. 测试移动赋值 ===" << std::endl;
    MyString s7("Initial s7");
    MyString s8("Move assign me!");
    s7 = std::move(s8);           // 移动赋值
    std::cout << "s7 移动赋值后: '" << s7.c_str() << "'\n";

    std::cout << "\n=== 6. 测试自我赋值 (防崩溃) ===" << std::endl;
    return 0;
}


