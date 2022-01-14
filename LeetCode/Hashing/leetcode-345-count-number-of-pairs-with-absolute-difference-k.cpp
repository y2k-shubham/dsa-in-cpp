// LeetCode-345: https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int countKDifference(vector<int>& nums, int k) {
        unordered_map<int, int> freqMap;

        int numPairs = 0;
        for (int i = 0; i < nums.size(); i++) {
            int crrVal = nums[i];

            numPairs += freqMap[crrVal - k];
            numPairs += freqMap[k + crrVal];

            freqMap[crrVal]++;
        }

        return numPairs;
    }
};
