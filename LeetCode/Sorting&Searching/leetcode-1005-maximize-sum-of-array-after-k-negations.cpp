// LeetCode-1005: https://leetcode.com/problems/maximize-sum-of-array-after-k-negations/
// not as easy as it seems (more like medium)

#include <vector>
#include <numeric>

using namespace std;

class Solution {
private:
    inline int calcSum(vector<int>& vec) {
        return accumulate(vec.begin(), vec.end(), 0);
    }

public:
    int largestSumAfterKNegations(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());

        if (nums[0] >= 0) {
            if ((k % 2) == 0) {
                // we'll pick any one element and keep toggling it b/w positve & negative
                // and it will eventually end up in positive only
                return calcSum(nums);
            } else {
                // we'll keep toggling first element b/w positive & negative
                // and it'll eventually end up negative
                return calcSum(nums) - (2 * nums[0]);
            }
        }

        bool negativeElesFound = false;
        int i = 0;
        while ((i < nums.size()) && (nums[i] <= 0) && (k > 0)) {
            negativeElesFound = true;
            nums[i] *= -1;
            i++;
            k--;
        }

        if (k == 0) {
            return calcSum(nums);
        }

        if ((k % 2) == 0) {
            // again we can pick any element and keep toggling it b/w positive & negative
            // till we consume remaining 'k' so that sum of array will remain unchanged
            return calcSum(nums);
        } else {
            // sort array again to obtain the smallest element by absolute value
            if (negativeElesFound) {
                sort(nums.begin(), nums.end());
            }

            // we'll keep toggling first element b/w positive & negative
            // and it'll eventually end up negative
            return calcSum(nums) - (2 * nums[0]);
        }
    }
};
