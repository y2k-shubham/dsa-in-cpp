// LeedCode-1092: https://leetcode.com/problems/shortest-common-supersequence/
// SCS reconstruction: https://www.youtube.com/watch?v=pHXntFeu6f8
// GFG: https://www.geeksforgeeks.org/shortest-common-supersequence/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    void showMat(string str1, string str2, vector<vector<int> > memoMat) {
        int len1 = str1.size();
        int len2 = str2.size();

        printf("\t");
        for (int j = 0; j <= len2; j++) {
            printf("[%d]\t", j);
        }
        cout << endl;

        printf("\t");
        for (int j = 0; j <= len2; j++) {
            if (j > 0) {
                printf("%c\t", str2.at(j - 1));
            } else {
                printf("\t");
            }
        }
        cout << endl;

        for (int i = 0; i <= len1; i++) {
            if (i == 0) {
                printf("[%d]\t", i);
            } else {
                printf("[%d] %c\t", i, str1.at(i - 1));
            }

            for (int j = 0; j <= len2; j++) {
                printf("%d\t", memoMat[i][j]);
            }
            cout << endl;
        }
    }

    vector<vector<int> > createMemoMat(string str1, string str2) {
        int len1 = str1.size();
        int len2 = str2.size();

        vector<vector<int> > memoMat(len1 + 1);

        for (int i = 0; i <= len1; i++) {
            vector<int> memoMatRow(len2 + 1);
            memoMat[i] = memoMatRow;
        }

        return memoMat;
    }

    void fillMemoMat(string str1, string str2, vector<vector<int> >& memoMat) {
        int len1 = str1.size();
        int len2 = str2.size();

        // printf("str1=%s, str2=%s\n", str1.c_str(), str2.c_str());

        for (int i = 1; i <= len1; i++) {
            char ch1 = str1.at(i - 1);
            for (int j = 1; j <= len2; j++) {
                char ch2 = str2.at(j - 1);

                // printf("ch1=%c, ch2=%c equal=%s\n", ch1, ch2, (ch1 == ch2 ? "true" : "false"));

                if (ch1 == ch2) {
                    memoMat[i][j] = memoMat[i - 1][j - 1] + 1;
                } else {
                    memoMat[i][j] = max(memoMat[i - 1][j], memoMat[i][j - 1]);
                }
            }
        }
    }

   public:
    string findLCS(string str1, string str2, bool debug) {
        int len1 = str1.size();
        int len2 = str2.size();

        vector<vector<int> > memoMat = createMemoMat(str1, str2);
        fillMemoMat(str1, str2, memoMat);

        if (debug) {
            showMat(str1, str2, memoMat);
        }

        if (memoMat[len1][len2] == 0) {
            return "";
        }

        string lcs = "";
        int i = len1;
        int j = len2;
        while (i >= 1 || j >= 1) {
            if (debug) {
                // printf("mat[i=%d][j=%d] = %d\tlcs = %s\n", i, j, memoMat[i][j], lcs.c_str());
            }

            if (j >= 1 && memoMat[i][j] == memoMat[i][j - 1]) {
                j--;
            } else if (i >= 1 && memoMat[i][j] == memoMat[i - 1][j]) {
                i--;
            } else if (i >= 1 && j >= 1 && memoMat[i][j] == (memoMat[i - 1][j - 1] + 1)) {
                lcs = lcs + str1.at(i - 1);
                i--;
                j--;
            } else if (i > 1) {
                i--;
            } else {
                j--;
            }
        }

        reverse(lcs.begin(), lcs.end());

        return lcs;
    }

    string findSCS(string str1, string str2, bool debug) {
        int len1 = str1.size();
        int len2 = str2.size();

        string strLcs = findLCS(str1, str2, false);
        int lenLcs = strLcs.size();

        if (lenLcs == 0) {
            return str1 + str2;
        }

        if (debug) {
            printf("strLcs = %s\n", strLcs.c_str());
        }

        string scs = "";
        int i1 = 0;
        int i2 = 0;
        int iLcs = 0;
        while ((i1 < len1) && (i2 < len2) && (iLcs < lenLcs)) {
            bool match1 = str1.at(i1) == strLcs.at(iLcs);
            bool match2 = str2.at(i2) == strLcs.at(iLcs);

            if (match1 && match2) {
                scs = scs + strLcs.at(iLcs);

                i1++;
                i2++;
                iLcs++;
            } else if (match1) {
                scs = scs + str2.at(i2);
                i2++;
            } else if (match2) {
                scs = scs + str1.at(i1);
                i1++;
            } else {
                scs = scs + str1.at(i1);
                i1++;
            }
        }

        while (i1 < len1) {
            scs = scs + str1.at(i1);
            i1++;
        }

        while (i2 < len2) {
            scs = scs + str2.at(i2);
            i2++;
        }

        return scs;
    }

    string shortestCommonSupersequence(string str1, string str2) {
        return findSCS(str1, str2, false);
    }

    friend class TestSolution;
};

class TestSolution {
   public:
    void testFindLCS() {
        Solution soln = Solution();
        string str1;
        string str2;
        string lcsOutExpected;
        string lcsOutComputed;

        str1 = "abcdgh";
        str2 = "aedfhr";
        lcsOutExpected = "adh";
        lcsOutComputed = soln.findLCS(str1, str2, false);
        assert(lcsOutExpected == lcsOutComputed);

        str1 = "bbabacaa";
        str2 = "cccababab";
        lcsOutExpected = "baba";
        lcsOutComputed = soln.findLCS(str1, str2, false);
        // cout << lcsOutComputed << endl;
        assert(lcsOutExpected == lcsOutComputed);
    }

    void testFindSCS() {
        Solution soln = Solution();
        string str1;
        string str2;
        string scsOutExpected;
        string scsOutComputed;

        str1 = "geek";
        str2 = "eke";
        scsOutExpected = "geeke";
        scsOutComputed = soln.findSCS(str1, str2, false);
        assert(scsOutExpected == scsOutComputed);

        str1 = "AGGTAB";
        str2 = "GXTXAYB";
        scsOutExpected = "AGGXTXAYB";
        scsOutComputed = soln.findSCS(str1, str2, false);
        // cout << scsOutComputed << endl;
        assert(scsOutExpected == scsOutComputed);

        str1 = "bbabacaa";
        str2 = "cccababab";
        scsOutExpected = "cccabbabacaab";
        scsOutComputed = soln.findSCS(str1, str2, false);
        // cout << scsOutComputed << endl;
        assert(scsOutExpected == scsOutComputed);
    }
};

int main() {
    TestSolution testSoln = TestSolution();
    testSoln.testFindLCS();
    testSoln.testFindSCS();

    return 0;
}
