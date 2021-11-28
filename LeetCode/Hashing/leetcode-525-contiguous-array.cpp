// LeetCode-525: https://leetcode.com/problems/contiguous-array/
// not super easy to come up with this rather simple, familiar approach

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int findMaxLength(vector<int>& nums) {
        unordered_map<int, int> prefSumFirstIdxMap;
        prefSumFirstIdxMap[0] = -1;

        int longestSubArrLen = 0;
        int sum = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += (nums[i] == 1) ? 1 : -1;

            if (prefSumFirstIdxMap.find(sum) != prefSumFirstIdxMap.end()) {
                int crrSubArrLen = i - prefSumFirstIdxMap[sum];
                longestSubArrLen = max(longestSubArrLen, crrSubArrLen);
            } else {
                prefSumFirstIdxMap[sum] = i;
            }
        }

        return longestSubArrLen;
    }
};
