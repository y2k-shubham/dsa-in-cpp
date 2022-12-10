// LeetCode-2256: https://leetcode.com/problems/minimum-average-difference
// dumb problem, dont bother looking

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
private:
    vector <int> buildAvgRightVec(vector <int>& vec) {
        if (vec.empty()) {
            return {};
        }

        int len = vec.size();
        vector <int> avgRightVec(len, 0);

        long long sum = 0;
        for (int i = len - 1; i >= 0; i--) {
            sum += vec[i];
            avgRightVec[i] = (int) (sum / (len - i));
        }

        return avgRightVec;
    }

public:
    int minimumAverageDifference(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return 0;
        }

        int minAvgDiff = INT_MAX;
        int minAvgDiffIdx = len;

        vector <int> avgRightVec = buildAvgRightVec(nums);
        long long sum = 0;
        for (int i = 0; i < len; i++) {
            sum += nums[i];
            int avgLeft = (int) (sum / (i + 1));

            int avgRight = (i < (len - 1)) ? avgRightVec[i + 1] : 0;

            int avgDiff = abs(avgLeft - avgRight);
            if (avgDiff < minAvgDiff) {
                minAvgDiff = avgDiff;
                minAvgDiffIdx = i;
            }
        }

        return minAvgDiffIdx;
    }
};
