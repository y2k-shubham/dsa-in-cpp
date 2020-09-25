// LeetCode-63: https://leetcode.com/problems/unique-paths-ii/
// https://www.interviewbit.com/problems/unique-paths-in-a-grid/
// https://www.geeksforgeeks.org/unique-paths-in-a-grid-with-obstacles/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

vector<int> prepare1stRow(vector<vector<int>>& obstacleGrid) {
    int cols = obstacleGrid[0].size();

    vector<int> ways(cols + 1, 1);
    ways[0] = 0;

    int j;
    for (j = 1; (j <= cols) && (obstacleGrid[0][j - 1] != 1); j++)
        ;

    while (j <= cols) {
        if (obstacleGrid[0][j - 1] == 1) {
            ways[j] = INT_MIN;
        } else {
            ways[j] = 0;
        }
        j++;
    }

    return ways;
}

void fillRow(vector<vector<int>>& obstacleGrid, int row, vector<int>& prevRow, vector<int>& crrRow) {
    int cols = obstacleGrid[0].size();
    crrRow[0] = 0;

    int j;
    for (j = 1; j <= cols; j++) {
        bool selfBlocked = obstacleGrid[row][j - 1] == 1;
        if (selfBlocked) {
            crrRow[j] = INT_MIN;
        } else {
            crrRow[j] = max(crrRow[j - 1], 0) + max(prevRow[j], 0);
        }
    }
}

int findUniquePaths(vector<vector<int>>& obstacleGrid) {
    int m = obstacleGrid.size();
    int n = obstacleGrid[0].size();

    if (m == 0 || n == 0) {
        return 0;
    }

    vector<int> prevRow = prepare1stRow(obstacleGrid);
    vector<int> crrRow(n + 1, 1);

    for (int i = 1; i < m; i++) {
        fillRow(obstacleGrid, i, prevRow, crrRow);
        prevRow = crrRow;
    }

    if (m > 1) {
        return max(crrRow[n], 0);
    } else {
        return max(prevRow[n], 0);
    }
}

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    return findUniquePaths(obstacleGrid);
}
