#include <iostream>
#include "binarytree.h"

using std::cout;
using std::endl;
using std::cin;

/* preorder traverse to building bitree */
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
			exit (OVERFLOW);

		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
}

/* recursion traverse */
void PreOrderTraverse(BiTree T /* (* visit)(TElemType e) */)
{
	if (T)	
	{
		cout << T->data;

		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

void InOrderTraverse(BiTree T)
{
	if (T)
	{
		InOrderTraverse(T->lchild);

		cout << T->data;

		InOrderTraverse(T->rchild);
	}
}

void PostOrderTraverse(BiTree T)
{
	if (T)
	{
		PostOrderTraverse(T->lchild);

		PostOrderTraverse(T->rchild);

		cout << T->data;
	}
}

/* levelorder traverse */
void LevelOrderTraverse(BiTree T)
{
	// use queue
	const int N = 100;	
	int front = 0, rear = 0;
	BiTree SqQueue[N], p;

	if (!T)
		return;

	SqQueue[rear] = T;
	rear = (rear + 1) % N; // rear++

	while (rear != front)
	{
		p = SqQueue[front];	
		front = (front + 1) % N;

		cout << p->data;

		if (p->lchild)
		{
			SqQueue[rear] = p->lchild;
			rear = (rear + 1) % N;
		}

		if (p->rchild)
		{
			SqQueue[rear] = p->rchild;	
			rear = (rear + 1) % N;
		}
	} // while
}

/* unrecursion traverse */
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

/* transform lchild and rchild */
BiTree TransformLRChild(BiTree &T)
{
	if (!T)
		return NULL;

	BiTree left = TransformLRChild(T->lchild);
	BiTree right = TransformLRChild(T->rchild);

	T->lchild = right;
	T->rchild = left;

	return T;
}

/* depth */
int GetBiTreeDepth(BiTree T)
{
	if (!T)
		return 0;

	int depthLeft = GetBiTreeDepth(T->lchild); 
	int depthRight = GetBiTreeDepth(T->rchild);
	return depthLeft > depthRight ? (depthLeft + 1) : (depthRight + 1); // has a root
}

/* leaves */
int GetBiTreeLeaves(BiTree T)
{
	if (!T)
		return 0;
	if (!T->lchild && !T->rchild)
		return 1;

	int leafLeft = GetBiTreeLeaves(T->lchild);
	int leafRight = GetBiTreeLeaves(T->rchild);

	return (leafLeft + leafRight);
}

/* nodes */
int GetBiTreeNodes(BiTree T)
{
	if (!T)
		return 0;
	return GetBiTreeNodes(T->lchild) + GetBiTreeNodes(T->rchild) + 1; // has a root
}

int main(void)
{
	BiTree T;

	cout << "INPUT: ABC##DE#G##F###" << endl;
	CreateBiTree(T);

	cout << "PreOrderTraverse: ";
	PreOrderTraverse(T);
	cout << endl;

	cout << "InOrderTraverse: ";
	InOrderTraverse(T);
	cout << endl;

	cout << "PostOrderTraverse: ";
	PostOrderTraverse(T);
	cout << endl;

	cout << "LevelOrderTraverse: ";
	LevelOrderTraverse(T);
	cout << endl;

	cout << "PreOrderTraverseUnrec: ";
	PreOrderTraverseUnrec(T);
	cout << endl;

	cout << "InOrderTraverseUnrec: ";
	InOrderTraverseUnrec(T);
	cout << endl;

	cout << "PostOrderTraverseUnrec: ";
	PostOrderTraverseUnrec(T);
	cout << endl;
	
	cout << "TransformLRChild(PreOT): ";
	TransformLRChild(T);
	PreOrderTraverse(T);
	cout << endl;

	cout << "GetBiTreeDepth: ";
	int depth = GetBiTreeDepth(T);
	cout << depth << endl;

	cout << "GetBiTreeLeaves: ";
	int leaves = GetBiTreeLeaves(T);
	cout << leaves << endl;

	cout << "GetBiTreeNodes: ";
	int nodes = GetBiTreeNodes(T);
	cout << nodes << endl;

	return 0;
}


