// LeetCode-1582: https://leetcode.com/problems/special-positions-in-a-binary-matrix
// decent question, worth a look

#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int> > createMat(int numRows, int numCols, int defaultValue) {
        vector<vector<int> > mat(numRows);
        for (int i = 0; i < numRows; i++) {
            vector<int> row(numCols, defaultValue);
            mat[i] = row;
        }

        return mat;
    }

    int count1sInRow(vector<vector<int> >& mat, int row) {
        int numCols = mat[0].size();
        int count = 0;
        for (int j = 0; j < numCols; j++) {
            if (mat[row][j] == 1) {
                count++;
            }
        }

        return count;
    }

    int count1sInCol(vector<vector<int> >& mat, int col) {
        int numRows = mat.size();
        int count = 0;
        for (int i = 0; i < numRows; i++) {
            if (mat[i][col] == 1) {
                count++;
            }
        }

        return count;
    }

    vector<int> create1sFreqInRowsVec(vector<vector<int> >& mat) {
        int numRows = mat.size();
        int numCols = mat[0].size();

        vector<int> freqVec(numRows, 0);
        for (int i = 0; i < numRows; i++) {
            int num1s = 0;
            for (int j = 0; j < numCols; j++) {
                if (mat[i][j] == 1) {
                    num1s++;
                }
            }

            freqVec[i] = num1s;
        }

        return freqVec;
    }

    vector<int> create1sFreqInColsVec(vector<vector<int> >& mat) {
        int numRows = mat.size();
        int numCols = mat[0].size();

        vector<int> freqVec(numCols, 0);
        for (int j = 0; j < numCols; j++) {
            int num1s = 0;
            for (int i = 0; i < numRows; i++) {
                if (mat[i][j] == 1) {
                    num1s++;
                }
            }

            freqVec[j] = num1s;
        }

        return freqVec;
    }

public:
    int numSpecial(vector<vector<int>>& mat) {
        int numRows = mat.size();
        int numCols = mat[0].size();
        if (max(numRows, numCols) == 1) {
            return (mat[0][0] == 0) ? 0 : 1;
        } else if (numRows == 1) {
            return (count1sInRow(mat, 0) == 1) ? 1 : 0;
        } else if (numCols == 1) {
            return (count1sInCol(mat, 0) == 1) ? 1 : 0;
        }

        vector<int> freq1sInRowsVec = create1sFreqInRowsVec(mat);
        vector<int> freq1sInColsVec = create1sFreqInColsVec(mat);
        int numSpecial = 0;
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (mat[i][j] == 1 && freq1sInRowsVec[i] == 1 && freq1sInColsVec[j] == 1) {
                    numSpecial++;
                }
            }
        }

        return numSpecial;
    }
};
