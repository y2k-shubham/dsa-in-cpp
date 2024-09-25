// LeetCode-918: https://leetcode.com/problems/maximum-sum-circular-subarray/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int maxSubarraySumKadanes(vector<int>& vec) {
        int len = vec.size();

        int maxSum = vec[0];  // IMPORTANT: initialize with first ele and NOT with zero
        int crrSum = 0;
        for (int i = 0; i < len; i++) {
            int crrEle = vec[i % len];
            crrSum += crrEle;

            // IMPORTANT: note that we take max before setting crrSum to zero
            // this ensures that in an array containing all -ve nums, the
            // one with smallest absolute value gets picked
            maxSum = max(maxSum, crrSum);
            if (crrSum < 0) {
                crrSum = 0;
            }
        }

        return maxSum;
    }

    vector<int> buildPrefixSum(vector<int>& vec) {
        int len = vec.size();

        vector<int> prefSum(len);

        prefSum[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefSum[i] = prefSum[i - 1] + vec[i];
        }

        return prefSum;
    }

    vector<int> buildSuffixSum(vector<int>& vec) {
        int len = vec.size();

        vector<int> suffSum(len);

        suffSum[len - 1] = vec[len - 1];
        for (int i = len - 2; i >= 0; i--) {
            suffSum[i] = suffSum[i + 1] + vec[i];
        }

        return suffSum;
    }

    vector<int> buildPrefixMaxVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> prefMaxVec(len);

        prefMaxVec[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefMaxVec[i] = max(prefMaxVec[i - 1], vec[i]);
        }

        return prefMaxVec;
    }

    vector<int> buildSuffixMaxVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> suffMaxVec(len);

        suffMaxVec[len - 1] = vec[len - 1];
        for (int i = len - 2; i >= 0; i--) {
            suffMaxVec[i] = max(suffMaxVec[i + 1], vec[i]);
        }

        return suffMaxVec;
    }

    int maxWraparoundSubarraySum(vector<int>& vec) {
        vector<int> prefSum = buildPrefixSum(vec);
        vector<int> suffSum = buildSuffixSum(vec);

        vector<int> prefMaxSum = buildPrefixMaxVec(prefSum);
        vector<int> suffMaxSum = buildSuffixMaxVec(suffSum);

        int len = vec.size();
        int maxSum = vec[0];  // IMPORTANT: initialize with first ele and NOT with zero
        for (int i = -1; i < len; i++) {
            int prefSumContrib = (i < 0) ? 0 : prefMaxSum[i];
            int suffSumContrib = (i == (len - 1)) ? 0 : suffMaxSum[i + 1];

            int crrSum = prefSumContrib + suffSumContrib;
            maxSum = max(maxSum, crrSum);
        }

        return maxSum;
    }

   public:
    int maxSubarraySumCircular(vector<int>& nums) {
        return max(
            maxSubarraySumKadanes(nums),
            maxWraparoundSubarraySum(nums));
    }
};
