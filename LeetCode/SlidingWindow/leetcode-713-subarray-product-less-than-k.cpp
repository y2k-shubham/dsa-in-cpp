// LeetCode-713: https://leetcode.com/problems/subarray-product-less-than-k/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int sigmaN(int n) {
        return (n * (n + 1)) / 2;
    }

   public:
    // soln takes from LeetCode itself (Solution section)
    // (appears absurdly simple)
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int len = nums.size();
        if (len <= 0) {
            return 0;
        }
        // dont understand this expression
        if (k <= 1) {
            return 0;
        }

        int totalNumSubarrs = 0;

        int crrSubarrProd = 1;
        int iLo = 0, iHi = 0;
        while (iHi < len) {
            crrSubarrProd *= nums[iHi];

            while (crrSubarrProd >= k) {
                crrSubarrProd /= nums[iLo++];
            }

            int numSubarrsEndingAtIHi = (iLo <= iHi) ? (iHi - iLo + 1) : 0;
            totalNumSubarrs += numSubarrsEndingAtIHi;

            iHi++;
        }

        return totalNumSubarrs;
    }
};
