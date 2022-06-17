// LeetCode-146: https://leetcode.com/problems/lru-cache/
// LC gives TLE on a severe test-case

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

        if (dllHead == node) {
            dllHead = node->next;
        }
        if (dllTail == node) {
            dllTail = node->prev;
        }

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

        if (debug) {
            printf("--------------\n");
            printf("after remove tail\n");
            showDll();
            showDllReverse();
            showKVMap();
            showMMap();
        }

        return node;
    }

    void showDll() {
        printf("DLL is:-\n");

        Node* node = dllHead;
        while (node != nullptr) {
            cout << node->val << " ";
            node = node->next;
        }
        cout << endl;
    }

    void showDllReverse() {
        printf("reverse DLL is:-\n");

        Node* node = dllTail;
        while (node != nullptr) {
            cout << node->val << " ";
            node = node->prev;
        }
        cout << endl;
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
            printf("--------------\n");
            printf("after get(key=%d)\n", key);
            showDll();
            showDllReverse();
            showKVMap();
            showMMap();
        }

        return kvMap[key];
    }

    void put(int key, int value) {
        this->kvMap[key] = value;

        // it is important to check size of map after
        // adding key; because if same key is overwritten
        // then we need not evict cache
        if (((int) kvMap.size()) > capacity) {
            removeTail();
        }

        Node* node;
        if (kvMap.find(key) != kvMap.end()) {
            node = extractNode(key);
        } else {
            node = createNode(key);
        }

        updateHead(node);

        if (debug) {
            printf("--------------\n");
            printf("after put(key=%d, value=%d)\n", key, value);
            showDll();
            showDllReverse();
            showKVMap();
            showMMap();
        }
    }
};

class LRUCacheTest {
public:
    void test1() {
        LRUCache cache(2);

//        cache.debug = true;
        cache.put(1, 1); // [1]
        cache.put(2, 2); // [2, 1]
        assert(cache.get(1) == 1); // [1, 2]
        assert(cache.get(2) == 2); // [2, 1]

        cache.put(3, 3); // [3, 2]
        assert(cache.get(2) == 2); // [2, 3]
        assert(cache.get(1) == -1); // [2, 3]

        cache.put(4, 4); // [4, 2]
        assert(cache.get(1) == -1); // [4, 2]
        assert(cache.get(3) == -1); // [4, 2]
        assert(cache.get(4) == 4); // [4, 2]
        assert(cache.get(2) == 2); // [2, 4]
    }

    void test2() {
        LRUCache cache(2);

//        cache.debug = true;
        cache.put(1, 1); // [1]
        cache.put(2, 2); // [2, 1]
        assert(cache.get(1) == 1); // [1, 2]

        cache.put(3, 3); // [3, 1]
        assert(cache.get(2) == -1); // [3, 1]
        assert(cache.get(1) == 1); // [1, 3]

        cache.put(4, 4); // [4, 1]
        assert(cache.get(1) == 1); // [1, 4]
        assert(cache.get(3) == -1); // [1, 4]
        assert(cache.get(4) == 4); // [4, 1]
        assert(cache.get(2) == -1); // [4, 1]
    }

    void test3() {
        LRUCache cache(2);

//        cache.debug = true;
        assert(cache.get(2) == -1);
        cache.put(2, 6);
        assert(cache.get(1) == -1);
        cache.put(1, 5);
        cache.put(1, 2);
        assert(cache.get(1) == 2);
        assert(cache.get(2) == 6);
    }

    // LC sometimes gives TLE on this test case
    void test4() {
        LRUCache cache(1);

//        cache.debug = true;
        cache.put(1, 1);
        assert(cache.get(6) == -1);
        assert(cache.get(8) == -1);
        cache.put(12, 1);
        assert(cache.get(2) == -1);
        cache.put(15, 11);
        cache.put(5, 2);
        cache.put(1, 15);
        cache.put(4, 2);
        assert(cache.get(5) == -1);
        cache.put(15, 15);
    }


};

int main() {
    LRUCacheTest test = LRUCacheTest();

    test.test1();
    test.test2();
    test.test3();
    test.test4();

    return 0;
}

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
