#include <iostream>
#include "queue.h"
using namespace std;

/* initialize an Queue */
Status InitQueue(SqQueue *Q)
{
	Q->front = 0;
	Q->rear = 0;

	return OK;
}

/* get length of Queue */
int QueueLength(SqQueue Q)
{
	return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;
}

/* if cirular Q isn't full, insert an element */
Status EnQueue(SqQueue *Q, QElemType e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)
		return ERROR;

	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;

	return OK;
}

/* if Q isn't empty, delete head element */
Status DeQueue(SqQueue *Q, QElemType *e)
{
	if (Q->front == Q->rear)
		return ERROR;
	
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;

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

