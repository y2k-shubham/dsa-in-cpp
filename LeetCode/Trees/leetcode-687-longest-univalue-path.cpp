// LeetCode-687: https://leetcode.com/problems/longest-univalue-path/submissions/
// https://www.geeksforgeeks.org/longest-path-values-binary-tree/
// https://www.youtube.com/watch?v=cwYVhyl2A1s
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

// beats only 98% submissions on LC
/**
 * the function returns 2 values
 *  - 1st value denotes the length of longest downwards going chain containing univalue nodes starting at the node
 *    that returned this value
 *  - 2nd value denotes the answer => longest univalue path for the subtree rooted at the node that returned this value
 * 
 * also do note that this function returns the no of nodes in longest univalue path: which is 1 more than the no of edges
 */ 
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

// beats only 38% submissions on LC
// https://www.youtube.com/watch?v=cwYVhyl2A1s
int longestUnivaluePathRecGlobal(TreeNode* root, int& maxLen) {
    if (root == nullptr) {
        return 0;
    } else {
        int lRes = longestUnivaluePathRecGlobal(root->left, maxLen);
        int rRes = longestUnivaluePathRecGlobal(root->right, maxLen);

        int lPath = 0;
        if (root->left != nullptr && root->val == root->left->val) {
            lPath = lRes + 1;
        }

        int rPath = 0;
        if (root->right != nullptr && root->val == root->right->val) {
            rPath = rRes + 1;
        }

        maxLen = max(maxLen, lPath + rPath);

        return max(lPath, rPath);
    }
}

int longestUnivaluePath(TreeNode* root) {
    int maxLen = 0;
    longestUnivaluePathRecGlobal(root, maxLen);
    return maxLen;

    // return max(0, (longestUnivaluePathRec(root).second - 1));
}
