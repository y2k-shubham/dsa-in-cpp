// LeetCode-2058: https://leetcode.com/problems/find-the-minimum-and-maximum-number-of-nodes-between-critical-points/

#include <vector>
#include <climits>

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
    bool isCriticalPoint(
            ListNode* prevNode,
            ListNode* crrNode
    ) {
        ListNode* nextNode = crrNode->next;
        if ((prevNode == nullptr) || (crrNode == nullptr) || (nextNode == nullptr)) {
            return false;
        }

        return ((crrNode->val < prevNode->val) && (crrNode->val < nextNode->val))
               || ((crrNode->val > prevNode->val) && (crrNode->val > nextNode->val));
    }

public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        int firstCriticalPointIdx = INT_MAX;
        int lastCriticalPointIdx = INT_MIN;
        int minCriticalPointDist = INT_MAX;

        int i = 1;
        ListNode* prevNode = nullptr;
        ListNode* crrNode = head;
        while (crrNode != nullptr) {
            if (isCriticalPoint(prevNode, crrNode)) {
                if (firstCriticalPointIdx == INT_MAX) {
                    firstCriticalPointIdx = i;
                } else {
                    int crrCriticalPointDist = i - lastCriticalPointIdx;
                    minCriticalPointDist = min(minCriticalPointDist, crrCriticalPointDist);
                }

                lastCriticalPointIdx = i;
            }

            prevNode = crrNode;
            crrNode = crrNode->next;
            i++;
        }

        if ((firstCriticalPointIdx == INT_MAX) || (firstCriticalPointIdx == lastCriticalPointIdx)) {
            return {-1, -1};
        }
        int maxCriticalPointDist = lastCriticalPointIdx - firstCriticalPointIdx;

        return {minCriticalPointDist, maxCriticalPointDist};
    }
};
