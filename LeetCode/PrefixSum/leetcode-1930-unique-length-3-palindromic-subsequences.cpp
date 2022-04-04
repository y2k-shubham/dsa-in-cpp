// LeetCode-1930: https://leetcode.com/problems/unique-length-3-palindromic-subsequences/

#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <utility>

using namespace std;

#define BEGIN_CHAR 'a'
#define END_CHAR 'z'
#define NUM_CHARS 26

class Solution {
private:
    vector <vector <bool> > coveredCharPairsMat;
    vector <bool> midCharCoverageVec;
    vector <vector <int> > charFreqPrefSumMat;
    vector <vector <int> > charFreqSuffSumMat;
    unordered_set<string> subseqStrSet;

    void createCoveredCharPairsMat() {
        vector <vector <bool> > coveredCharPairsMat(NUM_CHARS);
        for (char ch = BEGIN_CHAR; ch <= END_CHAR; ch++) {
            vector <bool> coveredCharPairsVec(NUM_CHARS, false);
            coveredCharPairsMat[ch - BEGIN_CHAR] = coveredCharPairsVec;
        }

        this->coveredCharPairsMat = coveredCharPairsMat;
    }

    void createMidCharCoverageVec() {
        vector <bool> midCharCoverageVec(NUM_CHARS, false);
        this->midCharCoverageVec = midCharCoverageVec;
    }

    string createSubseqStr(ostringstream& oss, char side, char mid) {
        oss.str("");
        oss << side << mid << side;
        return oss.str();
    }

    vector <int> buildCharFreqPrefSumVec(string& str, char ch) {
        int len = str.size();
        if (len <= 0) {
            return {};
        }

        vector <int> charFreqPrefSumVec(len);
        if (str.at(0) == ch) {
            charFreqPrefSumVec[0] = 1;
        }

        for (int i = 1; i < len; i++) {
            charFreqPrefSumVec[i] = charFreqPrefSumVec[i - 1];
            if (str.at(i) == ch) {
                charFreqPrefSumVec[i]++;
            }
        }

        return charFreqPrefSumVec;
    }

    vector <vector <int> > buildCharFreqPrefSumMat(string& str) {
        vector <vector <int>> charFreqPrefSumMat(NUM_CHARS);
        for (char ch = BEGIN_CHAR; ch <= END_CHAR; ch++) {
            charFreqPrefSumMat[ch - BEGIN_CHAR] = buildCharFreqPrefSumVec(str, ch);
        }

        return charFreqPrefSumMat;
    }

    vector <int> buildCharFreqSuffSumVec(string& str, char ch) {
        int len = str.size();
        if (len <= 0) {
            return {};
        }

        vector <int> charFreqSuffSumVec(len);
        if (str.at(len - 1) == ch) {
            charFreqSuffSumVec[len - 1] = 1;
        }

        for (int i = len - 2; i >= 0; i--) {
            charFreqSuffSumVec[i] = charFreqSuffSumVec[i + 1];
            if (str.at(i) == ch) {
                charFreqSuffSumVec[i]++;
            }
        }

        return charFreqSuffSumVec;
    }

    vector <vector <int> > buildCharFreqSuffSumMat(string& str) {
        vector <vector <int>> charFreqSuffSumMat(NUM_CHARS);
        for (char ch = BEGIN_CHAR; ch <= END_CHAR; ch++) {
            charFreqSuffSumMat[ch - BEGIN_CHAR] = buildCharFreqSuffSumVec(str, ch);
        }

        return charFreqSuffSumMat;
    }

public:
    int countPalindromicSubsequence(string s) {
        createCoveredCharPairsMat();
        createMidCharCoverageVec();

        this->charFreqPrefSumMat = buildCharFreqPrefSumMat(s);
        this->charFreqSuffSumMat = buildCharFreqSuffSumMat(s);

        ostringstream oss;
        int len = s.size();

        for (int i = 1; i <= (len - 2); i++) {
            char midChar = s.at(i);
            if (midCharCoverageVec[midChar - BEGIN_CHAR]) {
                continue;
            }

            int numCoveredSideChars = 0;
            for (char sideChar = BEGIN_CHAR; sideChar <= END_CHAR; sideChar++) {
                // this is not needed because 'aaa' (side-char='a', mid-char='a')
                // could also be valid palindromic subseq
//                if (sideChar == midChar) {
//                    numCoveredSideChars++;
//                    continue;
//                }
                if (coveredCharPairsMat[midChar - BEGIN_CHAR][sideChar - BEGIN_CHAR]) {
                    numCoveredSideChars++;
                    continue;
                }

                bool occursBefore = charFreqPrefSumMat[sideChar - BEGIN_CHAR][i - 1] > 0;
                bool occursAfter = charFreqSuffSumMat[sideChar - BEGIN_CHAR][i + 1] > 0;
                if (occursBefore && occursAfter) {
                    string subseqStr = createSubseqStr(oss, sideChar, midChar);
                    subseqStrSet.insert(subseqStr);

                    coveredCharPairsMat[midChar - BEGIN_CHAR][sideChar - BEGIN_CHAR] = true;
                    numCoveredSideChars++;
                }
            }

            if (numCoveredSideChars == NUM_CHARS) {
                midCharCoverageVec[midChar - BEGIN_CHAR] = true;
            }
        }

        return subseqStrSet.size();
    }
};
