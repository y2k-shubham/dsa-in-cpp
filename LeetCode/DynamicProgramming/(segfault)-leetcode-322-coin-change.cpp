// LeetCode-322: https://leetcode.com/problems/coin-change/
// approach is correct, but gives SEGFAULT when submitted on LeetCode

#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool debug = false;

    int add(int val1, int val2) {
        if (max(val1, val2) == INT_MAX) {
            return INT_MAX;
        }

        return val1 + val2;
    }

    void showMat(
            vector<vector<int> >& mat,
            vector<int>& coins,
            int totalAmt
    ) {
        printf("mat is:-\n");

        printf("Amt\t\t");
        for (int i = 0; i <= totalAmt; i++) {
            printf("%d\t", i);
        }
        cout << endl;

        printf("Ind\t\t");
        for (int i = 0; i <= totalAmt; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        for (int i = 0; i <= coins.size(); i++) {
            int crrCoinVal = coins[i];
            printf("%d\t[%d]\t", crrCoinVal, i);

            for (int j = 0; j <= totalAmt; j++) {
                if (mat[i][j] == INT_MAX) {
                    printf("-\t");
                } else {
                    printf("%d\t", mat[i][j]);
                }
            }
            cout << endl;
        }
    }

    vector<vector<int> > buildMat(int numDenominations, int amount) {
        vector<vector<int>> mat(numDenominations + 1);

        for (int i = 0; i <= numDenominations; i++) {
            vector<int> matRow(amount + 1, INT_MAX);
            matRow[0] = 0;

            mat[i] = matRow;
        }

        return mat;
    }

    void fillMat(
            vector<vector<int> >& mat,
            vector<int>& coins,
            int totalAmt
    ) {
        for (int crrCoinIdx = 1; crrCoinIdx <= coins.size(); crrCoinIdx++) {
            int crrCoinVal = coins[crrCoinIdx - 1];

            for (int crrAmt = 1; crrAmt < crrCoinVal; crrAmt++) {
                mat[crrCoinIdx][crrAmt] = mat[crrCoinIdx - 1][crrAmt];
            }

            for (int crrAmt = crrCoinVal; crrAmt <= totalAmt; crrAmt++) {
                mat[crrCoinIdx][crrAmt] = add(1, mat[crrCoinIdx][crrAmt - crrCoinVal]);
            }
        }
    }

public:
    friend class SolutionTest;

    int coinChange(vector<int>& coins, int amount) {
        if (amount == 0) {
            return 0;
        }

        if (coins.empty()) {
            return -1;
        }

        int numDenominations = coins.size();
        sort(coins.begin(), coins.end());

        int smallestCoinVal = coins[0];
        if (amount < smallestCoinVal) {
            return -1;
        }

        vector<vector<int> > mat = buildMat(numDenominations, amount);
        if (debug) {
            showMat(mat, coins, amount);
        }

        fillMat(mat, coins, amount);
        if (debug) {
            showMat(mat, coins, amount);
        }

        int reqNumCoins = mat[numDenominations][amount];
        return (reqNumCoins == INT_MAX) ? -1 : reqNumCoins;
    }
};

class SolutionTest {
public:
    void testCoinChange() {
        Solution soln = Solution();
        vector<int> coinsIn;
        int amountIn;
        int numCoinsOutExpected, numCoinsOutComputed;

//        soln.debug = true;
        coinsIn = {1, 2, 5};
        amountIn = 11;
        numCoinsOutExpected = 3;
        numCoinsOutComputed = soln.coinChange(coinsIn, amountIn);
//        cout << numCoinsOutComputed << endl;
        assert(numCoinsOutExpected == numCoinsOutComputed);
//        soln.debug = false;

        coinsIn = {2};
        amountIn = 3;
        numCoinsOutExpected = -1;
        numCoinsOutComputed = soln.coinChange(coinsIn, amountIn);
        assert(numCoinsOutExpected == numCoinsOutComputed);

        coinsIn = {1};
        amountIn = 0;
        numCoinsOutExpected = 0;
        numCoinsOutComputed = soln.coinChange(coinsIn, amountIn);
        assert(numCoinsOutExpected == numCoinsOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCoinChange();

    return 0;
}
