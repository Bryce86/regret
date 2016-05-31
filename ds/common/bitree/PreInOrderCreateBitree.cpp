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

char pre[] = "ABDHLEKCFG";        //ǰ������
char mid[] = "HLDBEKAFCG";        //��������
char post[] = "LHDKEBFGCA";       //��������

//ȷ��c����������mid�е��±�,�������ĸ����ڵ��ֵ������ͬ
int Position(char c)
{
    return strchr(mid, c) - mid;
} 


/*  ����ǰ���������д�����
 *  i  : ������ǰ�������ַ��������ַ���pre[]�е��±�
 *  j  : ���������������ַ��������ַ���mid[]�е��±�
 *  len: �������ַ������еĳ���
 *
 *  �ο���http://hi.baidu.com/sulipol/blog/item/f01a20011dcce31a738b6524.html
 */
void PreMidCreateTree(BiTree &T, int i, int j, int len)
{
    if(len <= 0)
	{	
		T = NULL;
        return;
	}
    
	// ǰ�����У�"ABDHLEKCFG";
	// �������У�"HLDBEKAFCG";

    T = new BiTNode();
    T->data = pre[i];
    int m = Position(pre[i]);
    PreMidCreateTree(T->lchild, i+1, j, m-j);					//m-jΪ�������ַ�������
    PreMidCreateTree(T->rchild, i+(m-j)+1, m+1, len-1-(m-j));   //len-1-(m-j)Ϊ�������ַ�������
}


/*  ���ú����������д�����
 *  i: �����ĺ��������ַ�����β�ַ���post[]�е��±�
 *  j: ���������������ַ��������ַ���mid[]�е��±�
 *  len: �������ַ������еĳ���
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
    PostMidCreateTree(T->lchild, i-1-(len-1-(m-j)), j, m-j);//ע�����:m-j�������ĳ���,len-1-(m-j)�������ĳ���
    PostMidCreateTree(T->rchild, i-1, m+1, len-1-(m-j));
}

//����ݹ����
void PostTravelTree(BiTree T)        
{
    if(T)
    {
        PostTravelTree(T->lchild);    
        PostTravelTree(T->rchild);
        cout<<T->data<<" ";
    }
}

//ǰ��ݹ����
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

