// LeetCode-1217: https://leetcode.com/problems/minimum-cost-to-move-chips-to-the-same-position/

#include <vector>
#include <climits>

using namespace std;

class Solution {
private:
    pair<int, int> countNumEvenOddPosChips(vector<int>& position) {
        int numOddPosChips = 0;
        int numEvenPosChips = 0;

        for (int i = 0; i < position.size(); i++) {
            if ((position[i] & 1) > 0) {
                numOddPosChips++;
            } else {
                numEvenPosChips++;
            }
        }

        return {numEvenPosChips, numOddPosChips};
    }

public:
    int minCostToMoveChips(vector<int>& position) {
        pair<int, int> numEvenOddPosChips = countNumEvenOddPosChips(position);
        int numEvenPosChips = numEvenOddPosChips.first;
        int numOddPosChips = numEvenOddPosChips.second;

        int minCost = min(numEvenPosChips, numOddPosChips);
        return minCost;
    }
};
