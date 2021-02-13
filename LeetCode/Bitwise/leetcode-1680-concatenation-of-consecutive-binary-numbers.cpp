// LeetCode-1680: https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/
// LC Jan 2021 challenge: https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/582/week-4-january-22nd-january-28th/3618/

#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

#define MOD 1000000007

class Solution {
   public:
    int getNumBits(int n) {
        // ref: https://stackoverflow.com/questions/3064926/how-to-write-log-base2-in-c-c#comment26409985_3065433

        int numBits = 1;
        while (n >>= 1) {
            numBits++;
        }

        return numBits;
    }

    int fuseN(int prod, int n) {
        int numBits = getNumBits(n);

        for (int i = numBits; i > 0; i--) {
            prod = prod << 1;
            // note that here we are shifting (and then un-shifting) by 'i - 1' & not 'i'
            // (this is one of those off-by-one errors)
            prod = prod | (((1 << (i - 1)) & n) >> (i - 1));
            prod = prod % MOD;
        }

        return prod;
    }

    int concatenatedBinary(int n) {
        if (n == 1) {
            return 1;
        }

        int prod = 1;
        for (int i = 2; i <= n; i++) {
            prod = fuseN(prod, i);
        }

        return prod;
    }
};
