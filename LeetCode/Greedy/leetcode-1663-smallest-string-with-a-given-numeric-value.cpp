// LeetCode-1663: https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/

#include <iostream>
#include <sstream>

using namespace std;

#define BEGIN_CHAR 'a'
#define BEGING_CHAR_SCORE 1
#define END_CHAR 'z'
#define END_CHAR_SCORE 26
#define NUM_CHARS 26

class Solution {
   private:
    int getCharScore(char ch) {
        return ch - BEGIN_CHAR + 1;
    }

    bool canPutChar(char ch, int numRemChars, int remScore) {
        if (numRemChars == 0) {
            return false;
        }
        if (numRemChars == 1) {
            return ch == ((char)(BEGIN_CHAR + (remScore - 1)));
        }

        int crrCharScore = getCharScore(ch);
        int residualScore = remScore - crrCharScore;
        int residualChars = numRemChars - 1;

        float reqAvgScorePerChar = ((float)residualScore) / residualChars;
        if (reqAvgScorePerChar > END_CHAR_SCORE) {
            return false;
        }

        return true;
    }

    char findSmallestCharToPut(int numRemChars, int remScore) {
        for (char ch = BEGIN_CHAR; ch <= END_CHAR; ch++) {
            if (canPutChar(ch, numRemChars, remScore)) {
                return ch;
            }
        }

        // this can never happen (unless input is wrong)
        return '\0';
    }

   public:
   // barely accepted; speed 5 %tile
    string getSmallestString(int n, int k) {
        ostringstream oss;

        int numRemChars = n;
        int remScore = k;
        while (numRemChars > 0) {
            char ch = findSmallestCharToPut(numRemChars, remScore);

            numRemChars--;
            remScore -= getCharScore(ch);

            oss << ch;
        }

        return oss.str();
    }
};
