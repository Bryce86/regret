#include <iostream>
#include <cstdlib>
using namespace std;

typedef char ElemType;
typedef enum {Link=0, Thread} PointerTag;

typedef struct BiThrNode {
	ElemType data;	
	struct BiThrNode *lchild, *rchild;
	PointerTag LTag, RTag;
} BiThrNode, *BiThrTree;

// 先序创建二叉树
// NOTICE: 注意该处使用的是引用，省去二级指针的繁琐。C语言另当别论
void createBiTree(BiThrTree &T) { 
	// PreOrder: abdh##i##ej###cf##g## 
	char ch;
	cin >> ch;

	if (ch == '#')
		T = NULL;
	else {
		if (!(T = new(BiThrNode)))
			exit(-1);

		T->data = ch;
		T->LTag = Link;  //初始化时指针标志均为Link
		T->RTag = Link;

		createBiTree(T->lchild);
		createBiTree(T->rchild);
	}

}

BiThrTree pre; //全局变量，始终指向刚刚访问过的结点

void InThreading(BiThrTree &T) {
	if (T) 
	{
		InThreading(T->lchild);	

		if (!T->lchild) {
			T->LTag = Thread;	
			T->lchild = pre;
		}

		if (!pre->rchild) {
			pre->RTag = Thread;
			pre->rchild = T;
		}

		pre = T;
		InThreading(T->rchild);
	} 
}

//中序线索化二叉树

/*
	和双向链表结构一样，在二叉树线索链表上添加一个头结点，并令其lchild域的指针
	指向二叉树的根结点，其rchild域的指针指向中序遍历时访问的最后一个结点的rchild。
	
	反之，令二叉树的中序序列中的第一个结点中，lchild域指针和最后一个结点的rchild域指针均
	指向头结点。这样定义的好处就是，既可以从第一个结点起顺后继进行遍历，也可以从最后一个
	结点起顺前驱进行遍历。

*/
BiThrTree InOrderThrTree(BiThrTree T) 
{
	BiThrTree Thre; //Thre为头结点的指针
	Thre = new(BiThrNode);
	Thre->lchild = T;
	Thre->rchild = Thre; // temp this
	pre = Thre;

	InThreading(T);

	// 线索化后pre指向刚刚访问过的最后一个结点
	// 然后将其与与头指针相关联
	pre->RTag = Thread;
	pre->rchild = Thre;
	
	Thre->rchild = pre; // and this

	return Thre;
} 

//中序遍历二叉树
void InOrderTraverse_Thr(BiThrTree &T)
{
	BiThrTree p;
	p = T->lchild;

	while (p != T) { //指针回指向头结点时结束
		while (p->LTag == Link)	
			p = p->lchild; // 找到左子树最左结点

		cout << p->data << " ";

		while (p->RTag == Thread && p->rchild != T) {
			p = p->rchild;	
			cout << p->data;
		}

		p = p->rchild;
	}
}

int main()
{
	cout << "input(pre) : abdh##i##ej###cf##g## " << endl;
	BiThrTree T;
	createBiTree(T);

	// 中序线索化 二叉树
	BiThrTree Thre = InOrderThrTree(T);
	
	// 中序遍历 线索二叉树
	cout << "InOrderTraverse_Thr: ";
	InOrderTraverse_Thr(Thre);
	cout << endl;

	return 0;
}


















