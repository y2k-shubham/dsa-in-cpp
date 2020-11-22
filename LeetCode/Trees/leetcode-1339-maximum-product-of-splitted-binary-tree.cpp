// LeetCode-1339: https://leetcode.com/problems/maximum-product-of-splitted-binary-tree/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>

typedef unsigned long long int ull;
#define MOD 1000000007

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

ull findSum(TreeNode *root) {
    if (root == nullptr) {
        return 0;
    } else {
        return ((ull)root->val) + findSum(root->left) + findSum(root->right);
    }
}

pair<ull, ull> maxProd(ull totSum, TreeNode *root) {
    if (root == nullptr) {
        return {0, 0};
    } else {
        pair<ull, ull> lRes = maxProd(totSum, root->left);
        pair<ull, ull> rRes = maxProd(totSum, root->right);

        ull crrSum = lRes.first + root->val + rRes.first;
        ull crrProd = crrSum * (totSum - crrSum);

        ull maxProd = (lRes.second > rRes.second) ? lRes.second : rRes.second;
        maxProd = (maxProd > crrProd) ? maxProd : crrProd;

        return {crrSum, maxProd};
    }
}

int maxProduct(TreeNode *root) {
    ull totSum = findSum(root);
    pair<ull, ull> res = maxProd(totSum, root);

    ull maxProd = res.second;
    return ((int)(maxProd % MOD));
}
