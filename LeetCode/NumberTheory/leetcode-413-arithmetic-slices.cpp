// LeetCode-413: https://leetcode.com/problems/arithmetic-slices/
// GFG: https://www.geeksforgeeks.org/count-the-arithmetic-sequences-in-the-array-of-size-at-least-3/

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int numberOfArithmeticSlices(vector<int>& A) {
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
};
