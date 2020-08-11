// https://leetcode.com/problems/excel-sheet-column-number/
// https://leetcode.com/explore/challenge/card/august-leetcoding-challenge/550/week-2-august-8th-august-14th/3419/
// https://www.interviewbit.com/problems/excel-column-number/
// https://www.geeksforgeeks.org/find-excel-column-number-column-title/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

int calcColBeginCharRank(char, int, bool);
void testCalcColBeginCharRank();
int titleToNumberCrooked(string);
void testTitleToNumberCrooked();
int titleToNumber(string);
void testTitleToNumber();

int main() {
    testCalcColBeginCharRank();
    testTitleToNumberCrooked();
    testTitleToNumber();

    return 0;
}

void testCalcColBeginCharRank() {
    assert(calcColBeginCharRank('A', 1, true) + 1 == 1);
    assert(calcColBeginCharRank('B', 1, true) + 1 == 2);
    assert(calcColBeginCharRank('P', 1, true) + 1 == 16);
    assert(calcColBeginCharRank('U', 1, true) + 1 == 21);
    assert(calcColBeginCharRank('Z', 1, true) + 1 == 26);
    assert(calcColBeginCharRank('A', 2, true) + 1 == 27);
    assert(calcColBeginCharRank('B', 2, true) + 1 == 53);
    assert(calcColBeginCharRank('N', 2, true) + 1 == 365);
    // cout << calcColBeginCharRank('U', 2, true) << endl;
    assert(calcColBeginCharRank('U', 2, true) + 1 == 547);
    assert(calcColBeginCharRank('Z', 2, true) + 1 == 677);
    assert(calcColBeginCharRank('A', 3, true) + 1 == 703);
}

int calcColBeginCharRank(char c, int pos, bool addLower) {
    int diff = c - 'A';
    int numLowerPosCharsPerms = diff * ((int)pow(26, pos - 1));

    // actually this thing should be moved to a separate function
    // since for a given number, it needs to be done only once (not for each alphabet of it's representation)
    if (addLower) {
        for (int i = pos - 1; i >= 1; i--) {
            numLowerPosCharsPerms += (int)pow(26, i);
        }
    }

    return numLowerPosCharsPerms;
}

void testTitleToNumberCrooked() {
    assert(titleToNumberCrooked("A") == 1);
    assert(titleToNumberCrooked("B") == 2);
    assert(titleToNumberCrooked("P") == 16);
    assert(titleToNumberCrooked("Z") == 26);
    assert(titleToNumberCrooked("AA") == 27);
    assert(titleToNumberCrooked("AP") == 42);
    assert(titleToNumberCrooked("BA") == 53);
    assert(titleToNumberCrooked("BB") == 54);
    assert(titleToNumberCrooked("NA") == 365);
    assert(titleToNumberCrooked("SZ") == 520);
    assert(titleToNumberCrooked("YU") == 671);
    assert(titleToNumberCrooked("ZA") == 677);
    assert(titleToNumberCrooked("ZZ") == 702);
    assert(titleToNumberCrooked("AAA") == 703);
    assert(titleToNumberCrooked("AAB") == 704);
    assert(titleToNumberCrooked("ABA") == 729);
    assert(titleToNumberCrooked("XFD") == 16384);
    assert(titleToNumberCrooked("CUZ") == 2600);
    assert(titleToNumberCrooked("NTP") == 10000);
}

int titleToNumberCrooked(string s) {
    // cout << endl << s << endl;
    int len = s.size();

    int rank = 0;
    for (int i = 0; i < len; i++) {
        int pos = len - i;
        char c = s.at(i);

        if (c == 'A' && i > 0) {
            continue;
        } else {
            // printf("rank = %d + %d\n", rank, calcColBeginCharRank(s.at(i), pos, i == 0));
            rank += calcColBeginCharRank(s.at(i), pos, i == 0);
        }
    }

    return rank + 1;
}

void testTitleToNumber() {
    assert(titleToNumber("A") == 1);
    assert(titleToNumber("B") == 2);
    assert(titleToNumber("P") == 16);
    assert(titleToNumber("Z") == 26);
    assert(titleToNumber("AA") == 27);
    assert(titleToNumber("AP") == 42);
    assert(titleToNumber("BA") == 53);
    assert(titleToNumber("BB") == 54);
    assert(titleToNumber("NA") == 365);
    assert(titleToNumber("SZ") == 520);
    assert(titleToNumber("YU") == 671);
    assert(titleToNumber("ZA") == 677);
    assert(titleToNumber("ZZ") == 702);
    assert(titleToNumber("AAA") == 703);
    assert(titleToNumber("AAB") == 704);
    assert(titleToNumber("ABA") == 729);
    assert(titleToNumber("XFD") == 16384);
    assert(titleToNumber("CUZ") == 2600);
    assert(titleToNumber("NTP") == 10000);
}

// approach taken from https://stackoverflow.com/a/848184/3679900
int titleToNumber(string s) {
    int len = s.size();
    int num = 0;
    int pow = 1;  // powers of 26 (weight of position)

    for (int i = 0; i < len; i++) {
        char c = s.at(len - i - 1);
        num += (c - 'A' + 1) * pow;
        pow *= 26;
    }

    return num;
}
