// LeetCode-404: https://leetcode.com/problems/sum-of-left-leaves/
// https://www.geeksforgeeks.org/find-sum-left-leaves-given-binary-tree/

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int sumOfLeftLeavesRec(TreeNode* root, bool isLeft) {
    if (root == nullptr) {
        return 0;
    } else if (root->left == nullptr && root->right == nullptr) {
        return isLeft ? root->val : 0;
    } else {
        return sumOfLeftLeavesRec(root->left, true) + sumOfLeftLeavesRec(root->right, false);
    }
}

int sumOfLeftLeaves(TreeNode* root) {
    return sumOfLeftLeavesRec(root, false);
}
