// LeetCode-32: https://leetcode.com/problems/longest-valid-parentheses/
// AlgorithmsMadeEasy; 2nd approach: https://www.youtube.com/watch?v=VdQuwtEd10M

#include <cstdio>
#include <iostream>
#include <cmath>

using namespace std;

class Solution {
private:
    int findLongestLeftToRight(string& str) {
        int longestSeqLen = 0;

        int numOpenParens = 0;
        int numCloseParens = 0;
        for (int i = 0; i < str.size(); i++) {
            char ch = str.at(i);

            if (ch == '(') {
                numOpenParens++;
            } else {
                numCloseParens++;
            }

            if (numOpenParens == numCloseParens) {
                int crrSeqLen = numCloseParens * 2;
                longestSeqLen = max(longestSeqLen, crrSeqLen);
            } else if (numOpenParens < numCloseParens) {
                numOpenParens = 0;
                numCloseParens = 0;
            }
        }

        return longestSeqLen;
    }

    int findLongestRightToLeft(string& str) {
        int longestSeqLen = 0;

        int numOpenParens = 0;
        int numCloseParens = 0;
        for (int i = ((int) str.size()) - 1; i >= 0; i--) {
            char ch = str.at(i);

            if (ch == ')') {
                numCloseParens++;
            } else {
                numOpenParens++;
            }

            if (numOpenParens == numCloseParens) {
                int crrSeqLen = numOpenParens * 2;
                longestSeqLen = max(longestSeqLen, crrSeqLen);
            } else if (numOpenParens > numCloseParens) {
                numOpenParens = 0;
                numCloseParens = 0;
            }
        }

        return longestSeqLen;
    }

public:
    int longestValidParentheses(string s) {
        return max(
                findLongestLeftToRight(s),
                findLongestRightToLeft(s)
        );
    }
};
