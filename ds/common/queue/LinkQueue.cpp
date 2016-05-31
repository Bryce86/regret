#include <iostream>
#include "queue.h"
#include <stdlib.h>
using namespace std;

Status initQueue(LinkQueue *Q)
{
	Q->front = (QueuePtr)malloc(sizeof(QNode));
	Q->front->data = -1;
	Q->front->next = NULL;
	Q->rear = Q->front;

	return 0;
}

/* insert elemnt at rear */
Status EnQueue(LinkQueue *Q, QElemType e)
{
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
	if (!s)
		exit(OVERFLOW);

	s->data = e;
	s->next = NULL;
	Q->rear->next = s;
	Q->rear = s;

	return OK;
}

/* if Q isn't empty, delete head element */
Status DeQueue(LinkQueue *Q, QElemType *e)
{
	QueuePtr p;	
	if (Q->front == Q->rear)
		return ERROR;

	p = Q->front->next;
	*e = p->data;

	Q->front->next = p->next;

	if (Q->rear == p)
		Q->rear = Q->front;

	free(p);

	return OK;
}

/* get length of Queue */
int QueueLength(LinkQueue Q)
{
	int count = 0;
	QueuePtr p = Q.front;
	while (p->next != NULL)
	{
		count++;	
		p = p->next;
	}

	return count;
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
