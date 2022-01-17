// LeetCode-290: https://leetcode.com/problems/word-pattern/

#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Solution {
   private:
    pair<string, int> readNextWord(string& stmt, int crrPos) {
        ostringstream oss;

        for (; crrPos < stmt.size(); crrPos++) {
            char ch = stmt.at(crrPos);
            if (ch == ' ') {
                crrPos++;
                break;
            } else {
                oss << ch;
            }
        }

        return {oss.str(), crrPos};
    }

   public:
    bool wordPattern(string pattern, string s) {
        unordered_map<char, string> charWordMap;
        unordered_map<string, char> wordCharMap;

        int ptIdx = 0;
        int strIdx = 0;
        while ((ptIdx < pattern.size()) && (strIdx < s.size())) {
            char ch = pattern.at(ptIdx++);

            pair<string, int> nextWordResp = readNextWord(s, strIdx);
            string nextWord = nextWordResp.first;
            strIdx = nextWordResp.second;

            bool isNewChar = charWordMap.find(ch) == charWordMap.end();
            bool isNewWord = wordCharMap.find(nextWord) == wordCharMap.end();
            if (isNewChar && isNewWord) {
                charWordMap[ch] = nextWord;
                wordCharMap[nextWord] = ch;
            } else if (!isNewChar && !isNewWord) {
                if ((charWordMap[ch] != nextWord) || (wordCharMap[nextWord] != ch)) {
                    return false;
                }
            } else {
                return false;
            }
        }

        if (ptIdx < pattern.size()) {
            return false;
        }
        if (strIdx < s.size()) {
            return false;
        }

        return true;
    }
};
