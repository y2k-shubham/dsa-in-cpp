// LeetCode-1578: https://leetcode.com/problems/minimum-time-to-make-rope-colorful/
// incomplete

#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

class Solution {
private:
    pair<int, int> findDedupingCost(
            vector<int>& costs,
            string& colors,
            int iLo
    ) {
        char crrSeqColor = colors.at(iLo);

        int totalCost = costs[iLo];
        int maxCost = costs[iLo];

        int j;
        for (j = iLo + 1; j < costs.size(); j++) {
            if (colors.at(j) != crrSeqColor) {
                break;
            }

            maxCost = max(maxCost, costs[j]);
            totalCost += costs[j];
        }

        int removalCost = (j == (iLo + 1)) ? 0 : (totalCost - maxCost);
        return {removalCost, j};
    }

public:
    friend class SolutionTest;

    int minCost(string colors, vector<int>& neededTime) {
        int totalRemovalCost = 0;
        for (int i = 0; i < neededTime.size(); i++) {
            pair<int, int> crrSeqRes = findDedupingCost(neededTime, colors, i);
            totalRemovalCost += crrSeqRes.first;
            i = crrSeqRes.second;
        }

        return totalRemovalCost;
    }
};

class SolutionTest {
public:
    void testFindDedupingCost() {
        Solution soln = Solution();
        vector<int> costs;
        string colors;
        int iLo;
        int minCostOutExpected, minCostOutComputed;

        costs = {6, 9, 2, 11};
        colors = "abba";

        iLo = 0;
        minCostOutExpected = 0;
        minCostOutComputed = soln.findDedupingCost(costs, colors, iLo).first;
        assert(minCostOutExpected == minCostOutComputed);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();
    solnTest.testFindDedupingCost();
    return 0;
}
