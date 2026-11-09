#include <iostream>
#include <vector>

bool verifyPostOrder(const std::vector<int>& postOrder,
                     int left, int right)
{
    // 空数或只有一个节点
    if (left >= right) return true;

    // 最后一个元素是根
    int root = postOrder[right];

    // 找左子树和右子树的界点
    int split = left;
    while (split < right && postOrder[split] < root) {
        split++;
    }

    // 验证右子树部分是否都大于根
    for (int i = split; i < right; ++i) {
        if (postOrder[i] < root) {
            return false;
        }
    }

    // 递归验证左子树[left, split-1] 和 
    // 右子树[split, right-1]
    return verifyPostOrder(postOrder, left, split-1) &&
           verifyPostOrder(postOrder, split, right-1);
}

bool verifyPostOrder(const std::vector<int>& postOrder)
{
    if (postOrder.empty()) return true;

    return verifyPostOrder(postOrder,
                           0,
                           static_cast<int>(postOrder.size())-1);
}

int main()
{
    std::vector<int> seq1 = {5,6,7,9,11,10,8};
    std::cout << std::boolalpha << verifyPostOrder(seq1) << "\n";

    std::vector<int> seq2 = {7,4,6,5};
    std::cout << std::boolalpha << verifyPostOrder(seq2) << "\n";

    return 0;
}

