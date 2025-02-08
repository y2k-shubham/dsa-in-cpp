// LeetCode-2341: https://leetcode.com/problems/maximum-number-of-pairs-in-array/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map <int, int> createFreqMap(vector <int>& vec) {
        unordered_map <int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

public:
    vector <int> numberOfPairs(vector <int>& nums) {
        unordered_map <int, int> freqMap = createFreqMap(nums);

        int numPairsRemoved = 0;
        int numElesRemaining = 0;

        for (auto it : freqMap) {
            int freq = it.second;

            numPairsRemoved += freq >> 1;
            numElesRemaining += freq & 1;
        }

        return {numPairsRemoved, numElesRemaining};
    }
};
