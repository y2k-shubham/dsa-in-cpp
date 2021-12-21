// LeetCode-2085: https://leetcode.com/problems/count-common-words-with-one-occurrence/
// extremely dumb problem; do NOT look (complete waste of time)

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    unordered_map<string, int> buildFreqMap(vector<string>& words) {
        unordered_map<string, int> freqMap;
        for (int i = 0; i < words.size(); i++) {
            freqMap[words[i]]++;
        }

        return freqMap;
    }

    int countSingleFreqWords(unordered_map<string, int>& freqMap1, unordered_map<string, int>& freqMap2) {
        int numSingleFreqWords = 0;

        for (unordered_map<string, int>::iterator it = freqMap1.begin(); it != freqMap2.end(); it++) {
            if ((it->second == 1) && (freqMap2.find(it->first) != freqMap2.end()) && (freqMap2[it->first] == 1)) {
                numSingleFreqWords++;
            }
        }

        return numSingleFreqWords;
    }

   public:
    int countWords(vector<string>& words1, vector<string>& words2) {
        unordered_map<string, int> freqMap1 = buildFreqMap(words1);
        unordered_map<string, int> freqMap2 = buildFreqMap(words2);

        return countSingleFreqWords(freqMap1, freqMap2);
    }
};
