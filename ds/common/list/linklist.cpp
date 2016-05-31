#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "linklist.h"

using namespace std;

/* 创建线性链表 */
LinkList buildLineList()
{
	srand((unsigned int)time(NULL));
	
	/* 头结点 */
	LinkList head = (LinkList)malloc(sizeof(LNode));
	LinkList curr = head;

	for (int i = 0; i < LINE_LIST_NODES; i++)
	{
		curr->next = (LinkList)malloc(sizeof(LNode));
		curr = curr->next;
		curr->data = rand() % RANDOM_VALUE;
		curr->next = NULL;
	}

	return head;
}

/* 创建有序线性链表 */
LinkList buildSortedLineList(int a[], int n)
{
	LinkList head = (LinkList)malloc(sizeof(LNode));	
	LinkList curr = head;

	for (int i = 0; i < n; i++)
	{
		curr->next = (LinkList)malloc(sizeof(LNode));
		curr = curr->next;
		curr->data = a[i];
		curr->next = NULL;
	}
	return head;
}

/* 创建带有环的单链表 */
LinkList buildHasCircleList(int a[], int n)
{
	LinkList head = (LinkList)malloc(sizeof(LNode));
	LinkList curr = head;
	LinkList intersect = NULL;

	for (int i = 0; i < n; i++)
	{
		curr->next = (LinkList)malloc(sizeof(LNode));	
		curr = curr->next;
		curr->data = a[i];

		if (i == n/2)
			intersect = curr;
		curr->next = NULL;
	}
	curr->next = intersect;

	return head;
}

/* 创建2个相交的单链表 */
void buildTwoIntersectList(LNode **L1, LNode **L2, int nodes)
{
	*L1 = (LinkList)malloc(sizeof(LNode));		
	*L2 = (LinkList)malloc(sizeof(LNode));

	LinkList curr1 = *L1;
	LinkList curr2 = *L2;
	LinkList intersect = NULL;

	for (int i = 0; i < nodes; i++)
	{
		curr1->next = (LinkList)malloc(sizeof(LNode));
		curr1 = curr1->next;
		curr1->data = i+1;
		curr1->next = NULL;
		if (i == nodes/2)
			intersect = curr1;
	}

	for (int i = 0; i < nodes/2; i++)
	{
		curr2->next = (LinkList)malloc(sizeof(LNode));	
		curr2 = curr2->next;
		curr2->data = (i+1)*(-1);
		curr2->next = NULL;
	}
	curr2->next = intersect;
}

