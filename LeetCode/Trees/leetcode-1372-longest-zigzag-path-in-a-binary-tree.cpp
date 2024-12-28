// LeetCode-1372: https://leetcode.com/problems/longest-zigzag-path-in-a-binary-tree/

#include <utility>
#include <cmath>

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
    inline bool isEmpty(TreeNode* root) {
        return root == nullptr;
    }

    inline bool isLeaf(TreeNode* root) {
        return !isEmpty(root) && isEmpty(root->left) && isEmpty(root->right);
    }

    pair <int, pair <int, int>> longestZigZagRec(TreeNode* root, int posn) {
        if (isEmpty(root)) {
            // printf("at empty\tposn=%d\t(node=null)\t, returning (%d, (%d, %d))\n", posn, 0, 0, 0);
            return {0, {0, 0}};
        }
        else if (isLeaf(root)) {
            // printf("at leaf \tposn=%d\t(node=%d)\t, returning (%d, (%d, %d))\n", posn, root->val, 1, 1, 1);
            return {1, {1, 1}};
        }
        else {
            pair <int, pair <int, int>> lRes = longestZigZagRec(root->left, posn * 2);
            pair <int, pair <int, int>> rRes = longestZigZagRec(root->right, (posn * 2) + 1);

            int leftLongestIncludingRoot = lRes.second.second + 1;
            int rightLongestIncludingRoot = rRes.second.first + 1;
            int longestIncludingRoot = max(leftLongestIncludingRoot, rightLongestIncludingRoot);

            int longestCurrSubtree = max(max(lRes.first, rRes.first), longestIncludingRoot);

            pair <int, pair <int, int>> crrRes = {
                longestCurrSubtree, {leftLongestIncludingRoot, rightLongestIncludingRoot}
            };
            // printf("at \t\t\tposn=%d\t(node=%d)\t, returning (%d, (%d, %d))\n", posn, root->val, crrRes.first, crrRes.second.first, crrRes.second.second);
            return crrRes;
        }
    }

    pair <int, pair <int, int>> longestZigZagRec(TreeNode* root) {
        if (isEmpty(root)) {
            return {0, {0, 0}};
        }
        else if (isLeaf(root)) {
            return {1, {1, 1}};
        }
        else {
            pair <int, pair <int, int>> lRes = longestZigZagRec(root->left);
            pair <int, pair <int, int>> rRes = longestZigZagRec(root->right);

            int leftLongestIncludingRoot = lRes.second.second + 1;
            int rightLongestIncludingRoot = rRes.second.first + 1;
            int longestIncludingRoot = max(leftLongestIncludingRoot, rightLongestIncludingRoot);

            int longestCurrSubtree = max(max(lRes.first, rRes.first), longestIncludingRoot);

            pair <int, pair <int, int>> crrRes = {
                longestCurrSubtree, {leftLongestIncludingRoot, rightLongestIncludingRoot}
            };
            return crrRes;
        }
    }

public:
    int longestZigZag(TreeNode* root) {
        pair <int, pair <int, int>> res = longestZigZagRec(root);
        return max(0, res.first - 1);
    }
};
