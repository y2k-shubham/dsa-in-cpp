// LeetCode-518: https://leetcode.com/problems/coin-change-2/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<int> > createMemoMat(int amount, vector<int>& coins) {
        int numCoins = coins.size();

        vector<vector<int> > memoMat(numCoins + 1);
        for (int i = 0; i <= numCoins; i++) {
            vector<int> memoMatRow(amount + 1, 0);
            memoMatRow[0] = 1;

            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    void fillMemoMat(int amount, vector<int>& coins, vector<vector<int> >& memoMat) {
        int numCoins = coins.size();
        sort(coins.begin(), coins.end());

        for (int c = 1; c <= numCoins; c++) {
            int a;
            int crrCoinVal = coins[c - 1];

            // value of current coin is greater than current amount
            for (a = 1; a < crrCoinVal; a++) {
                memoMat[c][a] = memoMat[c - 1][a];
            }

            for (; a <= amount; a++) {
                memoMat[c][a] = memoMat[c][a - crrCoinVal] + memoMat[c - 1][a];
            }
        }
    }

   public:
    int change(int amount, vector<int>& coins) {
        int numCoins = coins.size();

        vector<vector<int> > memoMat = createMemoMat(amount, coins);
        fillMemoMat(amount, coins, memoMat);

        return memoMat[numCoins][amount];
    }
};

class SolutionTest {
   public:
    void testChange() {
        Solution soln = Solution();
        int inAmount;
        vector<int> inCoins;
        int outCombsExpected, outCombsComputed;

        inAmount = 5;
        inCoins = {1, 2, 5};
        outCombsExpected = 4;
        outCombsComputed = soln.change(inAmount, inCoins);
        assert(outCombsExpected == outCombsComputed);

        inAmount = 15;
        inCoins = {1, 2, 5};
        outCombsExpected = 18;
        outCombsComputed = soln.change(inAmount, inCoins);
        assert(outCombsExpected == outCombsComputed);

        inAmount = 75;
        inCoins = {1, 2, 5};
        outCombsExpected = 312;
        outCombsComputed = soln.change(inAmount, inCoins);
        assert(outCombsExpected == outCombsComputed);

        inAmount = 3;
        inCoins = {2};
        outCombsExpected = 0;
        outCombsComputed = soln.change(inAmount, inCoins);
        assert(outCombsExpected == outCombsComputed);

        inAmount = 10;
        inCoins = {10};
        outCombsExpected = 1;
        outCombsComputed = soln.change(inAmount, inCoins);
        assert(outCombsExpected == outCombsComputed);

        inAmount = 150;
        inCoins = {1, 2, 5, 10, 20, 50, 100, 200};
        outCombsExpected = 21873;
        outCombsComputed = soln.change(inAmount, inCoins);
        // cout << outCombsComputed << endl;
        assert(outCombsExpected == outCombsComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testChange();
    return 0;
}
