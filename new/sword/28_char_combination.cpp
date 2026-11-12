#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

/*
扩展：如果不是求字符的所有排列，而是求字符的所有组合，应该怎么办？还是输入三个字符a、b、c，则它们的组合有a、b、c、ab、ac、bc、abc。
*/

void combine(const std::string& str, int index,
             std::string& path, std::vector<std::string>& result)
{
   if (index == static_cast<int>(str.size())) {
       if (!path.empty()) {
           result.push_back(path);
       }
       return;
   }

   // 选择当前字符
   path.push_back(str[index]);
   combine(str, index+1, path, result);
   path.pop_back(); // 回溯

   // 不选当前字符
    int next = index+1;
    while (next < static_cast<int>(str.size()) &&
           str[next] == str[index]) {
        ++next;
    }

   combine(str, next, path, result);
}

std::vector<std::string> combination(const std::string& str)
{
    std::vector<std::string> result;
    if (str.empty()) return result;

    // 先排序，后去重
    std::string sortedStr = str;
    std::sort(sortedStr.begin(), sortedStr.end());

    std::string path;
    combine(sortedStr, 0, path, result);
    return result;
}

int main()
{
    {
        std::string str = "abc";
        auto result = combination(str);
        for (const auto& s: result) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
        // 输出: a ab ac b bc c
    }

    {
        std::string str = "aab";
        auto result = combination(str);
        for (const auto& s: result) {
            std::cout << s << " ";
        }
        std::cout << std::endl;
        // 输出: aab aa ab a b
    }

    return 0;
}

