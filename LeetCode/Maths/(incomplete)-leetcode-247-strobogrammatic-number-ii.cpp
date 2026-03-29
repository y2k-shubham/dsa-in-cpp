// LeetCode-247: https://leetcode.com/problems/strobogrammatic-number-ii
// incomplete: answer seems correct but is outputting duplicates beyond n=9

#include <vector>
#include <utility>

using namespace std;

#define NULL_CHAR '\0'
#define BEGIN_DIGIT '0'

class Solution {
    bool debug = false;
    vector<int> symmetricDigits;
    vector<pair <int, int>> reflectionDigits;
    vector<string> strobogrammaticNums;

private:
    // ------- initialization helper functions / methods --------

    void initReflectionDigits() {
        reflectionDigits.push_back({0, 0});
        reflectionDigits.push_back({1, 1});
        reflectionDigits.push_back({6, 9});
        reflectionDigits.push_back({8, 8});
        reflectionDigits.push_back({9, 6});
    }

    void initSymmetricDigits() {
        symmetricDigits.push_back(0);
        symmetricDigits.push_back(1);
        symmetricDigits.push_back(8);
    }

    void init() {
        initReflectionDigits();
        initSymmetricDigits();
        strobogrammaticNums.clear();
    }

    // ------- sringifying helper functions / methods --------

    char convertToChar(int num) {
        return (char) (num + BEGIN_DIGIT);
    }

    string convertToStr(vector<char>& digits) {
        string str(digits.begin(), digits.end());
        return str;
    }

    void storeCurrentNum(vector<char>& digits) {
        strobogrammaticNums.push_back(convertToStr(digits));
    }

    // ------- recursion / backtracking core logic --------

    void genStrobogrammaticNumsRec(vector<char>& digits, int idx) {
        int len = digits.size();
        int halfLen = len / 2;

        if (idx > halfLen) {
            storeCurrentNum(digits);
            return;
        }

        // for odd-length 'n', center-most digit can only be symmetric
        bool isOddLen = (len & 1) == 1;
        if (isOddLen && (idx == halfLen)) {
            for (int digit : symmetricDigits) {
                digits[idx] = convertToChar(digit);
                storeCurrentNum(digits);
            }

            return;
        }

        // for any other digit position, we can place any digit, as long as its reflection is valid
        // (except for first digit which can't be zero)
        int iLo = (idx == 0) ? 1 : 0;
        for (int i = iLo; i < reflectionDigits.size(); i++) {
            pair<int, int> reflectionDigitPair = reflectionDigits[i];
            char ch = convertToChar(reflectionDigitPair.first);
            char chReflected = convertToChar(reflectionDigitPair.second);

            digits[idx] = ch;
            digits[len - idx - 1] = chReflected;

            if ((idx + 1) > halfLen) {
                storeCurrentNum(digits);
            } else {
                genStrobogrammaticNumsRec(digits, idx + 1);
            }
        }
    }

public:
    vector<string> findStrobogrammatic(int n) {
        if (n == 0) {
            return {};
        }
        if (n == 1) {
            return {"0", "1", "8"};
        }
        if (n == 2) {
            return {"11", "69", "88", "96"};
        }

        init();

        vector<char> digits(n, NULL_CHAR);
        genStrobogrammaticNumsRec(digits, 0);

        return strobogrammaticNums;
    }
};
