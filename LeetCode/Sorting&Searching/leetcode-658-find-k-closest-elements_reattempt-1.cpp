// LeetCode-658: https://leetcode.com/problems/find-k-closest-elements/
// good question: quite a few edge cases

#include <vector>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    pair<int, vector<int>::iterator> findLowerBoundIdxAndItr(vector<int>& vec, int target) {
        vector<int>::iterator lowerBoundItr = lower_bound(vec.begin(), vec.end(), target);
        int lowerBoundIdx = lowerBoundItr - vec.begin();
        return {lowerBoundIdx, lowerBoundItr};
    }

    pair<int, vector<int>::iterator> findUpperBoundIdxAndItr(vector<int>& vec, int target) {
        vector<int>::iterator upperBoundItr = upper_bound(vec.begin(), vec.end(), target);
        int upperBoundIdx = upperBoundItr - vec.begin();
        return {upperBoundIdx, upperBoundItr};
    }

    int calcAbsDiff(long long target, long long ele) {
        int minEle = min(target, ele);
        int maxEle = max(target, ele);

        if (minEle == INT_MIN) {
            return (maxEle == INT_MIN) ? 0 : INT_MAX;
        }
        if (maxEle == INT_MAX) {
            return (minEle == INT_MAX) ? 0 : INT_MAX;
        }

        return abs(target - ele);
    }

    bool isEle1Closer(long long target, long long ele1, long long ele2) {
        return calcAbsDiff(target, ele1) <= calcAbsDiff(target, ele2);
    }

    bool isBeginningOfArr(int idx) {
        return idx == 0;
    }

    bool isEndOfArr(int len, int idx) {
        return (len - 1) <= idx;
    }

    pair<int, int> findKClosestElesRange(vector<int>& vec, int k, int target, int iLo, int iHi) {
        if ((iHi - iLo + 1) >= k) {
            // target occurs more than k times in vec
            return {iLo, iLo + k - 1};
        }

        int len = vec.size();

        // note that here the range of elements included in our selection is [iLo .. iHi] (both inclusive)
        while ((iHi - iLo + 1) < k) {
            int prevEle = (iLo > 0) ? vec[iLo - 1] : INT_MIN;
            int nextEle = (iHi < (len - 1)) ? vec[iHi + 1] : INT_MAX;

            if (isEle1Closer(target, prevEle, nextEle) || isEndOfArr(len, iHi)) {
                iLo--;
            } else {
                iHi++;
            }
        }

        return {iLo, iHi};
    }

public:
    friend class SolutionTest;

    Solution() {
        disableDebug();
    }

    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int len = arr.size();
        if (len <= k) {
            return arr;
        }

        pair<int, vector<int>::iterator> lowerBoundIdxAndItr = findLowerBoundIdxAndItr(arr, x);
        int lowerBoundIdx = lowerBoundIdxAndItr.first;
        vector<int>::iterator lowerBoundItr = lowerBoundIdxAndItr.second;

        if (debug) {
            printf("lowerBound = arr[idx=%d] = %d\n", lowerBoundIdx, arr[lowerBoundIdx]);
        }

        if (lowerBoundIdx == 0) {
            // all elements in arr are greater than x,
            // so then just return first k (smallest) elements
            return vector<int>(arr.begin(), arr.begin() + k);
        }

        if (lowerBoundIdx >= len) {
            // all elements in arr are lesser than x,
            // so then just return last k (biggest) elements
            return vector<int>(arr.end() - k, arr.end());
        }

        pair<int, vector<int>::iterator> upperBoundIdxAndIter = findUpperBoundIdxAndItr(arr, x);
        int upperBoundIdx = upperBoundIdxAndIter.first;
        vector<int>::iterator upperBoundItr = upperBoundIdxAndIter.second;

        if (debug) {
            printf("upperBound = arr[idx=%d] = %d\n", upperBoundIdx, arr[upperBoundIdx]);
        }

        int iLo = lowerBoundIdx;
        int iHi = upperBoundIdx;
        if (lowerBoundIdx != upperBoundIdx) {
            // target is present in array
            // so then here we'll have iLo = idx of first occurrence of x in arr
            //                     and iHi = idx of last  occurrence of x in arr
            // and of course iLo and iHi could be same also
            iHi = upperBoundIdx - 1;
        } else {
            // target is absent in array
            // so then here we'll have iLo = iHi = idx of element closest to x in arr
            iLo--;
            if (debug) {
                printf("after deducting iLo = %d, iHi = %d\n", iLo, iHi);
            }
            int closestEleIdx = isEle1Closer(x, arr[iLo], arr[iHi]) ? iLo : iHi;
            iHi = iLo = closestEleIdx;
            if (debug) {
                printf("after finding closestEleIdx closestEleIdx = %d, iLo = %d, iHi = %d\n", closestEleIdx, iLo, iHi);
            }
        }

        if (debug) {
            printf("iLo = arr[idx=%d] = %d\t\tand iHi = arr[idx=%d] = %d\n", iLo, arr[iLo], iHi, arr[iHi]);
        }

        // note that at this point the range of elements included in our selection is [iLo .. iHi] (both inclusive)

        if (k == 1) {
            // Note: this can actually never happen because the the beginning itself we had checked whether len <= k
            // only one element to be returned
            // return just iLo or iHi (anyone would work)
            return vector<int>{arr[iLo]};
        }

        // find range of indices for k closest elements
        pair<int, int> kClosestElesIdxRange = findKClosestElesRange(arr, k, x, iLo, iHi);

        // return 'slice' of k closest elements range
        return vector<int>(arr.begin() + kClosestElesIdxRange.first, arr.begin() + kClosestElesIdxRange.second + 1);
    }
};

