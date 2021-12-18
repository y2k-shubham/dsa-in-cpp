// LeetCode-713: https://leetcode.com/problems/subarray-product-less-than-k/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
   private:
    int sigmaN(int n) {
        return (n * (n + 1)) / 2;
    }

   public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int len = nums.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return (nums[0] < k) ? 1 : 0;
        }
        if (k == 0) {
            return 0;
        }

        int totalNumSubarrs = 0;

        int iLo = 0;
        int iHi = 0;
        int crrWinProd = 1;
        while (iHi < len) {
            // keep expanding window until product is less than k
            crrWinProd *= nums[iHi];

            if (crrWinProd >= k) {
                int prevWinSize = iHi - 1 - iLo + 1;
                int prevWinNumSubarrs = sigmaN(prevWinSize);
                totalNumSubarrs += prevWinNumSubarrs;
                printf(
                    "nums[%d]=%d .. nums[%d]=%d; prod=%d, prevWinSize=%d, prevNumSubarrs=%d, totalNumSubarrs=%d\n",
                    iLo, nums[iLo],
                    iHi, nums[iHi],
                    crrWinProd,
                    prevWinSize,
                    prevWinNumSubarrs,
                    totalNumSubarrs);

                // keep shrinking window until product is greater than or equal to k
                while ((iLo <= iHi) && (crrWinProd >= k)) {
                    crrWinProd /= nums[iLo];
                    iLo++;
                }
            }

            iHi++;
        }

        return totalNumSubarrs;
    }
};
