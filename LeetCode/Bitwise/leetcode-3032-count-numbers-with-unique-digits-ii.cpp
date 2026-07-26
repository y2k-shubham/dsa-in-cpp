// LeetCode-3032: https://leetcode.com/problems/count-numbers-with-unique-digits-ii/

// Premium
// Companies: <unknown>

class Solution {
private:
    bool hasUniqueDigits(int n) {
        int digitSeenBitmask = 0;

        while (n > 0) {
            // extract current (least significant) digit from n
            int digit = n % 10;
            n /= 10;

            // check if this digit was already seen
            if ((digitSeenBitmask & (1 << digit)) > 0) {
                return false;
            }

            // update digit bitmask
            digitSeenBitmask |= 1 << digit;
        }

        return true;
    }

public:
    int numberCount(int a, int b) {
        int numUniqueDigitNums = 0;
        for (int i = a; i <= b; i++) {
            if (hasUniqueDigits(i)) {
                numUniqueDigitNums++;
            }
        }

        return numUniqueDigitNums;
    }
};
