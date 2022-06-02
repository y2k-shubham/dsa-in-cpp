// LeetCode-1038: https://leetcode.com/problems/binary-search-tree-to-greater-sum-tree/

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    int convertToGreaterSum(TreeNode* root, int greaterSum) {
        if (root == nullptr) {
            return greaterSum;
        }

        // right subtree
        greaterSum = convertToGreaterSum(root->right, greaterSum);

        // update greater sum & crr node's value
        greaterSum += root->val;
        root->val += greaterSum - root->val;

        // left subtree
        greaterSum = convertToGreaterSum(root->left, greaterSum);

        return greaterSum;
    }

public:
    TreeNode* bstToGst(TreeNode* root) {
        convertToGreaterSum(root, 0);
        return root;
    }
};
