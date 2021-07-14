// Somewhat wierd problem (easy but slightly tricky to understand / reason about)
// LeetCode-1433: https://leetcode.com/problems/check-if-a-string-can-break-another-string/

#include <algorithm>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
   private:
    bool doesBreak(string smallStr, string bigStr) {
        for (int i = 0; i < smallStr.size(); i++) {
            char chSmall = smallStr.at(i);
            char chBig = bigStr.at(i);

            if (chSmall > chBig) {
                return false;
            }
        }

        return true;
    }

   public:
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());

        return doesBreak(s1, s2) || doesBreak(s2, s1);
    }
};
