// LeetCode-2516: https://leetcode.com/problems/take-k-of-each-character-from-left-and-right
// good question; clever approach with tricky edge case
// solved after seeing hints on LeetCode

#include <vector>
#include <string>
#include <tuple>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

#define CHAR_A 'a'
#define CHAR_B 'b'
#define CHAR_C 'c'

#define tuple_get(tup, idx) get<idx>(tup)

class Solution {
private:
    bool debug = false;

    inline bool hasRequiredChars(tuple<int, int, int> freq, tuple<int, int, int> requiredFreq) {
        return (tuple_get(freq, 0) >= tuple_get(requiredFreq, 0)) &&
               (tuple_get(freq, 1) >= tuple_get(requiredFreq, 1)) &&
               (tuple_get(freq, 2) >= tuple_get(requiredFreq, 2));
    }

    inline tuple<int, int, int> getUpdatedFreq(tuple<int, int, int> freq, char ch) {
        if (ch == CHAR_A) {
            return {tuple_get(freq, 0) + 1, tuple_get(freq, 1), tuple_get(freq, 2)};
        } else if (ch == CHAR_B) {
            return {tuple_get(freq, 0), tuple_get(freq, 1) + 1, tuple_get(freq, 2)};
        } else {
            return {tuple_get(freq, 0), tuple_get(freq, 1), tuple_get(freq, 2) + 1};
        }
    }

    inline tuple<int, int, int> calcDiff(tuple<int, int, int> subtractFrom, tuple<int, int, int> subtractor) {
        return {tuple_get(subtractFrom, 0) - tuple_get(subtractor, 0),
                tuple_get(subtractFrom, 1) - tuple_get(subtractor, 1),
                tuple_get(subtractFrom, 2) - tuple_get(subtractor, 2)};
    }

    inline int calcNumMoves(int len, int leftIdx, int rightIdx) {
        return (leftIdx + 1) + (len - rightIdx);
    }

    vector<tuple<int, int, int>> calsFeqsFromRight(string& str) {
        int len = str.size();

        int aFreq = 0, bFreq = 0, cFreq = 0;
        vector<tuple<int, int, int>> freqs(len);

        int i = len - 1;
        for (int j = len - 1; j >= 0; j--) {
            char ch = str[j];
            if (ch == CHAR_A) {
                aFreq++;
            } else if (ch == CHAR_B) {
                bFreq++;
            } else {
                cFreq++;
            }

            freqs[i--] = {aFreq, bFreq, cFreq};
        }

        return freqs;
    }

    int findMinIdxFromRight(vector<tuple<int, int, int>>& freqs, tuple<int, int, int> requiredFreqs) {
        int len = freqs.size();

        for (int i = len - 1; i >= 0; i--) {
            tuple<int, int, int> freq = freqs[i];

            if (hasRequiredChars(freq, requiredFreqs)) {
                return i;
            }
        }

        return -1;
    }

