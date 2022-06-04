// LeetCode-51: https://leetcode.com/problems/n-queens/

#include <vector>

using namespace std;

class Solution {
private:
    // without 'inline': runtime is 7 ms (58 %tile)
    // with 'inline': runtime is 0 ms (100 %tile)
    inline bool isAttacking(int n, vector<int>& crrSoln, int crrRow, int crrCol) {
        for (int i = 0; i < crrRow; i++) {
            int j = crrSoln[i];

            if ((j == crrCol) || (abs(i - crrRow) == abs(j - crrCol))) {
                return true;
            }
        }

        return false;
    }

    int nQueensRec(int n, vector<int>& crrSoln, int crrRow) {
        if (crrRow >= n) {
            return 1;
        }

        int numSolns = 0;
        for (int crrCol = 0; crrCol < n; crrCol++) {
            crrSoln[crrRow] = crrCol;
            if (!isAttacking(n, crrSoln, crrRow, crrCol)) {
                numSolns += nQueensRec(n, crrSoln, crrRow + 1);
            }
            crrSoln[crrRow] = -1;
        }

        return numSolns;
    }

public:
    int totalNQueens(int n) {
        vector<int> crrSoln(n, -1);

        return nQueensRec(n, crrSoln, 0);
    }
};
