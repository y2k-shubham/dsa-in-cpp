// LeetCode-1403: https://leetcode.com/problems/minimum-subsequence-in-non-increasing-order/
// lame problem (really dont solve)

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<int> minSubsequence(vector<int>& nums) {
        int len = nums.size();
        if (len == 1) {
            return nums;
        }

        // https://stackoverflow.com/a/3221813/3679900
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        sort(nums.begin(), nums.end());

        int subseqSum = 0;
        int subseqBeginIdx = -1;

        for (int i = len - 1; i >= 0 && subseqSum <= (totalSum - subseqSum); i--) {
            subseqSum += nums[i];
            subseqBeginIdx = i;
        }

        vector<int> subseqEles(nums.begin() + subseqBeginIdx, nums.end());
        sort(subseqEles.begin(), subseqEles.end(), greater<int>());

        return subseqEles;
    }
};
