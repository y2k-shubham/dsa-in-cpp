// LeetCode-3070: https://leetcode.com/problems/count-submatrices-with-top-left-element-and-sum-less-than-k/

#include <vector>

using namespace std;

class Solution {
private:
    bool debug = false;

    vector<vector<int>> createSumGrid(int rows, int cols) {
        vector<vector<int>> sumGrid(rows);

        for (int r = 0; r < rows; r++) {
            sumGrid[r] = vector<int>(cols, 0);
        }

        return sumGrid;
    }

    int copyFirstRowAndCol(vector<vector<int>>& grid, vector<vector<int>>& sumGrid, int k) {
        int rows = grid.size();
        int cols = grid[0].size();

        int numSubMatrices = 1;
        sumGrid[0][0] = grid[0][0];

        // copy first row
        for (int c = 1; c < cols; c++) {
            int sum = sumGrid[0][c - 1] + grid[0][c];
            sumGrid[0][c] = sum;

            if (sum <= k) {
                numSubMatrices++;
            }
        }

        // copy first col
        for (int r = 1; r < rows; r++) {
            int sum = sumGrid[r - 1][0] + grid[r][0];
            sumGrid[r][0] = sum;

            if (sum <= k) {
                numSubMatrices++;
            }
        }

        return numSubMatrices;
    }

public:
    int countSubmatrices(vector<vector<int>>& grid, int k) {
        if (grid[0][0] > k) {
            return 0;
        }

        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<int>> sumGrid = createSumGrid(rows, cols);
        int numSubMatrices = copyFirstRowAndCol(grid, sumGrid, k);

        int maxCol = cols - 1;
        for (int i = 1; i < rows; i++) {
            for (int j = 1; j <= maxCol; j++) {
                int sum = sumGrid[i][j - 1] + sumGrid[i - 1][j] - sumGrid[i - 1][j - 1] + grid[i][j];
                sumGrid[i][j] = sum;

                if (sum <= k) {
                    numSubMatrices++;
                } else {
                    maxCol = j - 1;
                    break;
                }
            }
        }

        return numSubMatrices;
    }
};
