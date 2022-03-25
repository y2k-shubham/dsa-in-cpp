// LeetCode-1029: https://leetcode.com/problems/two-city-scheduling/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class Solution {
   private:
    vector<pair<int, pair<int, int>>> buildDiffCostVec(vector<vector<int>>& costs) {
        vector<pair<int, pair<int, int>>> diffCostVec;
        for (int i = 0; i < costs.size(); i++) {
            int aCost = costs[i][0];
            int bCost = costs[i][1];
            int diffCost = aCost - bCost;

            diffCostVec.push_back({diffCost, {aCost, bCost}});
        }

        return diffCostVec;
    }

   public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        // sort costs by ascending order diffs aCost-bCost
        vector<pair<int, pair<int, int>>> diffCostVec = buildDiffCostVec(costs);
        sort(diffCostVec.begin(), diffCostVec.end());

        int len2N = costs.size();
        int lenN = len2N / 2;

        vector<pair<int, int>> aAssign;
        vector<pair<int, int>> bAssign;

        int i;
        // then greedily pick first half items for A (where aCost-bCost is relatively small)
        int totalACost = 0;
        for (i = 0; i < lenN; i++) {
            pair<int, int> tup = diffCostVec[i].second;

            totalACost += tup.first;
            aAssign.push_back(tup);
        }
        // then greedily pick next half items for B (where aCost-bCost is relatively big)
        int totalBCost = 0;
        while (i < len2N) {
            pair<int, int> tup = diffCostVec[i].second;

            totalBCost += tup.second;
            bAssign.push_back(tup);

            i++;
        }

        return totalACost + totalBCost;
    }
};
