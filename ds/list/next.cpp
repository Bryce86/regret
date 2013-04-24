#include <iostream>
using namespace std;

typedef struct LNode {
	int data;
	struct LNode *next;
}LNode, *LinkList;

LinkList buildList()
{
	LinkList head = new LNode;
	LinkList curr = head;

	for (int i = 0; i < 5; i++)
	{
		curr->next = new LNode;	
		curr = curr->next;
		curr->data = i;
		curr->next = NULL;
	}

	return head;
}

int main(void)
{
	cout << "DATA : 0 1 2 3 4" << endl << endl;
	LinkList head = buildList();	
	LinkList list = head->next;
	LinkList p1 = list;
	LinkList p2 = list;

	cout << "list != NULL :" << endl;
	while (p1 != NULL)
	{
		cout << p1->data << " ";
		cout << p1 << " --> ";
		p1 = p1->next;
		cout << p1 << " " << endl;
	}

	cout << endl;
	cout << "list->next != NULL :" << endl;
	while (p2->next != NULL)
	{
		cout << p2->data << " ";
		cout << p2 << " --> ";
		p2 = p2->next;
		cout << p2 << " " << endl;
	}

	return 0;
}

