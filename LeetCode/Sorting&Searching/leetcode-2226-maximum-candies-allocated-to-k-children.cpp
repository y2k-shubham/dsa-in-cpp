// LeetCode-2226: https://leetcode.com/problems/maximum-candies-allocated-to-k-children/

#include <vector>
#include <map>
#include <climits>
#include <numeric>
#include <cassert>

using namespace std;

class Solution {
private:
    map<int, int> buildFreqMap(vector<int>& vec) {
        map<int, int> freqMap;

        for (int i = 0; i < vec.size(); i++) {
            freqMap[vec[i]]++;
        }

        return freqMap;
    }

    long long countTotalCandies(vector<int>& candies) {
        long long sum = accumulate(candies.begin(), candies.end(), (long long) 0);
        return sum;
    }

    int findMinCandiesPerChild(long long sum, long long k) {
        if (sum < k) {
            return -1;
        }

        return 1;
    }

    long long findMaxCandiesPerChild(long long sum, long long k) {
        return (long long) floor((sum * 1.0) / k);
    }

    bool canGiveCandiesToEachChild(map<int, int>& freqMap, long long k, long long numCandies) {
        if (numCandies <= 0) {
            return true;
        }

        long long totalNumChildrenGotCandies = 0;

        for (auto rit = freqMap.rbegin(); rit != freqMap.rend(); rit++) {
            int numCandiesCrrPileSize = rit->first;
            int numPilesCrrPileSize = rit->second;

            long long childrenGotCandiesPerPile = numCandiesCrrPileSize / numCandies;
            long long childrenGotCandiesAllPiles = childrenGotCandiesPerPile * numPilesCrrPileSize;

            if (childrenGotCandiesAllPiles == 0) {
                break;
            } else {
                totalNumChildrenGotCandies += childrenGotCandiesAllPiles;

                if (totalNumChildrenGotCandies >= k) {
                    return true;
                }
            }
        }

        return false;
    }

public:
    friend class SolutionTest;

    int maximumCandies(vector<int>& candies, long long k) {
        long long numTotalCandies = countTotalCandies(candies);

        long long minCandiesPerChild = findMinCandiesPerChild(numTotalCandies, k);
        long long maxCandiesPerChildTheoretical = findMaxCandiesPerChild(numTotalCandies, k);
        if (minCandiesPerChild < 0) {
            return 0;
        }

        map<int, int> freqMap = buildFreqMap(candies);

        long long maxCandiesPerChildActual = minCandiesPerChild;

        long long limLo = minCandiesPerChild;
        long long limHi = maxCandiesPerChildTheoretical;
        while (limLo <= limHi) {
            long long limMid = (limLo + limHi) / 2;

            if (canGiveCandiesToEachChild(freqMap, k, limMid)) {
                maxCandiesPerChildActual = max(maxCandiesPerChildActual, limMid);
                limLo = limMid + 1;
            } else {
                limHi = limMid - 1;
            }
        }

        return maxCandiesPerChildActual;
    }
};

class SolutionTest {
public:
    void testFindMinCandiesPerChild() {
        Solution soln = Solution();
        long long sumIn;
        long long kIn;
        long long minCandiesOutExpected, minCandiesOutComputed;

        sumIn = 0;
        kIn = 0;
        minCandiesOutExpected = 1;
        minCandiesOutComputed = soln.findMinCandiesPerChild(sumIn, kIn);
        assert(minCandiesOutExpected == minCandiesOutComputed);

        sumIn = 13;
        kIn = 11;
        minCandiesOutExpected = 1;
        minCandiesOutComputed = soln.findMinCandiesPerChild(sumIn, kIn);
        assert(minCandiesOutExpected == minCandiesOutComputed);

        sumIn = 11;
        kIn = 13;
        minCandiesOutExpected = -1;
        minCandiesOutComputed = soln.findMinCandiesPerChild(sumIn, kIn);
        assert(minCandiesOutExpected == minCandiesOutComputed);
    }

