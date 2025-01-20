// LeetCode-2661: https://leetcode.com/problems/first-completely-painted-row-or-column/

#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
private:
    pair <int, int> convertToPosn(int numCols, int num) {
        num--;

        int row = num / numCols;
        int col = num % numCols;

        return {row, col};
    }

    unordered_map <int, pair <int, int>> buildNumPosnMap(vector <vector <int>>& mat) {
        unordered_map <int, pair <int, int>> numPosns;

        for (int i = 0; i < mat.size(); i++) {
            for (int j = 0; j < mat[0].size(); j++) {
                numPosns[mat[i][j]] = {i, j};
            }
        }

        return numPosns;
    }

public:
    int firstCompleteIndex(vector <int>& arr, vector <vector <int>>& mat) {
        int numRows = mat.size();
        int numCols = mat[0].size();

        vector <int> numColoredCellsInRow(numRows, 0);
        vector <int> numColoredCellsInCol(numCols, 0);

        unordered_map <int, pair <int, int>> numPosns = buildNumPosnMap(mat);

        for (int i = 0; i < arr.size(); i++) {
            int val = arr[i];

            pair <int, int> rowCol = numPosns[val];
            int row = rowCol.first;
            int col = rowCol.second;

            numColoredCellsInRow[row]++;
            numColoredCellsInCol[col]++;

            if (numColoredCellsInRow[row] == numCols) {
                return i;
            }
            if (numColoredCellsInCol[col] == numRows) {
                return i;
            }
        }

        return -1;
    }
};
