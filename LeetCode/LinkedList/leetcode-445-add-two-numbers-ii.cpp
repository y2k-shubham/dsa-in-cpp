// LeetCode-445: https://leetcode.com/problems/add-two-numbers-ii/
// done using stack -> unnecessarily complex / bulky & also takes more memory (stack)
// LC-submission: speed 56% tile

#include <cstdio>
#include <iostream>
#include <stack>
#include <utility>

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
    ListNode* createNode(int val) {
        ListNode* newNode = new ListNode;
        newNode->val = val;
        newNode->next = nullptr;
        return newNode;
    }

    int findLen(ListNode* head) {
        int numNodes = 0;

        ListNode* list = head;
        while (list != nullptr) {
            list = list->next;
            numNodes++;
        }

        return numNodes;
    }

    pair<pair<ListNode*, int>, pair<ListNode*, int> > getLenSegregatedLists(ListNode* head1, ListNode* head2) {
        int len1 = findLen(head1);
        int len2 = findLen(head2);

        int lenLong = max(len1, len2);
        int lenShort = min(len1, len2);
        ListNode* listShort = (len1 <= len2) ? head1 : head2;
        ListNode* listLong = (len1 > len2) ? head1 : head2;

        return {{listShort, lenShort}, {listLong, lenLong}};
    }

    stack<pair<ListNode*, ListNode*> > convertToStack(
        ListNode* listShortHead,
        int listShortLen,
        ListNode* listLongHead,
        int listLongLen) {
        int lenDiff = listLongLen - listShortLen;
        stack<pair<ListNode*, ListNode*> > stk;

        // push all extra digits of long list into stack
        ListNode* listLong = listLongHead;
        for (int i = 1; i <= lenDiff; i++) {
            stk.push({nullptr, listLong});
            listLong = listLong->next;
        }

        // push all (remaining) matching digits of both lists into stack
        ListNode* listShort = listShortHead;
        for (int i = 1; i <= listShortLen; i++) {
            stk.push({listShort, listLong});

            listLong = listLong->next;
            listShort = listShort->next;
        }

        return stk;
    }

    ListNode* buildSumList(stack<pair<ListNode*, ListNode*> >& stk) {
        ListNode* sumListHead = nullptr;
        int carry = 0;

        while (!stk.empty()) {
            ListNode* node1 = stk.top().first;
            ListNode* node2 = stk.top().second;
            stk.pop();

            int dig1 = (node1 == nullptr) ? 0 : node1->val;
            int dig2 = (node2 == nullptr) ? 0 : node2->val;

            int sum = dig1 + dig2 + carry;

            int dig = sum % 10;
            carry = sum / 10;

            ListNode* newNode = createNode(dig);

            newNode->next = sumListHead;
            sumListHead = newNode;
        }

        while (carry > 0) {
            int sum = carry;

            int dig = sum % 10;
            carry = sum / 10;

            ListNode* newNode = createNode(dig);

            newNode->next = sumListHead;
            sumListHead = newNode;
        }

        return sumListHead;
    }

   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        pair<pair<ListNode*, int>, pair<ListNode*, int> > segregatedLists = getLenSegregatedLists(l1, l2);

        ListNode* listShort = segregatedLists.first.first;
        int listShortLen = segregatedLists.first.second;
        ListNode* listLong = segregatedLists.second.first;
        int listLongLen = segregatedLists.second.second;

        stack<pair<ListNode*, ListNode*> > stk = convertToStack(
            listShort,
            listShortLen,
            listLong,
            listLongLen);

        ListNode* sumList = buildSumList(stk);
        return sumList;
    }
};
