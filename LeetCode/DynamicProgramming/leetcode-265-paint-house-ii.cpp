// LeetCode-265: https://leetcode.com/problems/paint-house-ii/
// Definitely NOT a hard problem; just a generalized version of 'Paint House I'

#include <vector>

using namespace std;

class Solution {
private:
    vector<vector<int>> createMinCostMat(vector<vector<int>>& costMat) {
        int n = costMat.size();
        int k = costMat[0].size();

        vector<vector<int>> minCostMat(n);
        minCostMat[0] = costMat[0];

        for (int j = 1; j < n; j++) {
            minCostMat[j] = vector<int>(k, INT_MAX);
        }

        return minCostMat;
    }

    int findMinCostExcludingIdx(vector<int>& vec, int excludeIdx) {
        int minCost = INT_MAX;

        for (int j = 0; j < vec.size(); j++) {
            if (j != excludeIdx) {
                minCost = min(minCost, vec[j]);
            }
        }

        return minCost;
    }

    void fillMinCostMat(vector<vector<int>>& costMat, vector<vector<int>>& minCostMat) {
        int n = costMat.size();
        int k = costMat[0].size();

        for (int j = 1; j < n; j++) {
            vector<int> prevMinCostVec = minCostMat[j - 1];
            for (int i = 0; i < k; i++) {
                minCostMat[j][i] = costMat[j][i] + findMinCostExcludingIdx(prevMinCostVec, i);
            }
        }
    }

public:
    int minCostII(vector<vector<int>>& costs) {
        int n = costs.size();
        int k = costs[0].size();

        if (min(n, k) < 1) {
            return 0;
        }
        if (n == 1) {
            vector<int> costVec = costs[0];
            return findMinCostExcludingIdx(costVec, -1);
        }

        vector<vector<int>> minCostMat = createMinCostMat(costs);
        fillMinCostMat(costs, minCostMat);

        vector<int> minCostVec = minCostMat[n - 1];
        return findMinCostExcludingIdx(minCostVec, -1);
    }
};
