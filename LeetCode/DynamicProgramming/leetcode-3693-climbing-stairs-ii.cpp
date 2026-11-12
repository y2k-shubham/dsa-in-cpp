// LeetCode-3693: https://leetcode.com/problems/climbing-stairs-ii/

// its medium, but unsure why felt a little bit difficult to solve
// also of course can be solved in O(1) space since we only ever check last 3 costs

#include <vector>

using namespace std;

class Solution {
public:
    int climbStairs(int n, vector<int>& costs) {
        int len = costs.size();
        vector <int> minCosts(len, INT_MAX);

        for (int i = 0; i < len; i++) {
            int reachCostFromPrev1Step = (i < 0) ? INT_MAX : (costs[i] + 1 + ((i <= 0) ? 0 : minCosts[i - 1]));
            int reachCostFromPrev2Step = (i < 1) ? INT_MAX : (costs[i] + 4 + ((i <= 1) ? 0 : minCosts[i - 2]));
            int reachCostFromPrev3Step = (i < 2) ? INT_MAX : (costs[i] + 9 + ((i <= 2) ? 0 : minCosts[i - 3]));

            int minReachCost = min(reachCostFromPrev1Step, min(reachCostFromPrev2Step, reachCostFromPrev3Step));
            minCosts[i] = minReachCost;
        }

        return minCosts[len - 1];
    }
};
