// LeetCode-222: https://leetcode.com/problems/count-complete-tree-nodes/
// https://www.youtube.com/watch?v=CvrPf1-flAA

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

int getLHeight(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        return 1 + getLHeight(root->left);
    }
}

int getRHeight(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        return 1 + getRHeight(root->right);
    }
}

int numNodes(int height) {
    return (int)(pow(2, height) - 1);
}

int countNodes(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        int lHeight = getLHeight(root->left);
        int rHeight = getRHeight(root->right);

        if (lHeight == rHeight) {
            // perfect binary tree
            return numNodes(lHeight + 1);
        } else {
            /**
           * otherwise we can't be sure
           *  - both left and right subtree could have the 'boundary' of imperfectness
           *  - or worse yet, left and right subtree in themselves could be perfect,
           *    ye the right subtree could have one less level than left one
           * thus we have no other option than to recursively find counts for both left & right subtrees
           */
            return countNodes(root->left) + 1 + countNodes(root->right);
        }
    }
}