/**
 * @file leetcode-980-unique-paths-iii.cpp
 * @author y2k-shubham (Shubham Gupta)
 * @brief LeetCode-980: https://leetcode.com/problems/unique-paths-iii/
 *        backtracking based solution: https://www.youtube.com/watch?v=lh_EBh8FbA4
 * @date 2020-09-26
 */

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

pair<pair<int, int>, int> findStartAndZeroesCount(vector<vector<int>>& grid) {
    int numZeroes = 0;
    pair<int, int> startPoint;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[0].size(); j++) {
            if (grid[i][j] == 0) {
                numZeroes++;
            } else if (grid[i][j] == 1) {
                startPoint = {i, j};
            }
        }
    }

    return {startPoint, numZeroes};
}

int uniquePathsBackTrack(vector<vector<int>>& grid, int totZeroes, int crrZeroes, int crrRow, int crrCol) {
    int numRows = grid.size();
    int numCols = grid[0].size();

    // printf("at [%d][%d], crrZeroes = %d\n", crrRow, crrCol, crrZeroes);

    if (crrRow < 0 || crrRow >= numRows || crrCol < 0 || crrCol >= numCols) {
        // walked off the grid
        return 0;
    } else {
        int crrCellVal = grid[crrRow][crrCol];

        if (crrCellVal < 0) {
            // reached either (1) a cell with obstacle (2) an already visited cell
            return 0;
        } else if (crrCellVal == 1 && crrZeroes > 0) {
            // reached (back) at the starting point
            return 0;
        } else if (crrCellVal == 2) {
            // reached the ending point
            if (crrZeroes < totZeroes) {
                // without having visited all intermediate cells
                return 0;
            } else {
                // after having visited all intermediate cells: this is a required / solution path
                return 1;
            }
        } else {
            // either (1) making first step out of starting point
            // or (2) reached some 0 : unvisited but 'visit-able'

            // mark up the no of consumed zeroes
            int newZeroes = crrZeroes + 1;
            if (grid[crrRow][crrCol] == 1) {
                // if it is starting point, then do NOT increment no of visited zeroes
                newZeroes = 0;
            }

            // (1) mark it visited and
            grid[crrRow][crrCol] = -2;

            // (2) and then try recursing in all directions
            int totalPaths = 0;
            // up
            totalPaths += uniquePathsBackTrack(grid, totZeroes, newZeroes, crrRow - 1, crrCol);
            // right
            totalPaths += uniquePathsBackTrack(grid, totZeroes, newZeroes, crrRow, crrCol + 1);
            // down
            totalPaths += uniquePathsBackTrack(grid, totZeroes, newZeroes, crrRow + 1, crrCol);
            // left
            totalPaths += uniquePathsBackTrack(grid, totZeroes, newZeroes, crrRow, crrCol - 1);

            // (also afterwards, mark is unvisted as required by backtracking)
            grid[crrRow][crrCol] = 0;

            return totalPaths;
        }
    }
}

int uniquePathsIII(vector<vector<int>>& grid) {
    pair<pair<int, int>, int> startAndZerosCount = findStartAndZeroesCount(grid);

    int startRow = startAndZerosCount.first.first;
    int startCol = startAndZerosCount.first.second;
    return uniquePathsBackTrack(grid, startAndZerosCount.second, 0, startRow, startCol);
}
