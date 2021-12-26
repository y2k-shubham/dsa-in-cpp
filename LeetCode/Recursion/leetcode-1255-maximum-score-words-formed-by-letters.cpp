// LeetCode-1255: https://leetcode.com/problems/maximum-score-words-formed-by-letters/
// simple backtracking soln; LC speed %tile = 70

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

#define NUM_ALPHAS 26

class Solution {
   private:
    vector<int> buildFreqVec(string word) {
        vector<int> freqVec(NUM_ALPHAS, 0);
        for (int i = 0; i < word.size(); i++) {
            freqVec[word.at(i) - 'a']++;
        }

        return freqVec;
    }

    vector<int> buildFreqVec(vector<char>& letters) {
        vector<int> freqVec(NUM_ALPHAS, 0);
        for (int i = 0; i < letters.size(); i++) {
            freqVec[letters[i] - 'a']++;
        }

        return freqVec;
    }

    unordered_map<string, vector<int> > buildWordCharFreqMap(vector<string>& words) {
        unordered_map<string, vector<int> > wordCharFreqMap;
        for (int i = 0; i < words.size(); i++) {
            wordCharFreqMap[words[i]] = buildFreqVec(words[i]);
        }

        return wordCharFreqMap;
    }

    int findScore(vector<int>& alphaScores, string word) {
        int score = 0;

        for (int i = 0; i < word.size(); i++) {
            score += alphaScores[word.at(i) - 'a'];
        }

        return score;
    }

    unordered_map<string, int> buildWordScoreMap(vector<string>& words, vector<int>& alphaScores) {
        unordered_map<string, int> wordScoreMap;
        for (int i = 0; i < words.size(); i++) {
            wordScoreMap[words[i]] = findScore(alphaScores, words[i]);
        }

        return wordScoreMap;
    }

    bool canFormWord(vector<int>& availChars, vector<int>& reqChars) {
        for (int i = 0; i < reqChars.size(); i++) {
            if (availChars[i] < reqChars[i]) {
                return false;
            }
        }

        return true;
    }

    void useCharsFormWord(vector<int>& availChars, vector<int>& reqChars) {
        for (int i = 0; i < reqChars.size(); i++) {
            availChars[i] -= reqChars[i];
        }
    }

    void returnCharsUnformWord(vector<int>& availChars, vector<int>& reqChars) {
        for (int i = 0; i < reqChars.size(); i++) {
            availChars[i] += reqChars[i];
        }
    }

    int findMaxScore(
        vector<int>& availCharFreqs,
        vector<string>& words,
        unordered_map<string, vector<int> >& wordCharFreqMap,
        unordered_map<string, int>& wordScoreMap,
        int idx) {
        if (idx >= words.size()) {
            return 0;
        }

        string crrWord = words[idx];
        vector<int> crrWordCharFreqs = wordCharFreqMap[crrWord];
        int crrWordScore = wordScoreMap[crrWord];

        int scoreWithCrrWord = 0;
        if (canFormWord(availCharFreqs, crrWordCharFreqs)) {
            useCharsFormWord(availCharFreqs, crrWordCharFreqs);
            scoreWithCrrWord = crrWordScore + findMaxScore(availCharFreqs, words, wordCharFreqMap, wordScoreMap, idx + 1);
            returnCharsUnformWord(availCharFreqs, crrWordCharFreqs);
        }

        int scoreWithoutCrrWord = findMaxScore(availCharFreqs, words, wordCharFreqMap, wordScoreMap, idx + 1);

        return max(scoreWithCrrWord, scoreWithoutCrrWord);
    }

   public:
    int maxScoreWords(vector<string>& words, vector<char>& letters, vector<int>& score) {
        vector<int> availCharFreqs = buildFreqVec(letters);
        unordered_map<string, vector<int> > wordCharFreqMap = buildWordCharFreqMap(words);
        unordered_map<string, int> wordScoreMap = buildWordScoreMap(words, score);

        return findMaxScore(availCharFreqs, words, wordCharFreqMap, wordScoreMap, 0);
    }
};
