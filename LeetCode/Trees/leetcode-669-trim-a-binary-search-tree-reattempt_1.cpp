// LeetCode-669: https://leetcode.com/problems/trim-a-binary-search-tree/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode *trimBST(TreeNode *root, int low, int high) {
        if (root == nullptr) {
            return nullptr;
        } else if (root->val < low) {
            return trimBST(root->right, low, high);
        } else if (high < root->val) {
            return trimBST(root->left, low, high);
        } else {
            root->left = trimBST(root->left, low, root->val - 1);
            root->right = trimBST(root->right, root->val + 1, high);
            return root;
        }
    }
};
