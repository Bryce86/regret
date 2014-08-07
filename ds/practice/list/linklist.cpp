#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "linklist.h"

using namespace std;

/* 创建线性链表 */
LinkList buildLineList()
{
	return NULL;
}

/* 创建有序线性链表 */
LinkList buildSortedLineList(int a[], int n)
{
	return NULL;
}

/* 创建带有环的单链表 */
LinkList buildHasCircleList(int a[], int n)
{
	return NULL;
}

/* 创建2个相交的单链表 */
void buildTwoIntersectList(LNode **L1, LNode **L2, int nodes)
{

}

/* 遍历线性链表 */
void TraverseLineList(LinkList &l)
{

}

/* 获取单链表中值为k的结点 */
LinkList GetOneNodeFromList(LinkList &l, int k)
{
	return NULL;
}

/* 1. 求单链表中结点的个数 */
/* 这是最最基本的了，应该能够迅速写出正确的代码，注意检查链表是否为空。时间复杂度为O（n）。*/
int GetListNodes(LinkList &l)
{
	return 0;
}


/* 2. 将单链表反转 */
/* 从头到尾遍历原链表，每遍历一个结点，将其摘下放在新链表的最前端。注意链表为空和只有一个结点的情况。时间复杂度为O（n）。*/
LinkList ReverseList(LinkList &l)
{
	return NULL;
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
	return NULL; // 后面的指针所指结点就是倒数第k个结点 
}

/* 4.查找单链表的中间结点 */
/* 此题可应用于上一题类似的思想。也是设置两个指针，只不过这里是，两个指针同时向前走，前面的指针每次走两步，
 * 后面的指针每次走一步，前面的指针走到最后一个结点时，后面的指针所指结点就是中间结点，即第（n/2+1）个结点。
 * 注意链表为空，链表结点个数为1和2的情况。时间复杂度O（n）。
 */
LinkList GetMiddleNode(LinkList &l)
{
	return NULL; // 后面的指针所指结点即为中间结点 
}

/* 5. 从尾到头遍历单链表 */
/* 对于这种颠倒顺序的问题，我们应该就会想到栈，后进先出。所以，这一题要么自己使用栈，要么让系统使用栈，
 * 也就是递归。注意链表为空的情况。时间复杂度为O（n）。
 */
void ReversePrintListRec(LinkList &l)
{

}

void ReversePrintListUnrec(LinkList &l)
{

}

/* 6. 已知两个单链表L1和L2各自有序， 把它们合并成一个链表依然有序 */
/* 这个类似归并排序。尤其注意两个链表都为空，和其中一个为空时的情况。只需要O（1）的空间。
 * 时间复杂度为O（max(len1, len2)）。
 */
LinkList MergeSortedListRec(LinkList &L1, LinkList &L2)
{
	return NULL;
}

LinkList MergeSortedListUnrec(LinkList &L1, LinkList &L2)
{
	return NULL;
}

/* 7. 判断一个单链表是否有环 */
/* 这里也是用到两个指针。如果一个链表中有环，也就是说用一个指针去遍历，是永远走不到头的。
 * 因此，我们可以用两个指针去遍历，一个指针一次走两步，一个指针一次走一步，如果有环，两个指针肯定会在环中相遇。
 * 时间复杂度为O（n）。
 */
bool ListHasCircle(LinkList &l)
{
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
	return false;
}

/* 9. 求两个单链表相交的第一个结点 */
/* 对第一个链表遍历，计算长度len1，同时保存最后一个节点的地址。
 * 对第二个链表遍历，计算长度len2，同时检查最后一个节点是否和第一个链表的最后一个节点相同，若不相同，不相交，结束。
 * 两个链表均从头节点开始，假设len1大于len2，那么将第一个链表先遍历len1-len2个节点，
 * 此时两个链表当前节点到第一个相交节点的距离就相等了，然后一起向后遍历，知道两个节点的地址相同。
 * 时间复杂度，O(len1+len2)。
 */
LinkList GetListFirstIntersectNode(LinkList &L1, LinkList &L2)
{
	return NULL;	
}

/* 10. 已知一个单链表存在环， 求进入环中的第一个结点 */
/* 首先判断是否存在环，若不存在结束。在环中的一个节点处断开（当然函数结束时不能破坏原链表），
 * 这样就形成了两个相交的单链表，求进入环中的第一个节点也就转换成了求两个单链表相交的第一个节点。
 */ 
LinkList GetFirstNodeIntoCircle(LinkList &l)
{
	return NULL;
}

/* 11. 给出一单链表指针pHead和一结点指针pToBeDeleted，O(1)时间复杂度删除结点pToBeDeleted */
/* 对于删除节点，我们普通的思路就是让该节点的前一个节点指向该节点的下一个节点，这种情况需要遍历找到该节点的前一个节点，
 * 时间复杂度为O(n)。对于链表，链表中的每个节点结构都是一样的，所以我们可以把该节点的下一个节点的数据复制到该节点，
 * 然后删除下一个节点即可。要注意最后一个节点的情况，这个时候只能用常见的方法来操作，
 * 先找到前一个节点，但总体的平均时间复杂度还是O(1)。
 */
void DeleteOneNode(LinkList &l, LinkList &pToBeDeleted)
{

}

int main(int argc, char **argv)
{
	LinkList head = buildLineList();
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
