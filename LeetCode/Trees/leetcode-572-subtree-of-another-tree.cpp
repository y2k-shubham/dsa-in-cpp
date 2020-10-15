// LeetCode-572: https://leetcode.com/problems/subtree-of-another-tree/
// soln: https://www.youtube.com/watch?v=HdMs2Fl_I-Q

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

// LC submission - speed: 96 %centile, memory: 5 %centile

bool areEqual(TreeNode* t1, TreeNode* t2) {
    if (t1 == nullptr || t2 == nullptr) {
        return (t1 == nullptr) && (t2 == nullptr);
    } else {
        return (t1->val == t2->val) && areEqual(t1->left, t2->left) && areEqual(t1->right, t2->right);
    }
}

bool isSubtree(TreeNode* t1, TreeNode* t2) {
    if (t1 == nullptr || t2 == nullptr) {
        return (t1 == nullptr) && (t2 == nullptr);
    } else {
        return areEqual(t1, t2) || isSubtree(t1->left, t2) || isSubtree(t1->right, t2);
    }
}
