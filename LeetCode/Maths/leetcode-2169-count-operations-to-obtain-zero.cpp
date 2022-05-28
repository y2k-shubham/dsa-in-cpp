// LeetCode-2169: https://leetcode.com/problems/count-operations-to-obtain-zero/
// why?

#include <iostream>

using namespace std;

class Solution {
public:
    int countOperations(int num1, int num2) {
        int numOps = 0;

        while (min(num1, num2) > 0) {
            if (num1 >= num2) {
                num1 -= num2;
            } else {
                num2 -= num1;
            }

            ++numOps;
        }

        return numOps;
    }
};
