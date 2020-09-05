// LeetCode-16: https://leetcode.com/problems/3sum-closest/
// https://www.geeksforgeeks.org/find-a-triplet-in-an-array-whose-sum-is-closest-to-a-given-number/

#include <algorithm>
#include <climits>
#include <cmath>
#include <vector>

using namespace std;

class Solution {
   public:
    int threeSumClosest(vector<int>& nums, int targetSum) {
        sort(nums.begin(), nums.end());
        int len = nums.size();

        int closestSum = -1;
        int closestSumDiff = INT_MAX;

        for (int i = 0; i < len - 2; i++) {
            int remSum = targetSum - nums[i];

            // now here we perform 2sum search (for remSum) on the subarray [i+1 .. <end>]
            int j = i + 1;
            int k = len - 1;
            while (j < k) {
                int crrRemSum = nums[j] + nums[k];

                // find the current triplet's sum and update the 'closestSum' if possible
                int crrSum = crrRemSum + nums[i];
                int crrSumDiff = abs(crrSum - targetSum);
                if (crrSumDiff < closestSumDiff) {
                    if (crrSumDiff == 0) {
                      // if current triplets sum is equal to target sum, then return
                      // (because the sum can't be any more closer)
                        return targetSum;
                    }

                    closestSum = crrSum;
                    closestSumDiff = crrSumDiff;
                }

                // note that here we are essentially performing 2sum search on the subarray [i+1 .. <end>]
                if (crrRemSum < remSum) {
                    j++;
                } else {
                    // greater rather than greater than or equal to
                    // (because equality will be handled in crrSumDiff == 0 expression)
                    --k;
                }
            }
        }

        return closestSum;
    }
};
