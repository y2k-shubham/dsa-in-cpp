// LeetCode-1574: https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
// Good question; implemented after reading editorial. Has way too-many edge cases.
// wrong; currently failing on this input [13,0,14,7,18,18,18,16,8,15,20] ; expectedOutput = 8

#include <vector>
#include <climits>
#include <algorithm>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    bool isStrictlyDecreasing(vector<int>& vec) {
        int len = vec.size();
        for (int i = 1; i < len; i++) {
            if (vec[i - 1] <= vec[i]) {
                return false;
            }
        }

        return true;
    }

    bool isNonIncreasing(vector<int>& vec) {
        int len = vec.size();
        for (int i = 1; i < len; i++) {
            if (vec[i - 1] < vec[i]) {
                return false;
            }
        }

        return true;
    }

    int getMaxSameElementSubarrayLen(vector<int>& vec) {
        int len = vec.size();
        int maxLen = 1;
        int currLen = 1;

        for (int i = 1; i < len; i++) {
            if (vec[i - 1] == vec[i]) {
                currLen++;
            } else {
                maxLen = max(maxLen, currLen);
                currLen = 1;
            }
        }

        return max(maxLen, currLen);
    }

    int findInflexionPointFromLeft(vector<int>& vec) {
        int len = vec.size();
        for (int i = 1; i < len; i++) {
            if (vec[i] < vec[i - 1]) {
                return i - 1;
            }
        }

        return INT_MAX;
    }

    int findInflexionPointFromRight(vector<int>& vec) {
        int len = vec.size();
        for (int i = len - 2; i >= 0; i--) {
            if (vec[i] > vec[i + 1]) {
                return i + 1;
            }
        }

        return INT_MIN;
    }

    inline int moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vector<int>& vec, int beginIdx, int val) {
        int len = vec.size();
        if ((beginIdx >= len) || (vec[beginIdx] > val)) {
            return INT_MIN;
        }

        for (int i = beginIdx; i < len; i++) {
            if (vec[i] > val) {
                return i - 1;
            }
        }

        return len - 1;
    }

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

