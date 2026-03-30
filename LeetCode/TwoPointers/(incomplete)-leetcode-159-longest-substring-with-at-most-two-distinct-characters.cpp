// LeetCode-159: https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/

// incomplete: wrong answer on multiple test-cases like following
/**
 * beceecba
 * beceeacba
 */

#include <string>
#include <unordered_map>

using namespace std;

#define MAX_ALLOWED_DISTINCT_CHARS 2

class Solution {
private:
    int expandWindowTillLessThan3DistinctChars(
        string& str,
        unordered_map<char, int>& charFreqMap,
        int startIdx) {
        if (charFreqMap.size() >= (MAX_ALLOWED_DISTINCT_CHARS + 1)) {
            return startIdx;
        }

        int i;
        for (
            i = startIdx;
            (i < str.size()) && (charFreqMap.size() <= MAX_ALLOWED_DISTINCT_CHARS);
            i++) {
            char ch = str.at(i);
            charFreqMap[ch]++;
        }

        return i;
    }

    int contractWindowTillMoreThan2DistinctChars(
        string& str,
        unordered_map<char, int>& charFreqMap,
        int startIdx) {
        if (charFreqMap.size() <= MAX_ALLOWED_DISTINCT_CHARS) {
            return startIdx;
        }

        int i;
        for (
            i = startIdx;
            charFreqMap.size() > MAX_ALLOWED_DISTINCT_CHARS;
            i++) {
            char ch = str.at(i);
            int crrFreq = charFreqMap[ch];

            if (crrFreq > 1) {
                charFreqMap[ch] = crrFreq - 1;
            } else {
                charFreqMap.erase(ch);
            }
        }

        return i;
    }

public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        int len = s.size();
        if (len <= MAX_ALLOWED_DISTINCT_CHARS) {
            return len;
        }

        unordered_map<char, int> charFreqMap;
        int maxWindowSize = MAX_ALLOWED_DISTINCT_CHARS;

        int iLo = 0;
        int iHi = 0;
        while (iHi < len) {
            bool noChange = true;

            // expand window
            int iHiNew = expandWindowTillLessThan3DistinctChars(s, charFreqMap, iHi);
            if (iHiNew != iHi) {
                int crrWindowSize = (iLo == 0) ? (iHiNew - 1) : (iHiNew - iLo);
                maxWindowSize = max(crrWindowSize, maxWindowSize);
                noChange = false;
            }
            iHi = iHiNew;

            // contract window
            int iLoNew = contractWindowTillMoreThan2DistinctChars(s, charFreqMap, iLo);
            if (iLoNew != iLo) {
                noChange = false;
            }
            iLo = iLoNew;

            if (noChange) {
                break;
            }
        }

        return maxWindowSize;
    }
};
