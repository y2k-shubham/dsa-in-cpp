// LeetCode-523: https://leetcode.com/problems/continuous-subarray-sum/
// (solved after seeing Editorial)

// Solution is based on properties of modulo-arithmetic:
// very difficult to solve by oneself unless one has been apprised of the logic in advance

#include <cassert>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> remainderFirstIdx = {{0, -1}};

        int currentRemainder = 0;
        for (int i = 0; i < nums.size(); i++) {
            currentRemainder = (currentRemainder + nums[i]) % k;

            if (remainderFirstIdx.find(currentRemainder) != remainderFirstIdx.end()) {
                if (i - remainderFirstIdx[currentRemainder] > 1) {
                    return true;
                }
            } else {
                remainderFirstIdx[currentRemainder] = i;
            }
        }

        return false;
    }
};

class SolutionTest {
public:
    void testCheckSubarraySum() {
        Solution soln = Solution();
        vector<int> vecIn;
        int kIn;
        bool outExpected, outComputed;

        vecIn = {23, 2, 4, 6, 7};
        kIn = 6;
        outExpected = true;
        outComputed = soln.checkSubarraySum(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {23, 2, 6, 4, 7};
        kIn = 6;
        outExpected = true;
        outComputed = soln.checkSubarraySum(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {23, 2, 6, 4, 7};
        kIn = 13;
        outExpected = false;
        outComputed = soln.checkSubarraySum(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {1, 5, 2, 1, 5, 2, 1, 3};
        kIn = 5;
        outExpected = true;
        outComputed = soln.checkSubarraySum(vecIn, kIn);
        assert(outExpected == outComputed);

        printf("[testCheckSubarraySum] All test-cases passed!\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCheckSubarraySum();

    return 0;
}
