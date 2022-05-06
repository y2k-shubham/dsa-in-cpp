// LeetCode-792: https://leetcode.com/problems/number-of-matching-subsequences/

// clever pre-computation approach;
// each subseq match with str
//  - takes O(len(subseq)) time
//  - [and is independent of len(str)]

// still LeetCode submission was abysmal
// speed 12 %tile, memory 16 %tile

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>
#include <climits>

using namespace std;

#define NUM_ALPHAS 26
#define BEGIN_ALPHA 'a'
#define END_ALPHA 'z'

class Solution {
private:
    bool debug = false;

    vector<vector<int> > createNextIdxMat(int len) {
        vector<vector<int> > mat(NUM_ALPHAS);

        for (char ch = BEGIN_ALPHA; ch <= END_ALPHA; ch++) {
            vector<int> vec(len, INT_MAX);
            mat[ch - BEGIN_ALPHA] = vec;
        }

        return mat;
    }

    void fillCol(vector<vector<int> >& mat, int colIdx, vector<int>& vec) {
        for (int i = 0; i < mat.size(); i++) {
            mat[i][colIdx] = vec[i];
        }
    }

    void fillNextIdxMat(string& str, vector<vector<int> >& mat) {
        int len = str.size();
        if (len == 0) {
            return;
        }

        vector<int> nextIdxVec(NUM_ALPHAS, INT_MAX);
        for (int j = len - 2; j >= 0; j--) {
            // note that at jth column, we fill position of j+1th character of string
            // (since we want index of next occurrence)
            char ch = str.at(j + 1);
            nextIdxVec[ch - BEGIN_ALPHA] = j + 1;

            fillCol(mat, j, nextIdxVec);

            if (debug) {
                printf("\n-----str.at(j=%d) = %c-----\n", j, ch);
                showNextIdxVec(nextIdxVec);
                showNextIdxMat(mat, str);
                printf("\n----------\n");
            }
        }
    }

    vector<vector<int> > prepareNextIdxMat(string& str) {
        int len = str.size();
        if (len == 0) {
            return {};
        }

        vector<vector<int> > mat = createNextIdxMat(len);
        fillNextIdxMat(str, mat);

        return mat;
    }

    void showNextIdxVec(vector<int>& nextIdxVec) {
        printf("nextIdx vec is:-\n");

        for (char ch = BEGIN_ALPHA; ch <= END_ALPHA; ch++) {
            int i = ch - BEGIN_ALPHA;
            printf("%c\t[%d]\t", ch, i);

            if (nextIdxVec[i] == INT_MAX) {
                printf("-\n");
            } else {
                printf("%d\n", nextIdxVec[i]);
            }
        }
        cout << endl;
    }

    void showNextIdxMat(vector<vector<int> >& mat, string& str) {
        int len = str.size();

        printf("nextIdx mat is:-\n");

        printf("Str:\t\t");
        for (int j = 0; j < len; j++) {
            printf("%c\t", str.at(j));
        }
        cout << endl;

        printf("\t\t");
        for (int j = 0; j < len; j++) {
            printf("[%d]\t", j);
        }
        cout << endl;

        for (char ch = BEGIN_ALPHA; ch <= END_ALPHA; ch++) {
            int i = ch - BEGIN_ALPHA;
            printf("%c\t[%d]\t", ch, i);

            for (int j = 0; j < len; j++) {
                if (mat[i][j] == INT_MAX) {
                    printf("-\t");
                } else {
                    printf("%d\t", mat[i][j]);
                }
            }
            cout << endl;
        }
        cout << endl;
    }

    bool hasSubseq(string& str, vector<vector<int> >& mat, string& subseq) {
        int len = str.size();

        int j = 0;
        for (int i = 0; i < subseq.size();) {
            // IMPORTANT: do NOT forget to add this
            // (this is the case when string itself ended while part of subsequence is left to match)
            if (j >= len) {
                return false;
            }

            char ch = subseq.at(i);
            if (str.at(j) == ch) {
                if (debug) {
                    printf("at subseq.at(i=%d)=%c, matched str.at(j=%d)=%c\n", i, subseq.at(i), j, str.at(j));
                }

                i++;
                j++;
                continue;
            }

            if (mat[ch - BEGIN_ALPHA][j] == INT_MAX) {
                if (debug) {
                    printf("at subseq.at(i=%d)=%c, returned false\n", i, subseq.at(i));
                }
                return false;
            } else {
                j = mat[ch - BEGIN_ALPHA][j];
                if (debug) {
                    printf("at subseq.at(i=%d)=%c, skipped to str.at(j=%d)=%c\n", i, subseq.at(i), j, str.at(j));
                }
            }
        }

        return true;
    }

public:
    friend class SolutionTest;

