// LeetCode-3227: https://leetcode.com/problems/vowels-game-in-a-string

/**
 * 1. if there are odd no of vowels in string, Alice will take them all in first move leaving nothing for Bob, thereby winning
 * 2. if there are even no of vowels in string, Alice will take up all but one, thereby leaving only 1 vowel for Bob, hence again winning
 * So Bob can only win if there are no vowels present in string
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    vector <bool> isVowel;

    void createIsVowelVector() {
        vector <bool> isVowel('z' + 1, false);
        isVowel['a'] = true;
        isVowel['e'] = true;
        isVowel['i'] = true;
        isVowel['o'] = true;
        isVowel['u'] = true;

        this->isVowel = isVowel;
    }

    bool hasVowels(string& str) {
        for (char ch: str) {
            if (isVowel[ch]) {
                return true;
            }
        }

        return false;
    }

public:
    bool doesAliceWin(string s) {
        if (s.empty()) {
            return false;
        }

        createIsVowelVector();
        return hasVowels(s);
    }
};
