#include <iostream>
#include <cstdlib>
#include <queue>
#include <list>

using std::cout;
using std::endl;
using std::cin;

#define BITREE_OVERFLOW -1

typedef char TElemType;

typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/*
 * 题目列表：
 * 1. 二叉树的建立
 *		1.1 前序建立二叉树
 *		1.2 由前序遍历序列和中序遍历序列重建二叉树
 *		1.3 由后序遍历序列和中序遍历序列重建二叉树
 * 2. 遍历二叉树
 *		2.1 递归：前序遍历、中序遍历、后序遍历
 *		2.2 非递归：前序遍历、中序遍历、后序遍历
 *		2.3 分层次遍历二叉树（按层次从上往下，从左往右）
 *		2.4 Morris：前序遍历、中序遍历、后序遍历
 * 3. 求二叉树的镜像
 * 4. 求二叉树的深度
 * 5. 求二叉树中的叶子结点的个数
 * 6. 求二叉树中的结点个数
 * 7. 求二叉树第K层的结点个数
 * 8. 判断两棵二叉树是否结构相同
 * 9. 判断二叉树是不是平衡二叉树（AVL）
 * 10. 判断二叉树是不是完全二叉树
 * 11. 求二叉树中两个结点的最低公共祖先结点
 * 12. 求二叉树中结点的最大距离
 * 13. 将二叉查找树（BST）变为有序的双向链表
 */

// 1.1 前序建立二叉树
void CreateBiTree(BiTree &T)
{
	/* PreOrder: A B C # # D E # G # # F # # #
	 
		    A
		   / 
		  B  
		 / \
	    C   D
		   / \
		  E   F
		   \
		    G
	 */

	char ch;	

	cin >> ch;

	if (ch == '#')
		T = NULL;
	else
	{
		if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))	
			exit (BITREE_OVERFLOW);

		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

// 1.2 由前序遍历序列和中序遍历序列重建二叉树
// 1.3 由后序遍历序列和中序遍历序列重建二叉树
// see PreInOrderCreateBitree.cpp

// 2.1 前序遍历二叉树 （递归）
void PreOrderTraverse(BiTree T /* (* visit)(TElemType e) */)
{
	if (T)	
	{
		cout << T->data;

		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

// 2.1 中序遍历二叉树 （递归）
void InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);

		cout << T->data;

		InOrderTraverse(T->rchild);
	}
}

// 2.1 后续遍历二叉树 （递归）
void PostOrderTraverse(BiTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);

		PostOrderTraverse(T->rchild);

		cout << T->data;
	}
}

// 2.2 非递归：前序遍历二叉树
void PreOrderTraverseUnrec(BiTree T)
{
	// use stack
	const int N = 50;
	int top = 0;
	BiTree stack[N], p;

	p = T;
	while (p || top > 0)
	{
		while (p)
		{
			cout << p->data;	
			stack[top++] = p;
			p = p->lchild;
		}

		if (top > 0)
		{
			p = stack[--top];
			p = p->rchild;
		}
	} // while
}

// 2.2 非递归：中序遍历二叉树
void InOrderTraverseUnrec(BiTree T)
{
	// use stack
	const int N = 50;
	int top = 0;
	BiTree stack[N], p;

	p = T;
	while (p || top > 0)
	{
		while (p)	
		{
			stack[top++] = p;	
			p = p->lchild;
		}

		if (top > 0)
		{
			p = stack[--top];
			cout << p->data;	
			p = p->rchild;
		}
	} // while
}

// 2.2 非递归：后序遍历二叉树
void PostOrderTraverseUnrec(BiTree T)
{
	// use stack
	const int N = 50;
	int top = 0;
	BiTree stack[N], p;

	p = T;
	while (p || top > 0)
	{
		while (p)	
		{
			stack[top++] = p;		
			if (p->lchild)
				p = p->lchild;
			else
				p = p->rchild;
		}

		if (top > 0)
		{
			p = stack[--top];
			cout << p->data;

			// when return from right child, stack[top-1]->rchild = p
			if (top > 0 && stack[top-1]->rchild != p)
				p = stack[top-1]->rchild;
			else
				p = NULL;
		}
	} // while
}

