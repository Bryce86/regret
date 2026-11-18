#include <stdio.h>
#include <stddef.h>
#include <math.h>

// 方法一：二分法（整数版，LeetCode 69）
int my_sqrt_int(int x)
{
    if (x < 2) return x;

    int left = 1;
    int right = x / 2;
    int ans = 0;

    while (left <= right)
    {
        int mid = left + (right-left)/2;
        long long sq = (long long)mid * mid;

        if (sq == x) {
            return mid;
        } else if (sq < x) {
            ans = mid;
            left = mid+1;
        } else {
            right = mid-1; 
        }
    }
    return ans;
}

// 方法二：牛顿迭代法（浮点版）
double my_sqrt(double x)
{
    if (x < 0) return -1.0;
    if (x == 0.0 || x == 1.0) return x;

    double g = x;
    double eps = 1e-7;

    while (fabs(g * g - x) > eps) {
        g = (g + x / g) / 2.0;
    }

    return g;
}

// 方法三：二分法（浮点版）
double my_sqrt_bin(double x)
{
    if (x < 0) return -1.0;
    if (x == 0.0 || x == 1.0) return x;

    double lo = x > 1.0 ? 0.0 : x;
    double hi = x > 1.0 ? x : 1.0;
    double eps = 1e-7;

    while (hi - lo > eps)
    {
        double mid = lo + (hi-lo) / 2.0;
        if (mid * mid < x)
            lo = mid;
        else
            hi = mid;
    }
    return lo;
}

int main()
{
    int sq = my_sqrt_int(16);
    printf("sqrt(16) => %d\n", sq);

    return 0;
}
