// LeetCode-1480: https://leetcode.com/problems/running-sum-of-1d-array/
// are you serious?

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> runningSum(vector<int>& nums) {
        int len = nums.size();

        vector<int> runningSumVec(len, 0);
        runningSumVec[0] = nums[0];

        for (int i = 1; i < len; i++) {
            runningSumVec[i] = runningSumVec[i - 1] + nums[i];
        }

        return runningSumVec;
    }
};
