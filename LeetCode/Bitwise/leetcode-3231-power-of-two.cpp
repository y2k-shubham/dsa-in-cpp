// LeetCode-3231: https://leetcode.com/problems/power-of-two/

#include <climits>

class Solution {
public:
    bool isPowerOfTwo(int n) {
        // n = abs(n); -> this is NOT required; even for negative numbers
        // i mean doing this ^ will give wrong answer for negative numbers

        if (n == 0) {
            return false;
        }
        if (n == 1) {
            return true;
        }
        if (n == INT_MIN) {
            return false;
        }

        return (n & (n - 1)) == 0;
    }
};
