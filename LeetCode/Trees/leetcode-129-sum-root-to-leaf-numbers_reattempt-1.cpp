// LeetCode-129: https://leetcode.com/problems/sum-root-to-leaf-numbers/
// https://www.geeksforgeeks.org/sum-numbers-formed-root-leaf-paths/
// https://www.interviewbit.com/problems/sum-root-to-leaf-numbers/

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
    inline bool isNull(TreeNode* root) {
        return root == nullptr;
    }

    inline bool hasLeftChild(TreeNode* root) {
        return root->left != nullptr;
    }

    inline bool hasRightChild(TreeNode* root) {
        return root->right != nullptr;
    }

    inline bool isLeaf(TreeNode* root) {
        return !isNull(root) && (root->left == nullptr) && (root->right == nullptr);
    }

    int sumNumbersRec(TreeNode* root, int crrRunningNum) {
        if (isNull(root)) {
            return 0;
        }

        int updatedRunningNum = (crrRunningNum * 10) + root->val;
        if (isLeaf(root)) {
            return updatedRunningNum;
        }

        int leftSum = hasLeftChild(root) ? sumNumbersRec(root->left, updatedRunningNum) : 0;
        int rightSum = hasRightChild(root) ? sumNumbersRec(root->right, updatedRunningNum) : 0;

        return leftSum + rightSum;
    }

public:
    int sumNumbers(TreeNode* root) {
        return sumNumbersRec(root, 0);
    }
};
