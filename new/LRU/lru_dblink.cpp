#include <iostream>
#include <unordered_map>
using namespace std;

// 双向链表结点
struct Node {
    int key;
    int value;
    Node* prev;
    Node* next;
    Node(int k, int v) :
        key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache
{
private:

    int capacity;
    int size;
    Node* head;  // 虚拟头节点 （哨兵）
    Node* tail;  // 虚拟尾节点 （哨兵）
    std::unordered_map<int, Node*> cache; // 哈希表：key -> 节点指针

    // 将节点移动到链表头部（表示最近使用）
    void moveToHead(Node* node) {
        removeNode(node);
        addToHead(node);
    }

    // 从链表中移除节点
    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // 将节点添加到链表头部（head 之后）
    void addToHead(Node* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    // 移除链表尾部节点（tail 之前），并返回其 key
    Node* removeTail() {
        Node* node = tail->prev;
        removeNode(node);
        return node;
    }

public:

    // 构造函数：初始化哨兵节点
    LRUCache(int cap) : capacity(cap), size(0) {
        head = new Node(0, 0); // 虚拟头
        tail = new Node(0, 0); // 虚拟尾
        head->next = tail;
        tail->prev = head;
    }

    // 析构函数：释放所有节点内存
    ~LRUCache() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    // get 操作：O(1)
    int get(int key) {
        if (cache.find(key) == cache.end()) {
            return -1; // key 不存在
        }
        Node* node = cache[key];
        moveToHead(node); // 标记为最近使用
        return node->value;
    }

    // put 操作：O(1)
    void put(int key, int value) {
        if (cache.find(key) != cache.end()) {
            // key 已存在，更新值并移到头部
            Node* node = cache[key];
            node->value = value;
            moveToHead(node);
        } else {
            // key 不存在，创建新节点
            Node* newNode = new Node(key, value);
            cache[key] = newNode;
            addToHead(newNode);
            size++;

            if (size > capacity) {
                // 容量满了，淘汰尾部最久未使用的节点
                Node* tailNode = removeTail();
                cache.erase(tailNode->key);
                delete tailNode;
                size--;
            }
        }
    }

    // 打印当前缓存状态（从头部到尾部，用于调试）
    void printCache() const {
        Node* curr = head->next;
        cout << "Cache (head->tail = 最近->最久): ";
        while (curr != tail) {
            cout << "[" << curr->key << ":" << curr->value << "]";
            if (curr->next != tail) cout << " <-> ";
            curr = curr->next;
        }
        cout << endl;
    }
};

int main() {

    LRUCache cache(3); // 容量为 3

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.printCache(); // [1:10] <-> [2:20] <-> [3:30]

    cout << "get(2): " << cache.get(2) << endl; // 输出 20，节点2移到头部
    cache.printCache(); // [2:20] <-> [1:10] <-> [3:30]

    cache.put(4, 40); // 容量满，淘汰最旧的节点3
    cache.printCache(); // [4:40] <-> [2:20] <-> [1:10]

    cout << "get(3): " << cache.get(3) << endl; // 输出 -1，节点3已被淘汰
    cout << "get(1): " << cache.get(1) << endl; // 输出 10，节点1移到头部
    cache.printCache(); // [1:10] <-> [4:40] <-> [2:20]

    return 0;
}

