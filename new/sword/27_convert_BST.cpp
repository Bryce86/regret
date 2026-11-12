#include <iostream>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    TreeNode* prev = nullptr; // 中序遍历的前驱节点
    TreeNode* head = nullptr; // 双向链表的头节点

    void inorder(TreeNode* node) {
        if (!node) return;

        inorder(node->left);

        // 处理当前节点
        if (!prev) {
            // 第一个节点，作为链表头
            head = node;
        } else {
            prev->right = node;
            node->left = prev;
        }
        prev = node;

        inorder(node->right);
    }

public:
    TreeNode* convert(TreeNode* root) {
        if (!root) return nullptr;
        inorder(root);
        return head;
    }
};

// 辅助函数：正向打印链表
void printList(TreeNode* head) {
    TreeNode* cur = head;
    while (cur) {
        std::cout << cur->val;
        if (cur->right)
            std::cout << " <-> ";
        cur = cur->right;
    }
    std::cout << std::endl;
}

// 辅助函数：反向打印链表（验证双向）
void printListBackward(TreeNode* tail) {
    TreeNode* cur = tail;
    // 先找到尾节点
    while (cur && cur->right)
        cur = cur->right;
    while (cur) {
        std::cout << cur->val;
        if (cur->left)
            std::cout << " <-> ";
        cur = cur->left;
    }
    std::cout << std::endl;
}

int main()
{
    //       4
    //      / \
    //     2   5
    //    / \
    //   1   3
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(5);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;
    TreeNode* head = sol.convert(root);

    std::cout << "Forward : ";
    printList(head);

    std::cout << "Backward: ";
    printListBackward(head);

    return 0;
}

