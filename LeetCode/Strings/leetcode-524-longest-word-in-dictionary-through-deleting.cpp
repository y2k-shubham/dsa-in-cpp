// LeetCode-524: https://leetcode.com/problems/longest-word-in-dictionary-through-deleting/
// optimal queries-based subsequence matching approach taken from LeetCode-792: https://github.com/y2k-shubham/dsa-in-cpp/blob/585eaccf6a367ae618cfc96d90375a432acc4dd6/LeetCode/Strings/leetcode-792-number-of-matching-subsequences.cpp

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

class LeetCode792Solution {
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
    friend class Solution;

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

class Solution {
public:
    friend class SolutionTest;

    string findLongestWord(string s, vector<string>& dictionary) {
        LeetCode792Solution lc792Soln = LeetCode792Solution();
        vector<vector<int> > mat = lc792Soln.prepareNextIdxMat(s);

        string longestMatchingWord = "";
        for (int i = 0; i < dictionary.size(); i++) {
            string crrWord = dictionary[i];
            if (lc792Soln.hasSubseq(s, mat, crrWord)) {
                if (crrWord.size() > longestMatchingWord.size()) {
                    longestMatchingWord = crrWord;
                } else if ((crrWord.size() == longestMatchingWord.size()) && (crrWord < longestMatchingWord)) {
                    longestMatchingWord = crrWord;
                }
            }
        }

        return longestMatchingWord;
    }
};

class SolutionTest {
public:
    void testFindLongestWord() {
        Solution soln = Solution();
        string strIn;
        vector<string> dictIn;
        string strOutExpected, strOutComputed;

        strIn = "abpcplea";
        dictIn = {"ale", "apple", "monkey", "plea"};
        strOutExpected = "apple";
        strOutComputed = soln.findLongestWord(strIn, dictIn);
        assert(strOutExpected == strOutComputed);

        strIn = "abpcplea";
        dictIn = {"ale", "apple", "monkey", "acpea", "plea"};
        strOutExpected = "acpea";
        strOutComputed = soln.findLongestWord(strIn, dictIn);
        assert(strOutExpected == strOutComputed);

        strIn = "abpcplea";
        dictIn = {"a", "b", "c"};
        strOutExpected = "a";
        strOutComputed = soln.findLongestWord(strIn, dictIn);
        assert(strOutExpected == strOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindLongestWord();

    return 0;
}

