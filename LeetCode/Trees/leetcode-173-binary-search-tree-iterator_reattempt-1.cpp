// LeetCode-173: https://leetcode.com/problems/binary-search-tree-iterator/

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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class BSTIterator {
private:
    bool debug = false;

    // {node, bool -> first pop?}
    // when node is popped for 1st time -> we push it back (to iterate over left subtree)
    // when node is popped for 2nd time -> we print it (and then discard it)
    stack<pair<TreeNode *, bool> > stk;

    void showStack() {
        stack<pair<TreeNode *, bool> > stk = this->stk;

        printf("stack is:-\n");
        while (!stk.empty()) {
            pair<TreeNode *, bool> stkTop = stk.top();
            printf("(%d, %c)\t", stkTop.first->val, (stkTop.second ? 'T' : 'F'));

            stk.pop();
        }

        cout << endl;
    }

public:
    BSTIterator(TreeNode *root) {
        stk.push({root, true});

        if (debug) {
            printf("\n---------\n");
            printf("after pushing root %d\n", root->val);
            showStack();
        }
    }

    // poor performance: speed 9 %tile, memory 22 %tile
    int next() {
        pair<TreeNode *, bool> stkTop = stk.top();
        stk.pop();

        TreeNode *crrNode = stkTop.first;
        TreeNode *lChild = crrNode->left;
        TreeNode *rChild = crrNode->right;

        int returnVal = INT_MIN;
        if (stkTop.second) {
            // node popped for first time

            // push right child if exists
            if (rChild != nullptr) {
                stk.push({rChild, true});
            }

            if (lChild == nullptr) {
                // if no left child, then return current node
                returnVal = crrNode->val;
            } else {
                // push node back again with flag set to false
                stk.push({crrNode, false});
                // push left child
                stk.push({lChild, true});

                // recurse
                if (debug) {
                    printf("\n- - - - -\n");
                    printf("recursing\n");
                }
                returnVal = next();
            }
        } else {
            // return current node
            returnVal = crrNode->val;
        }

        if (debug) {
            printf("\n---------\n");
            printf("after popping node %d\n", returnVal);
            showStack();
        }

        return returnVal;
    }

    bool hasNext() {
        return !stk.empty();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
