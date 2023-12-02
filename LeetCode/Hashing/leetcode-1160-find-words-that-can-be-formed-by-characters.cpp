// LeetCode-1160: https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/
// dump problem; dont bother looking


#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

#define NUM_ALPHABETS 26
#define FIRST_ALPHABET 'a'

class Solution {
private:
    // ---------- map based solution; LC runtime ~ 160ms ----------
    inline unordered_map<char, int> buildCharFreqMap(string& chars) {
        unordered_map<char, int> charFreqMap;
        for (char ch: chars) {
            charFreqMap[ch]++;
        }
        return charFreqMap;
    }

    inline bool canFormWord(unordered_map<char, int>& availableCharFreqs, unordered_map<char, int>& requiredCharFreqs) {
        for (auto it: requiredCharFreqs) {
            if (availableCharFreqs[it.first] < it.second) {
                return false;
            }
        }

        return true;
    }

    int countCharactersUsingMap(vector<string>& words, string chars) {
        unordered_map<char, int> availableCharFreqs = buildCharFreqMap(chars);

        int totalLengthOfGoodWords = 0;
        for (string& word: words) {
            unordered_map<char, int> requiredCharFreqs = buildCharFreqMap(word);
            if (canFormWord(availableCharFreqs, requiredCharFreqs)) {
                totalLengthOfGoodWords += word.length();
            }
        }

        return totalLengthOfGoodWords;
    }

    // ---------- vector based solution; LC runtime ~ 50ms ----------

    inline vector<int> buildCharFreqVec(string& chars) {
        vector<int> charFreqVec(NUM_ALPHABETS, 0);
        for (char ch: chars) {
            charFreqVec[ch - FIRST_ALPHABET]++;
        }

        return charFreqVec;
    }

    inline bool canFormWord(vector<int>& availableCharFreqs, vector<int>& requiredCharFreqs) {
        for (int i = 0; i < NUM_ALPHABETS; i++) {
            if (availableCharFreqs[i] < requiredCharFreqs[i]) {
                return false;
            }
        }

        return true;
    }

    int countCharactersUsingVector(vector<string>& words, string chars) {
        vector<int> availableCharFreqsVec = buildCharFreqVec(chars);

        int totalLengthOfGoodWords = 0;
        for (string& word: words) {
            vector<int> requiredCharFreqsVec = buildCharFreqVec(word);
            if (canFormWord(availableCharFreqsVec, requiredCharFreqsVec)) {
                totalLengthOfGoodWords += word.length();
            }
        }

        return totalLengthOfGoodWords;
    }

public:

    int countCharacters(vector<string>& words, string chars) {
        // return countCharactersUsingMap(words, chars);
        return countCharactersUsingVector(words, chars);
    }
};
