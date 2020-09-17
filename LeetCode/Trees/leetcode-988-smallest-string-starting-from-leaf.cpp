// LeetCode-988: https://leetcode.com/problems/smallest-string-starting-from-leaf/

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

string smallestFromLeafRec(TreeNode *root, string crrStr) {
    if (root == nullptr) {
        return crrStr;
    } else {
        char crrChar = (char)(97 + root->val);
        string newStr = crrChar + crrStr;

        if (root->left == nullptr && root->right == nullptr) {
            return newStr;
        } else if (root->left != nullptr && root->right != nullptr) {
            string lRes = smallestFromLeafRec(root->left, newStr);
            string rRes = smallestFromLeafRec(root->right, newStr);

            // std::string compare https://www.geeksforgeeks.org/stdstringcompare-in-c/
            if (lRes.compare(rRes) < 0) {
                return lRes;
            } else {
                return rRes;
            }
        } else if (root->left != nullptr) {
            return smallestFromLeafRec(root->left, newStr);
        } else {
            // root->right !- nullptr
            return smallestFromLeafRec(root->right, newStr);
        }
    }
}

string smallestFromLeaf(TreeNode *root) {
    return smallestFromLeafRec(root, "");
}
