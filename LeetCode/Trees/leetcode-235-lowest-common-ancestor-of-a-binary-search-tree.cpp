// LeetCode-235: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/
// https://www.interviewbit.com/problems/least-common-ancestor/
// https://www.hackerrank.com/challenges/binary-search-tree-lowest-common-ancestor/problem

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

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (root == nullptr || p == nullptr || q == nullptr) {
        return NULL;
    } else if (p->val > q->val) {
        return lowestCommonAncestor(root, q, p);
    } else if (p->val <= root->val && root->val <= q->val) {
        return root;
        // in below expression, checking for q-val is redundant
        // since we've already handled that that in this if-block
    } else if (p->val < root->val && q->val < root->val) {
        return lowestCommonAncestor(root->left, p, q);
    } else {
        return lowestCommonAncestor(root->right, p, q);
    }
}