class SolutionTest {
public:
    void testFindLowerBoundIdxAndItr() {
        Solution soln = Solution();
        vector<int> vecIn;
        int targetIn;
        int idxOutExpected, idxOutComputed;

        vecIn = {1, 1, 1, 10, 10, 10};
        targetIn = 9;
        idxOutExpected = 3;
        idxOutComputed = soln.findLowerBoundIdxAndItr(vecIn, targetIn).first;
        assert(idxOutExpected == idxOutComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        targetIn = 8;
        idxOutExpected = 3;
        idxOutComputed = soln.findLowerBoundIdxAndItr(vecIn, targetIn).first;
        assert(idxOutExpected == idxOutComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        targetIn = 7;
        idxOutExpected = 3;
        idxOutComputed = soln.findLowerBoundIdxAndItr(vecIn, targetIn).first;
        assert(idxOutExpected == idxOutComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        targetIn = 6;
        idxOutExpected = 3;
        idxOutComputed = soln.findLowerBoundIdxAndItr(vecIn, targetIn).first;
        assert(idxOutExpected == idxOutComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        targetIn = 5;
        idxOutExpected = 3;
        idxOutComputed = soln.findLowerBoundIdxAndItr(vecIn, targetIn).first;
        assert(idxOutExpected == idxOutComputed);
    }

    void testCalcAbsDiff() {
        Solution soln = Solution();
        int ele1In, ele2In;
        int outExpected, outComputed;

        ele1In = 9;
        ele2In = 19;
        outExpected = 10;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);

        ele1In = -9;
        ele2In = 19;
        outExpected = 28;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);

        ele1In = -9;
        ele2In = -19;
        outExpected = 10;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);

        ele1In = INT_MIN;
        ele2In = -19;
        outExpected = INT_MAX;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);

        ele1In = INT_MIN;
        ele2In = INT_MIN;
        outExpected = 0;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);

