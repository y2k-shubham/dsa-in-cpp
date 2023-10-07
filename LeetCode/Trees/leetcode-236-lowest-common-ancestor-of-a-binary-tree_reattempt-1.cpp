// LeetCode-236: https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    bool buildPathStack(TreeNode* root, TreeNode* target, stack<TreeNode*>& stk) {
        if (root == nullptr) {
            return false;
        }

        stk.push(root);

        if (root == target) {
            return true;
        }

        if (root->left != nullptr) {
            bool foundInLeftSubtree = buildPathStack(root->left, target, stk);
            if (foundInLeftSubtree) {
                return true;
            }
        }

        if (root->right != nullptr) {
            bool foundInRightSubtree = buildPathStack(root->right, target, stk);
            if (foundInRightSubtree) {
                return true;
            }
        }

        stk.pop();
        return false;
    }

    stack<TreeNode*> reverseStack(stack<TreeNode*>& stk) {
        stack<TreeNode*> revStk;
        while (!stk.empty()) {
            revStk.push(stk.top());
            stk.pop();
        }

        return revStk;
    }

    TreeNode* findLCA(stack<TreeNode*>& pathStk1, stack<TreeNode*>& pathStk2) {
        TreeNode* lastCommonAncestor = nullptr;
        while (!pathStk1.empty() && !pathStk2.empty() && (pathStk1.top() == pathStk2.top())) {
            lastCommonAncestor = pathStk1.top();
            pathStk1.pop();
            pathStk2.pop();
        }

        return lastCommonAncestor;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        stack<TreeNode*> pathStkP;
        buildPathStack(root, p, pathStkP);
        stack<TreeNode*> revPathStkP = reverseStack(pathStkP);

        stack<TreeNode*> pathStkQ;
        buildPathStack(root, q, pathStkQ);
        stack<TreeNode*> revPathStkQ = reverseStack(pathStkQ);

        return findLCA(revPathStkP, revPathStkQ);
    }
};
