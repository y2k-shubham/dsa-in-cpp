// LeetCode-653: https://leetcode.com/problems/two-sum-iv-input-is-a-bst/

#include <stack>
#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>

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
    stack<TreeNode *> lStack;
    stack<TreeNode *> rStack;

    void deepPushLeft(TreeNode *node) {
        while (node != nullptr) {
            this->lStack.push(node);
            node = node->left;
        }
    }

    TreeNode *getNextNodeLeft() {
        if (lStack.empty()) {
            return nullptr;
        }

        TreeNode *node = lStack.top();
        lStack.pop();
        if (node->right != nullptr) {
            deepPushLeft(node->right);
        }

        return node;
    }

    void deepPushRight(TreeNode *node) {
        while (node != nullptr) {
            this->rStack.push(node);
            node = node->right;
        }
    }

    TreeNode *getNextNodeRight() {
        if (rStack.empty()) {
            return nullptr;
        }

        TreeNode *node = rStack.top();
        rStack.pop();
        if (node->left != nullptr) {
            deepPushRight(node->left);
        }

        return node;
    }

    void showLeftTrav() {
        printf("\nleftTrav is:-\n");

        TreeNode *node = getNextNodeLeft();
        while (node != nullptr) {
            printf("%d ", node->val);
            node = getNextNodeLeft();
        }

        cout << endl;
    }

    void showRightTrav() {
        printf("\nrightTrav is:-\n");

        TreeNode *node = getNextNodeRight();
        while (node != nullptr) {
            printf("%d ", node->val);
            node = getNextNodeRight();
        }

        cout << endl;
    }

public:
    bool findTarget(TreeNode *root, int k) {
        deepPushLeft(root);
        TreeNode *lNode = getNextNodeLeft();
        if (debug) {
            showLeftTrav();
        }

        deepPushRight(root);
        TreeNode *rNode = getNextNodeRight();
        if (debug) {
            showRightTrav();
        }

        while ((lNode != nullptr) && (rNode != nullptr) && (lNode->val < rNode->val)) {
            int sum = lNode->val + rNode->val;
            if (sum < k) {
                lNode = getNextNodeLeft();
            } else if (sum == k) {
                return true;
            } else {
                rNode = getNextNodeRight();
            }
        }

        return false;
    }
};
