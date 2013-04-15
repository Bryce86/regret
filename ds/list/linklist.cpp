#include <iostream>
#include <time.h>
#include "linklist.h"

using namespace std;

/* ������������ */
LinkList buildLineList()
{
	srand((unsigned int)time(NULL));
	
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

/* ���������������� */
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

/* �������л��ĵ����� */
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

/* ����2���ཻ�ĵ����� */
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

/* ������������ */
void TraverseLineList(LinkList &l)
{
	LinkList p = l;
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}

/* ��ȡ��������ֵΪk�Ľ��� */
LinkList GetOneNodeFromList(LinkList &l, int k)
{
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

/* 1. ���������н����ĸ��� */
/* ���������������ˣ�Ӧ���ܹ�Ѹ��д����ȷ�Ĵ��룬ע�����������Ƿ�Ϊ�ա�ʱ�临�Ӷ�ΪO��n����*/
int GetListNodes(LinkList &l)
{
	if (l == NULL || l->next == NULL)
		return 0;

	LinkList p = l;
	int count = 0;
	
	while (p != NULL)
	{
		p = p->next;
		count++;
	}
		
	return count;
}


/* 2. ����������ת */
/* ��ͷ��β����ԭ������ÿ����һ�����㣬����ժ�·�������������ǰ�ˡ�ע������Ϊ�պ�ֻ��һ��������������ʱ�临�Ӷ�ΪO��n����*/
LinkList ReverseList(LinkList &l)
{
	// ��������Ϊ�ջ�ֻ��һ�����㣬���跴ת��ֱ�ӷ���ԭ����ͷָ��
	if (l == NULL || l->next == NULL)
		return l;
	
	LinkList p = l;
	LinkList q = NULL; // ��ת����������ͷָ�룬��ʼΪNULL
	while (p != NULL)
	{
		LinkList temp = p;
		p = p->next;
		temp->next = q; // ����ǰ����ժ�£���������������ǰ��
		q = temp;
	}
	
	return q;
}

/* 3. ���ҵ������е�����k������ ��k>0��*/
/* ���ձ��ķ����ǣ���ͳ�Ƶ������н����ĸ�����Ȼ�����ҵ��ڣ�n-k�������㡣ע������Ϊ�գ�kΪ0��kΪ1��k���������нڵ�����ʱ��������
 * ʱ�临�Ӷ�ΪO��n����
 * ������Ҫ��һ����һ��˼·������˼·��������Ŀ��Ҳ����Ӧ�á���Ҫ˼·����ʹ������ָ�룬����ǰ����ָ���ߵ�������k�����㣬
 * ����ǰ������ָ���ľ�������k-1��֮��ǰ������ָ��һ����ǰ�ߣ�ǰ����ָ���ߵ�����һ������ʱ��
 * ����ָ����ָ�������ǵ�����k�����㡣
 */
LinkList ReverseGetKthNode(LinkList &l, unsigned int k)
{
	if (l == NULL || k == 0) // ����k�ļ����Ǵ�1��ʼ�ģ���kΪ0������Ϊ�շ���NULL
			return NULL;

	LinkList first = l;
	LinkList second = l;
	while (k > 1 && first != NULL) // ǰ����ָ�����ߵ�������k������
	{
		first = first->next;	
		k--;
	}

	if (k > 1 || first == NULL) // ��������С��k������NULL
		return NULL;

	while (first->next != NULL) // ǰ������ָ��һ����ǰ�ߣ�ֱ��ǰ����ָ��ָ������һ������    		
	{
		first = first->next;	
		second = second->next;
	}
	
	return second; // ������ָ����ָ�������ǵ�����k������ 	
}

/* 4.���ҵ��������м����� */
/* ������Ӧ������һ�����Ƶ�˼�롣Ҳ����������ָ�룬ֻ���������ǣ�����ָ��ͬʱ��ǰ�ߣ�ǰ����ָ��ÿ����������
 * ������ָ��ÿ����һ����ǰ����ָ���ߵ�����һ������ʱ��������ָ����ָ���������м����㣬���ڣ�n/2+1�������㡣
 * ע������Ϊ�գ�������������Ϊ1��2��������ʱ�临�Ӷ�O��n����
 */
LinkList GetMiddleNode(LinkList &l)
{
	if (l == NULL || l->next == NULL)  // ����Ϊ�ջ�ֻ��һ�����㣬����ͷָ��
		return l;
	
	LinkList fast = l;
	LinkList slow = l;

	while (fast != NULL && fast->next != NULL) // ǰ��ָ��ÿ����������ֱ��ָ������һ�����㣬����ָ��ÿ����һ��
	{
		fast = fast->next;
		slow = slow->next;
		if (fast->next != NULL)
			fast = fast->next;
	}

	return slow; // ������ָ����ָ���㼴Ϊ�м�����  
}

/* 5. ��β��ͷ���������� */
/* �������ֵߵ�˳�������⣬����Ӧ�þͻ��뵽ջ�������ȳ������ԣ���һ��Ҫô�Լ�ʹ��ջ��Ҫô��ϵͳʹ��ջ��
 * Ҳ���ǵݹ顣ע������Ϊ�յ�������ʱ�临�Ӷ�ΪO��n����
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

/* 6. ��֪����������L1��L2���������� �����Ǻϲ���һ��������Ȼ���� */
/* �������ƹ鲢����������ע������������Ϊ�գ�������һ��Ϊ��ʱ��������ֻ��ҪO��1���Ŀռ䡣
 * ʱ�临�Ӷ�ΪO��max(len1, len2)����
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

/* 7. �ж�һ���������Ƿ��л� */
/* ����Ҳ���õ�����ָ�롣����һ���������л���Ҳ����˵��һ��ָ��ȥ����������Զ�߲���ͷ�ġ�
 * ���ˣ����ǿ���������ָ��ȥ������һ��ָ��һ����������һ��ָ��һ����һ���������л�������ָ���϶����ڻ���������
 * ʱ�临�Ӷ�ΪO��n����
 */
bool ListHasCircle(LinkList &l)
{
	if (l == NULL || l->next == NULL)
		return false;

	LinkList fast = l; // ��ָ��ÿ��ǰ��2��
	LinkList slow = l; // ��ָ��ÿ��ǰ��1��

	while (fast != NULL && fast->next != NULL)
	{
		fast = fast->next->next;	
		slow = slow->next;

		if (fast == slow) // ���������ڻ�
			return true;
	}
	return false;
}

/* 8. �ж������������Ƿ��ཻ */
/* �������������ཻ��ĳһ�ڵ㣬��ô�������ཻ�ڵ�֮�������нڵ㶼���������������еġ�
 * Ҳ����˵���������������ཻ����ô����һ���ڵ��϶��ǹ��еġ�
 * �ȱ�����һ����������ס����һ���ڵ㣬Ȼ�������ڶ���������������һ���ڵ�ʱ�͵�һ������������һ���ڵ����Ƚϣ�
 * ������ͬ�����ཻ���������ཻ��ʱ�临�Ӷ�ΪO(len1+len2)����Ϊֻ��Ҫһ������ָ�뱣������һ���ڵ���ַ���ռ临�Ӷ�ΪO(1)��
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

/* 9. �������������ཻ�ĵ�һ������ */
/* �Ե�һ���������������㳤��len1��ͬʱ��������һ���ڵ��ĵ�ַ��
 * �Եڶ����������������㳤��len2��ͬʱ��������һ���ڵ��Ƿ��͵�һ������������һ���ڵ���ͬ��������ͬ�����ཻ��������
 * ������������ͷ�ڵ㿪ʼ������len1����len2����ô����һ�������ȱ���len1-len2���ڵ㣬
 * ��ʱ����������ǰ�ڵ㵽��һ���ཻ�ڵ��ľ����������ˣ�Ȼ��һ������������֪�������ڵ��ĵ�ַ��ͬ��
 * ʱ�临�Ӷȣ�O(len1+len2)��
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

	if (pNode1 != pNode2) // ���ֱཻ�ӷ���NULL
		return NULL;

	pNode1 = L1;
	pNode2 = L2;
	// �ȶ������������ĵ�ǰ���㣬ʹ֮��β�ڵ��ľ�������
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

/* 10. ��֪һ�����������ڻ��� �����뻷�еĵ�һ������ */
/* �����ж��Ƿ����ڻ����������ڽ������ڻ��е�һ���ڵ㴦�Ͽ�����Ȼ��������ʱ�����ƻ�ԭ��������
 * �������γ��������ཻ�ĵ������������뻷�еĵ�һ���ڵ�Ҳ��ת�������������������ཻ�ĵ�һ���ڵ㡣
 */ 
LinkList GetFirstNodeIntoCircle(LinkList &l)
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

	// �����еĴ˽ڵ���Ϊ������β�ڵ㣬�������������������ཻ����
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
	// �ȶ������������ĵ�ǰ���㣬ʹ֮��β�ڵ��ľ�������
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

/* 11. ����һ������ָ��pHead��һ����ָ��pToBeDeleted��O(1)ʱ�临�Ӷ�ɾ������pToBeDeleted */
/* ����ɾ���ڵ㣬������ͨ��˼·�����øýڵ���ǰһ���ڵ�ָ���ýڵ�����һ���ڵ㣬����������Ҫ�����ҵ��ýڵ���ǰһ���ڵ㣬
 * ʱ�临�Ӷ�ΪO(n)�����������������е�ÿ���ڵ��ṹ����һ���ģ��������ǿ��԰Ѹýڵ�����һ���ڵ������ݸ��Ƶ��ýڵ㣬
 * Ȼ��ɾ����һ���ڵ㼴�ɡ�Ҫע������һ���ڵ�������������ʱ��ֻ���ó����ķ�����������
 * ���ҵ�ǰһ���ڵ㣬��������ƽ��ʱ�临�ӶȻ���O(1)��
 */
void DeleteOneNode(LinkList &l, LinkList &pToBeDeleted)
{
	if (pToBeDeleted == NULL)	
		return;

	if (pToBeDeleted->next != NULL)
	{
		pToBeDeleted->data = pToBeDeleted->next->data; // ����һ���ڵ������ݸ��Ƶ����ڵ㣬Ȼ��ɾ����һ���ڵ�
		LinkList temp = pToBeDeleted->next;
		pToBeDeleted->next = pToBeDeleted->next->next;
		delete temp;
	}
	else // Ҫɾ����������һ���ڵ� 
	{
		if (l == pToBeDeleted) // ������ֻ��һ���ڵ�������  
		{
			l = pToBeDeleted;		
			delete pToBeDeleted;
		}
		else
		{
			LinkList pNode = l;		
			while (pNode->next != pToBeDeleted) // �ҵ������ڶ����ڵ�
				pNode = pNode->next;
			pNode->next = NULL;
			delete pToBeDeleted;
		}
	}
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
