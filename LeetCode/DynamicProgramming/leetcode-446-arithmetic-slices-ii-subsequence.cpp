// LeetCode-446: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/

#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <utility>
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

    void showMap(unordered_map<long long int, pair<int, int> > freqMap, string which) {
        printf("\n%s unordered_map is:-\n", which.c_str());

        for (unordered_map<long long int, pair<int, int> >::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            printf("[%lld] -> (len1=%d, len>1=%d)\n", (*it).first, (*it).second.first, (*it).second.second);
        }
    }

    // LeetCode: TLE using unordered_map & speed = 14 %tile using unordered_map (memory = 18 %tile)
    int findNumArithmeticSubseqs(vector<int> vec, bool debug) {
        int len = vec.size();
        vector<unordered_map<long long int, pair<int, int> > > diffSubseqsEndingMemo(len);

        int numTotalArithSubseqs = 0;
        for (int i = 1; i < len; i++) {
            if (debug) {
                printf("\n===========\n");
                showVec(vec, "vec");
                printf("\nat vec[i=%d] = %d\n", i, vec[i]);
            }
            unordered_map<long long int, pair<int, int> > diffSubseqsEnding;
            for (int j = 0; j < i; j++) {
                long long int diff = vec[i] - ((long long int)vec[j]);
                if (debug) {
                    printf("\n- - - - - - \n");
                    printf("with vec[j=%d] = %d, diff = %lld\n", j, vec[j], diff);
                }

                // length=1 diff subseqs
                int num1LenSubseqsCrrDiff = 0;

                // if (diffSubseqsEndingMemo[j].find(diff) != diffSubseqsEndingMemo[j].end()) {
                //     // all 1-len subseqs ending at j can also become 1-len subseqs ending at i
                //     num1LenSubseqsCrrDiff += diffSubseqsEndingMemo[j][diff].first;
                // }

                // vec[j], vec[i] will itself also be a 1-len subseq
                num1LenSubseqsCrrDiff += 1;

                diffSubseqsEnding[diff].first += num1LenSubseqsCrrDiff;

                if (debug) {
                    printf("num1LenSubseqsCrrDiff = %d, diffSubseqsEnding[diff=%lld].first = %d\n", num1LenSubseqsCrrDiff, diff, diffSubseqsEnding[diff].first);
                }

                // length>1 diff subseqs
                int numLongSubseqsCrrDiff = 0;

                if (diffSubseqsEndingMemo[j].find(diff) != diffSubseqsEndingMemo[j].end()) {
                    // all 1-len subseqs ending at j can also become 2 len subseqs ending at i
                    numLongSubseqsCrrDiff += diffSubseqsEndingMemo[j][diff].first;
                    // all > 1-len subeqs ending at j can also become > 1-len subseqs ending at i
                    numLongSubseqsCrrDiff += diffSubseqsEndingMemo[j][diff].second;

                    if (debug) {
                        printf("no of   1-len subseqs ending at vec[j=%d] = %d contributing = %d\n", j, vec[j], diffSubseqsEndingMemo[j][diff].first);
                        printf("no of > 1-len subseqs ending at vec[j=%d] = %d contributing = %d\n", j, vec[j], diffSubseqsEndingMemo[j][diff].second);
                    }
                }

                if (debug) {
                    printf("adding numLongSubseqsCrrDiff = %d to diffSubseqsEnding[diff=%lld].second = %d to make %d\n", numLongSubseqsCrrDiff, diff, diffSubseqsEnding[diff].second, (diffSubseqsEnding[diff].second + numLongSubseqsCrrDiff));
                }

                diffSubseqsEnding[diff].second += numLongSubseqsCrrDiff;
                // update no of 3+ len subseqs
                numTotalArithSubseqs += numLongSubseqsCrrDiff;

                if (debug) {
                    printf("numLongSubseqsCrrDiff = %d, diffSubseqsEnding[diff=%lld].second = %d\n", numLongSubseqsCrrDiff, diff, diffSubseqsEnding[diff].second);
                    printf("\nnumTotalArithSubseqs = %d\n", numTotalArithSubseqs);
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
        outComputed = soln.findNumArithmeticSubseqs(vecIn, false);
        // cout << outComputed << endl;
        assert(outExpected == outComputed);

        vecIn = {0, 2000000000, -294967296};
        outExpected = 0;
        outComputed = soln.findNumArithmeticSubseqs(vecIn, false);
        // cout << outComputed << endl;
        assert(outExpected == outComputed);

        vecIn = {1, 1, 1, 1};
        outExpected = 5;
        outComputed = soln.findNumArithmeticSubseqs(vecIn, false);
        // cout << outComputed << endl;
        assert(outExpected == outComputed);
    }
};

int main() {
    TestSolution testSoln = TestSolution();
    testSoln.testFindNumArithmeticSubseqs();

    return 0;
}
