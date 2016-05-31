#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

/// 生成N 个不同元素全排列 STL

int main()
{
    //int elements[] = {1, 2, 3, 4};
    int elements[] = {1, 2, 3};
    const size_t N = sizeof(elements) / sizeof(elements[0]);
    std::vector<int> vec(elements, elements+N);

    int count = 0;
    do
    {
        std::cout << ++count << ": ";
        std::copy(vec.begin(), vec.end(),
                  std::ostream_iterator<int>(std::cout, ", "));
/*
        for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        {
            cout << *it << ", ";
        }
*/
        std::cout << std::endl;

    } while (next_permutation(vec.begin(), vec.end()));

    return 0;
}
