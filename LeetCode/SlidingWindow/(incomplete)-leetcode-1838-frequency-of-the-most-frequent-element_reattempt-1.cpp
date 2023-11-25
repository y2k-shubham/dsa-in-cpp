// LeetCode-1838: https://leetcode.com/problems/frequency-of-the-most-frequent-element/
// (incomplete)

#include <vector>
#include <algorithm>
#include <cassert>
#include <utility>

using namespace std;

class Solution {
private:
    pair<int, int> calcTailEleDeltaHelper(vector<int>& sortedVec, int k, int tailEleIdx) {
        int tailEle = sortedVec[tailEleIdx];

        int i = tailEleIdx - 1;
        int totalDelta = 0;
        while ((i >= 0) && (totalDelta <= k)) {
            int crrDelta = tailEle - sortedVec[i];
            if ((totalDelta + crrDelta) > k) {
                break;
            }

            totalDelta += crrDelta;
            i--;
        }

        if (totalDelta == 0) {
            return {INT_MIN, -1};
        } else {
            return {totalDelta, i + 1};
        }
    }

    pair<int, int> calcTailEleDelta(vector<int>& sortedVec, int k) {
        int len = sortedVec.size();

        int tailEleIdx = len - 1;
        pair<int, int> tailEleDelta = {INT_MIN, -1};
        while ((tailEleIdx >= 0) && (tailEleDelta.first == INT_MIN)) {
            tailEleDelta = calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
            tailEleIdx--;
        }

        return tailEleDelta;
    }

public:
    friend class SolutionTest;

    int maxFrequency(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
    }
};

class SolutionTest {
public:
    void testCalcTailEleDeltaHelper() {
        Solution soln = Solution();
        vector<int> sortedVec;
        int k;
        int tailEleIdx;
        pair<int, int> outExpected, outComputed;

        sortedVec = {1, 4, 8, 13};
        k = 3;
        tailEleIdx = 3;
        outExpected = {INT_MIN, -1};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 4;
        tailEleIdx = 3;
        outExpected = {INT_MIN, -1};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 5;
        tailEleIdx = 3;
        outExpected = {5, 2};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 13;
        tailEleIdx = 3;
        outExpected = {5, 2};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 14;
        tailEleIdx = 3;
        outExpected = {14, 1};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 25;
        tailEleIdx = 3;
        outExpected = {14, 1};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 26;
        tailEleIdx = 3;
        outExpected = {26, 0};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 3;
        tailEleIdx = 2;
        outExpected = {INT_MIN, -1};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 4;
        tailEleIdx = 2;
        outExpected = {4, 1};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 10;
        tailEleIdx = 2;
        outExpected = {4, 1};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);

        sortedVec = {1, 4, 8, 13};
        k = 11;
        tailEleIdx = 2;
        outExpected = {11, 0};
        outComputed = soln.calcTailEleDeltaHelper(sortedVec, k, tailEleIdx);
//        printf("outComputed: %d, %d\n", outComputed.first, outComputed.second);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCalcTailEleDeltaHelper();

    return 0;
}
