// LeetCode-680: https://leetcode.com/problems/valid-palindrome-ii/

#include <iostream>

using namespace std;

class Solution {
private:
    bool isPalindromeSubstr(string &str, int lo, int hi) {
        while (lo < hi) {
            if (str.at(lo) != str.at(hi)) {
                return false;
            }

            lo++;
            hi--;
        }

        return true;
    }

public:
    bool validPalindrome(string s) {
        int len = s.size();
        if (len <= 1) {
            return true;
        }

        int lo = 0;
        int hi = len - 1;
        while (lo < hi) {
            if (s.at(lo) != s.at(hi)) {
                return isPalindromeSubstr(s, lo + 1, hi)
                       || isPalindromeSubstr(s, lo, hi - 1);
            }

            lo++;
            hi--;
        }

        return true;
    }
};
