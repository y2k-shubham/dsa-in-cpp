// LeetCode-142: https://leetcode.com/problems/linked-list-cycle-ii/
// impossible to solve without knowing the solution
// Sai Anish Malla: https://www.youtube.com/watch?v=UmudS7EXz6o

#include <cstdio>

struct ListNode {
    int val;
    ListNode* next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
private:
    ListNode* findConvergencePoint(ListNode* head) {
        ListNode* slowPtr = head;
        ListNode* fastPtr = head;

        do {
            if ((fastPtr->next == nullptr) || (fastPtr->next->next == nullptr)) {
                return nullptr;
            }

            fastPtr = fastPtr->next->next;
            slowPtr = slowPtr->next;
        } while (slowPtr != fastPtr);

        return slowPtr;
    }

    ListNode* findMeetingPoint(ListNode* node1, ListNode* node2) {
        while (node1 != node2) {
            node1 = node1->next;
            node2 = node2->next;
        }

        return node1;
    }

public:
    ListNode* detectCycle(ListNode* head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode* convergencePoint = findConvergencePoint(head);
        if (convergencePoint == nullptr) {
            return nullptr;
        }

        if (convergencePoint == head) {
            return head;
        } else {
            return findMeetingPoint(head, convergencePoint);
        }
    }
};