    inline int moveRightTillSatisfied(vector<tuple<int, int, int>>& freqs, tuple<int, int, int> requiredFreqs, int startIdx) {
        int len = freqs.size();

        for (int i = startIdx + 1; i < len; i++) {
            tuple<int, int, int> freq = freqs[i];

            if (!hasRequiredChars(freq, requiredFreqs)) {
                return i - 1;
            }
        }

        return len;
    }

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    int calcMinMoves(string& s, int k) {
        int len = s.size();

        vector<tuple<int, int, int>> freqsFromRight = calsFeqsFromRight(s);
        int aFreq = tuple_get(freqsFromRight[0], 0);
        int bFreq = tuple_get(freqsFromRight[0], 1);
        int cFreq = tuple_get(freqsFromRight[0], 2);
        if (aFreq < k || bFreq < k || cFreq < k) {
            return -1;
        }

        tuple<int, int, int> requiredFreq = {k, k, k};

        int leftIdx = -1;
        tuple<int, int, int> crrFreqFromLeft = {0, 0, 0};
        int rightIdx = findMinIdxFromRight(freqsFromRight, calcDiff(requiredFreq, crrFreqFromLeft));
        if (rightIdx == -1) {
            return -1;
        }
        int minMoves = calcNumMoves(len, leftIdx, rightIdx);
        if (debug) {
            showDebugOut(s, leftIdx, rightIdx, minMoves);
        }

        while (++leftIdx, rightIdx < len) {
            char ch = s.at(leftIdx);
            crrFreqFromLeft = getUpdatedFreq(crrFreqFromLeft, ch);

            rightIdx = moveRightTillSatisfied(freqsFromRight, calcDiff(requiredFreq, crrFreqFromLeft), rightIdx);
            if (rightIdx >= len) {
                break;
            }

            minMoves = min(minMoves, calcNumMoves(len, leftIdx, rightIdx));
            if (debug) {
                showDebugOut(s, leftIdx, rightIdx, minMoves);
            }
        }

        return minMoves;
    }

    void showDebugOut(string& str, int leftIdx, int rightIdx, int minMoves) {
        int len = str.size();

        printf("-----------\n");

        if (leftIdx == -1) {
            printf(" ");
        }
        cout << str << endl;

        if (leftIdx == -1) {
            printf("^");
        }
        for (int i = 0; i < len; i++) {
            if (i == leftIdx || i == rightIdx) {
                printf("^");
            } else {
                printf(" ");
            }
        }
        if (rightIdx == len) {
            printf("^");
        }
        printf("\n");

        char ch = ((0 <= leftIdx) && (leftIdx < len)) ? str.at(leftIdx) : '\0';
        printf("at s.(leftIdx=%d)='%c', calculated rightIdx=%d, numMoves=%d, updated minMoves=%d\n", leftIdx, ch, rightIdx, calcNumMoves(len, leftIdx, rightIdx), minMoves);

        printf("-----------\n");
    }

public:
    friend class SolutionTest;

    int takeCharacters(string s, int k) {
        int len = s.size();
        if (len < (3 * k)) {
            return -1;
        }
        if (k == 0) {
            return 0;
        }

        int minMovesRightToLeft = calcMinMoves(s, k);
        if (minMovesRightToLeft == -1) {
            return -1;
        }

        std::reverse(s.begin(), s.end());

        int minMovesLeftToRight = calcMinMoves(s, k);
        if (minMovesLeftToRight == -1) {
            return minMovesRightToLeft;
        }

        return min(minMovesRightToLeft, minMovesLeftToRight);
    }
};

class SolutionTest {
public:
    void testTakeCharacters() {
        Solution soln = Solution();
        string strIn;
        int kIn;
        int movesOutExpected, movesOutComputed;

        strIn = "aabaaaacaabc";

        kIn = 1;
        movesOutExpected = 3;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

//        soln.enableDebug();

        kIn = 2;
        movesOutExpected = 8;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        kIn = 3;
        movesOutExpected = -1;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        strIn = "a";

        kIn = 1;
        movesOutExpected = -1;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        strIn = "aaabbbccc";

        kIn = 1;
        movesOutExpected = 5;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        kIn = 2;
        movesOutExpected = 7;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        kIn = 3;
        movesOutExpected = 9;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        kIn = 4;
        movesOutExpected = -1;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        strIn = "aaaacbbbbaaaababbbccc";

        kIn = 3;
        movesOutExpected = 9;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        kIn = 4;
        movesOutExpected = 12;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        // this test case requires left to right computation (right to left one gives wrong / suboptimal answer)
        strIn = "acbcc";

        kIn = 1;
        movesOutExpected = 3;
        movesOutComputed = soln.takeCharacters(strIn, kIn);
        assert(movesOutExpected == movesOutComputed);

        printf("[testTakeCharacters] All test cases passed\n");
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testTakeCharacters();

    return 0;
}
