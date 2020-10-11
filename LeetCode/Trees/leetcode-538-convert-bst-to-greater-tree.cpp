// LeetCode-538: https://leetcode.com/problems/convert-bst-to-greater-tree/

#include <climits>
#include <cstdio>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int convertBST(TreeNode* root, int greaterSum) {
    if (root == nullptr) {
        return greaterSum;
    } else {
        int newSum = convertBST(root->right, greaterSum);
        root->val += newSum;
        return convertBST(root->left, root->val);
    }
}

TreeNode* convertBST(TreeNode* root) {
    convertBST(root, 0);
    return root;
}
