// LeetCode-875: https://leetcode.com/problems/koko-eating-bananas/

#include <numeric>
#include <vector>
#include <cassert>
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
private:
    bool debug;

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

    void showVec(vector<int>& vec, string name) {
        int len = vec.size();
        printf("%s vec is:-\n", name.c_str());

        printf("Idx:\t");
        for (int i = 0; i < len; i++) {
            printf("[%d]\t", i);
        }
        cout << endl;

        printf("Val:\t");
        for (int i = 0; i < len; i++) {
            printf("%d\t", vec[i]);
        }
        cout << endl;
    }

    bool isPossibleK(vector<int>& sortedPiles, int maxAvailableH, int k) {
        int len = sortedPiles.size();
        if (k >= sortedPiles[len - 1]) {
            return true;
        }

        // if (debug) {
        //     printf("\n========\n");
        //     printf("trying out k=%d; maxAvailableH=%d\n", k, maxAvailableH);
        //     printf("\n========\n");
        // }

        long long crrTotalH = 0;
        for (int i = len - 1; i >= 0; i--) {
            long long crrPileH = (long long) ceil((sortedPiles[i] * 1.0) / k);
            crrTotalH += crrPileH;

            // if (debug) {
            //     printf("\n--------\n");
            //     printf("at sortedPiles[i=%d] = %d\n", i, sortedPiles[i]);
            //     printf("crrPileH = ceil(%d / %d) = %d\n", sortedPiles[i], k, crrPileH);
            //     printf("crrTotalH = %lld\n", crrTotalH);
            // }

            int remPiles = i;
            int remHours = maxAvailableH - crrTotalH;
            // if (debug) {
            //     printf("remPiles = (i=%d + 1) = %d\n", i, remPiles);
            //     printf("remHours = (maxAvailableH=%d - crrTotalH=%d) = %d\n", maxAvailableH, crrTotalH, remHours);
            // }
            if (remPiles > remHours) {
                // if (debug) {
                //     printf("returning false\n");
                // }
                return false;
            }
        }

        return true;
    }

public:
    friend class SolutionTest;

    int minEatingSpeed(vector<int>& piles, int h) {
        sort(piles.begin(), piles.end());

        int len = piles.size();
        long long maxK = piles[len - 1];
        if (h <= len) {
            return maxK;
        }

        long long totalBananas = accumulate(piles.begin(), piles.end(), 0L);
        if (totalBananas <= h) {
            return 1;
        }

        long long minK = (long long) ceil((totalBananas * 1.0) / h);

        long long kAns = maxK;
        long long kLo = minK, kHi = maxK;
        while (kLo <= kHi) {
            long long midK = (kLo + kHi) / 2;

            if (debug) {
                printf("\n////////\n");
                printf("kLo=%d, kHi=%d; trying out midK=%d\n", kLo, kHi, midK);
                printf("\n////////\n");
            }

            if (isPossibleK(piles, h, midK)) {
                kAns = min(kAns, midK);
                if (debug) {
                    printf("possible; updated kAns=%d\n", kAns);
                }
                kHi = midK - 1;
            } else {
                if (debug) {
                    printf("not possible\n");
                }
                kLo = midK + 1;
            }
        }

        return kAns;
    }
};

class SolutionTest {
public:
    void testIsPossibleK() {
        Solution soln = Solution();
        vector <int> sortedPilesIn;
        int hMaxIn, kIn;
        bool outExpected, outComputed;

        sortedPilesIn = {3, 6, 7, 11};
        hMaxIn = 8;
        kIn = 3;
        outExpected = false;
        outComputed = soln.isPossibleK(sortedPilesIn, hMaxIn, kIn);
        assert(outExpected == outComputed);

        // soln.enableDebug();
        // soln.showVec(sortedPilesIn, "piles");
        sortedPilesIn = {3, 6, 7, 11};
        hMaxIn = 8;
        kIn = 4;
        outExpected = true;
        outComputed = soln.isPossibleK(sortedPilesIn, hMaxIn, kIn);
        assert(outExpected == outComputed);
        // soln.disableDebug();

        sortedPilesIn = {4, 11, 20, 23, 30};
        hMaxIn = 5;
        kIn = 29;
        outExpected = false;
        outComputed = soln.isPossibleK(sortedPilesIn, hMaxIn, kIn);
        assert(outExpected == outComputed);

        sortedPilesIn = {4, 11, 20, 23, 30};
        hMaxIn = 5;
        kIn = 30;
        outExpected = true;
        outComputed = soln.isPossibleK(sortedPilesIn, hMaxIn, kIn);
        assert(outExpected == outComputed);

        sortedPilesIn = {4, 11, 20, 23, 30};
        hMaxIn = 6;
        kIn = 22;
        outExpected = false;
        outComputed = soln.isPossibleK(sortedPilesIn, hMaxIn, kIn);
        assert(outExpected == outComputed);

        sortedPilesIn = {4, 11, 20, 23, 30};
        hMaxIn = 6;
        kIn = 23;
        outExpected = true;
        outComputed = soln.isPossibleK(sortedPilesIn, hMaxIn, kIn);
        assert(outExpected == outComputed);

        // soln.enableDebug();
        sortedPilesIn = {1000000000, 1000000000};
        // soln.showVec(sortedPilesIn, "piles");
        hMaxIn = 3;
        kIn = 999999981;
        outExpected = false;
        outComputed = soln.isPossibleK(sortedPilesIn, hMaxIn, kIn);
        assert(outExpected == outComputed);
        // soln.disableDebug();
    }

    void testMinEatingSpeed() {
        Solution soln = Solution();
        vector <int> pilesIn;
        int hIn;
        int kOutExpected, kOutComputed;

        // soln.enableDebug();
        pilesIn = {3, 6, 7, 11};
        // soln.showVec(pilesIn, "piles");
        hIn = 8;
        kOutExpected = 4;
        kOutComputed = soln.minEatingSpeed(pilesIn, hIn);
        // printf("kOutComputed: %d\n", kOutComputed);
        assert(kOutExpected == kOutComputed);
        // soln.disableDebug();

        pilesIn = {30,11,23,4,20};
        hIn = 5;
        kOutExpected = 30;
        kOutComputed = soln.minEatingSpeed(pilesIn, hIn);
        assert(kOutExpected == kOutComputed);

        pilesIn = {30,11,23,4,20};
        hIn = 6;
        kOutExpected = 23;
        kOutComputed = soln.minEatingSpeed(pilesIn, hIn);
        assert(kOutExpected == kOutComputed);

        pilesIn = {332484035,524908576,855865114,632922376,222257295,690155293,112677673,679580077,337406589,290818316,877337160,901728858,679284947,688210097,692137887,718203285,629455728,941802184};
        hIn = 823855818;
        kOutExpected = 14;
        kOutComputed = soln.minEatingSpeed(pilesIn, hIn);
        assert(kOutExpected == kOutComputed);

        // soln.enableDebug();
        pilesIn = {1000000000,1000000000};
        // soln.showVec(pilesIn, "piles");
        hIn = 3;
        kOutExpected = 1000000000;
        kOutComputed = soln.minEatingSpeed(pilesIn, hIn);
        assert(kOutExpected == kOutComputed);
        // soln.disableDebug();
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testIsPossibleK();
    solnTest.testMinEatingSpeed();

    return 0;
}
