// LeetCode-897: https://leetcode.com/problems/increasing-order-search-tree/

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

pair<TreeNode*, TreeNode*> flatten(TreeNode* node) {
    if (node == nullptr) {
        // unreachable unless input tree is NULL
        return {NULL, NULL};
    } else if (node->left == nullptr && node->right == nullptr) {
        // leaf node
        return {node, node};
    } else {
        pair<TreeNode*, TreeNode*> lRes = flatten(node->left);
        pair<TreeNode*, TreeNode*> rRes = flatten(node->right);

        pair<TreeNode*, TreeNode*> retRes = {NULL, NULL};
        node->left = NULL;

        TreeNode* nullNode = NULL;
        if (lRes == make_pair(nullNode, nullNode)) {
            retRes.first = node;
        } else {
            retRes.first = lRes.first;
            lRes.second->right = node;
        }

        if (rRes == make_pair(nullNode, nullNode)) {
            retRes.second = node;
        } else {
            retRes.second = rRes.second;
            node->right = rRes.first;
        }

        return retRes;
    }
}

TreeNode* increasingBST(TreeNode* root) {
    pair<TreeNode*, TreeNode*> res = flatten(root);
    return res.first;
}
