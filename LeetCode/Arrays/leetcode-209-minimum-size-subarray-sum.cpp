// LeetCode-209: https://leetcode.com/problems/minimum-size-subarray-sum/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int findShortestWindowWithTargetSum(vector<int>& vec, int targetSum) {
        int len = vec.size();
        int minWindowSize = INT_MAX;

        int i = 0;
        int j = 0;
        int crrSum = vec[0];
        while ((j < len) && (i < len)) {
            if (crrSum >= targetSum) {
                int crrWindowSize = j - i + 1;
                minWindowSize = min(minWindowSize, crrWindowSize);
                // decrease window
                crrSum -= vec[i];
                i++;
            } else {
                // increase window
                j++;
                if (j < len) {
                    crrSum += vec[j];
                }
            }
        }

        if (minWindowSize == INT_MAX) {
            return 0;
        }

        return minWindowSize;
    }

   public:
    int minSubArrayLen(int target, vector<int>& nums) {
        return findShortestWindowWithTargetSum(nums, target);
    }
};
