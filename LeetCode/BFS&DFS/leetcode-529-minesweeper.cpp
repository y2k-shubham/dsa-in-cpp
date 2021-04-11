// LeetCode-529: https://leetcode.com/problems/minesweeper/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<bool>> buildVisitedMat(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();

        vector<vector<bool>> visitedMat(rows);

        for (int i = 0; i < rows; i++) {
            vector<bool> visitedMatRow(cols, false);
            for (int j = 0; j < cols; j++) {
                switch (board[i][j]) {
                    case 'E':
                    case 'M':
                        visitedMatRow[j] = false;
                        break;

                    default:
                        visitedMatRow[j] = true;
                        break;
                }
            }

            visitedMat[i] = visitedMatRow;
        }

        return visitedMat;
    }

    vector<vector<int>> buildAdjMinesCountMat(vector<vector<char>>& board) {
        int rows = board.size();
        int cols = board[0].size();

        vector<vector<int>> adjMinesCountMat(rows);

        for (int i = 0; i < rows; i++) {
            vector<int> adjMinesCountMatRow(cols, -1);
            adjMinesCountMat[i] = adjMinesCountMatRow;
        }

        return adjMinesCountMat;
    }

    int getAdjMinesCount(vector<vector<char>>& board, vector<vector<int>>& adjMinesCountMat, int r, int c) {
        int rows = board.size();
        int cols = board[0].size();

        if (adjMinesCountMat[r][c] >= 0) {
            return adjMinesCountMat[r][c];
        }

        int count = 0;
        for (int rDelta = -1; rDelta <= 1; rDelta++) {
            for (int cDelta = -1; cDelta <= 1; cDelta++) {
                int rT = r + rDelta;
                int cT = c + cDelta;
                if (rT == r && cT == c) {
                    continue;
                }

                if (0 <= rT && rT < rows && 0 <= cT && cT < cols) {
                    if (board[rT][cT] == 'M') {
                        count++;
                    }
                }
            }
        }

        adjMinesCountMat[r][c] = count;
        return count;
    }

    void dfs(vector<vector<char>>& board, vector<vector<int>>& adjMinesCountMat, vector<vector<bool>>& visitedMat, int r, int c) {
        int rows = board.size();
        int cols = board[0].size();
        if (r < 0 || r >= rows || c < 0 || c >= cols) {
            return;
        }
        if (visitedMat[r][c]) {
            return;
        }
        if (board[r][c] == 'M') {
            board[r][c] = 'X';
            return;
        }

        visitedMat[r][c] = true;

        int adjMinesCount = getAdjMinesCount(board, adjMinesCountMat, r, c);
        if (adjMinesCount >= 1) {
            board[r][c] = '0' + adjMinesCount;
            return;
        }

        board[r][c] = 'B';
        for (int rDelta = -1; rDelta <= 1; rDelta++) {
            for (int cDelta = -1; cDelta <= 1; cDelta++) {
                int rT = r + rDelta;
                int cT = c + cDelta;
                if (rT == r && cT == c) {
                    continue;
                }

                if (0 <= rT && rT < rows && 0 <= cT && cT < cols) {
                    if (!visitedMat[rT][cT] && board[rT][cT] != 'M') {
                        dfs(board, adjMinesCountMat, visitedMat, rT, cT);
                    }
                }
            }
        }
    }

   public:
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int rows = board.size();
        int cols = board[0].size();

        vector<vector<bool>> visitedMat = buildVisitedMat(board);
        vector<vector<int>> adjMinesCountMat = buildAdjMinesCountMat(board);

        int r = click[0];
        int c = click[1];

        if (board[r][c] == 'M') {
            board[r][c] = 'X';
        } else {
            int adjMinesCount = getAdjMinesCount(board, adjMinesCountMat, r, c);

            if (adjMinesCount == 0) {
                dfs(board, adjMinesCountMat, visitedMat, r, c);
            } else {
                board[r][c] = '0' + adjMinesCount;
            }
        }

        return board;
    }
};
