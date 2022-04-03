// LeetCode-930: https://leetcode.com/problems/binary-subarrays-with-sum/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int numSubarraysWithSum(vector<int>& nums, int goal) {
        unordered_map<int, int> prefSumNumIdxsMap;
        prefSumNumIdxsMap[0] = 1;

        int numSubArrs = 0;

        int crrSum = 0;
        for (int i = 0; i < nums.size(); i++) {
            crrSum += nums[i];

            int diff = crrSum - goal;
            if (prefSumNumIdxsMap.find(diff) != prefSumNumIdxsMap.end()) {
                numSubArrs += prefSumNumIdxsMap[diff];
            }

            prefSumNumIdxsMap[crrSum]++;
        }

        return numSubArrs;
    }
};
