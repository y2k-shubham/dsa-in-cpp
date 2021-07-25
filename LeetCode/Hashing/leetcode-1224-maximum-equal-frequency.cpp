// LeetCode-1224: https://leetcode.com/problems/maximum-equal-frequency
// there's got to be an easier / different (more optimized) way
// quite a few edge cases

#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   public:
    // LC submission: speed 18 %tile, memory 7 %tile
    int maxEqualFreq(vector<int>& nums) {
        int len = nums.size();

        unordered_map<int, int> eleFreqMap;
        map<int, unordered_set<int> > freqElesMap;

        int maxEqPrefixLen = -1;
        for (int i = 0; i < len; i++) {
            int ele = nums[i];

            int crrFreq = (eleFreqMap.find(ele) == eleFreqMap.end()) ? 0 : eleFreqMap[ele];
            int newFreq = crrFreq + 1;

            eleFreqMap[ele] = newFreq;
            freqElesMap[newFreq].insert(ele);
            if (crrFreq > 0) {
                freqElesMap[crrFreq].erase(ele);

                if (freqElesMap[crrFreq].empty()) {
                    freqElesMap.erase(crrFreq);
                }
            }

            map<int, unordered_set<int> >::reverse_iterator jMax = freqElesMap.rbegin();
            int maxFreq = jMax->first;
            int numMaxFreqEles = jMax->second.size();

            map<int, unordered_set<int> >::iterator jMin = freqElesMap.begin();
            int minFreq = jMin->first;
            int numMinFreqEles = jMin->second.size();

            int numFreqs = freqElesMap.size();
            if (numFreqs == 2) {
                int diffMaxMinFreqs = maxFreq - minFreq;
                bool freqsDiffBy1 = diffMaxMinFreqs == 1;

                //printf("at v[%d] = %d, numFreqs = 2\n", i, nums[i]);

                if ((numMaxFreqEles == 1) && freqsDiffBy1) {
                    maxEqPrefixLen = i + 1;
                } else if ((numMinFreqEles == 1) && (minFreq == 1)) {
                    maxEqPrefixLen = i + 1;
                }
            } else if (numFreqs == 1) {
                if (maxFreq == 1) {
                    maxEqPrefixLen = i + 1;
                } else if (numMaxFreqEles == 1) {
                    maxEqPrefixLen = i + 1;
                }
            }
        }

        return max(1, maxEqPrefixLen);
    }
};
