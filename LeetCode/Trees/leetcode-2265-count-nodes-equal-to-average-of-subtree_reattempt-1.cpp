// LeetCode-2265: https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/

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
    pair<pair<int, int>, int> averageOfSubtreeRec(TreeNode* root) {
        pair<pair<int, int>, int> emptyPair = {{0, 0}, 0};

        if (root == nullptr) {
            return emptyPair;
        }

        pair<pair<int, int>, int> lRes = (root->left == nullptr) ? emptyPair : averageOfSubtreeRec(root->left);
        pair<pair<int, int>, int> rRes = (root->right == nullptr) ? emptyPair : averageOfSubtreeRec(root->right);

        int subtreeNodesSum = lRes.first.first + root->val + rRes.first.first;
        int subtreeNodesCount = lRes.first.second + 1 + rRes.first.second;
        int subtreeNodesAvgVal = subtreeNodesSum / subtreeNodesCount;

        int crrNodeValEqualsSubtreeAvg = (root->val == subtreeNodesAvgVal) ? 1 : 0;
        int subtreeNumNodesEqualAvgVals = lRes.second + crrNodeValEqualsSubtreeAvg + rRes.second;

        return {{subtreeNodesSum, subtreeNodesCount}, subtreeNumNodesEqualAvgVals};
    }

public:
    int averageOfSubtree(TreeNode* root) {
        pair<pair<int, int>, int> res = averageOfSubtreeRec(root);
        return res.second;
    }
};
