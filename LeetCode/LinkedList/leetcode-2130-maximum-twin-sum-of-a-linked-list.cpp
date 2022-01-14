// LeetCode-2130: https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list/

#include <cstdio>
#include <iostream>
#include <stack>

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
    ListNode* findMidNode(ListNode* head) {
        ListNode* slowPtr = head;
        ListNode* fastPtr = head;

        while (fastPtr != nullptr) {
            slowPtr = slowPtr->next;
            fastPtr = fastPtr->next->next;
        }

        return slowPtr;
    }

    stack<int> pushListToStack(ListNode* head) {
        stack<int> stk;

        for (ListNode* list = head; list != nullptr; list = list->next) {
            stk.push(list->val);
        }

        return stk;
    }

    int findMaxTwinSum(ListNode* head, stack<int>& stk) {
        int maxTwinSum = -1;

        ListNode* list = head;
        while (!stk.empty()) {
            int crrTwinSum = stk.top() + list->val;
            maxTwinSum = max(maxTwinSum, crrTwinSum);

            stk.pop();
            list = list->next;
        }

        return maxTwinSum;
    }

   public:
    int pairSum(ListNode* head) {
        ListNode* midNode = findMidNode(head);
        stack<int> stk = pushListToStack(midNode);
        return findMaxTwinSum(head, stk);
    }
};
