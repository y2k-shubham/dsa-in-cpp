// LeetCode-1856: https://leetcode.com/problems/maximum-subarray-min-product/

/**
 * input
 * [1]
 * output
 * 1
 * 
 * input
 * [2]
 * output
 * 4
 * 
 * input
 * [3]
 * output
 * 9
 * 
 * input
 * [1,2]
 * output
 * 4
 * 
 * input
 * [1,1]
 * output
 * 2
 * 
 * input
 * [2,2]
 * output
 * 8
 * 
 * input
 * [1,3,1]
 * output
 * 9
 * 
 * input
 * [1,2,3,2]
 * output
 * 14
 * 
 * input
 * [2,3,3,1,2]
 * output
 * 18
 * 
 * input
 * [3,1,5,6,4,2]
 * output
 * 60
 * 
 * input
 * [18,69,23,33,48,46,9,65,2,81,60,15,8,85,55,30,72,78,79,31,80,25,77,63,100,68,95,71,67,97,40,6,61,1,24,42,91,32,52,37,26,59,83,16,20,19,43,17,35,51,47,36,92,27,89,76,98,7,66,11,28,99,39,73,56,4,88,87,12,75,86,90,96,44,82,14,34,41,3,38,5,10,58,21,29,84,74,62,13,93,70,45,49,64,53,22,54,94,57,50,10000000,9999999,9999998,9999997,9999996,9999995,9999994,9999993,9999992,9999991,9999990,9999989,9999988,9999987,9999986,9999985,9999984,9999983,9999982,9999981,9999980,9999979,9999978,9999977,9999976,9999975,9999974,9999973,9999972,9999971,9999970,9999969,9999968,9999967,9999966,9999965,9999964,9999963,9999962,9999961,9999960,9999959,9999958,9999957,9999956,9999955,9999954,9999953,9999952,9999951,9999950,9999949,9999948,9999947,9999946,9999945,9999944,9999943,9999942,9999941,9999940,9999939,9999938,9999937,9999936,9999935,9999934,9999933,9999932,9999931,9999930,9999929,9999928,9999927,9999926,9999925,9999924,9999923,9999922,9999921,9999920,9999919,9999918,9999917,9999916,9999915,9999914,9999913,99...
 * output
 * 631781618
 */

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
