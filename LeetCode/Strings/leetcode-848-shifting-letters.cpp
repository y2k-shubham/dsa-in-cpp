// LeetCode-848: https://leetcode.com/problems/shifting-letters/
/**
 * @author Shubham Gupta (y2k-shubham)
 * @brief works for following cases
 * "abc"
 * [3,5,9]
 * "aaa"
 * [1,2,3]
 * "aaa"
 * [14,26,5]
 * "aaa"
 * [52,26,0]
 * 
 * LC breaks for following case
 * (but locally this case is passing)
 * "ruu"
 * [26,9,17]
 * @date 2021-07-24
 */

#include <cassert>
#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    vector<int> buildSuffixSumMod(vector<int>& vec, int mod) {
        int len = vec.size();
        if (len == 0) {
            return {};
        }

        vector<int> suffixSum(len, 0);

        suffixSum[len - 1] = vec[len - 1] % mod;
        for (int i = len - 2; i >= 0; i--) {
            suffixSum[i] = (suffixSum[i + 1] + vec[i]) % mod;
        }

        return suffixSum;
    }

    char getShiftedChar(char c, int shift) {
        shift = shift % 26;
        if (shift == 0) {
            return c;
        }

        if (c == 'z') {
            c = 'a';
            shift--;
        }

        return (char)(c + shift);
    }

   public:
    friend class SolutionTest;

    string shiftingLetters(string s, vector<int>& shifts) {
        int len = s.size();
        if (len <= 0) {
            return s;
        }

        vector<int> shiftsSuffixSum = buildSuffixSumMod(shifts, 26);

        vector<char> sVec(s.begin(), s.end());

        vector<char> shiftedSVec(len);
        for (int i = 0; i < len; i++) {
            shiftedSVec[i] = getShiftedChar(s.at(i), shiftsSuffixSum[i]);
        }

        string shiftedS(shiftedSVec.begin(), shiftedSVec.end());
        return shiftedS;
    }
};

class SolutionTest {
   public:
    void testBuildSuffixSumMod() {
        Solution soln = Solution();
        vector<int> vecIn;
        int mod = 26;
        vector<int> vecOutExpected;
        vector<int> vecOutComputed;

        vecIn = {};
        vecOutExpected = {};
        vecOutComputed = soln.buildSuffixSumMod(vecIn, 26);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {4};
        vecOutExpected = {4};
        vecOutComputed = soln.buildSuffixSumMod(vecIn, 26);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {5, 4};
        vecOutExpected = {9, 4};
        vecOutComputed = soln.buildSuffixSumMod(vecIn, 26);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {5, 9, 0, 1};
        vecOutExpected = {15, 10, 1, 1};
        vecOutComputed = soln.buildSuffixSumMod(vecIn, 26);
        assert(vecOutExpected == vecOutComputed);

        vecIn = {26, 9, 17};
        vecOutExpected = {0, 0, 17};
        vecOutComputed = soln.buildSuffixSumMod(vecIn, 26);
        assert(vecOutExpected == vecOutComputed);
    }

    void testGetShifterChar() {
        Solution soln = Solution();
        char chIn;
        char shiftIn;
        char chOutExpected;
        char chOutComputed;

        chIn = 'a';
        shiftIn = 0;
        chOutExpected = 'a';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'a';
        shiftIn = 1;
        chOutExpected = 'b';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'a';
        shiftIn = 5;
        chOutExpected = '5';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'a';
        shiftIn = 25;
        chOutExpected = 'z';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'a';
        shiftIn = 26;
        chOutExpected = 'a';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'a';
        shiftIn = 27;
        chOutExpected = 'b';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'z';
        shiftIn = 0;
        chOutExpected = 'z';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'z';
        shiftIn = 2;
        chOutExpected = 'b';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'z';
        shiftIn = 26;
        chOutExpected = 'z';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);

        chIn = 'z';
        shiftIn = 27;
        chOutExpected = 'a';
        chOutComputed = soln.getShiftedChar(chIn, shiftIn);
    }

    void testShiftingLetters() {
        Solution soln = Solution();
        string strIn;
        vector<int> shiftsIn;
        string strOutExpected;
        string strOutComputed;

        strIn = "";
        shiftsIn = {};
        strOutExpected = "";
        strOutComputed = soln.shiftingLetters(strIn, shiftsIn);

        strIn = "";
        shiftsIn = {4};
        strOutExpected = "";
        strOutComputed = soln.shiftingLetters(strIn, shiftsIn);

        strIn = "a";
        shiftsIn = {4};
        strOutExpected = "e";
        strOutComputed = soln.shiftingLetters(strIn, shiftsIn);

        strIn = "abc";
        shiftsIn = {3, 5, 9};
        strOutExpected = "rpl";
        strOutComputed = soln.shiftingLetters(strIn, shiftsIn);

        strIn = "aaa";
        shiftsIn = {1, 2, 3};
        strOutExpected = "gfd";
        strOutComputed = soln.shiftingLetters(strIn, shiftsIn);

        // LC breaks on this case
        strIn = "ruu";
        shiftsIn = {26, 9, 17};
        strOutExpected = "rul";
        strOutComputed = soln.shiftingLetters(strIn, shiftsIn);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testBuildSuffixSumMod();
    solnTest.testGetShifterChar();
    solnTest.testShiftingLetters();

    return 0;
}
