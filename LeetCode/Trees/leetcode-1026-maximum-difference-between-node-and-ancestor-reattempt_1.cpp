// LeetCode-1026: https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/
// GFG: https://www.geeksforgeeks.org/maximum-difference-between-node-and-its-ancestor-in-binary-tree/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <tuple>
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

class Solution {
   private:
    int maxAncDiffRec(TreeNode* root, pair<int, int> minMaxAncesVals) {
        if (root == nullptr) {
            return 0;
        }

        int maxCrrDiff = max(
            abs(root->val - minMaxAncesVals.first),
            abs(root->val - minMaxAncesVals.second));

        minMaxAncesVals.first = min(minMaxAncesVals.first, root->val);
        minMaxAncesVals.second = max(minMaxAncesVals.second, root->val);

        return max(
            maxCrrDiff,
            max(
                maxAncDiffRec(root->left, minMaxAncesVals),
                maxAncDiffRec(root->right, minMaxAncesVals)));
    }

   public:
    int maxAncestorDiff(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return maxAncDiffRec(root, {root->val, root->val});
    }
};
