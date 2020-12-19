// LeetCode-741: https://leetcode.com/problems/cherry-pickup/
// GFG: https://www.geeksforgeeks.org/maximum-points-top-left-matrix-bottom-right-return-back/
// hard problem: 3-dimensional memoization table on matrix search (like DFS)
// TechLife With Shivank: https://www.youtube.com/watch?v=q3-6jaNvj6c

#include <climits>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<vector<int>>> createMemoMat(vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    vector<vector<vector<int>>> memoMat(rows);
    for (int i = 0; i < rows; i++) {
        vector<vector<int>> memoSubMat(cols);
        for (int j = 0; j < cols; j++) {
            vector<int> memoSubSubMat(cols, INT_MIN);
            memoSubMat[j] = memoSubSubMat;
        }
        memoMat[i] = memoSubMat;
    }

    return memoMat;
}

// not great; LC-submission speed: 14 %tile, memory 10 %tile
int countCherries(vector<vector<int>>& grid, vector<vector<vector<int>>>& memoMat, int r1, int c1, int c2) {
    int rows = grid.size();
    int cols = grid[0].size();

    int r2 = r1 + c1 - c2;
    if (min(r1, r2) < 0 || min(c1, c2) < 0 || max(r1, r2) >= rows || max(c1, c2) >= cols) {
        return INT_MIN;
    } else if (min(grid[r1][c1], grid[r2][c2]) == -1) {
        return INT_MIN;
    } else if (memoMat[r1][c1][c2] != INT_MIN) {
        return memoMat[r1][c1][c2];
    } else if (r1 == (rows - 1) && c1 == (cols - 1)) {
        return grid[r1][c1];
    } else {
        int gain = grid[r1][c1];
        if (c1 != c2) {
            gain += grid[r2][c2];
        }

        gain += max(
            max(
                countCherries(grid, memoMat, r1 + 1, c1, c2),
                countCherries(grid, memoMat, r1, c1 + 1, c2)),
            max(
                countCherries(grid, memoMat, r1 + 1, c1, c2 + 1),
                countCherries(grid, memoMat, r1, c1 + 1, c2 + 1)));
        memoMat[r1][c1][c2] = gain;

        return gain;
    }
}

int cherryPickup(vector<vector<int>>& grid) {
    if (grid.size() == 1) {
        return max(0, grid[0][0]);
    } else {
        vector<vector<vector<int>>> memoMat = createMemoMat(grid);
        return max(0, countCherries(grid, memoMat, 0, 0, 0));
    }
}
