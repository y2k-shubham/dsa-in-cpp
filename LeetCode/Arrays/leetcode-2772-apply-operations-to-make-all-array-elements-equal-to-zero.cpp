// LeetCode-2772: https://leetcode.com/problems/apply-operations-to-make-all-array-elements-equal-to-zero/
// Not very easy, edge cases require quite a bit of hacks to handle

#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool debug = false;

    inline int findNextNonZeroIndex(vector<int>& vec, int startIdx) {
        for (int i = startIdx; i < vec.size(); i++) {
            if (vec[i] != 0) {
                return i;
            }
        }

        return INT_MAX;
    }

    inline bool subtractFirstValFromNextKElements(vector<int>& vec, int startIdx, int k) {
        if ((startIdx + k - 1) >= vec.size()) {
            return false;
        }

        int subtrahend = vec[startIdx];
        int steps = 0;
        for (int i = startIdx; steps < k; steps++, i++) {
            vec[i] -= subtrahend;
            if (vec[i] < 0) {
                return false;
            }
        }

        return true;
    }

    int countOccurrences(vector<int>& vec, int val) {
        return count(vec.begin(), vec.end(), val);
    }

    bool hasMaxValueAtEnd(vector<int>& vec) {
        vector<int> vecRev = vec;
        reverse(vecRev.begin(), vecRev.end());

        int maxValue = *max_element(vec.begin(), vec.end());

        int leftNonZeroIdx = findNextNonZeroIndex(vec, 0);
        if ((leftNonZeroIdx != INT_MAX) && (countOccurrences(vec, maxValue) == 1) && (vec[leftNonZeroIdx] == maxValue)) {
            return true;
        }

        int rightNonZeroIdx = findNextNonZeroIndex(vecRev, 0);
        if ((rightNonZeroIdx != INT_MAX) && (countOccurrences(vec, maxValue) == 1) && (vecRev[rightNonZeroIdx] == maxValue)) {
            return true;
        }

        return false;
    }

    void showVec(vector<int>& vec, string name, int startIdx, int k) {
        printf("%s vector is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        printf("\n");

        printf("\t");
        for (int i = 0; i < vec.size(); i++) {
            if (i == startIdx) {
                printf("^s\t");
            } else if (i == (startIdx + k - 1)) {
                printf("^e\t");
            } else {
                printf("\t");
            }
        }
        printf("\n");
    }

public:
    friend class SolutionTest;

    bool checkArray(vector<int>& nums, int k) {
        int len = nums.size();
        if (len < k) {
            return false;
        }
        if (k == 1) {
            return true;
        }

        /**
         * this is needed to handle cases like following where a strictly increasing order array is passed
         * resulting in our approach below to break down into O(n * k) complexity instead of O(n + k)
         *
         * how?
         * say input array is [1, 2, 3, ... 99999, 100000] (max-permissible value) and k=40000
         * now our algorithm below will perform as follows
         *  1. take first 40k elements (indexes 0 to 39999) and subtract 1 from them all
         *  2. then proceed by 1-step and take next 40k elements (indexes 1 to 40000) and subtract 1 from them all
         *  ..
         *  and so on
         *
         *  in such case we would run into time-limit-exceeded
         */
        if (hasMaxValueAtEnd(nums)) {
            return false;
        }

        int iter = 0;
        for (
                int nextIdx = findNextNonZeroIndex(nums, 0);
                nextIdx != INT_MAX;
                nextIdx = findNextNonZeroIndex(nums, nextIdx + 1)
                ) {
            if (debug) {
                printf("\n------------\n");
                printf("iter=%d, nextIdx=%d\n", iter++, nextIdx);
            }

            if (!subtractFirstValFromNextKElements(nums, nextIdx, k)) {
                if (debug) {
                    printf("subtractFirstValFromNextKElements returned false\n");
                    printf("\n------------\n");
                }
                return false;
            }
            if (debug) {
                showVec(nums, "nums", nextIdx, k);

                printf("\n------------\n");
            }
        }

        return true;
    }
};

class SolutionTest {
public:
    void testCheckArray() {
        Solution soln = Solution();
        vector<int> vecIn;
        int kIn;
        bool outExpected, outComputed;

        vecIn = {2, 2, 3, 1, 1, 0};
        kIn = 3;
        outExpected = true;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {2, 2, 3, 1, 1, 0};
        kIn = 2;
        outExpected = false;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {2, 2, 3, 1, 1, 0};
        kIn = 1;
        outExpected = true;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {2, 2, 3, 1, 1, 0};
        kIn = 4;
        outExpected = false;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {2, 2, 3, 1, 1, 0};
        kIn = 5;
        outExpected = false;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {1, 3, 1, 1};
        kIn = 2;
        outExpected = false;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 1, 0};
        kIn = 2;
        outExpected = true;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 1, 1};
        kIn = 2;
        outExpected = false;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 2, 1};
        kIn = 2;
        outExpected = true;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {1, 2, 2, 2};
        kIn = 2;
        outExpected = false;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {2, 2, 2, 2};
        kIn = 2;
        outExpected = true;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {2, 2, 2, 2};
        kIn = 4;
        outExpected = true;
        outComputed = soln.checkArray(vecIn, kIn);
        assert(outExpected == outComputed);

        vecIn = {};
        kIn = 40000;
        outExpected = false;
//        outComputed = soln.checkArray(vecIn, kIn);
//        assert(outExpected == outComputed);

        printf("[testCheckArray] All test-cases passed!\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCheckArray();

    return 0;
}
