// LeetCode-2190: https://leetcode.com/problems/most-frequent-number-following-key-in-an-array

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map <int, int> createFreqMapOfTargets(vector <int>& vec, int key) {
        unordered_map <int, int> freqMap;

        for (int i = 1; i < vec.size(); i++) {
            if (vec[i - 1] == key) {
                freqMap[vec[i]]++;
            }
        }

        return freqMap;
    }

    int getKeyWithMaxValue(unordered_map <int, int>& mMap) {
        int maxValue = -1;
        int maxValueKey;

        for (auto it : mMap) {
            if (it.second > maxValue) {
                maxValue = it.second;
                maxValueKey = it.first;
            }
        }

        return maxValueKey;
    }

public:
    int mostFrequent(vector <int>& nums, int key) {
        unordered_map <int, int> freqMapOfTargets = createFreqMapOfTargets(nums, key);
        return getKeyWithMaxValue(freqMapOfTargets);
    }
};
