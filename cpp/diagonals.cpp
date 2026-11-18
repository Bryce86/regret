#include <iostream>
#include <vector>

void printDiagonals(const std::vector<std::vector<int>>& matrix)
{
    if (matrix.empty() || matrix[0].empty()) return;

    int m = matrix.size();
    int n = matrix[0].size();

    // 共有 m + n - 1 条斜线
    for (int d = 0; d < m+n-1; ++d) {
        int r = std::min(d, m-1);
        int c = d - r;

        while (r >= 0 && c < n) {
            std::cout << matrix[r][c] << " ";
            --r;
            ++c;
        }
        std::cout << "\n";
    }
}

// Z 字形：交替方向
void printZigzag(const std::vector<std::vector<int>>& matrix)
{
    if (matrix.empty() || matrix[0].empty()) return;

    int m = matrix.size();
    int n = matrix[0].size();
    bool up = true;

    for (int d = 0; d < m+n-1; ++d)
    {
        int r = std::min(d, m-1);
        int c = d - r;
        
        if (up)
        {
            while (r >= 0 && c < n) {
                std::cout << matrix[r][c] << " ";
                --r;
                ++c;
            }
        } else {
            std::vector<int> temp;
            while (r >= 0 && c < n) {
                temp.push_back(matrix[r][c]);
                --r;
                ++c;
            }
            for (int i = static_cast<int>(temp.size())-1;
                 i >= 0; --i) {
                std::cout << temp[i] << " ";
            }
        }
        
        up = !up;
        std::cout << "\n";
    }
}

int main()
{
    std::vector<std::vector<int>> matrix {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9,10,11,12}
        //{13,14,15,16}
    };

    std::cout << "=== 固定方向（从左下->右上）斜线打印 ===" 
        << std::endl;
    printDiagonals(matrix);

    std::cout << "\n=== Z 字形斜线打印 ===" << std::endl;
    printZigzag(matrix);

    return 0;
}

