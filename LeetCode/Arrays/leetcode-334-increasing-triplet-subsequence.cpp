// LeetCode-334: https://leetcode.com/problems/increasing-triplet-subsequence/
// Solution: https://www.youtube.com/watch?v=HB9BJMNuiCs
// https://www.geeksforgeeks.org/find-a-sorted-subsequence-of-size-3-in-linear-time/

/**
 * @file leetcode-334-increasing-triplet-subsequence.cpp
 * @author y2k-shubham (Shubham Gupta)
 * @brief find an increasing subsequence of length 3 (triplet) in O(n) time & O(1) space
 * - very difficult problem (i still don't understand it)
 * - operations are quite similar to what we do in determining the 2nd smallest
 *   element in array
 * @date 2020-09-27
 */

#include <climits>
#include <cmath>
#include <vector>

using namespace std;

bool increasingTriplet(vector<int>& nums) {
    int len = nums.size();

    if (len < 3) {
        return false;
    } else {
        int left = INT_MAX;
        int mid = INT_MAX;

        for (int i = 0; i < len; i++) {
            int ele = nums[i];

            // re-ordering these 3 expressions also works fine
            if (mid < ele) {
                // ele greater than mid
                // we found 3 elements such that left < mid < ele
                return true;

                /**
                 * in following else-if expression
                 * 1. first part (left < ele) is redundant (kept for clarity)
                 * 2. in second part (ele <= mid) equality is necessary
                 *    which is understandable because otherwise we'll end up in
                 *    else clause and update left instead of updating mid)
                 */
            } else if (left < ele && ele <= mid) {
                // ele between left and mid
                mid = ele;
            } else {
                // ele less than left
                left = ele;
            }
        }

        return false;
    }
}
