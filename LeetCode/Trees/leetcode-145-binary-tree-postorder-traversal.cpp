// LeetCode-145: https://leetcode.com/problems/binary-tree-postorder-traversal/
// implemented using stack (instead of recursion)

#include <stack>
#include <utility>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    bool debug = false;

    void showStk(stack<pair<TreeNode *, int> > stk) {
        // printf("stack is:-\n");
        while (!stk.empty()) {
            printf("%d (%d)\n", stk.top().first->val, stk.top().second);
            stk.pop();
        }
    }

    void pushNodeToStk(
            stack<pair<TreeNode *, int> > &stk,
            TreeNode *root,
            int pushIter
    ) {
        if (root == nullptr) {
            return;
        }

        stk.push({root, pushIter});
        // if (root->right != nullptr) {
        //     stk.push(root->right);
        // }
        // if (root->left != nullptr) {
        //     stk.push(root->left);
        // }
    }

public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> postOrderVec;

        stack<pair<TreeNode *, int>> stk;
        pushNodeToStk(stk, root, 1);

        int iter = 1;
        while (!stk.empty()) {
            pair<TreeNode *, int> stkTop = stk.top();
            stk.pop();

            if (stkTop.second == 1) {
                // popped for first time, just expand and push again
                pushNodeToStk(stk, stkTop.first, 2);
                pushNodeToStk(stk, stkTop.first->right, 1);
                pushNodeToStk(stk, stkTop.first->left, 1);
            } else {
                postOrderVec.push_back(stkTop.first->val);
            }

            if (debug) {
                printf("\n---iter=%d---\n", iter++);
                showStk(stk);
            }
        }

        return postOrderVec;
    }
};
