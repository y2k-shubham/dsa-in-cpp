// LeetCode-1839: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/
// incomplete (segfault)

#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

#define NUM_VOWELS 5

class Solution {
   private:
    bool isLongerThanMin(int lo, int hi) {
        int crrSubstrLen = hi - lo + 1;
        bool _isLongerThanMin = crrSubstrLen > NUM_VOWELS;
        return _isLongerThanMin;
    }

    bool hasAllVowels(vector<list<int> >& vowIdxs) {
        // check if all vowels present
        for (int i = 0; i < vowIdxs.size(); i++) {
            if (vowIdxs[i].empty()) {
                // vowel ('a' + i) missing
                return false;
            }
        }

        return true;
    }

    bool hasAllVowelsInOrder(vector<list<int> >& vowIdxs) {
        // check if all vowels appear in correct order
        for (int i = 1; i < vowIdxs.size(); i++) {
            if (vowIdxs[i - 1].empty() || vowIdxs[i].empty()) {
                return false;
            }
            if (*vowIdxs[i - 1].rbegin() > *vowIdxs[i].begin()) {
                return false;
            }
        }

        return true;
    }

    bool isBeautiful(vector<list<int> >& vowIdxs) {
        return /*hasAllVowels(vowIdxs) &&*/ hasAllVowelsInOrder(vowIdxs);
    }

    void includeChar(string& str, vector<list<int> >& vowIdxs, int& i) {
        i++;
        char chIn = str.at(i);
        vowIdxs[chIn - 'a'].push_back(i);
    }

    void excludeChar(string& str, vector<list<int> >& vowIdxs, int& i) {
        char chOut = str.at(i);
        vowIdxs[chOut - 'a'].pop_front();
        i++;
    }

   public:
    int longestBeautifulSubstring(string word) {
        int len = word.size();
        if (len < 5) {
            return false;
        }

        vector<list<int> > vowIdxs(NUM_VOWELS);

        int iLo = 0;
        int iHi = -1;
        // fill up till len 5 (since beautiful substring cant be shorter than that)
        while (iHi < NUM_VOWELS) {
            includeChar(word, vowIdxs, iHi);
        }

        int maxBeautSubstrLen = 0;
        while (iHi < (len - 1)) {
            int crrSubstrLen = iHi - iLo + 1;
            bool _isLongerThanMin = isLongerThanMin(iLo, iHi);
            bool _hasAllVowels = hasAllVowels(vowIdxs);
            bool _isBeautiful = isBeautiful(vowIdxs);
            bool _shouldShrink = _hasAllVowels && _isLongerThanMin && !_isBeautiful;

            if (_isBeautiful) {
                maxBeautSubstrLen = max(maxBeautSubstrLen, crrSubstrLen);
                includeChar(word, vowIdxs, iHi);
            } else if (_shouldShrink) {
                while (_shouldShrink) {
                    excludeChar(word, vowIdxs, iLo);

                    bool _isLongerThanMin = isLongerThanMin(iLo, iHi);
                    bool _hasAllVowels = hasAllVowels(vowIdxs);
                    bool _isBeautiful = isBeautiful(vowIdxs);
                    bool _shouldShrink = _hasAllVowels && _isLongerThanMin && !_isBeautiful;
                }
            } else {
                includeChar(word, vowIdxs, iHi);
            }
        }

        int crrSubstrLen = iHi - iLo + 1;
        bool _isLongerThanMin = isLongerThanMin(iLo, iHi);
        bool _hasAllVowels = hasAllVowels(vowIdxs);
        bool _isBeautiful = isBeautiful(vowIdxs);
        bool _shouldShrink = _hasAllVowels && _isLongerThanMin && !_isBeautiful;
        maxBeautSubstrLen = _isBeautiful ? max(maxBeautSubstrLen, crrSubstrLen) : maxBeautSubstrLen;
        if (_isBeautiful) {
            includeChar(word, vowIdxs, iHi);
            bool _isBeautiful = isBeautiful(vowIdxs);
            maxBeautSubstrLen = _isBeautiful ? max(maxBeautSubstrLen, crrSubstrLen) : maxBeautSubstrLen;
        }

        return maxBeautSubstrLen;
    }
};
