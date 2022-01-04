// LeetCode-1493: https://leetcode.com/problems/longest-subarray-of-1s-after-deleting-one-element/

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<int, int> buildFreqMap(vector<int>& vec) {
        unordered_map<int, int> eleFreqMap;
        for (int i = 0; i < vec.size(); i++) {
            eleFreqMap[vec[i]]++;
        }

        return eleFreqMap;
    }

    vector<int> buildCont1sPrefixSum(vector<int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector<int> prefSum(len, 0);
        for (int i = 0; i < len; i++) {
            if (vec[i] == 1) {
                int prevPrefSum = (i > 0) ? prefSum[i - 1] : 0;
                prefSum[i] = prevPrefSum + 1;
            }
        }

        return prefSum;
    }

    vector<int> buildCont1sSuffixSum(vector<int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector<int> suffSum(len, 0);
        for (int i = len - 1; i >= 0; i--) {
            if (vec[i] == 1) {
                int nextSuffSum = (i == (len - 1)) ? 0 : suffSum[i + 1];
                suffSum[i] = nextSuffSum + 1;
            }
        }

        return suffSum;
    }

    int findLongestCont1sAfterOneDel(
        vector<int>& vec,
        vector<int>& prefSum,
        vector<int>& suffSum) {
        int len = vec.size();

        int max1sSubarrLen = 0;
        for (int i = 0; i < len; i++) {
            /**
             * we perform this only in case we are reading a zero;
             * as performing this for a 1 is (almost) redundant since
             * (as long as there's at least one 0 in input array), we would never actually delete a 1
             */
            if (vec[i] == 0) {
                int prevPrefSum = (i > 0) ? prefSum[i - 1] : 0;
                int nextSuffSum = (i == (len - 1)) ? 0 : suffSum[i + 1];

                int crr1sSubarrLen = prevPrefSum + nextSuffSum;
                max1sSubarrLen = max(max1sSubarrLen, crr1sSubarrLen);
            }
        }

        return max1sSubarrLen;
    }

   public:
    int longestSubarray(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return 0;
        }

        unordered_map<int, int> freqMap = buildFreqMap(nums);

        bool hasAll1s = freqMap[1] == len;
        if (hasAll1s) {
            return len - 1;
        }

        bool hasAll0s = freqMap[0] == len;
        if (hasAll0s) {
            return 0;
        }

        vector<int> prefSum = buildCont1sPrefixSum(nums);
        vector<int> suffSum = buildCont1sSuffixSum(nums);

        return findLongestCont1sAfterOneDel(nums, prefSum, suffSum);
    }
};
