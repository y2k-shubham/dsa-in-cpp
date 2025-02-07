// LeetCode-2401: https://leetcode.com/problems/longest-nice-subarray/
// incomplete

/**
 * 51 of 65 test-cases passed
 *
 * Failing test-case
 * [84139415,693324769,614626365,497710833,615598711,264,65552,50331652,1,1048576,16384,544,270532608,151813349,221976871,678178917,845710321,751376227,331656525,739558112,267703680]
 */

#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stack>

using namespace std;

#define BIT_REPR_LEN 31

class Solution {
private:
    bool debug = false;

    string getBinaryRepr(int num) {
        vector <unsigned short> bitReprVec(BIT_REPR_LEN, 0);
        int i = 0;
        while (num > 0) {
            unsigned short bit = num & 1; // remainder with 2
            bitReprVec[i++] = bit;

            num >>= 1; // divide by 2
        }

        ostringstream oss;
        for (int i = BIT_REPR_LEN - 1; i >= 0; i--) {
            oss << bitReprVec[i];
        }

        return oss.str();
    }

    void showVec(vector <int>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            printf("vec[i=%d]\t=\t%s\t=\t%d\n", i, getBinaryRepr(vec[i]).c_str(), vec[i]);
        }
    }

    void enableDebug() {
        debug = true;
    }

    void disbleDebug() {
        debug = false;
    }

    int swallowWhileNoMatchingBits(vector <int>& vec, int startIdx) {
        int len = vec.size();

        int i;
        int _or = 0;
        for (i = startIdx; (i < len) && ((_or & vec[i]) == 0); i++) {
            _or |= vec[i];
        }

        return i;
    }

    int swallowWhileMatchingBits(vector <int>& vec, int startIdx) {
        int len = vec.size();

        int i;
        int _or = vec[startIdx];
        for (i = startIdx; (i < len) && ((_or & vec[i]) != 0); i++) {
            _or |= vec[i];
        }

        return i;
    }

public:
    friend class SolutionTest;

    int longestNiceSubarray(vector <int>& nums) {
        int len = nums.size();
        int longestNiceSubarrayLen = 0;

        if (debug) {
            showVec(nums);
        }

        for (int i = 0; i < len;) {
            int newIdx1 = swallowWhileNoMatchingBits(nums, i);
            int crrNiceSubarrayLen = newIdx1 - i;
            if (debug) {
                printf("at nums[i=%d]=%d, found nums[newIdx=%d]=%d, so that niceSubarrLen=%d\n", i, nums[i], newIdx1, ((newIdx1 >= len) ? -1 : (nums[newIdx1])), crrNiceSubarrayLen);
            }
            longestNiceSubarrayLen = max(longestNiceSubarrayLen, crrNiceSubarrayLen);

            if (newIdx1 > i) {
                i = newIdx1;
            } else {
                i++;
            }

            // int newIdx2 = swallowWhileMatchingBits(nums, i);
            // i = newIdx2;
        }

        return longestNiceSubarrayLen;
    }
};

class SolutionTest {
public:
    void testSwallowWhileNoMatchingBits() {
        Solution soln = Solution();
        vector <int> vecIn;
        int startIdxIn;
        int idxOutExpected, idxOutComputed;

        vecIn = {1, 3, 8, 48, 10};

        startIdxIn = 0;
        idxOutExpected = 1;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 1;
        idxOutExpected = 4;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 2;
        idxOutExpected = 4;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 3;
        idxOutExpected = 5;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        // printf("computed=%d\n", idxOutComputed);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 4;
        idxOutExpected = 5;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {3, 1, 5, 11, 13};

        startIdxIn = 0;
        idxOutExpected = 1;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 1;
        idxOutExpected = 2;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 2;
        idxOutExpected = 3;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 3;
        idxOutExpected = 4;
        idxOutComputed = soln.swallowWhileNoMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);
    }

    void testSwallowWhileMatchingBits() {
        Solution soln = Solution();
        vector <int> vecIn;
        int startIdxIn;
        int idxOutExpected, idxOutComputed;

        vecIn = {1, 3, 8, 48, 10};

        startIdxIn = 0;
        idxOutExpected = 2;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 1;
        idxOutExpected = 2;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 2;
        idxOutExpected = 3;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 3;
        idxOutExpected = 4;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        // printf("computed=%d\n", idxOutComputed);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 4;
        idxOutExpected = 5;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {3, 1, 5, 11, 13};

        startIdxIn = 0;
        idxOutExpected = 5;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 1;
        idxOutExpected = 5;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 2;
        idxOutExpected = 5;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);

        startIdxIn = 3;
        idxOutExpected = 5;
        idxOutComputed = soln.swallowWhileMatchingBits(vecIn, startIdxIn);
        assert(idxOutExpected == idxOutComputed);
    }

    void testLongestNiceSubarray() {
        Solution soln = Solution();
        vector <int> vecIn;
        int lenOutExpected, lenOutComputed;

        vecIn = {1, 3, 8, 48, 10};
        lenOutExpected = 3;
        lenOutComputed = soln.longestNiceSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);

        vecIn = {3, 1, 5, 11, 13};
        lenOutExpected = 1;
        lenOutComputed = soln.longestNiceSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);

        soln.enableDebug();
        vecIn = {
            84139415, 693324769, 614626365, 497710833, 615598711, 264, 65552, 50331652, 1, 1048576, 16384, 544,
            270532608, 151813349, 221976871, 678178917, 845710321, 751376227, 331656525, 739558112, 267703680
        };
        lenOutExpected = 8;
        lenOutComputed = soln.longestNiceSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);
        soln.disbleDebug();
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testSwallowWhileNoMatchingBits();
    solnTest.testSwallowWhileMatchingBits();
    solnTest.testLongestNiceSubarray();

    return 0;
}
