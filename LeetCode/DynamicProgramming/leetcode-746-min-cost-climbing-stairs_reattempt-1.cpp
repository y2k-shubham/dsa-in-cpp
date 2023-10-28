// LeetCode-746: https://leetcode.com/problems/min-cost-climbing-stairs
// re-think space optimization (not done in following solution)

#include <vector>
#include <climits>

using namespace std;

class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int len = cost.size();
        if (len <= 1) {
            return 0;
        }

        vector<int> minReachCost(len + 1, INT_MAX);
        minReachCost[0] = minReachCost[1] = 0;

        for (int i = 2; i <= len; i++) {
            minReachCost[i] = min(
                    minReachCost[i - 1] + cost[i - 1],
                    minReachCost[i - 2] + cost[i - 2]
            );
        }

        return minReachCost[len];
    }
};
