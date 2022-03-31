// LeetCode-1371: https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/
// idea taken from LC hints

#include <cstdio>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <unordered_set>

#define SMALLEST_CHAR 'a'
using namespace std;

class Solution {
private:
    bool debug = false;
    unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

    bool isVowel(char ch) {
        return vowels.find(ch) != vowels.end();
    }

    // unused function
    int createBitMask(unordered_map<char, int> &freqMap) {
        int bitMask = 0;
        for (unordered_map<char, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            char ch = it->first;
            int freq = it->second;

            int freqMod = freq % 2;
            if (freqMod == 1) {
                bitMask |= 1 << (ch - SMALLEST_CHAR);
            }

            if (debug) {
                printf("after ch=%c (%d), bitMask=%d\n", ch, freq, bitMask);
            }
        }

        return bitMask;
    }

    int updateBitMask(int crrBitMask, char updatedChar, int updatedFreq) {
        int updatedBitMask = crrBitMask;

        // updating nth bit of number: https://stackoverflow.com/a/47990/3679900
        if ((updatedFreq % 2) == 0) {
            updatedBitMask &= ~(1 << (updatedChar - SMALLEST_CHAR));
        } else {
            updatedBitMask |= 1 << (updatedChar - SMALLEST_CHAR);
        }

        return updatedBitMask;
    }

public:
    friend class SolutionTest;

    int findTheLongestSubstring(string s) {
        unordered_map<int, int> bitMaskFirstIdxMap;
        bitMaskFirstIdxMap[0] = -1;

        int maxSubstrLen = 0;

        unordered_map<char, int> vowelFreqMap;
        int crrBitMask = 0;
        for (int i = 0; i < s.size(); i++) {
            char ch = s.at(i);
            if (isVowel(ch)) {
                if (debug) {
                    printf("\n---------\n");
                    printf("at s[%d] = '%c'\n", i, ch);
                }

                int crrFreq = vowelFreqMap[ch - SMALLEST_CHAR];
                int updatedFreq = crrFreq + 1;
                vowelFreqMap[ch - SMALLEST_CHAR] = updatedFreq;

                if (debug) {
                    printf("prevFreq = %d, updatedFreq = %d\n", crrFreq, updatedFreq);
                }

                int updatedBitMask = updateBitMask(crrBitMask, ch, updatedFreq);
                if (debug) {
                    printf("prevBitMask = %d, updatedBitMask = %d\n", crrBitMask, updatedBitMask);
                }
                crrBitMask = updatedBitMask;
            }

            if (bitMaskFirstIdxMap.find(crrBitMask) == bitMaskFirstIdxMap.end()) {
                if (debug) {
                    printf("bitmask=%d never occurred before, so updating it's first occurrence at idx=%d\n",
                           crrBitMask, i);
                }
                bitMaskFirstIdxMap[crrBitMask] = i;
            } else {
                int crrSubstrLen = i - bitMaskFirstIdxMap[crrBitMask];
                maxSubstrLen = max(maxSubstrLen, crrSubstrLen);
                if (debug) {
                    printf("bitmask=%d previously occurred at idx=%d\n", crrBitMask, bitMaskFirstIdxMap[crrBitMask]);
                    printf("crrSubstrLen = %d, updated maxSubstrLen = %d\n", crrSubstrLen, maxSubstrLen);
                }
            }
        }

        return maxSubstrLen;
    }
};

class SolutionTest {
public:
    void testCreateBitMask() {
        Solution soln = Solution();
        unordered_map<char, int> freqMapIn;
        int bitMaskOutExpected, bitMaskOutComputed;

        freqMapIn = {};
        bitMaskOutExpected = 0;
        bitMaskOutComputed = soln.createBitMask(freqMapIn);
        assert(bitMaskOutExpected == bitMaskOutComputed);

//        soln.debug = true;
        freqMapIn = {{'a', 3}};
        bitMaskOutExpected = 1;
        bitMaskOutComputed = soln.createBitMask(freqMapIn);
        assert(bitMaskOutExpected == bitMaskOutComputed);
//        soln.debug = false;

        freqMapIn = {{'e', 5},
                     {'i', 2},
                     {'a', 1}};
        bitMaskOutExpected = 17;
        bitMaskOutComputed = soln.createBitMask(freqMapIn);
        assert(bitMaskOutExpected == bitMaskOutComputed);
    }

    void testUpdateBitMask() {
        Solution soln = Solution();
        int crrBitMaskIn;
        char updatedCharIn;
        int updatedFreqIn;
        int updatedBitMaskOutExpected, updatedBitMaskOutComputed;

        crrBitMaskIn = 0;
        updatedCharIn = 'i';
        updatedFreqIn = 7;
        updatedBitMaskOutExpected = 256;
        updatedBitMaskOutComputed = soln.updateBitMask(crrBitMaskIn, updatedCharIn, updatedFreqIn);
        assert(updatedBitMaskOutExpected == updatedBitMaskOutComputed);

        crrBitMaskIn = 256;
        updatedCharIn = 'e';
        updatedFreqIn = 8;
        updatedBitMaskOutExpected = 256;
        updatedBitMaskOutComputed = soln.updateBitMask(crrBitMaskIn, updatedCharIn, updatedFreqIn);
        assert(updatedBitMaskOutExpected == updatedBitMaskOutComputed);

        crrBitMaskIn = 256;
        updatedCharIn = 'a';
        updatedFreqIn = 3;
        updatedBitMaskOutExpected = 257;
        updatedBitMaskOutComputed = soln.updateBitMask(crrBitMaskIn, updatedCharIn, updatedFreqIn);
        assert(updatedBitMaskOutExpected == updatedBitMaskOutComputed);
    }

    void testFindTheLongestSubstring() {
        Solution soln = Solution();
        string strIn;
        int outExpected, outComputed;

//        soln.debug = true;
        strIn = "g";
        outExpected = 1;
        outComputed = soln.findTheLongestSubstring(strIn);
        assert(outExpected == outComputed);
//        soln.debug = false;

        strIn = "gm";
        outExpected = 2;
        outComputed = soln.findTheLongestSubstring(strIn);
        assert(outExpected == outComputed);

        strIn = "gmo";
        outExpected = 2;
        outComputed = soln.findTheLongestSubstring(strIn);
        assert(outExpected == outComputed);

        strIn = "gmop";
        outExpected = 2;
        outComputed = soln.findTheLongestSubstring(strIn);
        assert(outExpected == outComputed);

        strIn = "gmopo";
        outExpected = 5;
        outComputed = soln.findTheLongestSubstring(strIn);
        assert(outExpected == outComputed);

        strIn = "eleetminicoworoep";
        outExpected = 13;
        outComputed = soln.findTheLongestSubstring(strIn);
        assert(outExpected == outComputed);

        strIn = "leetcodeisgreat";
        outExpected = 5;
        outComputed = soln.findTheLongestSubstring(strIn);
        assert(outExpected == outComputed);

        strIn = "bcbcbc";
        outExpected = 6;
        outComputed = soln.findTheLongestSubstring(strIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCreateBitMask();
    solnTest.testUpdateBitMask();
    solnTest.testFindTheLongestSubstring();

    return 0;
}
