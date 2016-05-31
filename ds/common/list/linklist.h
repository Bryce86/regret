#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#define LINE_LIST_NODES 10
#define RANDOM_VALUE 100

typedef int ElemType;

typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

#endif  /* __LINKLIST_H__ */

