// LeetCode-1019: https://leetcode.com/problems/next-greater-node-in-linked-list/submissions/
// GFG: https://www.geeksforgeeks.org/next-greater-element-in-the-linked-list/

#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

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
    int findLen(ListNode* node) {
        if (node == nullptr) {
            return 0;
        } else {
            return 1 + findLen(node->next);
        }
    }

    void fillNgeRight(ListNode* node, int idx, stack<int>& stk, vector<int>& ngeRight) {
        if (node != nullptr) {
            fillNgeRight(node->next, idx + 1, stk, ngeRight);

            while (!stk.empty() && (stk.top() <= node->val)) {
                stk.pop();
            }
            ngeRight[idx] = stk.empty() ? 0 : stk.top();

            stk.push(node->val);
        }
    }

   public:
    vector<int> nextLargerNodes(ListNode* head) {
        int len = findLen(head);
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {0};
        }

        stack<int> stk;
        vector<int> ngeRight(len);
        fillNgeRight(head, 0, stk, ngeRight);

        return ngeRight;
    }
};
