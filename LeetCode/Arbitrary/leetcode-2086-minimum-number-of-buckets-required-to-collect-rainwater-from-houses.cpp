// LeetCode-2086: https://leetcode.com/problems/minimum-number-of-buckets-required-to-collect-rainwater-from-houses/

/**
 * test cases
 * 
 * input="H..H"
 * expected_output=2
 * 
 * input=".H.H."
 * expected_output=1
 * 
 * input=".HHH."
 * expected_output=-1
 * 
 * input="."
 * expected_output=0
 * 
 * input="H"
 * expected_output=-1
 * 
 * input="HH..H"
 * expected_output=-1
 * 
 * input="H..HH"
 * expected_output=-1
 * 
 * input="H.H"
 * expected_output=1
 * 
 * input="H.H.HH...H.H"
 * expected_output=4
 */

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool canSolve(vector<char>& streetVec) {
        int len = streetVec.size();
        if (len == 0) {
            return true;
        }
        if ((len == 1) && (streetVec[0] == 'H')) {
            // single cell containing house -> no soln
            return false;
        }
        if (len >= 2) {
            // two consecutive houses in the beginning of street
            if (streetVec[0] == 'H' && streetVec[1] == 'H') {
                return false;
            }
            // two consecutive houses at the end of street
            if (streetVec[len - 2] == 'H' && streetVec[len - 1] == 'H') {
                return false;
            }
        }

        int crrHouseCount = 0;
        for (int i = 0; i < len; i++) {
            if (streetVec[i] == 'H') {
                // increment counter of consecutive houses
                crrHouseCount++;

                if (crrHouseCount >= 3) {
                    // found 3 consecutive houses
                    return false;
                }
            } else {
                // reset counter of consecutive houses
                crrHouseCount = 0;
            }
        }

        return true;
    }

    int placeBucketIfEmpty(vector<char>& streetVec, int pos) {
        if (streetVec[pos] == '.') {
            streetVec[pos] = 'B';
            return 1;
        }

        return 0;
    }

    int placeBuckets(vector<char>& streetVec) {
        int numBuckets = 0;

        int len = streetVec.size();
        if (len >= 2) {
            if (streetVec[0] == 'H') {
                // house at the beginning of the street
                numBuckets += placeBucketIfEmpty(streetVec, 1);
            }
            if (streetVec[len - 1] == 'H') {
                // house at the end of the street
                numBuckets += placeBucketIfEmpty(streetVec, len - 2);
            }
        }

        for (int i = 1; i < (len - 1); i++) {
            if (streetVec[i] == 'H') {
                // recall that by this time it is certain that
                // there cant be 3 consecutive houses -> that would be unsolvable

                if (streetVec[i - 1] == 'B') {
                    // adjacent bucket already present
                    continue;
                } else if (streetVec[i + 1] == 'H') {
                    // next cell also has a house,
                    // so must place bucket in preceding (vacant) cell
                    numBuckets += placeBucketIfEmpty(streetVec, i - 1);
                } else {
                    // here it means both preceding and next cells are empty
                    // then it is always better to place bucket in next cell

                    // note that due to the case involving house at the end of street
                    // (where we already place bucket in 2nd last cell)
                    // we end up in a scenario where succeeding cell of a house can already
                    // have a bucket placed (even before we reached till that point to scan)
                    numBuckets += placeBucketIfEmpty(streetVec, i + 1);
                }
            }
        }

        return numBuckets;
    }

   public:
    friend class SolutionTest;

    int minimumBuckets(string streetStr) {
        vector<char> streetVec(streetStr.begin(), streetStr.end());

        if (canSolve(streetVec)) {
            return placeBuckets(streetVec);
        } else {
            return -1;
        }
    }
};

class SolutionTest {
   public:
    void testCanSolve() {
        Solution soln = Solution();
        vector<char> vecIn;
        bool outExpected, outComputed;

        vecIn = {};
        outExpected = true;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);

        vecIn = {'.'};
        outExpected = true;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);

        vecIn = {'H'};
        outExpected = false;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);

        vecIn = {'H', 'H'};
        outExpected = false;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);

        vecIn = {'H', 'H', '.'};
        outExpected = false;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);

        vecIn = {'.', 'H', 'H'};
        outExpected = false;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);

        vecIn = {'H', '.', 'H'};
        outExpected = true;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);

        vecIn = {'.', 'H', 'H', '.'};
        outExpected = true;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);

        vecIn = {'H', '.', 'H', 'H', '.', 'H'};
        outExpected = true;
        outComputed = soln.canSolve(vecIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCanSolve();

    return 0;
}
