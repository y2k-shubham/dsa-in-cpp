// LeetCode-1419: https://leetcode.com/problems/minimum-number-of-frogs-croaking/
// wrong answer

/**
 * failing on this test case (could have more failing cases): "ccroroakcrcroacrokaoakkak"
 * expected answer = 4
 * calculated answer = 5
 */

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#define FIRST_CROAK_CHAR 'c'
#define LAST_CROAK_CHAR 'k'
#define MAX_ALPHABET 'z'
#define NULL_CHAR '\0'

class Solution {
private:
    int numCharsWithNonZeroFreq;
    vector <int> freqVec;
    vector <bool> croakChars;
    unordered_map <char, char> prevCroakChars;

    void init() {
        vector <bool> croakChars(MAX_ALPHABET + 1, false);
        croakChars['c'] = true;
        croakChars['r'] = true;
        croakChars['o'] = true;
        croakChars['a'] = true;
        croakChars['k'] = true;
        this->croakChars = croakChars;

        unordered_map <char, char> prevCroakChars;
        prevCroakChars['c'] = NULL_CHAR;
        prevCroakChars['r'] = 'c';
        prevCroakChars['o'] = 'r';
        prevCroakChars['a'] = 'o';
        prevCroakChars['k'] = 'a';
        this->prevCroakChars = prevCroakChars;

        vector <int> freqVec(MAX_ALPHABET + 1, 0);
        this->freqVec = freqVec;

        this->numCharsWithNonZeroFreq = 0;
    }

    bool isCroakChar(char ch) {
        return croakChars[ch];
    }

    bool isValidFrequency(char ch) {
        if (ch == FIRST_CROAK_CHAR) {
            return true;
        }

        int crrCharFreq = freqVec[ch];
        int prevCharFreq = freqVec[prevCroakChars[ch]];
        return prevCharFreq >= crrCharFreq;
    }

    int increaseFrequency(char ch) {
        if (freqVec[ch] == 0) {
            numCharsWithNonZeroFreq++;
        }

        freqVec[ch]++;
        return freqVec[ch];
    }

    int decreaseFrequency(char ch) {
        if (freqVec[ch] == 1) {
            numCharsWithNonZeroFreq--;
        }

        freqVec[ch]--;
        return freqVec[ch];
    }

    void consumeCroak() {
        decreaseFrequency('c');
        decreaseFrequency('r');
        decreaseFrequency('o');
        decreaseFrequency('a');
        decreaseFrequency('k');
    }

    bool isEndingOfWindow() {
        return numCharsWithNonZeroFreq == 0;
    }

public:
    int minNumberOfFrogs(string croakOfFrogs) {
        init();

        int maxFrogs = 0;
        int crrFrogs = 0;
        for (char ch : croakOfFrogs) {
            // if (!isCroakChar(ch)) {
            //     return -1;
            // }

            int freq = increaseFrequency(ch);
            if (!isValidFrequency(ch)) {
                return -1;
            }

            if (ch == LAST_CROAK_CHAR) {
                consumeCroak();

                ++crrFrogs;
                maxFrogs = max(maxFrogs, crrFrogs);

                if (isEndingOfWindow()) {
                    crrFrogs = 0;
                }
            }
        }

        return maxFrogs;
    }
};
