// LeetCode-1856: https://leetcode.com/problems/maximum-subarray-min-product/

#include <cstdio>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

#define MOD 1000000007

class Solution {
   private:
    vector<int> buildNleLeftIdxVec(vector<int>& vec) {
        int len = vec.size();

        stack<int> stk;
        vector<int> nleLeftIdxVec(len, -1);
        for (int i = 0; i < len; i++) {
            int crrEle = vec[i];

            while (!stk.empty() && (vec[stk.top()] >= crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                nleLeftIdxVec[i] = stk.top();
            }

            stk.push(i);
        }

        return nleLeftIdxVec;
    }

    vector<int> buildNleRightIdxVec(vector<int>& vec) {
        int len = vec.size();

        stack<int> stk;
        vector<int> nleRightIdxVec(len, len);
        for (int i = len - 1; i >= 0; i--) {
            int crrEle = vec[i];

            while (!stk.empty() && (vec[stk.top()] >= crrEle)) {
                stk.pop();
            }

            if (!stk.empty()) {
                nleRightIdxVec[i] = stk.top();
            }

            stk.push(i);
        }

        return nleRightIdxVec;
    }

    vector<long long> buildPrefixSumVec(vector<int>& vec) {
        int len = vec.size();

        vector<long long> prefixSumVec(len, 0);
        prefixSumVec[0] = vec[0];
        for (int i = 1; i < len; i++) {
            prefixSumVec[i] = prefixSumVec[i - 1] + vec[i];
        }

        return prefixSumVec;
    }

    int calcMaxMinProd(
        vector<int>& vec,
        vector<int>& nleLeftIdxVec,
        vector<int>& nleRightIdxVec,
        vector<long long>& prefixSumVec) {
        int len = vec.size();

        long long maxMinProd = 0;
        for (int i = 0; i < len; i++) {
            int nleLeftIdx = nleLeftIdxVec[i];
            int nleRightIdx = nleRightIdxVec[i];

            // - here we are taking that (longest) subarray for which current-element: vec[i] will be the minimum element
            // - when we do this for every element of array, we get the overall max min prod
            long long subArrSum = prefixSumVec[nleRightIdx - 1] - ((nleLeftIdx >= 0) ? prefixSumVec[nleLeftIdx] : 0);
            int subArrMin = vec[i];

            long long crrMinProd = subArrSum * subArrMin;
            maxMinProd = max(maxMinProd, crrMinProd);
        }

        return (int)(maxMinProd % MOD);
    }

   public:
    int maxSumMinProduct(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) {
            return (int)((((long long)nums[0]) * nums[0]) % MOD);
        }

        vector<int> nleLeftIdxVec = buildNleLeftIdxVec(nums);
        vector<int> nleRightIdxVec = buildNleRightIdxVec(nums);
        vector<long long> prefixSumVec = buildPrefixSumVec(nums);

        return calcMaxMinProd(
            nums,
            nleLeftIdxVec,
            nleRightIdxVec,
            prefixSumVec);
    }
};
