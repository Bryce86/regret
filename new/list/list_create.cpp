#include <iostream>
#include <memory>
#include <initializer_list>

/* check g++ default cpp standard
 *
 * g++ -dM -E -x c++ /dev/null | grep __cplusplus
 */

// version1: bare pointer
struct ListNode {
    int value;
    ListNode* next;
    explicit ListNode(int v = 0, ListNode* n = nullptr)
        : value(v), next(n) { }
};

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

// head insertion method
ListNode* buildListHead(std::initializer_list<int> vals)
{
    ListNode* head = nullptr;
    for (int v : vals) {
        head = new ListNode(v, head);
    }
    return head;
}

void printList(const ListNode* head)
{
    while (head)
    {
        std::cout << head->value;
        if (head->next)
            std::cout << " -> ";
        head = head->next;
    }
    std::cout << "\n";
}

void freeList(ListNode* head)
{
    while (head)
    {
        ListNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}

#if __cplusplus >= 201402L

// version2: unique_ptr (auto release)
struct Node {
    int value;
    std::unique_ptr<Node> next;
    explicit Node(int v = 0) : value(v), next(nullptr) {}
};

// tail insert, return owning pointer
std::unique_ptr<Node> buildUnique(std::initializer_list<int> vals)
{
    Node dummy;
    Node* tail = &dummy;

    for (int v : vals) {
        tail->next = std::make_unique<Node>(v);
        tail = tail->next.get();
    }
    return std::move(dummy.next);
}

void printUnique(const std::unique_ptr<Node>& head)
{
    const Node* p = head.get();
    while (p) {
        std::cout << p->value;
        if (p->next)
            std::cout << " -> ";
        p = p->next.get();
    }
    std::cout << "\n";
}

// not need free/delete

#endif

int main()
{
    // version1:
    ListNode* p = buildListTail({1,2,3,4,5,6});
    ListNode* q = buildListHead({1,2,3,4,5,6});

    std::cout << "tail insert method: \n";
    printList(p);
    std::cout << "head insert method: \n";
    printList(q);

#if __cplusplus >= 201402L

    // version2:
    auto r = buildUnique({1,2,3,4,5,6});
    printUnique(r);

#endif
}














