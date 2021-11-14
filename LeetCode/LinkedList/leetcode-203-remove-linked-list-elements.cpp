// LeetCode-203: https://leetcode.com/problems/remove-linked-list-elements/
// pretty easy question; can skip

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
    ListNode* removeElements(ListNode* head, int val) {
        if (head == nullptr) {
            return nullptr;
        }

        while ((head != nullptr) && (head->val == val)) {
            head = head->next;
        }

        if (head == nullptr) {
            return nullptr;
        }

        ListNode* list = head;
        while (list->next != nullptr) {
            if (list->next->val == val) {
                list->next = list->next->next;
            } else {
                list = list->next;
            }
        }

        return head;
    }
};
