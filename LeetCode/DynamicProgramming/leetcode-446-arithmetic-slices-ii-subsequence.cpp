// LeetCode-446: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

using namespace std;

class Solution {
   private:
    void showVec(vector<int> vec, const char* name) {
        printf("\nVector %s is:-\n", name);

        printf("Ind:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < vec.size(); i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    void showMap(map<int, int> freqMap, string which) {
        printf("\n%s map is:-\n", which.c_str());

        for (map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            printf("[%d] -> %d\n", (*it).first, (*it).second);
        }
    }

    int findNumArithmeticSubseqs(vector<int> vec, bool debug) {
        int len = vec.size();
        vector<map<int, int> > diffSubseqsEndingMemo(len);

        int numTotalArithSubseqs = 0;
        for (int i = 1; i < len; i++) {
            if (debug) {
                printf("\n===========\n");
                showVec(vec, "vec");
                printf("\n---------\nat vec[i=%d] = %d\n", i, vec[i]);
            }
            map<int, int> diffSubseqsEnding;

            for (int j = 0; j < i; j++) {
                int diff = vec[i] - vec[j];
                int numSubseqsCrrDiff = 0;

                numSubseqsCrrDiff = max(1, diffSubseqsEndingMemo[j][diff]);
                diffSubseqsEnding[diff] = diffSubseqsEnding[diff] + numSubseqsCrrDiff;

                if (debug) {
                    printf("\nwith vec[j=%d] = %d, numTotalArithSubseqs with diff = %d ending at j=%d is %d\n", j, vec[j], diff, j, diffSubseqsEndingMemo[j][diff]);
                    printf("so numSubseqsCrrDiff with diff = %d ending at i=%d becomes %d\n", diff, i, numSubseqsCrrDiff);
                    printf("and diffSubseqsEnding[diff=%d] for i=%d becomes %d\n", diff, i, diffSubseqsEnding[diff]);
                }
            }

            if (debug) {
                ostringstream oss;
                oss << "diffs freqMap for vec[i=" << i << "] = " << vec[i];
                showMap(diffSubseqsEnding, oss.str());
            }
            diffSubseqsEndingMemo[i] = diffSubseqsEnding;
        }

        return numTotalArithSubseqs;
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
        cout << outComputed << endl;
        assert(outExpected == outComputed);
    }
};

int main() {
    TestSolution testSoln = TestSolution();
    testSoln.testFindNumArithmeticSubseqs();

    return 0;
}
