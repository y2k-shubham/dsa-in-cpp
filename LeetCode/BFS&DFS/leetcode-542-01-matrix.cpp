// LeetCode-542: https://leetcode.com/problems/01-matrix/
// LC July 2021 challenge: https://leetcode.com/explore/challenge/card/july-leetcoding-challenge-2021/612/week-5-july-29th-july-31st/3831/
// harder than it seems

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> buildMinDistMat(int rows, int cols) {
        vector<vector<int>> minDistMat(rows);

        for (int i = 0; i < rows; i++) {
            vector<int> minDistMatRow(cols, INT_MAX);
            minDistMat[i] = minDistMatRow;
        }

        return minDistMat;
    }

    vector<vector<bool>> buildVisitedMat(int rows, int cols) {
        vector<vector<bool>> visitedMat(rows);

        for (int i = 0; i < rows; i++) {
            vector<bool> visitedMatRow(cols, false);
            visitedMat[i] = visitedMatRow;
        }

        return visitedMat;
    }

    list<pair<int, int>> getAdjCellIndices(int rows, int cols, int r, int c) {
        list<pair<int, int>> mList;

        // left
        if (c > 0) {
            mList.push_back({r, c - 1});
        }

        // top
        if (r > 0) {
            mList.push_back({r - 1, c});
        }

        // right
        if (c < cols - 1) {
            mList.push_back({r, c + 1});
        }

        // bottom
        if (r < rows - 1) {
            mList.push_back({r + 1, c});
        }

        return mList;
    }

    // barely accepted, LC-submission speed 5 %tile, memory 5 %tile
    void bfs(
        vector<vector<int>>& mat,
        vector<vector<int>>& minDistMat,
        int rBegin,
        int cBegin) {
        int rows = mat.size();
        int cols = mat[0].size();

        queue<pair<int, int>> que;
        minDistMat[rBegin][cBegin] = 0;
        que.push({rBegin, cBegin});

        while (!que.empty()) {
            pair<int, int> cell = que.front();
            que.pop();

            int r = cell.first;
            int c = cell.second;

            list<pair<int, int>> adjCellIndices = getAdjCellIndices(rows, cols, r, c);
            for (list<pair<int, int>>::iterator i = adjCellIndices.begin(); i != adjCellIndices.end(); i++) {
                int iR = i->first;
                int iC = i->second;

                int adjCellNewDist = (mat[iR][iC] == 0) ? 0 : (minDistMat[r][c] + 1);
                if (adjCellNewDist < minDistMat[iR][iC]) {
                    minDistMat[iR][iC] = adjCellNewDist;
                    que.push({iR, iC});
                }
            }
        }
    }

   public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int rows = mat.size();
        int cols = mat[0].size();

        vector<vector<int>> minDistMat = buildMinDistMat(rows, cols);

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if ((mat[r][c] == 0) && (minDistMat[r][c] == INT_MAX)) {
                    bfs(mat, minDistMat, r, c);
                }
            }
        }

        return minDistMat;
    }
};
