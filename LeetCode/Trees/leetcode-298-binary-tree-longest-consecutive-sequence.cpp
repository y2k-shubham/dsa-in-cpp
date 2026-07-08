// LeetCode-298: https://leetcode.com/problems/binary-tree-longest-consecutive-sequence/

#include <algorithm>
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
    pair<int, int> EMPTY_RES = {0, 0};
    pair<int, int> UNIT_RES = {1, 1};

    pair<int, int> longestConsecRec(TreeNode* root) {
        if (root == nullptr) {
            return EMPTY_RES;
        }

        bool hasLChild = root->left != nullptr;
        bool hasRChild = root->right != nullptr;

        if (!hasLChild && !hasRChild) {
            return UNIT_RES;
        }

        pair<int, int> lRes = hasLChild ? longestConsecRec(root->left) : EMPTY_RES;
        pair<int, int> rRes = hasRChild ? longestConsecRec(root->right) : EMPTY_RES;

        bool isLChildConsecutive = hasLChild ? (root->left->val == (root->val + 1)) : false;
        bool isRChildConsecutive = hasRChild ? (root->right->val == (root->val + 1)) : false;

        int crrNodeLRes = isLChildConsecutive ? (lRes.first + 1) : 1;
        int crrNodeRRes = isRChildConsecutive ? (rRes.first + 1) : 1;
        int crrNodeRes = max(crrNodeLRes, crrNodeRRes);

        int crrSubtreeLRes = lRes.second;
        int crrSubtreeRRes = rRes.second;
        int crrSubtreeRes = max(crrNodeRes, max(crrSubtreeLRes, crrSubtreeRRes));

        pair<int, int> crrRes = {crrNodeRes, crrSubtreeRes};
        return crrRes;
    }

public:
    int longestConsecutive(TreeNode* root) {
        pair<int, int> res = longestConsecRec(root);
        return res.second;
    }
};
