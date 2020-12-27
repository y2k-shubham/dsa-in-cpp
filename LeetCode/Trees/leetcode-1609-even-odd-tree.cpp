// LeetCode-1609: https://leetcode.com/problems/even-odd-tree/

#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <unordered_map>
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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
   public:
    bool isEvenOddRec(TreeNode* root, unordered_map<int, int>& lvlPrevValMap, int lvl) {
        if (root == nullptr) {
            return true;
        } else {
            bool lRes = isEvenOddRec(root->left, lvlPrevValMap, lvl + 1);
            if (!lRes) {
                return false;
            }

            int crrVal = root->val;
            if ((lvl % 2) == 0) {
                bool isOdd = (crrVal % 2) == 1;
                bool prevValAbsentOrSmaller = (lvlPrevValMap.find(lvl) == lvlPrevValMap.end()) || (lvlPrevValMap[lvl] < crrVal);
                if (isOdd && prevValAbsentOrSmaller) {
                    lvlPrevValMap[lvl] = crrVal;
                } else {
                    return false;
                }
            } else {
                bool isEven = (crrVal % 2) == 0;
                bool prevValAbsentOrGreater = (lvlPrevValMap.find(lvl) == lvlPrevValMap.end()) || (lvlPrevValMap[lvl] > crrVal);
                if (isEven && prevValAbsentOrGreater) {
                    lvlPrevValMap[lvl] = crrVal;
                } else {
                    return false;
                }
            }

            return isEvenOddRec(root->right, lvlPrevValMap, lvl + 1);
        }
    }

    bool isEvenOddTree(TreeNode* root) {
        unordered_map<int, int> lvlPrevValMap;
        return isEvenOddRec(root, lvlPrevValMap, 0);
    }
};
