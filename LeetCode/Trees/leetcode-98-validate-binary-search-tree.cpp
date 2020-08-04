// LeetCode-98: https://leetcode.com/problems/validate-binary-search-tree/
// 


#include <climits>
#include <cstdio>
#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool isValidBST(TreeNode *root) {
    return isValid(root, INT_MIN, INT_MAX);
}

bool isValid(TreeNode *root, int lo, int hi) {
    if (root == NULL) {
        return true;
    } else if (lo <= root->val && root->val <= hi) {
        bool lValid = false;
        if (root->val > INT_MIN) {
            lValid = isValid(root->left, lo, root->val - 1);
        } else {
            lValid = root->left == NULL;
        }

        bool rValid = false;
        if (root->val < INT_MAX) {
            rValid = lValid && isValid(root->right, root->val + 1, hi);
        } else {
            rValid = lValid && root->right == NULL;
        }

        return rValid;
    } else {
        return false;
    }
}