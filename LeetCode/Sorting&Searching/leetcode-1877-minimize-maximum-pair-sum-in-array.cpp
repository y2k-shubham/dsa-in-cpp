// LeetCode-1877: https://leetcode.com/problems/minimize-maximum-pair-sum-in-array/
// straight-forward dumb, greedy problem (can skip)

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int len = nums.size();
        int halfLen = len / 2;

        int maxSum = INT_MIN;
        for (int i = 0; i < halfLen; i++) {
            int crrSum = nums[i] + nums[len - i - 1];
            maxSum = max(maxSum, crrSum);
        }

        return maxSum;
    }
};
