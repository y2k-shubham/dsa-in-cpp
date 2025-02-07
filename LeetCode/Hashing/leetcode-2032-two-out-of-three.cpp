// LeetCode-2023: https://leetcode.com/problems/two-out-of-three

#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Solution {
private:
    void updateFreq(
        unordered_set<int>& mSet,
        unordered_map<int, int>& freqMap) {
        for (int val: mSet) {
            freqMap[val]++;
        }
    }

    void updateFreqOfVec(
        vector<int>& vec,
        unordered_map<int, int>& freqMap) {
        unordered_set<int> mSet(vec.begin(), vec.end());
        updateFreq(mSet, freqMap);
    }

public:
    vector<int> twoOutOfThree(
        vector<int>& nums1,
        vector<int>& nums2,
        vector<int>& nums3) {
        unordered_map<int, int> freqMap;

        updateFreqOfVec(nums1, freqMap);
        updateFreqOfVec(nums2, freqMap);
        updateFreqOfVec(nums3, freqMap);

        vector<int> numsWithFreqGreaterThan2;
        for (auto it: freqMap) {
            if (it.second >= 2) {
                numsWithFreqGreaterThan2.push_back(it.first);
            }
        }

        return numsWithFreqGreaterThan2;
    }
};
