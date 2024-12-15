// LeetCode-865: https://leetcode.com/problems/smallest-subtree-with-all-the-deepest-nodes

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

class Solution {
private:
    inline bool isEmpty(TreeNode* node) {
        return node == nullptr;
    }

    inline bool isLeaf(TreeNode* root) {
        return !isEmpty(root) && ((root->left == nullptr) && (root->right == nullptr));
    }

    pair <TreeNode*, int> subtreeWithAllDeepestRec(TreeNode* root, int depth) {
        if (isEmpty(root)) {
            return {nullptr, 0};
        } else if (isLeaf(root)) {
            return {root, depth};
        } else {
            pair <TreeNode*, int> lRes = subtreeWithAllDeepestRec(root->left, depth + 1);
            pair <TreeNode*, int> rRes = subtreeWithAllDeepestRec(root->right, depth + 1);

            if (lRes.second > rRes.second) {
                return lRes;
            } else if (lRes.second < rRes.second) {
                return rRes;
            } else {
                return {root, lRes.second};
            }
        }
    }

public:
    TreeNode* subtreeWithAllDeepest(TreeNode* root) {
        if (isEmpty(root) || isLeaf(root)) {
            return root;
        }

        pair <TreeNode*, int> res = subtreeWithAllDeepestRec(root, 0);
        return res.first;
    }
};
