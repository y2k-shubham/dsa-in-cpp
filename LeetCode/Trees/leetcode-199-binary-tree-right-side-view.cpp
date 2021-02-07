// LeetCode-199: https://leetcode.com/problems/binary-tree-right-side-view/
// LC Feb 2021 challenge: https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3630/

#include <climits>
#include <cstdio>
#include <iostream>
#include <unordered_map>
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
   public:
    void prepareMap(TreeNode* root, unordered_map<int, int>& rViewMap, int lvl) {
        if (root != nullptr) {
            if (rViewMap.find(lvl) == rViewMap.end()) {
                rViewMap[lvl] = root->val;
            }

            prepareMap(root->right, rViewMap, lvl + 1);
            prepareMap(root->left, rViewMap, lvl + 1);
        }
    }

    // LC-submission: speed 23 %tile, memory 56 %tile
    vector<int> rightSideView1(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        unordered_map<int, int> rViewMap;
        prepareMap(root, rViewMap, 1);

        int height = rViewMap.size();
        vector<int> rViewVec(height);

        for (int i = 1; i <= height; i++) {
            rViewVec[i - 1] = rViewMap[i];
        }

        return rViewVec;
    }

    int findHeight(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        } else {
            return 1 + max(findHeight(root->left), findHeight(root->right));
        }
    }

    void populateRightView(TreeNode* root, vector<int>& rView, int lvl) {
        if (root != nullptr) {
            if (rView[lvl] == INT_MIN) {
                rView[lvl] = root->val;
            }

            populateRightView(root->right, rView, lvl + 1);
            populateRightView(root->left, rView, lvl + 1);
        }
    }

    // LC-submission: speed 23 %tile, memory 92 %tile
    vector<int> rightSideView2(TreeNode* root) {
        int height = findHeight(root);
        if (height == 0) {
            return {};
        }

        vector<int> rView(height, INT_MIN);
        populateRightView(root, rView, 0);

        return rView;
    }

    vector<int> rightSideView(TreeNode* root) {
        return rightSideView2(root);
    }
};
