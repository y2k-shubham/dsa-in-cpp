// LeetCode-1759: https://leetcode.com/problems/count-number-of-homogenous-substrings/
// pretty dumb permitations problem; better skip

#include <cstdio>
#include <iostream>

using namespace std;

#define MOD 1000000007

class Solution {
   private:
    int findSigmaN(int n) {
        long long prod = n;
        prod *= n + 1;
        prod /= 2;
        return (int)(prod % MOD);
    }

   public:
    int countHomogenous(string s) {
        int len = s.size();
        if (len <= 1) {
            return len;
        }

        long long numHomoStrs = 0;
        char prevChar = '\0';
        int crrSeqLen = 0;
        for (int i = 0; i < len; i++) {
            int crrChar = s.at(i);
            if (crrChar == prevChar) {
                crrSeqLen++;
            } else {
                if (i > 0) {
                    numHomoStrs += findSigmaN(crrSeqLen);
                    numHomoStrs %= MOD;
                    // printf("resetting at s(i=%d)=%c, prevSeqLen=%d, prevSeqSigmaN=%d, numHomoStrs=%d\n", i, crrChar, crrSeqLen, findSigmaN(crrSeqLen), numHomoStrs);
                }

                crrSeqLen = 1;
            }

            prevChar = crrChar;
        }

        numHomoStrs += findSigmaN(crrSeqLen);
        numHomoStrs %= MOD;

        return (int)(numHomoStrs % MOD);
    }
};
