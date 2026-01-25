// LeetCode-41: https://leetcode.com/problems/first-missing-positive/
// NeetCode: https://www.youtube.com/watch?v=8g78yfzMlao
// (reasonably) Hard question, with very extreme test-cases

/**
 * Tricky test-case from LeetCode that causes integer overflow
 * [2147483647,2147483646,2147483645,3,2,1,-1,0,-2147483648]
 */

#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    vector<int> vec;
    int len;
    int numNonPositiveEles;
    bool debug = false;

    // --------- debugging ---------

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    void showDebugOutput(string when) {
        if (!debug) {
            return;
        }

        printf("%s, vec is:-\n", when.c_str());
        showVec();
        printf("numNonPositiveEles = %d\n\n", numNonPositiveEles);
    }

    void showVec() {
        printf("Vec is:-\n");

        printf("Idx:\t");
        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < len; i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    // --------- initialization ---------

    void reset() {
        vec = {};
        len = -1;
        numNonPositiveEles = -1;
    }

    void init(vector<int>& vec) {
        this->vec = vec;
        this->len = vec.size();
    }

    // --------- shift negative numbers to beginning of array ---------

    int findFirstPositiveEleIdx() {
        for (int i = 0; i < len; i++) {
            if (vec[i] > 0) {
                return i;
            }
        }

        return len;
    }

    void shiftNonPositiveEles() {
        int firstPositiveEleIdx = findFirstPositiveEleIdx();
        if (firstPositiveEleIdx >= len) {
            // all numbers were non-positive
            this->numNonPositiveEles = len;
            return;
        }

        int dstIdx = firstPositiveEleIdx;
        int srcIdx = dstIdx + 1;

        while (srcIdx < len) {
            if (vec[srcIdx] <= 0) {
                swapEles(srcIdx, dstIdx);
                dstIdx++;
            }
            srcIdx++;
        }

        this->numNonPositiveEles = dstIdx;
    }

    void swapEles(int idx1, int idx2) {
        int temp = vec[idx1];
        vec[idx1] = vec[idx2];
        vec[idx2] = temp;
    }

    // --------- process positive numbers ---------

    void registerPresenceOfPositiveEles() {
        int firstPositiveEleIdx = numNonPositiveEles;
        int theoreticalMaxMissingPositiveEle = len - numNonPositiveEles + 1;

        for (int i = firstPositiveEleIdx; i < len; i++) {
            int val = vec[i];
            int absVal = abs(val);
            if (absVal > theoreticalMaxMissingPositiveEle) {
                continue;
            }

            int valMarkerIdx = firstPositiveEleIdx + absVal - 1;
            if (valMarkerIdx < len) {
                // mark the (formerly positive) value at index 'val'
                // (from first positive element onwards) as negative,
                // in order to register the presence of this number
                vec[valMarkerIdx] = -(abs(vec[valMarkerIdx]));
            }
        }
    }

    // --------- find first missing positive number ---------

    int findFirstMissingPositiveEle() {
        for (int i = numNonPositiveEles; i < len; i++) {
            if (vec[i] > 0) {
                // presence of the positive number at index i
                // (from first positive element onwards) is NOT registered,
                // implying that it is missing
                return (i - numNonPositiveEles + 1);
            }
        }

        // all numbers from 1 onwards were present such that we found no 'holes'
        // so then the missing positive number would be just 1 greater than the biggest positive number found
        // which will be mathematically equal to number of positive numbers + 1
        int numPositiveEles = len - numNonPositiveEles;
        return numPositiveEles + 1;
    }

public:
    friend class SolutionTest;

    int firstMissingPositive(vector<int>& nums) {
        reset();
        init(nums);

        // showDebugOutput("before shifting non positive numbers");

        shiftNonPositiveEles();
        if (numNonPositiveEles == len) {
            // all numbers were non-positive
            return 1;
        }

        // showDebugOutput("after shifting non positive numbers");

        registerPresenceOfPositiveEles();

        // showDebugOutput("after registering presence of positive numbers");

        return findFirstMissingPositiveEle();
    }
};

class SolutionTest {
public:
    void testFindMissingPositive() {
        vector<int> vecIn;
        int outExpected, outComputed;
        Solution soln = Solution();

        // ------ LeetCode sample test-cases -------

        vecIn = {1, 2, 0};
        outExpected = 3;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {3, 4, -1, 1};
        outExpected = 2;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {7, 8, 9, 11, 12};
        outExpected = 1;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        // ------ self-constructured test-cases (replicated from first attempt file) -------

        vecIn = {2, 3, 7, 6, 8, -1, -10, 15};
        outExpected = 1;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 3, -7, 6, 8, 1, -10, 15};
        outExpected = 4;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 0, -1, -2};
        outExpected = 2;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {7, 8, 9, 11, 12};
        outExpected = 1;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {7, -2, 3, 1, 2, 20, -5};
        outExpected = 4;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {8, 1, 3, 7, 4, 2, 9};
        outExpected = 5;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 4, 1};
        outExpected = 3;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 3, 1};
        outExpected = 4;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2147483647,2147483646,2147483645,3,2,1,-1,0,-2147483648};
        outExpected = 4;
        outComputed = soln.firstMissingPositive(vecIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testFindMissingPositive();

    return 0;
}
