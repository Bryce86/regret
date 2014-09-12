// PreMidCreateBiTree.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstring>
using namespace std;

char pre[50] = "ABDHLEKCFG";        //前序序列
char mid[50] = "HLDBEKAFCG";        //中序序列
char post[50] = "LHDKEBFGCA";        //后序序列

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}BiTNode, *BiTree;

void PostTravelTree(BiTree pn);        //树的后序递归遍历
void PreTravelTree(BiTree pn);        //树的前序递归遍历
void PreMidCreateTree(BiTree &pn, int i, int j, int len);        //利用前序中序序列创建树
void PostMidCreateTree(BiTree &pn, int i, int j, int len);        //利用后序中序序列创建树
int Position(char c);                //确定c在中序序列mid中的下标,假设树的各个节点的值各不相同

int main(int argc, char* argv[])
{ 
    BiTree root1 = NULL, root2= NULL;

    PreMidCreateTree(root1, 0, 0, strlen(mid));
    PostTravelTree(root1); 
	cout<<endl;  

    PostMidCreateTree(root2, strlen(post)-1, 0, strlen(mid));
    PreTravelTree(root2); 
	cout<<endl;    

    return 0;
}


int Position(char c)
{
    return strchr(mid, c) - mid;
} 


/*  利用前序中序序列创建树,参考了http://hi.baidu.com/sulipol/blog/item/f01a20011dcce31a738b6524.html
 *的实现,代码十分简洁,竟然只有短短的"令人发指"的8行,递归实在太彪悍了!!!!!!!!!!!!!!!!!!!!!
 *        i: 子树的前序序列字符串的首字符在pre[]中的下标
 *        j: 子树的中序序列字符串的首字符在mid[]中的下标
 *      len: 子树的字符串序列的长度
 */
void PreMidCreateTree(BiTree &T, int i, int j, int len)
{
    if(len <= 0)
	{	
		T = NULL;
        return;
	}
    
/*
char pre[50] = "ABDHLEKCFG";        //前序序列
char mid[50] = "HLDBEKAFCG";        //中序序列
*/

    T = new BiTNode();
    T->data = pre[i];
    int m = Position(pre[i]);
    PreMidCreateTree(T->lchild, i+1, j, m-j);            //m-j为左子树字符串长度
    PreMidCreateTree(T->rchild, i+(m-j)+1, m+1, len-1-(m-j));    //len-1-(m-j)为右子树字符串长度
}


/*  利用后序中序序列创建树
 *        i: 子树的后序序列字符串的尾字符在post[]中的下标
 *        j: 子树的中序序列字符串的首字符在mid[]中的下标
 *      len: 子树的字符串序列的长度
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


void PostTravelTree(BiTree T)        //后序递归遍历
{
    if(T)
    {
        PostTravelTree(T->lchild);    
        PostTravelTree(T->rchild);
        cout<<T->data<<" ";
    }
}


void PreTravelTree(BiTree T)        //前序递归遍历
{
    if(T)
    {
        cout<<T->data<<" ";
        PreTravelTree(T->lchild);    
        PreTravelTree(T->rchild);
    }
}
