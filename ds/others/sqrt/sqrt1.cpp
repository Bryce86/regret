#include <iostream>
#include <math.h>
using namespace std;

namespace MATH {

int sqrt(int x)
{
    if (x < 1)
        return x;

    int l = 1;
    int r = x;
    int mid = 0;
    
    while (l <= r)
    {
        mid = l + (r - l) / 2; 

        if (mid == x / mid)
            return mid;
        else if (mid < x / mid)
            l = mid + 1;
        else
            r = mid - 1;
    }

    return r;
}

}

int main()
{
    cout << MATH::sqrt(16) << endl;
    cout << MATH::sqrt(10) << endl;

    cout << sqrt(16) << endl;
    cout << sqrt(10) << endl;

    return 0;
}
