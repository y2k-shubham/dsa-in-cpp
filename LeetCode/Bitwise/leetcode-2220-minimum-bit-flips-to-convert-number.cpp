// LeetCode-2220: https://leetcode.com/problems/minimum-bit-flips-to-convert-number/

using namespace std;

class Solution {
private:
    int countSetBits(int n) {
        int numSetBits = 0;

        while (n > 0) {
            if ((n & 1) == 1) {
                numSetBits++;
            }
            n = n >> 1;
        }

        return numSetBits;
    }

public:
    int minBitFlips(int start, int goal) {
        if (start == goal) {
            return 0;
        }

        int flipBitMask = start ^ goal;
        return countSetBits(flipBitMask);
    }
};
