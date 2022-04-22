// LeetCode-971: https://leetcode.com/problems/second-minimum-node-in-a-binary-tree/
// definitely not an easy problem

// Solution by nETSETOS: https://www.youtube.com/watch?v=zex8_82T46U
// (except that we haven't modified the tree)

#include <climits> // needed for LONG_MAX
#include <iostream> // this is needed for min(long long, long long) function!

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
    long long removeValUpdateMin(TreeNode *root, int victimVal) {
        if (root == nullptr) {
            return LONG_MAX;
        }

        bool isLeaf = (root->left == nullptr) && (root->right == nullptr);
        if (isLeaf) {
            if (root->val == victimVal) {
                return LONG_MAX;
            } else {
                return root->val;
            }
        }

        long long lRes = removeValUpdateMin(root->left, victimVal);
        long long rRes = removeValUpdateMin(root->right, victimVal);

        return min(lRes, rRes);
    }

public:
    int findSecondMinimumValue(TreeNode *root) {
        long long res = removeValUpdateMin(root, root->val);
        if (res == LONG_MAX) {
            // no 2nd minimum -> all nodes are equal
            return -1;
        } else {
            return (int) res;
        }
    }
};
