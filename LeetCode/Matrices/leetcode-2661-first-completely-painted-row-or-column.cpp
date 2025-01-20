// LeetCode-2661: https://leetcode.com/problems/first-completely-painted-row-or-column/

#include <vector>

using namespace std;

class Solution {
private:
    pair <int, int> convertToRowCol(int numCols, int num) {
        num--;

        int row = num / numCols;
        int col = num % numCols;

        return {row, col};
    }

public:
    int firstCompleteIndex(vector <int>& arr, vector <vector <int>>& mat) {
        int numRows = mat.size();
        int numCols = mat[0].size();

        vector <int> numColoredCellsInRow(numRows, 0);
        vector <int> numColoredCellsInCol(numCols, 0);

        for (int val : arr) {
            pair <int, int> rowCol = convertToRowCol(numCols, val);
            int row = rowCol.first;
            int col = rowCol.second;

            numColoredCellsInRow[row]++;
            numColoredCellsInCol[col]++;

            if (numColoredCellsInRow[row] == numCols) {
                return val;
            }
            if (numColoredCellsInCol[col] == numRows) {
                return val;
            }
        }

        return -1;
    }
};
