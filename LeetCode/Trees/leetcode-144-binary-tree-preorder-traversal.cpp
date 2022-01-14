// LeetCode-144: https://leetcode.com/problems/binary-tree-preorder-traversal/

#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
   private:
    void preOrderRec(TreeNode *root, vector<int> &preOrderVec) {
        if (root != nullptr) {
            preOrderVec.push_back(root->val);

            preOrderRec(root->left, preOrderVec);
            preOrderRec(root->right, preOrderVec);
        }
    }

   public:
    vector<int> preorderTraversal(TreeNode *root) {
        vector<int> preOrderVec;

        preOrderRec(root, preOrderVec);
        return preOrderVec;
    }
};
