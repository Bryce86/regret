#include <iostream>
#include <cstring> // 用于 strlen, strcpy 等
#include <stdexcept>

class String {
private:
    char* data; // 指向动态分配的字符数组
    int length; // 字符串长度

public:
    // 1. 默认构造函数
    String() : length(0) {
        data = new char[1];
        data[0] = '\0';
    }

    // 2. 带参构造函数 (从 C 风格字符串构造)
    String(const char* str) {
        if (!str) {
            length = 0;
            data = new char[1];
            data[0] = '\0';
        } else {
            length = strlen(str);
            data = new char[length+1];
            strcpy(data, str);
        }
    }

    // 3. 拷贝构造函数 (深拷贝)
    // 面试考点：防止两个对象指向同一块内存，避免重复释放
    String(const String& other) {
        length = other.length;
        data = new char[length+1];
        strcpy(data, other.data);
    }

    // 4. 赋值运算符重载 (深拷贝)
    // 面试考点：需要处理自赋值，并释放旧内存
    String& operator=(const String& other) {
        if (this == &other) { // 检查自赋值
            return *this;
        }

        delete[] data; // 释放当前对象原有的内存

        length = other.length;
        data = new char[length+1];
        strcpy(data, other.data);

        return *this;
    }

    // 5. 移动构造函数 (C++11 优化)
    // 面试考点：利用右值引用，
    //   通过“窃取”资源来避免不必要的内存分配和拷贝
    String(String&& other) noexcept : data(other.data),
        length(other.length)
    {
        other.data = nullptr;
        other.length = 0;
    }

    // 6. 移动赋值运算符 (C++11 优化)
    String& operator=(String&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            length = other.length;
            other.data = nullptr;
            other.length = 0;
        }
    }

    // 7. 析构函数
    ~String() {
        delete[] data;
    }

    // 8. 获取长度
    int size() const {
        return length;
    }

    // 9. 获取 C 风格字符串
    const char* c_str() const {
        return data;
    }

    // 10. 运算符重载：字符串拼接 (+)
    String operator+(const String& other) const {
        String newStr;
        newStr.length = this->length + other.length;
        newStr.data =  new char[newStr.length+1];

        strcpy(newStr.data, this->data);
        strcat(newStr.data, other.data);

        return newStr;
    }

    // 11. 运算符重载：比较 (==)
    bool operator==(const String& other) const {
        if (this->length != other.length)
            return false;
        return strcmp(this->data, other.data) == 0;
    }

    // 12. 下标访问运算符重载 []
    char& operator[](int index) {
        if (index < 0 || index >= length) {
            // 简单处理：返回第一个字符的引用，实际项目中应抛出异常
            //std::cerr << "Index out of bounds" << std::endl;
            //return data[0];

            throw std::overflow_error("Index out of bounds");
        }
        return data[index];
    }

    // const 版本的下标访问
    const char& operator[](int index) const {
        if (index < 0 || index >= length) {
            std::cerr << "Index out of bounds!" << std::endl;
            return data[0];
        }
        return data[index];
    }

    // 13. 输出流运算符重载 (友元函数)
    friend std::ostream& operator<<(std::ostream &os,
                                    const String& str)
    {
        os << str.data;
        return os;
    }
};

int main()
{
    String s1("Hello");
    String s2(" World");

    // 测试拼接
    String s3 = s1 + s2;
    std::cout << "s3: " << s3 << std::endl;

    // 测试拷贝构造
    String s4(s3);
    std::cout << "s4: " << s4 <<  std::endl;

    // 测试赋值
    String s5;
    s5 = s1;
    std::cout << "s5: " << s5 << std::endl;

    // 测试下标访问
    std::cout << "s1[1]: " << s1[1] << std::endl;

    // 测试比较
    if (s1 == s5) {
        std::cout << "s1 equals s5" << std::endl;
    }

    return 0;
}


