// LeetCode-18: https://leetcode.com/problems/4sum
// https://www.interviewbit.com/problems/4-sum/
// https://www.geeksforgeeks.org/find-four-numbers-with-sum-equal-to-given-sum/
// Time: O(n^3), Space: O(1) [plus whatever sorting takes]

// this problem is solvable in O(n^2logn) as discussed in https://www.geeksforgeeks.org/find-four-elements-that-sum-to-a-given-value-set-2/

#include <algorithm>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        int len = nums.size();

        vector<vector<int>> quads;
        for (int i = 0; i < len - 3; i++) {
            // skip over duplicates so that we never pick two same values in nums[i]
            if ((i > 0) && (nums[i] == nums[i - 1])) {
                continue;
            }

            for (int j = i + 1; j < len - 2; j++) {
                if ((j > i + 1) && (nums[j] == nums[j - 1])) {
                    // skip over duplicates so that we never pick two same values in nums[j] for a given nums[i]
                    continue;
                }

                // caching
                int ijSum = nums[i] + nums[j];
                int klReqSum = target - (nums[i] + nums[j]);

                int k = j + 1;
                int l = len - 1;
                while (k < l) {
                    int klSum = nums[k] + nums[l];

                    // find and update 4sum result
                    int crrSum = ijSum + klSum;
                    if (crrSum == target) {
                        quads.push_back({nums[i], nums[j], nums[k], nums[l]});
                    }

                    // decide whether to advance k or decrement l or both
                    bool incK = false;
                    bool decL = false;
                    if (klSum < klReqSum) {
                        incK = true;
                    } else if (klSum == klReqSum) {
                        incK = true;
                        decL = true;
                    } else {
                        decL = true;
                    }

                    if (incK) {
                        // increase k until we are rid of duplicates (for current values of nums[i] & nums[j])
                        k++;
                        while (k < l && nums[k] == nums[k - 1]) {
                            k++;
                        }
                    }

                    if (decL) {
                        // decrease l until we are rid of duplicates (for current values of nums[i] & nums[j])
                        l--;
                        while (k < l && nums[l] == nums[l + 1]) {
                            l--;
                        }
                    }
                }
            }
        }

        return quads;
    }
};
