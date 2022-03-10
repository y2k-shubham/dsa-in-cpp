// LeetCode-2: https://leetcode.com/problems/add-two-numbers/

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
        newNode->next = nullptr;
        newNode->val = val;
        return newNode;
    }

    ListNode* addNumsRec(ListNode* l1, ListNode* l2, int carry) {
        bool isL1Null = l1 == nullptr;
        bool isL2Null = l2 == nullptr;
        // IMPORTANT: we cant return null until carry is non-zero
        if (isL1Null && isL2Null && (carry == 0)) {
            return nullptr;
        }

        ListNode* l1Next = (l1 == nullptr) ? nullptr : l1->next;
        int l1Val = isL1Null ? 0 : l1->val;

        ListNode* l2Next = (l2 == nullptr) ? nullptr : l2->next;
        int l2Val = isL2Null ? 0 : l2->val;

        int sum = l1Val + l2Val + carry;
        // this might be a bit counter-intuitive,
        // but digit is determined by modulo & carry by division
        int dig = sum % 10;
        carry = sum / 10;

        ListNode* newNode = createNode(dig);
        newNode->next = addNumsRec(l1Next, l2Next, carry);

        return newNode;
    }

   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return addNumsRec(l1, l2, 0);
    }
};
