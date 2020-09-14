// LeetCode-91: https://leetcode.com/problems/decode-ways/
// https://www.interviewbit.com/problems/ways-to-decode/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

#define MOD 1000000007;
using namespace std;

void testGetIntVal();
int getIntVal(string&, int, int);
int findNumDecodings(string);
int numDecodings(string);

int main() {
    testGetIntVal();

    return 0;
}

map<int, char> getNumCharMap() {
    map<int, char> numCharMap = {
        {1, 'A'},
        {2, 'B'},
        {3, 'C'},
        {4, 'D'},
        {5, 'E'},
        {6, 'F'},
        {7, 'G'},
        {8, 'H'},
        {9, 'I'},
        {10, 'J'},
        {11, 'K'},
        {12, 'L'},
        {13, 'M'},
        {14, 'N'},
        {15, 'O'},
        {16, 'P'},
        {17, 'Q'},
        {18, 'R'},
        {19, 'S'},
        {20, 'T'},
        {21, 'U'},
        {22, 'V'},
        {23, 'W'},
        {24, 'X'},
        {25, 'Y'},
        {26, 'Z'}};
    return numCharMap;
}

map<char, int> getCharNumMap() {
    map<char, int> charNumMap = {
        {'A', 1},
        {'B', 2},
        {'C', 3},
        {'D', 4},
        {'E', 5},
        {'F', 6},
        {'G', 7},
        {'H', 8},
        {'I', 9},
        {'J', 10},
        {'K', 11},
        {'L', 12},
        {'M', 13},
        {'N', 14},
        {'O', 15},
        {'P', 16},
        {'Q', 17},
        {'R', 18},
        {'S', 19},
        {'T', 20},
        {'U', 21},
        {'V', 22},
        {'W', 23},
        {'X', 24},
        {'Y', 25},
        {'Z', 26}};
    return charNumMap;
}

// top-down memoization, barely accepted
// LC runtime: 20ms (bottom 5%)
// LC memory: 16.8MB (bottom 5%)
// went OOM on InterviewBit
int calcWays(map<int, char>& numCharMap, string s, int ind, map<int, int>& indNumWaysMap) {
    int sLen = s.size();
    if (sLen == 0 || ind > sLen) {
        return 0;
    } else if (ind == sLen) {
        return 1;
    } else if (indNumWaysMap.find(ind) != indNumWaysMap.end()) {
        return indNumWaysMap[ind];
    } else {
        int ways = 0;
        char crrCh = s.at(ind);
        char nextCh;
        bool invalid = false;

        // single digit to char
        /**
         * note that string beginning with current digit can be invalid if the first digit itself is
         * invalid (only possible when first dig of current substring is zero)
         */
        if (numCharMap.find(crrCh - '0') != numCharMap.end()) {
            ways += calcWays(numCharMap, s, ind + 1, indNumWaysMap);
        } else {
            invalid = true;
        }

        /**
         * if current substring is invalid (begins with zero), we need not check two-char match
         */
        if (!invalid) {
            // two digits to char
            if (ind < sLen - 1) {
                string twoDigs = "";
                twoDigs = twoDigs + s.at(ind);
                twoDigs = twoDigs + s.at(ind + 1);
                int num = stoi(twoDigs);

                if (numCharMap.find(num) != numCharMap.end()) {
                    ways += calcWays(numCharMap, s, ind + 2, indNumWaysMap);
                }
            }
        }

        indNumWaysMap[ind] = ways;
        return ways;
    }
}

int findNumDecodings1(string s) {
    map<int, char> numCharMap = getNumCharMap();
    map<char, int> charNumMap = getCharNumMap();

    map<int, int> indNumWaysMap;
    return calcWays(numCharMap, s, 0, indNumWaysMap);
}

void testGetIntVal() {
    string str;

    str = "0";
    assert(getIntVal(str, 0, 0) == 0);

    str = "6";
    assert(getIntVal(str, 0, 0) == 6);

    str = "61";
    assert(getIntVal(str, 1, 1) == 1);

    str = "61";
    assert(getIntVal(str, 0, 1) == 61);

    str = "143";
    assert(getIntVal(str, 0, 2) == 143);

    str = "143";
    assert(getIntVal(str, 0, 1) == 14);

    str = "143";
    assert(getIntVal(str, 1, 2) == 43);
}

int getIntVal(string& str, int lo, int hi) {
    int intVal = 0;
    for (int i = lo; i <= hi; i++) {
        int crrDig = str.at(i) - '0';
        intVal = (intVal * 10) + crrDig;
    }
    return intVal;
}

void testFindNumDecodings2() {
    string str;

    str = "";
    assert(findNumDecodings2(str, false) == 1);

    str = "0";
    assert(findNumDecodings2(str, false) == 0);

    str = "01";
    assert(findNumDecodings2(str, false) == 0);

    str = "1";
    assert(findNumDecodings2(str, false) == 1);

    str = "10";
    assert(findNumDecodings2(str, false) == 1);

    str = "11";
    assert(findNumDecodings2(str, false) == 2);

    str = "110";
    assert(findNumDecodings2(str, false) == 1);

    str = "";
    assert(findNumDecodings2(str, false) == 1);
}

// accepted on LC with 100 %centile speed;
// InterviewBit is crooked (1) requires handling invalid input sequences, (2) requires ans modulo 10^9+7
// (both have been handled here)
int findNumDecodings2(string str, bool debug) {
    int len = str.size();
    if (len == 0) {
        return 1;
    }

    if (getIntVal(str, 0, 0) == 0) {
        return 0;
    }

    int prev2Ways = 1;
    int prev1Ways = 1;
    int crrWays = 1;
    for (int i = 1; i < len; i++) {
        int crr1Dig = getIntVal(str, i, i);
        int prev1Dig = getIntVal(str, i - 1, i - 1);

        if (crr1Dig == 0) {
            // if we see a zero, we have to assert whether or not we are seeing a valid encoding
            if (prev1Dig == 1 || prev1Dig == 2) {
                /**
                 * IMPORTANT: note that here we take prev2Ways instead of prev1Ways
                 * explaination: say we have ...110
                 *  - now when we were looking at 2nd 1, we took sum of 2 preceding values to get no of ways
                 *    (because both 1s in isolation can be AA or two ones together can be L)
                 *  - however interesting thing happens once we process that 0
                 *  - now the 2nd one is necessarily consumed by 0 into a 10 -> K
                 *  - and we can no longer take 11 -> A possibility that we took earlier
                 */
                crrWays = prev2Ways;
            } else {
                return 0;
            }
        } else {
            // otherwise encoding will always be valid (since any dig from 1 to 9 represent some char)
            crrWays = prev1Ways;
        }

        // but if last 2-digs taken together also form a valid char encoding,
        // then add that (crr - 2) count too
        int crr2Digs = getIntVal(str, i - 1, i);
        if ((11 <= crr2Digs && crr2Digs <= 26) && crr2Digs != 20) {
            crrWays += prev2Ways;
        }

        crrWays = crrWays % MOD;

        prev2Ways = prev1Ways;
        prev1Ways = crrWays;
    }

    return crrWays;
}

int numDecodings(string s) {
    return findNumDecodings2(s, false);
}
