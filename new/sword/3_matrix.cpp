#include <iostream>
#include <vector>

bool findNumberIn2DArray(const std::vector<std::vector<int>>& matrix, int target)
{
    if (matrix.empty() || matrix[0].empty()) return false;

    int rows = matrix.size();
    int cols = matrix[0].size();

    int row = 0, col = cols-1; // 从右上角出发

    while (row < rows && col >= 0)
    {
        int cur = matrix[row][col];

        if (cur == target) {
            return true;
        } else if (cur > target) {
            --col; // 当前值太大，排除这一列
        } else { // cur < target
            ++row; // 当前值太小，排除这一行
        }
    }

    return false;
}

int main()
{
    std::vector<std::vector<int>> matrix = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 12},
        {6, 8, 11, 15}
    };

    bool r = findNumberIn2DArray(matrix, 7);
    std::cout << "find 7: " << (r ? "yes" : "no") << std::endl;

    r = findNumberIn2DArray(matrix, 5);
    std::cout << "find 5: " << (r ? "yes" : "no") << std::endl;

    return 0;
}

