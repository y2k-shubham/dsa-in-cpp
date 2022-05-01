// LeetCode-31: https://leetcode.com/problems/next-permutation/
// TechDose: https://www.youtube.com/watch?v=6qXO72FkqwM

// definitely NOT an easy problem

#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>

using namespace std;

class Solution {
private:
    bool debug = false;

    int findFirstDipIdxFromLeft(vector<int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return -1;
        }

        for (int i = len - 2; i >= 0; i--) {
            if (vec[i] < vec[i + 1]) {
                return i;
            }
        }

        return -1;
    }

    int findOptimalSwapIdxFromLeft(vector<int>& vec, int dipIdx) {
        int len = vec.size();
        if (len <= 1) {
            return -1;
        }

        if ((dipIdx >= len) || (0 > dipIdx)) {
            return -1;
        }

        int dipEle = vec[dipIdx];

        int smallestGreaterEle = INT_MAX;
        int smallestGreaterEleIdx = len;
        for (int i = dipIdx + 1; i < len; i++) {
            int crrEle = vec[i];
            if ((dipEle < crrEle) && (crrEle < smallestGreaterEle)) {
                smallestGreaterEle = crrEle;
                smallestGreaterEleIdx = i;
            }
        }

        return smallestGreaterEleIdx;
    }

    void swapEles(vector<int>& vec, int idx1, int idx2) {
        int tmp = vec[idx1];
        vec[idx1] = vec[idx2];
        vec[idx2] = tmp;
    }

    void debugOutput(vector<int>& vec, int dipIdx, int swapIdx) {
        printf("Idx:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;

        printf("Dip:\t");
        if (dipIdx < 0) {
            printf("%d\n", dipIdx);
        } else {
            for (int i = 0; i < dipIdx; i++) {
                printf("\t");
            }
            cout << '^' << endl;
        }

        printf("Swap:\t");
        if (swapIdx < 0) {
            printf("%d\n", swapIdx);
        } else {
            for (int i = 0; i < swapIdx; i++) {
                printf("\t");
            }
            cout << '^' << endl;
        }
    }

    string convertToStr(vector<int>& vec) {
        if (vec.empty()) {
            return "";
        }

        ostringstream oss;
        oss << vec[0];

        for (int i = 1; i < vec.size(); i++) {
            oss << ',' << vec[i];
        }

        return oss.str();
    }

public:
    friend class SolutionTest;

    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            if (debug) {
                printf("returning because length = %d <= 1\n", len);
            }

            return;
        }

        // find index of first such element from left
        // which is lesser than it's preceding element
        int dipIdx = findFirstDipIdxFromLeft(nums);
        if ((dipIdx < 0) || (len <= dipIdx)) {
            // we are already on greatest permutation

            // next permutation will be the smallest permutation
            // so just sort in ascending order
            sort(nums.begin(), nums.end());
            if (debug) {
                printf("returning smallest permutation = %s because we are already on greatest permutation\n",
                       convertToStr(nums).c_str());
            }

            return;
        }

        // find the index of smallest element on right of dipEle
        // which is still greater than dipEle
        int swapIdx = findOptimalSwapIdxFromLeft(nums, dipIdx);
        if ((swapIdx <= 0) || (swapIdx == dipIdx) || (swapIdx >= len)) {
            // should never happen (some bug in code)
            if (debug) {
                printf("returning because dipIdx = swapIdx = %d\n", dipIdx);
            }
            return;
        }

        if (debug) {
            debugOutput(nums, dipIdx, swapIdx);
        }

        // swap dipEle with swapEle
        swapEles(nums, dipIdx, swapIdx);

        // sort elements beyond dipIdx in ascending order
        sort(nums.begin() + dipIdx + 1, nums.end());
    }
};

class SolutionTest {
public:
    void testFindFirstDipIdxFromLeft() {
        Solution soln = Solution();
        vector<int> vecIn;
        int dipIdxOutExpected, dipIdxOutComputed;

        vecIn = {};
        dipIdxOutExpected = -1;
        dipIdxOutComputed = soln.findFirstDipIdxFromLeft(vecIn);
        assert(dipIdxOutExpected == dipIdxOutComputed);

        vecIn = {5};
        dipIdxOutExpected = -1;
        dipIdxOutComputed = soln.findFirstDipIdxFromLeft(vecIn);
        assert(dipIdxOutExpected == dipIdxOutComputed);

        vecIn = {5, 4};
        dipIdxOutExpected = -1;
        dipIdxOutComputed = soln.findFirstDipIdxFromLeft(vecIn);
        assert(dipIdxOutExpected == dipIdxOutComputed);

        vecIn = {4, 5};
        dipIdxOutExpected = 0;
        dipIdxOutComputed = soln.findFirstDipIdxFromLeft(vecIn);
        assert(dipIdxOutExpected == dipIdxOutComputed);

        vecIn = {1, 2, 3};
        dipIdxOutExpected = 1;
        dipIdxOutComputed = soln.findFirstDipIdxFromLeft(vecIn);
        assert(dipIdxOutExpected == dipIdxOutComputed);

        vecIn = {3, 2, 1};
        dipIdxOutExpected = -1;
        dipIdxOutComputed = soln.findFirstDipIdxFromLeft(vecIn);
        assert(dipIdxOutExpected == dipIdxOutComputed);

        vecIn = {1, 1, 5};
        dipIdxOutExpected = 1;
        dipIdxOutComputed = soln.findFirstDipIdxFromLeft(vecIn);
        assert(dipIdxOutExpected == dipIdxOutComputed);
    }

