// LeetCode-876: https://leetcode.com/problems/middle-of-the-linked-list/
// elementary (dumb) problen; dont even bother to check

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
    ListNode* middleNode(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* slowPtr = head;
        ListNode* fastPtr = head;
        while ((fastPtr != nullptr) && (fastPtr->next != nullptr)) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
        }

        return slowPtr;
    }
};
