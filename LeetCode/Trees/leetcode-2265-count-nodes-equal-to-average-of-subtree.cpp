// LeetCode-2265: https://leetcode.com/problems/count-nodes-equal-to-average-of-subtree/

#include <tuple>

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
    tuple<int, int, int> countAvgNodesRec(TreeNode* root) {
        if (root == nullptr) {
            return {0, 0, 0};
        }

        tuple<int, int, int> lRes = countAvgNodesRec(root->left);
        tuple<int, int, int> rRes = countAvgNodesRec(root->right);

        int numAvgNodes = get<0>(lRes) + get<0>(rRes);

        int totalSum = get<1>(lRes) + get<1>(rRes) + root->val;
        int numNodes = get<2>(lRes) + get<2>(rRes) + 1;
        int calcAvg = totalSum / numNodes;
        if (root->val == calcAvg) {
            numAvgNodes++;
        }

        return {numAvgNodes, totalSum, numNodes};
    }

public:
    int averageOfSubtree(TreeNode* root) {
        return get<0>(countAvgNodesRec(root));
    }
};