/* 遍历线性链表 */
void TraverseLineList(LinkList &l)
{
	// l为第一节点，非头结点
	LinkList p = l;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

/* 获取单链表中值为k的结点 */
LinkList GetOneNodeFromList(LinkList &l, int k)
{
	// l为第一节点，非头结点	
	if (l == NULL)	
		return NULL;

	LinkList pNode = l;
	while (pNode != NULL)
	{
		if (pNode->data == k)	
			return pNode;
		pNode = pNode->next;
	}

	return NULL;
}

/* 1. 求单链表中结点的个数 */
/* 这是最最基本的了，应该能够迅速写出正确的代码，注意检查链表是否为空。时间复杂度为O（n）。*/
int GetListNodes(LinkList &l)
{
	if (l == NULL)
		return 0;
	// 因为不是头结点，不然需要判断
	/*
	if (l->next == NULL)
		return 0;
	*/

	LinkList p = l;
	int count = 0;
	
	while (p != NULL)
	{
		p = p->next;
		count++;
	}
		
	return count;
}


/* 2. 将单链表反转 */
/* 从头到尾遍历原链表，每遍历一个结点，将其摘下放在新链表的最前端。注意链表为空和只有一个结点的情况。时间复杂度为O（n）。*/
LinkList ReverseList(LinkList &l)
{
	// 如果链表为空或只有一个结点，无需反转，直接返回原链表头指针
	if (l == NULL)
		return l;
	if (l->next == NULL)
		return l;
	
	LinkList p = l;
	LinkList q = NULL; // 反转后的新链表头指针，初始为NULL
	while (p != NULL)
	{
		LinkList temp = p;
		p = p->next;
		temp->next = q; // 将当前结点摘下，插入新链表的最前端
		q = temp;
	}
	
	return q;
}

/* 3. 查找单链表中倒数第k个结点 （k>0）*/
/* 最普遍的方法是，先统计单链表中结点的个数，然后再找到第（n-k）个结点。注意链表为空，k为0，k为1，k大于链表中节点个数时的情况。
 * 时间复杂度为O（n）。
 * 这里主要讲一下另一个思路，这种思路在其他题目中也会有应用。主要思路就是使用两个指针，先让前面的指针走到正向第k个结点，
 * 这样前后两个指针的距离差是k-1，之后前后两个指针一起向前走，前面的指针走到最后一个结点时，
 * 后面指针所指结点就是倒数第k个结点。
 */
LinkList ReverseGetKthNode(LinkList &l, unsigned int k)
{
	if (l == NULL || k == 0) // 这里k的计数是从1开始的，若k为0或链表为空返回NULL
			return NULL;

	LinkList first = l;
	LinkList second = l;
	while (k > 1 && first != NULL) // 前面的指针先走到正向第k个结点
	{
		first = first->next;	
		k--;
	}

	if (k > 1 || first == NULL) // 前面的指针先走到正向第k个结点
		return NULL;

	while (first->next != NULL) // 前后两个指针一起向前走，直到前面的指针指向最后一个结点 ; 这么处理是为了不让第二个指针处理second=second->next。
	{
		first = first->next;	
		second = second->next;
	}
	
	return second; // 后面的指针所指结点就是倒数第k个结点 
}

/* 4.查找单链表的中间结点 */
/* 此题可应用于上一题类似的思想。也是设置两个指针，只不过这里是，两个指针同时向前走，前面的指针每次走两步，
 * 后面的指针每次走一步，前面的指针走到最后一个结点时，后面的指针所指结点就是中间结点，即第（n/2+1）个结点。
 * 注意链表为空，链表结点个数为1和2的情况。时间复杂度O（n）。
 */
LinkList GetMiddleNode(LinkList &l)
{
	if (l == NULL)  // 链表为空或只有一个结点，返回头指针
		return l;
	
	if (l->next == NULL)
		return l;
	
	LinkList fast = l;
	LinkList slow = l;

	while (fast != NULL && fast->next != NULL) // 前面指针每次走两步，直到指向最后一个结点，后面指针每次走一步
	{
		fast = fast->next;
		slow = slow->next;
		if (fast->next != NULL)
			fast = fast->next;
	}

	return slow; // 后面的指针所指结点即为中间结点 
}

/* 5. 从尾到头遍历单链表 */
/* 对于这种颠倒顺序的问题，我们应该就会想到栈，后进先出。所以，这一题要么自己使用栈，要么让系统使用栈，
 * 也就是递归。注意链表为空的情况。时间复杂度为O（n）。
 */
void ReversePrintListRec(LinkList &l)
{
	if (l == NULL)	
		return;
	else
	{
		ReversePrintListRec(l->next);	
		cout << l->data << " "; 
	}
}

void ReversePrintListUnrec(LinkList &l)
{
	const int NUM = 50;	
	LinkList stack[NUM];
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
		cout << p->data << " ";
	}
	cout << endl;
}

/* 6. 已知两个单链表L1和L2各自有序， 把它们合并成一个链表依然有序 */
/* 这个类似归并排序。尤其注意两个链表都为空，和其中一个为空时的情况。只需要O（1）的空间。
 * 时间复杂度为O（max(len1, len2)）。
 */
LinkList MergeSortedListRec(LinkList &L1, LinkList &L2)
{
	if (L1 == NULL)
		return L2;
	if (L2 == NULL)
		return L1;

	LinkList pMerge = NULL;
	if (L1->data < L2->data)
	{
		pMerge = L1;
		pMerge->next = MergeSortedListRec(L1->next, L2);
	}
	else
	{
		pMerge = L2;	
		pMerge->next = MergeSortedListRec(L1, L2->next);
	}
	return pMerge;
}

