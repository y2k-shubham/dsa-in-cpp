// LeetCode-2100: https://leetcode.com/problems/find-good-days-to-rob-the-bank/

/**
 * self-thought approach
 * (very difficult to come up with)
 *
 * approach motiviation
 * - determining whether the array has a 'valley' shaped subarray (window) is trivial
 * - we want to be able to determine the same thing efficiently for a moving window (whether the current window has a valley shape)
 *
 * [5,3,3,3,5,6,2]
 * approach explanation
 *
 * 1. precompute an array in which
 *   - we mark every 'decreasing' range of numbers with a -1
 *   - that ways, prefix sum of last 'n' elements of this precomputed array would tell us whether a left side of valley (downhill slope) is present or not
 * [5, 3, 2, 4]
 * [-1, -1, -1, 0]
 *
 * 1.a. problem with above approach
 *    i. every single-element in itself is a 1-sized decreasing subarray -> that would be misleading
 *    [2, 3, ..]
 *    [-1, -1 ..]
 *
 *   ii. if there are 2 discrete decreasing subarrays placed one after another, how will we identify them separately? (because both will have -1 sign throughout)
 *    [3, 2, 1,       5, 4, 3]
 *    [-1, -1, -1,   -1, -1, -1]
 *
 * 1.b. solution to above problem
 *    i. flip signs in every subsequent decreasing subarray
 *   ii. that ways, taking absolute value of any prefix sum in there would actually tell us whether the required no of decreasing (contiguous) elements are present
 *    [5,3,3,3,5,6,2]
 *    [-1, -1, -1, -1, 1, -1, -1]
 *
 * 2. similarly, we'll pre-compute an array for every 'increasing' range of numbers and take it's suffix sum in sliding window
 *
 * input
 * [5,3,3,3,5,6,2]
 * 2
 * expected output
 * [2,3]
 *
 * input
 * [1,1,1,1,1]
 * 0
 * expected output
 * [0,1,2,3,4]
 *
 * input
 * [1,2,3,4,5,6]
 * 2
 * expected output
 * []
 *
 * input
 * [1,2,3,4]
 * 1
 * expected output
 * []
 */

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug;

    vector<int> buildDecPrefixArr(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> decPrefix(len, 0);

        int crrMarker = -1;
        for (int i = 0; i < len; i++) {
            if ((i == 0) || (vec[i - 1] >= vec[i])) {
                // do nothing -> this is what we want (decreasing prefix)
            } else {
                // reverse marker sign
                crrMarker *= -1;
            }

            decPrefix[i] = crrMarker;
        }

        return decPrefix;
    }

    vector<int> buildIncSuffixArr(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> incSuffix(len, 0);

        int crrMarker = 1;
        for (int i = len - 1; i >= 0; i--) {
            if ((i == (len - 1)) || (vec[i] <= vec[i + 1])) {
                // do nothing -> this is what we want (decreasing prefix)
            } else {
                // reverse marker sign
                crrMarker *= -1;
            }

            incSuffix[i] = crrMarker;
        }

        return incSuffix;
    }

    vector<int> createIncVec(int len) {
        vector<int> vec(len);
        for (int i = 0; i < len; i++) {
            vec[i] = i;
        }

        return vec;
    }

    void showVec(vector<int>& vec, string name) {
        printf("\n%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

   public:
    friend class SolutionTest;

    vector<int> findValleyPoints(
        vector<int>& vec,
        int halfWidth,
        vector<int>& decPrefixArr,
        vector<int>& incSuffixArr) {
        int len = vec.size();
        int i = 0;

        int decPrefixSum = 0;
        while (i < halfWidth) {
            decPrefixSum += decPrefixArr[i++];
        }

        int incSuffixSum = 0;
        i++;
        while (i <= (2 * halfWidth)) {
            incSuffixSum += incSuffixArr[i++];
        }

        vector<int> valleyPoints;
        i = halfWidth;
        while ((i + halfWidth) < len) {
            if (i != halfWidth) {
                decPrefixSum -= ((i - (halfWidth + 1)) >= 0) ? decPrefixArr[i - (halfWidth + 1)] : 0;  // removed
                decPrefixSum += ((i - 1) >= 0) ? decPrefixArr[i - 1] : 0;                              // added

                incSuffixSum -= incSuffixArr[i];                                            // removed
                incSuffixSum += ((i + halfWidth) < len) ? incSuffixArr[i + halfWidth] : 0;  // added
            }

            // note that expressions (vec[i - 1] >= vec[i]) & (vec[i] <= vec[i + 1]) are necessary to rule out false positives in case of time=1
            // (over there, every sign change -> increasing or decreasing array, could otherwise fool us into believing that desired prefix & suffix arrays are present)
            if ((abs(decPrefixSum) == halfWidth) && (vec[i - 1] >= vec[i]) && (abs(incSuffixSum) == halfWidth) && (vec[i] <= vec[i + 1])) {
                valleyPoints.push_back(i);
            }

            i++;
        }

        return valleyPoints;
    }

    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int len = security.size();
        if (len < ((2 * time) + 1)) {
            return {};
        }
        if (time == 0) {
            return createIncVec(len);
        }

        vector<int> decPrefixArr = buildDecPrefixArr(security);
        vector<int> incSuffixArr = buildIncSuffixArr(security);
        if (this->debug) {
            showVec(decPrefixArr, "decPrefixArr");
            showVec(incSuffixArr, "incSuffixArr");
        }

        vector<int> valleyPoints = findValleyPoints(security, time, decPrefixArr, incSuffixArr);
        return valleyPoints;
    }
};

