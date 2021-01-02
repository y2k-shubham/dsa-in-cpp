// LeetCode-446: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Solution {
   private:
    int findNumArithmeticSubseqs(vector<int> vec, bool debug) {
        int len = vec.size();
        vector<map<int, int> > diffSubseqsEndingMemo(len);

        int numSubseqs = 0;
        for (int i = 1; i < len; i++) {
            if (debug) {
                printf("\n===========\nat vec[i=%d] = %d\n", i, vec[i]);
            }
            map<int, int> diffSubseqsEnding;

            for (int j = 0; j < i; j++) {
                int diff = vec[i] - vec[j];

                if (debug) {
                  printf("\nwith vec[j=%d] = %d, numSubseqs with diff = %d ending at j=%d is %d\n", j, vec[j], diff, j, diffSubseqsEndingMemo[j][diff]);
                  printf("so numSubseqs with diff = %d ending at i=%d becomes ");
                }

                diffSubseqsEnding[diff] = diffSubseqsEndingMemo[j][diff];
                if (diffSubseqsEnding[diff] >= 2) {
                    numSubseqs = numSubseqs + diffSubseqsEnding[diff];
                }
            }

            diffSubseqsEndingMemo[i] = diffSubseqsEnding;
        }

        return numSubseqs;
    }

   public:
    int numberOfArithmeticSlices(vector<int>& A) {
        return findNumArithmeticSubseqs(A, false);
    }

    friend class TestSolution;
};

class TestSolution {
   public:
    void testFindNumArithmeticSubseqs() {
        Solution soln = Solution();

        vector<int> vecIn;
        int outExpected;
        int outComputed;

        vecIn = {2, 4, 6, 8, 10};
        outExpected = 7;
        outComputed = soln.findNumArithmeticSubseqs(vecIn, true);
        assert(outExpected == outComputed);
    }
}
