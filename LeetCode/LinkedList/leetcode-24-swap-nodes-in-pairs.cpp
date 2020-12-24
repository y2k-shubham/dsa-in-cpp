// LeetCode-24: https://leetcode.com/problems/swap-nodes-in-pairs/
// Contest: https://leetcode.com/explore/challenge/card/december-leetcoding-challenge/572/week-4-december-22nd-december-28th/3579/

#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
   public:
    //recursive
    ListNode* swapPairsRec(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        } else {
            ListNode* crrNode = head;
            ListNode* nextNode = head->next;

            ListNode* partResult = swapPairsRec(nextNode->next);

            nextNode->next = crrNode;
            crrNode->next = partResult;

            return nextNode;
        }
    }

    // caller
    ListNode* swapPairs(ListNode* head) {
        return swapPairsRec(head);
    }

    // iterative
    ListNode* swapPairs2(ListNode* head) {
        if (head == NULL || head->next == NULL) {
            return head;
        } else {
            for (ListNode* list = head; list != NULL && list->next != NULL; list = list->next->next) {
                int tmp = list->val;
                list->val = list->next->val;
                list->next->val = tmp;
            }
            return head;
        }
    }
};
