// LeetCode-623: https://leetcode.com/problems/add-one-row-to-tree/

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

TreeNode* createNode(int val, TreeNode* left, TreeNode* right) {
    TreeNode* newNode = new TreeNode;
    newNode->val = val;
    newNode->left = left;
    newNode->right = right;
    return newNode;
}

TreeNode* addOneRow(TreeNode* root, int v, int d) {
    if (root == nullptr) {
        return NULL;
    } else if (d == 1) {
        TreeNode* newNode = createNode(v, root, NULL);
        return newNode;
    } else if (d == 2) {
        TreeNode* lNewNode = createNode(v, root->left, NULL);
        TreeNode* rNewNode = createNode(v, NULL, root->right);
        root->left = lNewNode;
        root->right = rNewNode;
        return root;
    } else {
        root->left = addOneRow(root->left, v, d - 1);
        root->right = addOneRow(root->right, v, d - 1);
        return root;
    }
}
