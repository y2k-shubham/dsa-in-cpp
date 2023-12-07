// LeetCode-1903: https://leetcode.com/problems/largest-odd-number-in-string/

#include <string>

using namespace std;

class Solution {
private:
    int getLastOddDigIdx(string& str) {
        for (int i = (str.length() - 1); i >= 0; i--) {
            int dig = str.at(i) - '0';
            if ((dig & 1) == 1) {
                return i;
            }
        }

        return -1;
    }

public:
    string largestOddNumber(string num) {
        int lastOddDigIdx = getLastOddDigIdx(num);
        if (lastOddDigIdx == -1) {
            return "";
        }

        return num.substr(0, lastOddDigIdx + 1);
    }
};
