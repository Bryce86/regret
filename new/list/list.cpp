#include <iostream>
#include <vector>
#include <stack>
#include <initializer_list>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int v = 0, ListNode* n = nullptr) : val(v), next(n) {}
};

void traverseList(ListNode* head)
{
    while (head) {
        cout << head->val;
        if (head->next) {
            cout << " -> ";
        }
        head = head->next;
    }
    cout << "\n";
}

// tail insertion method
ListNode* buildListTail(std::initializer_list<int> vals)
{
    ListNode dummy;
    ListNode* tail = &dummy;

    for (int v : vals) {
        tail->next = new ListNode(v);
        tail = tail->next;
    }
    return dummy.next;
}

void freeList(ListNode* head) {
    while (head)
    {
        ListNode* p = head;
        head = head->next;
        delete p;
    }
}

// circle tail insertion method
ListNode* buildCycleList(std::initializer_list<int> vals)
{
    ListNode dummy;
    ListNode* tail = &dummy;
    ListNode* intersect = nullptr;

    // transfer view to vector
    std::vector<int> vec(vals.begin(), vals.end());
    int n = vec.size();

    for (int i = 0; i < n; i++) {
        tail->next = new ListNode(vec[i]);
        tail = tail->next;
        // save the middle node
        if (i == n/2)  {
            intersect = tail;
        }
    }
    // last node points to the middle
    tail->next = intersect;

    return dummy.next;
}

bool hasCycle(ListNode* head) {
    if (!head) return false;

    ListNode* fast = head;
    ListNode* slow = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            return true;
        }
    }

    return false;
}

/* 已知一个单链表存在环， 求进入环中的第一个结点 */
ListNode* detectCycleEntry(ListNode* head)
{
    if (!head) return nullptr;

    ListNode* fast = head;
    ListNode* slow = head;

    // 阶段一：找相遇点
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;
    }

    // fast 走到头 = 无环
    if (!fast || !fast->next) return nullptr;

    // 阶段二：一个从 head，一个从相遇点，同速出发
    ListNode* p = head;
    while (p != slow) {
        p = p->next;
        slow = slow->next;
    }

    return p; /* 相遇即入口 */
}

// build 2 intersect lists with same length
// return the intersect node
ListNode* buildTwoIntersectLists(ListNode*& l1,
                                 ListNode*& l2)
{
    l1 = buildListTail({1,2,3});
    l2 = buildListTail({4,5,6});
    ListNode* common = buildListTail({7,8,9});

    if (l1) {
        ListNode* tmp = l1;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = common;
    } else {
        l1 = common;
    }

    if (l2) {
        ListNode* tmp = l2;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = common;
    } else {
        l2 = common;
    }

    return common;
}

bool hasIntersection(ListNode* l1, ListNode* l2)
{
    while (l1->next) {
        l1 = l1->next;
    }
    while (l2->next) {
        l2 = l2->next;
    }
    return (l1 == l2);
}

// not care about lengths
// short list finishes traversing, both pointer to the long one
// traverse together
ListNode* getIntersectionNode(ListNode* l1, ListNode* l2)
{
    if (!l1 || !l2) return nullptr;

    ListNode* p = l1;
    ListNode* q = l2;

    while (p != q) {
        p = p ? p->next : l2;
        q = q ? q->next : l1;
    }

    return p;
}

// length align firstly
ListNode* getIntersectionNodeByLen(ListNode* l1, ListNode* l2)
{
    int a = 0, b = 0;
    for (ListNode* p = l1; p; p = p->next) a++;
    for (ListNode* p = l2; p; p = p->next) b++;

    ListNode* p = l1;
    ListNode* q = l2;

    // if a-b > 0, l1 is longer than l2
    // if b-a < 0, l2 is longer than l1
    for (int i = 0; i < a-b; i++) p = p->next;
    for (int i = 0; i < b-a; i++) q = q->next;

    while (p && p != q) {
        p = p->next;
        q = q->next;
    }
    return p;
}

// get the node which's value K
ListNode* getKValueNode(ListNode* head, int k)
{
    while (head)
    {
        if (head->val == k)
            return head;
        head = head->next;
    }
    return nullptr;
}

// 1. get list length
int getListLength(ListNode* head)
{
    int count = 0;

    while (head) {
        head = head->next;
        count++;
    }

    return count;
}

// 2. reverse list (head insert)
ListNode* reverseList1(ListNode* head)
{
    ListNode dummy;
    dummy.next = nullptr;

    ListNode* p = head;

    while (p)
    {
        ListNode* q = p;
        p = p->next;
        q->next = dummy.next;
        dummy.next = q;
    }
    return dummy.next;
}

