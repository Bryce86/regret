#include <iostream>

class Singleton {
public:

    // 全局唯一访问入口
    static Singleton& getInstance() {
        static Singleton instance; // C++11 保证线程安全，首次调用时初始化
        return instance;
    }

    // 禁止拷贝
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // 禁止移动
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;

    void doSomething() const {
        std::cout <<"Singleton working" << std::endl;
    }

private:

    Singleton() {
        std::cout << "Singleton created" << std::endl;
    }

    ~Singleton() {
        std::cout << "Singleton destroyed" << std::endl;
    }
};

int main()
{
    Singleton::getInstance().doSomething();
    Singleton::getInstance().doSomething();

    return 0;
}

