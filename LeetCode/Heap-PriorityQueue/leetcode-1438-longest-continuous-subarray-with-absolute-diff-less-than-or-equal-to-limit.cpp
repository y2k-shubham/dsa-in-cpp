// LeetCode-1438: https://leetcode.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   public:
    friend class SolutionTest;

    int longestSubarray(vector<int>& nums, int limit) {
        int len = nums.size();
        if (len <= 1) {
            return len;
        }

        int maxWinLen = 1;
        int maxWinLoInd, maxWinHiInd;

        int lo = 0, hi = 0;
        int crrMin = nums[0], crrMax = nums[0];

        map<int, int> freqMap;
        freqMap[nums[0]]++;
        while (max(lo, hi) < len) {
            // shrink window
            while (abs(crrMax - crrMin) > limit) {
                // printf("1 nums[lo=%d] = %d, nums[hi=%d] = %d, crrMin = %d, crrMax = %d\n", lo, nums[lo], hi, nums[hi], crrMin, crrMax);
                int outEle = nums[lo];
                freqMap[outEle]--;
                if (freqMap[outEle] == 0) {
                    freqMap.erase(outEle);
                }

                lo++;

                crrMin = freqMap.begin()->first;
                crrMax = freqMap.rbegin()->first;
            }

            // expand window
            // note that without (hi < len) condition, we'll end up in an infinite loop
            while ((hi < len) && abs(crrMax - crrMin) <= limit) {
                // printf("2 nums[lo=%d] = %d, nums[hi=%d] = %d, crrMin = %d, crrMax = %d\n", lo, nums[lo], hi, nums[hi], crrMin, crrMax);
                int crrWinLen = hi - lo + 1;
                if (crrWinLen > maxWinLen) {
                    maxWinLen = crrWinLen;
                    maxWinLoInd = lo;
                    maxWinHiInd = hi;
                }

                hi++;

                if (hi < len) {
                    int inEle = nums[hi];
                    freqMap[inEle]++;

                    crrMin = freqMap.begin()->first;
                    crrMax = freqMap.rbegin()->first;
                }
            }
        }

        return maxWinLen;
    }
};

class SolutionTest {
   public:
    void testLongestSubarray() {
        Solution soln = Solution();
        vector<int> vec;
        int limit;
        int outExpected, outComputed;

        vec = {};
        limit = 5;
        outExpected = 0;
        outComputed = soln.longestSubarray(vec, limit);
        assert(outExpected == outComputed);

        vec = {4};
        limit = 5;
        outExpected = 1;
        outComputed = soln.longestSubarray(vec, limit);
        assert(outExpected == outComputed);

        vec = {4, 2};
        limit = 5;
        outExpected = 2;
        outComputed = soln.longestSubarray(vec, limit);
        assert(outExpected == outComputed);

        vec = {8, 2, 4, 7};
        limit = 4;
        outExpected = 2;
        outComputed = soln.longestSubarray(vec, limit);
        assert(outExpected == outComputed);

        vec = {10, 1, 2, 4, 7, 2};
        limit = 5;
        outExpected = 4;
        outComputed = soln.longestSubarray(vec, limit);
        assert(outExpected == outComputed);

        vec = {4, 2, 2, 2, 4, 4, 2, 2};
        limit = 0;
        outExpected = 3;
        outComputed = soln.longestSubarray(vec, limit);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testLongestSubarray();
}
