// LeetCode-129: https://leetcode.com/problems/sum-root-to-leaf-numbers/
// https://www.geeksforgeeks.org/sum-numbers-formed-root-leaf-paths/
// https://www.interviewbit.com/problems/sum-root-to-leaf-numbers/

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

int sumNumbers(TreeNode *root, int crrSum) {
    if (root == nullptr) {
        return crrSum;
    } else {
        int newSum = (crrSum * 10) + root->val;

        if (root->left == nullptr && root->right == nullptr) {
            return newSum;
        } else {
            int totalSum = 0;

            if (root->left != nullptr) {
                int lSum = sumNumbers(root->left, newSum);
                totalSum += lSum;
            }
            if (root->right != nullptr) {
                int rSum = sumNumbers(root->right, newSum);
                totalSum += rSum;
            }

            // printf("at node %d, gotSum = %d, lSum = %d, rSum = %d, returning Sum = %d\n", root->val, crrSum, newSum, lSum, rSum, (lSum + rSum));
            return totalSum;
        }
    }
}

int sumNumbers(TreeNode *root) {
    return sumNumbers(root, 0);
}
