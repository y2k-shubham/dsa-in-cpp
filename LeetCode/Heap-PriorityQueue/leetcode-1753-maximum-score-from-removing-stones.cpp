// LeetCode-1753: https://leetcode.com/problems/maximum-score-from-removing-stones/

#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

class Solution {
   public:

   // LC-submission: speed 31 %tile, memory 36 %tile
    int maximumScore(int a, int b, int c) {
        priority_queue<int> pQue;

        pQue.push(a);
        pQue.push(b);
        pQue.push(c);

        int score = 0;
        while (pQue.size() >= 2) {
            // take stones from 2 biggest piles
            int pile1Stones = pQue.top();
            pQue.pop();

            int pile2Stones = pQue.top();
            pQue.pop();

            // update score
            score++;

            // update pile sizes
            pile1Stones--;
            pile2Stones--;

            if (pile1Stones > 0) {
                pQue.push(pile1Stones);
            }
            if (pile2Stones > 0) {
                pQue.push(pile2Stones);
            }
        }

        return score;
    }
};
