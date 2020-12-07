// LeetCode-1289: https://leetcode.com/problems/minimum-falling-path-sum-ii/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> createMemoMat(vector<vector<int>>& A) {
    int len = A.size();

    vector<vector<int>> memoMat(len);
    for (int i = 0; i < len; i++) {
        vector<int> matRow(len, INT_MAX);
        if (i == 0) {
            matRow = A[0];
        }

        memoMat[i] = matRow;
    }

    return memoMat;
}

void calcMinLR(vector<vector<int>>& mat, int row, vector<int>& minL, vector<int>& minR) {
    int len = mat.size();

    int minLVal = INT_MAX;
    for (int j = 0; j < len; j++) {
        minLVal = min(minLVal, mat[row][j]);
        minL[j] = minLVal;
    }

    int minRVal = INT_MAX;
    for (int j = len - 1; j >= 0; j--) {
        minRVal = min(minRVal, mat[row][j]);
        minR[j] = minRVal;
    }
}

void testCalcMinLR() {
    vector<vector<int>> mat;
    int row;
    vector<int> minLExpected;
    vector<int> minRExpected;
    vector<int> minLComputed;
    vector<int> minRComputed;

    mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    row = 0;
    minLExpected = {1, 1, 1};
    minRExpected = {1, 2, 3};
    minLComputed = {INT_MAX, INT_MAX, INT_MAX};
    minRComputed = {INT_MAX, INT_MAX, INT_MAX};
    calcMinLR(mat, row, minLComputed, minRComputed);
    assert(minLExpected == minLComputed);
    assert(minRExpected == minRComputed);

    mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    row = 1;
    minLExpected = {4, 4, 4};
    minRExpected = {4, 5, 6};
    minLComputed = {INT_MAX, INT_MAX, INT_MAX};
    minRComputed = {INT_MAX, INT_MAX, INT_MAX};
    calcMinLR(mat, row, minLComputed, minRComputed);
    assert(minLExpected == minLComputed);
    assert(minRExpected == minRComputed);

    mat = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    row = 2;
    minLExpected = {7, 7, 7};
    minRExpected = {7, 8, 9};
    minLComputed = {INT_MAX, INT_MAX, INT_MAX};
    minRComputed = {INT_MAX, INT_MAX, INT_MAX};
    calcMinLR(mat, row, minLComputed, minRComputed);
    assert(minLExpected == minLComputed);
    assert(minRExpected == minRComputed);

    mat = {
        {8, 1, 3},
        {7, 4, 2},
        {9, 1, 1}};
    row = 0;
    minLExpected = {8, 1, 1};
    minRExpected = {1, 1, 3};
    minLComputed = {INT_MAX, INT_MAX, INT_MAX};
    minRComputed = {INT_MAX, INT_MAX, INT_MAX};
    calcMinLR(mat, row, minLComputed, minRComputed);
    assert(minLExpected == minLComputed);
    assert(minRExpected == minRComputed);

    mat = {
        {8, 1, 3},
        {7, 4, 2},
        {9, 1, 1}};
    row = 1;
    minLExpected = {7, 4, 2};
    minRExpected = {2, 2, 2};
    minLComputed = {INT_MAX, INT_MAX, INT_MAX};
    minRComputed = {INT_MAX, INT_MAX, INT_MAX};
    calcMinLR(mat, row, minLComputed, minRComputed);
    assert(minLExpected == minLComputed);
    assert(minRExpected == minRComputed);

    mat = {
        {8, 1, 3},
        {7, 4, 2},
        {9, 1, 1}};
    row = 2;
    minLExpected = {9, 1, 1};
    minRExpected = {1, 1, 1};
    minLComputed = {INT_MAX, INT_MAX, INT_MAX};
    minRComputed = {INT_MAX, INT_MAX, INT_MAX};
    calcMinLR(mat, row, minLComputed, minRComputed);
    assert(minLExpected == minLComputed);
    assert(minRExpected == minRComputed);
}

int calcMinFallingPathSum(vector<vector<int>>& A, vector<vector<int>>& memoMat, bool debug) {
    int len = A.size();

    vector<int> minL(len);
    vector<int> minR(len);
    for (int i = 1; i < len; i++) {
        calcMinLR(memoMat, i - 1, minL, minR);

        for (int j = 0; j < len; j++) {
            int minPrevCost = INT_MAX;
            if (j == 0) {
                minPrevCost = minR[1];
            } else if (j == len - 1) {
                minPrevCost = minL[len - 2];
            } else {
                minPrevCost = min(minL[j - 1], minR[j + 1]);
            }

            memoMat[i][j] = minPrevCost + A[i][j];
        }
    }

    int minCost = INT_MAX;
    for (int j = 0; j < len; j++) {
        minCost = min(minCost, memoMat[len - 1][j]);
    }

    return minCost;
}

// LC-submission speed: 63 %tile, memory: 9 %tile
int minFallingPathSum(vector<vector<int>>& A) {
    int len = A.size();
    vector<vector<int>> memoMat = createMemoMat(A);
    return calcMinFallingPathSum(A, memoMat, false);
}

int main() {
    testCalcMinLR();

    return 0;
}
