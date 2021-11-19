// LeetCode-1711: https://leetcode.com/problems/count-good-meals/
/**
 * not very easy
 *  - has some edge cases
 *  - involves a bit of combinatorics nCr (can also be classified as NumberTheory problem)
 *  - plus overflow (modulo result) is also a nuisance
 *
 * note that following 2 things require special handling (other things are intuitive)
 * 1. same no adding to pow of 2, like 4 + 4 = 8; so if we have n 4s, there will be nC2 ways of picking a pair of 4s from them
 * 2. to prevent each pair from being counted twice, we apply this neat trick that we skip computation if (diff > crrVal)
 */

#include <cassert>
#include <climits>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

#define MOD 1000000007

class Solution {
   private:
    bool debug;

    set<long long> buildPowerSet(int base, int maxPow) {
        set<long long> powerSet;
        for (int i = 0; i <= maxPow; i++) {
            powerSet.insert((long long)pow(base, i));
        }

        return powerSet;
    }

    unordered_map<int, int> buildFreqMap(vector<int>& vec) {
        unordered_map<int, int> freqMap;
        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    long long nCr(int n, int r) {
        int diff = n - r;
        if (diff < r) {
            return nCr(n, diff);
        }

        long long prod = 1;
        int i = 1;
        while (i <= r) {
            prod *= n;
            prod /= i;

            n--;
            i++;
        }

        return prod;
    }

   public:
    friend class SolutionTest;

    int countPairs(vector<int>& deliciousness) {
        int len = deliciousness.size();
        if (len <= 1) {
            return 0;
        }

        set<long long> powerSet = buildPowerSet(2, 41);
        unordered_map<int, int> freqMap = buildFreqMap(deliciousness);

        long long numPairs = 0;
        for (unordered_map<int, int>::iterator it1 = freqMap.begin(); it1 != freqMap.end(); it1++) {
            int crrVal = it1->first;
            int crrValFreq = it1->second;
            // if (crrVal == 0) {
            //     // had to skip zero (and handle separately because it was causing strange unexplained behaviour)
            //     continue;
            // }

            for (set<long long>::iterator it2 = powerSet.begin(); it2 != powerSet.end(); it2++) {
                long long diffLong = (int)(*it2 - crrVal);
                if (diffLong > INT_MAX) {
                    // this leverages the fact that powerSet is sorted
                    continue;
                }

                int diff = (int)diffLong;
                if (diff > crrVal) {
                    // this is done to avoid double counting of each pair (combination)
                    break;
                }

                if (diff == crrVal) {
                    // same no adding to power of 2; like 4 + 4 = 8
                    if (crrValFreq > 1) {
                        // ways to pick 2 values from n occurences of same no
                        long long combs = nCr(crrValFreq, 2);

                        if (this->debug) {
                            printf("found %d[%d] x 2 = %lld, adding %dC%d = %lld to answer=%lld to get %lld\n", crrVal, crrValFreq, *it2, crrValFreq, 2, combs, numPairs, (numPairs + combs));
                        }
                        numPairs += combs;
                    }
                } else if (freqMap.find(diff) != freqMap.end()) {
                    int diffFreq = freqMap[diff];
                    // if (diffFreq <= 0) {
                    //     continue;
                    // }

                    long long crrCombs = crrValFreq * ((long long)diffFreq);

                    if (this->debug) {
                        printf("found %d[%d] + %d[%d] = %lld, adding %lld to answer=%lld to get %lld\n", crrVal, crrValFreq, diff, diffFreq, *it2, crrCombs, numPairs, (numPairs + crrCombs));
                    }
                    numPairs += crrCombs;
                    // numPairs %= MOD;
                }
            }
        }

        // if (freqMap.find(0) != freqMap.end()) {
        //     int zeroFreq = freqMap[0];
        //     for (set<long long>::iterator it2 = powerSet.begin(); it2 != powerSet.end(); it2++) {
        //         long long powOf2Long = *it2;
        //         if (powOf2Long > INT_MAX) {
        //             break;
        //         }

        //         int powOf2 = (int)powOf2Long;
        //         if (freqMap.find(powOf2) != freqMap.end()) {
        //             numPairs += zeroFreq * freqMap[powOf2];
        //         }
        //     }
        // }

        return (int)(numPairs % MOD);
    }
};

class SolutionTest {
   public:
    void testCountPairs() {
        Solution soln = Solution();
        vector<int> inVec;
        int outExpected, outComputed;

        inVec = {};
        outExpected = 0;
        outComputed = soln.countPairs(inVec);
        assert(outExpected == outComputed);

        inVec = {3};
        outExpected = 0;
        outComputed = soln.countPairs(inVec);
        assert(outExpected == outComputed);

        inVec = {1, 3, 5, 7, 9};
        outExpected = 4;
        outComputed = soln.countPairs(inVec);
        assert(outExpected == outComputed);

        // soln.debug = true;
        inVec = {1, 1, 1, 3, 3, 3, 7};
        outExpected = 15;
        outComputed = soln.countPairs(inVec);
        assert(outExpected == outComputed);
        // soln.debug = false;

        inVec = {1, 1, 2};
        outExpected = 1;
        outComputed = soln.countPairs(inVec);
        assert(outExpected == outComputed);

        inVec = {1, 3, 5, 8};
        outExpected = 2;
        outComputed = soln.countPairs(inVec);
        assert(outExpected == outComputed);

        // soln.debug = true;
        inVec = {1, 3, 0, 5, 8, 0};
        outExpected = 6;
        outComputed = soln.countPairs(inVec);
        // cout << outComputed << endl;
        assert(outExpected == outComputed);
        // soln.debug = false;

        inVec = {2160, 1936, 3, 29, 27, 5, 2503, 1593, 2, 0, 16, 0, 3860, 28908, 6, 2, 15, 49, 6246, 1946, 23, 105, 7996, 196, 0, 2, 55, 457, 5, 3, 924, 7268, 16, 48, 4, 0, 12, 116, 2628, 1468};
        outExpected = 53;
        outComputed = soln.countPairs(inVec);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testCountPairs();

    return 0;
}
