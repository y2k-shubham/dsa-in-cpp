// LeetCode-923: https://leetcode.com/problems/3sum-with-multiplicity/
// AlgorithmsMadeEasy: https://www.youtube.com/watch?v=jZcAldZP1ag
// optimized soln below is incomplete (gives wrong answer)

#include <vector>

using namespace std;

#define MOD 1000000007
#define MAX_NUM 100
#define MAX_2_NUM_SUM 200

class Solution {
private:
    // time O(n^2); space O(n)
    // not super easy to write bug-free
    int method1(vector<int>& vec, int target) {
        long long numTuples = 0;

        int len = vec.size();
        for (int i = 0; i < len; i++) {
            int eleI = vec[i];
            vector<int> numFreqVec(MAX_NUM + 1, 0);
            for (int j = i + 1; j < len; j++) {
                int eleJ = vec[j];

                int delta = target - (eleI + eleJ);
                if ((delta >= 0) && (delta <= MAX_NUM)) {
                    numTuples += numFreqVec[delta];
                }

                numFreqVec[eleJ]++;
            }
        }

        return (int) (numTuples % MOD);
    }

    vector<int> buildFreqVec(vector<int>& vec) {
        vector <int> freqVec(MAX_NUM + 1, 0);
        for (int i = 0; i < vec.size(); i++) {
            freqVec[vec[i]]++;
        }

        return freqVec;
    }

    long long hcf(long long big, long long small) {
        long long rem = big % small;
        if (rem == 0) {
            return small;
        }

        return hcf(small, rem);
    }

    long long nCr(long long n, long long r) {
        r = min(r, n - r);

        long long numr = 1;
        long long denr = 1;
        while (r >= 1) {
            numr *= n;
            denr *= r;

            long long gcd = hcf(numr, denr);
            numr /= gcd;
            denr /= gcd;

            n--;
            r--;
        }

        return numr / denr;
    }

    // incomplete (wrong answer)
    int method2(vector<int>& vec, int target) {
        vector <int> freqVec = buildFreqVec(vec);

        long long numTuples = 0;
        for (int i = 0; i < MAX_NUM; i++) {
            int eleI = i;
            long long freqEleI = freqVec[eleI];
            if (freqEleI <= 0) {
                continue;
            }
            long long freqEleIC3 = nCr(freqEleI, 3);
            long long freqEleIC2 = nCr(freqEleI, 2);

            // note that j starts with i itself
            for (int j = i; j < MAX_NUM; j++) {
                int eleJ = j;
                long long freqEleJ = freqVec[eleJ];
                if (freqEleJ <= 0) {
                    continue;
                }

                int delta = target - (eleI + eleJ);
                if ((delta < 0) || (delta > MAX_NUM)) {
                    continue;
                }
                long long freqDelta = freqVec[delta];
                if (freqDelta <= 0) {
                    continue;
                }

                if ((eleI == eleJ) && (eleJ == delta)) {
                    if (freqEleI >= 3) {
                        numTuples += freqEleIC3;
                    }
                } else if ((eleI == eleJ) && (eleJ != delta)) {
                    if (freqEleI >= 2) {
                        numTuples += freqEleIC2 * freqDelta;
                    }

                    // following if-expression is difficult to come up with
                } else if ((eleI < eleJ) && (eleJ < delta)) {
                    numTuples += freqEleI * freqEleJ * freqDelta;
                }
            }
        }

        return (int) (numTuples % MOD);
    }

public:
    int threeSumMulti(vector<int>& arr, int target) {
        return method1(arr, target);
    }
};
