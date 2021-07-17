// LeetCode-927: https://leetcode.com/problems/three-equal-parts/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/610/week-3-july-15th-july-21st/3817/

// hard problem
// incomplete (many edge cases / desperately need simpler, less twisted implementation)

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int count1s(vector<int>& vec) {
        int len = vec.size();

        int num1s = 0;
        for (int i = 0; i < len; i++) {
            if (vec[i] == 1) {
                num1s++;
            }
        }

        return num1s;
    }

    int findRightIdxHaving1s(vector<int>& vec, int req1s) {
        int len = vec.size();

        int num1s = 0;
        for (int i = len - 1; i > 1; i--) {
            if (vec[i] == 1) {
                num1s++;

                if (num1s == req1s) {
                    return i;
                }
            }
        }

        return -1;
    }

    vector<int> getBinVectorSlice(vector<int>& vec, int lo, int hi) {
        int startIdx = -1;
        for (startIdx = lo; (startIdx <= hi) && (vec[startIdx] != 1); startIdx++)
            ;

        vector<int> sliceVec;
        for (int i = startIdx; i <= hi; i++) {
            sliceVec.push_back(vec[i]);
        }

        //printf("slicing following vec b/w lo=%d & hi=%d\n", lo, hi);
        //showVec(vec, "vec");
        //showVec(sliceVec, "sliceVec");

        return sliceVec;
    }

    pair<int, vector<int>> getBinVectorSlice(vector<int>& vec, int lo, int req1s, int reqTrailing0s) {
        int len = vec.size();

        int idxFirst1 = -1;
        for (idxFirst1 = lo; idxFirst1 < len; idxFirst1++) {
            if (vec[idxFirst1] == 1) {
                break;
            }
        }
        if (idxFirst1 == len) {
            return {-1, {}};
        }
        // printf("idxFirst1=%d, reqTrailing0s=%d\n", idxFirst1, reqTrailing0s);

        int num1s = 1;
        int hi = idxFirst1;
        while ((hi < len) && (num1s < req1s)) {
            if (vec[hi] == 1) {
                num1s++;

                if (num1s >= req1s) {
                    break;
                }
            }

            hi++;
        }
        // printf("achieved num1s=%d req1s=%d at hi=%d\n", num1s, req1s, hi);
        if ((hi >= len) || (num1s != req1s)) {
            return {-1, {}};
        }

        int numTrailing0s = 0;
        while ((hi < len) && (numTrailing0s < reqTrailing0s)) {
            if (vec[hi] == 0) {
                numTrailing0s++;

                if (numTrailing0s >= reqTrailing0s) {
                    break;
                }
            } else {
                num1s++;
                break;
            }

            hi++;
        }
        // printf("achieved numTrailing0s=%d reqTrailing0s=%d at hi=%d\n", numTrailing0s, reqTrailing0s, hi);
        if ((hi >= len) || (num1s != req1s) || (numTrailing0s != reqTrailing0s)) {
            return {-1, {}};
        }

        return {hi, getBinVectorSlice(vec, idxFirst1, hi)};
    }

    int countTrailing0s(vector<int>& vec) {
        int len = vec.size();

        int numTrailing0s = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (vec[i] == 0) {
                numTrailing0s++;
            } else {
                break;
            }
        }

        return numTrailing0s;
    }

    bool hasAll0s(vector<int>& vec, int lo, int hi) {
        if (lo > hi) {
            return true;
        }

        for (int i = lo; i <= hi; i++) {
            if (vec[i] == 1) {
                return false;
            }
        }

        return true;
    }

    void showVec(vector<int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());
        for (int i = 0; i < vec.size(); i++) {
            printf("%d ", vec[i]);
        }
        cout << endl;
    }

   public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int len = arr.size();

        int num1s = count1s(arr);
        if ((num1s % 3) != 0) {
            return {-1, -1};
        }

        int req1sPerSlice = num1s / 3;
        int maxRightIdx = findRightIdxHaving1s(arr, req1sPerSlice);
        // printf("maxRightIdx=%d\n", maxRightIdx);

        vector<int> rightSlice = getBinVectorSlice(arr, maxRightIdx, len - 1);
        int numTrailing0s = countTrailing0s(rightSlice);
        // showVec(rightSlice, "rightSlice");

        pair<int, vector<int>> leftSliceTuple = getBinVectorSlice(arr, 0, req1sPerSlice, numTrailing0s);
        vector<int> leftSlice = leftSliceTuple.second;
        if (leftSlice.empty()) {
            return {-1, -1};
        }
        int leftIdx = leftSliceTuple.first;
        // showVec(leftSlice, "leftSlice");
        // printf("leftIdx=%d\n", leftIdx);

        pair<int, vector<int>> midSliceTuple = getBinVectorSlice(arr, leftIdx + 1, req1sPerSlice, numTrailing0s);
        vector<int> midSlice = midSliceTuple.second;
        if (midSlice.empty()) {
            return {-1, -1};
        }
        int midIdx = midSliceTuple.first;

        if ((leftIdx >= midIdx) || (midIdx >= maxRightIdx)) {
            return {-1, -1};
        }

        if (!hasAll0s(arr, midIdx + 1, maxRightIdx - 1)) {
            return {-1, -1};
        }

        return {leftIdx, midIdx + 1};
    }
};
