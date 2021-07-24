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
 * breaks for following case
 * "ruu"
 * [26,9,17]
 * @date 2021-07-24
 */

#include <cstdio>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<int> buildSuffixSumMod(vector<int>& vec, int mod) {
        int len = vec.size();

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
    string shiftingLetters(string s, vector<int>& shifts) {
        int len = s.size();
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
