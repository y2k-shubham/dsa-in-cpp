// LeetCode-594: https://leetcode.com/problems/longest-harmonious-subsequence/
// Feb-2021 challenge: https://leetcode.com/explore/challenge/card/february-leetcoding-challenge-2021/584/week-1-february-1st-february-7th/3628/

/**
 * this question can also be solved by simply sorting the array
 * and scanning windows (two pointer approach)
 * 
 * that soln has been added in 'Sorting&Searching' package (and is more performant)
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

    int findLHS(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return 0;
        }

        return findLHSLen1Caller(nums);
    }
};
