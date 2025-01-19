// LeetCode-415: https://leetcode.com/problems/add-strings/
// takes more time to implement than one would initially think

#include <string>
#include <vector>
#include <list>
#include <sstream>

using namespace std;

#define ZERO_CHAR '0'
#define ZERO_STR "0"

class Solution {
private:
    vector <int> convertStrOfDigToVecOfDig(string& num, int reqLen) {
        int len = num.size();
        vector <int> vecOfDig(reqLen);

        for (int i = 0; i < len; i++) {
            char digitChar = num.at(i);
            int digitInt = digitChar - ZERO_CHAR;
            vecOfDig[i] = digitInt;
        }

        for (int i = len; i < reqLen; i++) {
            vecOfDig[i] = 0;
        }

        return vecOfDig;
    }

    vector <int> add(vector <int>& num1, vector <int>& num2) {
        int len = num1.size();
        vector <int> numSum(len + 1);

        int carry = 0;
        for (int i = 0; i < len; i++) {
            int dig1 = num1[i];
            int dig2 = num2[i];

            int sum = dig1 + dig2 + carry;

            int quot = sum % 10;
            carry = sum / 10;

            numSum[i] = quot;
        }

        numSum[len] = carry;

        return numSum;
    }

    string convertVecOfDigToStrOfDig(vector <int>& vecOfDig) {
        int len = vecOfDig.size();
        ostringstream oss;

        bool haveSeenNonZeroDigs = false;
        for (int i = len - 1; i >= 0; i--) {
            int digInt = vecOfDig[i];
            if (digInt == 0) {
                if (!haveSeenNonZeroDigs) {
                    continue;
                }
            } else {
                haveSeenNonZeroDigs = true;
            }

            char digChar = (char)(digInt + ZERO_CHAR);
            oss << digChar;
        }

        return oss.str();
    }

public:
    string addStrings(string num1, string num2) {
        if (num1 == ZERO_STR) {
            return num2;
        }
        if (num2 == ZERO_STR) {
            return num1;
        }

        int len1 = num1.size();
        int len2 = num2.size();
        int lenMax = max(len1, len2);

        string num1Rev = num1;
        reverse(num1Rev.begin(), num1Rev.end());

        string num2Rev = num2;
        reverse(num2Rev.begin(), num2Rev.end());

        vector <int> num1Vec = convertStrOfDigToVecOfDig(num1Rev, lenMax);
        vector <int> num2Vec = convertStrOfDigToVecOfDig(num2Rev, lenMax);

        vector <int> numSumVec = add(num1Vec, num2Vec);
        string numSumStr = convertVecOfDigToStrOfDig(numSumVec);

        return numSumStr;
    }
};
