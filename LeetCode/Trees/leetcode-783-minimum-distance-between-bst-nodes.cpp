// LeetCode-783: https://leetcode.com/problems/minimum-distance-between-bst-nodes

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int minDiff1(TreeNode* root, int& prevVal) {
    if (root == nullptr) {
        return INT_MAX;
    } else {
        int lMinDiff = minDiff1(root->left, prevVal);
        int crrMinDiff = (prevVal == INT_MIN) ? INT_MAX : abs(root->val - prevVal);
        prevVal = root->val;
        int rMinDiff = minDiff1(root->right, prevVal);
        return min(crrMinDiff, min(lMinDiff, rMinDiff));
    }
}

int minDiffInBST(TreeNode* root) {
    int prevVal = INT_MIN;
    return minDiff1(root, prevVal);
}
