// LeetCode-173: https://leetcode.com/problems/binary-search-tree-iterator/

#include <cstdio>
#include <iostream>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// LC-submission: RunTime 76 %tile, Memory 12 %tile
class BSTIterator {
   public:
    BSTIterator(TreeNode *root) {
        pushTillPossible(root);
    }

    /** @return the next smallest number */
    int next() {
        TreeNode *topNode = stk.top();
        stk.pop();
        pushTillPossible(topNode->right);
        return topNode->val;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !stk.empty();
    }

   private:
    stack<TreeNode *> stk;

    void pushTillPossible(TreeNode *root) {
        while (root != nullptr) {
            stk.push(root);
            root = root->left;
        }
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
