// LeetCode-461: https://leetcode.com/problems/hamming-distance/
// pretty dumb problem; dont even bother looking

class Solution {
   public:
    int hammingDistance(int x, int y) {
        int diffs = 0;

        for (int i = 0; i < 32; i++) {
            int mask = 1 << i;

            int xMasked = x & mask;
            int yMasked = y & mask;
            if (xMasked != yMasked) {
                diffs++;
            }
        }

        return diffs;
    }
};
