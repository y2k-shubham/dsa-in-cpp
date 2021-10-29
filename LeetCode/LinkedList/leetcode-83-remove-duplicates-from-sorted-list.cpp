// LeetCode-83: https://leetcode.com/problems/remove-duplicates-from-sorted-list/

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
    ListNode* deleteDuplicates(ListNode* head) {
        if (head == nullptr) {
            return head;
        }

        ListNode* list;
        for (list = head->next; (list != nullptr) && (list->val == head->val); list = list->next) {
            // nothing
        }

        head->next = list;
        deleteDuplicates(list);

        return head;
    }
};
