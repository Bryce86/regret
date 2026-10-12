#include <stdio.h>
#include <stdlib.h>

// declare node
typedef struct ListNode {
    int value;
    struct ListNode *next;
} ListNode;

// create node
static ListNode* make_node(int val)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    node->value = val;
    node->next = NULL;
    return node;
}

// tail insertion method
ListNode* list_create_tail(const int arr[], size_t n)
{
    // local sentinel (not consider empty list)
    ListNode dummy;
    ListNode* tail = &dummy;
    dummy.next = NULL;

    for (size_t i = 0; i < n; i++)
    {
        tail->next = make_node(arr[i]);
        tail = tail->next;
    }
    return dummy.next;
}

// head insertion method
ListNode* list_create_head(const int arr[], size_t n)
{
    ListNode* head = NULL;

    for (size_t i = 0; i < n; i++)
    {
        ListNode* node = make_node(arr[i]);
        node->next = head;
        head = node;
    }
    return head;
}

// output
void list_print(const ListNode* head)
{
    while (head) {
        printf("%d -> ", head->value);
        head = head->next;
    }
    printf("NULL\n");
}

// release list
void list_free(ListNode* head)
{
    while (head)
    {
        ListNode* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main()
{
    int data[] = {15,26,33,41,50,68};
    size_t n = sizeof(data)/sizeof(data[0]);

    ListNode* p = list_create_tail(data, n);
    ListNode* q = list_create_head(data, n);

    printf("asc:\n");
    list_print(p);
    printf("desc:\n");
    list_print(q);

    list_free(p);
    list_free(q);

    return 0;
}




