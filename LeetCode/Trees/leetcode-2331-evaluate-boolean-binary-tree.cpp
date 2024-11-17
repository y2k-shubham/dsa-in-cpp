// LeetCode-2331: https://leetcode.com/problems/evaluate-boolean-binary-tree

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool evaluateTree(TreeNode* root) {
        if (root == nullptr) {
            return false;
        }

        bool hasLeftChild = root->left != nullptr;
        bool hasRightChild = root->right != nullptr;

        if (!hasLeftChild && !hasRightChild) {
            return root->val == 1;
        }

        if (hasLeftChild && hasRightChild) {
            if (root->val == 2) {
                return evaluateTree(root->left) || evaluateTree(root->right);
            } else {
                return evaluateTree(root->left) && evaluateTree(root->right);
            }
        }

        return false;
    }
};
