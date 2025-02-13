// LeetCode-2221: https://leetcode.com/problems/find-triangular-sum-of-an-array

#include <vector>

using namespace std;

class Solution {
public:
    int triangularSum(vector <int>& nums) {
        int len = nums.size();
        if (len == 1) {
            return nums[0];
        }

        for (int i = 1; i < len; i++) {
            for (int j = 0; j < (len - i); j++) {
                nums[j] = (nums[j] + nums[j + 1]) % 10;
            }
        }

        return nums[0];
    }
};
