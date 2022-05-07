// LeetCode-1297: https://leetcode.com/problems/maximum-number-of-occurrences-of-a-substring/
// straight-forward do-as-directed problem; should skip looking

#include <unordered_map>
#include <iostream>

using namespace std;

class Solution {
private:
    void countChar(unordered_map<char, int>& freqMap, char ch) {
        freqMap[ch]++;
    }

    void unCountChar(unordered_map<char, int>& freqMap, char ch) {
        freqMap[ch]--;
        if (freqMap[ch] == 0) {
            freqMap.erase(ch);
        }
    }

    int findMaxVal(unordered_map<string, int>& freqMap) {
        int maxVal = INT_MIN;

        for (auto it = freqMap.begin(); it != freqMap.end(); it++) {
            maxVal = max(maxVal, it->second);
        }

        return maxVal;
    }

    int findMaxOccurrence(string& str, int winSize, int maxUniqueChars) {
        int len = str.size();
        if (len < winSize) {
            return 0;
        }

        unordered_map<char, int> freqMap;
        unordered_map<string, int> substrFreqMap;

        // build window
        for (int i = 0; i < winSize; i++) {
            countChar(freqMap, str.at(i));
        }
        if (freqMap.size() <= maxUniqueChars) {
            substrFreqMap[str.substr(0, winSize)]++;
        }

        // move window
        for (int i = winSize; i < len; i++) {
            char outGoingChar = str.at(i - winSize);
            unCountChar(freqMap, outGoingChar);

            char inComingChar = str.at(i);
            countChar(freqMap, inComingChar);

            if (freqMap.size() <= maxUniqueChars) {
                substrFreqMap[str.substr(i - winSize + 1, winSize)]++;
            }
        }

        return findMaxVal(substrFreqMap);
    }

public:
    int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        int overallMaxOccurrence = INT_MIN;

        for (int i = minSize; i <= maxSize; i++) {
            overallMaxOccurrence = max(overallMaxOccurrence, findMaxOccurrence(s, i, maxLetters));
        }

        return max(0, overallMaxOccurrence);
    }
};

