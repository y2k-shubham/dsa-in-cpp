// LeetCode-1026: https://leetcode.com/problems/maximum-difference-between-node-and-ancestor/
// GFG: https://www.geeksforgeeks.org/maximum-difference-between-node-and-its-ancestor-in-binary-tree/


#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

tuple<int, int, int> maxAncDiff(TreeNode* root) {
    if (root == nullptr) {
        return {INT_MAX, INT_MIN, -1};
    } else {
        tuple<int, int, int> lRes = maxAncDiff(root->left);
        tuple<int, int, int> rRes = maxAncDiff(root->right);

        int minDesc = min(get<0>(lRes), get<0>(rRes));
        int crrMaxMinDiff = (minDesc == INT_MAX) ? -1 : abs(root->val - minDesc);

        int maxDesc = max(get<1>(lRes), get<1>(rRes));
        int crrMaxMaxDiff = (maxDesc == INT_MIN) ? -1 : abs(maxDesc - root->val);

        int crrMaxDiff = max(crrMaxMinDiff, crrMaxMaxDiff);
        int childMaxDiff = max(get<2>(lRes), get<2>(rRes));

        int returnMaxDiff = max(crrMaxDiff, childMaxDiff);

        int minVal = min(minDesc, root->val);
        int maxVal = max(maxDesc, root->val);

        return {minVal, maxVal, returnMaxDiff};
    }
}

int maxAncestorDiff(TreeNode* root) {
    tuple<int, int, int> res = maxAncDiff(root);
    return get<2>(res);
}
