// LeetCode-114: https://leetcode.com/problems/flatten-binary-tree-to-linked-list/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3742/

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
    /////////////
    /// Soln-1 - LC-submission speed: 42 %tile, memory: 86 %tile
    /// although clearly this one should've been faster
    /////////////

    TreeNode* flattenRec1(TreeNode* root) {
        if (root == nullptr) {
            return NULL;
        } else if (root->left == nullptr && root->right == nullptr) {
            // leaf node
            return root;
        } else if (root->left != nullptr && root->right != nullptr) {
            TreeNode* lTail = flattenRec1(root->left);
            TreeNode* rTail = flattenRec1(root->right);

            // link up tail of left subtree's list to right-subtree's head
            lTail->right = root->right;

            // move left node towards right
            root->right = root->left;
            root->left = NULL;

            return rTail;
        } else if (root->left != nullptr) {
            TreeNode* lTail = flattenRec1(root->left);
            // move left node towards right
            root->right = root->left;
            root->left = NULL;
            return lTail;
        } else {
            // root->right != nullptr
            return flattenRec1(root->right);
        }
    }

    /////////////
    /// Soln-2 - LC-submission speed: 86 %tile, memory: 95 %tile
    /////////////

    TreeNode* getExtremeRightNode(TreeNode* root) {
        if (root == nullptr) {
            return NULL;
        } else {
            TreeNode* node;
            for (node = root; node->right != nullptr; node = node->right) {
            }

            return node;
        }
    }

    TreeNode* flattenRec2(TreeNode* root) {
        if (root == nullptr) {
            return NULL;
        } else {
            TreeNode* lRes = flattenRec2(root->left);
            TreeNode* rRes = flattenRec2(root->right);

            root->left = NULL;

            if (lRes != nullptr) {
                root->right = lRes;

                TreeNode* extremeRightNode = getExtremeRightNode(root);
                extremeRightNode->right = rRes;
            } else {
                root->right = rRes;
            }

            return root;
        }
    }

   public:
    void flatten(TreeNode* root) {
        flattenRec2(root);
    }
};
