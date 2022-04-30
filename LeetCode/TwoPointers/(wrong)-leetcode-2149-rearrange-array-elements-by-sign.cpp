// LeetCode-2149: https://leetcode.com/problems/rearrange-array-elements-by-sign/
// wrong

#include <vector>
#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    void debugOutput(
            vector<int>& vec,
            int iReadPositive,
            int iReadNegative,
            int iWrite
    ) {
        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;

        printf("Read+:\t");
        for (int i = 0; i < iReadPositive; i++) {
            printf("\t");
        }
        printf("^\n");

        printf("Read-:\t");
        for (int i = 0; i < iReadNegative; i++) {
            printf("\t");
        }
        printf("^\n");

        printf("Write:\t");
        for (int i = 0; i < iWrite; i++) {
            printf("\t");
        }
        printf("^\n");
    }

    int getNextPositiveIdx(vector<int>& vec, int from) {
        int len = vec.size();

        for (int i = from; i < len; i++) {
            if (vec[i] >= 0) {
                return i;
            }
        }

        return len;
    }

    int getNextNegativeIdx(vector<int>& vec, int from) {
        int len = vec.size();

        for (int i = from; i < len; i++) {
            if (vec[i] < 0) {
                return i;
            }
        }

        return len;
    }

    bool swap(vector<int>& vec, int idx1, int idx2) {
        if (idx1 == idx2) {
            return false;
        }

        int tmp = vec[idx1];
        vec[idx1] = vec[idx2];
        vec[idx2] = tmp;

        return true;
    }

public:
    friend class SolutionTest;

    vector<int> rearrangeArray(vector<int>& nums) {
        int len = nums.size();
        if (len < 2) {
            return nums;
        }

        int iWrite = 0;
        int iReadPositive = getNextPositiveIdx(nums, 0);
        int iReadNegative = getNextNegativeIdx(nums, 0);
        if (debug) {
            printf("\n--------\n");
            printf("Before loop\n");
            debugOutput(nums, iReadPositive, iReadNegative, iWrite);
            printf("\n--------\n");
        }

        int isPositiveTurn = 1;
        int iter = 1;
        while (iWrite < len) {
            if (isPositiveTurn > 0) {
                if (swap(nums, iWrite, iReadPositive)) {
                    iReadNegative = iReadPositive;
                }
                iReadPositive = getNextPositiveIdx(nums, iReadPositive + 1);
            } else {
                if (swap(nums, iWrite, iReadNegative)) {
                    iReadPositive = iReadNegative;
                }
                iReadNegative = getNextNegativeIdx(nums, iReadNegative + 1);
            }

            iWrite++;
            isPositiveTurn = 1 - isPositiveTurn;

            if (debug) {
                printf("\n--------\n");
                printf("After iter=%d, positiveTurn=%s\n", iter++, ((isPositiveTurn == 1) ? "true" : "false"));
                debugOutput(nums, iReadPositive, iReadNegative, iWrite);
                printf("\n--------\n");
            }
        }

        return nums;
    }
};

class SolutionTest {
public:
    void testRearrangeArray() {
        Solution soln = Solution();
        vector <int> numsIn;
        vector <int> numsOutExpected, numsOutComputed;

        numsIn = {};
        numsOutExpected = {};
        numsOutComputed = soln.rearrangeArray(numsIn);
        assert(numsOutExpected == numsOutComputed);

        numsIn = {4};
        numsOutExpected = {4};
        numsOutComputed = soln.rearrangeArray(numsIn);
        assert(numsOutExpected == numsOutComputed);

        numsIn = {4,-3};
        numsOutExpected = {4,-3};
        numsOutComputed = soln.rearrangeArray(numsIn);
        assert(numsOutExpected == numsOutComputed);

//        soln.debug = true;
        numsIn = {-3,4};
        numsOutExpected = {4,-3};
        numsOutComputed = soln.rearrangeArray(numsIn);
        assert(numsOutExpected == numsOutComputed);
//        soln.debug = false;

        soln.debug = true;
        numsIn = {-3,-5,1,4};
        numsOutExpected = {1,-3,4,-5};
        numsOutComputed = soln.rearrangeArray(numsIn);
        assert(numsOutExpected == numsOutComputed);
        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testRearrangeArray();

    return 0;
}
