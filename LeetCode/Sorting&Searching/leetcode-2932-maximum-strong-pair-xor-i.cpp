// LeetCode-2932: https://leetcode.com/problems/maximum-strong-pair-xor-i/
// straightforward; should skip seeing

#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

using namespace std;

class Solution {
private:
    bool debug = false;

    vector<int> getSortedDedupedVec(vector<int>& vec) {
        if (vec.empty()) {
            return {};
        }

        set<int> setVec(vec.begin(), vec.end());
        vector<int> sortedVec(setVec.begin(), setVec.end());
//        sort(sortedVec.begin(), sortedVec.end());
        return sortedVec;
    }

    int findMaxXORForPair(vector<int>& vec, int idx) {
        int maxXor = 0;

        int eleIdx = vec[idx];
        if (debug) {
            printf("\tDetermining maxXOR for vec[idx=%d] = %d\n", idx, eleIdx);
        }

        for (int i = idx - 1; (i >= 0) && ((2 * vec[i]) >= eleIdx); i--) {
            int currXor = eleIdx ^ vec[i];
            if (debug) {
                printf("\t\tAt vec[i=%d] = %d, currXor = %d\n", i, vec[i], currXor);
            }

            maxXor = max(maxXor, currXor);
        }

        if (debug) {
            printf("\tmaxXOR = %d\n", maxXor);
        }

        return maxXor;
    }

    void enableDebug() {
        debug = true;
    }

    void disableDebug() {
        debug = false;
    }

public:
    friend class SolutionTest;

    int maximumStrongPairXor(vector<int>& numVec) {
        vector<int> sortedVec = getSortedDedupedVec(numVec);

        int maxPairXor = 0;
        for (int i = 0; i < sortedVec.size(); i++) {
            if (debug) {
                printf("----------------\n");
            }

            int currPairXor = findMaxXORForPair(sortedVec, i);
            if (debug) {
                printf("At sortedVec[i=%d] = %d, currPairXor=%d\n", i, sortedVec[i], currPairXor);
                printf("----------------\n");
            }

            maxPairXor = max(maxPairXor, currPairXor);
        }

        return maxPairXor;
    }
};

class SolutionTest {
public:
    void testGetSortedDedupedVec() {
        Solution soln = Solution();
        vector<int> vecIn;
        vector<int> sortedDedupedVecOutExpected, sortedDedupedVecOutComputed;

        vecIn = {};
        sortedDedupedVecOutExpected = {};
        sortedDedupedVecOutComputed = soln.getSortedDedupedVec(vecIn);
        assert(sortedDedupedVecOutComputed == sortedDedupedVecOutExpected);

        vecIn = {5, 3, 4, 3, 1, 2, 1, 6};
        sortedDedupedVecOutExpected = {1, 2, 3, 4, 5, 6};
        sortedDedupedVecOutComputed = soln.getSortedDedupedVec(vecIn);
        assert(sortedDedupedVecOutComputed == sortedDedupedVecOutExpected);

        printf("[testGetSortedDedupedVec] All test cases passed.\n");
    }

    void testMaximumStrongPairXor() {
        Solution soln = Solution();
        vector<int> vecIn;
        int maxPairXorOutExpected, maxPairXorOutComputed;

        vecIn = {1, 2, 3, 4, 5};
        maxPairXorOutExpected = 7;
        maxPairXorOutComputed = soln.maximumStrongPairXor(vecIn);
        assert(maxPairXorOutComputed == maxPairXorOutExpected);

        vecIn = {10, 100};
        maxPairXorOutExpected = 0;
        maxPairXorOutComputed = soln.maximumStrongPairXor(vecIn);
        assert(maxPairXorOutComputed == maxPairXorOutExpected);

        vecIn = {5, 6, 25, 30};
        maxPairXorOutExpected = 7;
        maxPairXorOutComputed = soln.maximumStrongPairXor(vecIn);
        assert(maxPairXorOutComputed == maxPairXorOutExpected);

//        soln.enableDebug();
        vecIn = {1, 1, 2, 3, 5};
        maxPairXorOutExpected = 6;
        maxPairXorOutComputed = soln.maximumStrongPairXor(vecIn);
        assert(maxPairXorOutComputed == maxPairXorOutExpected);
//        soln.disableDebug();

        vecIn = {5, 3, 4, 3, 1, 2, 1, 6};
        maxPairXorOutExpected = 7;
        maxPairXorOutComputed = soln.maximumStrongPairXor(vecIn);
        assert(maxPairXorOutComputed == maxPairXorOutExpected);

        printf("[testMaximumStrongPairXor] All test cases passed.\n");
    }
};

int main() {
    SolutionTest testObj = SolutionTest();

    testObj.testGetSortedDedupedVec();
    testObj.testMaximumStrongPairXor();

    return 0;
}
