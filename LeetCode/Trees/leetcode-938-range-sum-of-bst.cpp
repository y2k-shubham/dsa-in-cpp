// LeetCode-938: https://leetcode.com/problems/range-sum-of-bst/submissions/
#include <cstdio>
#include <iostream>
#include <climits>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// LC runtime: 216 ms
int rangeSumBST(TreeNode* root, int L, int R) {
        if (root == nullptr) {
            return 0;
        } else if (R < root->val) {
            return rangeSumBST(root->left, L, R);
        } else if (L <= root->val && root->val <= R) {
            return rangeSumBST(root->left, L, root->val - 1) + root->val + rangeSumBST(root->right, root->val + 1, R);
        } else {
            return rangeSumBST(root->right, L, R);
        }
    }


// can also be solved by taking BST current subtree range;
// but (1) that one is much tougher to implement
//     (2) runtime, memory is about the same