public:
    friend class SolutionTest;

    int findLengthOfShortestSubarray(vector<int>& arr) {
        int len = arr.size();
        if (len <= 1) {
            if (debug) {
                printf("returning zero from here 0\n");
            }
            return 0;
        }

        if (isStrictlyDecreasing(arr)) {
            if (debug) {
                printf("returning (len=%d - 1) = %d; from 0\n", len, (len - 1));
            }
            return len - 1;
        }

        int inflexionIdxFromRight = findInflexionPointFromRight(arr);
        if (inflexionIdxFromRight == INT_MIN) {
            // array is already sorted
            if (debug) {
                printf("returning zero from here 1\n");
            }
            return 0;
        }

        int leftPtr = 0;
        int leftPtrMaxIdx = findInflexionPointFromLeft(arr);
        if (leftPtrMaxIdx == INT_MAX) {
            // array is already sorted; should never happen
            if (debug) {
                printf("returning zero from here 2\n");
            }
            return 0;
        }
        int rightPtr = inflexionIdxFromRight;
        int rightPtrMaxIdx = len - 1;

        if (isNonIncreasing(arr)) {
            return min((len - leftPtrMaxIdx - 1), inflexionIdxFromRight);
        }
        if ((leftPtrMaxIdx < len) && (rightPtrMaxIdx >= 0) && (arr[leftPtrMaxIdx] <= arr[rightPtrMaxIdx])) {
            return rightPtrMaxIdx - leftPtrMaxIdx - 1;
        }

//        if ((leftPtrMaxIdx + 1) == inflexionIdxFromRight) {
//            return min(
//                    (len - leftPtrMaxIdx - 1),
//                    inflexionIdxFromRight
//            );
//        }

        int minSubarrLen = INT_MAX;
        while ((leftPtr <= leftPtrMaxIdx) && (rightPtr <= rightPtrMaxIdx)) {
            leftPtr = moveLeftPtrTowardsRightTillEleLessThanEqualToVal(arr, 0, arr[rightPtr]);
            if (leftPtr == INT_MIN) {
                rightPtr++;
                continue;

//                if (debug) {
//                    printf("returning (len=%d - 1) = %d; leftPtr=%d [leftPtrMaxIdx=%d], [rightPtrBeginIdx=%d] rightPtr=%d, crrSubarrLen=%d, minSubarrLen=%d\n", len, (len - 1), leftPtr, leftPtrMaxIdx, inflexionIdxFromRight, rightPtr, 0, minSubarrLen);
//                }
//                return len - 1;
            }
            if ((leftPtr >= len - 2) || (leftPtr + 1 == rightPtr)) {
                if (debug) {
                    printf("returning zero from here 3\n");
                }
                return 0;
            }

            int crrSubarrLen = rightPtr - leftPtr - 1;
            minSubarrLen = min(minSubarrLen, crrSubarrLen);
//            if (debug) {
//                printf("leftPtr=%d [leftPtrMaxIdx=%d], [rightPtrBeginIdx=%d] rightPtr=%d, crrSubarrLen=%d, minSubarrLen=%d\n", leftPtr, leftPtrMaxIdx, inflexionIdxFromRight, rightPtr, crrSubarrLen, minSubarrLen);
//            }

            rightPtr++;
        }


        if (debug) {
            printf("returning min(minSubarrLen=%d, (len - leftPtrMaxIdx - 1)=%d, inflexionIdxFromRight=%d) = %d; from 2\n",
                   minSubarrLen, (len - leftPtrMaxIdx - 1), inflexionIdxFromRight,
                   min(minSubarrLen, min((len - leftPtrMaxIdx - 1), inflexionIdxFromRight)
                   ));
        }
        return min(
                minSubarrLen,
                min((len - leftPtrMaxIdx - 1), inflexionIdxFromRight)
        );

        if (minSubarrLen == INT_MAX) {
            if (debug) {
                printf("returning (len=%d - 1) = %d; from 1\n", len, (len - 1));
            }
            return (len - 1);
        } else {
            if (debug) {
                printf("returning min(minSubarrLen=%d, (len - leftPtrMaxIdx - 1)=%d, inflexionIdxFromRight=%d) = %d; from 2\n",
                       minSubarrLen, (len - leftPtrMaxIdx - 1), inflexionIdxFromRight,
                       min(minSubarrLen, min((len - leftPtrMaxIdx - 1), inflexionIdxFromRight)
                       ));
            }
            return min(
                    minSubarrLen,
                    min((len - leftPtrMaxIdx - 1), inflexionIdxFromRight)
            );
        }
    }
};

class SolutionTest {
public:
    void testFindInflexionPointFromLeft() {
        Solution soln = Solution();
        vector<int> vec;
        int outExpected, outComputed;

        vec = vector<int>{1, 2, 3, 10, 4, 2, 3, 5};
        outExpected = 3;
        outComputed = soln.findInflexionPointFromLeft(vec);
        assert(outExpected == outComputed);

        vec = vector<int>{5, 4, 3, 2, 1};
        outExpected = 0;
        outComputed = soln.findInflexionPointFromLeft(vec);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3};
        outExpected = INT_MAX;
        outComputed = soln.findInflexionPointFromLeft(vec);
        assert(outExpected == outComputed);

