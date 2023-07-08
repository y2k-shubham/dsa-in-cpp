// LeetCode-100: https://leetcode.com/problems/same-tree/

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isSameTree(TreeNode *p, TreeNode *q) {
        bool pIsNull = p == nullptr;
        bool qIsNull = q == nullptr;

        if (pIsNull && qIsNull) {
            return true;
        } else if (!pIsNull && !qIsNull) {
            if (p->val == q->val) {
                return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};
