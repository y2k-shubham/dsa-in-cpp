// Weekly Contest 286: https://leetcode.com/contest/weekly-contest-286/problems/maximum-value-of-k-coins-from-piles/
// hard, dynamic programming

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
private:
    int findMaxPileSize(vector<vector<int>> &piles) {
        int maxPileSize = 0;
        for (int i = 0; i < piles.size(); i++) {
            maxPileSize = max(maxPileSize, (int) piles[i].size());
        }

        return maxPileSize;
    }

    pair <int, int> calcNumRowsCols(vector<vector<int>> &piles, int maxPileSize, int k) {
        int n = piles.size();
        int numCols = n;
        int numRows = max(maxPileSize, k);

        return {numRows, numCols};
    }

    vector<vector<int> > createMemoMat(vector<vector<int>> &piles, int maxPileSize, int k) {
        pair <int, int> numRowsCols = calcNumRowsCols(piles, maxPileSize, k);
        int numRows = numRowsCols.first;
        int numCols = numRowsCols.second;

        vector<vector<int>> memoMat(numRows);
        for (int i = 0; i < numRows; i++) {
            vector<int> memoMatRow(numCols);
            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    int fillMemoMat(
            vector<vector<int>> &piles,
            int maxPileSize,
            int k,
            vector<vector<int>> &memoMat
    ) {
        pair <int, int> numRowsCols = calcNumRowsCols(piles, maxPileSize, k);
        int numRows = numRowsCols.first;
        int numCols = numRowsCols.second;

        vector <int> maxValFromRows(numRows);
        for (int j = 0; j < numCols; j++) {
            int crrPileSize = piles[j].size();

            // calc cumulative sum of current pile coins
            vector <int> crrPileCumSum(numRows);
            int i;
            // calculate cum sum of actual pile coins
            crrPileCumSum[0] = piles[j][0];
            for (i = 1; i < crrPileSize; i++) {
                crrPileCumSum[i] = crrPileCumSum[i - 1] + piles[j][i];
            }
            // fill up remaining values with total sum
            while (i < numRows) {
                crrPileCumSum[i] = crrPileCumSum[i - 1];
                i++;
            }

            int maxValCrrCol = 0;
            for (int i = 0; i < numRows; i++) {
                int k;
                for (k = 0; k <= min(i, crrPileSize); k++) {
                    // here k denotes no of coins picked from current (jth) pile
                    int crrPileVal = (k == 0) ? 0 : crrPileCumSum[k - 1];
                    int remNumCoins = i - k + 1;
                    int prevPilesMaxVal = maxValFromRows[i - k];
                }
            }
        }
    }

public:
    int maxValueOfCoins(vector<vector<int>> &piles, int k) {

    }
};
