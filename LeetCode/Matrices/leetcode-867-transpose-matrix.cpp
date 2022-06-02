// LeetCode-867: https://leetcode.com/problems/transpose-matrix/
// begging you to skip

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        int numRows = matrix.size();
        int numCols = matrix[0].size();

        vector<vector<int> > transMatrix(numCols);
        for (int i = 0; i < numCols; i++) {
            vector<int> transMatrixRow(numRows);
            transMatrix[i] = transMatrixRow;
        }

        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                transMatrix[j][i] = matrix[i][j];
            }
        }

        return transMatrix;
    }
};
