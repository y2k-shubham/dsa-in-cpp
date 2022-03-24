// LeetCode-392: https://leetcode.com/problems/is-subsequence/submissions/

#include <iostream>

using namespace std;

class Solution {
   public:
    bool isSubsequence(string s, string t) {
        int lenS = s.size();
        int lenT = t.size();

        if (lenS == 0) {
            return true;
        }
        if (lenT < lenS) {
            return false;
        }

        int iS = 0;
        int iT = 0;
        while ((iS < lenS) && (iT < lenT)) {
            if (s.at(iS) == t.at(iT)) {
                iS++;
            }

            iT++;
        }

        return (iS >= lenS);
    }
};
