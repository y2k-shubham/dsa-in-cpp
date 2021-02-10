// LeetCode-138: https://leetcode.com/problems/copy-list-with-random-pointer/
// Feb 2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/585/week-2-february-8th-february-14th/3635/

// running into SEGFAULT (AddressSanitizer ..)

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
   public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
   public:
    Node* convertToLinkedList(vector<int> vec) {
        Node* head = NULL;
        Node* list = NULL;

        for (int i = 0; i < vec.size(); i++) {
            Node* newNode = new Node(vec[i]);
            if (head == NULL) {
                head = list = newNode;
            } else {
                list->next = newNode;
                list = newNode;
            }
        }

        return head;
    }

    unordered_map<int, Node*> preparePosnNodeMap(Node* head) {
        unordered_map<int, Node*> posnNodeMap;

        int posn = 1;
        for (Node* list = head; list != nullptr; list = list->next) {
            posnNodeMap[posn] = list;
            posn++;
        }

        return posnNodeMap;
    }

    void showPosnNodeMap(unordered_map<int, Node*> posnNodeMap) {
        printf("\nPosnNodeMap is:-\n");
        for (unordered_map<int, Node*>::iterator it = posnNodeMap.begin(); it != posnNodeMap.end(); it++) {
            printf("[%d] -> %d\n", (*it).first, (*it).second->val);
        }
    }

    unordered_map<Node*, int> prepareNodePosnMap(Node* head) {
        unordered_map<Node*, int> nodePosnMap;

        int posn = 1;
        for (Node* list = head; list != nullptr; list = list->next) {
            nodePosnMap[list] = posn;
            posn++;
        }

        return nodePosnMap;
    }

    void showNodePosnMap(unordered_map<Node*, int> nodePosnMap) {
        printf("\nNodePosnMap is:-\n");
        for (unordered_map<Node*, int>::iterator it = nodePosnMap.begin(); it != nodePosnMap.end(); it++) {
            printf("%d <- [%d]\n", (*it).first->val, (*it).second);
        }
    }

    Node* duplicateNode(Node* orgNode) {
        Node* copyNode = new Node(orgNode->val);
        return copyNode;
    }

    Node* copyListWithoutRandomPtrs(Node* orgHead) {
        Node* copyHead;
        Node* copyList;

        for (Node* orgList = orgHead; orgList != nullptr; orgList = orgList->next) {
            if (copyHead == nullptr) {
                copyHead = copyList = duplicateNode(orgList);
            } else {
                Node* copyNode = duplicateNode(orgList);
                copyList->next = copyNode;
                copyList = copyNode;
            }
        }

        return copyHead;
    }

    void copyRandomPtrs(Node* orgHead, Node* copyHead) {
        unordered_map<Node*, int> orgNodePosnMap = prepareNodePosnMap(orgHead);
        showNodePosnMap(orgNodePosnMap);
        unordered_map<int, Node*> copyPosnNodeMap = preparePosnNodeMap(copyHead);
        showPosnNodeMap(copyPosnNodeMap);

        Node* orgList = orgHead;
        Node* copyList = copyHead;
        while (orgList != nullptr) {
            if (orgList->random != nullptr) {
                int orgRandomPosn = orgNodePosnMap[orgList->random];
                copyList->random = copyPosnNodeMap[orgRandomPosn];
            }

            orgList = orgList->next;
            copyList = copyList->next;
        }
    }

    Node* copyRandomList(Node* orgHead) {
        if (orgHead == nullptr) {
            return NULL;
        }

        Node* copyHead = copyListWithoutRandomPtrs(orgHead);
        copyRandomPtrs(orgHead, copyHead);

        return copyHead;
    }
};

int main() {
    Solution soln = *(new Solution());

    Node* head = soln.convertToLinkedList({8, 1, 3, 7});
    soln.showPosnNodeMap(soln.preparePosnNodeMap(head));
    soln.showNodePosnMap(soln.prepareNodePosnMap(head));

    return 0;
}
