// LeetCode-124: https://leetcode.com/problems/binary-tree-maximum-path-sum/
// harder than it seems on the first sight (often because problem gets misunderstood)

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
    int findMaxNode(TreeNode *root) {
        if (root == nullptr) {
            return INT_MIN;
        }

        return max(
                root->val,
                max(
                        findMaxNode(root->left),
                        findMaxNode(root->right)
                )
        );
    }

    // LC submission: speed 33 %tile, memory 9 %tile
    pair<int, int> maxPathSumRec(TreeNode *root) {
        if (root == nullptr) {
            return {0, INT_MIN};
        }

        pair<int, int> lRes = maxPathSumRec(root->left);
        pair<int, int> rRes = maxPathSumRec(root->right);

        int crrPathSum = lRes.first + root->val + rRes.first;
        int crrMaxSum = max(0, max(lRes.first, rRes.first) + root->val);

        return {
                crrMaxSum,
                max(
                        max(crrPathSum, crrMaxSum),
                        max(lRes.second, rRes.second)
                )
        };
    }

public:
    int maxPathSum(TreeNode *root) {
        int maxNode = findMaxNode(root);
        if (maxNode <= 0) {
            return maxNode;
        }

        return maxPathSumRec(root).second;
    }
};
