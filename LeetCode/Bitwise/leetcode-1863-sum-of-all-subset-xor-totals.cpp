// LeetCode-1863: https://leetcode.com/problems/sum-of-all-subset-xor-totals/

#include <vector>

using namespace std;

class Solution {
private:
    // method-1 (incomplete / wrong answer): using recursion

    void subsetXORSumRec(
            vector<int>& vec,
            int reqSubsetSize,
            int crrSubsetSize,
            int crrIdx,
            int crrSum,
            int& totalSum
    ) {
        if ((reqSubsetSize == 0) || (crrSubsetSize > reqSubsetSize)) {
            // base case 1
            return;
        }
        if (crrSubsetSize == 1) {
            // base case 2
            totalSum += vec[crrIdx];
            return;
        }
        if (crrSubsetSize == reqSubsetSize) {
            // base case 3
            totalSum += crrSum;
            return;
        }

        if (crrSum == 0) {
            // first call
            crrSum = vec[crrIdx];
            crrSubsetSize = 1;
        }

        for (int i = (crrIdx + 1); i < vec.size(); i++) {
            subsetXORSumRec(
                    vec,
                    reqSubsetSize,
                    crrSubsetSize,
                    i,
                    crrSum,
                    totalSum
            );

            subsetXORSumRec(
                    vec,
                    reqSubsetSize,
                    crrSubsetSize + 1,
                    i,
                    crrSum ^ vec[i],
                    totalSum
            );
        }
    }

    int method1WrongAnswer(vector<int>& nums) {
        int len = nums.size();

        int totalSum = 0;
        for (int i = 0; i < len; i++) {
            int remLen = len - i;

            for (int size = 1; size <= remLen; size++) {
                subsetXORSumRec(
                        nums,
                        size,
                        0,
                        i,
                        0,
                        totalSum
                );
            }
        }

        return totalSum;
    }

    // method-2 (accepted): using bit-representation
    int subsetXORSumBit(vector<int>& vec) {
        int len = vec.size();

        int totalSum = 0;

        int uLimit = (1 << len) - 1; // (2 ^ len) - 1
        for (int i = 1; i <= uLimit; i++) {
            int _xor = 0;
            for (int j = 0; j < len; j++) {
                if ((i & (1 << j)) > 0) {
                    _xor ^= vec[j];
                }
            }

            totalSum += _xor;
        }

        return totalSum;
    }

public:
    int subsetXORSum(vector<int>& nums) {
        return subsetXORSumBit(nums);
    }
};
