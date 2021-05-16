// GFG: https://www.geeksforgeeks.org/check-for-majority-element-in-a-sorted-array/
// LeetCode-1150: https://leetcode.com/problems/check-if-a-number-is-majority-element-in-a-sorted-array/
// BinarySearch soln: https://stackoverflow.com/a/47344672/3679900

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    int binSearchFirstIdx(vector<int>& vec, int ele, int lo, int hi) {
        int len = hi - lo + 1;
        switch (len) {
            case 0:
                return INT_MAX;
                break;

            case 1:
                return (vec[lo] == ele) ? lo : INT_MAX;
                break;

            case 2:
                if (vec[lo] == ele) {
                    return lo;
                } else if (vec[hi] == ele) {
                    return hi;
                } else {
                    return INT_MAX;
                }
                break;

            default:
                int mid = (lo + hi) / 2;
                if (ele < vec[mid]) {
                    return binSearchFirstIdx(vec, ele, lo, mid - 1);
                } else if (vec[mid] == ele) {
                    return min(binSearchFirstIdx(vec, ele, lo, mid - 1), mid);
                } else {
                    return binSearchFirstIdx(vec, ele, mid + 1, hi);
                }
                break;
        }

        return INT_MAX;
    }

    int binSearchLastIdx(vector<int>& vec, int ele, int lo, int hi) {
        int len = hi - lo + 1;
        switch (len) {
            case 0:
                return INT_MIN;
                break;

            case 1:
                return (vec[hi] == ele) ? hi : INT_MIN;
                break;

            case 2:
                if (vec[hi] == ele) {
                    return hi;
                } else if (vec[lo] == ele) {
                    return lo;
                } else {
                    return INT_MIN;
                }
                break;

            default:
                int mid = (lo + hi) / 2;
                if (ele < vec[mid]) {
                    return binSearchLastIdx(vec, ele, lo, mid - 1);
                } else if (vec[mid] == ele) {
                    return max(mid, binSearchLastIdx(vec, ele, mid + 1, hi));
                } else {
                    return binSearchLastIdx(vec, ele, mid + 1, hi);
                }
                break;
        }

        return INT_MIN;
    }

   public:
    bool isMajority(vector<int>& sortedVec, int ele) {
        int len = sortedVec.size();

        switch (len) {
            case 0:
                return false;
                break;

            case 1:
                return sortedVec[0] == ele;
                break;

            default:
                int mid = len / 2;
                if (sortedVec[mid] != ele) {
                    return false;
                }

                int firstIdx = binSearchFirstIdx(sortedVec, ele, 0, len - 1);
                int lastIdx = binSearchLastIdx(sortedVec, ele, 0, len - 1);

                int freq = lastIdx - firstIdx + 1;
                return freq > (len / 2);

                break;
        }
    }

    friend class SolutionTest;
};

class SolutionTest {
   public:
    void testBinSearchFirstIdx() {
        vector<int> vec;
        int ele;
        int idxOutExpected;
        int idxOutComputed;
        Solution soln = Solution();

        vec = {};
        ele = -2;
        idxOutExpected = INT_MAX;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {3};
        ele = -2;
        idxOutExpected = INT_MAX;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = -2;
        idxOutExpected = INT_MAX;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = 1;
        idxOutExpected = 0;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = 2;
        idxOutExpected = INT_MAX;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = 3;
        idxOutExpected = 1;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = 5;
        idxOutExpected = INT_MAX;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 4};
        ele = 4;
        idxOutExpected = 0;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 5, 5, 9};
        ele = 5;
        idxOutExpected = 1;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 5, 9, 9};
        ele = 5;
        idxOutExpected = 1;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 5, 9, 9};
        ele = 9;
        idxOutExpected = 2;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 9, 9, 9};
        ele = 9;
        idxOutExpected = 1;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 4, 4, 4};
        ele = 4;
        idxOutExpected = 0;
        idxOutComputed = soln.binSearchFirstIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);
    }

    void testBinSearchLastIdx() {
        vector<int> vec;
        int ele;
        int idxOutExpected;
        int idxOutComputed;
        Solution soln = Solution();

        vec = {};
        ele = -2;
        idxOutExpected = INT_MIN;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {3};
        ele = -2;
        idxOutExpected = INT_MIN;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = -2;
        idxOutExpected = INT_MIN;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = 1;
        idxOutExpected = 0;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = 2;
        idxOutExpected = INT_MIN;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = 3;
        idxOutExpected = 1;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {1, 3};
        ele = 5;
        idxOutExpected = INT_MIN;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 4};
        ele = 4;
        idxOutExpected = 1;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 5, 5, 9};
        ele = 5;
        idxOutExpected = 2;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 5, 9, 9};
        ele = 5;
        idxOutExpected = 1;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 5, 9, 9};
        ele = 9;
        idxOutExpected = 3;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 9, 9, 9};
        ele = 9;
        idxOutExpected = 3;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);

        vec = {4, 4, 4, 4};
        ele = 4;
        idxOutExpected = 3;
        idxOutComputed = soln.binSearchLastIdx(vec, ele, 0, (((int)vec.size()) - 1));
        assert(idxOutExpected == idxOutComputed);
    }

    void testIsMajority() {
        vector<int> vec;
        int ele;
        bool isMajorityOutExpected;
        bool isMajorityOutComputed;
        Solution soln = Solution();

        vec = {};
        ele = -1;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3};
        ele = -1;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3};
        ele = 3;
        isMajorityOutExpected = true;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 9};
        ele = 3;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 9};
        ele = 8;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 9};
        ele = 9;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 3};
        ele = 3;
        isMajorityOutExpected = true;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 4, 9};
        ele = 3;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 4, 9};
        ele = 4;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 4, 9};
        ele = 9;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 3, 4};
        ele = 3;
        isMajorityOutExpected = true;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 3, 4};
        ele = 4;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 4, 4};
        ele = 3;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 4, 4};
        ele = 4;
        isMajorityOutExpected = true;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 3, 4, 4};
        ele = 3;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 3, 4, 4};
        ele = 4;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 3, 3, 4};
        ele = 3;
        isMajorityOutExpected = true;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 3, 3, 4};
        ele = 4;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 4, 4, 4};
        ele = 3;
        isMajorityOutExpected = false;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);

        vec = {3, 4, 4, 4};
        ele = 4;
        isMajorityOutExpected = true;
        isMajorityOutComputed = soln.isMajority(vec, ele);
        assert(isMajorityOutExpected == isMajorityOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBinSearchFirstIdx();
    solnTest.testBinSearchLastIdx();

    solnTest.testIsMajority();
}
