// LeetCode-549: https://leetcode.com/problems/binary-tree-longest-consecutive-sequence-ii

#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Result {
    public:
    int maxConsecSeqLen;
    int crrIncConsecSeqLen;
    int crrDecConsecSeqLen;

    Result(
        int maxConsecSeqLen,
        int crrIncConsecSeqLen,
        int crrDecConsecSeqLen) {
        this->maxConsecSeqLen = maxConsecSeqLen;
        this->crrIncConsecSeqLen = crrIncConsecSeqLen;
        this->crrDecConsecSeqLen = crrDecConsecSeqLen;
    }
};

class Solution {
private:
    Result EMPTY_RES = Result(0, 0, 0);
    Result UNIT_RES = Result(1, 1, 1);

    Result longestConsecRec(TreeNode* root) {
        if (root == nullptr) {
            return EMPTY_RES;
        }

        bool hasLChild = root->left != nullptr;
        bool hasRChild = root->right != nullptr;

        if (!hasLChild && !hasRChild) {
            return UNIT_RES;
        }

        // recursively get results for left and right subtrees
        Result lRes = hasLChild ? longestConsecRec(root->left) : EMPTY_RES;
        Result rRes = hasRChild ? longestConsecRec(root->right) : EMPTY_RES;

        // check if left child forms an increasing or decreasing sequence with the current node
        bool isLChildConsecInc = hasLChild ? (root->left->val == (root->val + 1)) : false;
        bool isLChildConsecDec = hasLChild ? (root->left->val == (root->val - 1)) : false;
        // check if right child forms an increasing or decreasing sequence with the curr node
        bool isRChildConsecInc = hasRChild ? (root->right->val == (root->val + 1)) : false;
        bool isRChildConsecDec = hasRChild ? (root->right->val == (root->val - 1)) : false;

        // calculate max length of increasing consecutive sequence starting from current node
        int crrIncConsecSeqLen = max(
            isLChildConsecInc ? lRes.crrIncConsecSeqLen + 1 : 1,
            isRChildConsecInc ? rRes.crrIncConsecSeqLen + 1 : 1
        );
        // calculate max length of decreasing consecutive sequence starting from current node
        int crrDecConsecSeqLen = max(
            isLChildConsecDec ? lRes.crrDecConsecSeqLen + 1 : 1,
            isRChildConsecDec ? rRes.crrDecConsecSeqLen + 1 : 1
        );
        // calculate max length of increasing or decreasing consecutive sequence starting from current node
        int crrNodeMaxConsecSeqLen = max(crrIncConsecSeqLen, crrDecConsecSeqLen);

        // calculate length of consecutive sequence 'bending' at current node
        int crrNodeBendingConsecSeqLen = max(
            (isLChildConsecInc && isRChildConsecDec) ? (lRes.crrIncConsecSeqLen + rRes.crrDecConsecSeqLen + 1) : 1,
            (isLChildConsecDec && isRChildConsecInc) ? (lRes.crrDecConsecSeqLen + rRes.crrIncConsecSeqLen + 1) : 1
        );
        // calculate max length of consecutive sequences in either of left or right subtrees
        int crrSubtreeMaxConsecSeqLen = max(
            max(crrNodeBendingConsecSeqLen, crrNodeMaxConsecSeqLen),
            max(lRes.maxConsecSeqLen, rRes.maxConsecSeqLen)
        );

        // build and return overall result
        Result crrRes = Result(
            crrSubtreeMaxConsecSeqLen,
            crrIncConsecSeqLen,
            crrDecConsecSeqLen
        );
        return crrRes;
    }

public:
    int longestConsecutive(TreeNode* root) {
        Result result = longestConsecRec(root);
        return result.maxConsecSeqLen;
    }
};

