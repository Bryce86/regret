#include <iostream>
using namespace std;

/* get linklist node num */
int GetLinkListNodes(LinkList &l)
{
	if (l == NULL)	
		return 0;

	int count = 0;
	LinkList p = l;

	while (p->next != NULL)
	{
		p = p->next;	
		count++
	}

	return count;
}

/* reverse linklist */
LinkList & ReverseLinkList(LinkList &l)
{
	// if list is null or only one node, return list		
	if (l == NULL || l->next == NULL) 
		return l;

	LinkList p = l;
	LinkList q = NULL;

	while (p)
	{
		LinkList temp = p;	
		p = p->next;
		temp->next = q; //remove current node, insert into the front of new list (q)
		q = temp;
	}
	
	return q;
}

/* search the the k'th node that count from the end in list */
LinkList & ReverseGetKthNode(LinkList &l, int k)
{
	if (k = 0 || l == NULL)
		return NULL;

	Linklist first = l;
	LinkList second = l;

	while (k > 1 && first != NULL)
	{
		first = first->next;			
		k--;
	}

	if (k > 1 || first == NULL)
		return NULL;

	while (first->next != NULL)
	{
		first = first->next;	
		second = second->next;
	}

	return second;
}

/* search the middle node in list */
LinkList & GetMiddleNode(LinkList &l)
{
	if (l == NULL || l->next == NULL)
		return l;

	LinkList first = l;
	LinkList second = l;

	while (first->next != NULL)
	{
		first = first->next;			
		if (first->next != NULL)
			first = first->next;

		second = second->next;
	}
	return second;
}

/* print nodes from end to front */
void ReversePrintLinkList(LinkList &l) //stack
{
	LinkList stack[50];
	int top = 0;

	LinkList p = l;
	while (p != NULL)
	{
		stack[top++] = p;		
		p = p->next;
	}

	while (top > 0)
	{
		p = stack[--top];	
		cout << p->data;
	}
}

void ReversePrintLinkList(LinkList &l) //recursion
{
	if (l == NULL)
		return;
	else
	{
		ReversePrintLinkList(l->next);	
		cout << l->data;
	}
}

/* two list l1, l2, both sorted, merge them, and keep sorted */
LinkList & MergeSortedLinkList(LinkList &p1, LinkList &p2)
{
	if (p1 == NULL)
		return p2;
	if (p2 == NULL)
		return p1;

	// get list header?
	LinkList pMerge = NULL;
	if (p1->data < p2->data)
	{
		pMerge = p1;	
		pMerge->next = NULL;
		p1 = p1->next;
	}
	else
	{
		pMerge = p2;	
		pMerge->next = NULL;
		p2 = p2->next;
	}

	LinkList temp = pMerge;	
	while (p1 != NULL && p2 != NULL)
	{
		if (p1->data < p2->data)	
		{
			temp->next = p1;			
			p1 = p1->next;
			temp = temp->next;
			temp->next = NULL;
		}
		else
		{
			temp->next = p2;	
			p2 = p2->next;
			temp = temp->next;
			temp->next = NULL;
		}
	}

	if (p1 != NULL)
		temp->next = p1;
	if (p2 != NULL)
		temp->next = p2;

	return pMerge;
}

LinkList & MergeSortedLinkList(LinkList &p1, LinkList &p2) // recursion
{
	if (p1 == NULL)	
		return p2;
	if (p2 == NULL)
		return p1;

	LinkList pMerge = NULL;
	if (p1->data < p2->data)
	{
		pMerge = p1;	
		pMerge->next = MergeSortedLinkList(p1->next, p2);
	}
	else
	{
		pMerge = p2;	
		pMerge->next = MergeSortedLinkList(p1, p2->next);
	}

	return pMerge;
}

/* judeg linklist has circle */
bool LinkListHasCircle(LinkList &l)
{
	LinkList fast = l;
	LinkList slow = l;

	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;	
		slow = slow->next;

		if (fast == slow)
			return true;
	}

	return false;
}

/* judge linklist whether be intersection */
bool LinkListIsInterSection(LinkList &p1, LinkList &p2)
{
	if (p1 == NULL || p2 == NULL)
		return false;

	LinkList pTail1 = p1;
	while (pTail1->next != NULL)	
		pTail1 = pTail1->next;

	LinkList pTail2 = p2;
	while (pTail2->next != NULL)
		pTail2 = pTail2->next;
	
	return (pTail1 == pTail2);
}

/* the first intersection node of two lists */
LinkList & GetFirstInterSectionNode(LinkList &p1, LinkList &p2)
{
	if (p1 == NULL || p2 == NULL)
		return NULL;

	int len1 = 1;
	LinkList pTail1 = p1;
	while (pTail1->next != NULL)
	{
		pTail1 = pTail1->next;	
		len1++;
	}

	int len2 = 1;
	LinkList pTail2 = p2;
	while (pTail2->next != NULL)
	{
		pTail2 = pTail2->next;	
		len2++;
	}

	if (pTail1 != pTail2)
		return NULL;

	LinkList pNode1 = p1;
	LinkList pNode2 = p2;

	if (len1 > len2)
	{
		int k = len1 - len2;	
		while (k--)
			pNode1 = pNode1->next;
	}
	else
	{
		int k = len2 - len1;	
		while (k--)
			pNode2 = pNode2->next;
	}

	while (pNode1 != pNode2)
	{
		pNode1 = pNode1->next;	
		pNode2 = pNode2->next;
	}

	return pNode1;
}

/* there is a linklist that has a circle, get the first node into the circle */
LinkList & GetFirstNodeIntoCircle(LinkList &l)
{
	if (l == NULL || l->next == NULL)
		return NULL;

	LinkList fast = l;
	LinkList slow = l;
	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
			break;
	}

	if (fast == NULL || fast->next == NULL)
		return NULL;

	LinkList pAssumedTail = slow;
	LinkList p1 = l;
	LinkList p2 = pAssumedTail->next;

	LinkList pNode1 = p1;
	ine len1 = 1;
	while (pNode1 != pAssumedTail)
	{
		pNode1 = pNode1->next;	
		len1++;
	}

	LinkList pNode2 = p2;
	int len2 = 1;
	while (pNode2 != pAssumedTail)
	{
		pNode2 = pNode2->next;	
		len2++;
	}

	pNode1 = p1;
	pNode2 = p2;

	if (len1 > len2)
	{
		int k = len1 - len2;	
		while (k--)
			pNode1 = pNode1->next;
	}
	else
	{
		int k = len2 - len1;	
		while (k--)
			pNode2 = pNode2->next;
	}

	while (pNode1 != pNode2)
	{
		pNode1 = pNode1->next;	
		pNode2 = pNode2->next;
	}

	return pNode1;
}

/* delete one node, need O(1) */
void deleteOneNode(LinkList &l, LinkList &pToBeDeleted)
{
	if (pToBeDeleted == NULL)
		return;

	if (pToBeDeleted->next != NULL)
	{
		pToBeDeleted->data = pToBeDeleted->next->data;
		LinkList temp = pToBeDeleted->next;
		pToBeDeleted->next = pToBeDeleted->next->next;
		delete temp;
	}
	else
	{
		if (l == pToBeDeleted)	
		{
			l = NULL;	
			delete pToBeDeleted;
		}
		else
		{
			LinkList pNode = l;		
			while (pNode->next != pToBeDeleted)
				pNode = pNode->next;
			pNode->next = NULL;
			delete pToBeDeleted;
		}
	}
}