LinkList MergeSortedListUnrec(LinkList &L1, LinkList &L2)
{
	if (L1 == NULL)
		return L2;
	if (L2 == NULL)
		return L1;
	
	LinkList pMerge = NULL;
	if (L1->data < L2->data)
	{
		pMerge = L1;	
		//pMerge->next = NULL;
		L1 = L1->next;
	}
	else
	{
		pMerge = L2;
		//pMerge->next = NULL;
		L2 = L2->next;
	}

	LinkList temp = pMerge;
	while (L1 != NULL && L2 != NULL)
	{
		if (L1->data < L2->data)	
		{
			temp->next = L1;
			L1 = L1->next;
			temp = temp->next;
			temp->next = NULL;
		}
		else
		{
			temp->next = L2;
			L2 = L2->next;
			temp = temp->next;
			temp->next = NULL;
		}
	}

	if (L1 != NULL)
		temp->next = L1;
	if (L2 != NULL)
		temp->next = L2;

	return pMerge;
}

/* 7. 判断一个单链表是否有环 */
/* 这里也是用到两个指针。如果一个链表中有环，也就是说用一个指针去遍历，是永远走不到头的。
 * 因此，我们可以用两个指针去遍历，一个指针一次走两步，一个指针一次走一步，如果有环，两个指针肯定会在环中相遇。
 * 时间复杂度为O（n）。
 */
