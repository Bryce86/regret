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

}

/* recursion traverse */
void PreOrderTraverse(BiTree T /* (* visit)(TElemType e) */)
{
}


void InOrderTraverse(BiTree T)
{

}

void PostOrderTraverse(BiTree T)
{

}

/* levelorder traverse */
void LevelOrderTraverse(BiTree T)
{
	// use queue

}

/* unrecursion traverse */
void PreOrderTraverseUnrec(BiTree T)
{
	// use stack
}

void InOrderTraverseUnrec(BiTree T)
{
	// use stack
}

void PostOrderTraverseUnrec(BiTree T)
{
	// use stack
}

/* transform lchild and rchild */
BiTree TransformLRChild(BiTree &T)
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
	
	return T;
}

/* depth */
int GetBiTreeDepth(BiTree T)
{
	return 0;
}

/* leaves */
int GetBiTreeLeaves(BiTree T)
{
	return 0;
}

/* nodes */
int GetBiTreeNodes(BiTree T)
{
	return 0;
}

/* nodes of level k */
int GetBiTreeNodesOfLevelK(BiTree T, int k)
{
	return 0;
}

/* compare BiTree structure, not care data */
bool CmpBiTreeStructure(BiTree &T1, BiTree &T2)
{
	return 0;
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

	cout << "GetBiTreeNodesOfLevelK: ";
	nodes = GetBiTreeNodesOfLevelK(T, 4);
	cout << nodes << endl;

	cout << "CmpBiTreeStructure: ";
	BiTree T2 = T;
	bool same = CmpBiTreeStructure(T, T2);
	cout << same << endl;

	return 0;
}


