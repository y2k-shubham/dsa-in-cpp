// LeetCode-255: https://leetcode.com/problems/verify-preorder-sequence-in-binary-search-tree
// Premium
// Companies: [Expedia]

#include <vector>
#include <stack>

using namespace std;

class PreOrderSubtreeValidationResult {
private:
    bool isValid;
    int minVal;
    int maxVal;

public:
    PreOrderSubtreeValidationResult(
        bool isValid,
        int minVal,
        int maxVal) {
        this->isValid = isValid;
        this->minVal = minVal;
        this->maxVal = maxVal;
    }

    // ------- getters --------

    bool getIsValid() {
        return isValid;
    }

    int getMinVal() {
        return minVal;
    }

    int getMaxVal() {
        return maxVal;
    }

    bool isEmptySubtree() {
        return (getMinVal() == INT_MIN) && (getMaxVal() == INT_MAX);
    }

    static PreOrderSubtreeValidationResult invalidSubtreeValidationResult() {
        return PreOrderSubtreeValidationResult(false, INT_MAX, INT_MIN);
    }

    static PreOrderSubtreeValidationResult emptySubtreeValidationResult() {
        return PreOrderSubtreeValidationResult(true, INT_MIN, INT_MAX);
    }
};

class Solution {
private:
    vector <int> createNgeRightVec(vector <int>& vec) {
        stack <pair<int, int>> stk;

        int len = vec.size();
        vector <int> ngeRightIdxVec(len);

        for (int i = len - 1; i >= 0; i--) {
            int crrVal = vec[i];

            while (!stk.empty() && (stk.top().second <= crrVal)) {
                stk.pop();
            }

            pair <int, int> ngeRightIdxVal = stk.empty() ? make_pair(INT_MAX, INT_MIN) : stk.top();
            ngeRightIdxVec[i] = ngeRightIdxVal.first;

            stk.push(make_pair(i, crrVal));
        }

        return ngeRightIdxVec;
    }

    void showVec(vector <int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        printf("\n");
    }

    PreOrderSubtreeValidationResult verifyPreorderRec(
        vector<int>& preorder,
        vector<int>& ngeRightIdxVec,
        int lo,
        int hi) {
        int totalLen = preorder.size();
        hi = min(hi, totalLen - 1);

        int evalLen = hi - lo + 1;
        if (evalLen <= 0) {
            // empty subtree
            return PreOrderSubtreeValidationResult::emptySubtreeValidationResult();
        }

        int crrVal = preorder[lo];
        if (evalLen == 1) {
            // single value subtree
            return PreOrderSubtreeValidationResult(true, crrVal, crrVal);
        }
        if (evalLen == 2) {
            // two-value subtree
            int otherVal = preorder[hi];
            int minVal = min(crrVal, otherVal);
            int maxVal = max(crrVal, otherVal);
            return PreOrderSubtreeValidationResult(true, minVal, maxVal);
        }

        int ngeRightIdx = ngeRightIdxVec[lo];

        // get left subtree validation result
        PreOrderSubtreeValidationResult lRes = verifyPreorderRec(preorder, ngeRightIdxVec, lo + 1, ngeRightIdx - 1);
        bool isLSubtreeValidAndCompatible = lRes.getIsValid() && (lRes.getMaxVal() < crrVal);

        // get right subtree validation result
        PreOrderSubtreeValidationResult rRes = verifyPreorderRec(preorder, ngeRightIdxVec, ngeRightIdx, hi);
        bool isRSubtreeValidAndCompatible = rRes.getIsValid() && (rRes.getMinVal() > crrVal);

        if (!lRes.getIsValid() || !rRes.getIsValid()) {
            return PreOrderSubtreeValidationResult::invalidSubtreeValidationResult();
        } else if (lRes.isEmptySubtree() && rRes.isEmptySubtree()) {
            return PreOrderSubtreeValidationResult(true, crrVal, crrVal);
        } else if (lRes.isEmptySubtree() && isRSubtreeValidAndCompatible) {
            return PreOrderSubtreeValidationResult(true, crrVal, rRes.getMaxVal());
        } else if (rRes.isEmptySubtree() && isLSubtreeValidAndCompatible) {
            return PreOrderSubtreeValidationResult(true, lRes.getMinVal(), crrVal);
        } else if (isLSubtreeValidAndCompatible && isRSubtreeValidAndCompatible) {
            return PreOrderSubtreeValidationResult(true, lRes.getMinVal(), rRes.getMaxVal());
        } else {
            return PreOrderSubtreeValidationResult::invalidSubtreeValidationResult();
        }
    }

public:
    bool verifyPreorder(vector<int>& preorder) {
        int len = preorder.size();
        if (len <= 1) {
            return true;
        }

        vector <int> ngeRightIdxVec = createNgeRightVec(preorder);
        // showVec(ngeRightIdxVec, "ngeRightIdxVec");

        PreOrderSubtreeValidationResult res = verifyPreorderRec(preorder, ngeRightIdxVec, 0, len - 1);
        return res.getIsValid();
    }
};
