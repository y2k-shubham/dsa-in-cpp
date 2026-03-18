// LeetCode-2270: https://leetcode.com/problems/number-of-ways-to-split-array/

#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    int waysToSplitArray(vector<int>& nums) {
        int len = nums.size();

        long long totalSum = accumulate(nums.begin(), nums.end(), 0L);
        long long leftSum = nums[0];
        long long rightSum = totalSum - leftSum;

        int numWays = (leftSum >= rightSum) ? 1 : 0;
        for (int i = 1; i < len - 1; i++) {
            leftSum += nums[i];
            rightSum -= nums[i];

            if (leftSum >= rightSum) {
                numWays++;
            }
        }

        return numWays;
    }
};
