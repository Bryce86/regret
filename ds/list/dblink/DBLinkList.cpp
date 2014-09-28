#include <iostream>
#include <cstdlib>
#include <memory.h>
#include <time.h>
#include <unistd.h>
using namespace std;

#define ELEMENT_NUM 10

typedef struct DBLNode {
	int data;
	struct DBLNode *prev;
	struct DBLNode *next;
}DBLNode, *DBLinkList;

typedef struct DLink {
	DBLinkList head;	
	DBLinkList tail;
}DLink;

//create double linklist
DBLinkList buildDBLinkList(int n) {
	srand((unsigned int)time(NULL));

	DBLinkList head = new(DBLNode);
	memset(head, 0x0, sizeof(DBLNode));
	head->data = -1;
	DBLinkList temp = head;
	
	for (int i = 0; i < n; i++)
	{
		temp->next = new(DBLNode);	
		temp->next->prev = temp;	
		temp = temp->next;
		temp->data = rand() % 100;
		temp->next = NULL;
	}
	// if we need circle link:
/*
	head->prev = temp; // temp is tail just now
	temp->next = head; 
*/
	return head;
}

void TraverseDBLinkList(DBLinkList dbl) {

	// except head node
	dbl = dbl->next;

	if (dbl)	
	{
		while (dbl != NULL)		
		{
			cout << dbl->data << " ";	
			dbl = dbl->next;
		}

		cout << endl;
	}
}

void InsertNode(DBLinkList dbl, int x, int pos) {
	if (dbl) 
	{
		DBLinkList ins = new(DBLNode);
		ins->data = x;

		// only head node
		if (dbl->next == NULL)	
		{
			dbl->next = ins;	
			ins->prev = dbl;
		} else { //
			if (pos < ELEMENT_NUM) {
				dbl = dbl->next; // fisrt node

				for (int i = 0; i < pos; i++)	
				{
					dbl = dbl->next;		
				}
				dbl->prev->next = ins;	
				ins->prev = dbl->prev;
				ins->next = dbl;
				dbl->prev = ins;

			} else {
				cout << "out of range !" << endl;	
			}
		}
	}	
}

void deleteDBLinkList(DBLinkList dbl) {
	DBLinkList temp = dbl;

	while (dbl)	
	{
		temp = dbl->next;	
		delete dbl;
		dbl = temp;
	}
}

int main(void)
{
	DBLinkList dbl = buildDBLinkList(ELEMENT_NUM);

	//traverse
	TraverseDBLinkList(dbl);

	//insert
	InsertNode(dbl, -3, 5);
	TraverseDBLinkList(dbl);

	//delete
	deleteDBLinkList(dbl);

	return 0;
}


