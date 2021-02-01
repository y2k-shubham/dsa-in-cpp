// LeetCode-1305: https://leetcode.com/problems/all-elements-in-two-binary-search-trees/

#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class TreeIterator {
   private:
    stack<TreeNode*> stk;

    void push(TreeNode* node) {
        while (node != nullptr) {
            stk.push(node);
            node = node->left;
        }
    }

   public:
    bool hasNext() {
        return !stk.empty();
    }

    int seeNext() {
        TreeNode* node = stk.top();
        return node->val;
    }

    int getNext() {
        TreeNode* node = stk.top();
        stk.pop();

        if (node->right != nullptr) {
            push(node->right);
        }

        return node->val;
    }

    TreeIterator(TreeNode* root) {
        push(root);
    }
};

class Solution {
   public:
    vector<int> getAllElements(TreeNode* root1, TreeNode* root2) {
        vector<int> vals;

        if (root1 == nullptr && root2 == nullptr) {
            // do nothing
        } else if (root1 == nullptr) {
            TreeIterator ti = TreeIterator(root2);
            while (ti.hasNext()) {
                vals.push_back(ti.getNext());
            }
        } else if (root2 == nullptr) {
            TreeIterator ti = TreeIterator(root1);
            while (ti.hasNext()) {
                vals.push_back(ti.getNext());
            }
        } else {
            TreeIterator ti1 = TreeIterator(root1);
            TreeIterator ti2 = TreeIterator(root2);

            while (ti1.hasNext() && ti2.hasNext()) {
                if (ti1.seeNext() <= ti2.seeNext()) {
                    vals.push_back(ti1.getNext());
                } else {
                    vals.push_back(ti2.getNext());
                }
            }

            while (ti1.hasNext()) {
                vals.push_back(ti1.getNext());
            }

            while (ti2.hasNext()) {
                vals.push_back(ti2.getNext());
            }
        }

        return vals;
    }
};