        ele1In = INT_MIN;
        ele2In = INT_MAX;
        outExpected = INT_MAX;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);

        ele1In = 9;
        ele2In = INT_MAX;
        outExpected = INT_MAX;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);

        ele1In = INT_MAX;
        ele2In = INT_MAX;
        outExpected = 0;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);

        ele1In = INT_MIN;
        ele2In = INT_MAX;
        outExpected = INT_MAX;
        outComputed = soln.calcAbsDiff(ele1In, ele2In);
        assert(outExpected == outComputed);
    }

    void testIsEle1Closer() {
        Solution soln = Solution();
        int targetIn, ele1In, ele2In;
        bool outExpected, outComputed;

        targetIn = 5;
        ele1In = 3;
        ele2In = 7;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = 3;
        ele2In = 6;
        outExpected = false;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = 3;
        ele2In = 8;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = 3;
        ele2In = 5;
        outExpected = false;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = 4;
        ele2In = 5;
        outExpected = false;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = 5;
        ele2In = 5;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = 5;
        ele2In = 7;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = 5;
        ele2In = 6;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = INT_MIN;
        ele2In = 6;
        outExpected = false;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = -15;
        ele2In = INT_MIN;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = 191;
        ele2In = INT_MAX;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = INT_MAX;
        ele2In = -16;
        outExpected = false;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = INT_MIN;
        ele2In = INT_MAX;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = INT_MIN;
        ele2In = INT_MIN;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 5;
        ele1In = INT_MAX;
        ele2In = INT_MAX;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 9;
        ele1In = 1;
        ele2In = 10;
        outExpected = false;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 9;
        ele1In = 10;
        ele2In = 1;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 6;
        ele1In = 1;
        ele2In = 10;
        outExpected = false;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);

        targetIn = 6;
        ele1In = 10;
        ele2In = 1;
        outExpected = true;
        outComputed = soln.isEle1Closer(targetIn, ele1In, ele2In);
        assert(outExpected == outComputed);
    }

    void testFindKClosestElesRange() {
        Solution soln = Solution();
        vector<int> vecIn;
        int kIn, targetIn;
        int iLoIn, iHiIn;
        pair<int, int> outExpected, outComputed;

        // target = 9

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        targetIn = 9;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {3, 3};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 2;
        targetIn = 9;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {3, 4};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 3;
        targetIn = 9;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {3, 5};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 4;
        targetIn = 9;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {2, 5};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 5;
        targetIn = 9;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {1, 5};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        // target = 6

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        targetIn = 6;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {3, 3};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 2;
        targetIn = 6;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {3, 4};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 3;
        targetIn = 6;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {3, 5};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 4;
        targetIn = 6;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {2, 5};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 5;
        targetIn = 6;
        iLoIn = 3;
        iHiIn = 3;
        outExpected = {1, 5};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        // target = 5

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        targetIn = 5;
        iLoIn = 2;
        iHiIn = 2;
        outExpected = {2, 2};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 2;
        targetIn = 5;
        iLoIn = 2;
        iHiIn = 2;
        outExpected = {1, 2};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 3;
        targetIn = 5;
        iLoIn = 2;
        iHiIn = 2;
        outExpected = {0, 2};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 4;
        targetIn = 5;
        iLoIn = 2;
        iHiIn = 2;
        outExpected = {0, 3};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        // target = 1

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        targetIn = 1;
        iLoIn = 0;
        iHiIn = 2;
        outExpected = {0, 0};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 2;
        targetIn = 1;
        iLoIn = 0;
        iHiIn = 2;
        outExpected = {0, 1};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 3;
        targetIn = 1;
        iLoIn = 0;
        iHiIn = 2;
        outExpected = {0, 2};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 4;
        targetIn = 1;
        iLoIn = 0;
        iHiIn = 2;
        outExpected = {0, 3};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        // target = 10

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        targetIn = 10;
        iLoIn = 3;
        iHiIn = 5;
        outExpected = {3, 3};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 2;
        targetIn = 10;
        iLoIn = 3;
        iHiIn = 5;
        outExpected = {3, 4};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 3;
        targetIn = 10;
        iLoIn = 3;
        iHiIn = 5;
        outExpected = {3, 5};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 10, 10, 10};
        kIn = 4;
        targetIn = 10;
        iLoIn = 3;
        iHiIn = 5;
        outExpected = {2, 5};
        outComputed = soln.findKClosestElesRange(vecIn, kIn, targetIn, iLoIn, iHiIn);
        assert(outExpected == outComputed);
    }

    void testFindClosestElements() {
        Solution soln = Solution();
        vector<int> arrIn;
        int kIn, xIn;
        vector<int> outExpected, outComputed;

        arrIn = {1, 2, 3, 4, 5};
        kIn = 4;
        xIn = 3;
        outExpected = {1, 2, 3, 4};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 1, 2, 3, 4, 5};
        kIn = 4;
        xIn = -1;
        outExpected = {1, 1, 2, 3};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 1, 2, 3, 4, 5};
        kIn = 4;
        xIn = 9;
        outExpected = {2, 3, 4, 5};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 1, 2, 3, 4, 5};
        kIn = 4;
        xIn = 5;
        outExpected = {2, 3, 4, 5};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 1, 2, 3, 4, 5};
        kIn = 4;
        xIn = 1;
        outExpected = {1, 1, 2, 3};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 16, 19, 41, 63, 64, 109, 111, 117, 142, 191};
        kIn = 4;
        xIn = 54;
        outExpected = {19, 41, 63, 64};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 16, 19, 41, 63, 64, 109, 111, 117, 142, 191};
        kIn = 4;
        xIn = 121;
        outExpected = {109, 111, 117, 142};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        xIn = 4;
        outExpected = {1};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        xIn = 5;
        outExpected = {1};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 1, 1, 9, 9, 9};
        kIn = 1;
        xIn = 5;
        outExpected = {1};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        // soln.enableDebug();

        arrIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        xIn = 6;
        outExpected = {10};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {1, 1, 1, 10, 10, 10};
        kIn = 1;
        xIn = 9;
        outExpected = {10};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);

        arrIn = {2, 4, 4, 4, 4, 4, 10, 15};
        kIn = 2;
        xIn = 4;
        outExpected = {4, 4};
        outComputed = soln.findClosestElements(arrIn, kIn, xIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindLowerBoundIdxAndItr();
    solnTest.testCalcAbsDiff();
    solnTest.testIsEle1Closer();
    solnTest.testFindKClosestElesRange();
    solnTest.testFindClosestElements();

    return 0;
}
