// LeetCode-503: https://leetcode.com/problems/next-greater-element-ii/
// NickWhite: https://www.youtube.com/watch?v=ARkl69eBzhY

#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildDoubleLenVec(vector<int>& vec) {
        int len = vec.size();
        int srcIdx, dstIdx;

        vector<int> doubleLenVec(2 * len);

        // 1st copy into first half
        srcIdx = 0, dstIdx = 0;
        while (srcIdx < len) {
            doubleLenVec[dstIdx++] = vec[srcIdx++];
        }

        // 2nd copy into second half
        srcIdx = 0, dstIdx = len;
        while (srcIdx < len) {
            doubleLenVec[dstIdx++] = vec[srcIdx++];
        }

        return doubleLenVec;
    }

    vector<int> buildNgeRightCircular(vector<int>& doubleLenVec) {
        int doubleLen = doubleLenVec.size();
        vector<int> doubleLenNgeIdx(doubleLen, -1);

        int len = doubleLen / 2;

        stack<int> stk;
        for (int i = doubleLen - 1; i >= 0; i--) {
            int crrEle = doubleLenVec[i];

            while (!stk.empty() && (stk.top() <= crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                doubleLenNgeIdx[i] = stk.top();
            }

            stk.push(crrEle);
        }

        return doubleLenNgeIdx;
    }

    vector<int> extractHalfVec(vector<int>& doubleLenVec) {
        int doubleLen = doubleLenVec.size();
        int len = doubleLen / 2;

        vector<int> vec(doubleLenVec.begin(), doubleLenVec.begin() + len);
        return vec;
    }

   public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        vector<int> doubleLenVec = buildDoubleLenVec(nums);
        vector<int> doubleLenNgeRightCircular = buildNgeRightCircular(doubleLenVec);
        vector<int> ngeRightCircular = extractHalfVec(doubleLenNgeRightCircular);

        return ngeRightCircular;
    }
};
