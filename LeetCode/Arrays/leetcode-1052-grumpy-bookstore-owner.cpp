// LeetCode-1052: https://leetcode.com/problems/grumpy-bookstore-owner/submissions/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildGrumpyPrefixSumVec(vector<int>& customers, vector<int>& grumpy) {
        int len = customers.size();

        vector<int> prefixSumVec(len, 0);
        for (int i = 0; i < len; i++) {
            int addend1 = (i == 0) ? 0 : prefixSumVec[i - 1];
            int addend2 = (grumpy[i] == 1) ? customers[i] : 0;
            prefixSumVec[i] = addend1 + addend2;
        }

        return prefixSumVec;
    }

    int calcNonGrumpySum(vector<int>& customers, vector<int>& grumpy) {
        int sum = 0;

        for (int i = 0; i < grumpy.size(); i++) {
            if (grumpy[i] == 0) {
                sum += customers[i];
            }
        }

        return sum;
    }

    int calcMaxGrumpyWindowSum(vector<int>& prefixSum, int winLen) {
        int maxWindowSum = 0;

        for (int i = 0; (i + winLen - 1) < prefixSum.size(); i++) {
            int winBeginPrevSum = (i == 0) ? 0 : prefixSum[i - 1];
            int winEndSum = prefixSum[i + winLen - 1];

            int crrWindowSum = winEndSum - winBeginPrevSum;
            maxWindowSum = max(maxWindowSum, crrWindowSum);
        }

        return maxWindowSum;
    }

   public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int minutes) {
        int nonGrumpySum = calcNonGrumpySum(customers, grumpy);

        vector<int> prefixSum = buildGrumpyPrefixSumVec(customers, grumpy);
        int maxGrumpyWindowSum = calcMaxGrumpyWindowSum(prefixSum, minutes);

        return nonGrumpySum + maxGrumpyWindowSum;
    }
};
