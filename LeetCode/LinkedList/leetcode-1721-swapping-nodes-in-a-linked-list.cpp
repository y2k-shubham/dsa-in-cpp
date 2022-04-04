// LeetCode-1721: https://leetcode.com/problems/swapping-nodes-in-a-linked-list/

#include <cstdio>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    ListNode *getKthNodeFromBegin(ListNode *head, int k) {
        ListNode *list = head;
        for (int i = 1; i < k; i++) {
            list = list->next;
        }

        return list;
    }

    ListNode *getKthNodeFromEnd(ListNode *head, ListNode *kthNodeFromBegin) {
        ListNode *list = head;

        while (kthNodeFromBegin->next != nullptr) {
            kthNodeFromBegin = kthNodeFromBegin->next;
            list = list->next;
        }

        return list;
    }

    void swapVals(ListNode *node1, ListNode *node2) {
        int tmp = node1->val;
        node1->val = node2->val;
        node2->val = tmp;
    }

public:
    ListNode *swapNodes(ListNode *head, int k) {
        ListNode *kthNodeFromBegin = getKthNodeFromBegin(head, k);
        ListNode *kthNodeFromEnd = getKthNodeFromEnd(head, kthNodeFromBegin);

        swapVals(kthNodeFromBegin, kthNodeFromEnd);

        return head;
    }
};
