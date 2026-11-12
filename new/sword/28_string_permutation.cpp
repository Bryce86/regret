#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


void permute(std::string& str, int start,
             std::vector<std::string>& result)
{
    if (start == static_cast<int>(str.size())-1) {
        result.push_back(str);
        return;
    }

    for (int i = start; i < static_cast<int>(str.size()); ++i)
    {
        // 跳过重复字符，避免产生重复排列
        if (i != start && str[i] == str[start]) continue;

        std::swap(str[start], str[i]); // 固定第 start 个字符
        permute(str, start+1, result); // 递归排列剩余字符
        std::swap(str[start], str[i]); // 回溯，恢复原状
    }
}

std::vector<std::string> permutation(std::string str)
{
    std::vector<std::string> result;
    if(str.empty()) return result;

    std::sort(str.begin(), str.end()); // 先排序，方便去重
    permute(str, 0, result);
    return result;
}

int main()
{
    {
        std::string str = "abc";
        auto result = permutation(str);
        for (const auto& s : result) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
        // 输出：abc acb bac bca cab cba
    }

    {
        std::string str = "aab";
        auto result = permutation(str);
        for (const auto& s : result) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
        // 输出：aab aba baa （去重）
    }

    return 0;
}

