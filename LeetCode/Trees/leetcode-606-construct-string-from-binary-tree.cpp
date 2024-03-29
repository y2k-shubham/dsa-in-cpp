// LeetCode-606: https://leetcode.com/problems/construct-string-from-binary-tree/
// soln: https://www.youtube.com/watch?v=22FsZB6rSxI
// LC submission - [speed] 28ms, 15%centile, [memory] 26.80MB, 53 %centile

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

string tree2str(TreeNode* t) {
    if (t == nullptr) {
        return "";
    } else if (t->left != nullptr && t->right != nullptr) {
        return to_string(t->val) + "(" + tree2str(t->left) + ")(" + tree2str(t->right) + ")";
    } else if (t->left == nullptr && t->right == nullptr) {
        return "" + to_string(t->val);
    } else if (t->left != nullptr) {
        return to_string(t->val) + "(" + tree2str(t->left) + ")";
    } else {
        return to_string(t->val) + "()(" + tree2str(t->right) + ")";
    }
}
