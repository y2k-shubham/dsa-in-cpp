// LeetCode-337: https://leetcode.com/problems/house-robber-iii/
// basic principle is still same as Maximum Sum Subsequence Non-Adjacent
// (which is also true for house-robber & house-robber-ii )
// (TusharRoy: https://www.youtube.com/watch?v=UtGtF6nc35g )

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

pair<int, int> getIncExcSums(TreeNode *root) {
    if (root == nullptr) {
        // leaf node, can't rob anything
        return {0, 0};
    } else if (root->left == nullptr && root->right == nullptr) {
        // just one node, inc-value means rob it (root->val), exc-value means dont rob (0)
        return {root->val, 0};
    } else if (root->left != nullptr && root->right != nullptr) {
        pair<int, int> lRes = getIncExcSums(root->left);
        pair<int, int> rRes = getIncExcSums(root->right);

        int maxIncSum = lRes.second + rRes.second + root->val;
        // important: note that exc value of this node is the max of
        // inc & exc values from both children
        int maxExcSum = max(lRes.first, lRes.second) + max(rRes.first, rRes.second);

        return {maxIncSum, maxExcSum};
    } else if (root->left != nullptr) {
        // important: note that exc value of this node is the max of inc & exc values from child
        pair<int, int> lRes = getIncExcSums(root->left);
        return {root->val + lRes.second, max(lRes.first, lRes.second)};
    } else {
        // important: note that exc value of this node is the max of inc & exc values from child
        pair<int, int> rRes = getIncExcSums(root->right);
        return {root->val + rRes.second, max(rRes.first, rRes.second)};
    }
}

int rob(TreeNode *root) {
    pair<int, int> incExcSums = getIncExcSums(root);
    return max(incExcSums.first, incExcSums.second);
}
