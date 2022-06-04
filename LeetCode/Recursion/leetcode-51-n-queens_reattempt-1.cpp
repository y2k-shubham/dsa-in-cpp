// LeetCode-51: https://leetcode.com/problems/n-queens/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    vector<string> buildSolnStrVec(int n, vector<int>& crrSoln) {
        vector<string> solnStrVec(n);

        for (int i = 0; i < n; i++) {
            string crrRowstr(n, '.');
            crrRowstr[crrSoln[i]] = 'Q';

            solnStrVec[i] = crrRowstr;
        }

        return solnStrVec;
    }

    bool isAttacking(int n, vector<int>& crrSoln, int crrRow, int crrCol) {
        for (int i = 0; i < crrRow; i++) {
            int j = crrSoln[i];

            if ((j == crrCol) || (abs(i - crrRow) == abs(j - crrCol))) {
                return true;
            }
        }

        return false;
    }

    void nQueensRec(
            int n,
            vector<vector<string> >& solns,
            int crrRow,
            vector<int> crrSoln
    ) {
        if (crrRow >= n) {
            solns.push_back(buildSolnStrVec(n, crrSoln));
            return;
        }

        for (int crrCol = 0; crrCol < n; crrCol++) {
            if (!isAttacking(n, crrSoln, crrRow, crrCol)) {
                crrSoln[crrRow] = crrCol;
                nQueensRec(n, solns, crrRow + 1, crrSoln);
                crrSoln[crrRow] = -1;
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string> > solns;
        vector<int> crrSoln(n, -1);

        nQueensRec(n, solns, 0, crrSoln);

        return solns;
    }
};
