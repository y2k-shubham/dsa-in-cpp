// BiWeekly Contest 45 (Feb 2021): https://leetcode.com/contest/biweekly-contest-45/problems/minimum-length-of-string-after-deleting-similar-ends/
// without using references to pass string, it goes TLE

#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
   public:
    bool canDelete(string& str, int i, int j) {
        int len = str.size();

        if (i < len && j >= 0) {
            return str.at(i) == str.at(j);
        }

        return false;
    }

    int eatCharsFromLeft(string& str, int idx) {
        int len = str.size();
        char ch = str.at(idx);

        int i;
        for (i = idx; (i < len) && (str.at(i) == ch); i++) {
            // nothing
        }

        return i;
    }

    int eatCharsFromRight(string& str, int idx) {
        char ch = str.at(idx);

        int i;
        for (i = idx - 1; (i >= 0) && (str.at(i) == ch); i--) {
            // nothing
        }

        return i;
    }

    int minimumLength(string str) {
        int len = str.size();
        if (len <= 1) {
            return 1;
        }

        int i = 0;
        int j = len - 1;
        while (canDelete(str, i, j)) {
            i = eatCharsFromLeft(str, i);
            if (i > j) {
                return 0;
            }

            j = eatCharsFromRight(str, j);
            if (j < i) {
                return 0;
            }

            if (i == j) {
                return 1;
            }
        }

        return (j - i + 1);
    }
};
