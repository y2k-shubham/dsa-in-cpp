// LeetCode-2024: https://leetcode.com/problems/maximize-the-confusion-of-an-exam/
// incomplete

#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

class Solution {
private:
    vector<int> buildPrefixSumVec(string &str, char ch) {
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

    vector<int> buildSuffixSumVec(string &str, char ch) {
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

    int findMaxConsec(
            string& str,
            int k,
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

    int maxConsecutiveAnswers(string answerKey, int k) {

    }
};

class SolutionTest {
public:
    void testBuildPrefixSumVec() {
        Solution soln = Solution();
        string strIn;
        char chIn;
        vector<int> prefSumOutExpected;
        vector<int> prefSumOutComputed;

        strIn = "";
        chIn = '\0';
        prefSumOutExpected = {};
        prefSumOutComputed = soln.buildPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);

        strIn = "F";
        chIn = 'F';
        prefSumOutExpected = {1};
        prefSumOutComputed = soln.buildPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);

        strIn = "F";
        chIn = 'T';
        prefSumOutExpected = {0};
        prefSumOutComputed = soln.buildPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);

        strIn = "TFTT";
        chIn = 'T';
        prefSumOutExpected = {1, 0, 1, 2};
        prefSumOutComputed = soln.buildPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);

        strIn = "TFTFFTF";
        chIn = 'F';
        prefSumOutExpected = {0, 1, 0, 1, 2, 0, 1};
        prefSumOutComputed = soln.buildPrefixSumVec(strIn, chIn);
        assert(prefSumOutExpected == prefSumOutComputed);
    }

    void testBuildSuffixSumVec() {
        Solution soln = Solution();
        string strIn;
        char chIn;
        vector<int> suffSumOutExpected;
        vector<int> suffSumOutComputed;

        strIn = "";
        chIn = '\0';
        suffSumOutExpected = {};
        suffSumOutComputed = soln.buildSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);

        strIn = "F";
        chIn = 'F';
        suffSumOutExpected = {1};
        suffSumOutComputed = soln.buildSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);

        strIn = "F";
        chIn = 'T';
        suffSumOutExpected = {0};
        suffSumOutComputed = soln.buildSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);

        strIn = "TFTT";
        chIn = 'T';
        suffSumOutExpected = {1, 0, 2, 1};
        suffSumOutComputed = soln.buildSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);

        strIn = "TFTFFTF";
        chIn = 'F';
        suffSumOutExpected = {0, 1, 0, 2, 1, 0, 1};
        suffSumOutComputed = soln.buildSuffixSumVec(strIn, chIn);
        assert(suffSumOutExpected == suffSumOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildPrefixSumVec();
    solnTest.testBuildSuffixSumVec();

    return 0;
}
