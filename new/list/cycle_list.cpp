#include <stdio.h>
#include <stdlib.h>

/* ---------- 1. 基本定义 ---------- */
typedef struct Node {
    int val;
    struct Node *next;
} Node;

static Node *newNode(int v) {
    Node *p = (Node *)malloc(sizeof(Node));
    if (!p) { perror("malloc"); exit(EXIT_FAILURE); }
    p->val  = v;
    p->next = NULL;
    return p;
}

static Node *buildList(const int a[], int n) {
    Node dummy, *tail = &dummy;
    dummy.next = NULL;
    for (int i = 0; i < n; i++) {
        tail->next = newNode(a[i]);
        tail = tail->next;
    }
    return dummy.next;
}

static void printList(const char *name, Node *h) {
    printf("%s: ", name);
    if (!h) { printf("(空)\n"); return; }
    while (h) {
        printf("%d", h->val);
        h = h->next;
        if (h) printf(" -> ");
    }
    printf("\n");
}

static void freeList(Node *h) {
    while (h) { Node *t = h; h = h->next; free(t); }
}

/* ---------- 2. 造一条带环的链表（测试专用）
 * pos: 尾节点连回去的位置下标（0-based），-1 表示无环
 */
Node *buildCyclic(const int a[], int n, int pos) {
    Node *head = buildList(a, n);
    if (pos < 0 || pos >= n) return head;      /* 无环 */
    Node *tail = head, *entry = head;
    while (tail->next) tail = tail->next;      /* 找尾 */
    for (int i = 0; i < pos; i++) entry = entry->next;  /* 找入口 */
    tail->next = entry;                        /* ★ 成环 */
    return head;
}

/* 安全释放带环链表：先打断环，再 free */
static void freeCyclic(Node *head, Node *entry) {
    if (!head) return;
    if (entry) {                               /* 有环：找到环上最后一个节点，断链 */
        Node *p = entry;
        while (p->next != entry) p = p->next;
        p->next = NULL;
    }
    freeList(head);                            /* 现在是无环链了 */
}

/* ---------- 3. 判环（Floyd 判圈，LeetCode 141）----------
 * 返回 1 有环，0 无环。可选参数 meet 用于返回相遇点（不需要传 NULL）。
 */
int hasCycle(Node *head, Node **meet) {
    if (!head) { if (meet) *meet = NULL; return 0; }

    Node *slow = head, *fast = head;
    while (fast && fast->next) {               /* ★ 顺序不能反，见下文坑位1 */
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {                    /* 追上了 = 有环 */
            if (meet) *meet = slow;
            return 1;
        }
    }
    if (meet) *meet = NULL;
    return 0;                                  /* fast 到 NULL = 无环 */
}

/* ---------- 4. 求环的入口（LeetCode 142）----------
 * 原理：设起点到入口 a，入口到相遇点 b，环长 c。
 *   slow 走了 a+b，fast 走了 a+b+kc，且 fast = 2*slow
 *   => a+b = k*c => a = k*c - b = (k-1)*c + (c-b)
 *   即「从相遇点再走 c-b 回到入口」=「从 head 走 a 到入口」
 *   所以两指针分别从 head 和相遇点同速出发，相遇处就是入口。
 */
Node *detectCycleEntry(Node *head) {
    if (!head) return NULL;

    Node *slow = head, *fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;               /* 先找到相遇点 */
    }
    if (!fast || !fast->next) return NULL;     /* 没相遇 = 无环 */

    /* 第二阶段：一个从 head，一个从相遇点，同速前进 */
    Node *p = head;
    while (p != slow) {
        p    = p->next;
        slow = slow->next;
    }
    return p;                                  /* 入口节点 */
}

/* ---------- 5. 求环的长度（从相遇点绕一圈计数）---------- */
int cycleLength(Node *meet) {
    if (!meet) return 0;
    int len = 1;
    Node *p = meet->next;
    while (p != meet) {
        len++;
        p = p->next;
    }
    return len;
}

/* ---------- 6. 验证 ---------- */
int main(void) {
    int a[] = {3, 2, 0, -4};

    /* 用例1：有环，入口在下标 1（值 2） */
    Node *c1 = buildCyclic(a, 4, 1);
    Node *m1 = NULL;
    printf("=== 有环链表 ===\n");
    printf("有环? %d\n", hasCycle(c1, &m1));           /* 1 */
    if (m1) {
        printf("相遇点值: %d\n", m1->val);
        printf("环长度:   %d\n", cycleLength(m1));     /* 3 */
    }
    Node *e1 = detectCycleEntry(c1);
    printf("环入口值: %d\n", e1 ? e1->val : -1);       /* 2 */
    freeCyclic(c1, e1);

    /* 用例2：无环 */
    printf("\n=== 无环链表 ===\n");
    Node *c2 = buildCyclic(a, 4, -1);
    printf("有环? %d\n", hasCycle(c2, NULL));          /* 0 */
    printf("入口? %p\n", (void *)detectCycleEntry(c2));/* (nil) */
    freeList(c2);

    /* 用例3：边界——空表、单节点、单节点自环、两节点环 */
    printf("\n=== 边界 ===\n");
    printf("空表: hasCycle=%d\n", hasCycle(NULL, NULL));

    Node *s = newNode(1);
    printf("单节点无环: %d\n", hasCycle(s, NULL));     /* 0 */
    s->next = s;                                       /* 自环 */
    printf("单节点自环: %d\n", hasCycle(s, &m1));      /* 1 */
    printf("  入口=%d, 环长=%d\n",
           detectCycleEntry(s)->val, cycleLength(m1)); /* 1, 1 */
    s->next = NULL; free(s);

    //Node *two = buildList((int[]){7, 8}, 2);
    int b[] = {7, 8};
    Node *two = buildList(b, 2);
    two->next->next = two;                             /* 8->7 成环 */
    printf("两节点环: 入口=%d, 环长=%d\n",
           detectCycleEntry(two)->val,                  /* 7 */
           cycleLength(NULL) + 0 + (hasCycle(two,&m1)?cycleLength(m1):0));
    freeCyclic(two, detectCycleEntry(two));

    return 0;
}
