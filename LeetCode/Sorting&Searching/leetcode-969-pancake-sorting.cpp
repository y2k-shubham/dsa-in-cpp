// LeetCode-969: https://leetcode.com/problems/pancake-sorting/

// AlgorithmsMadeEasy: https://www.youtube.com/watch?v=5BD8i5leLRs
// completely brute-force, simulation-like problem (do as directed; apply no brains)

// solution not accepted at LeetCode because dont know why (their answers are different -> longer in fact)

/**
 * Input
 * [3,2,4,1]
 * Own answer
 * [3,4,2,3,2]
 * LeetCode
 * [4,2,4,3]
 *
 * Input
 * [1,2,3]
 * Own answer
 * []
 * LeetCode
 * []
 *
 * Input
 * [5,6,3,1,2,4]
 * Own answer
 * [2,6,4,3,2]
 * LeetCode
 * [4,6,2,5,1,4,1,3,2,2,1,1,6]
 *
 * Input
 * [6,3,1,2,4,5]
 * Own answer
 * [6,5,3,2]
 * LeetCode
 * [3,6,3,5,1,4,1,3,2,2,1,1,6]
 *
 * Input
 * [3,1,2,4,5,6]
 * Own answer
 * [3,2]
 * LeetCode
 * [2,6,4,5,1,4,1,3,2,2,1,1,6]
 *
 * Input
 * [1,2,4,5,6,3]
 * Own answer
 * [5,6,3,2]
 * LeetCode
 * [1,6,5,5,1,4,1,3,2,2,1,1,6]
 *
 * Input
 * [2,4,5,6,3,1]
 * Own answer
 * [4,6,3,2]
 * LeetCode
 * [6,6,1,5,1,4,1,3,2,2,1,1,6]
 *
 * Input
 * [4,5,6,3,1,2]
 * Own answer
 * [3,6,2,3,2]
 * LeetCode
 * [5,6,1,5,1,4,1,3,2,2,1,1,6]
 *
 * Input
 * [4,1,2,3,5,6]
 * Own answer
 * [4,3]
 * LeetCode
 * [2,6,4,5,4,4,1,3,1,2,1,1,6]
 */

#include <vector>
#include <algorithm>
#include <climits>
#include <list>

using namespace std;

class Solution {
private:
    int findEleIdx(vector<int>& vec, int lo, int hi, int ele) {
        for (int i = lo; i <= hi; i++) {
            if (vec[i] == ele) {
                return i;
            }
        }

        return INT_MIN;
    }

    int skipElesAtCorrectPosn(vector<int>& vec, int hi) {
        while ((hi >= 0) && (vec[hi] == (hi + 1))) {
            hi--;
        }

        return hi;
    }

    list<int> performPancakeFlips(vector<int>& vec, int srcIdx, int dstIdx) {
        list<int> flipIdxs = {};
        if (srcIdx == dstIdx) {
            // do nothing
            return flipIdxs;
        }

        if (srcIdx > 0) {
            // first bring element to 0th index
            reverse(vec.begin(), vec.begin() + srcIdx);
            flipIdxs.push_back(srcIdx + 1);
        }

        if (dstIdx > 0) {
            // then reverse the arr[0 .. dst]
            reverse(vec.begin(), vec.begin() + dstIdx);
            flipIdxs.push_back(dstIdx + 1);
        }

        return flipIdxs;
    }

    vector<int> convertToVec(list<int>& mList) {
        if (mList.empty()) {
            return {};
        }

        vector<int> mVec(mList.begin(), mList.end());
        return mVec;
    }

public:
    vector<int> pancakeSort(vector<int>& arr) {
        int len = arr.size();
        if (len <= 1) {
            return {};
        }

        list<int> flipIdxs = {};

        int maxEle = len;
        int maxIdx = len - 1;
        while (maxEle > 1) {
            maxIdx = skipElesAtCorrectPosn(arr, maxIdx);
            maxEle = maxIdx + 1;
            if (maxEle == 1) {
                break;
            }

            int maxEleIdx = findEleIdx(arr, 0, maxIdx, maxEle);
            if (maxEleIdx == maxIdx) {
                // would never happen because we already have skipElesAtCorrectPosn(..)
                // but just for sake of clarity
                maxEle--;
                maxEleIdx--;
                continue;
            }

            // perform flips
            list<int> crrFlipIdxs = performPancakeFlips(arr, maxEleIdx, maxIdx);
            if (!crrFlipIdxs.empty()) {
                // append flip indexes in result-set
                // https://stackoverflow.com/a/1449735/3679900
                flipIdxs.insert(flipIdxs.end(), crrFlipIdxs.begin(), crrFlipIdxs.end());
            }

            maxEle--;
            maxIdx--;
        }

        return convertToVec(flipIdxs);
    }
};
