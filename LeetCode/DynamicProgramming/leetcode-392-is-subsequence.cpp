// LeetCode-392: https://leetcode.com/problems/is-subsequence/

#include <cstdio>
#include <iostream>

using namespace std;

// LC-submission speed: 100 %tile, memory: 63 %tile
bool isSubsequence(string s, string t) {
    int tInd = 0;
    int sInd = 0;

    int tLen = t.size();
    int sLen = s.size();

    if (tLen == 0) {
        return sLen == 0;
    } else {
        while ((sInd < sLen) && (tInd < tLen)) {
            if (s.at(sInd) == t.at(tInd)) {
                sInd++;
            }
            tInd++;
        }

        return (sInd == sLen);
    }
}
