// PreMidCreateBiTree.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <cstring>
using namespace std;

char pre[50] = "ABDHLEKCFG";        //ǰ������
char mid[50] = "HLDBEKAFCG";        //��������
char post[50] = "LHDKEBFGCA";        //��������

typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}BiTNode, *BiTree;

void PostTravelTree(BiTree pn);        //���ĺ���ݹ����
void PreTravelTree(BiTree pn);        //����ǰ��ݹ����
void PreMidCreateTree(BiTree &pn, int i, int j, int len);        //����ǰ���������д�����
void PostMidCreateTree(BiTree &pn, int i, int j, int len);        //���ú����������д�����
int Position(char c);                //ȷ��c����������mid�е��±�,�������ĸ����ڵ��ֵ������ͬ

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


/*  ����ǰ���������д�����,�ο���http://hi.baidu.com/sulipol/blog/item/f01a20011dcce31a738b6524.html
 *��ʵ��,����ʮ�ּ��,��Ȼֻ�ж̶̵�"���˷�ָ"��8��,�ݹ�ʵ��̫�뺷��!!!!!!!!!!!!!!!!!!!!!
 *        i: ������ǰ�������ַ��������ַ���pre[]�е��±�
 *        j: ���������������ַ��������ַ���mid[]�е��±�
 *      len: �������ַ������еĳ���
 */
void PreMidCreateTree(BiTree &T, int i, int j, int len)
{
    if(len <= 0)
	{	
		T = NULL;
        return;
	}
    
/*
char pre[50] = "ABDHLEKCFG";        //ǰ������
char mid[50] = "HLDBEKAFCG";        //��������
*/

    T = new BiTNode();
    T->data = pre[i];
    int m = Position(pre[i]);
    PreMidCreateTree(T->lchild, i+1, j, m-j);            //m-jΪ�������ַ�������
    PreMidCreateTree(T->rchild, i+(m-j)+1, m+1, len-1-(m-j));    //len-1-(m-j)Ϊ�������ַ�������
}


/*  ���ú����������д�����
 *        i: �����ĺ��������ַ�����β�ַ���post[]�е��±�
 *        j: ���������������ַ��������ַ���mid[]�е��±�
 *      len: �������ַ������еĳ���
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


void PostTravelTree(BiTree T)        //����ݹ����
{
    if(T)
    {
        PostTravelTree(T->lchild);    
        PostTravelTree(T->rchild);
        cout<<T->data<<" ";
    }
}


void PreTravelTree(BiTree T)        //ǰ��ݹ����
{
    if(T)
    {
        cout<<T->data<<" ";
        PreTravelTree(T->lchild);    
        PreTravelTree(T->rchild);
    }
}
