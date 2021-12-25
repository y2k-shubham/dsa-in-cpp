// LeetCode-2108: https://leetcode.com/problems/find-first-palindromic-string-in-the-array/
// pretty dumb problem; dont bother to look

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool isPalindrome(string& str) {
        int len = str.size();
        if (len <= 1) {
            return true;
        }

        int iLo = 0, iHi = len - 1;
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
    string firstPalindrome(vector<string>& words) {
        for (int i = 0; i < words.size(); i++) {
            if (isPalindrome(words[i])) {
                return words[i];
            }
        }

        return "";
    }
};
