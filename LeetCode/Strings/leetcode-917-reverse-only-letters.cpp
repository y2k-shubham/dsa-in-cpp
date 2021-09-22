// LeetCode-917: https://leetcode.com/problems/reverse-only-letters/

#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

class Solution {
   public:
    string reverseOnlyLetters(string s) {
        int len = s.size();

        int iLo = 0;
        int iHi = len - 1;
        while (iLo < iHi) {
            bool loIsAlpha = isalpha(s.at(iLo));
            if (!loIsAlpha) {
                iLo++;
                continue;
            }

            bool hiIsAlpha = isalpha(s.at(iHi));
            if (!hiIsAlpha) {
                iHi--;
                continue;
            }

            char chTmp = s.at(iLo);
            s[iLo] = s.at(iHi);
            s[iHi] = chTmp;

            iLo++;
            iHi--;
        }

        return s;
    }
};
