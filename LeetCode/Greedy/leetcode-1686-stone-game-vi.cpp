// LeetCode-1686: https://leetcode.com/problems/stone-game-vi/
// simple but NOT easy

// soln-blog: https://federico-feresini.medium.com/
// soln-video: https://www.youtube.com/watch?v=iEf6bWgqHZo

#include <cstdio>
#include <functional>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   public:
    int stoneGameVI(vector<int>& aliceValues, vector<int>& bobValues) {
        int len = aliceValues.size();

        vector<pair<int, int> > sumVec(len);
        for (int i = 0; i < len; i++) {
            sumVec[i] = {aliceValues[i] + bobValues[i], aliceValues[i]};
        }

        // sort in descending order https://stackoverflow.com/a/9025216/3679900
        // note that for two stones, if sum of values are same, then it doesn't matter which
        // one we pick (mathematically the net gain / loss will be same)
        sort(sumVec.begin(), sumVec.end(), greater<pair<int, int> >());

        int aliceScore = 0;
        int bobScore = 0;
        int turn = 0;  // 0=alice, 1=bob
        for (int i = 0; i < len; i++) {
            if (turn == 0) {
                aliceScore += sumVec[i].second;
            } else {
                bobScore += sumVec[i].first - sumVec[i].second;
            }

            turn = 1 - turn;  // change turn
        }

        int winner;
        if (aliceScore > bobScore) {
            winner = 1;
        } else if (aliceScore == bobScore) {
            winner = 0;
        } else {
            winner = -1;
        }

        return winner;
    }
};
