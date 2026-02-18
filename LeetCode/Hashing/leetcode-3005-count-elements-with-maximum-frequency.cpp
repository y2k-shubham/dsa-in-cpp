// LeetCode-3005: https://leetcode.com/problems/count-elements-with-maximum-frequency/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    pair<unordered_map<int, int>, int> getFreqMapAndMaxFreq(vector<int>& vec) {
        unordered_map<int, int> freqMap;
        int maxFreq = 0;

        for (auto it = vec.begin(); it != vec.end(); it++) {
            int val = *it;

            // int crrFreq = freqMap[val];                            // Runtime 3 ms
            int crrFreq = freqMap.count(val) ? freqMap.at(val) : 0;   // Runtime 4 ms
            int updatedFreq = crrFreq + 1;

            freqMap[val] = updatedFreq;

            maxFreq = max(maxFreq, updatedFreq);
        }

        return {freqMap, maxFreq};
    }

    int countItemsWithFreq(unordered_map<int, int>& freqMap, int freq) {
        int numItems = 0;
        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            if (it->second == freq) {
                ++numItems;
            }
        }

        return numItems;
    }

public:
    int maxFrequencyElements(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return len;
        }

        pair<unordered_map<int, int>, int> freqMapAndMaxFreq = getFreqMapAndMaxFreq(nums);
        unordered_map<int, int> freqMap = freqMapAndMaxFreq.first;
        int maxFreq = freqMapAndMaxFreq.second;

        int numItemsWithMaxFreq = countItemsWithFreq(freqMap, maxFreq);
        int sumOfFreqOfItemsWithMaxFreq = maxFreq * numItemsWithMaxFreq;

        return sumOfFreqOfItemsWithMaxFreq;
    }
};
