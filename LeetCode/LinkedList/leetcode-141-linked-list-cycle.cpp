// LeetCode-141: https://leetcode.com/problems/linked-list-cycle/

#include <cstdio>
#include <iostream>

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
   public:
    bool hasCycle(ListNode* head) {
        if ((head == nullptr) || (head->next == nullptr)) {
            return false;
        }

        ListNode* slowPtr = head;
        ListNode* fastPtr = head;

        do {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;

            if (slowPtr == fastPtr) {
                return true;
            }
        } while ((fastPtr != nullptr) && (fastPtr->next != nullptr));

        return false;
    }
};
