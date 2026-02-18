// LeetCode-2348: https://leetcode.com/problems/number-of-zero-filled-subarrays/
// Permutations and combinations

#include <vector>

using namespace std;

class Solution {
private:
    long long calcSigmaN(int n) {
        return (((long long)n) * (n + 1)) / 2;
    }

    int consumeNonZeroes(vector<int>& vec, int beginIdx) {
        int len = vec.size();

        int i;
        for (i = beginIdx; (i < len) && (vec[i] != 0); i++) {
            // do nothing
        }

        return i;
    }

    int consumeZeroes(vector<int>& vec, int beginIdx) {
        int len = vec.size();

        int i;
        for (i = beginIdx; (i < len) && (vec[i] == 0); i++) {
            // do nothing
        }

        return i;
    }

public:
    long long zeroFilledSubarray(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        int len = nums.size();
        long long totalNumZeroFilledSubArrs = 0;

        int i = 0;
        while (i < len) {
            int zeroesSubArrBeginIdx = consumeNonZeroes(nums, i);
            if (zeroesSubArrBeginIdx >= len) {
                break;
            }

            int zeroesSubArrEndIdx = consumeZeroes(nums, zeroesSubArrBeginIdx) - 1;

            int zeroesSubArrLen = zeroesSubArrEndIdx - zeroesSubArrBeginIdx + 1;

            long long crrNumZeroFilledSubArrs = calcSigmaN(zeroesSubArrLen);
            totalNumZeroFilledSubArrs += crrNumZeroFilledSubArrs;

            i = zeroesSubArrEndIdx + 1;
        }

        return totalNumZeroFilledSubArrs;
    }
};
