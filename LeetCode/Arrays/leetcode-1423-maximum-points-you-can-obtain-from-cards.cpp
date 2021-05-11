// LeetCode-1423: https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/599/week-2-may-8th-may-14th/3739/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildPrefixSum(vector<int>& vec) {
        int len = vec.size();

        vector<int> prefixSum(len);
        prefixSum[0] = vec[0];

        for (int i = 1; i < len; i++) {
            prefixSum[i] = prefixSum[i - 1] + vec[i];
        }

        return prefixSum;
    }

    vector<int> buildSuffixSum(vector<int>& vec) {
        int len = vec.size();

        vector<int> suffixSum(len);
        suffixSum[len - 1] = vec[len - 1];

        for (int i = len - 2; i >= 0; i--) {
            suffixSum[i] = suffixSum[i + 1] + vec[i];
        }

        return suffixSum;
    }

    int findMaxKSum(vector<int>& vec, int k) {
        bool debug = false;

        int len = vec.size();

        vector<int> prefixSum = buildPrefixSum(vec);
        vector<int> suffixSum = buildSuffixSum(vec);

        int i = k - 1;
        int j = len;
        int maxSum = 0;
        // note that i will become -1 [out of bounds]
        // (just like j was len in beginning)
        while (i >= -1) {
            int lSum = ((i >= 0) ? prefixSum[i] : 0);
            int rSum = ((j < len) ? suffixSum[j] : 0);

            int crrSum = lSum + rSum;
            maxSum = max(maxSum, crrSum);

            if (debug) {
                printf("crrSum = (prefixSum[i=%d] = %d) + (suffixSum[j=%d] = %d) = %d\n", i, lSum, j, rSum, crrSum);
            }

            i--;
            j--;
        }

        return maxSum;
    }

   public:
    int maxScore(vector<int>& cardPoints, int k) {
        int len = cardPoints.size();
        if (k >= len) {
          // sum of vector items
            return accumulate(cardPoints.begin(), cardPoints.end(), 0);
        }

        return findMaxKSum(cardPoints, k);
    }
};
