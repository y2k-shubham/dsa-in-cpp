// LeetCode-112: https://leetcode.com/problems/path-sum/
// not as easy as it appears; has some edge cases because of possible negative target condition

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
    inline bool isLeaf(TreeNode* root) {
        return (root != nullptr) && (root->left == nullptr) && (root->right == nullptr);
    }

public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return false;
        }
        if ((targetSum == root->val) && isLeaf(root)) {
            return true;
        }

        return ((root->left != nullptr) && hasPathSum(root->left, targetSum - root->val))
               || ((root->right != nullptr) && hasPathSum(root->right, targetSum - root->val));
    }
};
