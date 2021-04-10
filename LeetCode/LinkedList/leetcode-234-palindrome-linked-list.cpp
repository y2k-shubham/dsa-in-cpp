// LeetCode-234: https://leetcode.com/problems/palindrome-linked-list/
// LC April 2021 challenge: https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/593/week-1-april-1st-april-7th/3693/

#include <cstdio>
#include <cstdlib>
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
   private:
    int findLen(ListNode* head) {
        if (head == nullptr) {
            return 0;
        } else {
            return 1 + findLen(head->next);
        }
    }

    ListNode* splitList(ListNode* head, int splitLen) {
        ListNode* list = head;
        int i = 1;

        while (i < splitLen) {
            list = list->next;
            i++;
        }

        ListNode* splitHead = list->next;
        list->next = NULL;

        return splitHead;
    }

    ListNode* revList(ListNode* head) {
        if (head == nullptr) {
            return NULL;
        } else if (head->next == nullptr) {
            return head;
        } else {
            // create copy of next node
            ListNode* nextNode = head->next;

            // reverse the remaining list
            // (and retrieve the head of reversed list)
            ListNode* revHead = revList(head->next);

            nextNode->next = head;
            head->next = NULL;

            return revHead;
        }
    }

    bool areEqual(ListNode* head1, ListNode* head2) {
        ListNode* list1 = head1;
        ListNode* list2 = head2;

        while (list1 != nullptr && list2 != nullptr) {
            if (list1->val != list2->val) {
                return false;
            }

            list1 = list1->next;
            list2 = list2->next;
        }

        if (list1 != nullptr || list2 != nullptr) {
            return false;
        }

        return true;
    }

   public:
    bool isPalindrome(ListNode* head) {
        int len = findLen(head);
        if (len <= 1) {
            return true;
        }

        ListNode* splitHead = splitList(head, len / 2);
        if ((len % 2) == 1) {
            splitHead = splitHead->next;
        }

        ListNode* revSplitHead = revList(splitHead);
        return areEqual(head, revSplitHead);
    }
};
