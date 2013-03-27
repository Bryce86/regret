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
void PreOrdeerTraverseUnrec(BiTree T);
void InOrderTraverseUnrec(BiTree T);
void PostOrderTraverseUnrec(BiTree T);

/* Thread bitree traverse */
/*
void PreOrderTraverseThread(BiTree T);
void InOrderTraverseThread(BiTree T);
void PostOrderTraverseThread(BiTree T);
*/

/* transfer lchild and rchild */

/* Depth */

/* leaf */

#endif /* _BINARY_TREE_H_ */
