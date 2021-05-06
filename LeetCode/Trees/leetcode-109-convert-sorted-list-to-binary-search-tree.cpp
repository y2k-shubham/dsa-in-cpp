// https://leetcode.com/problems/convert-sorted-list-to-binary-search-tree/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/598/week-1-may-1st-may-7th/3733/

#include <cstdio>
#include <iostream>

using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
   private:
    TreeNode* createNode(int val) {
        TreeNode* newNode = new TreeNode;
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    TreeNode* convertToTreeNodes(ListNode* head) {
        if (head == nullptr) {
            return NULL;
        } else {
            TreeNode* newHead = NULL;
            TreeNode* newList = NULL;

            for (ListNode* list = head; list != nullptr; list = list->next) {
                if (newHead == nullptr) {
                    newHead = createNode(list->val);
                    newList = newHead;
                } else {
                    TreeNode* newNode = createNode(list->val);
                    newList->right = newNode;
                    newList = newNode;
                }
            }

            return newHead;
        }
    }

    TreeNode* splitList(TreeNode* head) {
        if (head == nullptr) {
            return NULL;
        } else if (head->right == nullptr) {
            return head;
        } else {
            TreeNode* listSlowMinus1 = NULL;
            TreeNode* listSlow = head;
            TreeNode* listFast = head;

            while ((listFast != nullptr) && (listFast->right != nullptr)) {
                listSlowMinus1 = listSlow;
                listSlow = listSlow->right;
                listFast = listFast->right->right;
            }
            if (listSlowMinus1 != nullptr) {
                listSlowMinus1->right = NULL;
            }

            return listSlow;
        }
    }

    TreeNode* sortedListToBstUtil(TreeNode* head) {
        if (head == nullptr) {
            return NULL;
        } else if (head->right == nullptr) {
            return head;
        } else {
            TreeNode* root = splitList(head);

            TreeNode* lSubtreeRoot = sortedListToBstUtil(head);
            TreeNode* rSubtreeRoot = sortedListToBstUtil(root->right);

            root->left = lSubtreeRoot;
            root->right = rSubtreeRoot;

            return root;
        }
    }

   public:
    TreeNode* sortedListToBST(ListNode* head) {
        TreeNode* newHead = convertToTreeNodes(head);
        return sortedListToBstUtil(newHead);
    }
};
