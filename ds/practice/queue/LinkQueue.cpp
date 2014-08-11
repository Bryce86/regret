#include <iostream>
#include "queue.h"
#include <stdlib.h>
using namespace std;

Status initQueue(LinkQueue *Q)
{
	return 0;
}

/* insert elemnt at rear */
Status EnQueue(LinkQueue *Q, QElemType e)
{
	return OK;
}

/* if Q isn't empty, delete head element */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	return OK;
}

/* get length of Queue */
int QueueLength(LinkQueue Q)
{
	return 0;
}

int main()
{
	LinkQueue Q;
	initQueue(&Q);

	EnQueue(&Q, 1);
	EnQueue(&Q, 2);
	EnQueue(&Q, 3);
	EnQueue(&Q, 4);
	EnQueue(&Q, 5);
	int length = QueueLength(Q);

	cout << "length: " << length << endl;

	QElemType e;
	for (int i = 0; i < length; i++)
	{
		DeQueue(&Q, &e);
		cout << e << endl;
	}

	return 0;
}
