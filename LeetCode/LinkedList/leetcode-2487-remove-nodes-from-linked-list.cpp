// LeetCode-2487: https://leetcode.com/problems/remove-nodes-from-linked-list

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode *removeNodes(ListNode *head) {
        if (head == nullptr) {
            return nullptr;
        }

        ListNode *nextSmallerNode = removeNodes(head->next);
        head->next = nextSmallerNode;

        if (nextSmallerNode == nullptr) {
            return head;
        } else if (head->val < nextSmallerNode->val) {
            return nextSmallerNode;
        } else {
            return head;
        }
    }
};
