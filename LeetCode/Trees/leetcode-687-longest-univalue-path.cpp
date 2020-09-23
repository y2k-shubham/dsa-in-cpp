// LeetCode-687: https://leetcode.com/problems/longest-univalue-path/submissions/
// https://www.geeksforgeeks.org/longest-path-values-binary-tree/
// this code was successfully submitted to LC, not compiling for some reason

#include <cmath>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

pair<int, int> longestUnivaluePathRec(TreeNode* root);

pair<int, int> longestUnivaluePathRec(TreeNode* root) {
    if (root == nullptr) {
        return {0, 0};
    } else if (root->left == nullptr && root->right == nullptr) {
        return {1, 1};
    } else if (root->left != nullptr && root->right != nullptr) {
        pair<int, int> lRes = longestUnivaluePathRec(root->left);
        pair<int, int> rRes = longestUnivaluePathRec(root->right);

        bool lEquals = (root->val == root->left->val);
        bool rEquals = (root->val == root->right->val);

        int longestContChain = 1;
        longestContChain = lEquals ? max((lRes.first + 1), longestContChain) : longestContChain;
        longestContChain = rEquals ? max(rRes.first + 1, longestContChain) : longestContChain;

        int longestOverallChainCurrentSubtree = max(longestContChain, max(lRes.second, rRes.second));
        if (lEquals && rEquals) {
            longestOverallChainCurrentSubtree = max(longestOverallChainCurrentSubtree, (lRes.first + rRes.first + 1));
        }

        return {longestContChain, longestOverallChainCurrentSubtree};
    } else if (root->left != nullptr) {
        pair<int, int> lRes = longestUnivaluePathRec(root->left);

        int longestContChain = (root->val == root->left->val) ? (lRes.first + 1) : 1;
        int longestOverallChainCurrentSubtree = max(longestContChain, lRes.second);

        return {longestContChain, longestOverallChainCurrentSubtree};
    } else {
        pair<int, int> rRes = longestUnivaluePathRec(root->right);

        int longestContChain = (root->val == root->right->val) ? (rRes.first + 1) : 1;
        int longestOverallChainCurrentSubtree = max(longestContChain, rRes.second);

        return {longestContChain, longestOverallChainCurrentSubtree};
    }
}

int longestUnivaluePath(TreeNode* root) {
    return max(0, (longestUnivaluePathRec(root).second - 1));
}