        printf("[testFindInflexionPointFromLeft] All test-cases passed!\n");
    }

    void testFindInflexionPointFromRight() {
        Solution soln = Solution();
        vector<int> vec;
        int outExpected, outComputed;

        vec = vector<int>{1, 2, 3, 10, 4, 2, 3, 5};
        outExpected = 5;
        outComputed = soln.findInflexionPointFromRight(vec);
        assert(outExpected == outComputed);

        vec = vector<int>{5, 4, 3, 2, 1};
        outExpected = 4;
        outComputed = soln.findInflexionPointFromRight(vec);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3};
        outExpected = INT_MIN;
        outComputed = soln.findInflexionPointFromRight(vec);
        assert(outExpected == outComputed);

        printf("[testFindInflexionPointFromRight] All test-cases passed!\n");
    }

    void testMoveLeftPtrTowardsRightTillEleLessThanEqualToVal() {
        Solution soln = Solution();
        vector<int> vec;
        int val, idxBegin;
        int outExpected, outComputed;

        vec = vector<int>{1, 2, 3, 10, 4, 2, 3, 5};

        val = 2;
        idxBegin = 0;
        outExpected = 1;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        val = 2;
        idxBegin = 1;
        outExpected = 1;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        val = 9;
        idxBegin = 0;
        outExpected = 2;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        val = 10;
        idxBegin = 1;
        outExpected = 7;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        vec = vector<int>{5, 4, 3, 2, 1};

        val = 1;
        idxBegin = 1;
        outExpected = INT_MIN;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        val = 1;
        idxBegin = 3;
        outExpected = INT_MIN;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3};

        val = 2;
        idxBegin = 0;
        outExpected = 1;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        val = 2;
        idxBegin = 1;
        outExpected = 1;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        val = 2;
        idxBegin = 3;
        outExpected = INT_MIN;
        outComputed = soln.moveLeftPtrTowardsRightTillEleLessThanEqualToVal(vec, idxBegin, val);
        assert(outExpected == outComputed);

        printf("[testFindFirstIdxFromRightLessThanOrEqualToVal] All test-cases passed!\n");
    }

    void testFindLengthOfShortestSubarray() {
        Solution soln = Solution();
        vector<int> vec;
        int outExpected, outComputed;

        vec = vector<int>{1, 2, 3, 10, 4, 2, 3, 5};
        outExpected = 3;
        outComputed = soln.findLengthOfShortestSubarray(vec);
        assert(outExpected == outComputed);

//        soln.enableDebug();
        vec = vector<int>{5, 4, 3, 2, 1};
        outExpected = 4;
        outComputed = soln.findLengthOfShortestSubarray(vec);
//        printf("[testFindLengthOfShortestSubarray] outExpected=%d, outComputed=%d\n", outExpected, outComputed);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3};
        outExpected = 0;
        outComputed = soln.findLengthOfShortestSubarray(vec);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3, 10, 0, 7, 8, 9};
        outExpected = 2;
        outComputed = soln.findLengthOfShortestSubarray(vec);
//        printf("[testFindLengthOfShortestSubarray] outExpected=%d, outComputed=%d\n", outExpected, outComputed);
        assert(outExpected == outComputed);


//        soln.enableDebug();
        vec = vector<int>{2, 2, 2, 1, 1, 1};
        outExpected = 3;
        outComputed = soln.findLengthOfShortestSubarray(vec);
//        printf("[testFindLengthOfShortestSubarray] outExpected=%d, outComputed=%d\n", outExpected, outComputed);
        assert(outExpected == outComputed);
//        soln.disableDebug();

        vec = vector<int>{1, 1, 1, 2, 2, 2, 2};
        outExpected = 0;
        outComputed = soln.findLengthOfShortestSubarray(vec);
        assert(outExpected == outComputed);

        vec = vector<int>{3, 3, 2, 2, 2, 1, 23, 1, 1, 1};
        outExpected = 7;
        outComputed = soln.findLengthOfShortestSubarray(vec);
        assert(outExpected == outComputed);


//        soln.enableDebug();
        vec = vector<int>{3, 3, 2, 2, 2, 1, 1, 1, 1};
        outExpected = 5;
        outComputed = soln.findLengthOfShortestSubarray(vec);
//        printf("[testFindLengthOfShortestSubarray] outExpected=%d, outComputed=%d\n", outExpected, outComputed);
        assert(outExpected == outComputed);
//        soln.disableDebug();

//        soln.enableDebug();
        vec = vector<int>{1, 3, 2, 4};
        outExpected = 1;
        outComputed = soln.findLengthOfShortestSubarray(vec);
//        printf("[testFindLengthOfShortestSubarray] outExpected=%d, outComputed=%d\n", outExpected, outComputed);
        assert(outExpected == outComputed);
//        soln.disableDebug();

        printf("[testFindLengthOfShortestSubarray] All test-cases passed!\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindInflexionPointFromLeft();
    solnTest.testFindInflexionPointFromRight();
    solnTest.testMoveLeftPtrTowardsRightTillEleLessThanEqualToVal();
    solnTest.testFindLengthOfShortestSubarray();

    return 0;
}
