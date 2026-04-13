// LeetCode-1848: https://leetcode.com/problems/minimum-distance-to-the-target-element

#include <vector>
#include <climits>
#include <cmath>

using namespace std;

class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int len = nums.size();
        if (len <= 1) {
            return len - 1;
        }

        int minDiff = INT_MAX;
        for (int i = 0; i < len; i++) {
            if (nums[i] == target) {
                int crrDiff = abs(i - start);
                if (crrDiff < minDiff) {
                    minDiff = crrDiff;
                }
            }
        }

        return minDiff;
    }
};
