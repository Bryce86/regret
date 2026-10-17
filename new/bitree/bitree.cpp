#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char c) : data(c), left(nullptr), right(nullptr) {}
};

TreeNode* buildFromStr(const std::string& s, int& idx)
{
    if (idx >= s.size()) return nullptr;

    char ch = s[idx++];
    if (ch == '#') return nullptr;

    TreeNode* root = new TreeNode(ch);
    root->left = buildFromStr(s, idx);
    root->right = buildFromStr(s, idx);
    return root;
}

TreeNode* createTree() {
    char ch;
    std::cin >> ch;
    if (ch == '#') return nullptr;

    TreeNode* root = new TreeNode(ch);
    root->left = createTree();
    root->right = createTree();
    return root;
}

void createTree(TreeNode*& T) {
    char ch;
    std::cin >> ch;
    if (ch == '#') { T = nullptr; return; }

    T = new TreeNode(ch);
    createTree(T->left);
    createTree(T->right);
}

void preorder(TreeNode* T) {
    if (!T) return;
    cout << T->data << " ";
    preorder(T->left);
    preorder(T->right);
}

void inorder(TreeNode* T) {
    if (!T) return;
    inorder(T->left);
    cout << T->data << " ";
    inorder(T->right);
}

void postorder(TreeNode* T) {
    if (!T) return;
    postorder(T->left);
    postorder(T->right);
    cout << T->data << " ";
}

// un-recursive
void preorderIter(TreeNode* T) {
    std::stack<TreeNode*> s;
    TreeNode* p = T;

    while (p || !s.empty())
    {
        while (p)
        {
            cout << p->data << " ";
            s.push(p);
            p = p->left;
        }

        p = s.top()->right;
        s.pop();
    }
}

void inorderIter(TreeNode* T)
{
    std::stack<TreeNode*> s;
    TreeNode* p = T;

    while (p || !s.empty())
    {
        while (p)  // 一路向左，全部压栈
        {
            s.push(p);
            p = p->left;
        }

        p = s.top(); // 左边走到头了，访问栈顶
        s.pop();
        cout << p->data << " ";
        p = p->right; // 转向右子树（重复上述过程）
    }
}

// 写法 1：双栈法（最直观，面试首选）
// 后序是「左右根」，而「根右左」恰好是前序把左右入栈顺序对调的结果；再把结果逆序，就是后序。第二个栈正好完成逆序。
void postorderIter1(TreeNode* root)
{
    if (!root)
        return;

    std::stack<TreeNode*> s1, s2;
    s1.push(root);

    while (!s1.empty())
    {
        TreeNode* cur = s1.top();
        s1.pop();
        s2.push(cur);
        if (cur->left) s1.push(cur->left);
        if (cur->right) s1.push(cur->right);
    }

    while(!s2.empty())
    {
        std::cout << s2.top()->data << " ";
        s2.pop();
    }
}

//写法 2：单栈 + prev 指针（真·单栈，经典教材写法）
//核心思路：栈顶结点能否访问，取决于右子树是否为空或是否刚刚访问过。
void postorderIter2(TreeNode* root)
{
    std::stack<TreeNode*> s;
    TreeNode* p = root;
    TreeNode* prev = nullptr;

    while (p || !s.empty())
    {
        while (p)
        {
            s.push(p);
            p = p->left;
        }

        TreeNode* top = s.top();
        // prev 是关键：它区分了「第一次走到这个根」（该去右边）和「从右边回来了」（该打印并弹栈）。
        if (top->right && top->right != prev) {
            p = top->right; // 右子树还没处理，转过去
        } else {
            std::cout << top->data << " "; // 无右孩子 / 刚从右孩子回来 → 可以访问
            prev = top;
            s.pop();
        }
    }
}

