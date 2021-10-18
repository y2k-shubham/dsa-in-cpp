// LeetCode-993: https://leetcode.com/problems/cousins-in-binary-tree/

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

class Solution {
   private:
    pair<int, int> findDepthAndParent(TreeNode *root, int x, int depth) {
        if (root == nullptr) {
            return {depth, -1};
        }
        if (root->val == x) {
            return {depth, -1};
        }

        if ((root->left != nullptr) && (root->left->val == x)) {
            return {depth + 1, root->val};
        }
        if ((root->right != nullptr) && (root->right->val == x)) {
            return {depth + 1, root->val};
        }

        pair<int, int> lRes = findDepthAndParent(root->left, x, depth + 1);
        if (lRes.second > 0) {
            return lRes;
        }

        return findDepthAndParent(root->right, x, depth + 1);
    }

   public:
    bool isCousins(TreeNode *root, int x, int y) {
        if (root == nullptr) {
            return false;
        }
        if ((root->val == x) || (root->val == y)) {
            return false;
        }

        pair<int, int> resX = findDepthAndParent(root, x, 0);
        pair<int, int> resY = findDepthAndParent(root, y, 0);

        if (
            (min(resX.second, resY.second) > 0) &&
            (resX.first == resY.first) &&
            (resX.second != resY.second)) {
            return true;
        }

        return false;
    }
};
