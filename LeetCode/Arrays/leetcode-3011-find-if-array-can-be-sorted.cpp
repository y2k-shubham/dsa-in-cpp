// LeetCode-3011: https://leetcode.com/problems/find-if-array-can-be-sorted/

/**
 * Solution explanation:
 * 1. Chunk array into 'regions' or 'domains' where a region is a continuous sequence of elements
 *    having same no of set bits. Regions are identified by their indices-boundary (startIdx, endIdx)
 * 2. For each region determine the (minVal, maxVal) pair for it
 * 3. Traversing over (minVal, maxVal) of regions from left to right, determine if any region has it's
 *    minVal smaller than maxVal of any preceding region (on it's left) that we've already seen. If that's
 *    the case, then it's not possible to sort. Otherwise array can be sorted with given operations & constraints
 */

#include <vector>
#include <utility>
#include <cassert>

using namespace std;

class Solution {
public:
    friend class SolutionTest;

    bool canSortArray(vector<int>& nums) {
        if (nums.size() <= 1) {
            return true;
        }

        vector<pair<int, int> > minMaxVec = buildSameNumSetBitValueDomainsMinMaxVec(nums);
        int numDomains = minMaxVec.size();

        int maxSoFar = minMaxVec[0].second;
        for (int i = 1; i < numDomains; i++) {
            if (maxSoFar > minMaxVec[i].first) {
                return false;
            }
            maxSoFar = max(maxSoFar, minMaxVec[i].second);
        }

        return true;
    }

private:
    // generated by Amazon Q
    vector<pair<int, int> > buildSameNumSetBitValueDomainsMinMaxVec(vector<int>& vec) {
        vector<pair<int, int> > minMaxVec;
        int len = vec.size();

        int startIdx = 0;
        while (startIdx < len) {
            int endIdx = swallowSameNumSetBitValues(vec, startIdx);
            pair<int, int> minMax = findMinMaxValueInRange(vec, startIdx, endIdx);
            minMaxVec.push_back(minMax);

            startIdx = endIdx + 1;
        }

        return minMaxVec;
    }

    // generated by Amazon Q
    pair<int, int> findMinMaxValueInRange(vector<int>& vec, int startIdx, int endIdx) {
        int len = vec.size();
        int minValue = INT_MAX;
        int maxValue = INT_MIN;

        for (int i = startIdx; i <= endIdx; i++) {
            minValue = min(minValue, vec[i]);
            maxValue = max(maxValue, vec[i]);
        }

        return {minValue, maxValue};
    }

    int swallowSameNumSetBitValues(vector<int>& vec, int startIdx) {
        int numSetBits = calcNumSetBits(vec[startIdx]);

        int len = vec.size();
        for (int i = startIdx + 1; i < len; i++) {
            if (calcNumSetBits(vec[i]) != numSetBits) {
                return i - 1;
            }
        }

        return len - 1;
    }

    // generated by Amazon Q
    int calcNumSetBits(int n) {
        int numSetBits = 0;
        while (n > 0) {
            numSetBits += (n & 1);
            n >>= 1;
        }
        return numSetBits;
    }
};

class SolutionTest {
public:
    void testCanSortArray() {
        Solution soln = Solution();
        vector<int> vecIn;
        bool outExpected, outComputed;

        vecIn = {8, 4, 2, 30, 15};
        outExpected = true;
        outComputed = soln.canSortArray(vecIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 3, 4, 5};
        outExpected = true;
        outComputed = soln.canSortArray(vecIn);
        assert(outExpected == outComputed);

        vecIn = {5, 4, 3, 2, 1};
        outExpected = false;
        outComputed = soln.canSortArray(vecIn);
        assert(outExpected == outComputed);

        vecIn = {3, 16, 8, 4, 2};
        outExpected = false;
        outComputed = soln.canSortArray(vecIn);
        assert(outExpected == outComputed);

        vecIn = {16, 8, 4, 2};
        outExpected = true;
        outComputed = soln.canSortArray(vecIn);
        assert(outExpected == outComputed);

        vecIn = {17, 9, 5, 3};
        outExpected = true;
        outComputed = soln.canSortArray(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 3, 16, 8, 4};
        outExpected = true;
        outComputed = soln.canSortArray(vecIn);
        assert(outExpected == outComputed);

        vecIn = {2, 28, 9};
        outExpected = false;
        outComputed = soln.canSortArray(vecIn);
        assert(outExpected == outComputed);

        printf("[testCanSortArray] All tests passed!\n");
    }

    void testBuildSameNumSetBitValueDomainsMinMaxVec() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<pair<int, int> > minMaxVecOutExpected, minMaxVecOutComputed;

        vecIn = {8, 4, 2, 30, 15};
        minMaxVecOutExpected = {{2,  8},
                                {15, 30}};
        minMaxVecOutComputed = soln.buildSameNumSetBitValueDomainsMinMaxVec(vecIn);
        assert(minMaxVecOutExpected.size() == minMaxVecOutComputed.size());
        assert(minMaxVecOutExpected == minMaxVecOutComputed);

        vecIn = {1, 2, 3, 4, 5};
        minMaxVecOutExpected = {{1, 2},
                                {3, 3},
                                {4, 4},
                                {5, 5}};
        minMaxVecOutComputed = soln.buildSameNumSetBitValueDomainsMinMaxVec(vecIn);
        assert(minMaxVecOutExpected.size() == minMaxVecOutComputed.size());
        assert(minMaxVecOutExpected == minMaxVecOutComputed);

