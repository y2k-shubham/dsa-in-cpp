// LeetCode-2090: https://leetcode.com/problems/k-radius-subarray-averages/
// straightforward do-as-directed question; dont bother looking

#include <vector>
#include <cassert>
#include <numeric>

using namespace std;

class Solution {
private:
    long long sumFirstNEles(const std::vector<int>& vec, int n) {
        return accumulate(vec.begin(), vec.begin() + min(n, static_cast<int>(vec.size())), 0L);
    }

public:
    friend class SolutionTest;

    vector<int> getAverages(vector<int>& nums, int k) {
        if (k == 0) {
            return nums;
        }

        int lenVec = nums.size();
        vector<int> numsKWindowAvg(lenVec, -1);

        int lenWindow = (2 * k) + 1;
        if (lenVec < lenWindow) {
            return numsKWindowAvg;
        }

        long long crrSum = sumFirstNEles(nums, lenWindow);
        numsKWindowAvg[k] = (int) (crrSum / lenWindow);

        for (int i = (k + 1); i < (lenVec - k); i++) {
            crrSum -= nums[i - k - 1];
            crrSum += nums[i + k];

            numsKWindowAvg[i] = (int) (crrSum / lenWindow);
        }

        return numsKWindowAvg;
    }
};

class SolutionTest {
public:
    void testGetAverages() {
        Solution soln = Solution();

        vector<int> nums;
        int k;
        vector<int> expected;
        vector<int> computed;

        nums = {7, 4, 3, 9, 1, 8, 5, 2, 6};

        k = 3;
        expected = {-1, -1, -1, 5, 4, 4, -1, -1, -1};
        computed = soln.getAverages(nums, k);
        assert(expected == computed);

        k = 4;
        expected = {-1, -1, -1, -1, 5, -1, -1, -1, -1};
        computed = soln.getAverages(nums, k);
        assert(expected == computed);

        k = 5;
        expected = {-1, -1, -1, -1, -1, -1, -1, -1, -1};
        computed = soln.getAverages(nums, k);
        assert(expected == computed);

        nums = {100000};
        k = 0;
        expected = {100000};
        computed = soln.getAverages(nums, k);
        assert(expected == computed);

        nums = {8};
        k = 100000;
        expected = {-1};
        computed = soln.getAverages(nums, k);
        assert(expected == computed);

        printf("[testGetAverages] All test-cases passed\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testGetAverages();

    return 0;
}
