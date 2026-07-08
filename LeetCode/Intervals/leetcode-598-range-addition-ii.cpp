// LeetCode-598: https://leetcode.com/problems/range-addition-ii/

#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int>> createMat(int rows, int cols) {
        vector<vector<int>> mat(rows, vector<int>(cols, 0));
        return mat;
    }

    void recordRangeUpdates(vector<vector<int>>& mat, int endRow, int endCol) {
        mat[endRow][endCol] += 1;
    }

    int getRightVal(vector<vector<int>>& mat, int i, int j) {
        int cols = mat[0].size();
        if (j == (cols - 1)) {
            return 0;
        } else {
            return mat[i][j + 1];
        }
    }

    int getBottomVal(vector<vector<int>>& mat, int i, int j) {
        int rows = mat.size();
        if (i == rows - 1) {
            return 0;
        } else {
            return mat[i + 1][j];
        }
    }

    void applyUpdateInCell(vector<vector<int>>& mat, int i, int j) {
        int rightVal = getRightVal(mat, i, j);
        int bottomVal = getBottomVal(mat, i, j);

        mat[i][j] += max(rightVal, bottomVal);
    }

    void applyRangeUpdatesInWideMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();

        // apply updates in bottom right triangle
        for (int rShift = 0; rShift < rows; rShift++) {
            for (int rBegin = (rows - rShift); rBegin >= 0; rBegin--) {
                int i = rBegin;
                int j = cols - 1;

                while (i < rows) {
                    applyUpdateInCell(mat, i, j);

                    i++;
                    j--;
                }
            }
        }

        // apply updates in middle band
        for (int cShift = 1; cShift <= (cols - rows - 1); cShift++) {
            for (int cBegin = (cols - cShift - 1); cBegin > rows; cBegin--) {
                int i = 0;
                int j = cBegin;

                while (i < rows) {
                    applyUpdateInCell(mat, i, j);

                    i++;
                    j--;
                }
            }
        }

        // apply updates in upper left triangle
        for (int cShift = 0; cShift < rows; cShift++) {
            for (int cBegin = (cols - cShift); cBegin >= 0; cBegin--) {
                int i = 0;
                int j = cBegin;

                while (j >= 0) {
                    applyUpdateInCell(mat, i, j);

                    i++;
                    j--;
                }
            }
        }
    }

    void applyRangeUpdatesInTallMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();

        // apply updates in bottom right triangle

    }

public:
    int maxCount(int m, int n, vector<vector<int>>& ops) {

    }
};
