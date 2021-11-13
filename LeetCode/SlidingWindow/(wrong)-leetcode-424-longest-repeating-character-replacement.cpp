// LeetCode-424: https://leetcode.com/problems/longest-repeating-character-replacement/
// wrong soln; anyways not easy to think and also quite a feq edge cases

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

class Solution {
   private:
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

   public:
    int characterReplacement(string s, int k) {
        int len = s.size();
        if (len <= 1) {
            return len;
        }

        if (k == 0) {
            return findLongestSameCharSubstrLen(s);
        }

        int maxSubstringLen = -1;
        map<char, int> freqMap;
        map<int, set<char> > freqCharsMap;

        int iLo = -1;
        int iHi = -1;
        while ((iLo <= iHi) && (iHi < len)) {
            // expand window till there are exactly 'k' other chars in window
            // apart from the highest frequency char
            while (iHi < len) {
                iHi++;
                if (iHi == 0) {
                    iLo = 0;
                }
                if (iHi >= len) {
                    break;
                }

                char chIn = s.at(iHi);
                int prevFreq = freqMap[chIn];
                int newFreq = prevFreq + 1;
                if (prevFreq > 0) {
                    freqCharsMap[prevFreq].erase(chIn);
                }
                freqCharsMap[newFreq].insert(chIn);
                freqMap[chIn]++;

                int maxFreq = freqMap[*freqCharsMap.rbegin()->second.begin()];
                int winSize = iHi - iLo + 1;
                int numNonMaxFreqChars = winSize - maxFreq;
                if (numNonMaxFreqChars <= k) {
                    // 'k' or lesser undesired chars in window that can be defaced (replaced)
                    maxSubstringLen = max(maxSubstringLen, winSize);
                } else {
                    // more than 'k' undesired chars in window
                    break;
                }
            }

            // shrink window till there are more than 'k' undesired chars in window
            while (iLo < iHi) {
                char chOut = s.at(iLo);
                int prevFreq = freqMap[chOut];
                int newFreq = prevFreq - 1;
                if (newFreq > 0) {
                    freqCharsMap[newFreq].insert(chOut);
                }
                freqCharsMap[prevFreq].erase(chOut);
                freqMap[chOut]--;

                iLo++;
                if (iLo >= iHi) {
                    break;
                }

                int maxFreq = freqMap[*freqCharsMap.rbegin()->second.begin()];
                int winSize = iHi - iLo + 1;
                int numNonMaxFreqChars = winSize - maxFreq;
                if (numNonMaxFreqChars <= k) {
                    // 'k' or lesser undesired chars in window that can be defaced (replaced)
                    maxSubstringLen = max(maxSubstringLen, winSize);
                    break;
                } else {
                    // more than 'k' undesired chars in window
                    continue;
                }
            }
        }

        return maxSubstringLen;
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

        str = "ABAB";
        k = 2;
        outExpected = 4;
        outComputed = soln.characterReplacement(str, k);
        assert(outExpected == outComputed);

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
        pair<int, int> winIdx = findMaxSingleCharFreqWindow(str, 6);
        printf("%d, %d\n", winIdx.first, winIdx.second);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCharacterReplacement();

    return 0;
}
