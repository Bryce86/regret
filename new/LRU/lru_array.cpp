#include <iostream>
#include <string>

struct Entry {
    int key;
    int value;
};

class LRUCache {
private:
    Entry* arr;       // 数组
    int capacity;     // 容量
    int size;         // 当前元素个数

    // 在数组中查找 key，返回下标，找不到返回 -1
    int find(int key) {
        for (int i = 0; i < size; i++) {
            if (arr[i].key == key) {
                return i;
            }
        }
        return -1;
    }

    // 把下标 idx 的元素移到尾部
    void moveToTail(int idx) {
        Entry temp = arr[idx];
        // 把 idx 后面的元素全部前移一位
        for (int i = idx; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        arr[size - 1] = temp;
    }

    // 删除头部元素（最久未使用），后面的元素全部前移
    void removeHead() {
        for (int i = 0; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

public:
    LRUCache(int cap) : capacity(cap), size(0) {
        arr = new Entry[capacity];
    }

    ~LRUCache() {
        delete[] arr;
    }

    int get(int key) {
        int idx = find(key);
        if (idx == -1) return -1;  // 没找到

        moveToTail(idx);           // 移到尾部，标记为"最近使用"
        return arr[size - 1].value;
    }

    void put(int key, int value) {
        int idx = find(key);

        if (idx != -1) {
            // key 已存在：更新值，移到尾部
            arr[idx].value = value;
            moveToTail(idx);
        } else {
            // key 不存在
            if (size == capacity) {
                // 满了，淘汰头部（最久未使用）
                removeHead();
            }
            // 插入到尾部
            arr[size].key = key;
            arr[size].value = value;
            size++;
        }
    }

    void print() {
        std::cout << "缓存（头→尾 = 最久→最近）: ";
        for (int i = 0; i < size; i++) {
            std::cout << "[" << arr[i].key << ":" << arr[i].value << "] ";
        }
        std::cout << std::endl;
    }
};

int main() {
    LRUCache cache(3);  // 容量为 3

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.print();  // [1:10] [2:20] [3:30]

    cache.get(1);   // 访问 key=1，移到尾部
    cache.print();  // [2:20] [3:30] [1:10]

    cache.put(4, 40);  // 满了，淘汰头部 key=2
    cache.print();  // [3:30] [1:10] [4:40]

    cache.get(2);   // key=2 已被淘汰
    std::cout << "get(2) = " << cache.get(2) << std::endl;  // -1

    cache.put(3, 300);  // key=3 已存在，更新值并移到尾部
    cache.print();  // [1:10] [4:40] [3:300]

    return 0;
}


