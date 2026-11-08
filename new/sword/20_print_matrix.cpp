#include <iostream>
#include <vector>

std::vector<int> spiralOrder(const std::vector<std::vector<int>>& matrix)
{
    std::vector<int> result;
    if (matrix.empty() || matrix[0].empty())
        return result;

    int top = 0;
    int bottom = static_cast<int>(matrix.size())-1;
    int left = 0;
    int right = static_cast<int>(matrix[0].size())-1;

    while (true)
    {
        // 1. 从左到右打印上边
        for (int i = left; i <= right; ++i) {
            result.push_back(matrix[top][i]);
        }
        if (++top > bottom) break;

        // 2. 从上到下打印右边
        for (int i = top; i <= bottom; ++i) {
            result.push_back(matrix[i][right]);
        }
        if (--right < left) break;

        // 3. 从右到左打印下边
        for (int i = right; i >= left; --i) {
            result.push_back(matrix[bottom][i]);
        }
        if (--bottom < top) break;

        // 4. 从下到上打印左边
        for (int i = bottom; i >= top; --i) {
            result.push_back(matrix[i][left]);
        }
        if (++left > right) break;
    }

    return result;
}

int main()
{
    std::cout << "matrix:\n";
    std::cout << "  { 1,  2,  3,  4}\n";
    std::cout << "  { 5,  6,  7,  8}\n";
    std::cout << "  { 9, 10, 11, 12}\n";
    std::cout << "  {13, 14, 15, 16}\n";
    std::cout << "\n";

    std::vector<std::vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    auto result = spiralOrder(matrix);
    for (auto x : result) 
        std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}



