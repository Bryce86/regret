#include <iostream>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using std::cout;
using std::endl;

void Swap(int &a, int &b) {
}

void BubbleSort(int *array, int len) {
}

void BubbleSort1(int *array, int len) {
}

void BubbleSort2(int *array, int len) {
}

void SelectSort(int *array, int len) {
}

void InsertSort(int *array, int len) {
}

void InsertSort1(int *array, int len) {
}

void mergearray(/*specify arguments*/) {
}

void mergesort(/*specify arguments*/) {
}

void MergeSort(int *array, int len) {
}

void quicksort(/*specify arguments*/) {
}

void QuickSort(int *array, int len) {
}

void ShellSort(int *array, int len) {
}

void maxHeapDownAdjust(/*specify arguments*/) {
}

void makeMaxHeap(/*specify arguments*/) {
}

void MaxHeapSort(int *array, int len) {
}

#define MAX_VALUES 10
#define VALUES_RANGE 100

void showArray(int *array, int len, std::string prefix)
{
    assert(len >= 0);

    cout << prefix.c_str();
    for (int i = 0; i < len; ++i)
        cout << array[i] << " ";
    cout << endl;
}

int main()
{
    int array[MAX_VALUES] = {0};
    // generate array elements by random

    int len = MAX_VALUES;
    srand((unsigned)time(NULL));
    std::string prefix;

    // display origin array
    for (int i = 0; i < len; ++i) {
        array[i] = rand() % VALUES_RANGE;
    }
    prefix = ">> Initial Array: ";
    showArray(array, len, prefix);

    // input the index of per sort algorithms
    cout << ">> Choose sort algorithm: \n"
         << "1. Bubble 1\n"
         << "2. Bubble 2\n"
         << "3. Bubble 3\n"
         << "4. Select\n"
         << "5. Insert 1\n"
         << "6. Insert 2\n"
         << "7. Shell\n"
         << "8. Merge\n"
         << "9. Quick\n"
         << "0. Heap\n"
         << ">> ";

    char c = getchar();

    switch (c)
    {
    case '1':
	    BubbleSort(array, len);

        prefix = "Bubble: ";
        break;
    case '2':
        BubbleSort1(array, len);

        prefix = "Bubble1: ";
        break;
    case '3':
        BubbleSort2(array, len);

        prefix = "Bubble2: ";
        break;
    case '4':
        SelectSort(array, len);
        
        prefix = "Select: ";
        break;
    case '5':
        InsertSort(array, len);

        prefix = "Insert: ";
        break;
    case '6':
        InsertSort1(array, len);

        prefix = "Insert1: ";
        break;
    case '7':
        ShellSort(array, len);	

        prefix = "Shell: ";
        break;
    case '8':
        MergeSort(array, len);

        prefix = "Merge: ";
        break;
    case '9':
        QuickSort(array, len);

        prefix = "Quick: ";
        break;
    case '0':
        MaxHeapSort(array, len);

        prefix = "Heap: ";
        break;
    default:

end:
        cout << "idx(" << c << ") invalid or out of range." << endl;
        return -1;
    }

    showArray(array, len, prefix);

    return 0;
}

