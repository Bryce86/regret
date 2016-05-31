#include <iostream>

using namespace std;

int binarysearch(int *arr, int len, int x)
{

    return -1;
}

int binarysearch_in_recursion(int *arr, int l, int r, int x)
{

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

