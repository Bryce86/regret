// PreInOrderCreateBitree.cpp : 
//
// PreOrder and InOrder to build bitree
// PostOrder and InOrder to build bitree

#include <iostream>
#include <cstring>
using namespace std;

typedef struct BiTNode {
    char data;
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

char pre[] = "ABDHLEKCFG";        //前序序列
char mid[] = "HLDBEKAFCG";        //中序序列
char post[] = "LHDKEBFGCA";       //后序序列

//确定c在中序序列mid中的下标,假设树的各个节点的值各不相同
int Position(char c)
{
    return strchr(mid, c) - mid;
} 


/*  利用前序中序序列创建树
 *  i  : 子树的前序序列字符串的首字符在pre[]中的下标
 *  j  : 子树的中序序列字符串的首字符在mid[]中的下标
 *  len: 子树的字符串序列的长度
 *
 *  参考：http://hi.baidu.com/sulipol/blog/item/f01a20011dcce31a738b6524.html
 */
void PreMidCreateTree(BiTree &T, int i, int j, int len)
{
    if(len <= 0)
	{	
		T = NULL;
        return;
	}
    
	// 前序序列："ABDHLEKCFG";
	// 后序序列："HLDBEKAFCG";

    T = new BiTNode();
    T->data = pre[i];
    int m = Position(pre[i]);
    PreMidCreateTree(T->lchild, i+1, j, m-j);					//m-j为左子树字符串长度
    PreMidCreateTree(T->rchild, i+(m-j)+1, m+1, len-1-(m-j));   //len-1-(m-j)为右子树字符串长度
}


/*  利用后序中序序列创建树
 *  i: 子树的后序序列字符串的尾字符在post[]中的下标
 *  j: 子树的中序序列字符串的首字符在mid[]中的下标
 *  len: 子树的字符串序列的长度
 */
void PostMidCreateTree(BiTree &T, int i, int j, int len)
{
    if(len <= 0)
	{
		T = NULL;
        return;
	}

    T = new BiTNode();
    T->data = post[i];
    int m = Position(post[i]);
    PostMidCreateTree(T->lchild, i-1-(len-1-(m-j)), j, m-j);//注意参数:m-j左子树的长度,len-1-(m-j)右子树的长度
    PostMidCreateTree(T->rchild, i-1, m+1, len-1-(m-j));
}

//后序递归遍历
void PostTravelTree(BiTree T)        
{
    if(T)
    {
        PostTravelTree(T->lchild);    
        PostTravelTree(T->rchild);
        cout<<T->data<<" ";
    }
}

//前序递归遍历
void PreTravelTree(BiTree T)        
{
    if(T)
    {
        cout<<T->data<<" ";
        PreTravelTree(T->lchild);    
        PreTravelTree(T->rchild);
    }
}

int main(int argc, char* argv[])
{ 
    BiTree T1 = NULL, T2= NULL;

	cout << "PreOrder: " << pre << endl;
	cout << "InOrder: " << mid << endl;
	cout << "PostOrder: " << post << endl;

	cout << "PreMidCreateBiTree: ";
    PreMidCreateTree(T1, 0, 0, strlen(mid));
    PostTravelTree(T1); 
	cout<<endl;  

	cout << "PostMidCreateBiTree: ";
    PostMidCreateTree(T2, strlen(post)-1, 0, strlen(mid));
    PreTravelTree(T2); 
	cout<<endl;    

    return 0;
}

