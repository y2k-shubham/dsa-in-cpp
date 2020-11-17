// LeetCode-968: https://leetcode.com/problems/binary-tree-cameras/
// super hard problem

#include <cmath>
#include <cstdio>
#include <iostream>
#include <set>
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

// greedy solution explained at https://leetcode.com/problems/binary-tree-cameras/solution/
int minCamerasRec(TreeNode* root, TreeNode* parent, set<TreeNode*>& coveredNodes) {
    if (root == nullptr) {
        return 0;
    } else {
        int lRes = minCamerasRec(root->left, root, coveredNodes);
        int rRes = minCamerasRec(root->right, root, coveredNodes);
        int crrRes = 0;

        bool leftChildUncovered = (root->left != nullptr) && (coveredNodes.find(root->left) == coveredNodes.end());
        bool rightChildUncovered = (root->right != nullptr) && (coveredNodes.find(root->right) == coveredNodes.end());
        if (leftChildUncovered || rightChildUncovered) {
            crrRes = 1;
            coveredNodes.insert(parent);
            coveredNodes.insert(root);
            coveredNodes.insert(root->left);
            coveredNodes.insert(root->right);
        }

        return (lRes + rRes + crrRes);
    }
}

// LC submission: speed: 18 %tile, memory: 18 %tile
int minCameraCover1Greedy(TreeNode* root) {
    set<TreeNode*> coveredNodes;

    int minCameras = minCamerasRec(root, NULL, coveredNodes);

    if (coveredNodes.find(root) == coveredNodes.end()) {
        minCameras++;
        coveredNodes.insert(root);
    }

    return minCameras;
}

int minCameraCover(TreeNode* root) {
  return minCameraCover1Greedy(root);
}
