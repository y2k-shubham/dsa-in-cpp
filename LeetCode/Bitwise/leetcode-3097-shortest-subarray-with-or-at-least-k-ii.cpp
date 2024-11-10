// LeetCode-3097: https://leetcode.com/problems/shortest-subarray-with-or-at-least-k-ii/
// TimeComplexity: O(32n) => O(n)

// good question
// core idea of maintaining bit-frequency table for reversing bitwise-OR operation taken from here https://stackoverflow.com/a/61306206/3679900

#include <vector>
#include <utility>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    inline void showVec(vector<int>& vec) {
        printf("vec is:-\n");

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
    }

    inline int findHighestSetBitIndex(vector<int>& bitFreqVec) {
        int highestSetBitIndex = -1;
        for (int i = 31; i >= 0; i--) {
            if (bitFreqVec[i] > 0) {
                highestSetBitIndex = i;
                break;
            }
        }

        return highestSetBitIndex;
    }

    inline void showBitFreqVec(vector<int>& bitFreqVec) {
        printf("bitFreqVec is \n");

        int highestSetBitIndex = findHighestSetBitIndex(bitFreqVec);

        printf("Idx:\t");
        for (int i = highestSetBitIndex; i >= 0; i--) {
            printf("[%d]\t", i);
        }
        printf("\n");

        printf("Freq:\t");
        for (int i = highestSetBitIndex; i >= 0; i--) {
            printf("%d\t", bitFreqVec[i]);
        }
        printf("\n");
    }

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    vector<int> createBitFreqVec(int num) {
        vector<int> bitFreqVec(32, 0);

        for (int i = 0; i < 32; i++) {
            if ((num & (1 << i)) > 0) {
                bitFreqVec[i]++;
            }
        }

        return bitFreqVec;
    }

    inline int calcOrOfBitwiseRepresentation(vector<int>& bitFreqVec) {
        int orRes = 0;
        for (int i = 0; i < 32; i++) {
            if (bitFreqVec[i] > 0) {
                orRes |= (1 << i);
            }
        }

        return orRes;
    }

    inline void updateBitwiseRepresentationAddNum(vector<int>& bitFreqVec, int num) {
        for (int i = 0; i < 32; i++) {
            if ((num & (1 << i)) > 0) {
                bitFreqVec[i]++;
            }
        }
    }

    inline void updateBitwiseRepresentationSubtractNum(vector<int>& bitFreqVec, int num) {
        for (int i = 0; i < 32; i++) {
            if ((num & (1 << i)) > 0) {
                bitFreqVec[i]--;
            }
        }
    }

    inline pair<int, int> expandWindowTillOrLessThanK(vector<int>& vec, int k, vector<int>& bitFreqVec, int crrOr, int j) {
        ++j;

        int len = vec.size();
        while ((j < len) && (crrOr < k)) {
            int crrEle = vec[j];

            updateBitwiseRepresentationAddNum(bitFreqVec, crrEle);
            crrOr |= crrEle;

            j++;
        }

        j--;

        return {j, crrOr};
    }

    inline pair<int, int> shrinkWindowTillOrGreaterThanK(vector<int>& vec, int k, int& minSubArrLen, vector<int>& bitFreqVec, int crrOr, int i, int j) {
        while ((i < j) && (crrOr >= k)) {
            int crrEle = vec[i];

            updateBitwiseRepresentationSubtractNum(bitFreqVec, crrEle);
            crrOr = calcOrOfBitwiseRepresentation(bitFreqVec);

            i++;

            if (crrOr >= k) {
                minSubArrLen = min(minSubArrLen, j - i + 1);
            }
        }

        // maybe redundant
        if (i == j) {
            crrOr = vec[i];
            bitFreqVec = createBitFreqVec(crrOr);
        }

        return {i, crrOr};
    }

