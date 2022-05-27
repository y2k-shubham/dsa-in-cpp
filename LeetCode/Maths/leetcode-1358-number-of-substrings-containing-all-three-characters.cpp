// LeetCode-1358: https://leetcode.com/problems/number-of-substrings-containing-all-three-characters/
// a little bit like Permutation & Combination

#include <cstdio>
#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
   public:
    int numberOfSubstrings(string s) {
        int len = s.size();
        if (len < 3) {
            return 0;
        }

        unordered_map<char, int> charFreqMap;

        int numSubStrs = 0;
        int iLo = 0;
        int iHi = -1;
        while (iHi < len) {
            iHi++;
            if (iHi >= len) {
                break;
            }

            char ch = s.at(iHi);
            charFreqMap[ch]++;

            if (charFreqMap.size() == 3) {
                // every substring starting at iLo & ending at iHi, iHi+1 .. (len-1)
                // will have all characters
                numSubStrs += len - iHi;

                while ((iHi - iLo) >= 2) {
                    char ch = s.at(iLo++);
                    charFreqMap[ch]--;
                    if (charFreqMap[ch] == 0) {
                        charFreqMap.erase(ch);
                        break;
                    }

                    // every substring starting at (incremented) iLo & ending at iHi, iHi+1 .. (len-1)
                    // will have all characters
                    numSubStrs += len - iHi;
                }
            }
        }

        return numSubStrs;
    }
};
