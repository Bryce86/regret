#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_

typedef char TElemType;

typdef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

void CreateBiTree(BiTree &T);
void PreOrderTraverse(BiTree T /* (* visit)(TElemType e) */);
void InOrderTraverse(BiTree T);
void PostOrderTraverse(BiTree T);
void LevelOrderTraverse(BiTree T);

#endif /* _BINARY_TREE_H_ */