// 2.3 层次遍历二叉树
// 相当于广度优先搜索，使用队列实现。
// 队列初始化，将根节点压入队列。当队列不为空
// 进行如下操作：弹出一个结点，访问，
// 若其左子结点或右子结点不为空，将其压入队列。
void LevelOrderTraverse(BiTree T)
{
	if (!T)
		return;

	// use std::queue
	std::queue<BiTree> q;
	q.push(T);

	while (!q.empty())
	{
		BiTree p = q.front();		
		q.pop();

		cout << p->data;

		if (p->lchild)
			q.push(p->lchild);
		if (p->rchild)
			q.push(p->rchild);
	} // while
}

// 2.4 Morris：前序遍历二叉树
// 2.4 Morris：中序遍历二叉树
void InOrderTraverse_Morris(const BiTree T)
{
    BiTree p, temp;

    p = T;
    while (p)
    {
        if (p->lchild == NULL) {
            cout << p->data;
            p = p->rchild;
        }
        else
        {
            temp = p->lchild; 

            // find the last rchild of the current lchild
            while (temp->rchild != NULL && temp->rchild != p)
            {
                temp = temp->rchild; 
            }

            if (temp->rchild == NULL)
            {
                temp->rchild = p; 
                p = p->lchild;
            }
            else
            {
                cout << p->data; 
                temp->rchild = NULL;
                p = p->rchild;
            }
        }
    
    } // while
}

// 2.4 Morris：后序遍历二叉树

// 3. 求二叉树的镜像
// 递归：
// （1）如果二叉树为空，返回空
// （2）如果二叉树不为空，求左子树和右子树的镜像，
//		然后交换左子树和右子树
BiTree MirrorBiTree(BiTree &T)
{
	/* PreOrder: 
	 
		    A
		     \
		      B
		     / \
	        D   C
		   / \
		  F   E
		     /
		    G
	 */	
	
	if (!T)
		return NULL;

	BiTree left = MirrorBiTree(T->lchild);
	BiTree right = MirrorBiTree(T->rchild);

	T->lchild = right;
	T->rchild = left;

	return T;
}

// 4. 求二叉树的深度
// 递归：
// （1）如果二叉树为空，二叉树深度为0
// （2）如果二叉树不为空，二叉树深度=max（左子树深度，右子树深度）+ 1
int GetBiTreeDepth(const BiTree T)
{
	if (!T)
		return 0;

	int depthLeft = GetBiTreeDepth(T->lchild); 
	int depthRight = GetBiTreeDepth(T->rchild);
	return depthLeft > depthRight ? (depthLeft + 1) : (depthRight + 1); 
}

// 5. 求二叉树中的叶子结点的个数
// 递归：
// （1）如果二叉树为空，返回0
// （2）如果二叉树不为空，且左右子树为空，返回1
// （3）如果二叉树不为空，且左右子树不同时为空，
//		返回左子树中叶子结点个数 + 右子树叶子结点个数。
int GetBiTreeLeaves(const BiTree T)
{
	if (!T)
		return 0;
	if (!T->lchild && !T->rchild)
		return 1;

	int leafLeft = GetBiTreeLeaves(T->lchild);
	int leafRight = GetBiTreeLeaves(T->rchild);

	return (leafLeft + leafRight);
}

// 6. 求二叉树中的结点个数
// 递归：
// （1）如果二叉数为空，结点个数为0
// （2）如果二叉树不为空，二叉树结点个数=左结点个数+右结点个数+1
int GetBiTreeNodes(const BiTree T)
{
	if (!T)
		return 0;

	return GetBiTreeNodes(T->lchild) + GetBiTreeNodes(T->rchild) + 1; 
}

