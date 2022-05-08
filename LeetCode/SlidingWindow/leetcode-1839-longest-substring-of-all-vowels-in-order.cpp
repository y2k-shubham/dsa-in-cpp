// LeetCode-1839: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/

#include <cstdio>
#include <iostream>
#include <map>
#include <cassert>
#include <unordered_map>

using namespace std;

class Solution {
private:
    bool debug = false;

    const char firstAlpha = 'a';
    const char lastAlpha = 'u';
    map<char, char> nextAlphaMap = {
            {'a', 'e'},
            {'e', 'i'},
            {'i', 'o'},
            {'o', 'u'},
            {'u', '\0'},
    };

    void resetFreqs(unordered_map<char, int>& freqMap) {
        for (char ch = firstAlpha; ch <= lastAlpha; ch++) {
            freqMap[ch] = 0;
        }
    }

public:
    friend class SolutionTest;

    // poor performance
    // LC submission speed 5 %tile, memory 26 %tile
    int longestBeautifulSubstring(string word) {
        int maxWinLen = 0;

        int crrWinLo = 0;
        int crrWinHi = 0;
        char reqAlpha = firstAlpha;
        unordered_map<char, int> freqMap;
        while (crrWinHi < word.size()) {
            char crrAlpha = word.at(crrWinHi);
            freqMap[crrAlpha]++;

            bool hiIncremented = true;
            if (crrAlpha == reqAlpha) {
                // we got the alphabet we were expecting

                if (crrAlpha == lastAlpha) {
                    // if that alphabet was 'u', then update the max window length
                    int crrWinLen = crrWinHi - crrWinLo + 1;
                    if (debug) {
                        printf("1: at word.at(iHi=%d)=%c, crrWinLen=%d\n", crrWinHi, crrAlpha, crrWinLen);
                    }
                    maxWinLen = max(maxWinLen, crrWinLen);
                }

                // just continue as it is
                crrWinHi++;
            } else if ((freqMap[reqAlpha] > 0) && (crrAlpha == nextAlphaMap[reqAlpha])) {
                // we got next (vowel) alphabet of the one that was ongoing (expecting)
                // IMPORTANT: this should've happened only after at least 1 occurrence of required alphabet

                // update our expectation from this point onwards
                reqAlpha = crrAlpha;

                // IMPORTANT: dont forget this -> we might have just moved from an 'o' to a 'u'
                if (crrAlpha == lastAlpha) {
                    int crrWinLen = crrWinHi - crrWinLo + 1;
                    if (debug) {
                        printf("2: at word.at(iHi=%d)=%c, crrWinLen=%d\n", crrWinHi, crrAlpha, crrWinLen);
                    }
                    maxWinLen = max(maxWinLen, crrWinLen);
                }

                // again continue as it is
                crrWinHi++;
            } else {
                if (debug) {
                    printf("resetting window at word.at(iHi=%d)=%c because cond1=%s, cond2=%s\n", crrWinHi, crrAlpha,
                           (((freqMap[reqAlpha] > 0)) ? "true" : "false"),
                           ((crrAlpha == nextAlphaMap[reqAlpha]) ? "true" : "false"));
                }

                // we'll have to reset our Sliding window as we've run into a malformed sequence
                resetFreqs(freqMap);

                if (crrAlpha != firstAlpha) {
                    // if we aren't at an 'a', we also advance the end of our window
                    crrWinHi++;
                } else {
                    hiIncremented = false;
                }

                // reset the window & expectation
                crrWinLo = crrWinHi;
                reqAlpha = firstAlpha;
            }

            if (debug) {
                int hiEff = hiIncremented ? (crrWinHi - 1) : crrWinHi;
                printf("after word.at(iLo=%d)=%c .. word.at(iHi=%d)=%c, reqAlpha=%c\n", crrWinLo, word.at(crrWinLo),
                       hiEff, crrAlpha, reqAlpha);
            }
        }

        return maxWinLen;
    }
};

class SolutionTest {
public:
    void testLongestBeautifulSubstring() {
        Solution soln = Solution();
        string strIn;
        int outExpected, outComputed;

//        soln.debug = true;
        strIn = "aeiaaioaaaaeiiiiouuuooaauuaeiu";
        outExpected = 13;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);
//        soln.debug = false;

        strIn = "aeeeiiiioooauuuaeiou";
        outExpected = 5;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

        strIn = "a";
        outExpected = 0;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

        strIn = "ae";
        outExpected = 0;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

        strIn = "aei";
        outExpected = 0;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

        strIn = "aeio";
        outExpected = 0;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

        strIn = "aeiou";
        outExpected = 5;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

        strIn = "aeiouu";
        outExpected = 6;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

        strIn = "aeiouua";
        outExpected = 6;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

        strIn = "aeiouaua";
        outExpected = 5;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);

//        soln.debug = true;
        strIn = "auoeioueiaaioeuieuoaieuaoeuoaiaoueioiaeuiuaeouaoie";
        outExpected = 0;
        outComputed = soln.longestBeautifulSubstring(strIn);
        assert(outComputed == outExpected);
//        soln.debug = false;
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testLongestBeautifulSubstring();

    return 0;
}
