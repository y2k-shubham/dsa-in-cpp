// LeetCode-965: https://leetcode.com/problems/univalued-binary-tree

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
    bool isUnivalTree(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }

        bool hasNoLChild = (root->left == nullptr);
        bool hasNoRChild = (root->right == nullptr);

        bool isLChildUnival = hasNoLChild ? true : (root->val == root->left->val);
        bool isRChildUnival = hasNoRChild ? true : (root->val == root->right->val);

        if (!isLChildUnival || !isRChildUnival) {
            return false;
        }

        bool isLSubtreeUnival = hasNoLChild ? true : isUnivalTree(root->left);
        bool isRSubtreeUnival = hasNoRChild ? true : isUnivalTree(root->right);

        return isLSubtreeUnival && isRSubtreeUnival;
    }
}
