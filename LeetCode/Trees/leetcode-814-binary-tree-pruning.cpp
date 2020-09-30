// LeetCode-814: https://leetcode.com/problems/binary-tree-pruning/
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

int pruneTreeRec(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    } else {
        int lRes = pruneTreeRec(root->left);
        if (lRes == 0) {
            root->left = NULL;
        }

        int rRes = pruneTreeRec(root->right);
        if (rRes == 0) {
            root->right = NULL;
        }

        if (root->val == 1) {
            return lRes + rRes + 1;
        } else {
            return lRes + rRes;
        }
    }
}

TreeNode* pruneTree(TreeNode* root) {
    int numOnes = pruneTreeRec(root);
    if (numOnes == 0) {
        return NULL;
    } else {
        return root;
    }
}
