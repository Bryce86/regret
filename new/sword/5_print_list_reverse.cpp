#include <iostream>
#include <stack>
#include <vector>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x = -1) : val(x), next(nullptr) {}
};

ListNode* buildListTail(int a[], int n)
{
    ListNode dummy;
    ListNode* tail = &dummy;

    for (int i = 0; i < n; i++)
    {
        tail->next = new ListNode(a[i]);
        tail = tail->next;
    }
    return dummy.next;
}

void printList(ListNode* head)
{
    while (head)
    {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << "\n";
}

/*
方法一：栈（推荐，面试首选）
遍历链表，把每个节点的值压入栈，再依次弹出打印。
*/

// 返回逆序数组（更通用，不直接打印）
std::vector<int> printListFromTailToHead(ListNode* head)
{
    std::stack<int> stk;

    ListNode* cur = head;
    while (cur) {
        stk.push(cur->val);
        cur = cur->next;
    }

    std::vector<int> result;
    while (!stk.empty())
    {
        result.push_back(stk.top());
        stk.pop();
    }

    return result;
}

/*
方法二：递归
递归到链表末尾，回溯时打印，天然就是逆序。
*/
void printListInReverse(ListNode* head)
{
    if (!head) return;

    printListInReverse(head->next);
    std::cout << head->val << " ";
}

/*
方法三：反转链表后再正序打印
先原地反转链表，再遍历打印。
但会破坏原链表结构，除非题目允许，否则不推荐。
*/

int main()
{
    int a[] = {1,2,3,4,5,6};
    ListNode* p = buildListTail(a, 6);
    printList(p);

    // method 1
    auto v1 = printListFromTailToHead(p);
    for (auto x : v1) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // method 2
    printListInReverse(p); std::cout << "\n";

    return 0;
}


