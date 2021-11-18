// LeetCode-1839: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/
// incomplete (segfault)

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

#define NUM_VOWELS 5

class Solution {
   private:
    int getVowIdx(char ch) {
        int idx = -1;
        switch (ch) {
            case 'a':
                idx = 0;
                break;

            case 'e':
                idx = 1;
                break;

            case 'i':
                idx = 2;
                break;

            case 'o':
                idx = 3;
                break;

            case 'u':
                idx = 4;
                break;

            default:
                break;
        }

        return idx;
    }

    bool isLongerThanMin(int lo, int hi) {
        int crrSubstrLen = hi - lo + 1;
        bool _isLongerThanMin = crrSubstrLen > NUM_VOWELS;
        return _isLongerThanMin;
    }

    bool hasAllVowels(vector<list<int> >& vowIdxs) {
        printf("hasAll-start\n");
        // check if all vowels present
        for (int i = 0; i < vowIdxs.size(); i++) {
            if (vowIdxs[i].empty()) {
                // vowel ('a' + i) missing
                printf("hasAll-end\n");
                return false;
            }
        }

        printf("hasAll-end\n");
        return true;
    }

    bool hasAllVowelsInOrder(vector<list<int> >& vowIdxs) {
        printf("inOrder-start\n");
        // check if all vowels appear in correct order
        for (int i = 1; i < vowIdxs.size(); i++) {
            if (vowIdxs[i - 1].empty() || vowIdxs[i].empty()) {
                printf("inOrder-end\n");
                return false;
            }
            if (*vowIdxs[i - 1].rbegin() > *vowIdxs[i].begin()) {
                printf("inOrder-end\n");
                return false;
            }
        }

        printf("inOrder-end\n");
        return true;
    }

    bool isBeautiful(vector<list<int> >& vowIdxs) {
        return /*hasAllVowels(vowIdxs) &&*/ hasAllVowelsInOrder(vowIdxs);
    }

    void includeChar(string& str, vector<list<int> >& vowIdxs, int& i) {
        i++;
        printf("including str.at(%d)\n", i);
        char chIn = str.at(i);
        vowIdxs[getVowIdx(chIn)].push_back(i);
    }

    void excludeChar(string& str, vector<list<int> >& vowIdxs, int& i) {
        char chOut = str.at(i);
        vowIdxs[getVowIdx(chOut)].pop_front();
        i++;
    }

   public:
    int longestBeautifulSubstring(string word) {
        int len = word.size();
        if (len < 5) {
            return false;
        }

        vector<list<int> > vowIdxs(NUM_VOWELS);

        printf("came here 1\n");

        int iLo = 0;
        int iHi = -1;
        // fill up till len 5 (since beautiful substring cant be shorter than that)
        do {
            includeChar(word, vowIdxs, iHi);
        } while (iHi < (NUM_VOWELS - 1));

        printf("came here 2\n");
        int maxBeautSubstrLen = 0;
        while (iHi < len) {
            int crrSubstrLen = iHi - iLo + 1;
            bool _isLongerThanMin = isLongerThanMin(iLo, iHi);
            bool _hasAllVowels = hasAllVowels(vowIdxs);
            bool _isBeautiful = isBeautiful(vowIdxs);
            bool _shouldShrink = (iHi == (len - 1)) || (_hasAllVowels && _isLongerThanMin && !_isBeautiful);

            if (_shouldShrink) {
                excludeChar(word, vowIdxs, iLo);
            } else {
                maxBeautSubstrLen = _isBeautiful ? max(maxBeautSubstrLen, crrSubstrLen) : maxBeautSubstrLen;
                includeChar(word, vowIdxs, iHi);
            }
        }

        return maxBeautSubstrLen;
    }
};

class SolutionTest {
   public:
    void testLongestBeautifulSubstring() {
        Solution soln = Solution();
        string word;
        int outExpected;
        int outComputed;

        // word = "";
        // outExpected = 0;
        // outComputed = soln.longestBeautifulSubstring(word);
        // assert(outExpected == outComputed);

        // word = "aeio";
        // outExpected = 0;
        // outComputed = soln.longestBeautifulSubstring(word);
        // assert(outExpected == outComputed);

        word = "aeiou";
        outExpected = 5;
        outComputed = soln.longestBeautifulSubstring(word);
        assert(outExpected == outComputed);

        // word = "aaaaaeeeeoouuuu";
        // outExpected = 0;
        // outComputed = soln.longestBeautifulSubstring(word);
        // assert(outExpected == outComputed);

        // word = "a";
        // outExpected = 0;
        // outComputed = soln.longestBeautifulSubstring(word);
        // assert(outExpected == outComputed);

        // word = "aeeeiiiioooauuuaeiou";
        // outExpected = 5;
        // outComputed = soln.longestBeautifulSubstring(word);
        // assert(outExpected == outComputed);

        // word = "aeiaaioaaaaeiiiiouuuooaauuaeiu";
        // outExpected = 0;
        // outComputed = soln.longestBeautifulSubstring(word);
        // assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testLongestBeautifulSubstring();

    return 0;
}
