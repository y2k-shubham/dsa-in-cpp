// LeetCode-2139: https://leetcode.com/problems/minimum-moves-to-reach-target-score/

class Solution {
   public:
    int minMoves(int target, int maxDoubles) {
        int numMoves = 0;

        while (target > 1) {
            if (maxDoubles > 0) {
                // 1 extra increment operation for odd numbers
                if ((target % 2) == 1) {
                    numMoves++;
                }

                // until double moves not exhausted, use them
                target /= 2;
                numMoves++;
                maxDoubles--;
            } else {
                // if double moves exhausted, then directly calculate no of increment moves
                numMoves += target - 1;
                // and directly set target to 1
                // (note that target=1 stmt should come after preceding moves-increment operation)
                target = 1;
            }
        }

        return numMoves;
    }
};
