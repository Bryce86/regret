#ifndef _LINKLIST_H_
#define _LINKLIST_H_ 

typedef struct LNode {
	ElemType data;
	struct LNode *next;
}LNode, *LinkList;

#endif /* _LINKLIST_H_ */
