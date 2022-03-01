// LeetCode-2182: https://leetcode.com/problems/construct-string-with-repeat-limit/

#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;

#define NULL_BYTE '\0'

class Solution {
   private:
    map<char, int> buildFreqMap(string& str) {
        map<char, int> freqMap;

        for (int i = 0; i < str.size(); i++) {
            freqMap[str.at(i)]++;
        }

        return freqMap;
    }

    pair<char, int> extractLargestChar(map<char, int>& freqMap, char skipChar, int limit) {
        if (freqMap.empty()) {
            return {NULL_BYTE, 0};
        }

        map<char, int>::reverse_iterator it = freqMap.rbegin();
        if (it->first == skipChar) {
          // largest character must be skipped;
          // so then we'll extract the 2nd largest char, but with freq = 1 only (greedy approach)
            it++;
            limit = 1;
        }
        if (it == freqMap.rend()) {
            return {NULL_BYTE, 0};
        }

        char largestChar = it->first;
        int largestCharFreq = it->second;

        int extractedFreq = min(limit, largestCharFreq);

        int updatedFreq = largestCharFreq - extractedFreq;
        if (updatedFreq == 0) {
            freqMap.erase(largestChar);
        } else {
            freqMap[largestChar] = updatedFreq;
        }

        return {largestChar, extractedFreq};
    }

   public:
    string repeatLimitedString(string s, int repeatLimit) {
        map<char, int> freqMap = buildFreqMap(s);

        ostringstream oss;
        char prevChar = NULL_BYTE;
        while (!freqMap.empty()) {
            pair<char, int> charFreqPair = extractLargestChar(freqMap, prevChar, repeatLimit);
            char crrChar = charFreqPair.first;
            int crrCharFreq = charFreqPair.second;

            if (crrChar == NULL_BYTE) {
                // no more characters to extract
                break;
            }

            oss << string(crrCharFreq, crrChar);
            prevChar = crrChar;
        }

        return oss.str();
    }
};
