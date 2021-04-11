// LeetCode-1302: https://leetcode.com/problems/deepest-leaves-sum/
// LC April 2021 challenge: https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/594/week-2-april-8th-april-14th/3704/
// GFG: https://www.geeksforgeeks.org/sum-nodes-maximum-depth-binary-tree/

#include <cmath>
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
   private:
    int findHeight(TreeNode *root) {
        if (root == nullptr) {
            return 0;
        }

        return 1 + max(findHeight(root->left), findHeight(root->right));
    }

    int findNodesSumAtLvl(TreeNode *root, int targetLvl, int crrLvl) {
        if (root == nullptr) {
            return 0;
        } else if (crrLvl < targetLvl) {
            return findNodesSumAtLvl(root->left, targetLvl, crrLvl + 1) + findNodesSumAtLvl(root->right, targetLvl, crrLvl + 1);
        } else if (crrLvl == targetLvl) {
            return root->val;
        } else {
            return 0;
        }
    }

   public:
    int deepestLeavesSum(TreeNode *root) {
        int height = findHeight(root);

        return findNodesSumAtLvl(root, height, 1);
    }
};