void levelOrder(TreeNode* T)
{
    if (!T) return;
    std::queue<TreeNode*> q;
    q.push(T);
    while (!q.empty())
    {
        TreeNode* cur = q.front();
        q.pop();

        std::cout << cur->data << " ";

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

int depth(TreeNode* T)
{
    if (!T)
        return 0;
    int ldep = depth(T->left);
    int rdep = depth(T->right);
    return ldep > rdep ? (ldep+1) : (rdep+1);

    //return T ? std::max(depth(T->left), depth(T->right)) + 1 : 0;
}

int nodes(TreeNode* T) {
    if (!T)
        return 0;
    return nodes(T->left) + nodes(T->right) + 1;
}

int leaves(TreeNode* T) {
    //return !T ? 0 : (!T->left && !T->right) ? 1 : leaves(T->left)+leaves(T->right);

    if (!T)
        return 0;
    if (!T->left && !T->right)
        return 1;

    return leaves(T->left)+leaves(T->right);
}

void destroy(TreeNode* T) {
    if (!T)
        return;
    destroy(T->left);
    destroy(T->right);
    delete T;
}

int getTreeNodesOfLevelK(TreeNode* T, int k)
{
    if (!T || k < 1) return 0;
    if (k == 1) return 1;

    int left = getTreeNodesOfLevelK(T->left, k-1);
    int right = getTreeNodesOfLevelK(T->right, k-1);

    return (left+right);
}

bool cmpTreeNodeStructure(TreeNode* T1, TreeNode* T2)
{
    if (!T1 && !T2)
        return true;
    else if (!T1 || !T2)
        return false;

    bool left = cmpTreeNodeStructure(T1->left, T2->left);
    bool right = cmpTreeNodeStructure(T1->right, T2->right);

    return (left && right);
}

bool isAVL(const TreeNode* T, int& height)
{
    //TODO:
    return true;
}

// 10. 判断二叉树是不是完全二叉树
// 若设二叉树的深度为h，除了第h层外，其他各层(1~(h-1))的结点都达到
// 最大个数，第h层所有的结点都连续集中在左边，这就是完全二叉树。
// 算法：
// 按层次（从上到下，从左往右）遍历二叉树，当遇到一个结点的左子树为空时，
// 则该结点的右子树必须为空，且后面遍历的结点右子树必须为空，
// 否则不是完全二叉树。
bool isCompleteBinaryTree(TreeNode* T)
{
    if (!T) return false;

    bool notHaveChild = false;
    bool result = true;

    std::queue<TreeNode*> q;
    q.push(T);

    while (!q.empty())
    {
        TreeNode* p = q.front();
        q.pop();

        if (notHaveChild)
        {
            if (p->left != nullptr || p->right != nullptr)
            {
                result = false;
                break;
            }
        }
        else
        {
            if (p->left != nullptr && p->right != nullptr)
            {
                q.push(p->left);
                q.push(p->right);
            }
            else if(p->left != nullptr && p->right == nullptr)
            {
                notHaveChild = true;
                q.push(p->left);
            }
            else if (p->left == nullptr && p->right != nullptr)
            {
                result = false;
                break;
            }
        }
    }

    return result;
}

TreeNode* getNodePtr(TreeNode* T, char c)
{
    if (!T) return nullptr;

    std::queue<TreeNode*> q;
    q.push(T);

    while (!q.empty())
    {
        TreeNode* p = q.front();
        q.pop();

        if (p->data == c)
            return p;
        if (p->left)
            q.push(p->left);
        if (p->right)
            q.push(p->right);
    }

    return nullptr;
}

bool getPath(TreeNode* root, TreeNode* target,
             std::vector<TreeNode*>& path)
{
    if (!root) return false;
    path.push_back(root);
    if (root == target) return true;

    if (getPath(root->left, target, path) ||
        getPath(root->right, target, path))
        return true;

    path.pop_back();
    return false;
}

// 路径法：最稳的通用写法
// 二叉树中两个结点的最低公共祖先结点
TreeNode* lowestCommonAncestorPath(TreeNode* root,
                                   TreeNode* p,
                                   TreeNode* q)
{
    std::vector<TreeNode*> pathP, pathQ;
    if (!getPath(root, p, pathP) || !getPath(root, q, pathQ))
        return nullptr;

    TreeNode* lca = nullptr;
    size_t i = 0;

    while (i < pathP.size() && i < pathQ.size())
    {
        if (pathP[i] == pathQ[i])
            lca = pathP[i];
        else
            break;
        ++i;
    }
    return lca;
}

// 普通二叉树 LCA：递归后序分治版
// 假设 p、q 一定存在于树中 （如果不存在，需要检查）
TreeNode* lowestCommonAncestor(TreeNode* root,
                               TreeNode* p,
                               TreeNode* q)
{
    if (!root) return nullptr;
    if (root == p || root == q) return root;

    TreeNode* left  = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);

    if (left && right) return root; // p,q分居两侧

    return left ? left : right; // 都在同一侧，返回非空那一边
}

int main()
{
    /* 前序建树
     *
            A
           / \
          B   C
         / \   \
        D   E   F
    */

    std::string s = "ABD##E##C#F##";
    int idx = 0;
    TreeNode* root = buildFromStr(s, idx);

    std::cout << "前序(递归): ";    preorder(root);         std::cout << '\n';
    std::cout << "前序(非递归): ";  preorderIter(root);     std::cout << '\n';
    std::cout << "中序: ";          inorder(root);          std::cout << '\n';
    std::cout << "中序(非递归): ";  inorderIter(root);      std::cout << '\n';
    std::cout << "后序: ";          postorder(root);        std::cout << '\n';
    std::cout << "后序(非递归): ";  postorderIter1(root);   std::cout << '\n';
    std::cout << "后序(非递归): ";  postorderIter2(root);   std::cout << '\n';
    std::cout << "层序: ";          levelOrder(root);       std::cout << '\n';
    std::cout << "深度="    << depth(root)
              << " 结点数=" << nodes(root)
              << " 叶子数=" << leaves(root) << '\n';

    // extended functions
    std::cout << "第k层叶子个数：" << getTreeNodesOfLevelK(root, 3); std::cout << "\n";
    std::cout << "是完全二叉树吗：" << (isCompleteBinaryTree(root) ? "yes" : "no") << "\n";

    std::cout << "二叉树的最近公共祖先: \n";
    TreeNode* pD = getNodePtr(root, 'D');
    TreeNode* pE = getNodePtr(root, 'E');
    TreeNode* lca = lowestCommonAncestorPath(root, pD, pE);
    std:: cout << "LCA('D', 'E') = " << lca->data << "\n";


    destroy(root);   // unique_ptr 版这行可删

    return 0;
}

