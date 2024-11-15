// LeetCode-1574: https://leetcode.com/problems/shortest-subarray-to-be-removed-to-make-array-sorted/
// Wrong

#include <vector>
#include <climits>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    int findInflexionPointFromLeft(vector<int>& vec) {
        int len = vec.size();
        for (int i = 1; i < len; i++) {
            if (vec[i] < vec[i - 1]) {
                return i - 1;
            }
        }

        return INT_MAX;
    }

    int findFirstIdxFromLeftGreaterThanOrEqualToVal(vector<int>& vec, int val, int idxBegin) {
        int len = vec.size();
        for (int i = idxBegin; i < len; i++) {
            if (vec[i] >= val) {
                return i;
            }
        }

        // should never happen
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

    int findFirstIdxFromRightLessThanOrEqualToVal(vector<int>& vec, int val, int idxBegin) {
        for (int i = idxBegin; i >= 0; i--) {
            if (vec[i] <= val) {
                return i;
            }
        }

        // should never happen
        return INT_MIN;
    }

public:
    friend class SolutionTest;

    int findLengthOfShortestSubarray(vector<int>& arr) {
        int len = arr.size();
        if (len <= 1) {
//            printf("returning 0 at 1\n");
            return 0;
        }

        int infIdxLeft = findInflexionPointFromLeft(arr);
        if (infIdxLeft == INT_MAX) {
//            printf("returning 0 at 2\n");
            return 0;
        }
        int subArr1Len = len - infIdxLeft - 1;

        int infIdxRight = findInflexionPointFromRight(arr);
        if (infIdxRight == INT_MIN) {
//            printf("returning 0 at 3\n");
            return 0;
        }
        int subArr2Len = infIdxRight;

        int contIdxLeft = findFirstIdxFromLeftGreaterThanOrEqualToVal(arr, arr[infIdxLeft], infIdxLeft + 1);
//        if (contIdxLeft == INT_MAX) {
//            printf("returning diff at 4: (len=%d - infIdxLeft=%d - 1) = %d\n", len, infIdxLeft, len - infIdxLeft - 1);
//            return len - infIdxLeft - 1;
//        }
        int subArr3Len = (contIdxLeft == INT_MAX) ? INT_MAX : (contIdxLeft - infIdxLeft - 1);

        int contIdxRight = findFirstIdxFromRightLessThanOrEqualToVal(arr, arr[infIdxRight], infIdxRight - 1);
//        if (contIdxRight == INT_MIN) {
//            printf("returning diff at 5\n");
//            return subArr2Len;
//        }
        int subArr4Len = (contIdxRight == INT_MIN) ? INT_MAX : (infIdxRight - contIdxRight - 1);

        // print subArr1Len .. subArr4Len
//        printf("subArr1Len = %d, subArr2Len = %d, subArr3Len = %d, subArr4Len = %d\n", subArr1Len, subArr2Len, subArr3Len, subArr4Len);

        return min(
                min(subArr1Len, subArr2Len),
                min(subArr3Len, subArr4Len)
        );
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

    void testFindFirstIdxFromLeftGreaterThanOrEqualToVal() {
        Solution soln = Solution();
        vector<int> vec;
        int val, idxBegin;
        int outExpected, outComputed;

        vec = vector<int>{1, 2, 3, 10, 4, 2, 3, 5};
        val = 10;
        idxBegin = 4;
        outExpected = INT_MAX;
        outComputed = soln.findFirstIdxFromLeftGreaterThanOrEqualToVal(vec, val, idxBegin);
        assert(outExpected == outComputed);

        vec = vector<int>{5, 4, 3, 2, 1};
        val = 5;
        idxBegin = 1;
        outExpected = INT_MAX;
        outComputed = soln.findFirstIdxFromLeftGreaterThanOrEqualToVal(vec, val, idxBegin);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3};
        val = 2;
        idxBegin = 2;
        outExpected = 2;
        outComputed = soln.findFirstIdxFromLeftGreaterThanOrEqualToVal(vec, val, idxBegin);
        assert(outExpected == outComputed);

        printf("[testFindFirstIdxFromLeftGreaterThanOrEqualToVal] All test-cases passed!\n");
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

    void testFindFirstIdxFromRightLessThanOrEqualToVal() {
        Solution soln = Solution();
        vector<int> vec;
        int val, idxBegin;
        int outExpected, outComputed;

        vec = vector<int>{1, 2, 3, 10, 4, 2, 3, 5};
        val = 2;
        idxBegin = 4;
        outExpected = 1;
        outComputed = soln.findFirstIdxFromRightLessThanOrEqualToVal(vec, val, idxBegin);
        assert(outExpected == outComputed);

        vec = vector<int>{5, 4, 3, 2, 1};
        val = 1;
        idxBegin = 3;
        outExpected = INT_MIN;
        outComputed = soln.findFirstIdxFromRightLessThanOrEqualToVal(vec, val, idxBegin);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3};
        val = 3;
        idxBegin = 1;
        outExpected = 1;
        outComputed = soln.findFirstIdxFromRightLessThanOrEqualToVal(vec, val, idxBegin);
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

        vec = vector<int>{5, 4, 3, 2, 1};
        outExpected = 4;
        outComputed = soln.findLengthOfShortestSubarray(vec);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3};
        outExpected = 0;
        outComputed = soln.findLengthOfShortestSubarray(vec);
        assert(outExpected == outComputed);

        vec = vector<int>{1, 2, 3, 10, 0, 7, 8, 9};
        outExpected = 2;
        outComputed = soln.findLengthOfShortestSubarray(vec);
        assert(outExpected == outComputed);

        printf("[testFindLengthOfShortestSubarray] All test-cases passed!\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindInflexionPointFromLeft();
    solnTest.testFindFirstIdxFromLeftGreaterThanOrEqualToVal();
    solnTest.testFindInflexionPointFromRight();
    solnTest.testFindFirstIdxFromRightLessThanOrEqualToVal();
    solnTest.testFindLengthOfShortestSubarray();

    return 0;
}
