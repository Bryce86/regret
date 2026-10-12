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

/* 造一条带环链表：pos 为尾节点连回的下标(0-based)，-1 表示无环 */
static Node *buildCyclic(const int a[], int n, int pos) {
    Node dummy, *tail = &dummy, *entry = NULL;
    dummy.next = NULL;
    for (int i = 0; i < n; i++) {
        tail->next = newNode(a[i]);
        tail = tail->next;
        if (i == pos) entry = tail;
    }
    if (pos >= 0 && pos < n) tail->next = entry;   /* 成环 */
    return dummy.next;
}

/* 安全释放带环链表：先断环再 free */
static void freeCyclic(Node *head) {
    if (!head) return;
    Node* slow = head;
    Node* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {                        /* 有环：找到环上某点，绕一圈断链 */
            Node *p = slow->next;
            while (p != slow) { Node *t = p->next; p->next = NULL; p = t; }
            slow->next = NULL;
            break;
        }
    }
    while (head) { Node *t = head; head = head->next; free(t); }
}

/* ---------- 2. 主算法：求环的第一个节点（LeetCode 142）----------
 * 返回环入口节点指针；无环或空表返回 NULL。
 */
Node *detectCycleEntry(Node *head) {
    if (!head) return NULL;

    /* ---- 阶段一：找相遇点 ---- */
    Node *slow = head, *fast = head;
    while (fast && fast->next) {                   /* ★ 顺序不可反 */
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) break;                   /* 追上了，必有环 */
    }
    if (!fast || !fast->next) return NULL;         /* fast 走到头 = 无环 */

    /* ---- 阶段二：一个从 head，一个从相遇点，同速出发 ---- */
    Node *p = head;
    while (p != slow) {
        p    = p->next;
        slow = slow->next;
    }
    return p;                                      /* 相遇即入口 */
}

/* ---------- 3. 辅助：顺便求环长度（从相遇点绕一圈）---------- */
int cycleLength(Node *head) {
    Node *meet = NULL;
    Node *s = head, *f = head;
    while (f && f->next) {
        s = s->next; f = f->next->next;
        if (s == f) { meet = s; break; }
    }
    if (!meet) return 0;
    int len = 1;
    for (Node *p = meet->next; p != meet; p = p->next) len++;
    return len;
}

/* ---------- 4. 验证 ---------- */
int main(void) {
    /* 用例1: 3→2→0→-4，尾连回下标1(值2)，入口应为 2 */
    //Node *c1 = buildCyclic((int[]){3, 2, 0, -4}, 4, 1);
    int a1[] = {3,2,0,-4};
    Node *c1 = buildCyclic(a1, 4, 1);
    printf("用例1 入口值: %d (期望 2), 环长: %d\n",
           detectCycleEntry(c1)->val, cycleLength(c1));
    freeCyclic(c1);

    /* 用例2: 无环 */
    //Node *c2 = buildCyclic((int[]){1, 2, 3}, 3, -1);
    int a2[] = {1,2,3};
    Node *c2 = buildCyclic(a2, 3, -1);
    printf("用例2 入口: %s (期望 无)\n",
           detectCycleEntry(c2) ? "非空" : "NULL");
    freeCyclic(c2);

    /* 用例3: 单节点自环 */
    Node *s = newNode(9); s->next = s;
    printf("用例3 入口值: %d, 环长: %d\n",
           detectCycleEntry(s)->val, cycleLength(s));
    freeCyclic(s);

    /* 用例4: 整个链表就是一个环（入口就是 head） */
    //Node *c4 = buildCyclic((int[]){5, 6, 7}, 3, 0);
    int a4[] = {5,6,7};
    Node *c4 = buildCyclic(a4, 3, 0);
    printf("用例4 入口值: %d (期望 5), 环长: %d\n",
           detectCycleEntry(c4)->val, cycleLength(c4));
    freeCyclic(c4);

    /* 用例5: 空表 */
    printf("用例5 入口: %s (期望 NULL)\n",
           detectCycleEntry(NULL) ? "非空" : "NULL");

    return 0;
}

