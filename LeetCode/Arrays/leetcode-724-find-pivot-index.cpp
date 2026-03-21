// LeetCode-724: https://leetcode.com/problems/find-pivot-index/
// Identical to LeetCode-1991: https://leetcode.com/problems/find-the-middle-index-in-array/

#include <numeric>
#include <vector>

using namespace std;

class Solution {
public:
    int pivotIndex(vector<int>& nums) {
        int len = nums.size();
        if (len <= 0) {
            return -1;
        }
        if (len == 1) {
            return 0;
        }

        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        int leftSum = 0;
        int rightSum = totalSum - nums[0];
        for (int i = 0; i < len; i++) {
            if (leftSum == rightSum) {
                return i;
            }

            leftSum += nums[i];
            if (i + 1 < len) {
                rightSum -= nums[i + 1];
            }
        }

        return -1;
    }
};
