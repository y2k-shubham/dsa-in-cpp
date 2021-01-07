// LeetCode 3: https://leetcode.com/problems/longest-substring-without-repeating-characters/
// LC Jan 2021 challenge: https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/579/week-1-january-1st-january-7th/3595/
// GFG: https://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/
// InterviewBit: https://www.interviewbit.com/problems/longest-substring-without-repeat/

// 1st attempt was much much faster

#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
   public:
    int getMaxFreq(map<int, unordered_set<char> >& freqCharsMap) {
        if (freqCharsMap.empty()) {
            return 0;
        } else {
            return freqCharsMap.rbegin()->first;
        }
    }

    void addChar(
        unordered_map<char, int>& charFreqMap,
        map<int, unordered_set<char> >& freqCharsMap,
        char ch) {
        int crrFreq = charFreqMap[ch];
        freqCharsMap[crrFreq].erase(ch);
        if (freqCharsMap[crrFreq].empty()) {
            freqCharsMap.erase(crrFreq);
        }

        int newFreq = crrFreq + 1;
        charFreqMap[ch] = newFreq;
        freqCharsMap[newFreq].insert(ch);
    }

    void removeChar(
        unordered_map<char, int>& charFreqMap,
        map<int, unordered_set<char> >& freqCharsMap,
        char ch) {
        int crrFreq = charFreqMap[ch];
        freqCharsMap[crrFreq].erase(ch);
        if (freqCharsMap[crrFreq].empty()) {
            freqCharsMap.erase(crrFreq);
        }

        int newFreq = crrFreq - 1;
        if (newFreq > 0) {
            charFreqMap[ch] = newFreq;
            freqCharsMap[newFreq].insert(ch);
        } else {
            charFreqMap.erase(ch);
        }
    }

    int lengthOfLongestSubstring(string str) {
        int strLen = str.size();

        unordered_map<char, int> charFreqMap;
        map<int, unordered_set<char> > freqCharsMap;

        int i = 0;
        int j = -1;

        int maxReqWinLen = 0;
        bool someChange = true;
        while (someChange && (i <= (strLen - 1))) {
            someChange = false;
            if ((getMaxFreq(freqCharsMap) <= 1) && (j < (strLen - 1))) {
                j++;
                char addedChar = str.at(j);

                addChar(charFreqMap, freqCharsMap, addedChar);
                someChange = true;
            } else if (i < j) {
                char removedChar = str.at(i);
                i++;

                removeChar(charFreqMap, freqCharsMap, removedChar);
                someChange = true;
            }

            if (someChange) {
                int crrWinLen = j - i + 1;
                if (getMaxFreq(freqCharsMap) <= 1) {
                    maxReqWinLen = max(maxReqWinLen, crrWinLen);
                }
            }
        }

        return maxReqWinLen;
    }
};
