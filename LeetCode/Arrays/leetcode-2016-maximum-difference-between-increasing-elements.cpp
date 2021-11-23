// LeetCode-2016: https://leetcode.com/problems/maximum-difference-between-increasing-elements/
// pretty dumb proble; should skip looking

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int maximumDifference(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) {
            return -1;
        }

        int maxDiffSoFar = -1;
        int maxValSoFar = -1;
        for (int i = len - 1; i >= 0; i--) {
            int crrVal = nums[i];
            if (crrVal < maxValSoFar) {
                int crrDiff = maxValSoFar - crrVal;
                maxDiffSoFar = max(maxDiffSoFar, crrDiff);
            }

            maxValSoFar = max(maxValSoFar, crrVal);
        }

        return maxDiffSoFar;
    }
};
