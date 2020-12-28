// LeetCode-951: https://leetcode.com/problems/flip-equivalent-binary-trees/

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

class Solution {
   private:
    int getNumNonNullChildren(TreeNode* root) {
        if (root == nullptr) {
            return -1;
        } else {
            int numChildren = 0;

            if (root->left != nullptr) {
                numChildren++;
            }

            if (root->right != nullptr) {
                numChildren++;
            }

            return numChildren;
        }
    }

    TreeNode* getNonNullChild(TreeNode* root) {
        if (root == nullptr) {
            return NULL;
        } else if (root->left != nullptr) {
            return root->left;
        } else if (root->right != nullptr) {
            return root->right;
        } else {
            return NULL;
        }
    }

    pair<TreeNode*, TreeNode*> getMinMaxChildren(TreeNode* root) {
        if (root == nullptr) {
            return {NULL, NULL};
        } else if (root->left != nullptr && root->right != nullptr) {
            if (root->left->val < root->right->val) {
                return {root->left, root->right};
            } else {
                return {root->right, root->left};
            }
        } else {
            return {NULL, NULL};
        }
    }

   public:
    bool flipEquiv(TreeNode* root1, TreeNode* root2) {
        bool root1Null = root1 == nullptr;
        bool root2Null = root2 == nullptr;

        if (root1Null && root2Null) {
            return true;
        } else if (!root1Null && !root2Null) {
            if (root1->val != root2->val) {
                return false;
            }

            int root1NumChildren = getNumNonNullChildren(root1);
            int root2NumChildren = getNumNonNullChildren(root2);

            if (root1NumChildren == root2NumChildren) {
                switch (root1NumChildren) {
                    case 0: {
                        return true;
                    }

                    case 1: {
                        TreeNode* root1Child = getNonNullChild(root1);
                        TreeNode* root2Child = getNonNullChild(root2);
                        return (root1Child->val == root2Child->val) &&
                               flipEquiv(root1Child, root2Child);
                    }

                    case 2: {
                        pair<TreeNode*, TreeNode*> minMaxChildren1 = getMinMaxChildren(root1);
                        pair<TreeNode*, TreeNode*> minMaxChildren2 = getMinMaxChildren(root2);

                        return (minMaxChildren1.first->val == minMaxChildren2.first->val) &&
                               (minMaxChildren1.second->val == minMaxChildren2.second->val) &&
                               flipEquiv(minMaxChildren1.first, minMaxChildren2.first) &&
                               flipEquiv(minMaxChildren1.second, minMaxChildren2.second);
                    }

                    default:
                        return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }
};
