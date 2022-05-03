// LeetCode-160: https://leetcode.com/problems/intersection-of-two-linked-lists/

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    int findLen(ListNode* head) {
        int len = 0;

        for (ListNode* list = head; list != nullptr; list = list->next) {
            len++;
        }

        return len;
    }

    ListNode* getNthNode(ListNode* head, int n) {
        if (n <= 1) {
            return head;
        }

        ListNode* list;
        for (
                list = head;
                (list != nullptr) && (n > 1);
                n--, (list = list->next)
                );

        return list;
    }

    ListNode* findIntersectingNode(ListNode* headA, ListNode* headB) {
        ListNode* listA = headA;
        ListNode* listB = headB;

        while ((listA != nullptr) && (listB != nullptr)) {
            if (listA == listB) {
                return listA;
            }

            listA = listA->next;
            listB = listB->next;
        }

        return nullptr;
    }

public:
    ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
        int lenA = findLen(headA);
        int lenB = findLen(headB);
        if (min(lenA, lenB) == 0) {
            return nullptr;
        }

        ListNode* headLong;
        ListNode* headShort;
        int lenLong, lenShort;
        if (lenA >= lenB) {
            lenLong = lenA;
            headLong = headA;

            lenShort = lenB;
            headShort = headB;
        } else {
            lenLong = lenB;
            headLong = headB;

            lenShort = lenA;
            headShort = headA;
        }

        int lenDiff = lenLong - lenShort;
        ListNode* headLongShifted = getNthNode(headLong, lenDiff + 1);

        return findIntersectingNode(headLongShifted, headShort);
    }
};
