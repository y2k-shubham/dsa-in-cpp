// LeetCode-872: https://leetcode.com/problems/leaf-similar-trees/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <utility>
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

void storeLeaves(TreeNode* root, vector<int>& leaves) {
    if (root != nullptr) {
        if (root->left == nullptr && root->right == nullptr) {
            leaves.push_back(root->val);
        } else {
            storeLeaves(root->left, leaves);
            storeLeaves(root->right, leaves);
        }
    }
}

bool leafSimilar(TreeNode* root1, TreeNode* root2) {
    vector<int> leaves1;
    storeLeaves(root1, leaves1);

    vector<int> leaves2;
    storeLeaves(root2, leaves2);

    return (leaves1 == leaves2);
}
