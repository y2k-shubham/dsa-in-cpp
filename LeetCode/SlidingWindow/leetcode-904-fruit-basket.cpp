// LeetCode-904: https://leetcode.com/problems/fruit-into-baskets/

#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   private:
    bool debug = false;

    void showVec(vector<int>& vec) {
        printf("\nfruitsVec is:-\n");

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

    void showFreqMap(unordered_map<int, int>& freqMap) {
        printf("\nfreqMap is:-\n");
        for (unordered_map<int, int>::iterator it = freqMap.begin(); it != freqMap.end(); it++) {
            printf("[%d] -> %d\n", it->first, it->second);
        }
    }

   public:
    friend class SolutionTest;

    int totalFruit(vector<int>& fruits) {
        int len = fruits.size();
        if (len <= 2) {
            return len;
        }

        // pick first 2 fruits
        int maxWinLen = 2;
        int maxWinLo = 0, maxWinHi = 1;

        // pick first 2 fruits (window spans from [iLo, iHi])
        int iLo = 0, iHi = 1;

        // pick first 2 fruits
        unordered_map<int, int> fruitFreqMap;
        fruitFreqMap[fruits[0]]++;
        fruitFreqMap[fruits[1]]++;

        bool updated = true;
        int iter = 0;
        while ((iLo <= iHi) && (iHi <= len) && updated && (iter <= len + 5)) {
            updated = false;
            iter++;
            if (debug) {
                printf("\n--------\n");
                printf("updated = %s\n", (updated ? "true" : "false"));
                showVec(fruits);
            }

            // expand window till there are only a max of 2 types of fruits
            while ((iHi < (len - 1)) && (fruitFreqMap.size() <= 2)) {
                iHi++;

                // pick fruit at iHi
                fruitFreqMap[fruits[iHi]]++;
                updated = true;

                if (debug) {
                    printf("\n- - - -\n");
                    printf("Expanding iLo=%d, iHi=%d\n", iLo, iHi);
                    printf("Picked fruits[iHi=%d] = %d\n", iHi, fruits[iHi]);
                    showFreqMap(fruitFreqMap);
                }

                if (fruitFreqMap.size() <= 2) {
                    int crrWinLen = iHi - iLo + 1;
                    if (crrWinLen > maxWinLen) {
                        maxWinLen = crrWinLen;
                        maxWinLo = iLo;
                        maxWinHi = iHi - 1;
                    }
                }
            }

            if (debug) {
                printf("\n--------\n");
            }

            // shrink window as long as there are more than 2 types of fruits
            while ((iLo <= iHi) && (fruitFreqMap.size() > 2)) {
                int crrFruit = fruits[iLo];

                // remove fruit at iLo
                fruitFreqMap[crrFruit]--;
                updated = true;

                if (debug) {
                    printf("\n- - - -\n");
                    printf("Shrinking iLo=%d, iHi=%d\n", iLo, iHi);
                    printf("Dropped fruits[iLo=%d] = %d\n", iLo, fruits[iLo]);
                    showFreqMap(fruitFreqMap);
                }

                if (fruitFreqMap[crrFruit] == 0) {
                    fruitFreqMap.erase(crrFruit);

                    if (fruitFreqMap.size() <= 2) {
                        int crrWinLen = iHi - iLo;
                        if ((crrWinLen >= 1) && (crrWinLen > maxWinLen)) {
                            maxWinLen = crrWinLen;
                            maxWinLo = iLo + 1;
                            maxWinHi = iHi - 1;
                        }
                    }
                }

                iLo++;
            }
        }

        return maxWinLen;
    }
};

class SolutionTest {
   public:
    void testTotalFruit() {
        Solution soln = Solution();
        vector<int> fruitsIn;
        int numOutExpected, numOutComputed;

        fruitsIn = {};
        numOutExpected = 0;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);

        fruitsIn = {2};
        numOutExpected = 1;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);

        fruitsIn = {3, 6};
        numOutExpected = 2;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);

        // soln.debug = true;
        fruitsIn = {3, 6, 3};
        numOutExpected = 3;
        numOutComputed = soln.totalFruit(fruitsIn);
        // printf("expected = %d, computed = %d\n", numOutExpected, numOutComputed);
        assert(numOutExpected == numOutComputed);
        // soln.debug = false;

        fruitsIn = {3, 6, 3, 6};
        numOutExpected = 4;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);

        fruitsIn = {3, 6, 3, 4, 6};
        numOutExpected = 3;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);

        fruitsIn = {1, 2, 1};
        numOutExpected = 3;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);

        fruitsIn = {0, 1, 2, 2};
        numOutExpected = 3;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);

        fruitsIn = {1, 2, 3, 2, 2};
        numOutExpected = 4;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);

        fruitsIn = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
        numOutExpected = 5;
        numOutComputed = soln.totalFruit(fruitsIn);
        assert(numOutExpected == numOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testTotalFruit();
    return 0;
}
