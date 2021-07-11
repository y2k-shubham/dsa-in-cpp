// LeetCode-639: https://leetcode.com/problems/decode-ways-ii/

#include <cstdio>
#include <iostream>

using namespace std;

#define MOD 1000000007

class Solution {
   private:
    int getNumWays1Char(char ch) {
        switch (ch) {
            case '*':
                return 9;
                break;

            case '0':
                return 0;
                break;

            default:
                return 1;
                break;
        }
    }

    int getNumWays2Chars(string str) {
        char ch1 = str.at(0);
        char ch2 = str.at(1);

        if (ch1 != '*' && ch2 != '*') {
            if (ch1 == '0') {
                // 0 followed by another digit (NOT *)
                return 0;
            } else if (ch1 == '1') {
                // 1 followed by another digit (NOT *)
                return 1;
            } else if (ch1 == '2') {
                // 2 followed by another digit (NOT *)
                if ('0' <= ch2 && ch2 <= '6') {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                // any other number followed by another digit (NOT *)
                return 0;
            }
        } else if (ch1 == '*' && ch2 == '*') {
            // everything from 11, 12 .. 19 & 21, 22 .. 26 can be formed
            return 15;
        } else if (ch2 == '*') {
            if (ch1 == '0') {
                return 0;
            } else if (ch1 == '1') {
                return 9;
            } else if (ch1 == '2') {
                return 6;
            } else {
                return 0;
            }
        } else {
            // ch1 = *, ch2 != *
            if ('0' <= ch2 && ch2 <= '6') {
                return 2;
            } else {
                return 1;
            }
        }
    }

   public:
    int numDecodings(string str) {
        int len = str.size();
        if (len == 0) {
            return 1;
        }
        if (len == 1) {
            return getNumWays1Char(str.at(0));
        }

        long long int prev2 = 1;
        long long int prev1 = 1;

        for (int i = 0; i < len; i++) {
            long long int oneDigWays = (prev1 * getNumWays1Char(str.at(i))) % MOD;

            long long int twoDigWays = 0;
            if (i >= 1) {
                string twoChars = str.substr(i - 1, 2);
                twoDigWays = (prev2 * getNumWays2Chars(twoChars)) % MOD;
                // printf("i=%d, ch=%c, prev1=%d, oneDigWays=%d, twoChars=%s, prev2=%d, twoDigWays=%d\n", i, str.at(i), prev1, oneDigWays, twoChars.c_str(), prev2, twoDigWays);
            }

            long long int crr = (oneDigWays + twoDigWays) % MOD;

            prev2 = prev1;
            prev1 = crr;
        }

        return (int)prev1;
    }
};