public:
    friend class SolutionTest;

    int minimumSubarrayLength(vector<int>& nums, int k) {
        if (k == 0) {
            return 1;
        }

        // find maximum element of nums using std::max_element
        int maxEle = *max_element(nums.begin(), nums.end());
        if (maxEle >= k) {
            return 1;
        }

        if (debug) {
            showVec(nums);
        }

        int len = nums.size();

        int i = 0;
        int j = 0;
        int crrOr = nums[0];
        vector<int> bitFreqVec = createBitFreqVec(crrOr);
        int minSubArrLen = INT_MAX;

        while (j < len) {
            if (crrOr < k) {
                if (j >= (len - 1)) {
                    // can't expand window any further, so break
                    break;
                }

                // expand window (increase j) until crrOr < k
                auto mPair = expandWindowTillOrLessThanK(nums, k, bitFreqVec, crrOr, j);
                j = mPair.first;
                crrOr = mPair.second;

                if (crrOr >= k) {
                    int crrSubArrLen = j - i + 1;
                    minSubArrLen = min(minSubArrLen, crrSubArrLen);
                }

                if (debug) {
                    printf("\n---after expanding window---\n\n");
                    if (j < len) {
                        printf("vec[i=%d .. j=%d] = [%d .. %d], crrOr=%d\n", i, j, nums[i], nums[j], crrOr);
                    } else {
                        printf("vec[i=%d .. j=%d] = [%d .. XX), crrOr=%d\n", i, j, nums[i], crrOr);
                    }
                    showBitFreqVec(bitFreqVec);
                    if (crrOr >= k) {
                        int crrSubArrLen = j - i + 1;
                        printf("crrSubArrLen=%d, minSubArrLen=%d\n", crrSubArrLen, minSubArrLen);
                    }
                    printf("\n-----\n");
                }
            } else {
                // shrink window (increase i) until crrOr >= k
                auto mPair = shrinkWindowTillOrGreaterThanK(nums, k, minSubArrLen, bitFreqVec, crrOr, i, j);
                i = mPair.first;
                crrOr = mPair.second;

                if (debug) {
                    int crrSubArrLen = j - i + 1;
                    printf("\n---after shrinking window---\n\n");
                    printf("vec[i=%d .. j=%d] = [%d .. %d], crrOr=%d\n", i, j, nums[i], nums[j], crrOr);
                    showBitFreqVec(bitFreqVec);
                    printf("crrSubArrLen=%d, minSubArrLen=%d\n", crrSubArrLen, minSubArrLen);
                    printf("\n-----\n");
                }
            }
        }

        return (minSubArrLen == INT_MAX) ? -1 : minSubArrLen;
    }
};

class SolutionTest {
public:
    void testMinimumSubarrayLength() {
        Solution soln = Solution();
        vector<int> vecIn;
        int kIn;
        int lenOutExpected, lenOutComputed;

        vecIn = {1, 2, 3};
        kIn = 2;
        lenOutExpected = 1;
        lenOutComputed = soln.minimumSubarrayLength(vecIn, kIn);
        assert(lenOutExpected == lenOutComputed);

//        soln.enableDebug();
        vecIn = {2, 1, 8};
        kIn = 10;
        lenOutExpected = 3;
        lenOutComputed = soln.minimumSubarrayLength(vecIn, kIn);
        assert(lenOutExpected == lenOutComputed);
//        soln.disableDebug();

        vecIn = {1, 2};
        kIn = 0;
        lenOutExpected = 1;
        lenOutComputed = soln.minimumSubarrayLength(vecIn, kIn);
        assert(lenOutExpected == lenOutComputed);

//        soln.enableDebug();
        vecIn = {8, 1, 3, 7, 4, 2, 9};
        kIn = 16;
        lenOutExpected = -1;
        lenOutComputed = soln.minimumSubarrayLength(vecIn, kIn);
        assert(lenOutExpected == lenOutComputed);
//        soln.disableDebug();

        printf("[testMinimumSubarrayLength] All test-cases passed!\n");
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testMinimumSubarrayLength();

    return 0;
}
