// LeetCode-1578: https://leetcode.com/problems/minimum-time-to-make-rope-colorful/

#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    int minCost(string colors, vector<int>& neededTime) {
        int len = colors.size();
        if (len <= 1) {
            return 0;
        }

        int totalTime = 0;

        int crrSeqLen = 0;
        int crrMaxTime = 0;
        int crrTotalTime = 0;
        for (int i = 0; i < len; i++) {
            bool equalsPrev = (i == 0) ? false : (colors.at(i - 1) == colors.at(i));
            if (equalsPrev) {
                // if crr balloon is same colored as previous,
                // just update max-time & total-time (of current continuous seq of same-colored balloons)
                crrMaxTime = max(crrMaxTime, neededTime[i]);
                crrTotalTime += neededTime[i];
                crrSeqLen++;
            } else {
                // otherwise it is the beginning of a new seq of (some different) colored balloons
                if (crrSeqLen >= 2) {
                    // first update totalTime with the time it would take to remove all but 1 (the one that takes max-time) balloon
                    // balloon in the previous continuous seq of same-colored balloons
                    totalTime += crrTotalTime - crrMaxTime;
                }

                // then reset the variables to indicate beginning of a new seq of (some different) colored balloons
                crrSeqLen = 1;
                crrMaxTime = neededTime[i];
                crrTotalTime = neededTime[i];
            }
        }

        // this is needed to handle the case where rope ends with a seq of same-colored balloons
        // (since loop would end and this trailing seq of same-colored balloons would get left out)
        if (crrSeqLen >= 2) {
            totalTime += crrTotalTime - crrMaxTime;
        }

        return totalTime;
    }
};
