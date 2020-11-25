// LeetCode-221: https://leetcode.com/problems/maximal-square/
// TusharRoy: https://www.youtube.com/watch?v=_Lf1looyJMU

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    return 0;
}

int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
        return 0;
    } else {
        // happy path
        vector<vector<int>> memoMat = createMemoMat(matrix);
        return fillMemoMat(matrix, memoMat);
    }
}

vector<vector<int>> createMemoMat(vector<vector<char>>& mat) {
    int rows = mat.size();
    int cols = mat[0].size();
    vector<vector<int>> memoMat(rows + 1);
    for (int i = 0; i <= rows; i++) {
        vector<int> rowVec(cols + 1, 0);
        memoMat[i] = rowVec;
    }
    return memoMat;
}

int fillMemoMat(vector<vector<char>>& mat, vector<vector<int>>& memoMat) {
    int rows = mat.size();
    int cols = mat[0].size();

    int maxSqrSide = 0;
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= cols; j++) {
            int idxRow = i;
            int idxCol = j;

            if (mat[idxRow - 1][idxCol - 1] == '0') {
                memoMat[idxRow][idxCol] = 0;
            } else {
                memoMat[i][j] = min(
                                    memoMat[idxRow - 1][idxCol - 1],
                                    min(
                                        memoMat[idxRow - 1][idxCol],
                                        memoMat[idxRow][idxCol - 1])) +
                                1;
                maxSqrSide = max(maxSqrSide, memoMat[i][j]);
            }
        }
    }

    return (maxSqrSide * maxSqrSide);
}