        vecIn = {3, 16, 8, 4, 2};
        minMaxVecOutExpected = {{3, 3},
                                {2, 16}};
        minMaxVecOutComputed = soln.buildSameNumSetBitValueDomainsMinMaxVec(vecIn);
        assert(minMaxVecOutExpected.size() == minMaxVecOutComputed.size());
        assert(minMaxVecOutExpected == minMaxVecOutComputed);

        vecIn = {2, 28, 9};
        minMaxVecOutExpected = {{2,  2},
                                {28, 28},
                                {9,  9}};
        minMaxVecOutComputed = soln.buildSameNumSetBitValueDomainsMinMaxVec(vecIn);
        assert(minMaxVecOutExpected.size() == minMaxVecOutComputed.size());
        assert(minMaxVecOutExpected == minMaxVecOutComputed);

        printf("[testBuildSameNumSetBitValueDomainsMinMaxVec] All tests passed!\n");
    }

    void testFindMinMaxValueInRange() {
        Solution soln = Solution();
        vector<int> vecIn;
        pair<int, int> minMaxOutExpected, minMaxOutComputed;

        vecIn = {8, 4, 2, 30, 15};

        minMaxOutExpected = make_pair(2, 30);
        minMaxOutComputed = soln.findMinMaxValueInRange(vecIn, 0, 4);
        assert(minMaxOutExpected.first == minMaxOutComputed.first && minMaxOutExpected.second == minMaxOutComputed.second);

        minMaxOutExpected = make_pair(2, 30);
        minMaxOutComputed = soln.findMinMaxValueInRange(vecIn, 2, 4);
        assert(minMaxOutExpected.first == minMaxOutComputed.first && minMaxOutExpected.second == minMaxOutComputed.second);

        minMaxOutExpected = make_pair(2, 8);
        minMaxOutComputed = soln.findMinMaxValueInRange(vecIn, 0, 2);
        assert(minMaxOutExpected.first == minMaxOutComputed.first && minMaxOutExpected.second == minMaxOutComputed.second);

        minMaxOutExpected = make_pair(4, 8);
        minMaxOutComputed = soln.findMinMaxValueInRange(vecIn, 0, 1);
        assert(minMaxOutExpected.first == minMaxOutComputed.first && minMaxOutExpected.second == minMaxOutComputed.second);

        minMaxOutExpected = make_pair(8, 8);
        minMaxOutComputed = soln.findMinMaxValueInRange(vecIn, 0, 0);
        assert(minMaxOutExpected.first == minMaxOutComputed.first && minMaxOutExpected.second == minMaxOutComputed.second);

        minMaxOutExpected = make_pair(4, 4);
        minMaxOutComputed = soln.findMinMaxValueInRange(vecIn, 1, 1);
        assert(minMaxOutExpected.first == minMaxOutComputed.first && minMaxOutExpected.second == minMaxOutComputed.second);

        minMaxOutExpected = make_pair(15, 30);
        minMaxOutComputed = soln.findMinMaxValueInRange(vecIn, 3, 4);
        assert(minMaxOutExpected.first == minMaxOutComputed.first && minMaxOutExpected.second == minMaxOutComputed.second);

        printf("[testFindMinMaxValueInRange] All tests passed!\n");
    }

    void testSwallowSameNumSetBitValues() {
        Solution soln = Solution();
        vector<int> vecIn;
        int startIdx;
        int endIdxOutExpected, endIdxOutComputed;

        vecIn = {8, 4, 2, 30, 15};

        startIdx = 0;
        endIdxOutExpected = 2;
        endIdxOutComputed = soln.swallowSameNumSetBitValues(vecIn, startIdx);
        assert(endIdxOutExpected == endIdxOutComputed);

        startIdx = 1;
        endIdxOutExpected = 2;
        endIdxOutComputed = soln.swallowSameNumSetBitValues(vecIn, startIdx);
        assert(endIdxOutExpected == endIdxOutComputed);

        startIdx = 2;
        endIdxOutExpected = 2;
        endIdxOutComputed = soln.swallowSameNumSetBitValues(vecIn, startIdx);
        assert(endIdxOutExpected == endIdxOutComputed);

        startIdx = 3;
        endIdxOutExpected = 4;
        endIdxOutComputed = soln.swallowSameNumSetBitValues(vecIn, startIdx);
        assert(endIdxOutExpected == endIdxOutComputed);

        startIdx = 4;
        endIdxOutExpected = 4;
        endIdxOutComputed = soln.swallowSameNumSetBitValues(vecIn, startIdx);
        assert(endIdxOutExpected == endIdxOutComputed);

        printf("[testSwallowSameNumSetBitValues] All tests passed!\n");
    }

    // generated by Amazon Q
    void testCalcNumSetBits() {
        Solution soln = Solution();

        assert(soln.calcNumSetBits(0) == 0);
        assert(soln.calcNumSetBits(1) == 1);
        assert(soln.calcNumSetBits(2) == 1);
        assert(soln.calcNumSetBits(3) == 2);
        assert(soln.calcNumSetBits(4) == 1);
        assert(soln.calcNumSetBits(5) == 2);
        assert(soln.calcNumSetBits(6) == 2);
        assert(soln.calcNumSetBits(7) == 3);
        assert(soln.calcNumSetBits(8) == 1);

        printf("[testCalcNumSetBits] All tests passed!\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCanSortArray();
    solnTest.testBuildSameNumSetBitValueDomainsMinMaxVec();
    solnTest.testFindMinMaxValueInRange();
    solnTest.testSwallowSameNumSetBitValues();
    solnTest.testCalcNumSetBits();

    return 0;
}
