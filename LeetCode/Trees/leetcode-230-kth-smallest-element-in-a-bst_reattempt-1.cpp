// LeetCode-230: https://leetcode.com/problems/kth-smallest-element-in-a-bst/

#include <climits>

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
    int kthSmallestRec(TreeNode *root, int k, int& crrIdx) {
        if (root == nullptr) {
            return INT_MIN;
        }

        int lRes = kthSmallestRec(root->left, k, crrIdx);
        if (lRes != INT_MIN) {
            return lRes;
        }

        if (crrIdx == k) {
            return root->val;
        } else {
            crrIdx++;
        }

        return kthSmallestRec(root->right, k, crrIdx);
    }

public:
    int kthSmallest(TreeNode *root, int k) {
        int crrIdx = 1;
        return kthSmallestRec(root, k, crrIdx);
    }
};


