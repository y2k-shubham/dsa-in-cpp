// LeetCode-486: https://leetcode.com/problems/predict-the-winner/

#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<vector<pair<int, int> > > createMemoMat(vector<int>& nums) {
        int len = nums.size();

        vector<vector<pair<int, int> > > memoMat(len);
        for (int i = 0; i < len; i++) {
            vector<pair<int, int> > memoMatRow(len);
            memoMatRow[i].first = nums[i];
            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    /**
     * formulation of memoization table memoMat
     *
     * memoMat[r][c] = {p1Score, p2Score}
     *
     * above means that if we take subarray nums[r .. c], then
     * - whichever player takes first turn can achieve a maximum of p1Score score
     * - and the other player (who takes second turn) can achieve a maximum of p2Score score
     */
    void fillMemoMat(vector<int>& nums, vector<vector<pair<int, int> > >& memoMat) {
        int len = nums.size();

        for (int subLen = 2; subLen <= len; subLen++) {
            int cLo = subLen - 1;
            int cHi = len - 1;

            int rLo = 0;
            int rHi = len - subLen;

            int c = cLo;
            int r = rLo;
            while (c <= cHi) {
                // determine scores of both players when picking numbers in nums[r .. c] subarray

                // how much can both players score if player 1 starts by picking nums[r]
                int p1LPickScore = nums[r] + memoMat[r + 1][c].second;
                int p2LPickScore = memoMat[r + 1][c].first;

                // how much can both players score if player 1 starts by picking nums[c]
                int p1RPickScore = nums[c] + memoMat[r][c - 1].second;
                int p2RPickScore = memoMat[r][c - 1].first;

                // pick that combination of scores which makes
                // - player 1 score higher (among the two combinations)
                // - or if player 1 is scoring same in both combinations, then pick that where player 2 scores lesser
                if ((p1LPickScore > p1RPickScore) || ((p1LPickScore == p1RPickScore) && (p2LPickScore < p2RPickScore))) {
                    memoMat[r][c] = {p1LPickScore, p2LPickScore};
                } else {
                    memoMat[r][c] = {p1RPickScore, p2RPickScore};
                }

                r++;
                c++;
            }
        }
    }

   public:
    bool PredictTheWinner(vector<int>& nums) {
        int len = nums.size();
        if (len <= 2) {
            return true;
        }

        vector<vector<pair<int, int> > > memoMat = createMemoMat(nums);
        fillMemoMat(nums, memoMat);

        return memoMat[0][len - 1].first >= memoMat[0][len - 1].second;
    }
};
