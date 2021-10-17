// LeetCode-239: https://leetcode.com/problems/sliding-window-maximum/
// we need a heap + map data-structure to solve this efficiently
// here we've just used an ordered map instead

#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int len = nums.size();

        map<int, int> freqMap;
        vector<int> windowMax;

        for (int i = 0; i < min(k, len); i++) {
            freqMap[nums[i]]++;
        }
        windowMax.push_back(freqMap.rbegin()->first);

        for (int i = k; i < len; i++) {
            int outEle = nums[i - k];
            freqMap[outEle]--;
            if (freqMap[outEle] == 0) {
                freqMap.erase(outEle);
            }

            int inEle = nums[i];
            freqMap[inEle]++;

            windowMax.push_back(freqMap.rbegin()->first);
        }

        return windowMax;
    }
};
