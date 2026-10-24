#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution
{
public:

    TreeNode* PreInOrderBuildTree(const std::vector<int>& preorder,
                        const std::vector<int>& inorder)
    {
        if (preorder.empty() || inorder.empty() ||
            preorder.size() != inorder.size()) {
            return nullptr;
        }

        // 中序值 -> 下标，加速查找根的位置
        std::unordered_map<int, int> indexMap;
        for (int i = 0; i < (int)inorder.size(); ++i) {
            indexMap[inorder[i]] = i;
        }

        return build_pre_in(preorder, 0, preorder.size()-1,
                            inorder, 0, inorder.size()-1,
                            indexMap);
    }

    TreeNode* InPostOrderBuildTree(const std::vector<int>& inorder,
                                   const std::vector<int>& postorder)
    {
        if (inorder.empty() || postorder.empty() ||
            inorder.size() != postorder.size()) {
            return nullptr;
        }

        // 中序值 -> 下标，方便快速找到根
        std::unordered_map<int, int> indexMap;
        for (int i = 0; i < (int)inorder.size(); ++i) {
            indexMap[inorder[i]] = i;
        }

        int postIdx = (int)postorder.size() - 1;
        return build_in_post(inorder, 0, (int)inorder.size() - 1,
                             postorder, postIdx, indexMap);
    }

    void print_preorder(TreeNode* T) {
        if (!T) return;

        std::cout << T->val << " ";
        print_preorder(T->left);
        print_preorder(T->right);
    }

    void print_inorder(TreeNode* T) {
        if (!T) return;

        print_inorder(T->left);
        cout << T->val << " ";
        print_inorder(T->right);
    }

    void print_postorder(TreeNode* T) {
        if (!T) return;

        print_postorder(T->left);
        print_postorder(T->right);
        cout << T->val << " ";
    }

private:

    TreeNode* build_pre_in(const std::vector<int>& preorder, int preL, int preR,
                                 const std::vector<int>& inorder, int inL, int inR,
                                 const std::unordered_map<int, int>& indexMap)
    {
        if (preL > preR) return nullptr;

        int rootVal = preorder[preL];
        TreeNode* root = new TreeNode(rootVal);

        // 根在中序中的位置
        int inRoot = indexMap.at(rootVal);
        // 左子树节点数
        int leftSize = inRoot - inL;

        // 递归构建左子树
        root->left = build_pre_in(preorder, preL+1, preL+leftSize,
                                  inorder, inL, inRoot-1,
                                  indexMap);

        // 递归构建右子树
        root->right = build_pre_in(preorder, preL+leftSize+1, preR,
                                   inorder, inRoot+1, inR,
                                   indexMap);
        return root;
    }

    /*
前序+中序版本：preorder 数组始终不动，用 preL 和 preR 两个下标来"圈出"当前子树对应的区间。
后序+中序版本：用 postIdx 一个引用变量，从后往前依次消费后序数组的元素。
为什么后序版不需要 postL / postR？
因为后序遍历的顺序是 左 → 右 → 根，倒过来取就是 根 → 右 → 左。
postIdx 从末尾开始，每取一个元素就 postIdx--，天然就是按"根 → 右子树 → 左子树"的顺序消费。
*/

    TreeNode* build_in_post(const std::vector<int>& inorder, int inL, int inR,
                            const std::vector<int>& postorder, int& postIdx,
                            const std::unordered_map<int, int>& indexMap) {
        if (inL > inR) return nullptr;

        int rootVal = postorder[postIdx--];
        TreeNode* root = new TreeNode(rootVal);

        int inRoot = indexMap.at(rootVal);

        // 必须先建右子树，因为 postIdx 是从后往前取的
        root->right = build_in_post(inorder, inRoot + 1, inR,
                                    postorder, postIdx, indexMap);
        root->left  = build_in_post(inorder, inL, inRoot - 1,
                                    postorder, postIdx, indexMap);
        return root;
    }
};

int main()
{
    std::vector<int> preorder  = {1,2,4,7,3,5,6,8};
    std::vector<int> inorder   = {4,7,2,1,5,3,8,6};
    std::vector<int> postorder = {7,4,2,5,8,6,3,1};

    cout << "== PreInOrderBuildTree:\n";

    Solution s1;
    TreeNode* p = s1.PreInOrderBuildTree(preorder, inorder);

    cout << "preorder: ";
    s1.print_preorder(p); cout << "\n";

    cout << "inorder: ";
    s1.print_inorder(p); cout << "\n";

    cout << "postorder: ";
    s1.print_postorder(p); cout << "\n";

    cout << "\n== InPostOrderBuildTree:\n";

    Solution s2;
    TreeNode* q = s2.InPostOrderBuildTree(inorder, postorder);

    cout << "preorder: ";
    s2.print_preorder(q); cout << "\n";

    cout << "inorder: ";
    s2.print_inorder(q); cout << "\n";

    cout << "postorder: ";
    s2.print_postorder(q); cout << "\n";

    return 0;
}


