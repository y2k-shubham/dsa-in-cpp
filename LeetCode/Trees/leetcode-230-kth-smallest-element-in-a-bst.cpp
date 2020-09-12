// LeetCode-230: https://leetcode.com/problems/kth-smallest-element-in-a-bst/submissions/
// https://www.interviewbit.com/problems/kth-smallest-element-in-tree/
// https://www.geeksforgeeks.org/find-k-th-smallest-element-in-bst-order-statistics-in-bst/
// explaination of 2nd approach: https://www.youtube.com/watch?v=KqMm81Y7j9M

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

// LC submission: speed 50 %centile, memory: 92 %centile
// source: https://www.youtube.com/watch?v=KqMm81Y7j9M
int kthSmallestRec2(TreeNode *root, int &k) {
    if (root == nullptr) {
        return INT_MIN;
    } else {
        // find left result
        int lRes = kthSmallestRec2(root->left, k);

        // if left result if non INT_MIN, then that's the global result: return it
        if (lRes != INT_MIN) {
            return lRes;
        }

        // check if current node itself is the result and if it is, return it
        if (k == 1) {
            return root->val;
        }
        // decrement k before going into right subtree
        // why we do this? if we came here, it means we didn't return the current node
        // yet we 'consumed' it, so we have to keep record that we've seen one more node
        k--;

        // return right result
        return kthSmallestRec2(root->right, k);
    }
}

int kthSmallest(TreeNode *root, int k) {
    return kthSmallestRec1(root, k, 1).second;
}
