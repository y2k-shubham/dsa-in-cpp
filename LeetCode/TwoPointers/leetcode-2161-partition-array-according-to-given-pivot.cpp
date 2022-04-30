// LeetCode-2161: https://leetcode.com/problems/partition-array-according-to-given-pivot/

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> pivotArray(vector<int>& nums, int pivot) {
        int len = nums.size();
        if (len <= 1) {
            return nums;
        }

        vector<int> rearrangedNums(len);

        int iLo = -1;
        for (int i = 0; i < len; i++) {
            int ele = nums[i];
            if (ele < pivot) {
                rearrangedNums[++iLo] = ele;
            }
        }

        int iHi = len;
        for (int i = len - 1; i >= 0; i--) {
            int ele = nums[i];
            if (pivot < ele) {
                rearrangedNums[--iHi] = ele;
            }
        }

        iLo++;
        while (iLo < iHi) {
            rearrangedNums[iLo++] = pivot;
        }

        return rearrangedNums;
    }
};
