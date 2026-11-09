#include <iostream>
#include <vector>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

void findPath(TreeNode* root, 
              int target,
              std::vector<int>& path,
              int currentSum,
              std::vector<std::vector<int>>& result)
{
    if (!root) return;

    currentSum += root->val;
    path.push_back(root->val);

    // 到达叶子结点，判断路径和是否等于目标
    bool isLeaf = (!root->left && !root->right);
    if (isLeaf && currentSum == target) {
        result.push_back(path);
    }

    // 递归左右子树
    findPath(root->left, target, path, currentSum, result);
    findPath(root->right, target, path, currentSum, result);

    // 回溯：返回父结点前，把当前结点从路径移除
    path.pop_back();
}

std::vector<std::vector<int>> findPath(TreeNode* root,
                                       int target)
{
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    findPath(root, target, path, 0, result);
    return result;
}

int main()
{
    //        10
    //       /  \
    //      5    12
    //     / \
    //    4   7
    TreeNode* root = new TreeNode(10);
    root->left = new TreeNode(5);
    root->right = new TreeNode(12);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(7);

    auto paths = findPath(root, 22);
    for (auto& p : paths) {
        for (int x : p) std::cout << x << " ";
        std::cout << std::endl;
    }
    // 输出：
    // 10 5 7
    // 10 12

    return 0;
}

