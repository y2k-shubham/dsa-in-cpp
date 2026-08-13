// LeetCode-270: https://leetcode.com/problems/closest-binary-search-tree-value/
// Premium
// Companies: [Meta][Google][Bloomberg][Uber][Fractal Analytics]
// not as easy as it appears

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


class Solution {
private:

public:
    int closestValue(TreeNode* root, double target) {
        if (root == nullptr) {
            return INT_MIN;
        }

        int crrVal = root->val;
        double crrDiff = abs(target - crrVal);

        bool isLeftChildNull = (root->left == nullptr);
        int leftResult = isLeftChildNull ? INT_MAX : closestValue(root->left, target);
        double leftDiff = isLeftChildNull ? INT_MAX : abs(target - leftResult);

        bool isRightChildNull = (root->right == nullptr);
        int rightResult = isRightChildNull ? INT_MAX : closestValue(root->right, target);
        double rightDiff = isRightChildNull ? INT_MAX : abs(target - rightResult);

        if ((leftDiff == crrDiff) && (crrDiff == rightDiff)) {
            return min(leftResult, min(crrVal, rightResult));
        } else if (leftDiff <= min(crrDiff, rightDiff)) {
            if (leftDiff == crrDiff) {
                return min(leftResult, crrVal);
            } else if (leftDiff == rightDiff) {
                return min(leftResult, rightResult);
            } else {
                return leftResult;
            }
        } else if (rightDiff <= min(crrDiff, leftDiff)) {
            if (rightDiff == crrDiff) {
                return min(rightResult, crrVal);
            } else if (rightDiff == leftDiff) {
                return min(rightResult, leftResult);
            } else {
                return rightResult;
            }
        } else {
            if (crrDiff == leftDiff) {
                return min(crrVal, leftResult);
            } else if (crrDiff == rightDiff) {
                return min(crrVal, rightResult);
            } else {
                return crrVal;
            }
        }
    }
};