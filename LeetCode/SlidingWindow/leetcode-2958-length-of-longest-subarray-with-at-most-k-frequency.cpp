// LeetCode-2958: https://leetcode.com/problems/length-of-longest-subarray-with-at-most-k-frequency/
// Check IMPORTANT comments: those are basic edge-cases for such SlidingWindow questions

#include <unordered_map>
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class Solution {
private:
    int expandWindowTillPossible(
        vector <int>& vec,
        int maxAllowedFreq,
        unordered_map <int, int>& freqMap,
        int beginIdx) {
        int len = vec.size();

        // IMPORTANT: we ought to start with beginIdx + 1, otherwise we'll double-count element at beginIdx
        // (which was already counted during last window expansion)
        for (int i = beginIdx + 1; i < len; i++) {
            int ele = vec[i];
            int crrFreq = freqMap[ele];

            int newFreq = crrFreq + 1;
            freqMap[ele] = newFreq;

            if (newFreq > maxAllowedFreq) {
                return i;
            }
        }

        return len;
    }

    int shrinkWindowTillNecessary(
        vector <int>& vec,
        int maxAllowedFreq,
        unordered_map <int, int>& freqMap,
        int beginIdx) {
        int len = vec.size();

        for (int i = beginIdx; i < len; i++) {
            int ele = vec[i];
            int crrFreq = freqMap[ele];

            int newFreq = crrFreq - 1;
            freqMap[ele] = newFreq;

            if (newFreq == maxAllowedFreq) {
                // IMPORTANT: we ought to return i + 1, otherwise window's last excluded element
                // will not be counted (window will remain 1-len longer than intended)
                return i + 1;
            }
        }

        return len;
    }

public:
    int maxSubarrayLength(vector <int>& nums, int k) {
        int len = nums.size();

        int maxSubarrayLen = 0;
        unordered_map <int, int> freqMap;

        int beginIdx = 0;
        int endIdx = -1;
        bool windowMoved = true;
        while ((endIdx < len) && windowMoved) {
            windowMoved = false;

            int newEndIdx = expandWindowTillPossible(nums, k, freqMap, endIdx);
            if (newEndIdx != endIdx) {
                windowMoved = true;

                int crrSubarrayLen = newEndIdx - max(beginIdx, 0);
                maxSubarrayLen = max(maxSubarrayLen, crrSubarrayLen);

                // printf("expanded: [beginIdx=%d .. newEndIdx=%d), crrSubarrayLen=%d\n", beginIdx, newEndIdx, crrSubarrayLen);

                endIdx = newEndIdx;
            } else {
                // printf("not-expanded: [beginIdx=%d .. newEndIdx=%d]\n", beginIdx, newEndIdx);
            }

            if (endIdx >= len) {
                break;
            }

            int newBeginIdx = shrinkWindowTillNecessary(nums, k, freqMap, beginIdx);
            // printf("shrinked: [newBeginIdx=%d .. endIdx=%d]\n", newBeginIdx, endIdx);
            if (newBeginIdx != beginIdx) {
                windowMoved = true;
                // printf("shrinked: [newBeginIdx=%d .. endIdx=%d]\n", newBeginIdx, endIdx);
                beginIdx = newBeginIdx;
            }
        }

        return maxSubarrayLen;
    }
};

class SolutionTest {
public:
    void testMaxSubarrayLength() {
        Solution soln = Solution();
        vector <int> vecIn;
        int kIn;
        int maxSubarrayLenOutExpected, maxSubarrayLenOutComputed;

        vecIn = {1, 2, 3, 1, 2, 3, 1, 2};
        kIn = 2;
        maxSubarrayLenOutExpected = 6;
        maxSubarrayLenOutComputed = soln.maxSubarrayLength(vecIn, kIn);
        assert(maxSubarrayLenOutExpected == maxSubarrayLenOutComputed);

        vecIn = {1, 2, 1, 2, 1, 2, 1, 2};
        kIn = 1;
        maxSubarrayLenOutExpected = 2;
        maxSubarrayLenOutComputed = soln.maxSubarrayLength(vecIn, kIn);
        assert(maxSubarrayLenOutExpected == maxSubarrayLenOutComputed);

        vecIn = {5, 5, 5, 5, 5, 5, 5};
        kIn = 4;
        maxSubarrayLenOutExpected = 4;
        maxSubarrayLenOutComputed = soln.maxSubarrayLength(vecIn, kIn);
        assert(maxSubarrayLenOutExpected == maxSubarrayLenOutComputed);

        vecIn = {5};
        kIn = 1;
        maxSubarrayLenOutExpected = 1;
        maxSubarrayLenOutComputed = soln.maxSubarrayLength(vecIn, kIn);
        assert(maxSubarrayLenOutExpected == maxSubarrayLenOutComputed);

        vecIn = {5, 8};
        kIn = 1;
        maxSubarrayLenOutExpected = 2;
        maxSubarrayLenOutComputed = soln.maxSubarrayLength(vecIn, kIn);
        assert(maxSubarrayLenOutExpected == maxSubarrayLenOutComputed);

        vecIn = {5, 5};
        kIn = 1;
        maxSubarrayLenOutExpected = 1;
        maxSubarrayLenOutComputed = soln.maxSubarrayLength(vecIn, kIn);
        assert(maxSubarrayLenOutExpected == maxSubarrayLenOutComputed);

        vecIn = {2, 2, 3};
        kIn = 1;
        maxSubarrayLenOutExpected = 2;
        maxSubarrayLenOutComputed = soln.maxSubarrayLength(vecIn, kIn);
        assert(maxSubarrayLenOutExpected == maxSubarrayLenOutComputed);
    }
};

int main(int argc, char* argv[]) {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMaxSubarrayLength();

    return 0;
}
