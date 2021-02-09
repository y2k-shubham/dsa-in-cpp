// LeetCode-538: https://leetcode.com/problems/convert-bst-to-greater-tree/
// Feb 2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/585/week-2-february-8th-february-14th/3634/

#include <climits>
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
   public:
    int convertToGreaterTree1(TreeNode* root, int greaterSum) {
        if (root == nullptr) {
            return greaterSum;
        } else {
            int newSum = convertToGreaterTree1(root->right, greaterSum);
            root->val += newSum;
            return convertToGreaterTree1(root->left, root->val);
        }
    }

    int convertToGreaterTree2(TreeNode* root, int greaterSum) {
        if (root == nullptr) {
            return 0;
        } else {
            // sum of all values greater than right-subtree of this node would be 'greaterSum'
            int rSum = convertToGreaterTree2(root->right, greaterSum);
            int crrVal = root->val;

            // sum of all values greater than left-subtree of this node would be
            // 'greaterSum' + 'rSum' + 'crrVal'
            int lSum = convertToGreaterTree2(root->left, greaterSum + rSum + crrVal);

            // sum of all values greater than current node would be 'greaterSum' + 'rSum'
            root->val += greaterSum + rSum;

            // we return sum of nodes in this subtree
            return (lSum + crrVal + rSum);
        }
    }

    TreeNode* convertBST(TreeNode* root) {
        convertToGreaterTree2(root, 0);
        return root;
    }
};
