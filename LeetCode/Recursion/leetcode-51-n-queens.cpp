// LeetCode-51: https://leetcode.com/problems/n-queens/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/601/week-4-may-22nd-may-28th/3752/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool isSafe(vector<int>& solnVec, int row, int col) {
        for (int i = 0; i < row; i++) {
            if ((solnVec[i] == col) || (abs(solnVec[i] - col) == abs(i - row))) {
                return false;
            }
        }

        return true;
    }

    vector<string> buildSolnMat(vector<int>& soln) {
        int len = soln.size();

        vector<string> solnMat(len);
        for (int i = 0; i < len; i++) {
            // ref: https://stackoverflow.com/a/41030227/3679900
            string solnMatRow(len, '.');
            solnMatRow[soln[i]] = 'Q';

            solnMat[i] = solnMatRow;
        }

        return solnMat;
    }

    void buildSolnRec(
        int n,
        vector<vector<string>>& solnMats,
        vector<int>& solnVec,
        int row) {
        if (row < n) {
            for (int j = 0; j < n; j++) {
                if (isSafe(solnVec, row, j)) {
                    solnVec[row] = j;
                    buildSolnRec(n, solnMats, solnVec, row + 1);
                }
            }
        } else {
            solnMats.push_back(buildSolnMat(solnVec));
        }
    }

    vector<vector<string>> findSolns(int n) {
        vector<vector<string>> solnMats;

        vector<int> solnVec(n);
        for (int j = 0; j < n; j++) {
            solnVec[0] = j;
            buildSolnRec(n, solnMats, solnVec, 1);
        }

        return solnMats;
    }

   public:
    vector<vector<string>> solveNQueens(int n) {
        if (n == 1) {
            return {{"Q"}};
        } else if (n < 4) {
            return {};
        } else {
            return findSolns(n);
        }
    }
};
