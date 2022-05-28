// LeetCode-1925: https://leetcode.com/problems/count-square-sum-triples/
// simple brute-force (check all pairs)

#include <cmath>

using namespace std;

class Solution {
public:
    int countTriples(int n) {
        int numTriplets = 0;

        for (int i = 1; i < n; i++) {
            int iSqr = i * i;
            for (int j = i + 1; j < n; j++) {
                int jSqr = j * j;

                int sqrsSum = iSqr + jSqr;

                int sqrsSumSqrt = (int) sqrt(sqrsSum);
                if (((sqrsSumSqrt * sqrsSumSqrt) == sqrsSum) && (sqrsSumSqrt <= n)) {
                    numTriplets += 2;
                }
            }
        }

        return numTriplets;
    }
};
