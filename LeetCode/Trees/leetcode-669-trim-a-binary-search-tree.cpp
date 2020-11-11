// LeetCode-669: https://leetcode.com/problems/trim-a-binary-search-tree/
// soln: https://www.youtube.com/watch?v=sJxVWROygXU
// https://www.geeksforgeeks.org/remove-bst-keys-outside-the-given-range/

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

TreeNode* trimBST(TreeNode* root, int low, int high) {
    if (root == nullptr) {
        return NULL;
    } else if (root->val < low) {
        // root ... (L .. R)
        return trimBST(root->right, low, high);
    } else if (root->val == low) {
        // (L=root .. R)
        root->left = NULL;
        root->right = trimBST(root->right, low, high);
        return root;
    } else if (low < root->val && root->val < high) {
        // (L .. root .. R)
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    } else if (high == root->val) {
        // (L .. root=R)
        root->left = trimBST(root->left, low, high);
        root->right = NULL;
        return root;
    } else {
        // (L .. R) .. root
        return trimBST(root->left, low, high);
    }
}
