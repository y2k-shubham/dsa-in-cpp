// LeetCode-1442: https://leetcode.com/problems/count-triplets-that-can-form-two-arrays-of-equal-xor/

#include <vector>
#include <cassert>

using namespace std;

class Solution {
private:
    vector<int> buildXorPrefixVec(vector<int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector<int> xorPrefixVec(len);
        xorPrefixVec[0] = vec[0];

        for (int i = 1; i < len; i++) {
            xorPrefixVec[i] = xorPrefixVec[i - 1] ^ vec[i];
        }

        return xorPrefixVec;
    }

    vector<int> buildXorSuffixVec(vector<int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return vec;
        }

        vector<int> xorSuffixVec(len);
        xorSuffixVec[len - 1] = vec[len - 1];

        for (int i = len - 2; i >= 0; i--) {
            xorSuffixVec[i] = vec[i] ^ xorSuffixVec[i + 1];
        }

        return xorSuffixVec;
    }

    int countTriplets_1_subOptimal(vector<int>& vec) {
        int len = vec.size();
        // IMPORTANT: solutions are possible even in arrays of length 2
        if (len < 2) {
            return 0;
        }

        vector<int> xorPrefixVec = buildXorPrefixVec(vec);
        int numTriplets = 0;
        for (int i = 0; i < len - 1; i++) {
            for (int k = i + 1; k < len; k++) {
                for (int j = i + 1; j <= k; j++) {
                    // XOR of elements from arr[i] to arr[j - 1]
                    int xorVec0toI = (i == 0) ? 0 : xorPrefixVec[i - 1];
                    int xorVec0toJ = xorPrefixVec[j - 1];
                    int xorVecItoJ = xorVec0toI ^ xorVec0toJ;

                    // XOR of elements from arr[j] to arr[k]
                    int xorVecJtoK;
                    if (j == k) {
                        xorVecJtoK = vec[j];
                    } else {
                        int xorVec0toJ = xorPrefixVec[j - 1];
                        int xorVec0toK = xorPrefixVec[k];
                        xorVecJtoK = xorVec0toJ ^ xorVec0toK;
                    }

                    if (xorVecItoJ == xorVecJtoK) {
                        ++numTriplets;
                    }
                }
            }
        }

        return numTriplets;
    }

public:
    friend class SolutionTest;

    int countTriplets(vector<int>& arr) {
        return countTriplets_1_subOptimal(arr);
    }
};

class SolutionTest {
public:
    void testBuildXorPrefixVec() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected, vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = soln.buildXorPrefixVec(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {15};
        vecOutExpected = {15};
        vecOutComputed = soln.buildXorPrefixVec(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {9, 3};
        vecOutExpected = {9, 10};
        vecOutComputed = soln.buildXorPrefixVec(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {9, 3, 18};
        vecOutExpected = {9, 10, 24};
        vecOutComputed = soln.buildXorPrefixVec(vecIn);
        assert(vecOutExpected == vecOutComputed);
    }

    void testBuildXorSuffixVec() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected, vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = soln.buildXorSuffixVec(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {3};
        vecOutExpected = {3};
        vecOutComputed = soln.buildXorSuffixVec(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {3, 9};
        vecOutExpected = {10, 9};
        vecOutComputed = soln.buildXorSuffixVec(vecIn);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {18, 3, 9};
        vecOutExpected = {24, 10, 9};
        vecOutComputed = soln.buildXorSuffixVec(vecIn);
        assert(vecOutExpected == vecOutComputed);
    }

    void testCountTriplets_1_subOptimal() {
        Solution soln = Solution();
        vector<int> vecIn;
        int outExpected, outComputed;

        vecIn = {};
        outExpected = 0;
        outComputed = soln.countTriplets_1_subOptimal(vecIn);
        assert(outExpected == outComputed);

        vecIn = {8};
        outExpected = 0;
        outComputed = soln.countTriplets_1_subOptimal(vecIn);
        assert(outExpected == outComputed);

        vecIn = {8, 1};
        outExpected = 0;
        outComputed = soln.countTriplets_1_subOptimal(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 2};
        outExpected = 1;
        outComputed = soln.countTriplets_1_subOptimal(vecIn);
        assert(outExpected == outComputed);

        vecIn = {8, 1, 3};
        outExpected = 0;
        outComputed = soln.countTriplets_1_subOptimal(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 3, 1, 6, 7};
        outExpected = 4;
        outComputed = soln.countTriplets_1_subOptimal(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 1, 1};
        outExpected = 10;
        outComputed = soln.countTriplets_1_subOptimal(vecIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildXorPrefixVec();
    solnTest.testBuildXorSuffixVec();
    solnTest.testCountTriplets_1_subOptimal();

    return 0;
}
