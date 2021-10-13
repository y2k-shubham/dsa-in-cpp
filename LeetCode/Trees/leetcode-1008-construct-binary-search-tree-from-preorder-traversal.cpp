// LeetCode-1008: https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/

#include <cstdio>
#include <iostream>
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

class Solution {
   private:
    TreeNode* createNode(int val) {
        TreeNode* newNode = new TreeNode;
        newNode->val = val;
        newNode->left = nullptr;
        newNode->right = nullptr;

        return newNode;
    }

    TreeNode* bstFromPreOrderRec(vector<int>& preOrder, int lo, int hi) {
        int len = hi - lo + 1;

        if (len <= 0) {
            return nullptr;
        } else if (len == 1) {
            return createNode(preOrder[lo]);
        } else {
            TreeNode* root = createNode(preOrder[lo]);

            // find the index at where right subtree nodes start
            int i;
            for (i = lo + 1; i <= hi; i++) {
                if (preOrder[i] > root->val) {
                    break;
                }
            }

            TreeNode* lChild = nullptr;
            if (i > (lo + 1)) {
                lChild = bstFromPreOrderRec(preOrder, lo + 1, i - 1);
            } else {
                // left subtree empty
            }

            TreeNode* rChild = nullptr;
            if (i <= hi) {
                rChild = bstFromPreOrderRec(preOrder, i, hi);
            } else {
                // right subtree empty
            }

            root->left = lChild;
            root->right = rChild;

            return root;
        }
    }

   public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        return bstFromPreOrderRec(preorder, 0, preorder.size() - 1);
    }
};
