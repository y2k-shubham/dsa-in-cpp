// LeetCode-146: https://leetcode.com/problems/lru-cache/
// incomplete

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <unordered_map>
#include <cassert>

using namespace std;

struct Node {
    int val;
    Node* prev;
    Node* next;

    Node() : val(0), next(nullptr) {}

    Node(int x) : val(x), next(nullptr) {}

    Node(int x, Node* next) : val(x), next(next) {}
};

class LRUCache {
private:
    bool debug = false;
    int capacity;
    Node* dllHead;
    Node* dllTail;
    unordered_map<int, int> kvMap;
    unordered_map<int, Node*> mMap;

    Node* createNode(int val) {
        Node* newNode = new Node;
        newNode->val = val;
        newNode->prev = nullptr;
        newNode->next = nullptr;
        return newNode;
    }

    Node* extractNode(int val) {
        if (mMap.find(val) == mMap.end()) {
            Node* newNode = createNode(val);
            mMap[val] = newNode;
            return newNode;
        }

        Node* node = mMap[val];
        if (node->prev != nullptr) {
            node->prev->next = node->next;
        }
        if (node->next != nullptr) {
            node->next->prev = node->prev;
        }
        node->prev = nullptr;
        node->next = nullptr;

        return node;
    }

    void updateHead(Node* node) {
        if (dllHead == nullptr) {
            dllHead = node;
            dllTail = node;
        } else {
            node->next = dllHead;
            dllHead->prev = node;
            dllHead = node;
        }
    }

    Node* removeTail() {
        if (dllTail == nullptr) {
            return nullptr;
        }

        Node* node = dllTail;
        mMap.erase(node->val);
        kvMap.erase(node->val);

        if (dllTail->prev != nullptr) {
            dllTail->prev->next = nullptr;
            dllTail = dllTail->prev;
        } else {
            dllHead = nullptr;
            dllTail = nullptr;
        }

        return node;
    }

    void showKVMap() {
        printf("kvMap is:-\n");
        for (auto it = kvMap.begin(); it != kvMap.end(); it++) {
            printf("%d -> %d\n", it->first, it->second);
        }
    }

    void showMMap() {
        printf("mMap is:-\n");
        for (auto it = mMap.begin(); it != mMap.end(); it++) {
            printf("%d -> [ * %d * ]\n", it->first, it->second->val);
        }
    }

public:
    friend class LRUCacheTest;

    LRUCache(int capacity) {
        this->capacity = capacity;
        dllTail = dllHead = nullptr;
    }

    int get(int key) {
        if (kvMap.find(key) == kvMap.end()) {
            return -1;
        }

        Node* node = extractNode(key);
        updateHead(node);

        if (debug) {
            printf("after get(key=%d)\n", key);
            showKVMap();
            showMMap();
        }

        return kvMap[key];
    }

    void put(int key, int value) {
        if (((int) kvMap.size()) >= capacity) {
            removeTail();
        }

        this->kvMap[key] = value;

        Node* node;
        if (kvMap.find(key) != kvMap.end()) {
            node = extractNode(key);
        } else {
            node = createNode(key);
        }

        updateHead(node);

        if (debug) {
            printf("after put(key=%d, value=%d)\n", key, value);
            showKVMap();
            showMMap();
        }
    }
};

class LRUCacheTest {
public:
    void test() {
        LRUCache cache(2);

        cache.put(1, 1);
        cache.put(2, 2);
        assert(cache.get(1) == 1);
        assert(cache.get(2) == 2);

//        cache.debug = true;
        cache.put(3, 3);
//        cout << cache.get(2) << endl;
        assert(cache.get(2) == 2);
        assert(cache.get(1) == -1);

        cache.put(4, 4);
        assert(cache.get(1) == -1);
        assert(cache.get(3) == 3);
        assert(cache.get(4) == 4);
    }
};

int main() {
    LRUCacheTest test = LRUCacheTest();

    test.test();

    return 0;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
