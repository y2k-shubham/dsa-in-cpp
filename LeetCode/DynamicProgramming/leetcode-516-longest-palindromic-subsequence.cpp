// LeetCode-516: https://leetcode.com/problems/longest-palindromic-subsequence/

#include <vector>
#include <cmath>
#include <string>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    bool debug = false;

    // show matrix with indices
    void showMatrix(string& str, vector<vector<int> >& matrix) {
        printf("\t\t");
        for (int i = 0; i < matrix.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("\t\t");
        for (int i = 0; i < matrix.size(); i++) {
            printf("%c\t", str.at(i));
        }
        cout << endl;

        for (int i = 0; i < matrix.size(); i++) {
            printf("[%d]\t%c\t", i, str[i]);
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] == -1) {
                    printf("-\t");
                } else {
                    printf("%d\t", matrix[i][j]);
                }
            }
            printf("\n");
        }
        printf("\n");
    }

    vector<vector<int> > buildMat(string& str) {
        int len = str.size();

        vector<vector<int> > mat(len, vector<int>(len, -1));
        // prefill 1-len subseq lens
        for (int i = 0; i < len; i++) {
            mat[i][i] = 1;
        }
        // prefill 2-len subseq lens
        for (int i = 0; i < len - 1; i++) {
            if (str[i] == str[i + 1]) {
                mat[i][i + 1] = 2;
            } else {
                mat[i][i + 1] = 1;
            };
        }

        return mat;
    }

    void fillMat(string& str, vector<vector<int>>& mat) {
        int len = str.size();

        int rLo = 0;
        int cHi = len - 1;
        for (int substrLen = 3; substrLen <= len; substrLen++) {
            int rHi = len - substrLen;
            int cLo = substrLen - 1;

            int r = rLo;
            int c = cLo;
            while ((r <= rHi) && (c <= cHi)) {
                if (str[r] == str[c]) {
                    mat[r][c] = mat[r + 1][c - 1] + 2;
                } else {
                    mat[r][c] = max(mat[r + 1][c], mat[r][c - 1]);
                }

                r++;
                c++;
            }

            if (debug) {
                printf("after fillMat(substrLen=%d), mat is:-\n", substrLen);
                showMatrix(str, mat);
            }
        }
    }

public:
    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    int longestPalindromeSubseq(string s) {
        int len = s.size();
        if (len <= 1) {
            return len;
        }
        if (len == 2) {
            return (s[0] == s[1]) ? 2 : 1;
        }

        vector<vector<int>> mat = buildMat(s);
        if (debug) {
            printf("after buildMat, mat is:-\n");
            showMatrix(s, mat);
        }

        fillMat(s, mat);

        return mat[0][len - 1];
    }
};

class SolutionTest {
public:
    void testLongestPalindromeSubseq() {
        Solution soln = Solution();
        string strIn;
        int outExpected, outComputed;

//        soln.enableDebug();
        strIn = "bbbab";
        outExpected = 4;
        outComputed = soln.longestPalindromeSubseq(strIn);
//        cout << outComputed << endl;
        assert(outComputed == outExpected);
        soln.disableDebug();

        strIn = "cbbd";
        outExpected = 2;
        outComputed = soln.longestPalindromeSubseq(strIn);
        assert(outComputed == outExpected);

        strIn = "c";
        outExpected = 1;
        outComputed = soln.longestPalindromeSubseq(strIn);
        assert(outComputed == outExpected);

        strIn = "cb";
        outExpected = 1;
        outComputed = soln.longestPalindromeSubseq(strIn);
        assert(outComputed == outExpected);

        strIn = "zz";
        outExpected = 2;
        outComputed = soln.longestPalindromeSubseq(strIn);
        assert(outComputed == outExpected);

        strIn = "cbc";
        outExpected = 3;
        outComputed = soln.longestPalindromeSubseq(strIn);
        assert(outComputed == outExpected);

        soln.enableDebug();
        strIn = "cmpbqmbdc";
        outExpected = 5;
        outComputed = soln.longestPalindromeSubseq(strIn);
        assert(outComputed == outExpected);
        soln.disableDebug();
    }
};

int main() {
    SolutionTest st = SolutionTest();

    st.testLongestPalindromeSubseq();

    return 0;
}
