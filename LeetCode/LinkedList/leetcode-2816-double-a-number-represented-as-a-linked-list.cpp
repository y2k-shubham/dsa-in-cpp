// LeetCode-2816: https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/

#include <utility>

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
private:
    ListNode* createNode(int val) {
        ListNode* newNode = new ListNode;
        newNode->val = val;
        newNode->next = nullptr;
        return newNode;
    }

    pair <int, int> getQuotAndCarry(int val) {
        int quot = val % 10;
        int carry = val / 10;
        return {quot, carry};
    }

    int doubleItRec(ListNode* head) {
        pair <int, int> quotAndCarry;

        if (head == nullptr) {
            return 0;
        } else if (head->next == nullptr) {
            int doubledVal = head->val * 2;
            quotAndCarry = getQuotAndCarry(doubledVal);
        } else {
            int carry = doubleItRec(head->next);
            quotAndCarry = getQuotAndCarry((head->val * 2) + carry);
        }

        head->val = quotAndCarry.first;
        return quotAndCarry.second;
    }

public:
    ListNode* doubleIt(ListNode* head) {
        int carry = doubleItRec(head);
        if (carry > 0) {
            ListNode* newNode = createNode(carry);
            newNode->next = head;
            return newNode;
        }
        return head;
    }
};