    int numMatchingSubseq(string s, vector<string>& words) {
        vector<vector<int> > mat = prepareNextIdxMat(s);

        int numSubseqs = 0;
        for (int i = 0; i < words.size(); i++) {
            if (hasSubseq(s, mat, words[i])) {
                ++numSubseqs;
            }
        }

        return numSubseqs;
    }
};

class SolutionTest {
public:
    void debugFillNextIdxMat() {
        Solution soln = Solution();
        string str;
        vector<vector<int> > mat;

//        soln.debug = true;
        str = "abcde";
        mat = soln.prepareNextIdxMat(str);
        soln.showNextIdxMat(mat, str);
//        soln.debug = false;

        str = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(str);
        soln.showNextIdxMat(mat, str);
    }

    void testHasSubseq() {
        Solution soln = Solution();
        string strIn;
        vector<vector<int> > mat;
        string subseqIn;
        bool outExpected, outComputed;

        strIn = "abcde";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "a";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "abcde";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "bb";
        outExpected = false;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

//        soln.debug = true;
        strIn = "abcde";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "acd";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);
//        soln.debug = false;

        strIn = "abcde";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "ace";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "abcde";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "adb";
        outExpected = false;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "ahjpjau";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "ja";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "ahbwzgqnuk";
        outExpected = false;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "tnmlanowax";
        outExpected = false;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "apj";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "apju";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "ahju";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "ahjau";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "ahjpau";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "ahpjau";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "dpa";
        outExpected = true;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "dsahjpjauf";
        mat = soln.prepareNextIdxMat(strIn);
        subseqIn = "dph";
        outExpected = false;
        outComputed = soln.hasSubseq(strIn, mat, subseqIn);
        assert(outExpected == outComputed);

        strIn = "iwdlcxpyagegrcnrcylxolxlnhhwnxyzltiscrjztiivnpnzlubzpueihinsqdfvypdteztiodbhaqhxskupwulvkzhczdyoouym";
        mat = soln.prepareNextIdxMat(strIn);
        vector<string> matchingSubseqs = {
                "hhwnxyzltiscrjztiivnpnzlubzpueihinsqdfvyp",
                "vnpnzlubzpueihinsqdfvypdteztiodbha",
                "rcnrcylxolxlnhhwnxyzltiscrjztiivnpnzlubzpueihi",
                "dfvypdteztiodbhaqhxskupwulvk",
                "zltiscrjztii",
        };
        outExpected = true;
        for (auto it = matchingSubseqs.begin(); it != matchingSubseqs.end(); it++) {
            outComputed = soln.hasSubseq(strIn, mat, *it);
            assert(outExpected == outComputed);
        }

        vector<string> nonMatchingSubseqs = {
                "wdmbatbcewwittubryrqwwrvfkrmniomofygybeqfzusrgeart",
                "myzfexqmzxnbmmnhmpbddqhrwrobqzjiwdzzpyzodejysuuquc",
                "wxvrcbihbasohfvuwuxleesqeujxvjfvgwnhltenbspdgzsdrs",
                "nztyysfhfbfcihyeaqdarqxfpjunevabzafvbmpbtenarvyizv",
                "nivufheyodfjuggrbndyojeahrzgptikjfqufhwyhzyyjteahx"
        };
        outExpected = false;
        for (auto it = nonMatchingSubseqs.begin(); it != nonMatchingSubseqs.end(); it++) {
            outComputed = soln.hasSubseq(strIn, mat, *it);
            assert(outExpected == outComputed);
        }
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

//    solnTest.debugFillNextIdxMat();
    solnTest.testHasSubseq();

    return 0;
}
