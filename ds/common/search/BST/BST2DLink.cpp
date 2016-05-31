/*
Convert BST to DBLinkList

��Ŀ������һ�Ŷ��������������ö���������ת����һ�������
      ˫������Ҫ���ܴ����κ��½ڵ㣬ֻ�ܵ������нڵ�ָ���ָ��
      ���磺

        10
       /  \
      6    14        => 4<->6<->8<->10<->12<->14<->16
    /  \  /   \
   4   8  12  16

������
1. �������У�ÿ����㶼������ָ���ӽ���ָ�롣
2. ��˫�������У�ÿ�����Ҳ������ָ�룬�ֱ�ָ��ǰһ�����ͺ�һ����㡣
3. �����������У����ӽ���ֵ����С�ڸ�����ֵ�����ӽ���ֵ���Ǵ��ڸ�����ֵ��
4. ������������ת��Ϊ˫������ʱ��ԭ��ָ�����ӽ���ָ�����Ϊ������ָ��ǰһ������ָ�룬
   ԭ��ָ�����ӽ���ָ�����Ϊ������ָ���һ������ָ�롣
5. ����Ҫ��ת��֮����������ź���ģ��������ǲ�ȡ���������
6. ������ת���������ʱ���������Ѿ�ת������һ������������ˣ�
   ���Ҵ��������е����һ������ǵ�ǰֵ���Ľ�㣬��������������������
   ����ȥ����ת�������������Ѹ������������е���С�Ľ����������
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