// 7. 求二叉树第K层的结点个数
// 递归：
// （1）如果二叉树为空，或者k<1，返回0
// （2）如果二叉树不为空，并且k==1，返回1
// （3）如果二叉树部位空，并且k>1，返回左子树中k-1层的结点个数
//		与右子树k-1层结点个数之和。
int GetBiTreeNodesOfLevelK(const BiTree T, int k)
{
	if (!T || k < 1)
		return 0;

	if (k == 1)
		return 1;

	int left = GetBiTreeNodesOfLevelK(T->lchild, k-1);
	int right = GetBiTreeNodesOfLevelK(T->rchild, k-1);

	return (left + right);
}

// 8. 判断两棵二叉树是否结构相同
// 不考虑数据内容，结构相同意味着对应的左子树和对应的右子树都结构相同。
// 递归：
// （1）如果两棵二叉树都为空，返回true
// （2）如果两棵二叉树一颗为空，另一颗不为空，返回false
// （3）如果两棵二叉树都不为空，如果对应的左子树和右子树都同构返回true，
//		其他返回false。
bool CmpBiTreeStructure(const BiTree T1, const BiTree T2)
{
	if (!T1 && !T2)
		return true;
	else if (!T1 || !T2)
		return false;

	bool left = CmpBiTreeStructure(T1->lchild, T2->lchild);
	bool right = CmpBiTreeStructure(T1->rchild, T2->rchild);

	return (left && right);
}

int _max(int a, int b) { return a > b ? a : b; }

// 9. 判断二叉树是不是平衡二叉树（AVL）
// 递归：
// （1）如果二叉树为空，返回true
// （2）如果二叉树不为空，如果左子树和右子树都是AVL树，
//		并且左子树和右子树高度相差不大于1，返回true，其他返回false
bool isAVL(const BiTree T, int &height)
{
	if (!T) {
		height = 0;	
		return true;
	}

	int leftHeight;
	bool leftResult = isAVL(T->lchild, leftHeight);

	int rightHeight;
	bool rightResult = isAVL(T->rchild, rightHeight);

	if (leftResult && rightResult && (abs(leftHeight - rightHeight) <= 1))
	{
		// 左子树和右子树都是AVL，并且高度相差不大于1，返回真
		height = _max (leftHeight, rightHeight) + 1;
		return true;
	}
	else
	{
		height = _max (leftHeight, rightHeight) + 1;
		return false;
	}
}

// 10. 判断二叉树是不是完全二叉树
// 若设二叉树的深度为h，除了第h层外，其他各层(1~(h-1))的结点都达到
// 最大个数，第h层所有的结点都连续集中在左边，这就是完全二叉树。
// 算法：
// 按层次（从上到下，从左往右）遍历二叉树，当遇到一个结点的左子树为空时，
// 则该结点的右子树必须为空，且后面遍历的结点右子树必须为空，
// 否则不是完全二叉树。
bool isCompleteBiTree(const BiTree T)
{
	if (!T)
		return false;

	bool mustHaveNoChild = false;
	bool result = true;

	std::queue<BiTree> q;	
	q.push(T);

	while (!q.empty())
	{
		BiTree p = q.front();
		q.pop();	

		// 已经出现了又空子树的结点了，后面出现的必须为叶子结点
		if (mustHaveNoChild)
		{
			if (p->lchild != NULL || p->rchild != NULL)	
			{
				result = false;	
				break;
			}
		}
		else
		{
			if (p->lchild  != NULL && p->rchild != NULL)	
			{
				q.push(p->lchild);	
				q.push(p->rchild);
			}
			else if (p->lchild != NULL && p->rchild == NULL)
			{
				mustHaveNoChild = true;
				q.push(p->lchild);	
			}
			else if (p->lchild == NULL && p->rchild != NULL)
			{
				result = false;
				break;
			}
		}
	}

	return result;
}

// 11. 求二叉树中两个结点的最低公共祖先结点
// 递归：
// （1）如果两个结点分别在根节点的左子树和右子树，则返回根节点
// （2）如果两个结点都在左子树，则递归处理左子树；
//		如果两个结点都在右子树，则递归处理右子树。
bool FindNode(const BiTree T, const BiTree pNode)
{
	if (T == NULL || pNode == NULL)
		return false;
	if (T == pNode)
		return true;

	bool found = FindNode(T->lchild, pNode);
	if (!found)
		found = FindNode(T->rchild, pNode);

	return found;
}

