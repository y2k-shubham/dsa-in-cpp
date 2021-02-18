// LeetCode-206: https://leetcode.com/problems/reverse-linked-list/

#include <cstdio>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) {
            // empty list case
            return NULL;
        } else if (head->next == nullptr) {
            // reached end of list; this is our new-head
            return head;
        } else {
            // persist next node for wiring
            ListNode* nextNode = head->next;

            // persist new head for returning
            ListNode* newHead = reverseList(nextNode);

            // wire nodes for reversal
            nextNode->next = head;
            // (dont forget this)
            head->next = NULL;

            return newHead;
        }
    }
};
