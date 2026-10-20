#include <iostream>
#include <stdexcept>

using namespace std;

// 定义双向链表节点结构
struct Node {
    int data;
    Node* prev;
    Node* next;
    Node(int val) : data(val), prev(nullptr), next(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head; // 头指针
    Node* tail; // 尾指针

    // 构造函数：初始化空链表
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // 析构函数：删除整个链表，释放内存
    ~DoublyLinkedList() {
        deleteList();
    }

    // 1. 创建节点并追加到链表尾部（用于快速构建链表）
    void append(int val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

    }

    // 2.1 遍历链表（正向）
    void traverseForward() const {
        if (!head) {
            cout << "List is empty.\n";
            return;
        }

        Node* curr = head;
        cout << "Forward: ";
        while (curr)
        {
            cout << curr->data;
            if (curr->next)
                cout << " <-> ";
            curr = curr->next;
        }
        cout << "\n";
    }

    // 2.2 反向遍历链表（从尾到头）
    void traverseReverse() const {
        if (!tail) {
            cout << "List is empty.\n";
            return;
        }

        Node* curr = tail; // 从尾节点开始
        cout << "Reverse: ";
        while (curr)
        {
            cout << curr->data;
            if (curr->prev)
                cout << " <-> "; // 如果还有前驱节点，就打印分隔符
            curr = curr->prev;
        }
        cout << "\n";
    }

    // 3. 获取链表长度
    int length() const {
        int count = 0;
        Node* curr = head;
        while (curr)
        {
            count++;
            curr = curr->next;
        }
        return count;
    }

    // 4. 插入节点
    // 在指定位置 index 插入新节点（index 从 0 开始）
    void insertAt(int index, int val)
    {
        int len = length();
        if (index < 0 || index > len) {
            throw std::out_of_range("Index out of range");
        }

        Node* newNode = new Node(val);

        // Case A: 插入到头部
        if (index == 0) {
            if (!head) {
                head = tail = newNode;
            }
            else
            {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
            return;
        }

        // Case B: 插入到尾部
        if (index == len) {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            return;
        }

        // Case C: 插入到中间
        Node* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }

        // 在curr之前插入newNode
        newNode->next = curr;
        newNode->prev = curr->prev;
        curr->prev->next = newNode;
        curr->prev = newNode;
    }

    // 5. 删除节点
    // 删除指定位置 index 的节点（index 从 0 开始）
    void deleteAt(int index) {
        int len = length();
        if (len == 0 || index < 0 || index >= len) {
            throw std::out_of_range("Index out of range or list is empty");
        }

        Node* target = nullptr;

        // Case A: 删除头节点
        if (index == 0)
        {
            target = head;
            if (head == tail) {
                head = tail = nullptr;
            } else {
                head = head->next;
                head->prev = nullptr;
            }
        }

        // Case B: 删除尾节点
        else if (index == len-1)
        {
            target = tail;
            tail = tail->prev;
            tail->next = nullptr;
        }

        // Case C: 删除中间节点
        else
        {
            target = head;
            // 找到要删除节点
            for (int i = 0; i < index; i++) {
                target = target->next;
            }

            target->prev->next = target->next;
            target->next->prev = target->prev;
        }

        delete target;
    }

    // 6. 删除整个链表
    void deleteList() {
        Node* curr = head;
        while (curr)
        {
            Node* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
        head = tail = nullptr;
        cout << "List has been deleted." << endl;
    }
};

int main()
{
    DoublyLinkedList list;

    //1. 创建链表
    cout << "--- Creating list (10, 20, 30) ---\n";

    list.append(10);
    list.append(20);
    list.append(30);
    list.traverseForward();
    list.traverseReverse();
    cout << "Length: " << list.length() << std::endl;

    //2. 插入节点
    cout << "\n--- Inserting 5 at head (index 0) ---\n";
    list.insertAt(0, 5);
    list.traverseForward();

    cout << "\n--- Inserting 25 in middle (index 2) ---\n";
    list.insertAt(2, 25);
    list.traverseForward();

    cout << "\n--- Inserting 35 at tail (index 5) ---\n";
    list.insertAt(5, 35);
    list.traverseForward();
    cout << "Length: " << list.length() << std::endl;


    // 3. 删除节点
    cout << "\n--- Deleting head (index 0) ---\n";
    list.deleteAt(0);
    list.traverseForward();

    cout << "\n--- Deleting tail (index 4) ---\n";
    list.deleteAt(4);
    list.traverseForward();

    cout << "\n--- Deleting middle (index 2) ---\n";
    list.deleteAt(2);
    list.traverseForward();

    // 4. 删除整个链表
    cout << "\n--- Deleting entire list ---\n";
    list.deleteList();
    list.traverseForward(); // Should print "List is empty."

    return 0;
}












