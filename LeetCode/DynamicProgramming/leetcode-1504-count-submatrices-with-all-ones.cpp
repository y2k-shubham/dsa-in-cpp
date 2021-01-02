// LeetCode-1504: https://leetcode.com/problems/count-submatrices-with-all-ones/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> createVSumMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();

        vector<vector<int>> vSumMatrix(rows);
        for (int i = 0; i < rows; i++) {
            vector<int> mRow(cols, 0);

            if (i == 0) {
                for (int j = 0; j < cols; j++) {
                    mRow[j] = mat[i][j];
                }
            } else {
                for (int j = 0; j < cols; j++) {
                    if (mat[i][j] == 0) {
                        mRow[j] = 0;
                    } else {
                        mRow[j] = vSumMatrix[i - 1][j] + 1;
                    }
                }
            }

            vSumMatrix[i] = mRow;
        }

        return vSumMatrix;
    }

    int count1sSubMatrices(vector<vector<int>>& vSumMatrix) {
        int rows = vSumMatrix.size();
        int cols = vSumMatrix[0].size();

        int numSubMatrices = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (vSumMatrix[i][j] > 0) {
                    int minHeight = INT_MAX;
                    for (int k = j; (k >= 0) && (vSumMatrix[i][k] > 0); k--) {
                        minHeight = min(minHeight, vSumMatrix[i][k]);
                        numSubMatrices = numSubMatrices + minHeight;
                    }
                }
            }
        }

        return numSubMatrices;
    }

    // LC-submission speed: 44 %tile, memory: 18 %tile
    int numSubmat(vector<vector<int>>& mat) {
        vector<vector<int>> vSumMatrix = createVSumMatrix(mat);
        return count1sSubMatrices(vSumMatrix);
    }
};

int main() {
    return 0;
}
