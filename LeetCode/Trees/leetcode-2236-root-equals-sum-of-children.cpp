// LeetCode-2236: https://leetcode.com/problems/root-equals-sum-of-children
// whosoever added this question in LeetCode should be punished for wasting everyone's time

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
    bool checkTree(TreeNode* root) {
        return root->val == ((root->left->val) + (root->right->val));
    }
};
