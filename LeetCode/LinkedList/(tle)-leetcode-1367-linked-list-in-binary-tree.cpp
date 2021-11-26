// LeetCode-1367: https://leetcode.com/problems/linked-list-in-binary-tree/
// brute for soln; gives TLE
// will need to construct root->leaf paths in tree & perform subarray / substring search against linked-list

#include <cstdio>
#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
   private:
    bool isSubPathRec(TreeNode *root, ListNode *orgHead, ListNode *crrHead) {
        bool headIsNull = crrHead == nullptr;
        bool rootIsNull = root == nullptr;

        if (headIsNull) {
            return true;
        } else if (rootIsNull) {
            return false;
        } else {
            bool hasSubPath = false;
            if (root->val == crrHead->val) {
                hasSubPath = isSubPathRec(root->left, orgHead, crrHead->next) || isSubPathRec(root->right, orgHead, crrHead->next);
            }

            return hasSubPath || isSubPathRec(root->left, orgHead, orgHead) || isSubPathRec(root->right, orgHead, orgHead);
        }
    }

   public:
    bool isSubPath(ListNode *head, TreeNode *root) {
        return isSubPathRec(root, head, head);
    }
};
