#include <iostream>
#include <string>
#include <cctype>

// 字符串回文
bool isPalindrome(const std::string& s)
{
    int left = 0;
    int right = static_cast<int>(s.size())-1;

    while (left < right) {
        if (s[left] != s[right])
            return false;
        left++;
        right--;
    }
    return true;
}

// 整数回文
// 这个只反转一半数字，避免溢出，时间 O(log₁₀n)。
bool isPalindrome(int x) {
    if (x < 0) return false; // 负数不是回文
    if (x % 10 == 0 && x != 0) return false; // 末尾是0且不是0本身

    int reversed = 0;
    while (x > reversed) {
        reversed = reversed * 10 + x % 10;
        x /= 10;
        std::cout << "reversed: " << reversed << std::endl;
        std::cout << "x: " << x << std::endl;
    }

    // 偶数位：x == reversed
    // 奇数位：x == reversed / 10（中间那位不用比）
    return x == reversed || x == reversed / 10;
}

// 忽略大小写和空格（常见变体）
bool isPalindromeIgnoreCase(const std::string& s)
{
    int left = 0;
    int right = static_cast<int>(s.size())-1;

    while (left < right)
    {
        while (left < right && 
               !std::isalnum((unsigned char)s[left])) {
            left++;
        }
        while (left < right && 
               !std::isalnum((unsigned char)s[right])) {
            right--;
        }

        if (std::tolower((unsigned char)s[left]) != 
            std::tolower((unsigned char)s[right]))
                return false;

        left++;
        right--;
    }
    return true;
}

int main()
{
    std::cout << std::boolalpha 
        << "isPalindrome(\"12321\") => "
        << isPalindrome("12321") << "\n";

    std::cout << std::boolalpha 
        << "isPalindrome(\"123321\") => "
        << isPalindrome("123321") << "\n";

    std::cout << std::boolalpha 
        << "isPalindrome(\"123421\") => "
        << isPalindrome("123421") << "\n";

    std::cout << std::boolalpha 
        << "isPalindrome(12321) => \n"
        << isPalindrome(12321) << "\n";

    std::cout << std::boolalpha 
        << "isPalindrome(123321) => \n"
        << isPalindrome(123321) << "\n";

    std::cout << std::boolalpha 
        << "isPalindrome(123421) => \n"
        << isPalindrome(123421) << "\n";

    // debug
    //isPalindrome(123321);

    return 0;
}

