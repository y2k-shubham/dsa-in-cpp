// LeetCode-2012: https://leetcode.com/problems/sum-of-beauty-in-the-array/

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildMaxElePrefixVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> maxElePrefixVec(len, INT_MIN);
        for (int i = 1; i < len; i++) {
            maxElePrefixVec[i] = max(maxElePrefixVec[i - 1], vec[i - 1]);
        }

        return maxElePrefixVec;
    }

    vector<int> buildMinEleSuffixVec(vector<int>& vec) {
        int len = vec.size();

        vector<int> minEleSuffixVec(len, INT_MAX);
        for (int i = len - 2; i >= 0; i--) {
            minEleSuffixVec[i] = min(minEleSuffixVec[i + 1], vec[i + 1]);
        }

        return minEleSuffixVec;
    }

    bool isAdjInOrder(vector<int>& vec, int idx) {
        return (vec[idx - 1] < vec[idx]) && (vec[idx] < vec[idx + 1]);
    }

    int calcSumBeauties(
        vector<int>& vec,
        vector<int>& maxElePrefixVec,
        vector<int>& minEleSuffixVec) {
        int len = vec.size();

        int sumBeauties = 0;
        for (int i = 1; i < len - 1; i++) {
            int crrBeauty = 0;

            if ((maxElePrefixVec[i] < vec[i]) && (vec[i] < minEleSuffixVec[i])) {
                crrBeauty = 2;
            } else if (isAdjInOrder(vec, i)) {
                crrBeauty = 1;
            }

            sumBeauties += crrBeauty;
        }

        return sumBeauties;
    }

   public:
    int sumOfBeauties(vector<int>& nums) {
        vector<int> maxElePrefixVec = buildMaxElePrefixVec(nums);
        vector<int> minEleSuffixVec = buildMinEleSuffixVec(nums);

        return calcSumBeauties(
            nums,
            maxElePrefixVec,
            minEleSuffixVec);
    }
};
