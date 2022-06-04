// LeetCode-698: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
// NeetCode: https://www.youtube.com/watch?v=mBk4I0X46oI
// definitely not a medium problem (it's harder)

/**
 * runs into TLE for last test-case
 *
 * [4,3,2,3,5,2,1]
 * 4
 *
 * [1,2,3,4]
 * 3
 *
 * [2,2,2,2,3,4,5]
 * 4
 *
 * [6,5,9,6,3,5,1,10,4,1,4,3,9,9,3,3]
 * 9
 *
 * [3,2,1,3,6,1,4,8,10,8,9,1,7,9,8,1]
 * 9
 */

#include <vector>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    inline bool canDivide(
            vector<int>& vec,
            int targetSubsetSum,
            int k,
            vector<bool>& taken,
            int crrSubsetSum,
            int crrIdx
    ) {
        if (k == 0) {
            if (debug) {
                printf("returning true as k became 0 when crrSubsetSum=%d, crrIdx=%d\n", crrSubsetSum, crrIdx);
            }
            return true;
        }
        if (crrSubsetSum == targetSubsetSum) {
            if (debug) {
                printf("recursing further when k=%d, crrSubsetSum=%d, crrIdx=%d\n", k, crrSubsetSum, crrIdx);
            }
            return canDivide(vec, targetSubsetSum, k - 1, taken, 0, 0);
        }

        for (int i = crrIdx; i < vec.size(); i++) {
            int crrSubsetSumUpdated = crrSubsetSum + vec[i];

            if (taken[i] || (crrSubsetSumUpdated > targetSubsetSum)) {
                continue;
            }

            taken[i] = true;
            if (canDivide(vec, targetSubsetSum, k, taken, crrSubsetSumUpdated, i + 1)) {
                if (debug) {
                    printf("returning true as canDivide returned true when k=%d, crrSubsetSum=%d, crrIdx=%d\n", k,
                           crrSubsetSum, crrIdx);
                }
                return true;
            }
            taken[i] = false;
        }

        return false;
    }

public:
    friend class SolutionTest;

    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int totalSum = accumulate(nums.begin(), nums.end(), 0);
        if ((totalSum % k) != 0) {
            return false;
        }

        int targetSum = totalSum / k;
        vector<bool> taken(nums.size(), false);

        // sorting improves performance as some early pruning is done in our recursive function
        // (otherwise it is NOT functionally necessary)
        sort(nums.begin(), nums.end(), greater<int>());

        return canDivide(nums, targetSum, k, taken, 0, 0);
    }
};

class SolutionTest {
public:
    void testCanPartitionKSubsets() {
        Solution s = Solution();

        vector<int> nums = {4, 3, 2, 3, 5, 2, 1};
        assert(s.canPartitionKSubsets(nums, 4) == true);

        nums = {4, 3, 2, 3, 5, 2, 1};
        assert(s.canPartitionKSubsets(nums, 3) == false);

//        s.debug = true;
        nums = {2, 2, 2, 2, 3, 4, 5};
        assert(s.canPartitionKSubsets(nums, 4) == false);
//        s.debug = false;
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testCanPartitionKSubsets();

    return 0;
}
