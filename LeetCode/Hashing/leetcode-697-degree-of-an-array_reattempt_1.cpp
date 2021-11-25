// LeetCode-697: https://leetcode.com/problems/degree-of-an-array/
// NickWhite: https://www.youtube.com/watch?v=7wT5sFELf7Q
// quite optimal soln; but still only 20 %tile speed & 50 %tile memory

#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   public:
    int findShortestSubArray(vector<int>& nums) {
        unordered_map<int, int> eleFreqMap;
        unordered_map<int, pair<int, int> > eleEdgeIdxsMap;  // first & last occurences

        int maxFreq = 0;
        for (int i = 0; i < nums.size(); i++) {
            int crrEle = nums[i];

            // determine frequency of element
            int crrFreq = eleFreqMap[crrEle];
            int newFreq = crrFreq + 1;

            // update frequency of element
            eleFreqMap[crrEle] = newFreq;
            // update max frequency of all elements
            maxFreq = max(maxFreq, newFreq);

            // update edge indexes of current element
            if (newFreq == 1) {
                eleEdgeIdxsMap[crrEle] = {i, i};
            } else {
                eleEdgeIdxsMap[crrEle].second = i;
            }
        }

        if (maxFreq == 1) {
            return 1;
        }

        // iterate over entire frequency map and for every element having freq equal to maxFreq,
        // determine the span of window containing it's first & last occurence
        int shortestWinLen = nums.size();
        for (unordered_map<int, int>::iterator it = eleFreqMap.begin(); it != eleFreqMap.end(); it++) {
            int ele = it->first;
            int freq = it->second;

            if (freq == maxFreq) {
                pair<int, int> edgeIdxs = eleEdgeIdxsMap[ele];
                int crrEleWinLen = edgeIdxs.second - edgeIdxs.first + 1;
                shortestWinLen = min(shortestWinLen, crrEleWinLen);
            }
        }

        return shortestWinLen;
    }
};
