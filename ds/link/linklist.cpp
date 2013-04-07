#include <iostream>
using namespace std;

/* 求单链表中结点的个数 */
/* 这是最最基本的了，应该能够迅速写出正确的代码，注意检查链表是否为空。时间复杂度为O（n）。*/
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

/* 将单链表反转 */
/* 从头到尾遍历原链表，每遍历一个结点，将其摘下放在新链表的最前端。注意链表为空和只有一个结点的情况。时间复杂度为O（n）。*/
LinkList & ReverseLinkList(LinkList &l)
{
	// 如果链表为空或只有一个结点，无需反转，直接返回原链表头指针		
	if (l == NULL || l->next == NULL) 
		return l;

	LinkList p = l;
	LinkList q = NULL; // 反转后的新链表头指针，初始为NULL

	while (p)
	{
		LinkList temp = p;	
		p = p->next;
		temp->next = q; // 将当前结点摘下，插入新链表的最前端
		q = temp;
	}
	
	return q;
}

/* 查找单链表中的倒数第K个结点（k > 0） */
/* 最普遍的方法是，先统计单链表中结点的个数，然后再找到第（n-k）个结点。注意链表为空，k为0，k为1，k大于链表中节点个数时的情况。
   时间复杂度为O（n）。
   这里主要讲一下另一个思路，这种思路在其他题目中也会有应用。主要思路就是使用两个指针，先让前面的指针走到正向第k个结点，
   这样前后两个指针的距离差是k-1，之后前后两个指针一起向前走，前面的指针走到最后一个结点时，
   后面指针所指结点就是倒数第k个结点。
*/
LinkList & ReverseGetKthNode(LinkList &l, int k)
{
	if (k = 0 || l == NULL) // 这里k的计数是从1开始的，若k为0或链表为空返回NULL
		return NULL;

	Linklist first = l;
	LinkList second = l;

	while (k > 1 && first != NULL) // 前面的指针先走到正向第k个结点      
	{
		first = first->next;			
		k--;
	}

	if (k > 1 || first == NULL)  // 结点个数小于k，返回NULL   
		return NULL;

	while (first->next != NULL) // 前后两个指针一起向前走，直到前面的指针指向最后一个结点    
	{
		first = first->next;	
		second = second->next;
	}

	return second;  // 后面的指针所指结点就是倒数第k个结点  
}

/* 查找单链表的中间结点 */
/* 此题可应用于上一题类似的思想。也是设置两个指针，只不过这里是，两个指针同时向前走，前面的指针每次走两步，
   后面的指针每次走一步，前面的指针走到最后一个结点时，后面的指针所指结点就是中间结点，即第（n/2+1）个结点。
   注意链表为空，链表结点个数为1和2的情况。时间复杂度O（n）。
*/
LinkList & GetMiddleNode(LinkList &l)
{
	if (l == NULL || l->next == NULL) // 链表为空或只有一个结点，返回头指针
		return l;

	LinkList first = l;
	LinkList second = l;

	while (first->next != NULL) // 前面指针每次走两步，直到指向最后一个结点，后面指针每次走一步
	{
		first = first->next;			
		if (first->next != NULL)
			first = first->next;

		second = second->next;
	}
	return second; // 后面的指针所指结点即为中间结点  
}

/* 从尾到头打印单链表 */
/* 对于这种颠倒顺序的问题，我们应该就会想到栈，后进先出。所以，这一题要么自己使用栈，要么让系统使用栈，
   也就是递归。注意链表为空的情况。时间复杂度为O（n）。
*/
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

/* 已知两个单链表pHead1 和pHead2 各自有序，把它们合并成一个链表依然有序 */
/* 这个类似归并排序。尤其注意两个链表都为空，和其中一个为空时的情况。只需要O（1）的空间。
   时间复杂度为O（max(len1, len2)）。
*/
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