// 3 pointers iterate
ListNode* reverseList2(ListNode* head)
{
    ListNode* prev = nullptr;
    ListNode* next = nullptr;
    ListNode* curr = head;

    while (curr)
    {
        next = curr->next; // 1.先记住后继，否则链就断了
        curr->next = prev; // 2.反转当前节点的指针
        prev = curr; // 3.prev, curr整体后移一步
        curr = next;
    }
    return prev; // 4.curr为空时，prev正好是原节点
}

// recursive
ListNode* reverseRec(ListNode* head)
{
    if (!head || !head->next)
        return head;

    ListNode* newHead = reverseRec(head->next);
    head->next->next = head;
    head->next = nullptr;

    return newHead;
}

//
ListNode* removeKthFromEnd(ListNode* head, int k)
{
    if (!head || k <= 0)
        return head;

    ListNode dummy;
    dummy.next = head;
    ListNode* fast = &dummy;
    ListNode* slow = &dummy;

    for (int i = 0; i < k; i++)
    {
        fast = fast->next;
        if (!fast) {
            cout << "K exceeds list length\n";
            return head;
        }
    }

    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }

    ListNode* del = slow->next;
    slow->next = del->next;
    free(del);

    return dummy.next;
}

//
ListNode* middleNode(ListNode* head)
{
    if (!head) return nullptr;

    ListNode* fast = head;
    ListNode* slow = head;

    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

ListNode* middleNodeFirst(ListNode* head)
{
    if (!head) return nullptr;

    ListNode* fast = head->next;
    ListNode* slow = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

void reversePrint(ListNode* head)
{
    if (!head) return;

    std::stack<int> s;
    ListNode* p = head;
    while (p) {
        s.push(p->val);
        p = p->next;
    }

    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << "\n";
}

// need a wrapper to output \n
void reversePrintRec(ListNode* head)
{
    if (!head) return;

    reversePrintRec(head->next);
    cout << head->val << " ";
}

ListNode* mergeTwoSortedLists(ListNode* l1, ListNode* l2)
{
    ListNode dummy;
    ListNode* tail = &dummy;
    dummy.next = nullptr;

    while (l1 && l2)
    {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    tail->next = l1 ? l1 : l2;

    return dummy.next;
}

ListNode* mergeTwoSortedListsRec(ListNode* l1, ListNode* l2)
{
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->val <= l2->val) {
        l1->next = mergeTwoSortedListsRec(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeTwoSortedListsRec(l1, l2->next);
        return l2;
    }
}

/* 2. 方法一：O(1) 偷天换日（LeetCode 237 标准解）
 * 只给待删节点指针，不給 head。
 * 返回 0 成功，-1 失败（node 为 NULL 或是尾节点）。
 * ★ 注意：被 free 的是 node->next，node 本身还在原地，只是内容被替换了。
 */
int deleteNode(ListNode* del)
{
    if (!del || !del->next) return -1; // tail node

    ListNode* tmp = del->next;
    del->val = tmp->val;
    del->next = tmp->next;
    delete tmp;
    return 0;
}

/* 3. 方法二：知道 head 时，老老实实找前驱（能删任意节点，含尾）
 * 需要 Node **phead，因为删头节点会改变 head —— 这就是前面讲二级指针的意义。
 */
int deleteNodeWithHead(ListNode*& head, ListNode* del)
{
    if (!head || !del) return -1;

    /* ① 删的是头节点：直接挪头 */
    if (head == del)
    {
        ListNode* tmp = head;
        head = head->next;
        delete head;
        return 0;
    }

    /* ② 其他情况：找前驱 */
    ListNode* p = head;

    /* ★ 判 p->next，保证退出时 p 是前驱 */
    while (p->next && p->next != del)
        p = p->next;

    if (!p->next) return -1; // not found

    p->next = del->next;
    delete del;
    return 0;
}

/* 方法三：通用兜底 —— 有 head 就用方法二，没 head 且非尾用方法一
 * 工程上最实用：先尝试 O(1)，失败再退化成 O(n) 扫描（仅当你知道它是尾节点且你有 head）。
 */
int deleteNodeSaft(ListNode*& head, ListNode* del)
{
    if (!del) return -1;
    if (del->next) return deleteNode(del); /* 非尾：O(1) 搞定 */
    if (head) return deleteNodeWithHead(head, del); /* 尾节点：只能靠 head 扫 */
    return -1; /* 既没后继又没 head，无解 */
}

int main()
{
    {
        cout << "(1) build list: ";
        ListNode* p = buildListTail({1,2,3,4,5,6});
        traverseList(p);
        freeList(p);
    }

    {
        cout << "(2) build cycle list: \n";
        ListNode* p = buildCycleList({1,2,3,4,5,6,7,8});
        // TODO: check circle
        cout << "hasCycle: "
             << (hasCycle(p) ? "yes" : "no") << "\n";
        // TODO: find intersection
        // TODO: free correctly
        //cout << "\n";
    }

    {
        cout << "(3) build 2 intersected lists: \n";
        ListNode* l1 = nullptr;
        ListNode* l2 = nullptr;
        ListNode* l3 = buildTwoIntersectLists(l1, l2);
        if (l1) traverseList(l1);
        if (l2) traverseList(l2);
        if (l3) traverseList(l3);

        cout << "has intersection: "
             << (hasIntersection(l1, l2) ? "yes" : "no") << "\n";

        cout << "intersection: ";
        auto i = getIntersectionNode(l1, l2);
        cout << i->val << "\n";
        cout << "intersection by len: ";
        auto j = getIntersectionNodeByLen(l1, l2);
        cout << j->val << "\n";
    }

    {
        cout << "(4) get the node == K:\n";
        ListNode* p = buildListTail({1,2,3,4,5,6,7,8});
        ListNode* k = getKValueNode(p, 5);
        cout << "K's Value: " << k->val << endl;
        freeList(p);
    }

    {
        cout << "(5) reverse list:\n";

        ListNode* p1 = buildListTail({1,2,3});
        cout << "p1: ";
        traverseList(p1);
        ListNode* q1 = reverseList1(p1);
        cout << "q1: ";
        traverseList(q1);

        ListNode* p2 = buildListTail({4,5,6});
        cout << "p2: ";
        traverseList(p2);
        ListNode* q2 = reverseList1(p2);
        cout << "q2: ";
        traverseList(q2);

        ListNode* p3 = buildListTail({7,8,9});
        cout << "p3: ";
        traverseList(p3);
        ListNode* q3 = reverseRec(p3);
        cout << "q3: ";
        traverseList(q3);

    }

    {
        cout << "(6) remove 4th from end:\n";
        ListNode* p = buildListTail({1,2,3,4,5,6,7,8});
        cout << "origin: ";
        traverseList(p);
        ListNode* q = removeKthFromEnd(p, 4);
        cout << "delete: ";
        traverseList(q);
    }

    {
        cout << "(7) middle node: \n";
        ListNode* p1 = buildListTail({1,2,3,4,5,6,7});
        traverseList(p1);
        ListNode* q1 = middleNode(p1);
        ListNode* q2 = middleNodeFirst(p1);
        cout << "q1: " << q1->val << endl;
        cout << "q2: " << q2->val << endl;

        ListNode* p2 = buildListTail({1,2,3,4,5,6,7,8});
        traverseList(p2);
        ListNode* q3 = middleNode(p2);
        ListNode* q4 = middleNodeFirst(p2);
        cout << "q3: " << q3->val << endl;
        cout << "q4: " << q4->val << endl;
    }

    {
        cout << "(8) print list reversely:\n";
        ListNode* p = buildListTail({1,2,3,4,5,6,7});
        traverseList(p);
        reversePrint(p);
        reversePrintRec(p); cout << "\n";
    }

    {
        cout << "(9) merge 2 sorted lists:\n";
        ListNode* p1 = buildListTail({1,3,5,7});
        traverseList(p1);
        ListNode* p2 = buildListTail({2,4,6,8});
        traverseList(p2);
        ListNode* p3 = mergeTwoSortedLists(p1, p2);
        traverseList(p3);

        p1 = buildListTail({1,3,5,7});
        p2 = buildListTail({2,4,6,8});
        p3 = mergeTwoSortedListsRec(p1, p2);
        traverseList(p3);
    }

    {
        cout << "cycle entry: ";
        ListNode* p = buildCycleList({1,2,3,4,5,6,7,8});
        ListNode* e = detectCycleEntry(p);
        cout << e->val << "\n";
    }

    {
        cout << "delete node:\n";
        ListNode* p1 = buildListTail({1,2,3});
        ListNode* d1 = p1->next;
        traverseList(p1);
        deleteNode(d1);
        traverseList(p1);

        ListNode* p2 = buildListTail({5,6,7});
        ListNode* d2 = p2->next->next;
        traverseList(p2);
        deleteNodeWithHead(p2, d2);
        traverseList(p2);
    }

    return 0;
}

