// LeetCode-2150: https://leetcode.com/problems/find-all-lonely-numbers-in-the-array/
// dumb proble; dont bother looking

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<int, int> buildFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    bool isLonely(unordered_map<int, int>& freqMap, int num) {
        int numFreq = freqMap[num];
        bool numPrevExists = freqMap.find(num - 1) != freqMap.end();
        bool numNextExists = freqMap.find(num + 1) != freqMap.end();

        return (numFreq == 1) && !numPrevExists && !numNextExists;
    }

    vector<int> findLonelyNums(vector<int>& vec, unordered_map<int, int>& freqMap) {
        vector<int> lonelyNums;

        for (int i = 0; i < vec.size(); i++) {
            if (isLonely(freqMap, vec[i])) {
                lonelyNums.push_back(vec[i]);
            }
        }

        return lonelyNums;
    }

   public:
    vector<int> findLonely(vector<int>& nums) {
        unordered_map<int, int> freqMap = buildFreqMap(nums);
        return findLonelyNums(nums, freqMap);
    }
};
