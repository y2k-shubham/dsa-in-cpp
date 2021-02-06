// LeetCode-594: https://leetcode.com/problems/longest-harmonious-subsequence/
// Feb-2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3628/

/**
 * (observation without assertion)
 * this question can also be solved by simply sorting the array
 * and scanning windows (two pointer approach)
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

    // LC-submission: speed 90 %tile
    int findLHSLen1(map<int, int>& freqMap) {
        int maxSubseqLen = 0;

        map<int, int>::iterator it1 = freqMap.begin();
        map<int, int>::iterator it2 = freqMap.begin();
        it2++;

        // iterate over freq-map in pairs (two vals at a time)
        while (it2 != freqMap.end()) {
            pair<int, int> valFreqP1 = {(*it1).first, (*it1).second};
            pair<int, int> valFreqP2 = {(*it2).first, (*it2).second};

            // if diff b/w vals is 1
            if ((valFreqP2.first - valFreqP1.first) == 1) {
                // then having a subseq comprising only these two vals will give us a total subseq length
                // equal to sum of frequencies of both vals
                int crrSubseqLen = valFreqP1.second + valFreqP2.second;
                // and then we take the max
                maxSubseqLen = max(maxSubseqLen, crrSubseqLen);
            }

            it1++;
            it2++;
        }

        return maxSubseqLen;
    }

    int findLHSLen1Caller(vector <int>& nums) {
        map<int, int> freqMap = prepareFreqMap(nums);
        if (freqMap.size() == 1) {
            return 0;
        }

        return findLHSLen1(freqMap);
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