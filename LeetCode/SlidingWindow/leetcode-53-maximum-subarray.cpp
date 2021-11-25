// LeetCode-53: https://leetcode.com/problems/maximum-subarray/

#include <climits>
#include <cmath>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = INT_MIN;
        int crrSum = 0;

        int i = 0;
        while (i < nums.size()) {
            int crrEle = nums[i];

            crrSum += crrEle;

            maxSum = max(maxSum, crrSum);
            crrSum = max(0, crrSum);

            i++;
        }

        return maxSum;
    }
};
