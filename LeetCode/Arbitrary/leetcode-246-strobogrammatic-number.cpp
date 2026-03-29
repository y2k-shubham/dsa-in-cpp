// LeetCode-246: https://leetcode.com/problems/strobogrammatic-number

#include <string>
#include <vector>

using namespace std;

#define MAX_ALPHABET_CHAR 128

class Solution {
    vector<bool> symmetricDigits;
    vector<char> reflectionDigits;

private:
    void initSymmetricDigits() {
        symmetricDigits = vector<bool>(MAX_ALPHABET_CHAR, false);
        symmetricDigits[0] = true;
        symmetricDigits[1] = true;
        symmetricDigits[8] = true;
        symmetricDigits['0'] = true;
        symmetricDigits['1'] = true;
        symmetricDigits['8'] = true;
    }

    void initReflectionDigits() {
        reflectionDigits = vector<char>(MAX_ALPHABET_CHAR, -1);
        reflectionDigits[6] = 9;
        reflectionDigits[9] = 6;
        reflectionDigits['6'] = '9';
        reflectionDigits['9'] = '6';
    }

    void init() {
        initSymmetricDigits();
        initReflectionDigits();
    }

    bool areStrobogrammaticDigits(char digit1, char digit2) {
        if (digit1 == digit2) {
            return symmetricDigits[digit1];
        } else {
            return (reflectionDigits[digit1] == digit2);
        }
    }

    bool areStrobogrammaticDigits(int digit1, int digit2) {
        return areStrobogrammaticDigits((char)digit1, (char)digit2);
    }

public:
    bool isStrobogrammatic(string num) {
        init();

        int len = num.size();

        for (int i = 0; i <= (len / 2); i++) {
            char digit1 = num[i];
            char digit2 = num[len - 1 - i];

            if (!areStrobogrammaticDigits(digit1, digit2)) {
                return false;
            }
        }

        return true;
    }
};
