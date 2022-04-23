// LeetCode-287: https://leetcode.com/problems/find-the-duplicate-number/
// this is just array variant of linked-list cycle-detection

#include <vector>

using namespace std;

class Solution {
private:
    int findConvergenceIndex(vector<int>& nums) {
        int len = nums.size();

        int fastI = 0;
        int slowI = 0;
        do {
            fastI = nums[nums[fastI]];
            slowI = nums[slowI];
        } while (fastI != slowI);

        return fastI;
    }

    int findDuplicateNum(vector<int>& nums, int convIdx) {
        int idx1 = 0;
        int idx2 = convIdx;

        while (idx1 != idx2) {
            idx1 = nums[idx1];
            idx2 = nums[idx2];
        }

        return idx1;
    }

public:
    int findDuplicate(vector<int>& nums) {
        int len = nums.size();
        if (len <= 2) {
            return nums[0];
        }

        int convIdx = findConvergenceIndex(nums);
        return findDuplicateNum(nums, convIdx);
    }
};

