// LeetCode-701: https://leetcode.com/problems/insert-into-a-binary-search-tree/

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
    TreeNode* createNode(int val) {
        TreeNode* newNode = new TreeNode;
        newNode->val = val;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

   public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        if (root == nullptr) {
            return createNode(val);
        } else if (val < root->val) {
            root->left = insertIntoBST(root->left, val);
            return root;
        } else if (val > root->val) {
            root->right = insertIntoBST(root->right, val);
            return root;
        } else {
            // duplicate node
            return nullptr;
        }
    }
};