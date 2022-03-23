// LeetCode-991: https://leetcode.com/problems/broken-calculator/

#include <cmath>
#include <cstdio>
#include <iostream>

using namespace std;

#define isEven(n) (((n & 1) == 1) ? false : true)

class Solution {
   public:
    int brokenCalc(int startValue, int target) {
        int numSteps = 0;
        while (target != startValue) {
            if (target < startValue) {
                numSteps += startValue - target;
                break;
            }

            if (isEven(target)) {
                if (startValue < (target / 2)) {
                    target /= 2;
                    numSteps++;
                } else {
                    int numExtraStepsHalveFirst = 1 + (startValue - (target / 2));
                    int numExtraStepsIncrementFirst = ((2 * startValue) - target) + 1;
                    numSteps += min(numExtraStepsHalveFirst, numExtraStepsIncrementFirst);
                    break;
                }
            } else {
                target += 1;
                numSteps++;
            }
        }

        return numSteps;
    }
};
