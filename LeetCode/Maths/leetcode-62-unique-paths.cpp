// LeetCode-62: https://leetcode.com/problems/unique-paths/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int hcf(int dividend, int divisor) {
        int remainder = dividend % divisor;
        if (remainder == 0) {
            return divisor;
        } else {
            return hcf(divisor, remainder);
        }
    }

    int nCr(int n, int r) {
        int num = 1;
        int den = 1;
        for (int i = 1; i <= r; i++) {
            num *= n - i + 1;
            den *= r - i + 1;
            int _hcf = hcf(num, den);
            num /= _hcf;
            den /= _hcf;
        }
        return num / den;
    }

    // soln-2: combinatorics; complexity = O(m + n)
    int uniquePaths2(int m, int n) {
        // out of m + n - 2 moves to be made, we pick n - 1 moves that must be in horizontal direction
        // (similarly we can pick m - 1 moves that must be in vertical directions)
        return nCr(m + n - 2, n - 1);
    }

    // soln-1: dynamic programming; complexity = O(m x n)
    int uniquePaths1(int m, int n) {
        if (m == 1 || n == 1) {
            return 1;
        }

        vector<vector<int> > mat(m);
        for (int i = 0; i < m; i++) {
            if (i == 0) {
                vector<int> row(n, 1);
                mat[i] = row;
            } else {
                vector<int> row(n, 0);
                row[0] = 1;
                mat[i] = row;
            }
        }

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                mat[i][j] = mat[i - 1][j] + mat[i][j - 1];
            }
        }

        return mat[m - 1][n - 1];
    }

    int uniquePaths(int m, int n) {
        return uniquePaths2(m, n);
    }
};
