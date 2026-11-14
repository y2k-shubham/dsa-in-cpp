// LeetCode-3364: https://leetcode.com/problems/minimum-positive-sum-subarray/

#include <vector>

using namespace std;

class Solution {
private:
    vector <int> createPrefixSum(vector <int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector <int> prefixSumVec(len, 0);
        prefixSumVec[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefixSumVec[i] = prefixSumVec[i - 1] + vec[i];
        }

        return prefixSumVec;
    }

    int calculateMinSubarraySumInLength(vector<int>& prefixSumVec, int subArrLen) {
        int vecLen = prefixSumVec.size();
        int minSubArrSum = INT_MAX;

        for (int iLo = 0, iHi = subArrLen - 1; iHi < vecLen; iLo++, iHi++) {
            int crrSubArrSum = prefixSumVec[iHi] - ((iLo == 0) ? 0 : prefixSumVec[iLo - 1]);
            if (crrSubArrSum > 0) {
                minSubArrSum = min(minSubArrSum, crrSubArrSum);
            }
        }

        return minSubArrSum;
    }

    int calculateMinSubarraySumInLengthRange(
        vector<int>& prefixSumVec,
        int minSubArrLen,
        int maxSubArrLen) {
        int len = prefixSumVec.size();
        int minSubArrSum = INT_MAX;
        for (int subArrLen = minSubArrLen; subArrLen <= maxSubArrLen; subArrLen++) {
            int crrLenSubArrSum = calculateMinSubarraySumInLength(prefixSumVec, subArrLen);
            if (crrLenSubArrSum > 0) {
                minSubArrSum = min(minSubArrSum, crrLenSubArrSum);
            }
        }

        return minSubArrSum;
    }

public:
    int minimumSumSubarray(vector<int>& nums, int l, int r) {
        int len = nums.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return nums[0];
        }

        vector <int> prefixSumVec = createPrefixSum(nums);
        int minSubArrSum = calculateMinSubarraySumInLengthRange(prefixSumVec, l, r);

        if (minSubArrSum == INT_MAX) {
            return -1;
        } else {
            return minSubArrSum;
        }
    }
};
