#include <iostream>
#include "queue.h"
using namespace std;

/* initialize an Queue */
Status InitQueue(SqQueue *Q)
{
	return OK;
}

/* get length of Queue */
int QueueLength(SqQueue Q)
{
	return 0;
}

/* if cirular Q isn't full, insert an element */
Status EnQueue(SqQueue *Q, QElemType e)
{
	return OK;
}

/* if Q isn't empty, delete head element */
Status DeQueue(SqQueue *Q, QElemType *e)
{
	return OK;
}

int main()
{
	SqQueue Q; 
	InitQueue(&Q);
	EnQueue(&Q, 1);
	EnQueue(&Q, 2);
	EnQueue(&Q, 3);
	EnQueue(&Q, 4);
	cout << QueueLength(Q) << endl;

	QElemType e;	
	DeQueue(&Q, &e);
	cout << e << endl;
	DeQueue(&Q, &e);
	cout << e << endl;
	DeQueue(&Q, &e);
	cout << e << endl;
	DeQueue(&Q, &e);
	cout << e << endl;

	return 0;
}

