// LeetCode-1026: https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/
// GFG: https://www.geeksforgeeks.org/maximum-difference-between-node-and-its-ancestor-in-binary-tree/

#include <climits>
#include <cmath>
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

class Solution {
private:
    int maxAncestorDiff(TreeNode* root, int maxAncestorVal, int minAncestorVal) {
        if (root == nullptr) {
            return INT_MIN;
        }

        int maxAncestorValUpdated = max(maxAncestorVal, root->val);
        int minAncestorValUpdated = min(minAncestorVal, root->val);
        int lSubtreeAns = maxAncestorDiff(root->left, maxAncestorValUpdated, minAncestorValUpdated);
        int rSubtreeAns = maxAncestorDiff(root->right, maxAncestorValUpdated, minAncestorValUpdated);

        int crrValMinDiff = (minAncestorVal == INT_MAX) ? 0 : abs(root->val - minAncestorVal);
        int crrValMaxDiff = (maxAncestorVal == INT_MIN) ? 0 : abs(maxAncestorVal - root->val);

        return max(
                max(crrValMinDiff, crrValMaxDiff),
                max(lSubtreeAns, rSubtreeAns)
        );
    }

public:
    int maxAncestorDiff(TreeNode* root) {
        return maxAncestorDiff(root, INT_MIN, INT_MAX);
    }
};
