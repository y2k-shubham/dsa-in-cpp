// LeetCode-1347: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram/

#include <iostream>
#include <unordered_map>

using namespace std;

class Solution {
   private:
    unordered_map<char, int> buildFreqMap(string& str) {
        unordered_map<char, int> freqMap;

        for (int i = 0; i < str.size(); i++) {
            freqMap[str.at(i)]++;
        }

        return freqMap;
    }

    int countMissingChars(
        unordered_map<char, int>& sourceFreqMap,
        unordered_map<char, int>& targetFreqMap) {
        int count = 0;

        for (
            unordered_map<char, int>::iterator it = targetFreqMap.begin();
            it != targetFreqMap.end();
            it++) {
            int targetMapFreq = it->second;
            int sourceMapFreq = sourceFreqMap[it->first];

            if (targetMapFreq > sourceMapFreq) {
                count += targetMapFreq - sourceMapFreq;
            }
        }

        return count;
    }

   public:
    int minSteps(string s, string t) {
        unordered_map<char, int> sourceFreqMap = buildFreqMap(s);
        unordered_map<char, int> targetFreqMap = buildFreqMap(t);

        return countMissingChars(sourceFreqMap, targetFreqMap);
    }
};
