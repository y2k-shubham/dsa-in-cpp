// LeetCode-890: https://leetcode.com/problems/find-and-replace-pattern/submissions/
// LC May 2021 challenge: https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/600/week-3-may-15th-may-21st/3750/

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    vector<int> reduceWordChars(string word) {
        int len = word.size();

        vector<int> intWordCode(len);
        unordered_map<char, int> charIntMap;

        int crrInt = 1;
        for (int i = 0; i < len; i++) {
            char ch = word.at(i);
            if (charIntMap.find(ch) == charIntMap.end()) {
                charIntMap[ch] = crrInt;
                crrInt++;
            }

            intWordCode[i] = charIntMap[ch];
        }

        return intWordCode;
    }

   public:
    vector<string> findAndReplacePattern(vector<string>& words, string pattern) {
        vector<int> patternCode = reduceWordChars(pattern);

        vector<string> matchingWords;
        for (int i = 0; i < words.size(); i++) {
            vector<int> wordCode = reduceWordChars(words[i]);
            if (patternCode == wordCode) {
                matchingWords.push_back(words[i]);
            }
        }

        return matchingWords;
    }
};