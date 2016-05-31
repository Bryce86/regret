#ifndef _QUEUE_H_
#define _QUEUE_H_

#define MAXSIZE 10
#define OK 0
#define ERROR 1
#define OVERFLOW -1

typedef int Status;
typedef int QElemType;

typedef struct
{
	QElemType data[MAXSIZE];
	int front;
	int rear;
}SqQueue;

typedef struct QNode
{
	QElemType data;
	struct QNode *next;
}QNode, *QueuePtr;

typedef struct
{
	QueuePtr front, rear;
}LinkQueue;

#endif // _QUEUE_H_
