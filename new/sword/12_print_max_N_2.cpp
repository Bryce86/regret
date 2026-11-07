#include <iostream>
#include <string>

void generate(std::string& num, int index)
{
    if (index == static_cast<int>(num.size())) {
        // 打印，去掉前导零
        bool leadingZero = true;
        for (char c : num) {
            if (leadingZero && c == '0')
                continue;
            leadingZero = false;
            std::cout << c;
        }
        if (!leadingZero)
            std::cout << " ";
        return;
    }

    for (int i = 0; i <= 9; ++i) {
        num[index] = i + '0';
        generate(num, index+1);
    }
}

void print1ToMaxNDigits(int n) {
    if (n < 0) return;

    std::string num(n, '0');
    generate(num, 0);
    std::cout << std::endl;
}

int main()
{
    print1ToMaxNDigits(3);
    return 0;
}

