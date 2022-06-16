// LeetCode-5: https://leetcode.com/problems/longest-palindromic-substring/

#include <vector>
#include <string>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    vector<vector<bool> > createMemoMat(string& str) {
        int len = str.length();
        vector<vector<bool> > memoMat(len, vector<bool>(len, false));

        // 1-length palindromic substrings
        for (int i = 0; i < len; i++) {
            memoMat[i][i] = true;
        }
        // 2-length palindromic substrings
        for (int i = 0; i < len - 1; i++) {
            if (str[i] == str[i + 1]) {
                memoMat[i][i + 1] = true;
            }
        }

        return memoMat;
    }

    void fillMemoMat(string& str, vector<vector<bool> >& memoMat) {
        int len = str.length();

        int rLo = 0;
        int cHi = len - 1;
        for (int substrLen = 3; substrLen <= len; substrLen++) {
            int rHi = len - substrLen;
            int cLo = substrLen - 1;

            int r = rLo;
            int c = cLo;
            while ((r <= rHi) && (c <= cHi)) {
                if (str[r] == str[c]) {
                    memoMat[r][c] = memoMat[r + 1][c - 1];
                }

                r++;
                c++;
            }
        }
    }

    string findLongestPalinSubstrLen(string& str, vector<vector<bool> >& memoMat) {
        int len = memoMat.size();

        int maxLen = 1;
        pair<int, int> maxBeginEndIdx;
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (memoMat[i][j]) {
                    int currLen = j - i + 1;
                    if (currLen > maxLen) {
                        maxLen = currLen;
                        maxBeginEndIdx = make_pair(i, j);
                    }
                }
            }
        }

        return str.substr(maxBeginEndIdx.first, maxLen);
    }

public:
    string longestPalindrome(string s) {
        int len = s.size();
        if (len <= 1) {
            return s;
        }

        vector<vector<bool> > memoMat = createMemoMat(s);
        fillMemoMat(s, memoMat);

        return findLongestPalinSubstrLen(s, memoMat);
    }
};

class SolutionTest {
public:
    void testLongestPalindrome() {
        Solution s = Solution();
        string strIn;
        string strOutExpected, strOutComputed;

        strIn = "babad";
        strOutExpected = "bab";
        strOutComputed = s.longestPalindrome(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "cbbd";
        strOutExpected = "bb";
        strOutComputed = s.longestPalindrome(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "babbad";
        strOutExpected = "abba";
        strOutComputed = s.longestPalindrome(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "babebad";
        strOutExpected = "abeba";
        strOutComputed = s.longestPalindrome(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "babebead";
        strOutExpected = "bab";
        strOutComputed = s.longestPalindrome(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "b";
        strOutExpected = "b";
        strOutComputed = s.longestPalindrome(strIn);
        assert(strOutExpected == strOutComputed);

        strIn = "qwertyuioplkjhgfdsazxcvbnm";
        strOutExpected = "q";
        strOutComputed = s.longestPalindrome(strIn);
        assert(strOutExpected == strOutComputed);
    }
};

int main() {
    SolutionTest st = SolutionTest();
    st.testLongestPalindrome();
    return 0;
}
