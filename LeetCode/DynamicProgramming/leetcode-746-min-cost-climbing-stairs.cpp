// LeetCode-746: https://leetcode.com/problems/min-cost-climbing-stairs/

#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();

        int prev2 = 0;
        int prev1 = 0;

        for (int i = 2; i <= len; i++) {
            int crr = min(prev2 + cost[i - 2], prev1 + cost[i - 1]);

            prev2 = prev1;
            prev1 = crr;
        }

        return prev1;
    }
};

class SolutionTest {
public:
    void testMinCostClimbingStairs() {
        Solution soln = Solution();
        vector<int> costIn;
        int minCostOutExpected;
        int minCostOutComputed;

//        cout << "puchi" << endl;

        costIn = {10, 15, 20};
        minCostOutExpected = 15;
        minCostOutComputed = soln.minCostClimbingStairs(costIn);
//        cout << minCostOutComputed << endl;
        assert(minCostOutComputed == minCostOutExpected);

        costIn = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
        minCostOutExpected = 6;
        minCostOutComputed = soln.minCostClimbingStairs(costIn);
//        cout << minCostOutComputed << endl;
        assert(minCostOutComputed == minCostOutExpected);
    }
};

int main() {
    SolutionTest solnTest = SolutionTest();

    solnTest.testMinCostClimbingStairs();

    return 0;
}
