// LeetCode-413: https://leetcode.com/problems/arithmetic-slices/
// LC Feb 2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/586/week-3-february-15th-february-21st/3644/
// GFG: https://www.geeksforgeeks.org/count-the-arithmetic-sequences-in-the-array-of-size-at-least-3/

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    /////////////////
    // 1st attempt //
    /////////////////

    int numberOfArithmeticSlices1(vector<int>& A) {
        int len = A.size();

        if (len <= 2) {
            return 0;
        }

        int numSlices = 0;

        int startInd = -1;
        int prevDiff = INT_MIN;
        for (int i = 1; i < len; i++) {
            int crrDiff = A[i] - A[i - 1];

            if (crrDiff == prevDiff) {
                if (startInd == -1) {
                    startInd = i - 2;
                    numSlices = numSlices + 1;
                } else {
                    numSlices = numSlices + (i - startInd - 1);
                }
            } else {
                startInd = -1;
            }

            prevDiff = crrDiff;
        }

        return numSlices;
    }

    /////////////////
    // 2nd attempt //
    /////////////////

    int sigmaN(int n) {
        return (n * (n + 1)) / 2;
    }

    bool isSliceBegin(vector<int>& vec, int idx) {
        int len = vec.size();
        if (idx >= (len - 2)) {
            return false;
        }

        return (vec[idx + 1] - vec[idx]) == (vec[idx + 2] - vec[idx + 1]);
    }

    int eatSlice(vector<int>& vec, int idx) {
        int len = vec.size();

        int i = idx + 1;
        int reqDiff = vec[i] - vec[i - 1];

        int crrDiff;
        while ((i < len) && ((crrDiff = vec[i] - vec[i - 1]) == reqDiff)) {
            i++;
        }

        return i - 1;
    }

    int numberOfArithmeticSlices2(vector<int>& A) {
        int len = A.size();
        if (len <= 2) {
            return 0;
        }

        int numSlices = 0;

        int i = 0;
        while (i < len) {
            if (isSliceBegin(A, i)) {
                int iBegin = i;
                int iEnd = eatSlice(A, iBegin);

                int seqLen = iEnd - iBegin + 1;
                numSlices += sigmaN(seqLen - 2);

                i = iEnd;
            } else {
                i++;
            }
        }

        return numSlices;
    }

    int numberOfArithmeticSlices(vector<int>& A) {
        return numberOfArithmeticSlices1(A);
    }
};
