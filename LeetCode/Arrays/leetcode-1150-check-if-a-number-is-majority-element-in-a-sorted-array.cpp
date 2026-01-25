// LeetCode-1150: https://leetcode.com/problems/check-if-a-number-is-majority-element-in-a-sorted-array
// Not a bad question, even if easy

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool isMajorityElement(vector<int>& nums, int target) {
        auto it = lower_bound(nums.begin(), nums.end(), target);
        if ((it == nums.end()) || (*it != target)) {
            // target not found in nums
            return false;
        }

        int beginIdx = it - nums.begin();

        int len = nums.size();
        int reqMinEndIdx = beginIdx + ((int) ceil(len / 2.0f));
        if (len & 1) {
            // if odd length array, then this adjustment is required
            reqMinEndIdx--;
        }

        if ((reqMinEndIdx >= len) || (nums[reqMinEndIdx] != target)) {
            // target present in nums but not a majority element
            return false;
        }

        return true;
    }
};
