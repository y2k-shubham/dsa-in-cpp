// LeetCode-80: https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int removeDuplicates(vector<int>& nums) {
    int len = nums.size();

    if (len <= 2) {
        return len;
    } else {
        int prevVal = INT_MIN;

        int lo = 0;
        int hi = 0;
        while (hi < len) {
            if (nums[hi] == prevVal) {
                hi++;
            } else {
                prevVal = nums[hi];
                if ((hi < len - 1) && (nums[hi] == nums[hi + 1])) {
                    nums[lo] = nums[lo + 1] = nums[hi];
                    lo += 2;
                    hi += 2;
                } else {
                    nums[lo] = nums[hi];
                    lo++;
                    hi++;
                }
            }
        }

        return lo;
    }
}