// LeetCode-1290: https://leetcode.com/problems/convert-binary-number-in-a-linked-list-to-integer/

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
private:
    ListNode* revList(ListNode* prevNode, ListNode* crrNode) {
        if (crrNode == nullptr) {
            return nullptr;
        }
        if (crrNode->next == nullptr) {
            crrNode->next = prevNode; // this is important
            return crrNode;
        }
        
        ListNode* newHead = revList(crrNode, crrNode->next);
        crrNode->next = prevNode;
        
        if (prevNode == nullptr) {
            // handling for crr-head -> updated tail
            crrNode->next = nullptr;
        }
        
        return newHead;
    }
    
public:
    int getDecimalValue(ListNode* head) {
        ListNode* revHead = revList(nullptr, head);
        
        int num = 0;
        int shift = 0;
        
        for (ListNode* list = revHead; list != nullptr; list = list->next) {
            num = num | (list->val << shift);
            shift++;
        }
        
        return num;
    }
};
