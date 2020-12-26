
// crooked file: commenting out print stmts leads to assertion failures

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

void showMat(string s, vector<vector<int> > memoMat) {
    int len = s.size();

    printf("\n\t");
    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    printf("\t");
    for (int i = 0; i < len; i++) {
        printf("'%c'\t", s.at(i));
    }
    cout << endl;

    for (int i = 0; i < len; i++) {
        printf("[%d] '%c'\t", i, s.at(i));
        for (int j = 0; j < len; j++) {
            if (i > j) {
                printf("\t");
            } else {
                printf("%d\t", memoMat[i][j]);
            }
        }
        cout << endl;
    }
}

unordered_map<int, char> getCodeCharMap() {
    unordered_map<int, char> codeCharMap = {
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
    return codeCharMap;
}

unordered_map<char, int> getCharCodeMap() {
    unordered_map<char, int> charCodeMap = {
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
    return charCodeMap;
}

vector<vector<int> > createMemoMat(string s) {
    int len = s.size();
    unordered_map<int, char> codeCharMap = getCodeCharMap();

    vector<vector<int> > memoMat(len);
    for (int i = 0; i < len; i++) {
        vector<int> memoMatRow(len, 0);

        int crrCode = s.at(i) - '0';
        if (codeCharMap.find(crrCode) != codeCharMap.end()) {
            memoMatRow[i] = 1;
        }

        memoMat[i] = memoMatRow;
    }

    return memoMat;
}

void fillMemoMat(string s, vector<vector<int> >& memoMat, bool debug) {
    int len = s.size();
    unordered_map<int, char> codeCharMap = getCodeCharMap();

    for (int subLen = 2; subLen <= len; subLen++) {
        int rLo = 0;
        int cLo = subLen - 1;

        int cHi = len - 1;

        if (debug) {
            printf("\n---------\n");
            printf("rLo=%d, cLo=%d, cHi=%d\n", rLo, cLo, cHi);
        }

        int iBegin = rLo;
        int iEnd = cLo;
        while (iEnd <= cHi) {
            int crrSingleDigCode = s.at(iEnd) - '0';

            if (debug) {
                printf("\ns[iBegin=%d] = %c, s[iEnd=%d] = %c\n", iBegin, s.at(iBegin), iEnd, s.at(iEnd));
            }

            int numWaysSingleDigCode = 0;
            if (codeCharMap.find(crrSingleDigCode) != codeCharMap.end()) {
                numWaysSingleDigCode = min(1, memoMat[iBegin][iEnd - 1]);
            }

            if (debug) {
                printf("crrSingleDigCode = %d, numWaysSingleDigCode = %d\n", crrSingleDigCode, numWaysSingleDigCode);
            }

            int prevSingleDigCode = s.at(iEnd - 1) - '0';
            int crrDoubleDigCode = prevSingleDigCode * 10 + crrSingleDigCode;

            int numWaysDoubleDigCode = 0;
            if (codeCharMap.find(crrDoubleDigCode) != codeCharMap.end()) {
                numWaysDoubleDigCode = min(1, memoMat[iBegin][iEnd - 2]);
            }

            if (debug) {
                printf("crrDoubleDigCode = %d, numWaysDoubleDigCode = %d\n", crrDoubleDigCode, numWaysDoubleDigCode);
            }

            memoMat[iBegin][iEnd] = numWaysSingleDigCode + numWaysDoubleDigCode;

            if (debug) {
                printf("memoMat[iBegin=%d][iEnd=%d] = numWaysSingleDigCode=%d + numWaysDoubleDigCode=%d = %d\n", iBegin, iEnd, numWaysSingleDigCode, numWaysDoubleDigCode, memoMat[iBegin][iEnd]);
            }

            iBegin++;
            iEnd++;
        }

        if (debug) {
            printf("\n~~~~~~~~~~~after subLen=%d~~~~~~~~~~~~\n", subLen);
            showMat(s, memoMat);
        }
    }
}

int numDecodingsDebug(string s, bool debug) {
    int len = s.size();

    if (len < 1) {
        return 0;
    } else if (len == 1) {
        int singleDigCode = s.at(0) - '0';

        unordered_map<int, char> codeCharMap = getCodeCharMap();
        if (codeCharMap.find(singleDigCode) == codeCharMap.end()) {
            return 0;
        } else {
            return 1;
        }
    } else {
        vector<vector<int> > memoMat = createMemoMat(s);
        if (debug) {
            showMat(s, memoMat);
        }

        fillMemoMat(s, memoMat, debug);
        if (debug) {
            showMat(s, memoMat);
        }

        int retVal = memoMat[0][len - 1];
        if (debug) {
            printf("\nreturning %d as answer\n================\n", retVal);
        }
        return retVal;
    }
}

void testNumDecodingsDebug() {
    string s;
    int outExpected;
    int outComputed;

    s = "";
    outExpected = 0;
    outComputed = numDecodingsDebug(s, false);
    assert(outExpected == outComputed);

    s = "0";
    outExpected = 0;
    outComputed = numDecodingsDebug(s, false);
    assert(outExpected == outComputed);

    s = "1";
    outExpected = 1;
    outComputed = numDecodingsDebug(s, false);
    assert(outExpected == outComputed);

    s = "9";
    outExpected = 1;
    outComputed = numDecodingsDebug(s, false);
    assert(outExpected == outComputed);

    s = "10";
    outExpected = 1;
    // commenting out print stmts (or passing false) leads to assertion failures
    outComputed = numDecodingsDebug(s, true);
    cout << outComputed << endl;
    assert(outExpected == outComputed);

    s = "11";
    outExpected = 2;
    outComputed = numDecodingsDebug(s, false);
    assert(outExpected == outComputed);

    s = "12";
    outExpected = 2;
    outComputed = numDecodingsDebug(s, false);
    assert(outExpected == outComputed);

    s = "19";
    outExpected = 2;
    outComputed = numDecodingsDebug(s, true);
    assert(outExpected == outComputed);

    s = "20";
    outExpected = 1;
    // commenting out print stmts (or passing false) leads to assertion failures
    outComputed = numDecodingsDebug(s, true);
    assert(outExpected == outComputed);

    s = "21";
    outExpected = 2;
    outComputed = numDecodingsDebug(s, false);
    assert(outExpected == outComputed);

    s = "26";
    outExpected = 2;
    outComputed = numDecodingsDebug(s, false);
    assert(outExpected == outComputed);

    s = "226";
    outExpected = 3;
    outComputed = numDecodingsDebug(s, true);
    assert(outExpected == outComputed);
}

int numDecodings(string s) {
    return numDecodingsDebug(s, false);
}

int main() {
    testNumDecodingsDebug();

    return 0;
}
