// LeetCode-2140: https://leetcode.com/problems/solving-questions-with-brainpower/
// very similar to 'Maximum Sum Subsequence Non-Adjacent'; TusharRoy: https://www.youtube.com/watch?v=UtGtF6nc35g

#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long mostPoints(vector<vector<int>>& questions) {
        int len = questions.size();
        if (len == 0) {
            return 0;
        }
        if (len == 1) {
            return questions[0][0];
        }


        // we'll fill up these vectors from right (end) to left (begin)
        vector<long long> incScores(len, 0); // incScores[i] represents max score possible by considering questions i..n and necessarily solving questions[i]
        vector<long long> excScores(len, 0); // excScores[i] represents max score possible by considering questions i..n and necessarily skipping questions[i]

        incScores[len - 1] = questions[len - 1][0];
        for (int i = len - 2; i >= 0; i--) {
            int crrScore = questions[i][0];
            int skipCount = questions[i][1];

            // determine max score possible from sequence of questions remaining after skipping the required no of questions beyond questions[i]
            long long prevMaxScore = 0;
            int prevMaxScoreIdx = i + skipCount + 1;
            if (prevMaxScoreIdx < len) {
                prevMaxScore = max(incScores[prevMaxScoreIdx], excScores[prevMaxScoreIdx]);
            }
            // in essence, this is the max 'inclusive' score: max score possible by solving / including questions[i]
            long long incScore = crrScore + prevMaxScore;
            incScores[i] = incScore;

            // this is the max 'exclusive' score: max score possible by skipping questions[i]
            long long excScore = max(incScores[i + 1], excScores[i + 1]);
            excScores[i] = excScore;
        }

        return max(incScores[0], excScores[0]);
    }
};
