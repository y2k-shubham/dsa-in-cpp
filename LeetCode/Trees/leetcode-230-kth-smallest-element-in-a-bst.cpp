// LeetCode-230: https://leetcode.com/problems/kth-smallest-element-in-a-bst/submissions/
// https://www.interviewbit.com/problems/kth-smallest-element-in-tree/
// https://www.geeksforgeeks.org/find-k-th-smallest-element-in-bst-order-statistics-in-bst/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
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

int main() {
    return 0;
}

// LC submission: speed: 17 %centile, memory: 82 %centile
pair<int, int> kthSmallestRec1(TreeNode *root, int k, int pos) {
    if (root == nullptr) {
        return {-1, INT_MAX};
    } else {
        // result of left subtree
        pair<int, int> lRes = kthSmallestRec1(root->left, k, pos);

        // if left subtree has the result (has k or more nodes), then return that result only
        if (lRes.first == k) {
            return lRes;
        }

        // determine position of current node (based on input pos and how many nodes are present in left subtree)
        int crrPos = max(pos, lRes.first + 1);
        pair<int, int> crrRes = {crrPos, root->val};

        // if current node is the kth node, then return it as result
        if (crrPos == k) {
            return crrRes;
        }

        // else if right subtree is non empty, the return it's result
        // IMPORTANT: this check is necessary because without it
        // if right subtree is empty, we'll end up return empty result
        if (root->right != nullptr) {
            return kthSmallestRec1(root->right, k, crrPos + 1);
        } else {
            return crrRes;
        }
    }
}

int kthSmallest(TreeNode *root, int k) {
    return kthSmallestRec1(root, k, 1).second;
}
