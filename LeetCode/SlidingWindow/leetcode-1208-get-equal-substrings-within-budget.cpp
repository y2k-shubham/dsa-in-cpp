// LeetCode-1208: https://leetcode.com/problems/get-equal-substrings-within-budget/
// reference (condensed, simple code): @cherryljr https://github.com/cherryljr/LeetCode/blob/master/Get%20Equal%20Substrings%20Within%20Budget.java

#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
   public:
    int equalSubstring(string s, string t, int maxCost) {
        int len = s.size();

        int maxWinLen = 0;
        int maxWinLo = -1, maxWinHi = -1;

        int crrWinLen = 0;
        int crrLo = 0, crrHi = 0;
        int crrCost = 0;
        while (crrHi < len) {
            crrCost += abs(s.at(crrHi) - t.at(crrHi));

            while (crrCost > maxCost) {
                crrCost -= abs(s.at(crrLo) - t.at(crrLo));
                crrLo++;
            }

            crrWinLen = crrHi - crrLo + 1;
            maxWinLen = max(maxWinLen, crrWinLen);

            crrHi++;
        }

        return maxWinLen;
    }
};
