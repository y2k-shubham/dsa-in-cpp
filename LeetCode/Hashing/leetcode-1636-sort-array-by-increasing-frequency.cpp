// LeetCode-1636: https://leetcode.com/problems/sort-array-by-increasing-frequency/

#include <vector>
#include <unordered_map>
#include <utility>
#include <algorithm>

using namespace std;

class Solution {
private:
    unordered_map <int, int> createFreqMap(vector <int>& vec) {
        unordered_map <int, int> freqMap;

        for (int val : vec) {
            freqMap[val]++;
        }

        return freqMap;
    }

    vector <pair <int, int>> convertToTupleVec(unordered_map <int, int>& freqMap) {
        vector <pair <int, int>> tupleVec;

        for (auto it : freqMap) {
            tupleVec.push_back({it.second, -it.first});
        }

        return tupleVec;
    }

    vector <int> convertToVec(vector <pair <int, int>>& freqValVec) {
        vector <int> vec;

        for (auto mPair : freqValVec) {
            int freq = mPair.first;
            int val = mPair.second;

            for (int i = 1; i <= freq; i++) {
                vec.push_back(-val);
            }
        }

        return vec;
    }

public:
    vector <int> frequencySort(vector <int>& nums) {
        unordered_map <int, int> freqMap = createFreqMap(nums);

        vector <pair <int, int>> freqValVec = convertToTupleVec(freqMap);
        sort(freqValVec.begin(), freqValVec.end());

        return convertToVec(freqValVec);
    }
};
