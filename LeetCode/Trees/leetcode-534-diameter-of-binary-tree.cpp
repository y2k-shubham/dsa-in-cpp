// LeetCode-534: https://leetcode.com/problems/diameter-of-binary-tree/
// both solns have > 95% percentile for both runtime & memory on LC
// https://www.geeksforgeeks.org/diameter-of-a-binary-tree-in-on-a-new-method/


#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

int diameter1(TreeNode* root, int& maxDiam) {
    if (root == nullptr) {
        return 0;
    } else {
        int lDia = diameter1(root->left, maxDiam);
        int rDia = diameter1(root->right, maxDiam);

        maxDiam = max(maxDiam, lDia + 1 + rDia);

        return max(lDia, rDia) + 1;
    }
}

pair<int, int> diameter2(TreeNode* root) {
    if (root == nullptr) {
        return {0, 0};
    } else {
        pair<int, int> lRes = diameter2(root->left);
        pair<int, int> rRes = diameter2(root->right);

        pair<int, int> crrRes;
        crrRes.first = max(lRes.first, rRes.first) + 1;
        crrRes.second = max(lRes.first + rRes.first + 1, max(crrRes.first, max(lRes.second, rRes.second)));

        return crrRes;
    }
}

int diameterOfBinaryTree(TreeNode* root) {
    // int maxDia = 0;
    // diameter1(root, maxDia);
    // return max(0, maxDia - 1);

    return max(0, diameter2(root).second - 1);
}
