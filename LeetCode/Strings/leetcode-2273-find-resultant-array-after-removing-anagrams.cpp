// LeetCode-2273: https://leetcode.com/problems/find-resultant-array-after-removing-anagrams/
// need not use stack; a more efficient, simple approach has been given in LC hints

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
private:
    int eatAnagrams(string likeWord, vector<string>& words, int iBegin) {
        int len = words.size();
        if (iBegin >= len) {
            return len;
        }

        for (int i = iBegin; i < len; i++) {
            string crrWord = words[i];
            if (likeWord.size() != crrWord.size()) {
                return i;
            }

            sort(crrWord.begin(), crrWord.end());
            if (likeWord != crrWord) {
                return i;
            }
        }

        return len;
    }

public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> reducedWords;

        int len = words.size();
        for (int i = 0; i < len;) {
            string crrHeadWord = words[i];
            reducedWords.push_back(crrHeadWord);

            sort(crrHeadWord.begin(), crrHeadWord.end());
            i = eatAnagrams(crrHeadWord, words, i + 1);
        }

        return reducedWords;
    }
};

