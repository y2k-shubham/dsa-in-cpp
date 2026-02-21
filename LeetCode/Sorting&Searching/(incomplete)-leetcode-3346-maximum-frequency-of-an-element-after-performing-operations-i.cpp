// LeetCode-3346: https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/
// incomplete / wrong

#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
private:
    unordered_map<int, int> createFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;
        for (int val : vec) {
            freqMap[val]++;
        }
        return freqMap;
    }

    int calcMaxFreqForTargetValue(
        vector<int>& vec,
        int k,
        int numOperations,
        int minVal,
        int maxVal,
        int targetVal,
        int targetValFreq) {
        // iterator to smallest value that can be converted to target
        int rangeLo = max(minVal, targetVal - k);
        vector<int>::iterator rangeLoIt = lower_bound(vec.begin(), vec.end(), rangeLo);

        // iterator to biggest value that can be converted to target (plus 1)
        int rangeHi = min(maxVal, targetVal + k);
        vector<int>::iterator rangeHiIt = upper_bound(vec.begin(), vec.end(), rangeHi);

        // total number of values that can be converted into target value (if there was no numOperations bound)
        int totalNumConvertibleVals = rangeHiIt - rangeLoIt;
        printf("for target=%d, range [lo=%d, hi=%d], numConvertibleVals=%d\n", targetVal, rangeLo, rangeHi, totalNumConvertibleVals);

        return max(min(numOperations, totalNumConvertibleVals), targetValFreq);
    }

public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int len = nums.size();

        sort(nums.begin(), nums.end());
        unordered_map<int, int> freqMap = createFreqMap(nums);

        int minVal = nums[0];
        int maxVal = nums[len - 1];

        int maxPossibleFreqOverall = 1;
        for (int targetVal = minVal; targetVal <= maxVal; targetVal++) {
            int targetValFreq = freqMap[targetVal];
            int maxPossibleFreqForCrrTarget = calcMaxFreqForTargetValue(nums, k, numOperations, minVal, maxVal, targetVal, targetValFreq);
            maxPossibleFreqOverall = max(maxPossibleFreqOverall, maxPossibleFreqForCrrTarget);
        }

        return maxPossibleFreqOverall;
    }
};
