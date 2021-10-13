// wrong, incomplete
// GFG: https://www.geeksforgeeks.org/smallest-substring-with-each-letter-occurring-both-in-uppercase-and-lowercase/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>

using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

map<char, pair<int, int> > createCharCaseMap() {
    map<char, pair<int, int> > charCaseMap;

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        charCaseMap[(int)ch] = {0, 0};
    }

    return charCaseMap;
}

void showMap(map<char, pair<int, int> >& charCaseMap) {
    for (int ch = 'A'; ch <= 'Z'; ch++) {
        if (max(charCaseMap[ch].first, charCaseMap[ch].second) > 0) {
            printf("%c : %c=%d, %c=%d\n", ch, (ch + 32), charCaseMap[ch].first, ch, charCaseMap[ch].second);
        }
    }
}

int solution(string& S) {
    bool debug = true;
    int len = S.size();
    if (len == 1) {
        return -1;
    }

    map<char, pair<int, int> > charCaseMap = createCharCaseMap();
    int numImbalance = 0;
    int minBalancedLen = 0;

    int iLo = 0;
    int iHi = -1;
    while (max(iLo, iHi) < len) {
        // expand window while imbalanced
        while ((iHi < len) && ((numImbalance > 0) || (iLo >= iHi))) {
            iHi++;

            char ch = S.at(iHi);
            char chUpper = (((int)ch) <= 91) ? ch : (ch - 32);
            bool isChUpper = ch == chUpper;

            bool bothCasesPresentBefore = min(charCaseMap[chUpper].first, charCaseMap[chUpper].second) > 0;
            bool noCasesPresentBefore = max(charCaseMap[chUpper].first, charCaseMap[chUpper].second) == 0;
            bool isBalancedBefore = bothCasesPresentBefore || noCasesPresentBefore;

            if (isChUpper) {
                charCaseMap[chUpper].second++;
            } else {
                charCaseMap[chUpper].first++;
            }

            bool bothCasesPresentAfter = min(charCaseMap[chUpper].first, charCaseMap[chUpper].second) > 0;
            bool noCasesPresentAfter = max(charCaseMap[chUpper].first, charCaseMap[chUpper].second) == 0;
            bool isBalancedAfter = bothCasesPresentAfter || noCasesPresentAfter;

            if (!isBalancedBefore && isBalancedAfter) {
                numImbalance--;
            }
            if (numImbalance == 0) {
                int crrWinLen = iHi - iLo + 1;
                minBalancedLen = min(minBalancedLen, crrWinLen);
            }

            if (debug) {
                printf("L1: s[iLo=%d]=%c .. s[iHi=%d]=%c\n", iLo, S.at(iLo), iHi, S.at(iHi));
                showMap(charCaseMap);
            }
        }

        // shrink window while balanced
        while ((iLo <= iHi) && (numImbalance > 0)) {
            char ch = S.at(iLo);
            char chUpper = (((int)ch) <= 91) ? ch : (ch - 32);
            bool isChUpper = ch == chUpper;

            bool bothCasesPresentBefore = min(charCaseMap[chUpper].first, charCaseMap[chUpper].second) > 0;
            bool noCasesPresentBefore = max(charCaseMap[chUpper].first, charCaseMap[chUpper].second) == 0;
            bool isBalancedBefore = bothCasesPresentBefore || noCasesPresentBefore;

            if (isChUpper) {
                charCaseMap[chUpper].second--;
            } else {
                charCaseMap[chUpper].first--;
            }

            bool bothCasesPresentAfter = min(charCaseMap[chUpper].first, charCaseMap[chUpper].second) > 0;
            bool noCasesPresentAfter = max(charCaseMap[chUpper].first, charCaseMap[chUpper].second) == 0;
            bool isBalancedAfter = bothCasesPresentAfter || noCasesPresentAfter;

            if (debug) {
                printf("L2: s[iLo=%d]=%c .. s[iHi=%d]=%c\n", iLo, S.at(iLo), iHi, S.at(iHi));
                showMap(charCaseMap);
            }

            iLo++;

            if (isBalancedBefore && !isBalancedAfter) {
                numImbalance++;
            } else if (isBalancedAfter) {
                int crrWinLen = iHi - iLo + 1;
                minBalancedLen = min(minBalancedLen, crrWinLen);
            }
        }
    }

    if (minBalancedLen > 0) {
        return minBalancedLen;
    } else {
        return -1;
    }
}

void solutionTest() {
    string strIn;
    int lenOutExpected, lenOutComputed;

    // strIn = "a";
    // lenOutExpected = -1;
    // lenOutComputed = solution(strIn);
    // assert(lenOutExpected == lenOutComputed);

    strIn = "azABaabza";
    lenOutExpected = 5;
    lenOutComputed = solution(strIn);
    cout << lenOutComputed << endl;
    assert(lenOutExpected == lenOutComputed);
}

int main() {
    solutionTest();
    return 0;
}
