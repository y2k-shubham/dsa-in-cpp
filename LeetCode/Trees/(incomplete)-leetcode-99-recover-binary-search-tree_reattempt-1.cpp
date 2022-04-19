// LeetCode-99: https://leetcode.com/problems/recover-binary-search-tree/
// optimized 3-pointer approach taken from https://www.geeksforgeeks.org/fix-two-swapped-nodes-of-bst/
// incomplete soln

#include <cstdio>
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
    void findSwappedPointers(
            TreeNode *crr,
            TreeNode *prev,
            TreeNode **ptrFirst,
            TreeNode **ptrMid,
            TreeNode **ptrLast
    ) {
        if (crr == nullptr) {
            return;
        }

        findSwappedPointers(crr->left, prev, ptrFirst, ptrMid, ptrLast);

        if ((prev != nullptr) && (prev->val > crr->val)) {
            if (ptrFirst == nullptr) {
                ptrFirst = &prev;
                ptrMid = &crr;
                printf("found 1st violation, setting ptrFirst=%d, ptrMid=%d\n", (*ptrFirst)->val, (*ptrMid)->val);
            } else {
                ptrLast = &crr;
                printf("found 2nd violation, setting ptrLast=%d\n", (*ptrLast)->val);
            }
        }

        findSwappedPointers(crr->right, crr, ptrFirst, ptrMid, ptrLast);
    }

    void showPtrs(
            TreeNode *ptrFirst,
            TreeNode *ptrMid,
            TreeNode *ptrLast
    ) {
        cout << "ptrFirst=" << ((ptrFirst == nullptr) ? "null" : to_string(ptrFirst->val)) << endl;
        cout << "ptrMid=" << ((ptrMid == nullptr) ? "null" : to_string(ptrMid->val)) << endl;
        cout << "ptrLast=" << ((ptrLast == nullptr) ? "null" : to_string(ptrLast->val)) << endl;
    }

    void swapNodes(TreeNode *node1, TreeNode *node2) {
        int tmp = node1->val;
        node1->val = node2->val;
        node2->val = tmp;
    }

    void swapNodes(
            TreeNode *ptrFirst,
            TreeNode *ptrMid,
            TreeNode *ptrLast
    ) {
        if ((ptrFirst == nullptr) && (ptrMid == nullptr) && (ptrLast == nullptr)) {
            return;
        }

        if (ptrLast == nullptr) {
            swapNodes(ptrFirst, ptrMid);
        } else {
            swapNodes(ptrMid, ptrLast);
        }
    }

public:
    void recoverTree(TreeNode *root) {
        TreeNode *prev = nullptr;
        TreeNode **ptrFirst = nullptr;
        TreeNode **ptrMid = nullptr;
        TreeNode **ptrLast = nullptr;

        findSwappedPointers(root, prev, ptrFirst, ptrMid, ptrLast);

        TreeNode *ptrFirst1 = (ptrFirst == nullptr) ? nullptr : *ptrFirst;
        TreeNode *ptrMid1 = (ptrMid == nullptr) ? nullptr : *ptrMid;
        TreeNode *ptrLast1 = (ptrLast == nullptr) ? nullptr : *ptrLast;

        showPtrs(ptrFirst1, ptrMid1, ptrLast1);

        swapNodes(ptrFirst1, ptrMid1, ptrLast1);
    }
};
