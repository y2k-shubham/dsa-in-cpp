// LeetCode-594: https://leetcode.com/problems/longest-harmonious-subsequence/
// Feb-2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3628/

/**
 * this question can also be solved by creating an ordered hashmap of frequencies
 * and then iterating over that map pair-wise
 * 
 * that soln has been added in 'Hashing' package (but is inferior in speed)
 */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
   public:
    map<int, int> prepareFreqMap(vector<int>& vec) {
        map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            int ele = vec[i];
            freqMap[ele]++;
        }

        return freqMap;
    }

    // LC-submission: speed 99 %tile
    int findLHSLen2(vector <int>& vec) {
        int len = vec.size();
        sort(vec.begin(), vec.end());

        int maxConseqSeqLen = 0;

        int prevNum = INT_MIN;
        int prevSeqLen = -1;
        
        int i = 0;
        while (i < len) {
            int crrNum = vec[i];
            int crrSeqLen = 0;
            while ((i < len) && (vec[i] == crrNum)) {
                i++;
                crrSeqLen++;
            }

            if ((prevNum != INT_MIN) && ((prevNum + 1) == crrNum)) {
                maxConseqSeqLen = max(maxConseqSeqLen, (prevSeqLen + crrSeqLen));
            }

            prevNum = crrNum;
            prevSeqLen = crrSeqLen;
        }

        return maxConseqSeqLen;
    }

    int findLHSLen2Caller(vector <int>& nums) {
        return findLHSLen2(nums);
    }

    int findLHS(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return 0;
        }

        return findLHSLen2Caller(nums);
    }
};
