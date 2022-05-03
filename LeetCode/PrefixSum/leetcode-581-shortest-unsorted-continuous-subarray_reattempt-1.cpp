// LeetCode-581: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    vector<int> buildMinValRightIdxVec(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> minValRightIdxVec(len, len);
        int minValRight = INT_MAX;
        int minValRightIdx = len;
        for (int i = len - 1; i >= 0; i--) {
            int crrVal = vec[i];
            if (crrVal < minValRight) {
                minValRight = crrVal;
                minValRightIdx = i;
            }

            minValRightIdxVec[i] = minValRightIdx;
        }

        return minValRightIdxVec;
    }

    vector<int> buildMaxValLeftIdxVec(vector<int>& vec) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> maxValLeftIdxVec(len, -1);
        int maxValLeft = INT_MIN;
        int maxValLeftIdx = -1;
        for (int i = 0; i < len; i++) {
            int crrVal = vec[i];
            if (crrVal > maxValLeft) {
                maxValLeft = crrVal;
                maxValLeftIdx = i;
            }

            maxValLeftIdxVec[i] = maxValLeftIdx;
        }

        return maxValLeftIdxVec;
    }

    void showVec(vector<int>& vec, string name) {
        printf("%s vec is:-\n", name.c_str());

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    int findInflexionIdxLeft(vector<int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return 1;
        }

        vector<int> minValRightIdxVec = buildMinValRightIdxVec(vec);
        if (debug) {
            showVec(minValRightIdxVec, "minValRightIdxVec");
        }

        for (int i = 0; i < len - 1; i++) {
            int crrVal = vec[i];

            int minValRightIdx = minValRightIdxVec[i + 1];
            int minValRight = (minValRightIdx < len) ? vec[minValRightIdx] : INT_MAX;

            if (crrVal > minValRight) {
                return i;
            }
        }

        return len;
    }

    int findInflexionIdxRight(vector<int>& vec) {
        int len = vec.size();
        if (len <= 1) {
            return -1;
        }

        vector<int> maxValLeftIdxVec = buildMaxValLeftIdxVec(vec);
        for (int i = len - 1; i > 0; i--) {
            int crrVal = vec[i];

            int maxValLeftIdx = maxValLeftIdxVec[i - 1];
            int maxValLeft = (maxValLeftIdx >= 0) ? vec[maxValLeftIdx] : INT_MIN;

            if (maxValLeft > crrVal) {
                return i;
            }
        }

        return -1;
    }

public:
    friend class SolutionTest;

    int findUnsortedSubarray(vector<int>& nums) {
        int len = nums.size();
        if (len <= 1) {
            return 0;
        }

        int inflexionIdxLeft = findInflexionIdxLeft(nums);
        int inflexionIdxRight = findInflexionIdxRight(nums);

        if ((inflexionIdxLeft >= len) && (inflexionIdxRight <= 0)) {
            return 0;
        } else if ((inflexionIdxLeft >= len) || (inflexionIdxRight <= 0)) {
            return INT_MAX;
        } else {
            return inflexionIdxRight - inflexionIdxLeft + 1;
        }
    }
};

class SolutionTest {
public:
    void testFindInflexionIdxLeft() {
        Solution soln = Solution();
        vector<int> vecIn;
        int idxOutExpected, idxOutComputed;

        vecIn = {};
        idxOutExpected = 1;
        idxOutComputed = soln.findInflexionIdxLeft(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {5};
        idxOutExpected = 1;
        idxOutComputed = soln.findInflexionIdxLeft(vecIn);
        assert(idxOutExpected == idxOutComputed);

//        soln.debug = true;
        vecIn = {5, 6};
        idxOutExpected = 2;
        idxOutComputed = soln.findInflexionIdxLeft(vecIn);
//        cout << idxOutComputed << endl;
        assert(idxOutExpected == idxOutComputed);
//        soln.debug = false;

        vecIn = {6, 5};
        idxOutExpected = 0;
        idxOutComputed = soln.findInflexionIdxLeft(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {2, 6, 4, 8, 10, 9, 15};
        idxOutExpected = 1;
        idxOutComputed = soln.findInflexionIdxLeft(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {1, 2, 3, 4};
        idxOutExpected = 4;
        idxOutComputed = soln.findInflexionIdxLeft(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {1};
        idxOutExpected = 1;
        idxOutComputed = soln.findInflexionIdxLeft(vecIn);
        assert(idxOutExpected == idxOutComputed);
    }

    void testFindInflexionIdxRight() {
        Solution soln = Solution();
        vector<int> vecIn;
        int idxOutExpected, idxOutComputed;

        vecIn = {};
        idxOutExpected = -1;
        idxOutComputed = soln.findInflexionIdxRight(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {5};
        idxOutExpected = -1;
        idxOutComputed = soln.findInflexionIdxRight(vecIn);
        assert(idxOutExpected == idxOutComputed);

//        soln.debug = true;
        vecIn = {5, 6};
        idxOutExpected = -1;
        idxOutComputed = soln.findInflexionIdxRight(vecIn);
//        cout << idxOutComputed << endl;
        assert(idxOutExpected == idxOutComputed);
//        soln.debug = false;

        vecIn = {6, 5};
        idxOutExpected = 1;
        idxOutComputed = soln.findInflexionIdxRight(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {2, 6, 4, 8, 10, 9, 15};
        idxOutExpected = 5;
        idxOutComputed = soln.findInflexionIdxRight(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {1, 2, 3, 4};
        idxOutExpected = -1;
        idxOutComputed = soln.findInflexionIdxRight(vecIn);
        assert(idxOutExpected == idxOutComputed);

        vecIn = {1};
        idxOutExpected = -1;
        idxOutComputed = soln.findInflexionIdxRight(vecIn);
        assert(idxOutExpected == idxOutComputed);
    }

    void testFindUnsortedSubarray() {
        Solution soln = Solution();
        vector<int> vecIn;
        int lenOutExpected, lenOutComputed;

        vecIn = {};
        lenOutExpected = 0;
        lenOutComputed = soln.findUnsortedSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);

        vecIn = {5};
        lenOutExpected = 0;
        lenOutComputed = soln.findUnsortedSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);

//        soln.debug = true;
        vecIn = {5, 6};
        lenOutExpected = 0;
        lenOutComputed = soln.findUnsortedSubarray(vecIn);
//        cout << lenOutComputed << endl;
        assert(lenOutExpected == lenOutComputed);
//        soln.debug = false;

        vecIn = {6, 5};
        lenOutExpected = 2;
        lenOutComputed = soln.findUnsortedSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);

        vecIn = {2, 6, 4, 8, 10, 9, 15};
        lenOutExpected = 5;
        lenOutComputed = soln.findUnsortedSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);

        vecIn = {1, 2, 3, 4};
        lenOutExpected = 0;
        lenOutComputed = soln.findUnsortedSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);

        vecIn = {1};
        lenOutExpected = 0;
        lenOutComputed = soln.findUnsortedSubarray(vecIn);
        assert(lenOutExpected == lenOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindInflexionIdxLeft();
    solnTest.testFindInflexionIdxRight();
    solnTest.testFindUnsortedSubarray();

    return 0;
}
