// wrong, incomplete
// GFG: https://www.geeksforgeeks.org/smallest-substring-with-each-letter-occurring-both-in-uppercase-and-lowercase/

#include <cassert>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

using namespace std;

void updateCharFreq(
    unordered_map<char, pair<int, int> >& charFreqMap,
    unordered_set<char>& imbCharSet,
    char ch,
    bool include) {
    bool isLower = islower(ch);
    char chLower = (char)tolower(ch);

    if (include) {
        if (isLower) {
            charFreqMap[chLower].first++;
        } else {
            charFreqMap[chLower].second++;
        }
    } else {
        if (isLower) {
            charFreqMap[chLower].first--;
        } else {
            charFreqMap[chLower].second--;
        }
    }

    bool hasBothCases = (charFreqMap[chLower].first > 0) && (charFreqMap[chLower].second > 0);
    bool hasNoCases = (charFreqMap[chLower].first == 0) && (charFreqMap[chLower].second == 0);

    if (hasBothCases || hasNoCases) {
        imbCharSet.erase(chLower);
    } else {
        imbCharSet.insert(chLower);
    }
}

void showDebugInfo(
    unordered_map<char, pair<int, int> >& charFreqMap,
    unordered_set<char>& imbCharSet) {
    printf("charFreqMap is:-\n");
    for (unordered_map<char, pair<int, int> >::iterator it = charFreqMap.begin(); it != charFreqMap.end(); it++) {
        printf("%c -> [%c]=%d, [%c]=%d\n", it->first, it->first, it->second.first, toupper(it->first), it->second.second);
    }

    printf("imbCharSet is:-\n");
    for (unordered_set<char>::iterator it = imbCharSet.begin(); it != imbCharSet.end(); it++) {
        printf("%c ", *it);
    }
    cout << endl;
}

int findMinWindow(string str, bool debug) {
    int len = str.size();
    if (len <= 1) {
        return -1;
    }

    unordered_map<char, pair<int, int> > charFreqMap;
    unordered_set<char> imbCharSet;

    int minWinLen = INT_MAX;
    int minWinLo = -1;
    int minWinHi = -1;
    updateCharFreq(charFreqMap, imbCharSet, str.at(0), true);

    int iLo = 0;
    int iHi = -1;
    while ((iLo <= iHi) && (iHi < len)) {
        bool updated = false;
        int crrWinLen = iHi - iLo + 1;

        // expand window while imbalanced
        while ((crrWinLen <= 0) || ((iHi < len) && !imbCharSet.empty())) {
            iHi++;

            if (iHi >= len) {
                iHi--;
                break;
            }

            updated = true;
            updateCharFreq(charFreqMap, imbCharSet, str.at(iHi), true);

            if (debug) {
                cout << endl;
                printf("L1 (iLo=%d, iHi=%d)\n", iLo, iHi);
                printf("L1 included str(iHi=%d) = %c\n", iHi, str.at(iHi));
                showDebugInfo(charFreqMap, imbCharSet);
            }
        }

        if (imbCharSet.empty()) {
            int crrWinLen = iHi - iLo + 1;
            if (crrWinLen < minWinLen) {
                minWinLen = crrWinLen;
                minWinLo = iLo;
                minWinHi = iHi;
            }
        }

        // shrink window till balanced
        while ((iLo <= iHi) && imbCharSet.empty()) {
            updated = true;
            updateCharFreq(charFreqMap, imbCharSet, str.at(iLo), false);
            if (debug) {
                cout << endl;
                printf("L2 (iLo=%d, iHi=%d)\n", iLo, iHi);
                printf("L2 excluded str(iLo=%d) = %c\n", iLo, str.at(iLo));
                showDebugInfo(charFreqMap, imbCharSet);
            }
            iLo++;

            if (imbCharSet.empty()) {
                int crrWinLen = iHi - iLo + 1;
                if (crrWinLen < minWinLen) {
                    minWinLen = crrWinLen;
                    minWinLo = iLo;
                    minWinHi = iHi;
                }
            }
        }

        if (!updated) {
            if (debug) {
                printf("breaking with iLo=%d, iHi=%d\n", iLo, iHi);
            }
            break;
        }
    }

    int result = (minWinLen == INT_MAX) ? -1 : minWinLen;
    if (debug) {
        printf("result = %d\n", result);
    }
    return result;
}

void testFindMinWindow() {
    string strIn;
    int outExpected, outComputed;

    strIn = "";
    outExpected = -1;
    outComputed = findMinWindow(strIn, false);
    assert(outExpected == outComputed);

    strIn = "azABaabba";
    outExpected = 5;
    outComputed = findMinWindow(strIn, true);
    assert(outExpected == outComputed);
}

int main() {
    testFindMinWindow();
    return 0;
}
