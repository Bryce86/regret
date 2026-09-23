#include <iostream>
#include <unordered_map>

struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    int size;
    Node* head;  // 虚拟头节点
    Node* tail;  // 虚拟尾节点
    std::unordered_map<int, Node*> map;  // key → 节点指针

    // 把节点添加到尾部（标记为最近使用）
    void addToTail(Node* node) {
        node->prev = tail->prev;
        node->next = tail;
        tail->prev->next = node;
        tail->prev = node;
    }

    // 从链表中摘除一个节点（不释放内存）
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 把节点移到尾部（先摘除，再加到尾部）
    void moveToTail(Node* node) {
        removeNode(node);
        addToTail(node);
    }

    // 删除头部节点（最久未使用），返回被删除的节点指针
    Node* removeHead() {
        Node* first = head->next;  // 真正的第一个节点
        removeNode(first);
        return first;
    }

public:
    LRUCache(int cap) : capacity(cap), size(0) {
        // 初始化虚拟头尾节点
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head->next = tail;
        tail->prev = head;
    }

    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }

    int get(int key) {
        auto it = map.find(key);
        if (it == map.end()) return -1;  // 不存在

        Node* node = it->second;
        moveToTail(node);  // 标记为最近使用，O(1)
        return node->value;
    }

    void put(int key, int value) {
        auto it = map.find(key);

        if (it != map.end()) {
            // key 已存在：更新值，移到尾部
            Node* node = it->second;
            node->value = value;
            moveToTail(node);  // O(1)
        } else {
            // key 不存在：新建节点
            Node* newNode = new Node(key, value);
            map[key] = newNode;
            addToTail(newNode);  // O(1)
            size++;

            // 超容量，淘汰头部
            if (size > capacity) {
                Node* removed = removeHead();  // O(1)
                map.erase(removed->key);       // O(1)
                delete removed;
                size--;
            }
        }
    }

    void print() {
        std::cout << "缓存（头→尾 = 最久→最近）: ";
        Node* curr = head->next;
        while (curr != tail) {
            std::cout << "[" << curr->key << ":" << curr->value << "] ";
            curr = curr->next;
        }
        std::cout << std::endl;
    }
};


int main() {
    LRUCache cache(3);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.print();  // [1:10] [2:20] [3:30]

    cache.get(1);   // 访问 key=1，移到尾部
    cache.print();  // [2:20] [3:30] [1:10]

    cache.put(4, 40);  // 满了，淘汰头部 key=2
    cache.print();  // [3:30] [1:10] [4:40]

    std::cout << "get(2) = " << cache.get(2) << std::endl;  // -1

    cache.put(3, 300);  // key=3 已存在，更新值并移到尾部
    cache.print();  // [1:10] [4:40] [3:300]

    return 0;
}

