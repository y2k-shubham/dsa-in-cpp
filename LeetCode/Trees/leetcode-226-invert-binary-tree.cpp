// LeetCode-226: https://leetcode.com/problems/invert-binary-tree/
// pretty straight-forward problem; better dont bother to look

#include <cstdio>
#include <iostream>

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
    TreeNode *invertTree(TreeNode *root) {
        if (root != nullptr) {
            root->left = invertTree(root->left);
            root->right = invertTree(root->right);

            TreeNode *tmp = root->left;
            root->left = root->right;
            root->right = tmp;
        }

        return root;
    }
};
