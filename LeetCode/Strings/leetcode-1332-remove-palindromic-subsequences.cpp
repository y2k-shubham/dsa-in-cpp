// LeetCode-1332: https://leetcode.com/problems/remove-palindromic-subsequences/
// easy problem

#include <cstdio>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
private:
    bool hasMultipleAlphas(string& str) {
        unordered_set<char> charSet(str.begin(), str.end());
        return charSet.size() > 1;
    }

    bool isPalindrome(string& str) {
        int iLo = 0;
        int iHi = ((int) str.size()) - 1;

        while (iLo < iHi) {
            if (str.at(iLo) != str.at(iHi)) {
                return false;
            }

            iLo++;
            iHi--;
        }

        return true;
    }

public:
    int removePalindromeSub(string s) {
        if (hasMultipleAlphas(s)) {
            // printf("hasMultipleAlphas(%s) = true\n", s.c_str());
            return isPalindrome(s) ? 1 : 2;
        } else {
            // printf("hasMultipleAlphas(%s) = false\n", s.c_str());
            return 1;
        }
    }
};
