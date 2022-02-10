// LeetCode-2131: https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/

/**
 * ["lc","cl","gg"]
 * 6
 *
 * ["ab","ty","yt","lc","cl","ab"]
 * 8
 *
 * ["ab","cc","ty","cc","yt","lc","cl","ab","cc"]
 * 14
 *
 * ["cc","cc","cc"]
 * 6
 *
 * ["cc","ll","xx"]
 * 2
 *
 * ["dd","aa","bb","dd","aa","dd","bb","dd","aa","cc","bb","cc","dd","cc"]
 * 22
 */

#include <cassert>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
   private:
    bool isPalin(string& str) {
        return (str.at(0) == str.at(1));
    }

    string getRevWord(string str) {
        reverse(str.begin(), str.end());
        return str;
    }

    unordered_map<string, pair<int, bool>> buildFreqPalinMap(vector<string>& words) {
        unordered_map<string, pair<int, bool>> freqPalinMap;

        for (int i = 0; i < words.size(); i++) {
            string word = words[i];

            freqPalinMap[word].first++;

            if (isPalin(word)) {
                freqPalinMap[word].second = true;
            }
        }

        return freqPalinMap;
    }

    int getPairableFreq(unordered_map<string, pair<int, bool>>& freqPalinMap, string& word) {
        if (isPalin(word)) {
            int crrFreq = freqPalinMap[word].first;
            // only even no of palindromic words can be paired with each other
            // so if there are 4 or 5 'cc's in array, the pairable frequency in both cases will be 2
            return (crrFreq & (INT_MAX - 1)) / 2;
        } else {
            string revWord = getRevWord(word);

            if (freqPalinMap.find(revWord) == freqPalinMap.end()) {
                // reverse string not present
                return 0;
            } else {
                // reverse string present
                return min(freqPalinMap[word].first, freqPalinMap[revWord].first);
            }
        }
    }

    void decFreq(unordered_map<string, pair<int, bool>>& freqPalinMap, string& word, int deltaFreq) {
        freqPalinMap[word].first -= deltaFreq;
        if (freqPalinMap[word].first == 0) {
            freqPalinMap.erase(word);
        }
    }

   public:
    int longestPalindrome(vector<string>& wordVec) {
        unordered_map<string, pair<int, bool>> freqPalinMap = buildFreqPalinMap(wordVec);
        unordered_set<string> wordSet(wordVec.begin(), wordVec.end());

        int maxPalinLen = 0;

        // pick all pair-able words (having their reverse also available in words)
        for (
            unordered_set<string>::iterator it = wordSet.begin();
            it != wordSet.end();
            it++) {
            string word = *it;
            int pairableFreq = getPairableFreq(freqPalinMap, word);

            if (pairableFreq >= 1) {
                maxPalinLen += pairableFreq * 2 * 2;

                decFreq(freqPalinMap, word, pairableFreq);

                string revWord = getRevWord(word);
                decFreq(freqPalinMap, revWord, pairableFreq);
            }
        }

        // pick a single remaining palindromic word (if available)
        for (
            unordered_set<string>::iterator it = wordSet.begin();
            it != wordSet.end();
            it++) {
            string word = *it;
            if ((freqPalinMap[word].first >= 1) && freqPalinMap[word].second) {
                maxPalinLen += 2;
                break;
            }
        }

        return maxPalinLen;
    }
};
