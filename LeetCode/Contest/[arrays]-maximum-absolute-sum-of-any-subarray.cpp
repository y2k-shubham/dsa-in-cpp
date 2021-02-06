// BiWeekly Contest-45 (Feb 2021): https://leetcode.com/contest/biweekly-contest-45/problems/maximum-absolute-sum-of-any-subarray/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maxSubArrSumKadanes(vector<int>& vec) {
        int maxSum = 0;

        int crrSum = 0;
        for (int i = 0; i < vec.size(); i++) {
            int crrEle = vec[i];

            crrSum += crrEle;
            if (crrSum < 0) {
                crrSum = 0;
            } else {
                maxSum = max(maxSum, crrSum);
            }
        }

        return maxSum;
    }

    void invertSigns(vector<int>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            vec[i] = -vec[i];
        }
    }

    int maxAbsoluteSum(vector<int>& nums) {
        int s1 = maxSubArrSumKadanes(nums);

        invertSigns(nums);
        int s2 = maxSubArrSumKadanes(nums);

        return max(s1, s2);
    }
};
