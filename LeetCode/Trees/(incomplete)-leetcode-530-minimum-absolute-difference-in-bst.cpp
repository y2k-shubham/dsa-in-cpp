// LeetCode-530: https://leetcode.com/problems/minimum-absolute-difference-in-bst/
// incomplete: running into some kind of AddressSanitizer error

#include <cstdio>
#include <iostream>
#include <utility>
#include <cmath>
#include <cassert>
#include <tuple>
#include <climits>

using namespace std;

#define INF_POSITIVE 999999999
#define INF_NEGATIVE 999999999

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
    int minus(int a, int b) {
        if (a == b) {
            return 0;
        } else if (a == INF_NEGATIVE) {
            return INF_NEGATIVE;
        } else if (b == INF_POSITIVE) {
            return INF_POSITIVE;
        } else {
            return a - b;
        }
        return abs(a - b);
    }

    tuple<int, int, int> findMinDiffRec(TreeNode *root) {
        if (root == nullptr) {
            return {INF_POSITIVE, INF_NEGATIVE, INF_POSITIVE};
        }

        auto leftRes = findMinDiffRec(root->left);
        auto rightRes = findMinDiffRec(root->right);

        int crrMinDiffLeft = abs(minus(root->val, get<1>(leftRes)));
        int crrMinDiffRight = abs(minus(root->val, get<0>(rightRes)));

        int minDiffLeftSubtree = get<2>(leftRes);
        int minDiffRightSubtree = get<2>(rightRes);

        int minValCrrSubtree = min(get<0>(leftRes), root->val);
        int maxValCrrSubtree = max(get<1>(rightRes), root->val);

        return {
                minValCrrSubtree,
                maxValCrrSubtree,
                min({crrMinDiffLeft, crrMinDiffRight, minDiffLeftSubtree, minDiffRightSubtree})
        };
    }

public:
    int getMinimumDifference(TreeNode *root) {
        return get<2>(findMinDiffRec(root));
    }
};