bool ListHasCircle(LinkList &l)
{
	if (l == NULL)
		return false;
	if (l->next == NULL)
		return false;
		
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

/* 8. 判断两个单链表是否相交 */
/* 如果两个链表相交于某一节点，那么在这个相交节点之后的所有节点都是两个链表所共有的。
 * 也就是说，如果两个链表相交，那么最后一个节点肯定是共有的。
 * 先遍历第一个链表，记住最后一个节点，然后遍历第二个链表，到最后一个节点时和第一个链表的最后一个节点做比较，
 * 如果相同，则相交，否则不相交。时间复杂度为O(len1+len2)，因为只需要一个额外指针保存最后一个节点地址，空间复杂度为O(1)。
 */
bool ListIsInterSection(LinkList &L1, LinkList &L2)
{
	if (L1 == NULL || L2 == NULL)
		return false;

	LinkList l1 = L1;
	while (l1->next != NULL)
		l1 = l1->next;

	LinkList l2 = L2;
	while (l2->next != NULL)
		l2 = l2->next;
			
	return (l1 == l2);
}

/* 9. 求两个单链表相交的第一个结点 */
/* 对第一个链表遍历，计算长度len1，同时保存最后一个节点的地址。
 * 对第二个链表遍历，计算长度len2，同时检查最后一个节点是否和第一个链表的最后一个节点相同，若不相同，不相交，结束。
 * 两个链表均从头节点开始，假设len1大于len2，那么将第一个链表先遍历len1-len2个节点，
 * 此时两个链表当前节点到第一个相交节点的距离就相等了，然后一起向后遍历，直到两个节点的地址相同。
 * 时间复杂度，O(len1+len2)。
 */
LinkList GetListFirstIntersectNode(LinkList &L1, LinkList &L2)
{
	if (L1 == NULL || L2 == NULL)
		return NULL;

	LinkList pNode1 = L1;
	int len1 = 1;
	while (pNode1->next != NULL)
	{
		pNode1 = pNode1->next;
		len1++;
	}

	LinkList pNode2 = L2;
	int len2 = 1;
	while (pNode2->next != NULL)
	{
		pNode2 = pNode2->next;
		len2++;
	}

	if (pNode1 != pNode2) // 不相交直接返回NULL
		return NULL;

	pNode1 = L1;
	pNode2 = L2;
	// 先对齐两个链表的当前结点，使之到尾节点的距离相等
	if (len1 > len2)
	{
		int k = (len1 - len2);	
		while (k--)
			pNode1 = pNode1->next;
	}
	else
	{
		int k = (len2 - len1);
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

/* 10. 已知一个单链表存在环， 求进入环中的第一个结点 */
/* 首先判断是否存在环，若不存在结束。在环中的一个节点处断开（当然函数结束时不能破坏原链表），
 * 这样就形成了两个相交的单链表，求进入环中的第一个节点也就转换成了求两个单链表相交的第一个节点。
 */ 
LinkList GetFirstNodeIntoCircle(LinkList &l)
{
	if (l == NULL)
		return NULL;
	if (l->next == NULL)
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
	LinkList pNode1 = l;
	LinkList pNode2 = pAssumedTail->next;

	int len1 = 1;
	while (pNode1 != pAssumedTail)
	{
		pNode1 = pNode1->next;
		len1++;
	}
	int len2 = 1;
	while (pNode2 != pAssumedTail)
	{
		pNode2 = pNode2->next;	
		len2++;
	}

	pNode1 = l;
	pNode2 = pAssumedTail->next;
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

/* 11. 给出一单链表指针pHead和一结点指针pToBeDeleted，O(1)时间复杂度删除结点pToBeDeleted */
/* 对于删除节点，我们普通的思路就是让该节点的前一个节点指向该节点的下一个节点，这种情况需要遍历找到该节点的前一个节点，
 * 时间复杂度为O(n)。对于链表，链表中的每个节点结构都是一样的，所以我们可以把该节点的下一个节点的数据复制到该节点，
 * 然后删除下一个节点即可。要注意最后一个节点的情况，这个时候只能用常见的方法来操作，
 * 先找到前一个节点，但总体的平均时间复杂度还是O(1)。
 */
void DeleteOneNode(LinkList &l, LinkList &pToBeDeleted)
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
		if (l == pToBeDeleted) // 链表中只有一个节点的情况 
		{
			l = pToBeDeleted;		
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

int main(int argc, char **argv)
{
	LinkList head = buildLineList();
	// 移除头结点
	LinkList list = head->next;
	
	cout << "0. Traverse List : ";
	TraverseLineList(list);

	cout << "1. Get List Nodes : ";
	int nodes = GetListNodes(list);
	cout << nodes << endl;

	cout << "2. Reverse List : ";
	LinkList reverse = ReverseList(list);
	TraverseLineList(reverse);

	cout << "3. Reverse Get Kth Node : ";
	LinkList rKth = ReverseGetKthNode(reverse, 3);	
	cout << rKth->data << endl;

	cout << "4. Get Middle Node : ";
	LinkList mid = GetMiddleNode(reverse);	
	cout << mid->data << endl;

	cout << "5. Reverse Print List(recursion) : ";
	ReversePrintListRec(reverse);
	cout << endl;

	cout << "5. Reverse Print List(stack) : ";
	ReversePrintListUnrec(reverse);

	cout << "6. Merge Sorted Lists(recursion) : ";
	int array1[5] = {1, 3, 5, 7, 9};
	int array2[5] = {2, 4, 6, 8, 10};
	LinkList s1 = buildSortedLineList(array1, 5);
	LinkList s2 = buildSortedLineList(array2, 5);
	LinkList merge = MergeSortedListRec(s1->next, s2->next);
	TraverseLineList(merge);

	s1 = buildSortedLineList(array1, 5);
	s2 = buildSortedLineList(array2, 5);
	cout << "6. Merge Sorted Lists(unrecursion) : ";
	merge = MergeSortedListUnrec(s1->next, s2->next);
	TraverseLineList(merge);

	cout << "7. Judge List Has Circle : ";
	int array3[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	LinkList circle = buildHasCircleList(array3, 10);
	bool hasCircle = ListHasCircle(circle->next);
	if (hasCircle)
		cout << "TRUE" << endl;
	else
		cout << "FALSE" << endl;
	//TraverseLineList(circle); // check
	
	cout << "8. Judge Two Lists Has intersection : " << endl;;
	LinkList si1 = NULL;
	LinkList si2 = NULL;
	buildTwoIntersectList(&si1, &si2, 10);
	cout << "   si1 : "; TraverseLineList(si1->next);
	cout << "   si2 : "; TraverseLineList(si2->next);
	bool intersection = ListIsInterSection(si1->next, si2->next);
	if (intersection)
		cout << "   TRUE" << endl;
	else
		cout << "   FALSE" << endl;
/*
	cout << "8. Judge Two Lists Has intersection : ";
	intersection = ListIsInterSection(s1->next, s2->next);
	if (intersection)
		cout << "TRUE" << endl;
	else
		cout << "FALSE" << endl;
*/
	cout << "9. Get First Intersect Node : ";
	LinkList si = GetListFirstIntersectNode(si1, si2);
	cout << si->data << endl;

	cout << "10. Get First Node Into Circle : ";
	LinkList fnic = GetFirstNodeIntoCircle(circle->next);
	cout << fnic->data << endl;

	cout << "11. Delete One Node, use O(1) : ";
	LinkList s3 = buildSortedLineList(array3, 10);
	LinkList pToBeDeleted = GetOneNodeFromList(s3->next, 5);
	DeleteOneNode(s3->next, pToBeDeleted);
	TraverseLineList(s3->next);
	
	return 0;
}
