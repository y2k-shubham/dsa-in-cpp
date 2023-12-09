// LeetCode-94: https://leetcode.com/problems/binary-tree-inorder-traversal/

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

class Solution {
private:
    // LC [runtime] 0ms, 100%tile [memory] 8.64MB, 81.6%tile
    inline void inOrderRec(TreeNode* root, vector<int>& inOrderVec) {
        if (root == nullptr) {
            return;
        }

        if (root->left != nullptr) {
            inOrderRec(root->left, inOrderVec);
        }

        inOrderVec.push_back(root->val);

        if (root->right != nullptr) {
            inOrderRec(root->right, inOrderVec);
        }
    }

public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> inOrderVec;
        inOrderRec(root, inOrderVec);

        return inOrderVec;
    }
};
