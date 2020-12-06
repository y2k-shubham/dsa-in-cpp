// LeetCode-877: https://leetcode.com/problems/stone-game/

/**
 * @file leetcode-877-stone-game.cpp
 * @author Shubham Gupta (y2k-shubham)
 * 
 * @brief the idea is that for each subarray of piles, we determine the scores earned by
 * Alex & Lee as per our constraints (Alex starts first, both play optimally). Assuming we
 * can do that, we can then combine the results of sub-problems as follows
 * 
 * suppose we have already computed results (scores earned by both) for subarrays
 * [i+1 .. j] & [i .. j-1] and we want to determine result for [i .. j], then there are 2 options
 *  1. Alex starts by picking [i], in which case Lee will be able to score what Alex would've as
 *     per result of [i+1 .. j], and correspondingly, in that range, Alex scores what Lee would've scored
 *  2. Alex starts by picking [j], in which case Lee will be able to score what Alex would've as
 *     per result of [i .. j-1], and correspondingly, in that range, Alex scores what Lee would've scored
 * 
 *  - then of the above two options, we (obviously) pick the one that promises higher total score (after sum)
 * for Alex.
 *  - In case both options earn equal score for Alex (is that even possible?), we pick the one
 * that gives lower score to Lee
 * 
 * @date 2020-12-07
 * @copyright Copyright (c) 2020
 */

#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

vector<vector<pair<int, int> > > createMemoMat(vector<int>& piles) {
    int len = piles.size();

    vector<vector<pair<int, int> > > memoMat(len);
    for (int i = 0; i < len; i++) {
        vector<pair<int, int> > row(len, {INT_MIN, INT_MAX});
        row[i] = {piles[i], 0};
        memoMat[i] = row;
    }

    return memoMat;
}

// LC-submission speed: 7 %tile, memory: 5 %tile
void fillMemoMat(vector<int>& piles, vector<vector<pair<int, int> > >& memoMat) {
    int len = piles.size();

    int rLo = 0;
    int cHi = len - 1;
    for (int subArrSize = 2; subArrSize <= len; subArrSize++) {
        int rBegin = rLo;
        int cBegin = subArrSize - 1;

        int i = rBegin;
        int j = cBegin;
        while (j <= cHi) {
            // in subarr i..j Alex starts by picking i
            pair<int, int> op1 = {piles[i] + memoMat[i + 1][j].second, memoMat[i + 1][j].first};
            // in subarr i..j Alex starts by picking j
            pair<int, int> op2 = {memoMat[i][j - 1].second + piles[j], memoMat[i][j - 1].first};

            if (op1.first > op2.first) {
                memoMat[i][j] = op1;
            } else if (op1.first == op2.first) {
                memoMat[i][j] = (op1.second < op2.second) ? op1 : op2;
            } else {
                memoMat[i][j] = op2;
            }

            i++;
            j++;
        }
    }
}

bool stoneGame(vector<int>& piles) {
    int len = piles.size();

    vector<vector<pair<int, int> > > memoMat = createMemoMat(piles);
    fillMemoMat(piles, memoMat);

    return (memoMat[0][len - 1].first > memoMat[0][len - 1].second);
}