BiTree GetLastCommonParent(const BiTree T, const BiTree pNode1, const BiTree pNode2)
{
	if (FindNode(T->lchild, pNode1))
	{
		if (FindNode(T->rchild, pNode2))	
			return T;
		else
			return GetLastCommonParent(T->lchild, pNode1, pNode2);
	}
	else
	{
		if (FindNode(T->lchild, pNode2))
			return T;
		else
			return GetLastCommonParent(T->rchild, pNode1, pNode2);
	}
}

// 递归效率很低，有很多重复的遍历
// 非递归：
// 先求从根节点到两个结点的路径，然后再比较路径的结点就行，
// 最后一个相同的结点也就是他们在二叉树中的最低公共祖先结点
bool GetNodePath(const BiTree T, const BiTree pNode, std::list<BiTree> &path)
{
	if (T == pNode)	
	{
		path.push_back(T);			
		return true;
	}

	if (T == NULL)
		return false;
	path.push_back(T);

	bool found = GetNodePath(T->lchild, pNode, path);
	if (!found)
		found = GetNodePath(T->rchild, pNode, path);
	if (!found)
		path.pop_back(); // remove the last NULL node;

	return found;
}

BiTree GetLastCommonParentUnrec(const BiTree T, const BiTree pNode1, const BiTree pNode2)
{
	if (T == NULL || pNode1 == NULL || pNode2 == NULL)
		return NULL;

	std::list<BiTree> path1;
	bool bRet1 = GetNodePath(T, pNode1, path1);	

	std::list<BiTree> path2;
	bool bRet2 = GetNodePath(T, pNode2, path2);

	if (!bRet1 || !bRet2)
		return NULL;

	BiTree found = NULL;
	std::list<BiTree>::const_iterator it1 = path1.begin();
	std::list<BiTree>::const_iterator it2 = path2.begin();

	while (it1 != path1.end() && it2 != path2.end())
	{
		if (*it1 == *it2)	
			found = *it1;
		else
			break;

		it1++;
		it2++;
	}
	
	return found;
}

// 12. 求二叉树中结点的最大距离
// 即二叉树中相距最远的两个结点之间的距离
// 递归：
// （1）如果二叉树为空，返回0，同时记录左子树和右子树的深度，都为0
// （2）如果二叉树不为空，最大距离要么是左子树中的最大距离，
//		要么是右子树中的最大距离，
//		要么是左子树结点中到根节点的最大距离 + 右子树结点中到根节点的最大距离，
//		同时记录左子树和右子树结点中到根节点的最大距离。
int GetMaxDistance(const BiTree T, int &maxLeft, int &maxRight)
{
	// maxLeft, 左子树的结点距离根节点的最大距离
	// maxRight, 右子树的结点距离根节点的最大距离
	if (T == NULL)
	{
		maxLeft = 0;
		maxRight = 0;
		return 0;	
	}

	int maxLL, maxLR, maxRL, maxRR;
	int maxDistLeft, maxDistRight;

	if (T->lchild != NULL)
	{
		maxDistLeft = GetMaxDistance(T->lchild, maxLL, maxLR);	
		maxLeft = _max(maxLL, maxLR) + 1;
	}
	else
	{
		maxDistLeft = 0;	
		maxLeft = 0;
	}

	if (T->rchild != NULL)
	{
		maxDistRight = GetMaxDistance(T->rchild, maxRL, maxRR);	
		maxRight = _max(maxRL, maxRR) + 1;
	}
	else
	{
		maxDistRight = 0;	
		maxRight = 0;
	}

	return _max(_max(maxDistLeft, maxDistRight), maxLeft+maxRight);
}

// 13. 将二叉查找树（BST）变为有序的双向链表

