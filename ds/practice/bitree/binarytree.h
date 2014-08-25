#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

#define OVERFLOW -1

typedef char TElemType;

typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

/* preorder traverse to building bitree */
void CreateBiTree(BiTree &T);

/* recursion traverse */
void PreOrderTraverse(BiTree T /* (* visit)(TElemType e) */);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);

/* levelorder traverse */
void LevelOrderTraverse(BiTree T);

/* unrecursion traverse */
void PreOrderTraverseUnrec(BiTree T);
void InOrderTraverseUnrec(BiTree T);
void PostOrderTraverseUnrec(BiTree T);

/* Thread bitree traverse */
/*
void PreOrderTraverseThread(BiTree T);
void InOrderTraverseThread(BiTree T);
void PostOrderTraverseThread(BiTree T);
*/

/* transform lchild and rchild */
BiTree TransformLRChild(BiTree &T);

/* depth */
int GetBiTreeDepth(BiTree T);

/* leaves */
int GetBiTreeLeaves(BiTree T);

/* nodes */
int GetBiTreeNodes(BiTree T);

/* nodes of level k */
int GetBiTreeNodesOfLevelK(BiTree T, int k);

/* compare BiTree structure, not care data */
bool CmpBiTreeStructure(BiTree &T1, BiTree &T2);

#endif /* _BINARY_TREE_H_ */
