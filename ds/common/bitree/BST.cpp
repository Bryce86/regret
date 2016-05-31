#include <iostream>
using namespace std;

typedef struct BiTNode {
	int data;
	BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/* 递归查找二叉排序树T中是否存在key，
 * 指针f指向T的双亲，其初始化调用值为NULL，
 * 若查找成功，则指针p指向该数据元素结点，并返回TRUE；
 * 否则指针p指向查找路径上访问的最后一个结点并返回FALSE。
 */
bool SearchBST(BiTree &T, int key, BiTree f, BiTree &p)
{
	if (!T)
	{
		p = f;	
		return false;
	}
	else if (key == T->data)
	{
		p = T;	
		return true;
	}
	else if (key < T->data)
		return SearchBST(T->lchild, key, T, p);
	else
		return SearchBST(T->rchild, key, T, p);
}

/* 当二叉排序树T中不存在关键字等于key的数据元素时，
 * 插入key并返回TRUE，否者返回FALSE。
 */
bool InsertBST(BiTree &T, int key)
{
	BiTree p, s;

	if (!SearchBST(T, key, NULL, p))
	{
		s = new BiTNode;
		s->data = key;
		s->lchild = s->rchild = NULL;

		if (!p) // 插入s为新的跟结点
		{
			T = s;	
		}
		else if (key < p->data)
			p->lchild = s; // 插入s为左孩子
		else
			p->rchild = s; // 插入s为右孩子

		return true;
	}
	else
		return false; // 树中已有关键字相同的结点，不再插入
}

void InsertBSTNode(BiTree &T, int key)
{
	if (!T)
	{
		T = new BiTNode;	
		T->data = key;
		T->lchild = T->rchild = NULL;
		return;
	}

	if (T->data == key)
		return;

	if (key < T->data)
		return InsertBSTNode(T->lchild, key);
	else
		return InsertBSTNode(T->rchild, key);
}

/* 从二叉排序树中删除结点p，并重接它的左或右子树 */
bool Delete(BiTree &T)
{
	BiTree q,s;
	if (T->rchild == NULL) // 右子树空则只需要重接它的左子树
	{
		q = T; 
		T = T->lchild;
		delete q;
	}
	else if (T->lchild == NULL) // 只需重接它的右子树
	{
		q = T;	
		T = T->rchild;
		delete q;
	}
	else // 左右子树均不为空
	{
		q = T;	
		s = T->lchild;

		while (s->rchild) // 转左，然后向右到尽头(找待删结点的前驱)
		{
			q = s;
			s = s->rchild;	
		}

		T->data = s->data; // s指向被删结点的直接前驱
		if (q != T)
			q->rchild = s->lchild; // 重接q的右子树
		else
			q->lchild = s->lchild; // 重接q的左子树

		delete s;
	}

	return true;
}

/* 若二叉排序树T中存在关键字等于key的数据元素时，
 * 则删除该数据元素结点，并返回TRUE；否则返回FALSE。
 */
bool DeleteBST(BiTree &T, int key)
{
	if (!T)
		return false;
	else
	{
		if (key == T->data)	
			return Delete(T);
		else if (key < T->data)
			DeleteBST(T->lchild, key);
		else
			DeleteBST(T->rchild, key);
	}
}

void InOrderTraverseBiTree(BiTree T)
{
    if (T)
    {
        InOrderTraverseBiTree(T->lchild);
        cout << T->data << " ";
        InOrderTraverseBiTree(T->rchild);
    }
}

int main()
{
	int arr[] = {62, 88, 58, 47, 35, 73, 51, 99, 37, 93};
	BiTree T = NULL;
	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i)
			InsertBST(T, arr[i]);
			//InsertBSTNode(T, arr[i]);

	InOrderTraverseBiTree(T); cout << endl;

	DeleteBST(T, 51);
	InOrderTraverseBiTree(T); cout << endl;
	return 0;
}
