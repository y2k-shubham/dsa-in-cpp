// LeetCode-513: https://leetcode.com/problems/find-bottom-left-tree-value/

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

pair<pair<int, int>, int> findBottomLeftValRec(TreeNode* root, int row, int col) {
    if (root == nullptr) {
        return {{-1, -1}, -1};
    } else if (root->left == nullptr && root->right == nullptr) {
        return {{row, col}, root->val};
    } else {
        pair<pair<int, int>, int> lRes = findBottomLeftValRec(root->left, row + 1, col - 1);
        pair<pair<int, int>, int> rRes = findBottomLeftValRec(root->right, row + 1, col + 1);

        int maxRow = max(lRes.first.first, rRes.first.first);
        if (maxRow <= 0) {
            return {{row, col}, root->val};
        } else {
            if (lRes.first.first > rRes.first.first) {
                return lRes;
            } else if (lRes.first.first == rRes.first.first) {
                if (lRes.first.second <= rRes.first.second) {
                    return lRes;
                } else {
                    return rRes;
                }
            } else {
                return rRes;
            }
        }
    }
}

int findBottomLeftValue(TreeNode* root) {
    pair<pair<int, int>, int> res = findBottomLeftValRec(root, 1, 0);
    return res.second;
}
