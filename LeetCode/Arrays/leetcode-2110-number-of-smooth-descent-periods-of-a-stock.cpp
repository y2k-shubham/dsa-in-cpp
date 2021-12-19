// LeetCode-2110: https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   public:
    long long getDescentPeriods(vector<int>& prices) {
        int len = prices.size();
        if (len <= 1) {
            return 1;
        }

        long long numPeriods = 0;
        int iLo = 0, iHi = 0;
        while (iHi < len) {
            while ((iHi < len) && ((iLo == iHi) || ((prices[iHi - 1] - prices[iHi]) == 1))) {
                numPeriods += iHi - iLo + 1;
                iHi++;
            }

            iLo = iHi;
        }

        return numPeriods;
    }
};
