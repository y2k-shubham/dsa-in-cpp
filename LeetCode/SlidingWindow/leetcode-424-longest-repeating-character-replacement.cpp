// LeetCode-424: https://leetcode.com/problems/longest-repeating-character-replacement/
// NickWhite: https://www.youtube.com/watch?v=00FmUN1pkGE

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

#define NUM_ALPHAS 26

class Solution {
   private:
    bool debug;
    int findLongestSameCharSubstrLen(string str) {
        int len = str.size();

        int longestSubstrLen = 1;
        int substrStartIdx = 0;
        for (int i = 1; i < len; i++) {
            char prevChar = str.at(i - 1);
            char crrChar = str.at(i);

            if (prevChar == crrChar) {
                // continue expanding window
                int crrSubstrLen = i - substrStartIdx + 1;
                longestSubstrLen = max(longestSubstrLen, crrSubstrLen);
            } else {
                // reset window
                substrStartIdx = i;
            }
        }

        return longestSubstrLen;
    }

    int findMaxVal(vector<int>& vec) {
        return *max_element(vec.begin(), vec.end());
    }

    void showFreqVec(vector<int>& vec) {
        for (int i = 0; i < vec.size(); i++) {
            if (vec[i] > 0) {
                printf("'%c' -> %d\n", ((char)('A' + i)), vec[i]);
            }
        }
    }

   public:
    friend class SolutionTest;

    int characterReplacement(string s, int k) {
        int len = s.size();
        if (len <= 1) {
            return len;
        }

        if (k == 0) {
            return findLongestSameCharSubstrLen(s);
        }
        if (k >= len) {
            return len;
        }

        vector<int> freqVec(NUM_ALPHAS, 0);
        int maxWinLen = -1;
        int iLo = -1;
        int iHi = -1;
        while ((iLo <= iHi) && (iHi < len)) {
            iHi++;
            if (iHi == 0) {
                iLo = 0;
            }
            if (iHi >= len) {
                break;
            }

            char chIn = s.at(iHi);
            freqVec[chIn - 'A']++;

            int maxFreq = findMaxVal(freqVec);
            if (debug) {
                printf("\n");
                printf("s[iLo=%d .. iHi=%d] = %c .. %c, included s[iHi=%d] = %c\n", iLo, iHi, s.at(iLo), s.at(iHi), iHi, s.at(iHi));
                showFreqVec(freqVec);
                printf("maxFreq = %d\n", maxFreq);
            }

            // keep shrinking the window till there are more than 'k' chars to replace
            while ((iLo < iHi) && ((iHi - iLo + 1 - maxFreq) > k)) {
                char chOut = s.at(iLo);
                iLo++;

                freqVec[chOut - 'A']--;

                maxFreq = findMaxVal(freqVec);

                if (debug) {
                    printf("\n");
                    printf("s[iLo=%d .. iHi=%d] = %c .. %c, excluded s[iLo-1=%d] = %c\n", iLo, iHi, s.at(iLo), s.at(iHi), iLo - 1, s.at(iLo - 1));
                    showFreqVec(freqVec);
                    printf("maxFreq = %d\n", maxFreq);
                }
            }

            int crrWinLen = iHi - iLo + 1;
            maxWinLen = max(maxWinLen, crrWinLen);
        }

        return maxWinLen;
    }
};

class SolutionTest {
   private:
    pair<int, int> findMaxSingleCharFreqWindow(string str, int winLen) {
        unordered_map<char, int> freqMap;

        int len = str.size();
        int maxFreq = 1;
        int maxFreqStart = -1;
        int maxFreqEnd = -1;
        int i = 0;
        while (i < len) {
            char chIn = str.at(i);
            int crrFreq = freqMap[chIn];
            int newFreq = crrFreq + 1;
            freqMap[chIn] = newFreq;

            if (i >= winLen) {
                char chOut = str.at(i - winLen);
                freqMap[chOut]--;
            }

            if (newFreq > maxFreq) {
                maxFreq = newFreq;
                maxFreqStart = i - len;
                maxFreqEnd = i;
            }
        }

        return {maxFreqStart, maxFreqEnd};
    }

   public:
    void testCharacterReplacement() {
        Solution soln = Solution();
        string str;
        int k;
        int outExpected, outComputed;

        // soln.debug = true;
        str = "ABAB";
        k = 2;
        outExpected = 4;
        outComputed = soln.characterReplacement(str, k);
        // printf("outComputed = %d\n", outComputed);
        assert(outExpected == outComputed);
        // soln.debug = false;

        str = "AABABBA";
        k = 1;
        outExpected = 4;
        outComputed = soln.characterReplacement(str, k);
        assert(outExpected == outComputed);

        str = "F";
        k = 1;
        outExpected = 1;
        outComputed = soln.characterReplacement(str, k);
        assert(outExpected == outComputed);

        str = "AFQ";
        k = 2;
        outExpected = 3;
        outComputed = soln.characterReplacement(str, k);
        assert(outExpected == outComputed);

        str = "AFQ";
        k = 1;
        outExpected = 2;
        outComputed = soln.characterReplacement(str, k);
        assert(outExpected == outComputed);

        str = "AFQ";
        k = 0;
        outExpected = 1;
        outComputed = soln.characterReplacement(str, k);
        assert(outExpected == outComputed);

        str = "ABAA";
        k = 0;
        outExpected = 2;
        outComputed = soln.characterReplacement(str, k);
        assert(outExpected == outComputed);

        str = "BAAAB";
        k = 2;
        outExpected = 5;
        outComputed = soln.characterReplacement(str, k);
        assert(outExpected == outComputed);

        str = "IMNJJTRMJEGMSOLSCCQICIHLQIOGBJAEHQOCRAJQMBIBATGLJDTBNCPIFRDLRIJHRABBJGQAOLIKRLHDRIGERENNMJSDSSMESSTR";
        k = 2;
        outExpected = 6;
        outComputed = soln.characterReplacement(str, k);
        // pair<int, int> winIdx = findMaxSingleCharFreqWindow(str, 6);
        // printf("%d, %d\n", winIdx.first, winIdx.second);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCharacterReplacement();

    return 0;
}
