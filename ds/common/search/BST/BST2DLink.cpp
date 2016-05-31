/*
Convert BST to DBLinkList

题目：输入一颗二叉搜索树，将该二叉搜索树转换成一个排序的
      双向链表。要求不能创建任何新节点，只能调整数中节点指针的指向。
      比如：

        10
       /  \
      6    14        => 4<->6<->8<->10<->12<->14<->16
    /  \  /   \
   4   8  12  16

分析：
1. 二叉树中，每个结点都有两个指向子结点的指针。
2. 在双向链表中，每个结点也有两个指针，分别指向前一个结点和后一个结点。
3. 二叉搜索树中，左子结点的值总是小于父结点的值，右子结点的值总是大于父结点的值。
4. 将二叉搜索树转换为双向链表时，原先指向左子结点的指针调整为链表中指向前一个结点的指针，
   原先指向右子结点的指针调整为链表中指向后一个结点的指针。
5. 由于要求转换之后的链表是排好序的，所以我们采取中序遍历。
6. 当遍历转换到根结点时，左子树已经转换成了一个排序的链表了，
   并且处在链表中的最后一个结点是当前值最大的结点，将其与根结点连接起来，
   接着去遍历转换右子树，并把根结点和右子树中的最小的结点连接起来
*/

#include <iostream>

using namespace std;

typedef struct BSTNode {
    int data;
    BSTNode *lchild;
    BSTNode *rchild;
}BSTNode, *BSTree;

int array[] = {4, 6, 8, 10, 12, 14, 16};

void insertBSTNode(BSTree &T, int x)
{
    if (T == NULL)
    {
        T = new BSTNode;
        T->data = x;
        T->lchild = T->rchild = NULL;
        return;
    }

    if (T->data == x)
        return;

    if (x < T->data)
        return insertBSTNode(T->lchild, x);
    else
        return insertBSTNode(T->rchild, x);
}

void buildBSTree(BSTree &T)
{
    for (unsigned int i = 0; i < sizeof(array)/sizeof(array[0]); ++i)
    {
        insertBSTNode(T, array[i]);
    }
}

void InOrderTraverseBiTree(BSTree T)
{
    if (T)
    {
        InOrderTraverseBiTree(T->lchild);
        cout << T->data << " ";
        InOrderTraverseBiTree(T->rchild);
    }
}

void Convert(BSTree T, BSTree &dbl)
{
    if (!T)
        return;

    BSTree curr = T;

    if (curr->lchild != NULL)
        Convert(curr->lchild, dbl);

    curr->lchild = dbl;

    if (dbl)
        dbl->rchild = curr;

    dbl = curr;

    if (curr->rchild != NULL)
        Convert(curr->rchild, dbl);
}

BSTree ConvertBST2DBLink(BSTree T)
{
    BSTree dbl = NULL;
    Convert(T, dbl);

    // get the head node
    while (dbl->lchild != NULL)
    {
        dbl = dbl->lchild;
    }

    return dbl;
}

void TraverseDBLink(BSTree dbl)
{
    while (dbl)
    {
        cout << dbl->data << " ";
        dbl = dbl->rchild;
    }
    cout << endl;
}

int main()
{
    BSTree T = NULL;
    buildBSTree(T);
    InOrderTraverseBiTree(T);
    cout << endl;

    BSTree dbl = ConvertBST2DBLink(T);
    TraverseDBLink(dbl);

    return 0;
}
