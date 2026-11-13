#include <iostream>
#include <vector>
#include <cmath>

// 埃氏筛实现
void printPrimeInN(const int N)
{
    std::vector<bool> is_prime(N+1, true);
    is_prime[0] =  is_prime[1] = false;

    for (int i = 2; i * i <= N; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= N; j += i ) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";
}

// 暴力试除写法
bool isPrime(int n) {
    if (n < 2) return false;
    
    for (int i = 2; i*i <= n; ++i) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    // 埃氏筛实现
    printPrimeInN(100);

    // 暴力试除写法
    for (int i = 2; i <= 100; ++i) {
        if (isPrime(i)) {
            std::cout << i << " ";
        }
    }
    std::cout << "\n";

    return 0;
}

