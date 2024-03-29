// TusharRoy: https://www.youtube.com/watch?v=lDYIvtBVmgo
// LeetCode-132: https://leetcode.com/problems/palindrome-partitioning-ii/
// GeeksForGeeks: https://www.geeksforgeeks.org/palindrome-partitioning-dp-17/
// InterviewBit: https://www.interviewbit.com/problems/palindrome-partitioning-ii/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

////////////////
// common stuff
////////////////

vector<vector<int> > createMemoMat(int len, int defaultValue) {
    vector<vector<int> > memoMat(len);

    for (int i = 0; i < len; i++) {
        vector<int> memoMatRow(len, defaultValue);
        memoMat[i] = memoMatRow;
    }

    return memoMat;
}

void showMemoMat(vector<vector<int> >& memoMat, string str) {
    int len = str.size();
    
    printf("\t");
    for (int i = 0; i < len; i++) {
        printf("%c\t", str.at(i));
    }
    cout << endl;

    printf("\t");
    for (int i = 0; i < len; i++) {
        printf("[%d]\t", i);
    }
    cout << endl;

    for (int i = 0; i < len; i++) {
        printf("%c [%d]\t", str.at(i), i);
        for (int j = 0; j < len; j++) {
            if (j < i) {
                printf("\t");
            } else {
                printf("%d\t", memoMat[i][j]);
            }
        }
        cout << endl;
    }
}

/////////////////////
// 1st implementation
/////////////////////

bool isPalindrome(string str) {
    int len = str.size();
    if (len <= 1) {
        return true;
    }

    int i = 0;
    while (i <= (len / 2)) {
        if (str.at(i) != str.at(len - i - 1)) {
            return false;
        }
        i++;
    }

    return true;
}

void testIsPalindrome() {
    string str;
    bool outExpected;
    bool outComputed;

    str = "";
    outExpected = true;
    outComputed = isPalindrome(str);
    assert(outExpected == outComputed);

    str = "f";
    outExpected = true;
    outComputed = isPalindrome(str);
    assert(outExpected == outComputed);

    str = "fa";
    outExpected = false;
    outComputed = isPalindrome(str);
    assert(outExpected == outComputed);

    str = "faf";
    outExpected = true;
    outComputed = isPalindrome(str);
    assert(outExpected == outComputed);

    str = "aa";
    outExpected = true;
    outComputed = isPalindrome(str);
    assert(outExpected == outComputed);

    str = "aabb";
    outExpected = false;
    outComputed = isPalindrome(str);
    assert(outExpected == outComputed);
}

// goes TLE on LeetCode
int findMinPartitions1(string str) {
    int len = str.size();
    if (len <= 1) {
        return 0;
    }
    if (isPalindrome(str)) {
        return 0;
    }

    vector<vector<int> > memoMat = createMemoMat(len, 0);

    int rLo = 0;
    int cHi = len - 1;

    for (int l = 2; l <= len; l++) {
        int i = rLo;
        int j = l - 1;

        while (j <= cHi) {
            if (!isPalindrome(str.substr(i, (j - i + 1)))) {
                int minCuts = INT_MAX;
                for (int k = i; k < j; k++) {
                    minCuts = min(minCuts, 1 + memoMat[i][k] + memoMat[k + 1][j]);
                }
                memoMat[i][j] = minCuts;
            }

            i++;
            j++;
        }
    }

    return memoMat[0][len - 1];
}

void testFindMinPartitions1() {
    string str;
    int outExpected;
    int outComputed;

    str = "";
    outExpected = 0;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "d";
    outExpected = 0;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "da";
    outExpected = 1;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "dd";
    outExpected = 0;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "ddy";
    outExpected = 1;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "dyd";
    outExpected = 0;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "common";
    outExpected = 2;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "uncommon";
    outExpected = 4;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "uncommonly";
    outExpected = 6;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "ababb";
    outExpected = 1;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "aaabba";
    outExpected = 1;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);

    str = "ababbbabbababa";
    outExpected = 3;
    outComputed = findMinPartitions1(str);
    assert(outExpected == outComputed);
}

/////////////////////
// 2nd implementation
/////////////////////

int findMinPartitions2(string str, bool debug) {
    int len = str.size();
    if (len <= 1) {
        return 0;
    }
    if (isPalindrome(str)) {
        return 0;
    }

    vector<vector<int> > memoMat = createMemoMat(len, 0);

    int rLo = 0;
    int cHi = len - 1;

    for (int l = 2; l <= len; l++) {
        int i = rLo;
        int j = l - 1;

        while (j <= cHi) {
            if ((str.at(i) == str.at(j)) && ((i + 1 == j) || (memoMat[i + 1][j - 1] == 0))) {
                // nothing
            } else {
                int minCuts = INT_MAX;
                for (int k = i; k < j; k++) {
                    minCuts = min(minCuts, 1 + memoMat[i][k] + memoMat[k + 1][j]);
                }
                memoMat[i][j] = minCuts;
            }

            i++;
            j++;
        }
    }

    if (debug) {
        showMemoMat(memoMat, str);
    }

    return memoMat[0][len - 1];
}

void testFindMinPartitions2() {
    string str;
    int outExpected;
    int outComputed;

    str = "";
    outExpected = 0;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "d";
    outExpected = 0;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "da";
    outExpected = 1;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "dd";
    outExpected = 0;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "ddy";
    outExpected = 1;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "dyd";
    outExpected = 0;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "common";
    outExpected = 2;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "uncommon";
    outExpected = 4;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "uncommonly";
    outExpected = 6;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "ababb";
    outExpected = 1;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "aaabba";
    outExpected = 1;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);

    str = "ababbbabbababa";
    outExpected = 3;
    outComputed = findMinPartitions2(str, false);
    assert(outExpected == outComputed);
}

int main() {
    testIsPalindrome();
    testFindMinPartitions1();
    testFindMinPartitions2();

    return 0;
}
