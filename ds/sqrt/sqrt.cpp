#include <iostream>
#include <stdlib.h>
using namespace std;

float epsilon = 0.000001;

float sqrtByBisection(float n)
{
   if (n < 0) 
       return n;
   
   float mid, last;
   float low = 0, high = n;

   mid = (low + high) / 2;

   do
   { 
       if (mid * mid > n)
           high = mid;
       else
           low = mid;
       
       last = mid;
       mid = (high + low ) / 2;
   } while (abs(mid - last) > epsilon);

   return mid;
}

int main()
{
    float x = sqrtByBisection(16);
    cout << x << endl;

    x = sqrtByBisection(9);
    cout << x << endl;

    return 0;
}

