// LeetCode-477: https://leetcode.com/problems/total-hamming-distance/

class Solution {
   public:
    int totalHammingDistance(vector<int>& nums) {
        int len = nums.size();
        if (len <= 0) {
            return 0;
        }

        int totalBitDiffs = 0;
        for (int bitPos = 0; bitPos < 32; bitPos++) {
            int bitMask = 1 << bitPos;

            int numSet = 0;
            int numUnset = 0;
            for (int i = 0; i < len; i++) {
                int crrVal = nums[i];

                if ((crrVal & bitMask) > 0) {
                    numSet++;
                } else {
                    numUnset++;
                }
            }

            int crrBitDiffs = numSet * numUnset;
            totalBitDiffs += crrBitDiffs;
        }

        return totalBitDiffs;
    }
};
