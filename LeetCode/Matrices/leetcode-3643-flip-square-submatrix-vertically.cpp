// LeetCode-3643: https://leetcode.com/problems/flip-square-submatrix-vertically
// Not that easy, has some edge caess.

#include <vector>

using namespace std;

class Solution {
private:
    void reverseColumnPart(vector<vector<int>>& mat, int col, int beginRow, int numEles) {
        int numRows = mat.size();

        int i1 = beginRow;
        int i2 = min(numRows - 1, beginRow + numEles - 1);

        while (i1 < i2) {
            swap(mat[i1][col], mat[i2][col]);
            i1++;
            i2--;
        }
    }

public:
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        int numRows = grid.size();
        if (numRows <= 1) {
            return grid;
        }
        if (k <= 1) {
            return grid;
        }

        int numCols = grid[0].size();
        int j1 = y;
        int j2 = min(numCols - 1, y + k - 1);

        for (int j = j1; j <= j2; j++) {
            reverseColumnPart(grid, j, x, k);
        }

        return grid;
    }
};
