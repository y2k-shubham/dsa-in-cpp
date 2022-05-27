// LeetCode-1518: https://leetcode.com/problems/water-bottles/

class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int numDrunkBottles = 0;

        int numFullBottles = numBottles;
        int numEmptyBottles = 0;
        while ((numFullBottles > 0) || (numEmptyBottles >= numExchange)) {
            if (numFullBottles > 0) {
                numDrunkBottles += numFullBottles;
                numEmptyBottles += numFullBottles;
                numFullBottles = 0;
            } else {
                numFullBottles = numEmptyBottles / numExchange;
                numEmptyBottles = numEmptyBottles % numExchange;
            }
        }

        return numDrunkBottles;
    }
};
