#include <iostream>
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

std::vector<int> levelOrder(TreeNode* root)
{
    std::vector<int> result;
    if (!root) return result;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode* node = q.front();
        q.pop();
        result.push_back(node->val);

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);

    }

    return result;
}

int main()
{
    //       1
    //      / \
    //     2   3
    //    / \   \
    //   4   5   6

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    auto result = levelOrder(root);
    for (auto x : result)
        std::cout << x << " ";
    std::cout << std::endl;

    return 0;
}
