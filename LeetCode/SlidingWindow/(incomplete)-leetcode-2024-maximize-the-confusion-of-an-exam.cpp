// LeetCode-2024: https://leetcode.com/problems/maximize-the-confusion-of-an-exam/
// incomplete

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    string str;
    int len;
    int k;
    int totalFs;
    int totalTs;
    vector <int>& consecPrefSumF;
    vector <int>& consecSuffSumF;
    vector <int>& consecPrefSumT;
    vector <int>& consecSuffSumT;

    vector<int> buildConsecPrefixSumVec(string &str, char ch) {
        int len = str.size();

        vector<int> prefSum(len, 0);
        int crrSum = 0;
        for (int i = 0; i < len; i++) {
            if (str.at(i) == ch) {
                crrSum += 1;
            } else {
                crrSum = 0;
            }

            prefSum[i] = crrSum;
        }

        return prefSum;
    }

    vector<int> buildConsecSuffixSumVec(string &str, char ch) {
        int len = str.size();

        vector<int> suffSum(len, 0);
        int crrSum = 0;
        for (int i = len - 1; i >= 0; i--) {
            if (str.at(i) == ch) {
                crrSum += 1;
            } else {
                crrSum = 0;
            }

            suffSum[i] = crrSum;
        }

        return suffSum;
    }

    int countTotalChars(string& str, char ch) {
        int sum = 0;

        for (auto it = str.begin(); it != str.end(); it++) {
            if (*it == ch) {
                sum++;
            }
        }

        return sum;
    }

    int advanceWindow() {
        char reqChar,
        vector<int>& crrCharPrefSum,
        vector<int>& crrCharSuffSum,
        int idxBegin,
        int idxEnd
    } {
        int crrOtherChars = 0;
    }
    
    int findMaxConsec(
            char reqChar,
            vector<int>& crrCharPrefSum,
            vector<int>& crrCharSuffSum
    ) {
        int len = str.size();

        int maxConseqChars = 0;
        int iLo = 0;
        int iHi = 0;

        // advance iHi till window has at least 'k' other chars
        int numOtherChars = 0;
        while ((iHi < len) && (numOtherChars < k)) {
            char ch = str.at(iHi);
            if (ch != reqChar) {
                numOtherChars++;
            }

            iHi++;
        }

        if (iHi == len) {
            return len;
        } else {
            int windowLen = iHi - iLo + 1;
            int numCharsRight = crrCharSuffSum[iHi + 1];
            int crrWindowConseqChars = windowLen + numCharsRight;
            maxConseqChars = max(maxConseqChars, crrWindowConseqChars);
        }

        // move (re-sizing) sliding window to keep 'k' other chars in window

    }

public:
    friend class SolutionTest;

    Solution() {

    }

    int maxConsecutiveAnswers(string answerKey, int k) {
        this->str = answerKey;
        this->len = str.size();
        this->k = k;

        this->consecPrefSumF = buildConsecPrefixSumVec(str, 'F');
        this->consecSuffSumF = buildConsecSuffixSumVec(str, 'F');
        this->consecPrefSumT = buildConsecPrefixSumVec(str, 'T');
        this->consecSuffSumT = buildConsecSuffixSumVec(str, 'T');

        this->totalFs = countTotalChars(str, 'F');
        this->totalTs = countTotalChars(str, 'T');
    }
};

class SolutionTest {
public:
    void testbuildConsecPrefixSumVec() {
        Solution soln = Solution();
        string strIn;
        char chIn;
        vector<int> prefSumOutExpected;
        vector<int> prefSumOutComputed;

        strIn = "";
        chIn = '\0';
        prefSumOutExpected = {};
        prefSumOutComputed = soln.buildConsecPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);

        strIn = "F";
        chIn = 'F';
        prefSumOutExpected = {1};
        prefSumOutComputed = soln.buildConsecPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);

        strIn = "F";
        chIn = 'T';
        prefSumOutExpected = {0};
        prefSumOutComputed = soln.buildConsecPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);

        strIn = "TFTT";
        chIn = 'T';
        prefSumOutExpected = {1, 0, 1, 2};
        prefSumOutComputed = soln.buildConsecPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);

        strIn = "TFTFFTF";
        chIn = 'F';
        prefSumOutExpected = {0, 1, 0, 1, 2, 0, 1};
        prefSumOutComputed = soln.buildConsecPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);
    }

    void testbuildConsecSuffixSumVec() {
        Solution soln = Solution();
        string strIn;
        char chIn;
        vector<int> suffSumOutExpected;
        vector<int> suffSumOutComputed;

        strIn = "";
        chIn = '\0';
        suffSumOutExpected = {};
        suffSumOutComputed = soln.buildConsecSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);

        strIn = "F";
        chIn = 'F';
        suffSumOutExpected = {1};
        suffSumOutComputed = soln.buildConsecSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);

        strIn = "F";
        chIn = 'T';
        suffSumOutExpected = {0};
        suffSumOutComputed = soln.buildConsecSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);

        strIn = "TFTT";
        chIn = 'T';
        suffSumOutExpected = {1, 0, 2, 1};
        suffSumOutComputed = soln.buildConsecSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);

        strIn = "TFTFFTF";
        chIn = 'F';
        suffSumOutExpected = {0, 1, 0, 2, 1, 0, 1};
        suffSumOutComputed = soln.buildConsecSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testbuildConsecPrefixSumVec();
    solnTest.testbuildConsecSuffixSumVec();

    return 0;
}
