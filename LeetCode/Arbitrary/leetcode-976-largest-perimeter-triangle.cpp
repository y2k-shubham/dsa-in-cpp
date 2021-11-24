// LeetCode-976: https://leetcode.com/problems/largest-perimeter-triangle/
// Helper Func: https://www.youtube.com/watch?v=1dmbC4I7yZE
// definitely not an easy problem

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int len = nums.size();
        for (int i = len - 3; i >= 0; i--) {
            if ((nums[i] + nums[i + 1]) > nums[i + 2]) {
                return nums[i] + nums[i + 1] + nums[i + 2];
            }
        }

        return 0;
    }
};
