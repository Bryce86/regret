#include <iostream>
#include <assert.h>

typedef struct DNode {
    int data;
    struct DNode *prev;
    struct DNode *next;
}DNode, *DLinkList;

using namespace std;

DLinkList buildDLink(int n)
{
    // first to build one header
    DLinkList head = new DNode;
    head->data = -1;
    head->prev = head->next = NULL;

    DLinkList temp = head;

    for (int i = 0;i < n; ++i) {
        temp->next = new (DNode);

        temp->next->prev = temp;
        temp = temp->next;
        temp->data = i;
        temp->next = NULL;
    }

    // total allocate n+1 memory block.
    return head;
}

void TraverseDLink(DLinkList dbl)
{
    assert(dbl != NULL);

    DLinkList l = dbl->next;

    while (l != NULL)
    {
        cout << l->data << " ";
        l = l->next;
    }
    cout << endl;
}

int getDNodeLength(DLinkList dbl)
{
    assert(dbl);

    int counter = 0;

    DLinkList temp = dbl->next;

    while (temp)
    {
        temp = temp->next;
        counter++;
    }

    return counter;
}

void insertNode(DLinkList dbl, int pos, int value)
{
    assert(dbl != NULL);

    DLinkList ins = new DNode;
    ins->data = value;

    // only head node
    if (dbl->next == NULL)
    {
        dbl->next = ins;
        ins->prev = dbl;
    }
    else
    {
        int len = getDNodeLength(dbl);
        DLinkList temp = dbl->next;

        if (pos <= len)
        {
            // find the insert position, and insert the head of pos
            int i = 1;
            while (temp->next != NULL && (i < pos)) {
                temp = temp->next;
                ++i;
            }

            if (pos != len)
            {
                temp->prev->next = ins;
                ins->prev = temp->prev;
                ins->next = temp;
                temp->prev = ins;
            }
            else // end node
            {
                temp->next = ins;
                ins->prev = temp;
                ins->next = NULL;
            }
        }
        else
        {
            cout << "position out of range !" << endl;
            return;
        }
    }
}

void deleteNode(DLinkList dbl, int pos, int &x)
{
    assert (dbl != NULL);

    // only one head node
    if (dbl->next == NULL)
        return;
    else
    {
        int len = getDNodeLength(dbl);

        if (pos <= len)
        {
            // find the delete position
            int i = 0;
            while (dbl->next != NULL && (i < pos))
            {
                dbl = dbl->next;
                ++i;
            }

            x = dbl->data;

            if (dbl->next != NULL) // in middle
            {
                dbl->prev->next = dbl->next;
                dbl->next->prev = dbl->prev;

                delete dbl;
            }
            else // end node
            {
                dbl->prev->next = NULL;
                delete dbl;
            }
        }
        else
        {
            cout << "pos not in range !" << endl;
            return;
        }
    }
}

void deleteDLink(DLinkList dbl)
{
    DLinkList temp = NULL;

    while (dbl)
    {
        temp = dbl->next;
        delete dbl;
        dbl = temp;
    }
}

int main()
{
    DLinkList dbl = buildDLink(10);
    cout << getDNodeLength(dbl) << endl;
    TraverseDLink(dbl);

    insertNode(dbl, 5, -3);
    TraverseDLink(dbl);

    insertNode(dbl, getDNodeLength(dbl), 123);
    TraverseDLink(dbl);

    int value = -1;
    deleteNode(dbl, 5, value);
    cout << "delete pos[5] : " << value << endl;
    TraverseDLink(dbl);

    value = -1;
    deleteNode(dbl, getDNodeLength(dbl), value);
    cout << "delete pos[" << getDNodeLength(dbl)+1 << "] : " << value << endl;
    TraverseDLink(dbl);

    deleteDLink(dbl);
    return 0;
}
