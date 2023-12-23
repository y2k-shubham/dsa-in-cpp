// LeetCode-2419: https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and

#include <vector>

using namespace std;

class Solution {
private:
    int findMaxEle(vector<int>& vec) {
        return *max_element(vec.begin(), vec.end());
    }

    int findMaxSubarrayOfEle(vector<int>& vec, int ele) {
        int maxSubarrayLen = 0;

        int crrSubarrayLen = 0;
        for (int i = 0; i < vec.size(); i++) {
            int crrEle = vec[i];
            if (crrEle == ele) {
                crrSubarrayLen++;
                maxSubarrayLen = max(maxSubarrayLen, crrSubarrayLen);
            } else {
                crrSubarrayLen = 0;
            }
        }

        return maxSubarrayLen;
    }

public:
    int longestSubarray(vector<int>& nums) {
        int maxEle = findMaxEle(nums);
        return findMaxSubarrayOfEle(nums, maxEle);
    }
};

