// LeetCode-3136: https://leetcode.com/problems/valid-word/

#include <string>
#include <unordered_set>

using namespace std;

class Solution {
private:
    unordered_set <char> vowels;

    void init() {
        vowels = {
            'a',
            'e',
            'i',
            'o',
            'u',
            // 'A',
            // 'E',
            // 'I',
            // 'O',
            // 'U'
        };
    }

    bool isAlphabet(char ch) {
        bool isLowerCaseAlphabet = ('a' <= ch) && (ch <= 'z');
        return isLowerCaseAlphabet || isUpperCaseAlphabet(ch);
    }

    bool isUpperCaseAlphabet(char ch) {
        return ('A' <= ch) && (ch <= 'Z');
    }

    bool isVowel(char ch) {
        return (vowels.count(tolower(ch)) > 0);
    }

    bool isConsonant(char ch) {
        return isAlphabet(ch) && !isVowel(ch);
    }

    bool isDigit(char ch) {
        return ('0' <= ch) && (ch <= '9');
    }

    bool isValidChar(char ch) {
        return isDigit(ch) || isAlphabet(ch);
    }

public:
    bool isValid(string word) {
        init();

        if (word.size() < 3) {
            return false;
        }

        bool hasVowel = false;
        bool hasConsonant = false;

        for (char ch : word) {
            if (!isValidChar(ch)) {
                return false;
            }

            if (isDigit(ch)) {
                continue;
            }

            if (isVowel(ch)) {
                hasVowel = true;
            } else if (isConsonant(ch)) {
                hasConsonant = true;
            }
        }

        return hasVowel && hasConsonant;
    }
};
