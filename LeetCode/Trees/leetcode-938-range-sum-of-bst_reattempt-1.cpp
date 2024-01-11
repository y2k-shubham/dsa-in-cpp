// LeetCode-938: https://leetcode.com/problems/range-sum-of-bst/submissions/

#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // LC runtime: 107 ms
    int rangeSumBST(TreeNode* root, int low, int high) {
        if (root == nullptr) {
            return 0;
        }
        if (root->val < low) {
            return rangeSumBST(root->right, low, high);
        }
        if (high < root->val) {
            return rangeSumBST(root->left, low, high);
        }

        return rangeSumBST(root->left, low, high) + root->val + rangeSumBST(root->right, low, high);
    }
};