/* 判断一个单链表中是否有环 */
/* 这里也是用到两个指针。如果一个链表中有环，也就是说用一个指针去遍历，是永远走不到头的。
   因此，我们可以用两个指针去遍历，一个指针一次走两步，一个指针一次走一步，如果有环，两个指针肯定会在环中相遇。
   时间复杂度为O（n）。
*/
bool LinkListHasCircle(LinkList &l)
{
	LinkList fast = l; // 快指针每次前进2步
	LinkList slow = l; // 慢指针每次前几1步

	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;	
		slow = slow->next;

		if (fast == slow) // 相遇，存在环
			return true;
	}

	return false;
}

/* 判断两个单链表是否相交 */
/* 如果两个链表相交于某一节点，那么在这个相交节点之后的所有节点都是两个链表所共有的。
   也就是说，如果两个链表相交，那么最后一个节点肯定是共有的。
   先遍历第一个链表，记住最后一个节点，然后遍历第二个链表，到最后一个节点时和第一个链表的最后一个节点做比较，
   如果相同，则相交，否则不相交。时间复杂度为O(len1+len2)，因为只需要一个额外指针保存最后一个节点地址，空间复杂度为O(1)。
*/
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

/* 求两个单链表相交的第一个节点 */
/* 对第一个链表遍历，计算长度len1，同时保存最后一个节点的地址。
   对第二个链表遍历，计算长度len2，同时检查最后一个节点是否和第一个链表的最后一个节点相同，若不相同，不相交，结束。
    两个链表均从头节点开始，假设len1大于len2，那么将第一个链表先遍历len1-len2个节点，
    此时两个链表当前节点到第一个相交节点的距离就相等了，然后一起向后遍历，知道两个节点的地址相同。
    时间复杂度，O(len1+len2)。
*/
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

	if (pTail1 != pTail2) // 不相交直接返回NULL
		return NULL;

	LinkList pNode1 = p1;
	LinkList pNode2 = p2;
	// 先对齐两个链表的当前结点，使之到尾节点的距离相等
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

/* 已知一个单链表中存在环，求进入环中的第一个节点 */
/* 首先判断是否存在环，若不存在结束。在环中的一个节点处断开（当然函数结束时不能破坏原链表），
   这样就形成了两个相交的单链表，求进入环中的第一个节点也就转换成了求两个单链表相交的第一个节点。
*/ 
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
		
	// 将环中的此节点作为假设的尾节点，将它变成两个单链表相交问题
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

	// 先对齐两个链表的当前结点，使之到尾节点的距离相等
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

/* 给出一单链表头指针pHead和一节点指针pToBeDeleted，O(1)时间复杂度删除节点pToBeDeleted */
/* 对于删除节点，我们普通的思路就是让该节点的前一个节点指向该节点的下一个节点，这种情况需要遍历找到该节点的前一个节点，
   时间复杂度为O(n)。对于链表，链表中的每个节点结构都是一样的，所以我们可以把该节点的下一个节点的数据复制到该节点，
   然后删除下一个节点即可。要注意最后一个节点的情况，这个时候只能用常见的方法来操作，
   先找到前一个节点，但总体的平均时间复杂度还是O(1)。
*/
void deleteOneNode(LinkList &l, LinkList &pToBeDeleted)
{
	if (pToBeDeleted == NULL)
		return;

	if (pToBeDeleted->next != NULL)
	{
		pToBeDeleted->data = pToBeDeleted->next->data; // 将下一个节点的数据复制到本节点，然后删除下一个节点
		LinkList temp = pToBeDeleted->next;
		pToBeDeleted->next = pToBeDeleted->next->next;
		delete temp;
	}
	else // 要删除的是最后一个节点  
	{
		if (l == pToBeDeleted)	// 链表中只有一个节点的情况  
		{
			l = NULL;	
			delete pToBeDeleted;
		}
		else
		{
			LinkList pNode = l;		
			while (pNode->next != pToBeDeleted) // 找到倒数第二个节点
				pNode = pNode->next;
			pNode->next = NULL;
			delete pToBeDeleted;
		}
	}
}










