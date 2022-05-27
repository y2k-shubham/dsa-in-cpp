// LeetCode-1551: https://leetcode.com/problems/minimum-operations-to-make-array-equal/
// LC April 2021 challenge: https://leetcode.com/explore/challenge/card/april-leetcoding-challenge-2021/593/week-1-april-1st-april-7th/3698/
#include <cstdio>
#include <iostream>

using namespace std;

class Solution {
   public:
    int sumOfAP(int a, int d, int n) {
        int l = a + (n - 1) * d;
        int sum = (n * (a + l)) / 2;

        return sum;
    }

    int findTargetVal(int n) {
        int sum = sumOfAP(1, 2, n);
        int targetVal = sum / n;

        return targetVal;
    }

    int findMinOps(int n, int targetVal) {
        int numOps = 0;
        for (int i = 1; i < targetVal; i += 2) {
            numOps += targetVal - i;
        }

        return numOps;
    }

    int minOperations(int n) {
      // final value for each element
        int targetVal = findTargetVal(n);

        //printf("for n=%d, targetVal=%d\n", n, targetVal);
        
        return findMinOps(n, targetVal);
    }
};
