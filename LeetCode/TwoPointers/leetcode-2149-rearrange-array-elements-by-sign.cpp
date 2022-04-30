// LeetCode-2149: https://leetcode.com/problems/rearrange-array-elements-by-sign///

// can't be solved without O(n) extra space
// and with extra space, it is too lame a problem to see

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) {
            return nums;
        }

        vector<int> rearrangedNums(len);

        int iPositive = 0;
        int iNegative = 1;
        for (int i = 0; i < len; i++) {
            int ele = nums[i];

            if (ele >= 0) {
                rearrangedNums[iPositive] = ele;
                iPositive += 2;
            } else {
                rearrangedNums[iNegative] = ele;
                iNegative += 2;
            }
        }

        return rearrangedNums;
    }
};
