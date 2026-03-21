// LeetCode-2670: https://leetcode.com/problems/find-the-distinct-difference-array/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> createFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;

        for (int ele : vec) {
            freqMap[ele]++;
        }

        return freqMap;
    }

    void removeEleFromFreqMap(unordered_map<int, int>& freqMap, int ele) {
        freqMap[ele]--;
        if (freqMap[ele] == 0) {
            freqMap.erase(ele);
        }
    }

public:
    vector<int> distinctDifferenceArray(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) {
            return {};
        }
        if (len == 1) {
            return {1};
        }


        unordered_map<int, int> leftFreqMap = {};
        unordered_map<int, int> overallFreqMap = createFreqMap(nums);
        unordered_map<int, int> rightFreqMap = overallFreqMap;

        vector<int> diffVec(len);
        for (int i = 0; i < len; i++) {
            leftFreqMap[nums[i]]++;
            removeEleFromFreqMap(rightFreqMap, nums[i]);

            int numUniqueElesLeft = leftFreqMap.size();
            int numUniqueElesRight = rightFreqMap.size();

            diffVec[i] = numUniqueElesLeft - numUniqueElesRight;
        }

        return diffVec;
    }
};
