// LeetCode-432: https://leetcode.com/problems/all-oone-data-structure/

/**
 * ["AllOne","inc","inc","getMaxKey","getMinKey","inc","getMaxKey","getMinKey"]
 * [[],["hello"],["hello"],[],[],["leet"],[],[]]
 * 
 * ["AllOne","inc","inc","inc","inc","inc","dec","dec","getMaxKey","getMinKey"]
 * [[],["a"],["b"],["b"],["b"],["b"],["b"],["b"],[],[]]
 * 
 * ["AllOne","inc","inc","inc","inc","inc","inc","dec", "dec","getMinKey","dec","getMaxKey","getMinKey"]
 * [[],["a"],["b"],["b"],["c"],["c"],["c"],["b"],["b"],[],["a"],[],[]]
 */

#include <cstdio>
#include <iostream>
#include <unordered_map>

using namespace std;

struct Node {
    string key;
    int count;
    Node* next;
    Node* prev;
};

// stellar performance (98 %tile), even though it is the straightforward DLL + map approach
class AllOne {
   private:
    Node* head;
    Node* tail;
    unordered_map<string, Node*> keyNodeMap;

    Node* createNode(string key) {
        Node* newNode = new Node;

        newNode->prev = nullptr;
        newNode->next = nullptr;

        newNode->key = key;
        newNode->count = 1;

        return newNode;
    }

    void swapNodes(Node* node1, Node* node2) {
        string tmpKey = node1->key;
        int tmpCount = node1->count;

        node1->key = node2->key;
        node1->count = node2->count;
        this->keyNodeMap[node2->key] = node1;

        node2->key = tmpKey;
        node2->count = tmpCount;
        this->keyNodeMap[tmpKey] = node2;
    }

    void moveLeft(Node* node) {
        Node* prevNode = node->prev;

        while ((prevNode != nullptr) && (prevNode->count < node->count)) {
            swapNodes(prevNode, node);

            node = prevNode;
            prevNode = node->prev;
        }

        if (prevNode == nullptr) {
            this->head = node;
        }
    }

    void moveRight(Node* node) {
        Node* nextNode = node->next;

        while ((nextNode != nullptr) && (node->count < nextNode->count)) {
            swapNodes(node, nextNode);

            node = nextNode;
            nextNode = node->next;
        }

        if (nextNode == nullptr) {
            this->tail = node;
        }
    }

    void deleteNode(Node* node) {
        Node* prevNode = node->prev;
        Node* nextNode = node->next;

        if (prevNode == nullptr && nextNode == nullptr) {
            this->head = nullptr;
            this->tail = nullptr;
        } else if (prevNode == nullptr) {
            this->head = node->next;
            this->head->prev = nullptr;
        } else if (nextNode == nullptr) {
            this->tail = node->prev;
            this->tail->next = nullptr;
        } else {
            node->prev->next = node->next;
            node->next->prev = node->prev;
        }

        // this had to be commented out because it gives address-sanitizer error on LC
        // free(node);
    }

   public:
    AllOne() {
        this->head = nullptr;
        this->tail = nullptr;
    }

    void inc(string key) {
        if (this->keyNodeMap.find(key) == this->keyNodeMap.end()) {
            Node* newNode = createNode(key);

            if (this->head == nullptr) {
                this->head = newNode;
            } else {
                this->tail->next = newNode;
                newNode->prev = this->tail;
            }
            this->tail = newNode;

            this->keyNodeMap[key] = newNode;
        } else {
            Node* node = this->keyNodeMap[key];
            node->count++;
            this->moveLeft(node);
        }
    }

    void dec(string key) {
        Node* node = this->keyNodeMap[key];
        node->count--;

        if (node->count == 0) {
            this->deleteNode(node);
            this->keyNodeMap.erase(key);
        } else {
            this->moveRight(node);
        }
    }

    string getMaxKey() {
        if (this->head == nullptr) {
            return "";
        } else {
            return this->head->key;
        }
    }

    string getMinKey() {
        if (this->tail == nullptr) {
            return "";
        } else {
            return this->tail->key;
        }
    }
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
