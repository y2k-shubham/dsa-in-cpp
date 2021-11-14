// LeetCode-237: https://leetcode.com/problems/delete-node-in-a-linked-list/

#include <cstdio>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
   public:
    void deleteNode(ListNode* node) {
        ListNode* prevNode = nullptr;
        while (node->next != nullptr) {
            node->val = node->next->val;

            prevNode = node;
            node = node->next;
        }

        prevNode->next = nullptr;
    }
};
