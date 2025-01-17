// LeetCode-1419: https://leetcode.com/problems/minimum-number-of-frogs-croaking/
// goot question

/**
 * if the input string is "(croak)(cro(croak)(cro(croak)ak)ak)"
 * then the answer is 3 and not 4
 * - even though "(cro(croak)(cro(croak)ak)ak)" contains 4 croaks overlapping
 * - yet one "(croak)" finishes before other 2 overlapping with the 'containing' croak starts
 *   - hence we say at a time the max croaks were 3 only
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

#define FIRST_CROAK_CHAR 'c'
#define LAST_CROAK_CHAR 'k'
#define MAX_ALPHABET 'z'
#define NULL_CHAR '\0'

class Solution {
private:
    bool debug = false;
    int numCharsWithNonZeroFreq;
    vector <int> freqVec;
    vector <bool> croakChars;
    unordered_map <char, char> prevCroakChars;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

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
    friend class SolutionTest;

    int minNumberOfFrogs(string croakOfFrogs) {
        init();

        int maxFrogs = 0;
        int crrFrogs = 0;
        for (char ch : croakOfFrogs) {
            // if (!isCroakChar(ch)) {
            //     return -1;
            // }

            increaseFrequency(ch);
            if (!isValidFrequency(ch)) {
                return -1;
            }

            if (ch == FIRST_CROAK_CHAR) {
                ++crrFrogs;
                maxFrogs = max(maxFrogs, crrFrogs);
            }

            if (ch == LAST_CROAK_CHAR) {
                consumeCroak();
                --crrFrogs;

                // maxFrogs = max(maxFrogs, crrFrogs);

                // if (isEndingOfWindow()) {
                //     crrFrogs = 0;
                // }
            }
        }

        if (!isEndingOfWindow()) {
            return -1;
        }

        return maxFrogs;
    }
};

class SolutionTest {
public:
    void testMinNumberOfFrogs() {
        Solution soln = Solution();

        assert(soln.minNumberOfFrogs("croakcroak") == 1);
        assert(soln.minNumberOfFrogs("crcoakroak") == 2);
        assert(soln.minNumberOfFrogs("croakcrook") == -1);
        assert(soln.minNumberOfFrogs("croakcroa") == -1);
        // soln.enableDebug();
        assert(soln.minNumberOfFrogs("ccroroakcrcroacrokaoakkak") == 4);
        assert(soln.minNumberOfFrogs("croakcrcrocroakakocroakakcroakcroak") == 3);
        // soln.disableDebug();
    }
};

int main() {
    SolutionTest test = SolutionTest();

    test.testMinNumberOfFrogs();

    return 0;
}
