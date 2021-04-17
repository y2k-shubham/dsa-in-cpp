// LeetCode-86: https://leetcode.com/problems/partition-list/
// LC April 2021 challenge: https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/594/week-2-april-8th-april-14th/3707/

#include <climits>
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
   private:
    pair<ListNode*, ListNode*> addNode(pair<ListNode*, ListNode*> headList, ListNode* newNode) {
        ListNode* head = headList.first;
        ListNode* list = headList.second;

        if (head == nullptr) {
            return {newNode, newNode};
        } else {
            list->next = newNode;
            return {head, newNode};
        }
    }

    ListNode* createNode(int val) {
        ListNode* newNode = new ListNode;
        newNode->val = val;
        newNode->next = NULL;
        return newNode;
    }

   public:
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr) {
            return NULL;
        }

        pair<ListNode*, ListNode*> smallHeadList = {NULL, NULL};
        pair<ListNode*, ListNode*> bigHeadList = {NULL, NULL};

        for (ListNode* myList = head; myList != nullptr; myList = myList->next) {
            if (myList->val < x) {
                smallHeadList = addNode(smallHeadList, myList);
            } else {
                bigHeadList = addNode(bigHeadList, myList);
            }
        }

        if ((smallHeadList.first == nullptr) || (bigHeadList.first == nullptr)) {
            return head;
        } else {
            smallHeadList.second->next = bigHeadList.first;
            bigHeadList.second->next = NULL;
            return smallHeadList.first;
        }
    }
};
