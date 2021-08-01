// LeetCode-654: https://leetcode.com/problems/maximum-binary-tree/

#include <climits>
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
        newNode->left = nullptr;
        newNode->right = nullptr;
        newNode->val = val;
        return newNode;
    }

    TreeNode* buildMaxTree(vector<int>& nums, int lo, int hi) {
        int len = hi - lo + 1;

        if (len <= 0) {
            return nullptr;
        }

        if (len == 1) {
            return createNode(nums[lo]);
        }

        int maxEle = INT_MIN;
        int maxEleIdx = -1;
        for (int i = lo; i <= hi; i++) {
            if (nums[i] > maxEle) {
                maxEle = nums[i];
                maxEleIdx = i;
            }
        }

        TreeNode* newNode = createNode(maxEle);
        newNode->left = buildMaxTree(nums, lo, maxEleIdx - 1);
        newNode->right = buildMaxTree(nums, maxEleIdx + 1, hi);

        return newNode;
    }

   public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        int len = nums.size();
        return buildMaxTree(nums, 0, len - 1);
    }
};
