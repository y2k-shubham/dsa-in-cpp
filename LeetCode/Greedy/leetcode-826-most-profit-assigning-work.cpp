// LeetCode-826: https://leetcode.com/problems/most-profit-assigning-work/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

bool comparator(pair<int, int>& p1, pair<int, int>& p2) {
    if (p1.first > p2.first) {
        // descending order of first value
        return true;
    } else if (p1.first < p2.first) {
        // descending order of first value
        return false;
    } else {
        // if first values of pairs match,
        // then descending order of second value
        return p1.second >= p2.second;
    }
}

class Solution {
   private:
    vector<pair<int, int> > zipVecs(vector<int>& vec1, vector<int>& vec2) {
        int len = vec1.size();

        vector<pair<int, int> > vecZipped(len);
        for (int i = 0; i < len; i++) {
            vecZipped[i] = {vec1[i], vec2[i]};
        }

        return vecZipped;
    }

    int findMaxProfit(
        vector<int>& abilityVec,
        vector<pair<int, int> >& profDiffVec) {
        int maxProfit = 0;

        vector<int>::iterator uBound = abilityVec.end();
        for (int i = 0; i < profDiffVec.size(); i++) {
            int profit = profDiffVec[i].first;
            int difficulty = profDiffVec[i].second;

            // check if there are some workers who have ability to do current job
            vector<int>::iterator it = lower_bound(abilityVec.begin(), uBound, difficulty);
            if (it != uBound) {
                // every worker from it to uBound+1 can be assigned current job
                int numWorkers = distance(it, uBound);
                maxProfit += numWorkers * profit;

                // update upper bound: shrink range
                // (as workers beyond uBound have already been assigned a job)
                uBound = it;
            }
        }

        return maxProfit;
    }

   public:
    int maxProfitAssignment(vector<int>& difficulty, vector<int>& profit, vector<int>& worker) {
        vector<pair<int, int> > profDiffVec = zipVecs(profit, difficulty);
        // sort jobs in [1] descending order of profit [2] descending order of difficulty
        sort(profDiffVec.begin(), profDiffVec.end(), comparator);

        // sort workers in ascending order of their abilities
        sort(worker.begin(), worker.end());

        return findMaxProfit(worker, profDiffVec);
    }
};
