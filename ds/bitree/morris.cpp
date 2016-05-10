#include <iostream>
using namespace std;

typedef char ElemType;

typedef struct BiTNode {
    ElemType data;    
    struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

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

void createBiTree(BiTree &T)
{
    char c;
    cin >> c;

    if (c == '#')
        T = NULL;
    else
    {
        T = new BiTNode();  
        if (!T)
        {
            cout << "new failed." << endl;
            return;
        }

        T->data = c;
        createBiTree(T->lchild);
        createBiTree(T->rchild);
    }
}

void PreOrderTraverse(const BiTree T)
{
    if (T)
    {
        cout << T->data;    

        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}

void InOrderTraverse_Morris(const BiTree T)
{
    BiTree p, temp;

    p = T;
    while (p)
    {
        if (p->lchild == NULL) {
            cout << p->data;
            p = p->rchild;
        }
        else
        {
            temp = p->lchild; 

            // find the last rchild of the current lchild
            while (temp->rchild != NULL && temp->rchild != p)
            {
                temp = temp->rchild; 
            }

            if (temp->rchild == NULL)
            {
                temp->rchild = p; 
                p = p->lchild;
            }
            else
            {
                cout << p->data; 
                temp->rchild = NULL;
                p = p->rchild;
            }
        }
    
    } // while
}

int main()
{
    BiTree T;
    cout << "PreOrder: A B C # # D E G # # F # # #" << endl;
    createBiTree(T);

    PreOrderTraverse(T);
    cout << endl;

    InOrderTraverse_Morris(T);
    cout << endl;

    return 0;
}