    void testFindMaxCandiesPerChild() {
        Solution soln = Solution();
        long long sumIn;
        long long kIn;
        long long maxCandiesOutExpected, maxCandiesOutComputed;

        sumIn = 19;
        kIn = 3;
        maxCandiesOutExpected = 6;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 19;
        kIn = 2;
        maxCandiesOutExpected = 9;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 29;
        kIn = 4;
        maxCandiesOutExpected = 7;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 24;
        kIn = 6;
        maxCandiesOutExpected = 4;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 25;
        kIn = 6;
        maxCandiesOutExpected = 4;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 26;
        kIn = 6;
        maxCandiesOutExpected = 4;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 27;
        kIn = 6;
        maxCandiesOutExpected = 4;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 28;
        kIn = 6;
        maxCandiesOutExpected = 4;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 29;
        kIn = 6;
        maxCandiesOutExpected = 4;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);

        sumIn = 30;
        kIn = 6;
        maxCandiesOutExpected = 5;
        maxCandiesOutComputed = soln.findMaxCandiesPerChild(sumIn, kIn);
        assert(maxCandiesOutExpected == maxCandiesOutComputed);
    }

    void testCanGiveCandiesToEachChild() {
        Solution soln = Solution();
        map<int, int> freqMapIn;
        long long kIn;
        long long numCandiesIn;
        bool outExpected, outComputed;

        freqMapIn = {{5, 1},
                     {6, 1},
                     {8, 1}};
        kIn = 3;
        numCandiesIn = 1;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{5, 1},
                     {6, 1},
                     {8, 1}};
        kIn = 3;
        numCandiesIn = 2;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{5, 1},
                     {6, 1},
                     {8, 1}};
        kIn = 3;
        numCandiesIn = 3;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{5, 1},
                     {6, 1},
                     {8, 1}};
        kIn = 3;
        numCandiesIn = 4;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{5, 1},
                     {6, 1},
                     {8, 1}};
        kIn = 3;
        numCandiesIn = 5;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{5, 1},
                     {6, 1},
                     {8, 1}};
        kIn = 3;
        numCandiesIn = 6;
        outExpected = false;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{2, 1},
                     {5, 1}};
        kIn = 11;
        numCandiesIn = 0;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{2, 1},
                     {5, 1}};
        kIn = 11;
        numCandiesIn = 1;
        outExpected = false;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{2, 1},
                     {5, 1}};
        kIn = 11;
        numCandiesIn = 2;
        outExpected = false;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{1,  1},
                     {2,  3},
                     {9,  3},
                     {10, 3}};
        kIn = 3;
        numCandiesIn = 9;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{1,  1},
                     {2,  3},
                     {9,  3},
                     {10, 3}};
        kIn = 3;
        numCandiesIn = 10;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{1,  1},
                     {2,  3},
                     {9,  3},
                     {10, 3}};
        kIn = 4;
        numCandiesIn = 9;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{1,  1},
                     {2,  3},
                     {9,  3},
                     {10, 3}};
        kIn = 4;
        numCandiesIn = 10;
        outExpected = false;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{1,  1},
                     {2,  3},
                     {9,  3},
                     {10, 3}};
        kIn = 5;
        numCandiesIn = 9;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{1,  1},
                     {2,  3},
                     {9,  3},
                     {10, 3}};
        kIn = 6;
        numCandiesIn = 9;
        outExpected = true;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);

        freqMapIn = {{1,  1},
                     {2,  3},
                     {9,  3},
                     {10, 3}};
        kIn = 7;
        numCandiesIn = 9;
        outExpected = false;
        outComputed = soln.canGiveCandiesToEachChild(freqMapIn, kIn, numCandiesIn);
        assert(outExpected == outComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testFindMinCandiesPerChild();
    solnTest.testFindMaxCandiesPerChild();
    solnTest.testCanGiveCandiesToEachChild();

    return 0;
}
