// LeetCode-563: https://leetcode.com/problems/binary-tree-tilt/
// both solns have > 90% percentile for both runtime & memory on LC
// https://www.geeksforgeeks.org/tilt-binary-tree/

#include <cmath>
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

// conventional soln
int findTilt(TreeNode* root, int& totalTilt) {
    if (root == nullptr) {
        return 0;
    } else {
        int lSum = findTilt(root->left, totalTilt);
        int rSum = findTilt(root->right, totalTilt);

        totalTilt += abs(lSum - rSum);

        return lSum + rSum + root->val;
    }
}

// tricky, egoistic soln
pair<int, int> findTiltRec(TreeNode* root) {
    if (root == nullptr) {
        return {0, 0};
    } else {
        pair<int, int> lRes = findTiltRec(root->left);
        pair<int, int> rRes = findTiltRec(root->right);

        int totalSum = lRes.first + root->val + rRes.first;

        int crrTilt = abs(lRes.first - rRes.first);
        int totalTilt = lRes.second + crrTilt + rRes.second;

        return {totalSum, totalTilt};
    }
}

int findTilt(TreeNode* root) {
    // int totalTilt = 0;
    // findTilt(root, totalTilt);
    // return totalTilt;

    return findTiltRec(root).second;
}