    void testFindOptimalSwapIdxFromLeft() {
        Solution soln = Solution();
        vector<int> vecIn;
        int dipIdxIn;
        int swapIdxOutExpected, swapIdxOutComputed;

        vecIn = {};
        dipIdxIn = soln.findFirstDipIdxFromLeft(vecIn);
        swapIdxOutExpected = -1;
        swapIdxOutComputed = soln.findOptimalSwapIdxFromLeft(vecIn, dipIdxIn);
        assert(swapIdxOutExpected == swapIdxOutComputed);

        vecIn = {4};
        dipIdxIn = soln.findFirstDipIdxFromLeft(vecIn);
        swapIdxOutExpected = -1;
        swapIdxOutComputed = soln.findOptimalSwapIdxFromLeft(vecIn, dipIdxIn);
        assert(swapIdxOutExpected == swapIdxOutComputed);

        vecIn = {4, 5};
        dipIdxIn = soln.findFirstDipIdxFromLeft(vecIn);
        swapIdxOutExpected = 1;
        swapIdxOutComputed = soln.findOptimalSwapIdxFromLeft(vecIn, dipIdxIn);
        assert(swapIdxOutExpected == swapIdxOutComputed);

        vecIn = {5, 4};
        dipIdxIn = soln.findFirstDipIdxFromLeft(vecIn);
        swapIdxOutExpected = -1;
        swapIdxOutComputed = soln.findOptimalSwapIdxFromLeft(vecIn, dipIdxIn);
        assert(swapIdxOutExpected == swapIdxOutComputed);

        vecIn = {1, 2, 3};
        dipIdxIn = soln.findFirstDipIdxFromLeft(vecIn);
        swapIdxOutExpected = 2;
        swapIdxOutComputed = soln.findOptimalSwapIdxFromLeft(vecIn, dipIdxIn);
        assert(swapIdxOutExpected == swapIdxOutComputed);

        vecIn = {3, 2, 1};
        dipIdxIn = soln.findFirstDipIdxFromLeft(vecIn);
        swapIdxOutExpected = -1;
        swapIdxOutComputed = soln.findOptimalSwapIdxFromLeft(vecIn, dipIdxIn);
        assert(swapIdxOutExpected == swapIdxOutComputed);

        vecIn = {1, 1, 5};
        dipIdxIn = soln.findFirstDipIdxFromLeft(vecIn);
        swapIdxOutExpected = 2;
        swapIdxOutComputed = soln.findOptimalSwapIdxFromLeft(vecIn, dipIdxIn);
        assert(swapIdxOutExpected == swapIdxOutComputed);
    }

    void testNextPermutation() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> vecOutExpected;

        vecIn = {};
        vecOutExpected = {};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {4};
        vecOutExpected = {4};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {4, 4};
        vecOutExpected = {4, 4};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

//        soln.debug = true;
        vecIn = {4, 5};
        vecOutExpected = {5, 4};
        soln.nextPermutation(vecIn);
//        printf("vecOutExpected = %s\n", soln.convertToStr(vecOutExpected).c_str());
//        printf("vecOutComputed = %s\n", soln.convertToStr(vecIn).c_str());
        assert(vecOutExpected == vecIn);
//        soln.debug = false;

        vecIn = {5, 4};
        vecOutExpected = {4, 5};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {1, 2, 3};
        vecOutExpected = {1, 3, 2};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {1, 3, 2};
        vecOutExpected = {2, 1, 3};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {2, 1, 3};
        vecOutExpected = {2, 3, 1};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {2, 3, 1};
        vecOutExpected = {3, 1, 2};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {3, 1, 2};
        vecOutExpected = {3, 2, 1};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {3, 2, 1};
        vecOutExpected = {1, 2, 3};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);

        vecIn = {1, 1, 5};
        vecOutExpected = {1, 5, 1};
        soln.nextPermutation(vecIn);
        assert(vecOutExpected == vecIn);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindFirstDipIdxFromLeft();
    solnTest.testFindOptimalSwapIdxFromLeft();
    solnTest.testNextPermutation();

    return 0;
}
