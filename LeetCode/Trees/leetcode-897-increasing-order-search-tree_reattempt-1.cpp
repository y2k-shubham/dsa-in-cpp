// LeetCode-897: https://leetcode.com/problems/increasing-order-search-tree/
// GFG: https://www.geeksforgeeks.org/flatten-bst-to-sorted-list-increasing-order/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

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
    // {headNode, tailNode}
    pair<TreeNode *, TreeNode *> rearrangeRec(TreeNode *root) {
        if (root == nullptr) {
            return {nullptr, nullptr};
        }

        TreeNode *rChild = root->right;
        pair<TreeNode *, TreeNode *> rSoln = rearrangeRec(rChild);

        TreeNode *lChild = root->left;
        pair<TreeNode *, TreeNode *> lSoln = rearrangeRec(lChild);

        root->left = nullptr;
        root->right = rSoln.first;

        TreeNode *tail = (rChild == nullptr) ? root : rSoln.second;
        if (lChild == nullptr) {
            return {root, tail};
        } else {
            lSoln.second->right = root;
            return {lSoln.first, tail};
        }
    }

public:
    TreeNode *increasingBST(TreeNode *root) {
        pair<TreeNode *, TreeNode *> soln = rearrangeRec(root);
        return soln.first;
    }
};
