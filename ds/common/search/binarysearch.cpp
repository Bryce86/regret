#include <iostream>

using namespace std;

int binarysearch(int *arr, int len, int x)
{
    int l = 0, r = len - 1;

    while (l <= r)
    {
        int mid = (l + r) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            l = mid + 1;
        else /* if (arr[mid] > x) */
            r = mid - 1;
    }

    return -1;
}

int binarysearch_in_recursion(int *arr, int l, int r, int x)
{
    if (l <= r)
    {
        int mid = (l + r) / 2;

        if (arr[mid] == x)
            return mid;
        else if (arr[mid] < x)
            return binarysearch_in_recursion(arr, mid + 1, r, x);
        else /* if (arr[mind] > x)*/
            return binarysearch_in_recursion(arr, l, mid - 1, x);
    }

    return -1;
}

int main()
{
    int array[] = {1,2,3,4,5,6,7,8,9,10};
    int len = sizeof(array)/sizeof(array[0]);

    int idx = binarysearch(array, len, 5);
    cout << idx << endl;

    idx = binarysearch_in_recursion(array, 0, len-1, 8);
    cout << idx << endl;

    return 0;
}

