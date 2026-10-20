#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
LeetCode 138. 随机链表的复制 / Copy List with Random Pointer。
剑指 Offer 面试题 26
*/


/*
复杂链表就是每个节点除了 next 指针，还有一个 random 指针，可能指向链表中任意节点或 nullptr。拷贝时要做到深拷贝：新链表的 val、next、random 都必须指向新节点，不能和原链表共享节点。
*/

struct ListNode {
    int val;
    ListNode* next;
    ListNode* random;
    explicit ListNode(int v = 0)
        : val(v), next(nullptr), random(nullptr) {}
};

ListNode* buildRandomListTail(std::vector<int> vals)
{
    ListNode dummy;
    ListNode* tail = &dummy;

    std::unordered_map<int, ListNode*> mp;

    // 创建链表
    for (int i = 0; i < vals.size(); i++) {
        mp[i] = new ListNode(vals[i]);
        tail->next = mp[i];
        tail = tail->next;
    }

    // 设置sibling/random pointer
    ListNode* head = dummy.next;
    int count = vals.size()-1;

    // like, circle
    while (head && count>=0) {
        head->random = mp[count--];
        head = head->next;
    }

    return dummy.next;
}

void printRandomList(const ListNode* head)
{
    while (head)
    {
        std::cout << head->val;
        if (head->random)
            std::cout << "(" << head->random->val << ")";
        if (head->next)
            std::cout << " -> ";
        head = head->next;
    }
    std::cout << "\n";
}

// 方法一：哈希表法（推荐）
ListNode* copyRandomListHash(ListNode* head)
{
    if (!head) return nullptr;

    std::unordered_map<ListNode*, ListNode*> mp;

    /// 第一遍：复制节点，建立 old -> new 映射
    ListNode* cur = head;
    while (cur) {
        mp[cur] = new ListNode(cur->val);
        cur = cur->next;
    }

    // 第二遍：连接 next 和 random
    cur = head;
    while (cur) {
        mp[cur]->next   = mp[cur->next];
        mp[cur]->random = mp[cur->random];
        cur = cur->next;
    }

    return mp[head];
}

// 方法二：原地拼接拆分法（O(1) 额外空间）

ListNode* copyRandomListSplit(ListNode* head)
{
    if (!head) return nullptr;

    ListNode* cur = head;

    // 1. 在每个原节点后面插入复制节点
    // A -> B -> C  变成  A -> A' -> B -> B' -> C -> C'
    while (cur)
    {
        ListNode* copy = new ListNode(cur->val);
        copy->next = cur->next;
        cur->next = copy;
        cur = copy->next;
    }

    // 2. 设置复制节点的 random
    cur = head;
    while (cur)
    {
        ListNode* copy = cur->next;
        // 如果A的random是C，那么cur->random->next就是C'
        if (cur->random)
            copy->random = cur->random->next;
        // 跳到下一原始结点
        cur = copy->next;
    }

    // 3. 拆分原链表和复制链表
    ListNode* newHead = head->next;
    cur = head;
    while (cur)
    {
        ListNode* copy = cur->next;
        cur->next = copy->next;
        if (copy->next) {
            copy->next = copy->next->next;
        }
        cur = cur->next;
    }

    return newHead;
}

int main()
{
    ListNode* list1 = buildRandomListTail({1,2,3,4,5,6});
    cout << "list(" << list1 << "): ";
    printRandomList(list1);

    ListNode* list2 = copyRandomListHash(list1);
    cout << "copy(" << list2 << "): ";
    printRandomList(list2);

    ListNode* list3 = copyRandomListSplit(list1);
    cout << "copy(" << list3 << "): ";
    printRandomList(list3);

    return 0;
}

