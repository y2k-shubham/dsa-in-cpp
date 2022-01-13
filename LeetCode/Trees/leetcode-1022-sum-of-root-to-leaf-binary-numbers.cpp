// LeetCode-1022: https://leetcode.com/problems/sum-of-root-to-leaf-binary-numbers/

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
    int findBinSumRec(TreeNode *root, int crrNum) {
        if (root == nullptr) {
            return crrNum;
        }

        crrNum <<= 1;
        crrNum |= root->val;

        if ((root->left == nullptr) && (root->right == nullptr)) {
            return crrNum;
        } else {
            int leftSum = (root->left == nullptr) ? 0 : findBinSumRec(root->left, crrNum);
            int rightSum = (root->right == nullptr) ? 0 : findBinSumRec(root->right, crrNum);

            return leftSum + rightSum;
        }
    }

   public:
    int sumRootToLeaf(TreeNode *root) {
        return findBinSumRec(root, 0);
    }
};
