// LeetCode-61: https://leetcode.com/problems/rotate-list/

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   private:
    ListNode* advanceByNSteps(ListNode* list, int n) {
        for (int i = 1; i <= n; i++) {
            if (list == nullptr) {
                return list;
            }

            list = list->next;
        }

        return list;
    }

    ListNode* findParentOfNthNodeFromEnd(ListNode* list, int n) {
        ListNode* bwdList = list;
        ListNode* fwdList = advanceByNSteps(list, n + 1);
        // printf("after advance by n=%d steps, fwdList=%d\n", n, fwdList->val);

        while (fwdList != nullptr) {
            fwdList = fwdList->next;
            bwdList = bwdList->next;
        }
        // printf("after advance to end, bwdList=%d, fwdList=null\n\n", bwdList->val);

        return bwdList;
    }

    ListNode* findLastNode(ListNode* list) {
        return findParentOfNthNodeFromEnd(list, 0);
    }

    int findNumNodes(ListNode* list) {
        int numNodes = 0;

        for (ListNode* iter = list; iter != nullptr; iter = iter->next) {
            numNodes++;
        }

        return numNodes;
    }

   public:
    ListNode* rotateRight(ListNode* head, int k) {
        int numNodes = findNumNodes(head);
        if (numNodes <= 1) {
            return head;
        }

        k = k % numNodes;
        if (k == 0) {
            return head;
        }

        ListNode* newLastNode = findParentOfNthNodeFromEnd(head, k);
        ListNode* newHeadNode = newLastNode->next;
        ListNode* oldLastNode = findLastNode(newHeadNode);

        oldLastNode->next = head;
        newLastNode->next = nullptr;

        return newHeadNode;
    }
};
