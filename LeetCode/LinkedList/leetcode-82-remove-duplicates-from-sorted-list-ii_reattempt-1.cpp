// LeetCode-82: https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
   private:
    ListNode* skipNodes(ListNode* head) {
        int skipVal = head->val;

        ListNode* list = head;
        while ((list != nullptr) && (list->val == skipVal)) {
            list = list->next;
        }

        return list;
    }

   public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* list = head;

        ListNode* listPrev = nullptr;
        while (list != nullptr) {
            if ((list->next != nullptr) && (list->val == list->next->val)) {
                list = skipNodes(list);

                if (listPrev == nullptr) {
                    if (list == nullptr) {
                        // list was entirely composed of repeated nodes
                        return nullptr;
                    } else {
                        head = list;
                    }
                } else {
                    listPrev->next = list;
                }
            } else {
                listPrev = list;
                list = list->next;
            }
        }

        return head;
    }
};