class SolutionTest {
   public:
    void testBuildDecPrefixArr() {
        Solution soln = Solution();
        vector<int> inVec;
        vector<int> outVecExpected, outVecComputed;

        inVec = {};
        outVecExpected = {};
        outVecComputed = soln.buildDecPrefixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5};
        outVecExpected = {-1};
        outVecComputed = soln.buildDecPrefixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 4, 3, 4, 1, 0};
        outVecExpected = {-1, -1, -1, 1, 1, 1};
        outVecComputed = soln.buildDecPrefixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 4};
        outVecExpected = {-1, -1};
        outVecComputed = soln.buildDecPrefixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 6};
        outVecExpected = {-1, 1};
        outVecComputed = soln.buildDecPrefixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {1, 2, 3, 4};
        outVecExpected = {-1, 1, -1, 1};
        outVecComputed = soln.buildDecPrefixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {1, 2, 3, 2, 0, -1};
        outVecExpected = {-1, 1, -1, -1, -1, -1};
        outVecComputed = soln.buildDecPrefixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {1, 2, 3, 4, 2, 0, -1};
        outVecExpected = {-1, 1, -1, 1, 1, 1, 1};
        outVecComputed = soln.buildDecPrefixArr(inVec);
        assert(outVecExpected == outVecComputed);
    }

    void testBuildIncSuffixArr() {
        Solution soln = Solution();
        vector<int> inVec;
        vector<int> outVecExpected, outVecComputed;

        inVec = {};
        outVecExpected = {};
        outVecComputed = soln.buildIncSuffixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5};
        outVecExpected = {1};
        outVecComputed = soln.buildIncSuffixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 6, 7, 7, 8};
        outVecExpected = {1, 1, 1, 1, 1};
        outVecComputed = soln.buildIncSuffixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 4, 3, 2, 1};
        outVecExpected = {1, -1, 1, -1, 1};
        outVecComputed = soln.buildIncSuffixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 4, 3, 7, 1, 0};
        outVecExpected = {1, -1, 1, 1, -1, 1};
        outVecComputed = soln.buildIncSuffixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 6, 9, 2, 5, 9};
        outVecExpected = {-1, -1, -1, 1, 1, 1};
        outVecComputed = soln.buildIncSuffixArr(inVec);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 6, 9, 8, 11, 2, 5, 9};
        outVecExpected = {1, 1, 1, -1, -1, 1, 1, 1};
        outVecComputed = soln.buildIncSuffixArr(inVec);
        assert(outVecExpected == outVecComputed);
    }

    void testGoodDaysToRobBank() {
        Solution soln = Solution();
        vector<int> inVec;
        int inHalfWidth;
        vector<int> outVecExpected, outVecComputed;

        inVec = {};
        inHalfWidth = 0;
        outVecExpected = {};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 8};
        inHalfWidth = 0;
        outVecExpected = {0, 1};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        assert(outVecExpected == outVecComputed);

        inVec = {5, 3, 3, 3, 5, 6, 2};
        inHalfWidth = 2;
        outVecExpected = {2, 3};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        assert(outVecExpected == outVecComputed);

        inVec = {1, 1, 1, 1, 1};
        inHalfWidth = 0;
        outVecExpected = {0, 1, 2, 3, 4};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        assert(outVecExpected == outVecComputed);

        // soln.debug = true;
        inVec = {1, 2, 3, 4, 5, 6};
        inHalfWidth = 2;
        outVecExpected = {};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        // soln.showVec(outVecComputed, "outVecComputed");
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;

        // soln.debug = true;
        inVec = {1, 2, 3, 4};
        inHalfWidth = 1;
        outVecExpected = {};
        outVecComputed = soln.goodDaysToRobBank(inVec, inHalfWidth);
        // soln.showVec(outVecComputed, "outVecComputed");
        assert(outVecExpected == outVecComputed);
        // soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildDecPrefixArr();
    solnTest.testBuildIncSuffixArr();

    solnTest.testGoodDaysToRobBank();

    return 0;
}
