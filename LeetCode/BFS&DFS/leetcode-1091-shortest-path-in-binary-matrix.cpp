// LeetCode-1091: https://leetcode.com/problems/shortest-path-in-binary-matrix/
// LC Feb 2021 challenge: https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/585/week-2-february-8th-february-14th/3638/

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Solution {
   public:
    vector<vector<int>> createDistMat(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        vector<vector<int>> distMat(rows);
        for (int i = 0; i < rows; i++) {
            vector<int> distRow(cols, INT_MAX);
            distMat[i] = distRow;
        }
        distMat[0][0] = 0;

        return distMat;
    }

    void bfs(vector<vector<int>>& grid, vector<vector<int>>& distMat) {
        int rows = grid.size();
        int cols = grid[0].size();

        queue<pair<int, int>> que;
        que.push({0, 0});
        while (!que.empty()) {
            pair<int, int> cell = que.front();
            que.pop();

            int crrI = cell.first;
            int crrJ = cell.second;
            int crrDist = distMat[cell.first][cell.second];

            int iLo = max(0, crrI - 1);
            int iHi = min(rows - 1, crrI + 1);
            int jLo = max(0, crrJ - 1);
            int jHi = min(cols - 1, crrJ + 1);

            for (int i = iLo; i <= iHi; i++) {
                for (int j = jLo; j <= jHi; j++) {
                    if (i == crrI && j == crrJ) {
                        // nothing
                    } else {
                        if ((grid[i][j] == 0) && (distMat[i][j] > (crrDist + 1))) {
                            distMat[i][j] = crrDist + 1;
                            que.push({i, j});
                        }
                    }
                }
            }
        }
    }

    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();

        if (grid[0][0] != 0 || grid[rows - 1][cols - 1] != 0) {
            // invalid input matrix
            return -1;
        }
        if (rows == 1 && cols == 1) {
            // unit-matrix (1x1)
            return 1;
        }

        vector<vector<int>> distMat = createDistMat(grid);
        bfs(grid, distMat);

        if (distMat[rows - 1][cols - 1] == INT_MAX) {
            // unreachable
            return -1;
        } else {
            // no of nodes in path = dist of destination node + 1
            return distMat[rows - 1][cols - 1] + 1;
        }
    }
};
