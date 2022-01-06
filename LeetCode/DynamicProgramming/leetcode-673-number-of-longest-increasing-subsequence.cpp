// LeetCode-673: https://leetcode.com/problems/number-of-longest-increasing-subsequence/

/**
 * input
 * [1,3,5,4,7]
 * output
 * 2
 *
 * input
 * [2,2,2,2,2]
 * output
 * 5
 *
 * input
 * [8,1,3,7,4,2,9]
 * output
 * 2
 *
 * input
 * [9,4,1,5,5,4,0,3,3,0]
 * output
 * 9
 *
 * input
 * [8,1,3,7,4,2,9,9,4,1,5,5,4,0,3,3,0]
 * output
 * 10
 *
 * input
 * [8,1,3,7,4,2,9,9,4,1,5,5,4,0,3,3,0,8,4,4,7,4,8,5,7,7,9]
 * output
 * 22
 * 
 */

#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   public:
    int findNumberOfLIS(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return len;
        }

        // populate lis vector along with frequencies
        vector<pair<int, int> > lisVec(len, {1, 1});
        int lisLen = 1;
        for (int i = 1; i < len; i++) {
            int crrVal = nums[i];
            pair<int, int> crrValLis = lisVec[i];

            for (int j = 0; j < i; j++) {
                if (nums[j] < crrVal) {
                    // found an increasing subseq

                    pair<int, int> prevValLis = lisVec[j];

                    if ((prevValLis.first + 1) == crrValLis.first) {
                        // subseq length equal to the one we have already found,
                        // just update the frequency
                        crrValLis.second += prevValLis.second;
                    } else if ((prevValLis.first + 1) > crrValLis.first) {
                        // we found a subseq of longer length,
                        // reset it's frequency (to the frequency of prevLis)
                        crrValLis.first = crrValLis.first + 1;
                        crrValLis.second = prevValLis.second;
                    }
                }
            }

            // persist lis for current value
            lisVec[i] = crrValLis;

            // update length of lis
            lisLen = max(lisLen, crrValLis.first);
        }

        // count no of increasing subseqs having length lisLen
        int freq = 0;
        for (int i = 0; i < len; i++) {
            if (lisVec[i].first == lisLen) {
                freq += lisVec[i].second;
            }
        }

        return freq;
    }
};