// 获取某个结点
BiTree GetNode(const BiTree T, char c)
{
	if (!T)
		return NULL;
	
	std::queue<BiTree> q;	
	q.push(T);
	
	while (!q.empty())
	{
		BiTree p = q.front();	
		q.pop();

		if (p->data == c)
			return p;

		if (p->lchild)
			q.push(p->lchild);
		if (p->rchild)
			q.push(p->rchild);
	}

	return NULL;
}

int main(void)
{
	BiTree T;

	cout << "1.1 INPUT(PRE): ABC##DE#G##F###" << endl;
	CreateBiTree(T);

	cout << "2.1 PreOrderTraverse: ";
	PreOrderTraverse(T);
	cout << endl;

	cout << "2.1 InOrderTraverse: ";
	InOrderTraverse(T);
	cout << endl;

	cout << "2.1 PostOrderTraverse: ";
	PostOrderTraverse(T);
	cout << endl;

	cout << "2.2 PreOrderTraverseUnrec: ";
	PreOrderTraverseUnrec(T);
	cout << endl;

	cout << "2.2 InOrderTraverseUnrec: ";
	InOrderTraverseUnrec(T);
	cout << endl;

	cout << "2.2 PostOrderTraverseUnrec: ";
	PostOrderTraverseUnrec(T);
	cout << endl;

	cout << "2.3 LevelOrderTraverse: ";
	LevelOrderTraverse(T);
	cout << endl;

	cout << "2.4 Morris: InOrderTraverse_Morris: "; 
	InOrderTraverse_Morris(T);
	cout << endl;
	
	cout << "3. MirrorBiTree(PreOT): ";
	MirrorBiTree(T);
	PreOrderTraverse(T);
	cout << endl;

	cout << "4. GetBiTreeDepth: ";
	int depth = GetBiTreeDepth(T);
	cout << depth << endl;

	cout << "5. GetBiTreeLeaves: ";
	int leaves = GetBiTreeLeaves(T);
	cout << leaves << endl;

	cout << "6. GetBiTreeNodes: ";
	int nodes = GetBiTreeNodes(T);
	cout << nodes << endl;

	cout << "7. GetBiTreeNodesOfLevelK: ";
	nodes = GetBiTreeNodesOfLevelK(T, 4);
	cout << nodes << endl;

	cout << "8. CmpBiTreeStructure: ";
	BiTree T2 = T;
	bool same = CmpBiTreeStructure(T, T2);
	cout << same << endl;

	cout << "9. isAVL: ";
	int height = -1;
	bool bIsAVL = isAVL(T, height);
	cout << bIsAVL << ", height: " << height << endl;

	/*
		 A
	    / \
	   B   C
	  / \  /
	 D   E F
	*/
	cout << "build CompleteBiTree(PRE): ABD##E##CF###" << endl;
	BiTree cb;
	CreateBiTree(cb);
	cout << "10. isCompleteBiTree: ";
   	bool isCB = isCompleteBiTree(cb);
	cout << isCB << endl;

	BiTree pNode1 = GetNode(cb, 'D');
	BiTree pNode2 = GetNode(cb, 'F');
	cout << "11. GetLastCommonParent " << pNode1->data << " and " << pNode2->data << " : ";
	// Can't get B and D, will core dump
	BiTree pParent = GetLastCommonParent(cb, pNode1, pNode2);
	cout << pParent->data << endl;

	BiTree pNode3 = GetNode(cb, 'B');
	BiTree pNode4 = GetNode(cb, 'D');
	cout << "12. GetLastCommonParentUnrec " << pNode3->data << " and " << pNode4->data << " : ";
	BiTree pParent1 = GetLastCommonParentUnrec(cb, pNode3, pNode4);
	cout << pParent1->data << endl;

	cout << "13. GetMaxDistance: ";
	int maxLeft = 0, maxRight = 0;
	int maxDist = GetMaxDistance(cb, maxLeft, maxRight);
	cout << "maxDist=" << maxDist << ", maxLeft=" << maxLeft << ",maxRight=" << maxRight << endl;

	return 0;
}


