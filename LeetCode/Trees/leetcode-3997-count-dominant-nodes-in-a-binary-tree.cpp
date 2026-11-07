// LeetCode-3997: https://leetcode.com/problems/count-dominant-nodes-in-a-binary-tree/

// Suboptimal solution:
// - haven't leveraged the property that input is complete binary tree,
// - but incidentally a better solution doesn't exist

#include <algorithm>
#include <climits>
#include <utility>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

#define EMPTY_SUBTREE_RES make_pair(INT_MIN, 0)

class Solution {
private:
    pair <int, int> countDominantNodesRec(TreeNode* root) {
        if (root == nullptr) {
            return EMPTY_SUBTREE_RES;
        }

        bool hasLChild = root->left != nullptr;
        pair <int, int> lRes = hasLChild ? countDominantNodesRec(root->left) : EMPTY_SUBTREE_RES;

        bool hasRChild = root->right != nullptr;
        pair <int, int> rRes = hasRChild ? countDominantNodesRec(root->right) : EMPTY_SUBTREE_RES;

        if (!hasLChild && !hasRChild) {
            return {root->val, 1};
        } else if (!hasLChild) {
            if (rRes.first <= root->val) {
                return {root->val, rRes.second + 1};
            } else {
                return rRes;
            }
        } else if (!hasRChild) {
            if (lRes.first <= root->val) {
                return {root->val, lRes.second + 1};
            } else {
                return lRes;
            }
        } else {
            if ((rRes.first <= root->val) && (lRes.first <= root->val)) {
                return {root->val, rRes.second + lRes.second + 1};
            } else {
                return {max(rRes.first, lRes.first), rRes.second + lRes.second};
            }
        }
    }

public:
    int countDominantNodes(TreeNode* root) {
        return countDominantNodesRec(root).second;
    }
};
