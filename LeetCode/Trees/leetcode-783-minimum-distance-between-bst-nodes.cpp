// LeetCode-783: https://leetcode.com/problems/minimum-distance-between-bst-nodes

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

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
    // int prevVal = INT_MIN;
    // return minDiff1(root, prevVal);

    return minDiff2(root, INT_MIN, false).second;
}

pair<int, int> minDiff2(TreeNode* root, int prevVal, bool isLChild) {
    if (root == nullptr) {
        return {INT_MIN, INT_MAX};
    } else {
        pair<int, int> lRes = minDiff2(root->left, prevVal, true);
        int lPrevVal = lRes.first;

        /**
         * find current diff taking into account
         * 1. prevVal from left result: lPrevVal
         * 2. prevVal received in input from parent
         */
        int crrDiff = INT_MAX;
        if (lPrevVal == INT_MIN) {
            crrDiff = (prevVal != INT_MIN) ? (root->val - prevVal) : INT_MAX;
        } else {
            crrDiff = root->val - lPrevVal;
        }

        pair<int, int> rRes = minDiff2(root->right, root->val, false);

        // decide what prevVal to return as result from here based on right prevVal result
        int rPrevVal = rRes.first;
        int prevVal = (rPrevVal == INT_MIN) ? root->val : rPrevVal;
        return {prevVal, min(crrDiff, min(lRes.second, rRes.second))};
    }
}
