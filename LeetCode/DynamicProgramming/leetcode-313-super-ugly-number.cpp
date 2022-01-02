// LeetCode-313: https://leetcode.com/problems/super-ugly-number/

#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showCrrState(
        vector<long long>& mVec,
        int crrInsertIdx,
        vector<int>& primes,
        unordered_map<int, int>& primeIdxMap) {
        printf("\nVec is:-\n");

        printf("Idx:\t");
        for (int i = 0; i < crrInsertIdx; i++) {
            printf("%d\t", (i + 1));
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < crrInsertIdx; i++) {
            printf("%lld\t", mVec[i]);
        }
        cout << endl;

        for (int p = 0; p < primes.size(); p++) {
            int crrPrime = primes[p];
            printf("%d\t", primes[p]);
            int crrPrimeIdx = primeIdxMap[crrPrime];

            for (int i = 0; i < crrPrimeIdx; i++) {
                printf("\t");
            }

            printf("^\n");
        }
    }

    map<long long, int> buildMultPrimeMap(vector<int>& primes) {
        map<long long, int> multPrimeMap;
        for (int i = 0; i < primes.size(); i++) {
            multPrimeMap[primes[i]] = primes[i];
        }

        return multPrimeMap;
    }

    unordered_map<int, int> buildPrimeIdxMap(vector<int>& primes) {
        unordered_map<int, int> primeIdxMap;
        for (int i = 0; i < primes.size(); i++) {
            primeIdxMap[primes[i]] = 0;
        }

        return primeIdxMap;
    }

   public:
    friend class SolutionTest;

    int nthSuperUglyNumber(int n, vector<int>& primes) {
        sort(primes.begin(), primes.end());
        int len = primes.size();

        if (len == 0) {
            // invalid input
            return 0;
        }
        if (n == 1) {
            // whenever n=1, then output=1 is fixed
            return 1;
        }
        if (len == 1) {
            return (int)pow(primes[0], (n - 1));
        }

        // this is mathematically wrong
        // if (n <= len) {
        //     if (debug) {
        //         printf("n=%d, len=%d, returning primes[%d-1]=primes[%d]=%d\n", n, len, n, (n - 1), primes[n - 1]);
        //     }
        //     return primes[n - 1];
        // }

        map<long long, int> multPrimeMap = buildMultPrimeMap(primes);

        vector<long long> mVec(n);
        mVec[0] = 1;
        int crrInsertIdx = 1;

        unordered_map<int, int> primeIdxMap = buildPrimeIdxMap(primes);

        // if (debug) {
        //     printf("going to execute loop\n");
        // }
        for (int i = 2; i <= n; i++) {
            if (debug) {
                printf("\n------\n");
                printf("determining multiple no i=%d\n", i);
            }

            // find smallest multiple (and corresponding prime no) from multPrimeMap;
            map<long long, int>::iterator mIt = multPrimeMap.begin();
            long long crrSmallestMultiple = mIt->first;
            int crrPrime = mIt->second;

            if (debug) {
                printf("\n");
                printf("prime=%d, multiple=%lld\n", crrPrime, crrSmallestMultiple);
            }

            // add smallest multiple to mList
            mVec[crrInsertIdx++] = crrSmallestMultiple;

            // determine next multiple of current 'prime' which we haven't already seen
            long long nextMultiple;
            do {
                // if (debug) {
                //     printf("puchi\n");
                // }

                // calculate next multiple of current prime
                nextMultiple = crrPrime * mVec[primeIdxMap[crrPrime]];
                // increment iterator of current prime
                primeIdxMap[crrPrime]++;
            } while (multPrimeMap.find(nextMultiple) != multPrimeMap.end());

            // update multiple of current prime
            multPrimeMap.erase(crrSmallestMultiple);
            multPrimeMap[nextMultiple] = crrPrime;
            if (debug) {
                printf("prime=%d, nextMultiple=%lld\n", crrPrime, nextMultiple);
                cout << endl;
                showCrrState(mVec, crrInsertIdx, primes, primeIdxMap);
            }
        }

        return (int) *mVec.rbegin();
    }
};

class SolutionTest {
   public:
    void testNthSuperUglyNumber() {
        Solution soln = Solution();
        vector<int> primesIn;
        int nIn;
        int nOutExpected, nOutComputed;

        primesIn = {};
        nIn = 9;
        nOutExpected = 0;
        nOutComputed = soln.nthSuperUglyNumber(nIn, primesIn);
        assert(nOutExpected == nOutComputed);

        primesIn = {2, 3, 5};
        nIn = 1;
        nOutExpected = 1;
        nOutComputed = soln.nthSuperUglyNumber(nIn, primesIn);
        assert(nOutExpected == nOutComputed);

        // soln.debug = true;
        primesIn = {2, 3, 5};
        nIn = 3;
        nOutExpected = 3;
        nOutComputed = soln.nthSuperUglyNumber(nIn, primesIn);
        assert(nOutExpected == nOutComputed);
        // soln.debug = false;

        // soln.debug = true;
        primesIn = {2, 7, 13, 19};
        nIn = 12;
        nOutExpected = 32;
        nOutComputed = soln.nthSuperUglyNumber(nIn, primesIn);
        assert(nOutExpected == nOutComputed);
        // soln.debug = false;

        primesIn = {2, 7, 13, 19};
        nIn = 12;
        nOutExpected = 32;
        nOutComputed = soln.nthSuperUglyNumber(nIn, primesIn);
        assert(nOutExpected == nOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testNthSuperUglyNumber();

    return 0;
}
