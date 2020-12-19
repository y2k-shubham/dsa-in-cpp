// LeetCode-1463: https://leetcode.com/problems/cherry-pickup-ii/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
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

// not great; LC-submission speed: 15 %tile, memory 10 %tile
int maxGainRecMemo(vector<vector<int>>& grid, vector<vector<vector<int>>>& memoMat, int r, int c1, int c2, bool debug) {
    int rows = grid.size();
    int cols = grid[0].size();

    if (min(r, min(c1, c1)) < 0 || r >= rows || max(c1, c2) >= cols) {
        return 0;
    } else {
        if (debug) {
            // printf("\n===========================\n");
            printf("\nrows=%d, cols=%d\n", rows, cols);
            printf("r=%d, c1=%d, c2=%d\n", r, c1, c2);
        }

        if (memoMat[r][c1][c2] == INT_MIN) {
            int crrGain = grid[r][c1];
            if (c1 != c2) {
                crrGain += grid[r][c2];
            }

            int futureGain = 0;
            if (r < rows - 1) {
                for (int d1 = -1; d1 <= 1; d1++) {
                    for (int d2 = -1; d2 <= 1; d2++) {
                        int nextC1 = min(cols - 1, max(0, c1 + d1));
                        int nextC2 = min(cols - 1, max(0, c2 + d2));
                        futureGain = max(futureGain, maxGainRecMemo(grid, memoMat, r + 1, nextC1, nextC2, debug));
                    }
                }
            }

            memoMat[r][c1][c2] = crrGain + futureGain;
        }

        return memoMat[r][c1][c2];
    }
}

void testMaxGainRecMemo() {
    vector<vector<int>> grid;
    vector<vector<vector<int>>> memoMat;
    int cols;
    int gainOutExpected;
    int gainOutComputed;

    grid = {{3, 1, 1},
            {2, 5, 1},
            {1, 5, 5},
            {2, 1, 1}};
    memoMat = createMemoMat(grid);
    cols = grid[0].size();
    gainOutExpected = 24;
    gainOutComputed = maxGainRecMemo(grid, memoMat, 0, 0, cols - 1, false);
    assert(gainOutExpected == gainOutComputed);

    grid = {{1, 0, 0, 0, 0, 0, 1},
            {2, 0, 0, 0, 0, 3, 0},
            {2, 0, 9, 0, 0, 0, 0},
            {0, 3, 0, 5, 4, 0, 0},
            {1, 0, 2, 3, 0, 0, 6}};
    memoMat = createMemoMat(grid);
    cols = grid[0].size();
    gainOutExpected = 28;
    gainOutComputed = maxGainRecMemo(grid, memoMat, 0, 0, cols - 1, false);
    assert(gainOutExpected == gainOutComputed);

    grid = {{1, 0, 0, 3},
            {0, 0, 0, 3},
            {0, 0, 3, 3},
            {9, 0, 3, 3}};
    memoMat = createMemoMat(grid);
    cols = grid[0].size();
    gainOutExpected = 22;
    gainOutComputed = maxGainRecMemo(grid, memoMat, 0, 0, cols - 1, false);
    assert(gainOutExpected == gainOutComputed);

    grid = {{1, 1},
            {1, 1}};
    memoMat = createMemoMat(grid);
    cols = grid[0].size();
    gainOutExpected = 4;
    gainOutComputed = maxGainRecMemo(grid, memoMat, 0, 0, cols - 1, false);
    assert(gainOutExpected == gainOutComputed);
}

int cherryPickup(vector<vector<int>>& grid) {
    vector<vector<vector<int>>> memoMat = createMemoMat(grid);

    int cols = grid[0].size();
    return maxGainRecMemo(grid, memoMat, 0, 0, cols - 1, false);
}

int main() {
    testMaxGainRecMemo();

    return 0;
}
