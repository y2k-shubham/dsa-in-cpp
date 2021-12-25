// LeetCode-1793: https://leetcode.com/problems/maximum-score-of-a-good-subarray/

// wrong soln
// - maybe it can be made to work; but why invest effort when a much easier soln already exists?
// - CherryCoding: https://www.youtube.com/watch?v=P0SA8NCKY3w
// - easy implementation is based on (almost identical to) 'largest rectangle in a histogram' leetcode-84: https://leetcode.com/problems/largest-rectangle-in-histogram/

/**
 * input
 * [1,4,3,7,4,5]
 * 3
 * output
 * 15
 *
 * input
 * [5,5,4,5,4,1,1,1]
 * 0
 * output
 * 20
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 2
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 3
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 4
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 5
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,1]
 * 6
 * output
 * 40
 *
 * input
 * [2,2,8,9,9,9,8,5,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3]
 * 3
 * output
 * 117
 *
 * input
 * [5868,4839,3608,4826,2829,2871,3224,3579,9860,6453,458,1617,2201,2906,8334,8410,3104,1385,5462,4287,2960,5417,2640,2287,6331,4494,773,1178,1426,5271,3221,7606,1091,9043,7008,7218,6004,4636,6253,5628,9533,2204,6903,6912,9736,793,8529,190,1302,4140,3212,2589,2735,109,9090,8351,332,8693,2461,6274,7233,2689,7255,3894,3855,1037,7385,3874]
 * 38
 * output
 * 37088
 */

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildMinValVec(vector<int>& vec, int k) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector<int> minValVec(len, INT_MAX);

        // from k to zero (leftwards)
        int minVal = vec[k];
        for (int i = k; i >= 0; i--) {
            minVal = min(minVal, vec[i]);
            minValVec[i] = minVal;
        }

        // from k to len-1 (rightwards)
        minVal = vec[k];
        for (int i = k; i < len; i++) {
            minVal = min(minVal, vec[i]);
            minValVec[i] = minVal;
        }

        return minValVec;
    }

    vector<int> buildMinValFreqVec(vector<int>& minValVec, int k) {
        int len = minValVec.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {1};
        }

        vector<int> minValFreqVec(len, 1);

        // from len-1 to k (inwards from right)
        for (int i = len - 2; i > k; i--) {
            if (minValVec[i] == minValVec[i + 1]) {
                minValFreqVec[i] = minValFreqVec[i + 1] + 1;
            }
        }

        // from 0 to k (inwards from left)
        for (int i = 1; i < k; i++) {
            if (minValVec[i - 1] == minValVec[i]) {
                minValFreqVec[i] = minValFreqVec[i - 1] + 1;
            }
        }

        return minValFreqVec;
    }

    int findMaxScore(
        vector<int>& vec,
        int k,
        vector<int>& minValVec,
        vector<int>& minValFreqVec) {
        int len = vec.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return vec[0];
        }

        int crrMinEle = vec[k];
        int crrScore = crrMinEle;
        int iLo = k, iHi = k;

        // eat all equal eles on left
        if ((k > 0) && (vec[k - 1] == crrMinEle)) {
            int numEqElesOnLeft = minValFreqVec[k - 1];
            iLo -= numEqElesOnLeft;
            crrScore += numEqElesOnLeft * crrMinEle;
        }
        // eat all equal eles on right
        if ((k < (len - 1)) && (crrMinEle == vec[k + 1])) {
            int numEqElesOnRight = minValFreqVec[k + 1];
            iHi += numEqElesOnRight;
            crrScore += numEqElesOnRight * crrMinEle;
        }

        int maxScore = crrScore;

        int crrSubArrLen = iHi - iLo + 1;
        while (crrSubArrLen < len) {
            int leftEle = (iLo > 0) ? minValVec[iLo - 1] : 0;
            int leftEleFreq = (iLo > 0) ? minValFreqVec[iLo - 1] : 0;
            int scoreAfterLeftExp = min(crrMinEle, leftEle) * (leftEleFreq + crrSubArrLen);

            int rightEle = (iHi < (len - 1)) ? minValVec[iHi + 1] : 0;
            int rightEleFreq = (iHi < (len - 1)) ? minValFreqVec[iHi + 1] : 0;
            int scoreAfterRightExp = min(crrMinEle, rightEle) * (rightEleFreq + crrSubArrLen);

            if (scoreAfterLeftExp > scoreAfterRightExp) {
                crrScore = scoreAfterLeftExp;
                iLo -= leftEleFreq;
                crrSubArrLen += leftEleFreq;
            } else {
                crrScore = scoreAfterRightExp;
                iHi += rightEleFreq;
                crrSubArrLen += rightEleFreq;
            }

            maxScore = max(maxScore, crrScore);
        }

        return maxScore;
    }

   public:
    int maximumScore(vector<int>& nums, int k) {
        int len = nums.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return nums[0];
        }

        vector<int> minValVec = buildMinValVec(nums, k);
        vector<int> minValFreqVec = buildMinValFreqVec(minValVec, k);

        return findMaxScore(nums, k, minValVec, minValFreqVec);
    }
};
