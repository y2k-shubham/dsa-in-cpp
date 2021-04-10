// LeetCode-329: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/
// LC April 2021 challenge: https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/594/week-2-april-8th-april-14th/3703/

// slightly simplified problems below:
// GFG: https://www.geeksforgeeks.org/longest-increasing-path-matrix/
// InterviewBit: https://www.interviewbit.com/problems/increasing-path-in-matrix/

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int>> matrix;
    vector<vector<int>> memoMat;
    vector<vector<bool>> visitedFlagMat;
    vector<vector<bool>> backtrackFlagMat;
    int rows;
    int cols;

    void init(vector<vector<int>> matrix) {
        this->matrix = matrix;
        this->rows = matrix.size();
        this->cols = matrix[0].size();

        initMemoMat(1);
        this->visitedFlagMat = initFlagMat(false);
        this->backtrackFlagMat = initFlagMat(false);
    }

    void initMemoMat(int initVal) {
        vector<vector<int>> memoMat(this->rows);

        for (int i = 0; i < this->rows; i++) {
            vector<int> memoMatRow(this->cols, initVal);
            memoMat[i] = memoMatRow;
        }

        this->memoMat = memoMat;
    }

    vector<vector<bool>> initFlagMat(bool initVal) {
        vector<vector<bool>> flagMat(this->rows);

        for (int i = 0; i < this->rows; i++) {
            vector<bool> flagMatRow(this->cols, initVal);
            flagMat[i] = flagMatRow;
        }

        return flagMat;
    }

    int dfsRec(int r, int c) {
        if (r >= this->rows || c >= this->cols) {
            return 0;
        }

        if (this->visitedFlagMat[r][c]) {
            return this->memoMat[r][c];
        }

        this->backtrackFlagMat[r][c] = true;
        int longestOutgoingPathLen = 1;

        if (r >= 1 && !this->backtrackFlagMat[r - 1][c] && this->matrix[r - 1][c] > this->matrix[r][c]) {
            longestOutgoingPathLen = max(longestOutgoingPathLen, 1 + dfsRec(r - 1, c));
        }
        if (c <= (cols - 2) && !this->backtrackFlagMat[r][c + 1] && this->matrix[r][c + 1] > this->matrix[r][c]) {
            longestOutgoingPathLen = max(longestOutgoingPathLen, 1 + dfsRec(r, c + 1));
        }
        if (r <= (rows - 2) && !this->backtrackFlagMat[r + 1][c] && this->matrix[r + 1][c] > this->matrix[r][c]) {
            longestOutgoingPathLen = max(longestOutgoingPathLen, 1 + dfsRec(r + 1, c));
        }
        if (c >= 1 && !this->backtrackFlagMat[r][c - 1] && this->matrix[r][c - 1] > this->matrix[r][c]) {
            longestOutgoingPathLen = max(longestOutgoingPathLen, 1 + dfsRec(r, c - 1));
        }

        this->memoMat[r][c] = longestOutgoingPathLen;
        this->visitedFlagMat[r][c] = true;
        this->backtrackFlagMat[r][c] = false;

        return longestOutgoingPathLen;
    }

    int longestIncPath() {
        int longestIncPath = 0;

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                longestIncPath = max(longestIncPath, this->memoMat[i][j]);
            }
        }

        return longestIncPath;
    }

   public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        init(matrix);
        if (this->rows == 1 && this->cols == 1) {
            return 1;
        }

        for (int i = 0; i < this->rows; i++) {
            for (int j = 0; j < this->cols; j++) {
                if (!this->visitedFlagMat[i][j]) {
                    dfsRec(i, j);
                }
            }
        }

        return longestIncPath();
    }
};
