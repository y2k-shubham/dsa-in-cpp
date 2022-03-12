// LeetCode-138: https://leetcode.com/problems/copy-list-with-random-pointer/
// GFG O(1) space: https://www.geeksforgeeks.org/clone-linked-list-next-random-pointer-o1-space/

#include <cstdio>
#include <iostream>

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
   private:
    void showList(Node* head, const char* msg) {
        printf("\n%s\n", msg);
        for (Node* list = head; list != nullptr; list = list->next) {
            if (list->random == nullptr) {
                printf("%d\n", list->val);
            } else {
                printf("%d ::> %d\n", list->val, list->random->val);
            }
        }
    }

    Node* createNode(int val) {
        Node* newNode = new Node(val);

        newNode->val = val;
        newNode->next = nullptr;
        newNode->random = nullptr;

        return newNode;
    }

    void insertCopyNodes(Node* head) {
        Node* list = head;

        while (list != nullptr) {
            Node* copyNode = createNode(list->val);

            copyNode->next = list->next;
            list->next = copyNode;

            list = copyNode->next;
        }
    }

    void wireRandomPtrsInCopyNodes(Node* head) {
        Node* list = head;

        while (list != nullptr) {
            Node* copyNode = list->next;

            if (list->random != nullptr) {
                copyNode->random = list->random->next;
            }

            list = copyNode->next;
        }
    }

    Node* unzipCopyNodes(Node* head) {
        Node* copyListHead = head->next;
        Node* copyList = copyListHead;

        head->next = head->next->next;
        Node* list = head->next;

        while (list != nullptr) {
            copyList->next = list->next;
            copyList = copyList->next;

            list->next = list->next->next;

            list = list->next;
        }

        copyList->next = nullptr;
        return copyListHead;
    }

   public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) {
            return nullptr;
        }

        insertCopyNodes(head);
        // showList(head, "after insert, original list is");

        wireRandomPtrsInCopyNodes(head);
        // showList(head, "after linking, original list is");

        Node* copyHead = unzipCopyNodes(head);
        // showList(head, "after de-linking, original list is");
        // showList(copyHead, "after de-linking, copy list is");

        return copyHead;
    }
};
