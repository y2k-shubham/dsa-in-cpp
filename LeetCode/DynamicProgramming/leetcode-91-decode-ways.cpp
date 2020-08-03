// https://leetcode.com/problems/decode-ways/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

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
// runtime: 20ms (bottom 5%)
// memory: 16.8MB (bottom 5%)
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

int numDecodings(string s) {
    map<int, char> numCharMap = getNumCharMap();
    map<char, int> charNumMap = getCharNumMap();

    map<int, int> indNumWaysMap;
    return calcWays(numCharMap, s, 0, indNumWaysMap);
}
