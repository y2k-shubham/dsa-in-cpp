// LeetCode-1909: https://leetcode.com/problems/remove-one-element-to-make-the-array-strictly-increasing/
// GeeksForGeeks: https://www.geeksforgeeks.org/check-whether-an-array-can-be-made-strictly-increasing-by-removing-at-most-one-element/

#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    // ---- approach-1: correct, fast but very complex -----

    int getViolatingIdxFromLeft(vector <int>& vec) {
        int len = vec.size();

        for (int i = 1; i < len; i++) {
            int prev = vec[i - 1];
            int crr = vec[i];

            if (prev >= crr) {
                return i;
            }
        }

        return INT_MIN;
    }

    int getViolatingIdxFromRight(vector <int>& vec) {
        int len = vec.size();

        for (int i = len - 2; i >= 0; i--) {
            int crr = vec[i];
            int next = vec[i + 1];

            if (crr >= next) {
                return i;
            }
        }

        return INT_MIN;
    }

    bool isCorrectViolatingIdx(vector <int>& vec, int idx) {
        int len = vec.size();

        int prev = (idx >= 1) ? vec[idx - 1] : INT_MIN;
        int next = (idx <= (len - 2)) ? vec[idx + 1] : INT_MAX;

        return prev < next;
    }

    bool solnApproach_1_self(vector <int>& nums) {
        int len = nums.size();
        if (len <= 2) {
            return true;
        }

        int violatingIdxFromLeft = getViolatingIdxFromLeft(nums);
        if (violatingIdxFromLeft < 0) {
            // no violation found; original array is already strictly ascending order
            return true;
        }

        int violatingIdxFromRight = getViolatingIdxFromRight(nums);
        if ((violatingIdxFromRight + 1) != violatingIdxFromLeft) {
            // array has more than 1 violations
            return false;
        }

        return isCorrectViolatingIdx(nums, violatingIdxFromLeft)
            || isCorrectViolatingIdx(nums, violatingIdxFromRight);
    }

    // ---- approach-2: correct, fast but very easy -----

    // WRONG: current implementation has some bug, needs to be fixed
    bool solnApproach_2_GFG(vector <int>& nums) {
        int len = nums.size();
        if (len <= 2) {
            return true;
        }

        int numViolations = 0;
        for (int i = 1; i < len; i++) {
            int prev = nums[i - 1];
            int crr = nums[i];

            if (prev >= crr) {
                // we found a violation
                numViolations++;

                if (numViolations >= 2) {
                    return false;
                }
            }
        }

        return true;
    }

public:
    bool canBeIncreasing(vector <int>& nums) {
        return solnApproach_2_GFG(nums);
    }
};

class SolutionTest {
public:
    void testCanBeIncreasing() {
        Solution soln = Solution();
        vector <int> vecIn;
        bool outExpected, outComputed;

        vecIn = {1, 2, 10, 5, 7};
        outExpected = true;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 10, 1, 7};
        outExpected = false;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 3, 1, 2};
        outExpected = false;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1};
        outExpected = false;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3, 15, 2, 4, 6};
        outExpected = false;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3, 15, 4, 5, 9, 3, 20};
        outExpected = false;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3, 15, 8, 10, 12};
        outExpected = true;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3, 1, 8, 10, 12};
        outExpected = true;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);

        vecIn = {105,924,32,968};
        outExpected = true;
        outComputed = soln.canBeIncreasing(vecIn);
        assert(outExpected == outComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCanBeIncreasing();

    return 0;
}
