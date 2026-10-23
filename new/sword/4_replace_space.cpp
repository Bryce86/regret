#include <iostream>
#include <cstring>

/*
 面试题4：替换空格

 题目：请实现一个函数，把字符串中的每个空格替换成"%20"。例如输入 "We are happy."，则输出"We%20are%20happy."。
 */


using std::cout;
using std::endl;


//为什么需要 length 参数？ 替换后字符串变长，
//必须知道缓冲区上限，防止越界。
void replaceSpace(char str[], int length)
{
    if (str == nullptr || length <= 0) return;

    // 1. 统计空格数
    int oldLen = strlen(str);
    int spaceCnt = 0;

    for (int i = 0; i < oldLen; i++) {
        if (str[i] == ' ')
            ++spaceCnt;
    }

    // 2. 计算新长度，检查缓冲区是否足够
    int newLen = oldLen + spaceCnt * 2; // oldLen里已经包含了空格个数，所以只需要额外补2个
    if (newLen > length) return; // 缓冲区不够

    // 3.
    int oldIdx = oldLen;
    int newIdx = newLen;

    while (oldIdx >= 0 && newIdx > oldIdx)
    {
        if (str[oldIdx] == ' ') {
            str[newIdx--] = '0';
            str[newIdx--] = '2';
            str[newIdx--] = '%';
        } else {
            str[newIdx--] = str[oldIdx];
        }
        --oldIdx;
    }
}

int main()
{
    char str[32] = "Hello, world! Guys!";

    cout << "old str: " << str << endl;

    replaceSpace(str, 32);

    cout << "new str: " << str << endl;

    return 0;
}


