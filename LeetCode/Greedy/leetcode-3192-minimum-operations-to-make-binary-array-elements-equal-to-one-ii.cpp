// LeetCode-3192: https://leetcode.com/problems/minimum-operations-to-make-binary-array-elements-equal-to-one-ii/

#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    int swallowNums(vector <int>& vec, int numToSwallow, int startIdx) {
        for (int i = startIdx; i >= 0; i--) {
            if (vec[i] != numToSwallow) {
                return i;
            }
        }

        return -1;
    }

public:
    friend class SolutionTest;

    int minOperations(vector <int>& nums) {
        int len = nums.size();

        int numFlips = 0;
        int i = len - 1;
        bool haveSeen1s = false;
        while (i >= 0) {
            int iNew = swallowNums(nums, 0, i);
            if (iNew != i) {
                numFlips += haveSeen1s ? 2 : 1;
            }

            i = iNew;

            iNew = swallowNums(nums, 1, i);
            if (iNew != i) {
                haveSeen1s = true;
            }

            i = iNew;
        }

        return numFlips;
    }
};

class SolutionTest {
public:
    void testMinOperations() {
        Solution soln = Solution();
        vector <int> vecIn;
        int minOperationsOutExpected, minOperationsOutComputed;

        vecIn = {0, 1, 1, 0, 1};
        minOperationsOutExpected = 4;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {1, 0, 0, 0};
        minOperationsOutExpected = 1;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {0, 1, 0, 0, 0};
        minOperationsOutExpected = 3;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {0, 0, 0, 1, 0, 0, 0};
        minOperationsOutExpected = 3;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {1, 1, 1, 0, 0, 0, 1, 0, 0, 0};
        minOperationsOutExpected = 3;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0};
        minOperationsOutExpected = 5;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {1};
        minOperationsOutExpected = 0;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {1, 1, 1, 1, 1};
        minOperationsOutExpected = 0;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {0};
        minOperationsOutExpected = 1;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {0, 0, 0, 0, 0};
        minOperationsOutExpected = 1;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {1, 1, 1, 1, 1, 0, 0};
        minOperationsOutExpected = 1;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {0, 0, 1, 1, 1, 1, 1};
        minOperationsOutExpected = 2;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {0, 0, 1};
        minOperationsOutExpected = 2;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);

        vecIn = {0, 1};
        minOperationsOutExpected = 2;
        minOperationsOutComputed = soln.minOperations(vecIn);
        assert(minOperationsOutExpected == minOperationsOutComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinOperations();

    return 0;
}
